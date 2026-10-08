// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/tile_layer.cpp
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_script_macros.h
//
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------



#include "pdg_project.h"

#define PDG_COMPILING_SCRIPT_IMPL

#include "pdg_script_interface.h"
#include "pdg_script_impl.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>

namespace pdg
{

    static JSStringRef symbol_tileType = 0;
    static JSStringRef symbol_facing = 0;

    static bool s_TileLayer_InNewFromCpp = false;

    JSObjectRef TileLayer_newFromCpp(JSContextRef ctx, TileLayer* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, TileLayer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, TileLayer_class());
        cppObj->mEventEmitterScriptObj = obj; cppObj->mSpriteLayerScriptObj = obj; cppObj->mTileLayerScriptObj = obj;
        return obj;
    }

    JSObjectRef TileLayer_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_TileLayer_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "TileLayer" " cannot be instantiated with \\'new\\'. Use the factory function: pdg." "createTileLayer" "()')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        TileLayer* cppObj = New_TileLayer(argumentCount, arguments, exception);
        if (exception && *exception) return nullptr;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            std::ostringstream excpt_;
            excpt_ << "throw '" << s_SavedError.str().c_str() << "'";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        };
        if (!cppObj)
        {
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to create C++ native " "TileLayer" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, TileLayer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, TileLayer_class());
        return obj;
    }

    JSClassRef TileLayer_class()
    {

        static JSStaticValue TileLayer_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction TileLayer_staticFunctions[] =
        {
            { "addHandler", TileLayer_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", TileLayer_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", TileLayer_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", TileLayer_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", TileLayer_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "setQueryBits", TileLayer_SetQueryBits, kJSPropertyAttributeDontDelete },
            { "getQueryBits", TileLayer_GetQueryBits, kJSPropertyAttributeDontDelete },
            { "setCamera", TileLayer_SetCamera, kJSPropertyAttributeDontDelete },
            { "getCamera", TileLayer_GetCamera, kJSPropertyAttributeDontDelete },
            { "getEffectiveCamera", TileLayer_GetEffectiveCamera, kJSPropertyAttributeDontDelete },
            { "setCameraParallax", TileLayer_SetCameraParallax, kJSPropertyAttributeDontDelete },
            { "get""WorldBounds", TileLayer_GetWorldBounds, kJSPropertyAttributeDontDelete },
            { "set""WorldBounds", TileLayer_SetWorldBounds, kJSPropertyAttributeDontDelete },
            { "createParticle", TileLayer_CreateParticle, kJSPropertyAttributeDontDelete },
            { "addParticle", TileLayer_AddParticle, kJSPropertyAttributeDontDelete },
            { "removeParticle", TileLayer_RemoveParticle, kJSPropertyAttributeDontDelete },
            { "removeAllParticles", TileLayer_RemoveAllParticles, kJSPropertyAttributeDontDelete },
            { "getParticleTrailCount", TileLayer_GetParticleTrailCount, kJSPropertyAttributeDontDelete },
            { "getParticleCount", TileLayer_GetParticleCount, kJSPropertyAttributeDontDelete },
            { "getNthParticle", TileLayer_GetNthParticle, kJSPropertyAttributeDontDelete },
            { "setMaxParticles", TileLayer_SetMaxParticles, kJSPropertyAttributeDontDelete },
            { "getMaxParticles", TileLayer_GetMaxParticles, kJSPropertyAttributeDontDelete },
            { "createParticleEmitter", TileLayer_CreateParticleEmitter, kJSPropertyAttributeDontDelete },
            { "removeParticleEmitter", TileLayer_RemoveParticleEmitter, kJSPropertyAttributeDontDelete },
            { "removeAllParticleEmitters", TileLayer_RemoveAllParticleEmitters, kJSPropertyAttributeDontDelete },
            { "setSerializationFlags", TileLayer_SetSerializationFlags, kJSPropertyAttributeDontDelete },
            { "startAnimations", TileLayer_StartAnimations, kJSPropertyAttributeDontDelete },
            { "stopAnimations", TileLayer_StopAnimations, kJSPropertyAttributeDontDelete },
            { "hide", TileLayer_Hide, kJSPropertyAttributeDontDelete },
            { "show", TileLayer_Show, kJSPropertyAttributeDontDelete },
            { "isHidden", TileLayer_IsHidden, kJSPropertyAttributeDontDelete },
            { "fadeIn", TileLayer_FadeIn, kJSPropertyAttributeDontDelete },
            { "fadeOut", TileLayer_FadeOut, kJSPropertyAttributeDontDelete },
            { "moveBehind", TileLayer_MoveBehind, kJSPropertyAttributeDontDelete },
            { "moveInFrontOf", TileLayer_MoveInFrontOf, kJSPropertyAttributeDontDelete },
            { "moveToFront", TileLayer_MoveToFront, kJSPropertyAttributeDontDelete },
            { "moveToBack", TileLayer_MoveToBack, kJSPropertyAttributeDontDelete },
            { "getZOrder", TileLayer_GetZOrder, kJSPropertyAttributeDontDelete },
            { "findSprite", TileLayer_FindSprite, kJSPropertyAttributeDontDelete },
            { "getNthSprite", TileLayer_GetNthSprite, kJSPropertyAttributeDontDelete },
            { "getSpriteZOrder", TileLayer_GetSpriteZOrder, kJSPropertyAttributeDontDelete },
            { "isSpriteBehind", TileLayer_IsSpriteBehind, kJSPropertyAttributeDontDelete },
            { "hasSprite", TileLayer_HasSprite, kJSPropertyAttributeDontDelete },
            { "addSprite", TileLayer_AddSprite, kJSPropertyAttributeDontDelete },
            { "removeSprite", TileLayer_RemoveSprite, kJSPropertyAttributeDontDelete },
            { "removeAllSprites", TileLayer_RemoveAllSprites, kJSPropertyAttributeDontDelete },
            { "enableCollisions", TileLayer_EnableCollisions, kJSPropertyAttributeDontDelete },
            { "disableCollisions", TileLayer_DisableCollisions, kJSPropertyAttributeDontDelete },
            { "enableCollisionsWithLayer", TileLayer_EnableCollisionsWithLayer, kJSPropertyAttributeDontDelete },
            { "disableCollisionsWithLayer", TileLayer_DisableCollisionsWithLayer, kJSPropertyAttributeDontDelete },
            { "createSprite", TileLayer_CreateSprite, kJSPropertyAttributeDontDelete },
#ifndef PDG_NO_GUI
            { "getSpritePort", TileLayer_GetSpritePort, kJSPropertyAttributeDontDelete },
            { "setSpritePort", TileLayer_SetSpritePort, kJSPropertyAttributeDontDelete },
            { "layerToPortPoint", TileLayer_LayerToPortPoint, kJSPropertyAttributeDontDelete },
            { "layerToPortOffset", TileLayer_LayerToPortOffset, kJSPropertyAttributeDontDelete },
            { "layerToPortVector", TileLayer_LayerToPortVector, kJSPropertyAttributeDontDelete },
            { "layerToPortRect", TileLayer_LayerToPortRect, kJSPropertyAttributeDontDelete },
            { "layerToPortQuad", TileLayer_LayerToPortQuad, kJSPropertyAttributeDontDelete },
            { "portToLayerPoint", TileLayer_PortToLayerPoint, kJSPropertyAttributeDontDelete },
            { "portToLayerOffset", TileLayer_PortToLayerOffset, kJSPropertyAttributeDontDelete },
            { "portToLayerVector", TileLayer_PortToLayerVector, kJSPropertyAttributeDontDelete },
            { "portToLayerRect", TileLayer_PortToLayerRect, kJSPropertyAttributeDontDelete },
            { "portToLayerQuad", TileLayer_PortToLayerQuad, kJSPropertyAttributeDontDelete },
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            { "setGravity", TileLayer_SetGravity, kJSPropertyAttributeDontDelete },
            { "setUseChipmunkPhysics", TileLayer_SetUseChipmunkPhysics, kJSPropertyAttributeDontDelete },
            { "setStaticLayer", TileLayer_SetStaticLayer, kJSPropertyAttributeDontDelete },
            { "setDamping", TileLayer_SetDamping, kJSPropertyAttributeDontDelete },
            { "getSpace", TileLayer_GetSpace, kJSPropertyAttributeDontDelete },
#endif
            { "setWorldSize", TileLayer_SetWorldSize, kJSPropertyAttributeDontDelete },
            { "getWorldSize", TileLayer_GetWorldSize, kJSPropertyAttributeDontDelete },
            { "defineTileSet", TileLayer_DefineTileSet, kJSPropertyAttributeDontDelete },
            { "loadMapData", TileLayer_LoadMapData, kJSPropertyAttributeDontDelete },
            { "getMapData", TileLayer_GetMapData, kJSPropertyAttributeDontDelete },
            { "getTileSetImage", TileLayer_GetTileSetImage, kJSPropertyAttributeDontDelete },
            { "getTileSize", TileLayer_GetTileSize, kJSPropertyAttributeDontDelete },
            { "getTileTypeAt", TileLayer_GetTileTypeAt, kJSPropertyAttributeDontDelete },
            { "getTileTypeAndFacingAt", TileLayer_GetTileTypeAndFacingAt, kJSPropertyAttributeDontDelete },
            { "setTileTypeAt", TileLayer_SetTileTypeAt, kJSPropertyAttributeDontDelete },
            { "checkCollision", TileLayer_CheckCollision, kJSPropertyAttributeDontDelete },
            { "on", TileLayer_On, kJSPropertyAttributeDontDelete },
            { "onCollideSprite", TileLayer_OnCollideSprite, kJSPropertyAttributeDontDelete },
            { "onCollideWall", TileLayer_OnCollideWall, kJSPropertyAttributeDontDelete },
            { "onOffscreen", TileLayer_OnOffscreen, kJSPropertyAttributeDontDelete },
            { "onOnscreen", TileLayer_OnOnscreen, kJSPropertyAttributeDontDelete },
            { "onExitLayer", TileLayer_OnExitLayer, kJSPropertyAttributeDontDelete },
            { "onAnimationLoop", TileLayer_OnAnimationLoop, kJSPropertyAttributeDontDelete },
            { "onAnimationEnd", TileLayer_OnAnimationEnd, kJSPropertyAttributeDontDelete },
            { "onFadeComplete", TileLayer_OnFadeComplete, kJSPropertyAttributeDontDelete },
            { "onFadeInComplete", TileLayer_OnFadeInComplete, kJSPropertyAttributeDontDelete },
            { "onFadeOutComplete", TileLayer_OnFadeOutComplete, kJSPropertyAttributeDontDelete },
            { "onMouseEnter", TileLayer_OnMouseEnter, kJSPropertyAttributeDontDelete },
            { "onMouseLeave", TileLayer_OnMouseLeave, kJSPropertyAttributeDontDelete },
            { "onMouseDown", TileLayer_OnMouseDown, kJSPropertyAttributeDontDelete },
            { "onMouseUp", TileLayer_OnMouseUp, kJSPropertyAttributeDontDelete },
            { "onMouseClick", TileLayer_OnMouseClick, kJSPropertyAttributeDontDelete },
            { "onErasePort", TileLayer_OnErasePort, kJSPropertyAttributeDontDelete },
            { "onPreDrawLayer", TileLayer_OnPreDrawLayer, kJSPropertyAttributeDontDelete },
            { "onPostDrawLayer", TileLayer_OnPostDrawLayer, kJSPropertyAttributeDontDelete },
            { "onDrawPortComplete", TileLayer_OnDrawPortComplete, kJSPropertyAttributeDontDelete },
            { "onAnimationStart", TileLayer_OnAnimationStart, kJSPropertyAttributeDontDelete },
            { "onPreAnimateLayer", TileLayer_OnPreAnimateLayer, kJSPropertyAttributeDontDelete },
            { "onPostAnimateLayer", TileLayer_OnPostAnimateLayer, kJSPropertyAttributeDontDelete },
            { "onAnimationComplete", TileLayer_OnAnimationComplete, kJSPropertyAttributeDontDelete },
            { "onLayerFadeInComplete", TileLayer_OnLayerFadeInComplete, kJSPropertyAttributeDontDelete },
            { "onLayerFadeOutComplete", TileLayer_OnLayerFadeOutComplete, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "TileLayer";
            definition.staticFunctions = TileLayer_staticFunctions;
            definition.staticValues = TileLayer_staticValues;
            definition.callAsConstructor = TileLayer_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef TileLayer_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "IEventHandler" " object:") );
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
#ifndef PDG_NO_GUI

    JSValueRef TileLayer_GetSpritePort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Port* port = self->getSpritePort();
        if (!port) return JSValueMakeNull(ctx);
        if (!port->mPortScriptObj)
        {
            return Port_newFromCpp(ctx, port);
        }
        else
        {
            return port->mPortScriptObj;
        };
    }
    JSValueRef TileLayer_SetSpritePort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Port* port = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef port_ = JSValueToObject(ctx, arguments[1 -1], exception);
            port = Port_getCppObject(port_);
        }
        if (!port)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Port"" (""port"")");
        self->setSpritePort(port);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_LayerToPortPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Point p;
            auto p_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], p, exception);
            if (!p_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*p_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            Point out = self->layerToPort(p);
            return JSC_PointToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_LayerToPortOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Offset o;
            auto o_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], o, exception);
            if (!o_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*o_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            Offset out = self->layerToPort(o);
            return JSC_OffsetToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_LayerToPortVector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Vector v;
            auto v_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], v, exception);
            if (!v_isVector.has_value()) { return JSValueMakeNull(ctx); }
            if (!*v_isVector)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
            };
            Vector out = self->layerToPort(v);
            return JSC_VectorToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_LayerToPortRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::RotatedRect r;
            auto r_isRotatedRect = JSC_ValueIsRotatedRect(ctx, arguments[1 -1], r, exception);
            if (!r_isRotatedRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*r_isRotatedRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "RotatedRect", arguments[1 -1]);
            };
            RotatedRect out = self->layerToPort(r);
            return JSC_RectToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_LayerToPortQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Quad q;
            auto q_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], q, exception);
            if (!q_isQuad.has_value()) { return JSValueMakeNull(ctx); }
            if (!*q_isQuad)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
            };
            Quad out = self->layerToPort(q);
            return JSC_QuadToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_PortToLayerPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Point p;
            auto p_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], p, exception);
            if (!p_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*p_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            Point out = self->portToLayer(p);
            return JSC_PointToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_PortToLayerOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Offset o;
            auto o_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], o, exception);
            if (!o_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*o_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            Offset out = self->portToLayer(o);
            return JSC_OffsetToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_PortToLayerVector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Vector v;
            auto v_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], v, exception);
            if (!v_isVector.has_value()) { return JSValueMakeNull(ctx); }
            if (!*v_isVector)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
            };
            Vector out = self->portToLayer(v);
            return JSC_VectorToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_PortToLayerRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::RotatedRect r;
            auto r_isRotatedRect = JSC_ValueIsRotatedRect(ctx, arguments[1 -1], r, exception);
            if (!r_isRotatedRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*r_isRotatedRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "RotatedRect", arguments[1 -1]);
            };
            RotatedRect out = self->portToLayer(r);
            return JSC_RectToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_PortToLayerQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Quad q;
            auto q_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], q, exception);
            if (!q_isQuad.has_value()) { return JSValueMakeNull(ctx); }
            if (!*q_isQuad)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
            };
            Quad out = self->portToLayer(q);
            return JSC_QuadToValue(ctx, out, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
#endif

    JSValueRef TileLayer_SetQueryBits(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""bits"")");
        double bits = JSValueToNumber(ctx, arguments[1 -1], exception);
        if(!std::isfinite(bits)||bits<0||bits>4294967295.0||std::floor(bits)!=bits)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned 32-bit query bits" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        self->setQueryBits(uint32_t(bits)); return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_GetQueryBits(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        return JSValueMakeNumber(ctx, self->getQueryBits());
    }
    JSValueRef TileLayer_SetCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        if (!argumentCount || JSValueIsNull(ctx, arguments[0]) || JSValueIsUndefined(ctx, arguments[0]))
        {
            self->setCamera(nullptr); return JSValueMakeUndefined(ctx);
        }
        else
        {
            ;
            try
            {
                if (!JSValueIsObjectOfClass(ctx, arguments[0], Camera_class()))
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Camera or null" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                Camera* camera = 0;
                if (JSValueIsObject(ctx, arguments[1 -1]))
                {
                    JSObjectRef camera_ = JSValueToObject(ctx, arguments[1 -1], exception);
                    camera = Camera_getCppObject(camera_);
                }
                if (!camera)
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""camera"")"); self->setCamera(camera); return JSValueMakeUndefined(ctx);
            }
            catch(const std::exception& error)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);
            }
        }
    }
    JSValueRef TileLayer_GetCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        auto* camera=self->getCamera(); if (!camera) return JSValueMakeNull(ctx);
        if (!camera->mCameraScriptObj)
        {
            return Camera_newFromCpp(ctx, camera);
        }
        else
        {
            return camera->mCameraScriptObj;
        };
    }
    JSValueRef TileLayer_GetEffectiveCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        auto* camera=self->getEffectiveCamera(); if (!camera) return JSValueMakeNull(ctx);
        if (!camera->mCameraScriptObj)
        {
            return Camera_newFromCpp(ctx, camera);
        }
        else
        {
            return camera->mCameraScriptObj;
        };
    }
    JSValueRef TileLayer_SetCameraParallax(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""movementRatio"")");
            double movementRatio = (argumentCount<1) ? 1 : JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""zoomRatio"")");
            double zoomRatio = (argumentCount<2) ? 1 : JSValueToNumber(ctx, arguments[2 -1], exception); self->setCameraParallax(movementRatio,zoomRatio); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_GetWorldBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Rect theWorldBounds = self->getWorldBounds();
        return JSC_RectToValue(ctx, theWorldBounds, exception);
    }
    JSValueRef TileLayer_SetWorldBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            pdg::Rect bounds;
            auto bounds_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], bounds, exception);
            if (!bounds_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*bounds_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
            };
            self->setWorldBounds(bounds); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_CreateParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=self->createParticle(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mParticleScriptObj)
            {
                return Particle_newFromCpp(ctx, result);
            }
            else
            {
                return result->mParticleScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_AddParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); Particle* value = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef value_ = JSValueToObject(ctx, arguments[1 -1], exception);
                value = Particle_getCppObject(value_);
            }
            if (!value)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Particle"" (""value"")"); self->addParticle(value); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_RemoveParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); Particle* value = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef value_ = JSValueToObject(ctx, arguments[1 -1], exception);
                value = Particle_getCppObject(value_);
            }
            if (!value)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Particle"" (""value"")"); self->removeParticle(value); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_RemoveAllParticles(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->removeAllParticles(); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_GetParticleTrailCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getParticleTrailCount());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_GetParticleCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getParticleCount());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_GetNthParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if (!std::isfinite(value) || value < 0 || value > UINT32_MAX || std::floor(value)!=value) throw std::invalid_argument("Expected a particle count or index"); auto* result=self->getNthParticle(static_cast<uint32_t>(value)); if (!result) return JSValueMakeNull(ctx);
            if (!result->mParticleScriptObj)
            {
                return Particle_newFromCpp(ctx, result);
            }
            else
            {
                return result->mParticleScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_SetMaxParticles(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if (!std::isfinite(value) || value < 0 || value > UINT32_MAX || std::floor(value)!=value) throw std::invalid_argument("Expected a particle count or index"); self->setMaxParticles(static_cast<uint32_t>(value)); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_GetMaxParticles(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMaxParticles());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_CreateParticleEmitter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=self->createParticleEmitter(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mParticleEmitterScriptObj)
            {
                return ParticleEmitter_newFromCpp(ctx, result);
            }
            else
            {
                return result->mParticleEmitterScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_RemoveParticleEmitter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); ParticleEmitter* value = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef value_ = JSValueToObject(ctx, arguments[1 -1], exception);
                value = ParticleEmitter_getCppObject(value_);
            }
            if (!value)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""ParticleEmitter"" (""value"")"); self->removeParticleEmitter(value); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_RemoveAllParticleEmitters(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->removeAllParticleEmitters(); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef TileLayer_SetSerializationFlags(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""flags"")");
        uint32 flags = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->setSerializationFlags(flags);
        return thisObject;
    }
    JSValueRef TileLayer_StartAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->startAnimations();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_StopAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->stopAnimations();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_Hide(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->hide();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_Show(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->show();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_IsHidden(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool hidden = self->isHidden();
        return JSValueMakeBoolean(ctx, hidden);
    }
    JSValueRef TileLayer_FadeIn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeIn(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeIn(durationSeconds);
        }
        return thisObject;
    }
    JSValueRef TileLayer_FadeOut(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeOut(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeOut(durationSeconds);
        }
        return thisObject;
    }
    JSValueRef TileLayer_MoveBehind(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        SpriteLayer* layer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef layer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            layer = SpriteLayer_getCppObject(layer_);
        }
        if (!layer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""layer"")");
        self->moveBehind(layer);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_MoveInFrontOf(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        SpriteLayer* layer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef layer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            layer = SpriteLayer_getCppObject(layer_);
        }
        if (!layer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""layer"")");
        self->moveInFrontOf(layer);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_MoveToFront(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToFront();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_MoveToBack(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToBack();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_IsSpriteBehind(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        Sprite* otherSprite = 0;
        if (JSValueIsObject(ctx, arguments[2 -1]))
        {
            JSObjectRef otherSprite_ = JSValueToObject(ctx, arguments[2 -1], exception);
            otherSprite = Sprite_getCppObject(otherSprite_);
        }
        if (!otherSprite)
            return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Sprite"" (""otherSprite"")");
        bool behind = self->isSpriteBehind(sprite, otherSprite);
        return JSValueMakeBoolean(ctx, behind);
    }
    JSValueRef TileLayer_GetZOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int zorder = self->getZOrder();
        return JSValueMakeNumber(ctx, zorder);
    }
    JSValueRef TileLayer_GetSpriteZOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        int zorder = self->getSpriteZOrder(sprite);
        return JSValueMakeNumber(ctx, zorder);
    }
    JSValueRef TileLayer_FindSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        Sprite* sprite = self->findSprite(id);
        if (!sprite) return JSValueMakeNull(ctx);
        if (!sprite->mSpriteScriptObj)
        {
            return Sprite_newFromCpp(ctx, sprite);
        }
        else
        {
            return sprite->mSpriteScriptObj;
        };
    }
    JSValueRef TileLayer_GetNthSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
        int32 index = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        Sprite* sprite = self->getNthSprite(index);
        if (!sprite) return JSValueMakeNull(ctx);
        if (!sprite->mSpriteScriptObj)
        {
            return Sprite_newFromCpp(ctx, sprite);
        }
        else
        {
            return sprite->mSpriteScriptObj;
        };
    }
    JSValueRef TileLayer_HasSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        bool found = self->hasSprite(sprite);
        return JSValueMakeBoolean(ctx, found);
    }
    JSValueRef TileLayer_AddSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            Sprite* newSprite = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef newSprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
                newSprite = Sprite_getCppObject(newSprite_);
            }
            if (!newSprite)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""newSprite"")");
            self->addSprite(newSprite);
            return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef TileLayer_RemoveSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            Sprite* oldSprite = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef oldSprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
                oldSprite = Sprite_getCppObject(oldSprite_);
            }
            if (!oldSprite)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""oldSprite"")");
            self->removeSprite(oldSprite);
            return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef TileLayer_RemoveAllSprites(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->removeAllSprites();
            return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef TileLayer_EnableCollisions(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->enableCollisions();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_DisableCollisions(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->disableCollisions();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_EnableCollisionsWithLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        SpriteLayer* otherLayer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef otherLayer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            otherLayer = SpriteLayer_getCppObject(otherLayer_);
        }
        if (!otherLayer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""otherLayer"")");
        self->enableCollisionsWithLayer(otherLayer);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_DisableCollisionsWithLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        SpriteLayer* otherLayer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef otherLayer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            otherLayer = SpriteLayer_getCppObject(otherLayer_);
        }
        if (!otherLayer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""otherLayer"")");
        self->disableCollisionsWithLayer(otherLayer);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_CreateSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Sprite* sprite = self->createSprite();
        if (!sprite) return JSValueMakeNull(ctx);
        if (!sprite->mSpriteScriptObj)
        {
            return Sprite_newFromCpp(ctx, sprite);
        }
        else
        {
            return sprite->mSpriteScriptObj;
        };
    }

#ifdef PDG_USE_CHIPMUNK_PHYSICS

    JSValueRef TileLayer_SetGravity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""gravity"")");
        double gravity = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setGravity(gravity);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_SetDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""damping"")");
        double damping = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setDamping(damping);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_SetStaticLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""isStatic"")");
        bool isStatic = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setStaticLayer(isStatic);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_SetUseChipmunkPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""useIt"")");
        bool useIt = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setUseChipmunkPhysics(useIt);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_GetSpace(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpSpace* space = self->getSpace();
        if (!space) return JSValueMakeNull(ctx);
        return cpSpace_newFromCpp(ctx, space);;
    }
#endif
    JSValueRef TileLayer_SetWorldSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
        int32 width = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
        int32 height = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsBoolean(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a boolean (""repeatingX"")");
        bool repeatingX = (argumentCount<3) ? false : JSValueToBoolean(ctx, arguments[3 -1]);
        if (argumentCount >= 4 && !JSValueIsBoolean(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a boolean (""repeatingY"")");
        bool repeatingY = (argumentCount<4) ? false : JSValueToBoolean(ctx, arguments[4 -1]);
        self->setWorldSize(width, height, repeatingX, repeatingY);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_GetWorldSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Rect r = self->getWorldSize();
        return JSC_RectToValue(ctx, r, exception);
    }
    JSValueRef TileLayer_GetTileTypeAt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
        int32 x = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
        int32 y = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        uint8 tileType;
        tileType = self->getTileTypeAt(x, y);
        return JSValueMakeNumber(ctx, tileType);
    }
    JSValueRef TileLayer_GetTileTypeAndFacingAt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
        int32 x = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
        int32 y = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        uint8 tileType;
        TileLayer::TFacing facing;
        tileType = self->getTileTypeAt(x, y, &facing);
        if (self->mUseFacing || self->mUseFlipping)
        {
            if (self->mUseFlipping && (!self->mFlipHoriz || !self->mFlipVert))
            {
                tileType &= 0x7f;
            }
            else
            {
                tileType &= 0x3f;
            }
        }
        JSObjectRef tileInfo = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, tileInfo, ((symbol_tileType) ? symbol_tileType : symbol_tileType = JSStringCreateWithUTF8CString("tileType")), JSValueMakeNumber(ctx, tileType), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, tileInfo, ((symbol_facing) ? symbol_facing : symbol_facing = JSStringCreateWithUTF8CString("facing")), JSValueMakeNumber(ctx, facing), kJSPropertyAttributeNone, exception);
        return tileInfo;
    }
    JSValueRef TileLayer_DefineTileSet(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""tileWidth"")");
        int32 tileWidth = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""tileHeight"")");
        int32 tileHeight = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        Image* tiles = 0;
        if (JSValueIsObject(ctx, arguments[3 -1]))
        {
            JSObjectRef tiles_ = JSValueToObject(ctx, arguments[3 -1], exception);
            tiles = Image_getCppObject(tiles_);
        }
        if (!tiles)
            return JSC_ThrowArgTypeException(ctx, exception, 3, "an object of type ""Image"" (""tiles"")");
        if (argumentCount >= 4 && !JSValueIsBoolean(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a boolean (""hasTransparency"")");
        bool hasTransparency = (argumentCount<4) ? true : JSValueToBoolean(ctx, arguments[4 -1]);
        if (argumentCount >= 5 && !JSValueIsBoolean(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a boolean (""flipTiles"")");
        bool flipTiles = (argumentCount<5) ? false : JSValueToBoolean(ctx, arguments[5 -1]);
        self->defineTileSet(tileWidth, tileHeight, tiles, hasTransparency, flipTiles);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_LoadMapData(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""mapWidth"")");
        long mapWidth = (argumentCount<2) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""mapHeight"")");
        long mapHeight = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""dstX"")");
        long dstX = (argumentCount<4) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
        if (argumentCount >= 5 && !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""dstY"")");
        long dstY = (argumentCount<5) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[5 -1], exception));
        if (mapWidth < 0 || mapHeight < 0 || dstX < 0 || dstY < 0)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "negative tile map dimensions" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        if (mapWidth > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "argument 2 (mapWidth) is larger than world width" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        if (mapWidth > self->mWorldWidth - dstX)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "mapWidth + dstX is larger than world width" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        if (mapHeight > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "argument 3 (mapHeight) is larger than world height" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        if (mapHeight > self->mWorldHeight - dstY)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "mapHeight + dstY is larger than world height" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        if (!IsUint8Array(arguments[0]) && !JSValueIsObjectOfClass(ctx, arguments[0], MemBlock_class()))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "argument 1 (data) must be either a Uint8Array or an object of type MemBlock" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        if (IsUint8Array(arguments[0]))
        {
            size_t bytes = 0;
            const uint8* ptr = nullptr;
            if (!GetUint8ArrayData(arguments[0], ptr, bytes))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "expected an attached, non-shared Uint8Array" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (bytes > UINT32_MAX)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "byte array exceeds the supported size" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (bytes < ((size_t)mapWidth * (size_t)mapHeight))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "argument 1 (data) is insufficient, please check mapWidth and mapHeight against data size" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->loadMapData(ptr, mapWidth, mapHeight, dstX, dstY);

        }
        else
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[0], MemBlock_class()))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "expected Uint8Array or MemBlock" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            MemBlock* memBlock = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef memBlock_ = JSValueToObject(ctx, arguments[1 -1], exception);
                memBlock = MemBlock_getCppObject(memBlock_);
            }
            if (!memBlock)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""MemBlock"" (""memBlock"")");
            if (memBlock->bytes < ((size_t)mapWidth * (size_t)mapHeight))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "argument 1 (data) is insufficient, please check mapWidth and mapHeight against data size" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->loadMapData((uint8*)memBlock->ptr, mapWidth, mapHeight, dstX, dstY);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_GetMapData(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""mapWidth"")");
        long mapWidth = (argumentCount<1) ? self->mWorldWidth : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""mapHeight"")");
        long mapHeight = (argumentCount<2) ? self->mWorldHeight : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""srcX"")");
        long srcX = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""srcY"")");
        long srcY = (argumentCount<4) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
        if (mapWidth > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "argument 1 (mapWidth) is larger than world width" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        if ((mapWidth + srcX) > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "mapWidth + srcX is larger than world width" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        if (mapHeight > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "argument 2 (mapHeight) is larger than world height" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        if ((mapHeight + srcY) > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "mapHeight + srcY is larger than world height" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        const uint8* dataPtr = self->getMapData(mapWidth, mapHeight, srcX, srcY);
        size_t bufferSize = mapWidth * mapHeight;
        uint8* ptr = (uint8*) std::malloc(bufferSize);
        std::memcpy(ptr, dataPtr, bufferSize);
        MemBlock* memBlock = new MemBlock((char*)ptr, bufferSize, true);
        if (!memBlock) return JSValueMakeNull(ctx);
        if (!memBlock->mMemBlockScriptObj)
        {
            return MemBlock_newFromCpp(ctx, memBlock);
        }
        else
        {
            return memBlock->mMemBlockScriptObj;
        };
    }
    JSValueRef TileLayer_GetTileSetImage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Image* tiles = self->getTileSetImage();
        if (!tiles) return JSValueMakeNull(ctx);
        if (!tiles->mImageScriptObj)
        {
            return Image_newFromCpp(ctx, tiles);
        }
        else
        {
            return tiles->mImageScriptObj;
        };
    }
    JSValueRef TileLayer_GetTileSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point size = self->getTileSize();
        return JSC_PointToValue(ctx, size, exception);
    }
    JSValueRef TileLayer_SetTileTypeAt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
        int32 x = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
        int32 y = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""t"")");
        uint32 t = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""facing"")");
        unsigned long facing = (argumentCount<4) ? (uint32) TileLayer::facing_Ignore : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[4 -1], exception));
        self->setTileTypeAt(x, y, t, (TileLayer::TFacing) facing);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TileLayer_CheckCollision(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Sprite* movingSprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef movingSprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            movingSprite = Sprite_getCppObject(movingSprite_);
        }
        if (!movingSprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""movingSprite"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""alphaThreshold"")");
        unsigned long alphaThreshold = (argumentCount<2) ? 128 : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsBoolean(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a boolean (""shortCircuit"")");
        bool shortCircuit = (argumentCount<3) ? true : JSValueToBoolean(ctx, arguments[3 -1]);
        uint32 overlapPx = self->checkCollision(movingSprite, alphaThreshold, shortCircuit);
        return JSValueMakeNumber(ctx, overlapPx);
    }
    JSValueRef TileLayer_On(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""eventCode"")");
        int32 eventCode = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        JSObjectRef func = JSValueToObject(ctx, arguments[2 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        long evtCode;
        if (eventCode <= pdg::Sprite::action_CollideWall)
        {
            evtCode = pdg::eventType_SpriteCollide;
        }
        else if (eventCode <= pdg::TileLayer::action_FadeOutComplete)
        {
            evtCode = pdg::eventType_SpriteAnimate;
        }
        else if (eventCode >= pdg::TileLayer::action_ErasePort)
        {
            evtCode = pdg::eventType_SpriteLayer;
        }
        else
        {
            evtCode = pdg::eventType_SpriteTouch;
        }
        self->addHandler(handler, evtCode);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnCollideSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnCollideWall(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnOffscreen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnOnscreen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnExitLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnAnimationLoop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnAnimationEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnFadeComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnFadeInComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnFadeOutComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnMouseEnter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnMouseLeave(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnMouseDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnMouseUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnMouseClick(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnErasePort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_ErasePort);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnPreDrawLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreDrawLayer);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnPostDrawLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostDrawLayer);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnDrawPortComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_DrawPortComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnAnimationStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationStart);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnPreAnimateLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreAnimateLayer);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnPostAnimateLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostAnimateLayer);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnAnimationComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnLayerFadeInComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeInComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef TileLayer_OnLayerFadeOutComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TileLayer* self=static_cast<TileLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeOutComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteLayer);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

#ifdef PDG_USING_JAVASCRIPT_CORE
    void CleanupTileLayerScriptObject(JSObjectRef obj) { if(obj)JSObjectSetPrivate(obj,nullptr); }
#else
    void CleanupTileLayerScriptObject(v8::UniquePersistent<v8::Object>& obj)
    {
        if(!obj.IsEmpty())
        {
            auto* isolate=v8::Isolate::GetCurrent();
            auto value=v8::Local<v8::Object>::New(isolate,obj);
            if(auto* wrapper=dynamic_cast<TileLayerWrap*>(v8script::safe_unwrap_object_wrap_or_prototype(isolate,value)))wrapper->forgetCppObject();
            obj.Reset();
        }
    }
#endif

    TileLayer* New_TileLayer(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        return new TileLayer();
    }

}
