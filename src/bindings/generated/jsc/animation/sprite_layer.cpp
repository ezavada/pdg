// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/sprite_layer.cpp
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

    static bool s_SpriteLayer_InNewFromCpp = false;

    JSObjectRef SpriteLayer_newFromCpp(JSContextRef ctx, SpriteLayer* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, SpriteLayer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, SpriteLayer_class());
        cppObj->mEventEmitterScriptObj = obj; cppObj->mSpriteLayerScriptObj = obj;
        return obj;
    }

    JSObjectRef SpriteLayer_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_SpriteLayer_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "SpriteLayer" " cannot be instantiated with \\'new\\'. Use the factory function: pdg." "createSpriteLayer" "()')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        SpriteLayer* cppObj = New_SpriteLayer(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to create C++ native " "SpriteLayer" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, SpriteLayer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, SpriteLayer_class());
        return obj;
    }

    JSClassRef SpriteLayer_class()
    {

        static JSStaticValue SpriteLayer_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction SpriteLayer_staticFunctions[] =
        {
            { "addHandler", SpriteLayer_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", SpriteLayer_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", SpriteLayer_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", SpriteLayer_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", SpriteLayer_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "get""MyClassTag", SpriteLayer_GetMyClassTag, kJSPropertyAttributeDontDelete },
            { "get""SerializedSize", SpriteLayer_GetSerializedSize, kJSPropertyAttributeDontDelete },
            { "serialize", SpriteLayer_Serialize, kJSPropertyAttributeDontDelete },
            { "deserialize", SpriteLayer_Deserialize, kJSPropertyAttributeDontDelete },
            { "setQueryBits", SpriteLayer_SetQueryBits, kJSPropertyAttributeDontDelete },
            { "getQueryBits", SpriteLayer_GetQueryBits, kJSPropertyAttributeDontDelete },
            { "setCamera", SpriteLayer_SetCamera, kJSPropertyAttributeDontDelete },
            { "getCamera", SpriteLayer_GetCamera, kJSPropertyAttributeDontDelete },
            { "getEffectiveCamera", SpriteLayer_GetEffectiveCamera, kJSPropertyAttributeDontDelete },
            { "setCameraParallax", SpriteLayer_SetCameraParallax, kJSPropertyAttributeDontDelete },
            { "get""WorldBounds", SpriteLayer_GetWorldBounds, kJSPropertyAttributeDontDelete },
            { "set""WorldBounds", SpriteLayer_SetWorldBounds, kJSPropertyAttributeDontDelete },
            { "createParticle", SpriteLayer_CreateParticle, kJSPropertyAttributeDontDelete },
            { "addParticle", SpriteLayer_AddParticle, kJSPropertyAttributeDontDelete },
            { "removeParticle", SpriteLayer_RemoveParticle, kJSPropertyAttributeDontDelete },
            { "removeAllParticles", SpriteLayer_RemoveAllParticles, kJSPropertyAttributeDontDelete },
            { "getParticleTrailCount", SpriteLayer_GetParticleTrailCount, kJSPropertyAttributeDontDelete },
            { "getParticleCount", SpriteLayer_GetParticleCount, kJSPropertyAttributeDontDelete },
            { "getNthParticle", SpriteLayer_GetNthParticle, kJSPropertyAttributeDontDelete },
            { "setMaxParticles", SpriteLayer_SetMaxParticles, kJSPropertyAttributeDontDelete },
            { "getMaxParticles", SpriteLayer_GetMaxParticles, kJSPropertyAttributeDontDelete },
            { "createParticleEmitter", SpriteLayer_CreateParticleEmitter, kJSPropertyAttributeDontDelete },
            { "removeParticleEmitter", SpriteLayer_RemoveParticleEmitter, kJSPropertyAttributeDontDelete },
            { "removeAllParticleEmitters", SpriteLayer_RemoveAllParticleEmitters, kJSPropertyAttributeDontDelete },
            { "setSerializationFlags", SpriteLayer_SetSerializationFlags, kJSPropertyAttributeDontDelete },
            { "startAnimations", SpriteLayer_StartAnimations, kJSPropertyAttributeDontDelete },
            { "stopAnimations", SpriteLayer_StopAnimations, kJSPropertyAttributeDontDelete },
            { "hide", SpriteLayer_Hide, kJSPropertyAttributeDontDelete },
            { "show", SpriteLayer_Show, kJSPropertyAttributeDontDelete },
            { "isHidden", SpriteLayer_IsHidden, kJSPropertyAttributeDontDelete },
            { "fadeIn", SpriteLayer_FadeIn, kJSPropertyAttributeDontDelete },
            { "fadeOut", SpriteLayer_FadeOut, kJSPropertyAttributeDontDelete },
            { "moveBehind", SpriteLayer_MoveBehind, kJSPropertyAttributeDontDelete },
            { "moveInFrontOf", SpriteLayer_MoveInFrontOf, kJSPropertyAttributeDontDelete },
            { "moveToFront", SpriteLayer_MoveToFront, kJSPropertyAttributeDontDelete },
            { "moveToBack", SpriteLayer_MoveToBack, kJSPropertyAttributeDontDelete },
            { "getZOrder", SpriteLayer_GetZOrder, kJSPropertyAttributeDontDelete },
            { "findSprite", SpriteLayer_FindSprite, kJSPropertyAttributeDontDelete },
            { "getNthSprite", SpriteLayer_GetNthSprite, kJSPropertyAttributeDontDelete },
            { "getSpriteZOrder", SpriteLayer_GetSpriteZOrder, kJSPropertyAttributeDontDelete },
            { "isSpriteBehind", SpriteLayer_IsSpriteBehind, kJSPropertyAttributeDontDelete },
            { "hasSprite", SpriteLayer_HasSprite, kJSPropertyAttributeDontDelete },
            { "addSprite", SpriteLayer_AddSprite, kJSPropertyAttributeDontDelete },
            { "removeSprite", SpriteLayer_RemoveSprite, kJSPropertyAttributeDontDelete },
            { "removeAllSprites", SpriteLayer_RemoveAllSprites, kJSPropertyAttributeDontDelete },
            { "enableCollisions", SpriteLayer_EnableCollisions, kJSPropertyAttributeDontDelete },
            { "disableCollisions", SpriteLayer_DisableCollisions, kJSPropertyAttributeDontDelete },
            { "enableCollisionsWithLayer", SpriteLayer_EnableCollisionsWithLayer, kJSPropertyAttributeDontDelete },
            { "disableCollisionsWithLayer", SpriteLayer_DisableCollisionsWithLayer, kJSPropertyAttributeDontDelete },
            { "createSprite", SpriteLayer_CreateSprite, kJSPropertyAttributeDontDelete },
#ifndef PDG_NO_GUI
            { "getSpritePort", SpriteLayer_GetSpritePort, kJSPropertyAttributeDontDelete },
            { "setSpritePort", SpriteLayer_SetSpritePort, kJSPropertyAttributeDontDelete },
            { "layerToPortPoint", SpriteLayer_LayerToPortPoint, kJSPropertyAttributeDontDelete },
            { "layerToPortOffset", SpriteLayer_LayerToPortOffset, kJSPropertyAttributeDontDelete },
            { "layerToPortVector", SpriteLayer_LayerToPortVector, kJSPropertyAttributeDontDelete },
            { "layerToPortRect", SpriteLayer_LayerToPortRect, kJSPropertyAttributeDontDelete },
            { "layerToPortQuad", SpriteLayer_LayerToPortQuad, kJSPropertyAttributeDontDelete },
            { "portToLayerPoint", SpriteLayer_PortToLayerPoint, kJSPropertyAttributeDontDelete },
            { "portToLayerOffset", SpriteLayer_PortToLayerOffset, kJSPropertyAttributeDontDelete },
            { "portToLayerVector", SpriteLayer_PortToLayerVector, kJSPropertyAttributeDontDelete },
            { "portToLayerRect", SpriteLayer_PortToLayerRect, kJSPropertyAttributeDontDelete },
            { "portToLayerQuad", SpriteLayer_PortToLayerQuad, kJSPropertyAttributeDontDelete },
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            { "setGravity", SpriteLayer_SetGravity, kJSPropertyAttributeDontDelete },
            { "setUseChipmunkPhysics", SpriteLayer_SetUseChipmunkPhysics, kJSPropertyAttributeDontDelete },
            { "setStaticLayer", SpriteLayer_SetStaticLayer, kJSPropertyAttributeDontDelete },
            { "setDamping", SpriteLayer_SetDamping, kJSPropertyAttributeDontDelete },
            { "getSpace", SpriteLayer_GetSpace, kJSPropertyAttributeDontDelete },
#endif
#ifdef PDG_SPRITER_SUPPORT
            { "createSpriteFromSpriterFile", SpriteLayer_CreateSpriteFromSpriterFile, kJSPropertyAttributeDontDelete },
            { "createSpriteFromSpriterEntity", SpriteLayer_CreateSpriteFromSpriterEntity, kJSPropertyAttributeDontDelete },
            { "applyCharacterMapToAll", SpriteLayer_ApplyCharacterMapToAll, kJSPropertyAttributeDontDelete },
            { "removeCharacterMapFromAll", SpriteLayer_RemoveCharacterMapFromAll, kJSPropertyAttributeDontDelete },
            { "enableSpriterEvents", SpriteLayer_EnableSpriterEvents, kJSPropertyAttributeDontDelete },
#endif
            { "on", SpriteLayer_On, kJSPropertyAttributeDontDelete },
            { "onCollideSprite", SpriteLayer_OnCollideSprite, kJSPropertyAttributeDontDelete },
            { "onCollideWall", SpriteLayer_OnCollideWall, kJSPropertyAttributeDontDelete },
            { "onOffscreen", SpriteLayer_OnOffscreen, kJSPropertyAttributeDontDelete },
            { "onOnscreen", SpriteLayer_OnOnscreen, kJSPropertyAttributeDontDelete },
            { "onExitLayer", SpriteLayer_OnExitLayer, kJSPropertyAttributeDontDelete },
            { "onAnimationLoop", SpriteLayer_OnAnimationLoop, kJSPropertyAttributeDontDelete },
            { "onAnimationEnd", SpriteLayer_OnAnimationEnd, kJSPropertyAttributeDontDelete },
            { "onFadeComplete", SpriteLayer_OnFadeComplete, kJSPropertyAttributeDontDelete },
            { "onFadeInComplete", SpriteLayer_OnFadeInComplete, kJSPropertyAttributeDontDelete },
            { "onFadeOutComplete", SpriteLayer_OnFadeOutComplete, kJSPropertyAttributeDontDelete },
            { "onMouseEnter", SpriteLayer_OnMouseEnter, kJSPropertyAttributeDontDelete },
            { "onMouseLeave", SpriteLayer_OnMouseLeave, kJSPropertyAttributeDontDelete },
            { "onMouseDown", SpriteLayer_OnMouseDown, kJSPropertyAttributeDontDelete },
            { "onMouseUp", SpriteLayer_OnMouseUp, kJSPropertyAttributeDontDelete },
            { "onMouseClick", SpriteLayer_OnMouseClick, kJSPropertyAttributeDontDelete },
            { "onErasePort", SpriteLayer_OnErasePort, kJSPropertyAttributeDontDelete },
            { "onPreDrawLayer", SpriteLayer_OnPreDrawLayer, kJSPropertyAttributeDontDelete },
            { "onPostDrawLayer", SpriteLayer_OnPostDrawLayer, kJSPropertyAttributeDontDelete },
            { "onDrawPortComplete", SpriteLayer_OnDrawPortComplete, kJSPropertyAttributeDontDelete },
            { "onAnimationStart", SpriteLayer_OnAnimationStart, kJSPropertyAttributeDontDelete },
            { "onPreAnimateLayer", SpriteLayer_OnPreAnimateLayer, kJSPropertyAttributeDontDelete },
            { "onPostAnimateLayer", SpriteLayer_OnPostAnimateLayer, kJSPropertyAttributeDontDelete },
            { "onAnimationComplete", SpriteLayer_OnAnimationComplete, kJSPropertyAttributeDontDelete },
            { "onLayerFadeInComplete", SpriteLayer_OnLayerFadeInComplete, kJSPropertyAttributeDontDelete },
            { "onLayerFadeOutComplete", SpriteLayer_OnLayerFadeOutComplete, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "SpriteLayer";
            definition.staticFunctions = SpriteLayer_staticFunctions;
            definition.staticValues = SpriteLayer_staticValues;
            definition.callAsConstructor = SpriteLayer_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef SpriteLayer_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_GetMyClassTag(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 theMyClassTag = self->getMyClassTag();
        return JSValueMakeNumber(ctx, theMyClassTag);
    }
    JSValueRef SpriteLayer_GetSerializedSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try
        {
            uint32 dataSize = self->getSerializedSize(serializer);
            return JSValueMakeNumber(ctx, dataSize);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef SpriteLayer_Serialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try { self->serialize(serializer); return JSValueMakeUndefined(ctx); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef SpriteLayer_Deserialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        Deserializer* deserializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef deserializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            deserializer = Deserializer_getCppObject(deserializer_);
        }
        if (!deserializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Deserializer"" (""deserializer"")");
        try
        {
            self->deserialize(deserializer);
            return JSValueMakeUndefined(ctx);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(sync_error& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(unknown_object& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

#ifndef PDG_NO_GUI

    JSValueRef SpriteLayer_GetSpritePort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetSpritePort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortVector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerVector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_SetQueryBits(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetQueryBits(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetEffectiveCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetCameraParallax(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetWorldBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetWorldBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_CreateParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_AddParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_RemoveParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_RemoveAllParticles(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetParticleTrailCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetParticleCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetNthParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetMaxParticles(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetMaxParticles(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_CreateParticleEmitter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_RemoveParticleEmitter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_RemoveAllParticleEmitters(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetSerializationFlags(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_StartAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_StopAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_Hide(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_Show(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_IsHidden(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_FadeIn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_FadeOut(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_MoveBehind(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_MoveInFrontOf(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_MoveToFront(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_MoveToBack(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_IsSpriteBehind(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetZOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetSpriteZOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_FindSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetNthSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_HasSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_AddSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_RemoveSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_RemoveAllSprites(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_EnableCollisions(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_DisableCollisions(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_EnableCollisionsWithLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_DisableCollisionsWithLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_CreateSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_SetGravity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetStaticLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetUseChipmunkPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetSpace(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

#ifdef PDG_SPRITER_SUPPORT
    JSValueRef SpriteLayer_CreateSpriteFromSpriterFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inFileName"")");
        JSStringRef inFileName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inFileName_Mem(JSStringGetMaximumUTF8CStringSize(inFileName_Str));
        JSStringGetUTF8CString(inFileName_Str, inFileName_Mem.ptr, inFileName_Mem.bytes);
        const char* inFileName = (const char*)inFileName_Mem.ptr;
        JSStringRelease(inFileName_Str);
        const char* inEntityName = 0;
        if (argumentCount >= 2 && JSValueIsString(ctx, arguments[1]))
        {
            if (!JSValueIsString(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a string (""entityName"")");
            JSStringRef entityName_Str = JSValueToStringCopy(ctx, arguments[2 -1], exception);
            MemBlock entityName_Mem(JSStringGetMaximumUTF8CStringSize(entityName_Str));
            JSStringGetUTF8CString(entityName_Str, entityName_Mem.ptr, entityName_Mem.bytes);
            const char* entityName = (const char*)entityName_Mem.ptr;
            JSStringRelease(entityName_Str);
            inEntityName = entityName;
        }
        Sprite* sprite = self->createSpriteFromSpriterFile(inFileName, inEntityName);
        if (!sprite) return JSValueMakeNull(ctx);
        return Sprite_newFromCpp(ctx, sprite);;
    }
    JSValueRef SpriteLayer_CreateSpriteFromSpriterEntity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inEntityName"")");
        JSStringRef inEntityName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inEntityName_Mem(JSStringGetMaximumUTF8CStringSize(inEntityName_Str));
        JSStringGetUTF8CString(inEntityName_Str, inEntityName_Mem.ptr, inEntityName_Mem.bytes);
        const char* inEntityName = (const char*)inEntityName_Mem.ptr;
        JSStringRelease(inEntityName_Str);
        Sprite* sprite = self->createSpriteFromSpriterEntity(inEntityName);
        if (!sprite) return JSValueMakeNull(ctx);
        return Sprite_newFromCpp(ctx, sprite);;
    }
    JSValueRef SpriteLayer_ApplyCharacterMapToAll(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""mapName"")");
        JSStringRef mapName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock mapName_Mem(JSStringGetMaximumUTF8CStringSize(mapName_Str));
        JSStringGetUTF8CString(mapName_Str, mapName_Mem.ptr, mapName_Mem.bytes);
        const char* mapName = (const char*)mapName_Mem.ptr;
        JSStringRelease(mapName_Str);
        self->applyCharacterMapToAll(mapName);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_RemoveCharacterMapFromAll(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""mapName"")");
        JSStringRef mapName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock mapName_Mem(JSStringGetMaximumUTF8CStringSize(mapName_Str));
        JSStringGetUTF8CString(mapName_Str, mapName_Mem.ptr, mapName_Mem.bytes);
        const char* mapName = (const char*)mapName_Mem.ptr;
        JSStringRelease(mapName_Str);
        self->removeCharacterMapFromAll(mapName);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_EnableSpriterEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Layer is disposed" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }

        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""enable"")");
        bool enable = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->enableSpriterEvents(enable);
        return JSValueMakeUndefined(ctx);
    }
#endif
    JSValueRef SpriteLayer_On(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        else if (eventCode <= pdg::SpriteLayer::action_FadeOutComplete)
        {
            evtCode = pdg::eventType_SpriteAnimate;
        }
        else if (eventCode >= pdg::SpriteLayer::action_ErasePort)
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

    JSValueRef SpriteLayer_OnCollideSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnCollideWall(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnOffscreen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Offscreen);
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

    JSValueRef SpriteLayer_OnOnscreen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Onscreen);
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

    JSValueRef SpriteLayer_OnExitLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_ExitLayer);
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

    JSValueRef SpriteLayer_OnAnimationLoop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationLoop);
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

    JSValueRef SpriteLayer_OnAnimationEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnFadeComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnFadeInComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnFadeOutComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnMouseEnter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnMouseLeave(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnMouseDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnMouseUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnMouseClick(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnErasePort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnPreDrawLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnPostDrawLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnDrawPortComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnAnimationStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnPreAnimateLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnPostAnimateLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnAnimationComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnLayerFadeInComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnLayerFadeOutComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self=static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    void CleanupSpriteLayerScriptObject(JSObjectRef obj) { if(obj)JSObjectSetPrivate(obj,nullptr); }
#else
    void CleanupSpriteLayerScriptObject(v8::UniquePersistent<v8::Object>& obj)
    {
        if(!obj.IsEmpty())
        {
            auto* isolate=v8::Isolate::GetCurrent();
            auto value=v8::Local<v8::Object>::New(isolate,obj);
            if(auto* wrapper=dynamic_cast<SpriteLayerWrap*>(v8script::safe_unwrap_object_wrap_or_prototype(isolate,value)))wrapper->forgetCppObject();
            obj.Reset();
        }
    }
#endif

    SpriteLayer* New_SpriteLayer(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
#ifndef PDG_NO_GUI
        Port* port = GraphicsManager::getSingletonInstance()->getMainPort();
        return createSpriteLayer(port);
#else
        return createSpriteLayer();
#endif
    }

    JSValueRef CreateSpriteLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
#ifndef PDG_NO_GUI
        Port* port = 0;
        if (argumentCount >= 1)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[1 -1], Port_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Port"" (""port"")");
            }
            else
            {
                JSObjectRef port_ = JSValueToObject(ctx, arguments[1 -1], exception);
                port = Port_getCppObject(port_);
            }
        };
        SpriteLayer* layer = createSpriteLayer(port);
#else
        SpriteLayer* layer = createSpriteLayer();
#endif
        if (!layer) return JSValueMakeNull(ctx);
        if (!layer->mSpriteLayerScriptObj)
        {
            return SpriteLayer_newFromCpp(ctx, layer);
        }
        else
        {
            return layer->mSpriteLayerScriptObj;
        };
    }

    JSValueRef CreateSpriteLayerFromSpriterFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""layerSpriterFilename"")");
        JSStringRef layerSpriterFilename_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock layerSpriterFilename_Mem(JSStringGetMaximumUTF8CStringSize(layerSpriterFilename_Str));
        JSStringGetUTF8CString(layerSpriterFilename_Str, layerSpriterFilename_Mem.ptr, layerSpriterFilename_Mem.bytes);
        const char* layerSpriterFilename = (const char*)layerSpriterFilename_Mem.ptr;
        JSStringRelease(layerSpriterFilename_Str);
        if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""addSprites"")");
        bool addSprites = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
#ifndef PDG_NO_GUI
        Port* port = 0;
        if (argumentCount >= 3)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[3 -1], Port_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 3, "an object of type ""Port"" (""port"")");
            }
            else
            {
                JSObjectRef port_ = JSValueToObject(ctx, arguments[3 -1], exception);
                port = Port_getCppObject(port_);
            }
        };
        SpriteLayer* layer = createSpriteLayerFromSpriterFile(layerSpriterFilename, addSprites, port);
#else
        SpriteLayer* layer = createSpriteLayerFromSpriterFile(layerSpriterFilename, addSprites);
#endif
        if (!layer) return JSValueMakeNull(ctx);
        if (!layer->mSpriteLayerScriptObj)
        {
            return SpriteLayer_newFromCpp(ctx, layer);
        }
        else
        {
            return layer->mSpriteLayerScriptObj;
        };
    }

    JSValueRef CleanupLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
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
        cleanupLayer(layer);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef CreateTileLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
#ifndef PDG_NO_GUI
        Port* port = 0;
        if (argumentCount >= 1)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[1 -1], Port_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Port"" (""port"")");
            }
            else
            {
                JSObjectRef port_ = JSValueToObject(ctx, arguments[1 -1], exception);
                port = Port_getCppObject(port_);
            }
        };
        TileLayer* layer = createTileLayer(port);
#else
        TileLayer* layer = createTileLayer();
#endif
        if (!layer) return JSValueMakeNull(ctx);
        if (!layer->mTileLayerScriptObj)
        {
            return TileLayer_newFromCpp(ctx, layer);
        }
        else
        {
            return layer->mTileLayerScriptObj;
        };
    }

}
