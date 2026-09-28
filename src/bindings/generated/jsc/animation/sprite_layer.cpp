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
        cppObj->mEventEmitterScriptObj = obj; cppObj->mAnimatedScriptObj = obj; cppObj->mSpriteLayerScriptObj = obj;
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
            { "getBoundingBox", SpriteLayer_GetBoundingBox, kJSPropertyAttributeDontDelete },
            { "getRotatedBounds", SpriteLayer_GetRotatedBounds, kJSPropertyAttributeDontDelete },
            { "getLocation", SpriteLayer_GetLocation, kJSPropertyAttributeDontDelete },
            { "getMovement", SpriteLayer_GetMovement, kJSPropertyAttributeDontDelete },
            { "getSize", SpriteLayer_GetSize, kJSPropertyAttributeDontDelete },
            { "getWidth", SpriteLayer_GetWidth, kJSPropertyAttributeDontDelete },
            { "getHeight", SpriteLayer_GetHeight, kJSPropertyAttributeDontDelete },
            { "getScale", SpriteLayer_GetScale, kJSPropertyAttributeDontDelete },
            { "getStretching", SpriteLayer_GetStretching, kJSPropertyAttributeDontDelete },
            { "getRotation", SpriteLayer_GetRotation, kJSPropertyAttributeDontDelete },
            { "getCenterOffset", SpriteLayer_GetCenterOffset, kJSPropertyAttributeDontDelete },
            { "getSpin", SpriteLayer_GetSpin, kJSPropertyAttributeDontDelete },
            { "setLocation", SpriteLayer_SetLocation, kJSPropertyAttributeDontDelete },
            { "moveTo", SpriteLayer_MoveTo, kJSPropertyAttributeDontDelete },
            { "moveBy", SpriteLayer_MoveBy, kJSPropertyAttributeDontDelete },
            { "setMovement", SpriteLayer_SetMovement, kJSPropertyAttributeDontDelete },
            { "changeMovementTo", SpriteLayer_ChangeMovementTo, kJSPropertyAttributeDontDelete },
            { "changeMovementBy", SpriteLayer_ChangeMovementBy, kJSPropertyAttributeDontDelete },
            { "setSize", SpriteLayer_SetSize, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetTo", SpriteLayer_ChangeCenterOffsetTo, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetBy", SpriteLayer_ChangeCenterOffsetBy, kJSPropertyAttributeDontDelete },
            { "setWidth", SpriteLayer_SetWidth, kJSPropertyAttributeDontDelete },
            { "setHeight", SpriteLayer_SetHeight, kJSPropertyAttributeDontDelete },
            { "setRotation", SpriteLayer_SetRotation, kJSPropertyAttributeDontDelete },
            { "setSpin", SpriteLayer_SetSpin, kJSPropertyAttributeDontDelete },
            { "setGrowing", SpriteLayer_SetGrowing, kJSPropertyAttributeDontDelete },
            { "setStretching", SpriteLayer_SetStretching, kJSPropertyAttributeDontDelete },
            { "setScale", SpriteLayer_SetScale, kJSPropertyAttributeDontDelete },
            { "changeSpinTo", SpriteLayer_ChangeSpinTo, kJSPropertyAttributeDontDelete },
            { "changeSpinBy", SpriteLayer_ChangeSpinBy, kJSPropertyAttributeDontDelete },
            { "changeGrowingTo", SpriteLayer_ChangeGrowingTo, kJSPropertyAttributeDontDelete },
            { "changeGrowingBy", SpriteLayer_ChangeGrowingBy, kJSPropertyAttributeDontDelete },
            { "changeStretchingTo", SpriteLayer_ChangeStretchingTo, kJSPropertyAttributeDontDelete },
            { "changeStretchingBy", SpriteLayer_ChangeStretchingBy, kJSPropertyAttributeDontDelete },
            { "changeScaleTo", SpriteLayer_ChangeScaleTo, kJSPropertyAttributeDontDelete },
            { "changeScaleBy", SpriteLayer_ChangeScaleBy, kJSPropertyAttributeDontDelete },
            { "grow", SpriteLayer_Grow, kJSPropertyAttributeDontDelete },
            { "stretch", SpriteLayer_Stretch, kJSPropertyAttributeDontDelete },
            { "resizeBy", SpriteLayer_ResizeBy, kJSPropertyAttributeDontDelete },
            { "resizeTo", SpriteLayer_ResizeTo, kJSPropertyAttributeDontDelete },
            { "rotateBy", SpriteLayer_RotateBy, kJSPropertyAttributeDontDelete },
            { "rotateTo", SpriteLayer_RotateTo, kJSPropertyAttributeDontDelete },
            { "setCenterOffset", SpriteLayer_SetCenterOffset, kJSPropertyAttributeDontDelete },
            { "setFlipX", SpriteLayer_SetFlipX, kJSPropertyAttributeDontDelete },
            { "setFlipY", SpriteLayer_SetFlipY, kJSPropertyAttributeDontDelete },
            { "stopMovement", SpriteLayer_StopMovement, kJSPropertyAttributeDontDelete },
            { "stopSpinning", SpriteLayer_StopSpinning, kJSPropertyAttributeDontDelete },
            { "stopGrowing", SpriteLayer_StopGrowing, kJSPropertyAttributeDontDelete },
            { "stopStretching", SpriteLayer_StopStretching, kJSPropertyAttributeDontDelete },
            { "pauseSchedule", SpriteLayer_PauseSchedule, kJSPropertyAttributeDontDelete },
            { "resumeSchedule", SpriteLayer_ResumeSchedule, kJSPropertyAttributeDontDelete },
            { "cancelSchedule", SpriteLayer_CancelSchedule, kJSPropertyAttributeDontDelete },
            { "flipX", SpriteLayer_FlipX, kJSPropertyAttributeDontDelete },
            { "flipY", SpriteLayer_FlipY, kJSPropertyAttributeDontDelete },
            { "andThen", SpriteLayer_AndThen, kJSPropertyAttributeDontDelete },
            { "isFlippedX", SpriteLayer_IsFlippedX, kJSPropertyAttributeDontDelete },
            { "isFlippedY", SpriteLayer_IsFlippedY, kJSPropertyAttributeDontDelete },
            { "isSchedulePaused", SpriteLayer_IsSchedulePaused, kJSPropertyAttributeDontDelete },
            { "hasScheduledAnimations", SpriteLayer_HasScheduledAnimations, kJSPropertyAttributeDontDelete },
            { "wait", SpriteLayer_Wait, kJSPropertyAttributeDontDelete },
            { "addAnimationHelper", SpriteLayer_AddAnimationHelper, kJSPropertyAttributeDontDelete },
            { "removeAnimationHelper", SpriteLayer_RemoveAnimationHelper, kJSPropertyAttributeDontDelete },
            { "clearAnimationHelpers", SpriteLayer_ClearAnimationHelpers, kJSPropertyAttributeDontDelete },
            { "get""MyClassTag", SpriteLayer_GetMyClassTag, kJSPropertyAttributeDontDelete },
            { "get""SerializedSize", SpriteLayer_GetSerializedSize, kJSPropertyAttributeDontDelete },
            { "serialize", SpriteLayer_Serialize, kJSPropertyAttributeDontDelete },
            { "deserialize", SpriteLayer_Deserialize, kJSPropertyAttributeDontDelete },
            { "createParticle", SpriteLayer_CreateParticle, kJSPropertyAttributeDontDelete },
            { "addParticle", SpriteLayer_AddParticle, kJSPropertyAttributeDontDelete },
            { "removeParticle", SpriteLayer_RemoveParticle, kJSPropertyAttributeDontDelete },
            { "removeAllParticles", SpriteLayer_RemoveAllParticles, kJSPropertyAttributeDontDelete },
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
            { "moveWith", SpriteLayer_MoveWith, kJSPropertyAttributeDontDelete },
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
            { "setOrigin", SpriteLayer_SetOrigin, kJSPropertyAttributeDontDelete },
            { "getOrigin", SpriteLayer_GetOrigin, kJSPropertyAttributeDontDelete },
            { "setAutoCenter", SpriteLayer_SetAutoCenter, kJSPropertyAttributeDontDelete },
            { "setFixedMoveAxis", SpriteLayer_SetFixedMoveAxis, kJSPropertyAttributeDontDelete },
            { "setZoom", SpriteLayer_SetZoom, kJSPropertyAttributeDontDelete },
            { "getZoom", SpriteLayer_GetZoom, kJSPropertyAttributeDontDelete },
            { "zoomTo", SpriteLayer_ZoomTo, kJSPropertyAttributeDontDelete },
            { "zoom", SpriteLayer_Zoom, kJSPropertyAttributeDontDelete },
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
            { "setKeepGravityDownward", SpriteLayer_SetKeepGravityDownward, kJSPropertyAttributeDontDelete },
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
            { "onZoomComplete", SpriteLayer_OnZoomComplete, kJSPropertyAttributeDontDelete },
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef SpriteLayer_GetBoundingBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Rect theBoundingBox = self->getBoundingBox();
        return JSC_RectToValue(ctx, theBoundingBox, exception);
    }
    JSValueRef SpriteLayer_GetRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::RotatedRect theRotatedBounds = self->getRotatedBounds();
        return JSC_RectToValue(ctx, theRotatedBounds, exception);
    }
    JSValueRef SpriteLayer_GetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Point theLocation = self->getLocation();
        return JSC_PointToValue(ctx, theLocation, exception);
    }
    JSValueRef SpriteLayer_GetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theMovement = self->getMovement();
        return JSC_OffsetToValue(ctx, theMovement, exception);
    }
    JSValueRef SpriteLayer_GetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theSize = self->getSize();
        return JSC_OffsetToValue(ctx, theSize, exception);
    }
    JSValueRef SpriteLayer_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theWidth = self->getWidth();
        return JSValueMakeNumber(ctx, theWidth);
    }
    JSValueRef SpriteLayer_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theHeight = self->getHeight();
        return JSValueMakeNumber(ctx, theHeight);
    }
    JSValueRef SpriteLayer_GetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theScale = self->getScale();
        return JSC_OffsetToValue(ctx, theScale, exception);
    }
    JSValueRef SpriteLayer_GetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theStretching = self->getStretching();
        return JSC_OffsetToValue(ctx, theStretching, exception);
    }
    JSValueRef SpriteLayer_GetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theRotation = self->getRotation();
        return JSValueMakeNumber(ctx, theRotation);
    }
    JSValueRef SpriteLayer_GetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theCenterOffset = self->getCenterOffset();
        return JSC_OffsetToValue(ctx, theCenterOffset, exception);
    }
    JSValueRef SpriteLayer_GetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theSpin = self->getSpin();
        return JSValueMakeNumber(ctx, theSpin);
    }
    JSValueRef SpriteLayer_SetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Point value;
            auto isPoint = JSC_ValueIsPoint(ctx, arguments[0], value, exception);
            if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (*isPoint)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setLocation(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setLocation(x, y); return thisObject;
            }
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
    JSValueRef SpriteLayer_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Point value;
            auto isPoint = JSC_ValueIsPoint(ctx, arguments[0], value, exception);
            if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (*isPoint)
            {
                if (argumentCount == 1) { self->moveTo(value); return thisObject; }
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount == 2) { self->moveTo(x, y); return thisObject; }
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef SpriteLayer_MoveBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount == 1) { self->moveBy(value); return thisObject; }
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount == 2) { self->moveBy(x, y); return thisObject; }
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef SpriteLayer_SetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setMovement(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setMovement(xPerSecond, yPerSecond); return thisObject;
            }
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
    JSValueRef SpriteLayer_ChangeMovementTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementTo(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef SpriteLayer_ChangeMovementBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementBy(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef SpriteLayer_SetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setSize(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
                double width = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
                double height = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setSize(width, height); return thisObject;
            }
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
    JSValueRef SpriteLayer_ChangeCenterOffsetTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef SpriteLayer_ChangeCenterOffsetBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef SpriteLayer_SetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setWidth(value); return thisObject;
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
    JSValueRef SpriteLayer_SetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setHeight(value); return thisObject;
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
    JSValueRef SpriteLayer_SetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setRotation(value); return thisObject;
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
    JSValueRef SpriteLayer_SetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setSpin(value); return thisObject;
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
    JSValueRef SpriteLayer_SetGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setGrowing(value); return thisObject;
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
    JSValueRef SpriteLayer_SetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            self->setStretching(widthPerSecond, heightPerSecond); return thisObject;
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
    JSValueRef SpriteLayer_SetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = (argumentCount<2) ? x : JSValueToNumber(ctx, arguments[2 -1], exception);
            self->setScale(x, y); return thisObject;
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
    JSValueRef SpriteLayer_ChangeSpinTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radiansPerSecond"")");
            double radiansPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeSpinTo(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ChangeSpinBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radiansPerSecond"")");
            double radiansPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeSpinBy(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ChangeGrowingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""amountPerSecond"")");
            double amountPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeGrowingTo(amountPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ChangeGrowingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""amountPerSecond"")");
            double amountPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeGrowingBy(amountPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ChangeStretchingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeStretchingTo(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ChangeStretchingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeStretchingBy(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ChangeScaleTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeScaleTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ChangeScaleBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeScaleBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_Grow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->grow(factor); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->grow(factor, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_Stretch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthFactor"")");
            double widthFactor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightFactor"")");
            double heightFactor = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount == 2) { self->stretch(widthFactor, heightFactor); return thisObject; }
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->stretch(widthFactor, heightFactor, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ResizeBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""deltaWidth"")");
            double deltaWidth = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""deltaHeight"")");
            double deltaHeight = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount == 2) { self->resizeBy(deltaWidth, deltaHeight); return thisObject; }
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->resizeBy(deltaWidth, deltaHeight, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_ResizeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
            double width = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
            double height = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->resizeTo(width, height, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef SpriteLayer_RotateBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->rotateBy(radians); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""directionValue"")");
            double directionValue = (argumentCount<4) ? static_cast<int>(rotationDirection_AsSpecified) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer rotation direction" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateBy(radians, durationSeconds, gEasingFunctions[easing], direction); return thisObject;
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
    JSValueRef SpriteLayer_RotateTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->rotateTo(radians); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""directionValue"")");
            double directionValue = (argumentCount<4) ? static_cast<int>(rotationDirection_AsSpecified) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer rotation direction" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateTo(radians, durationSeconds, gEasingFunctions[easing], direction); return thisObject;
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
    JSValueRef SpriteLayer_SetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->setCenterOffset(offset); return thisObject;
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
    JSValueRef SpriteLayer_SetFlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""flip"")");
            bool flip = JSValueToBoolean(ctx, arguments[1 -1]);
            self->setFlipX(flip); return thisObject;
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
    JSValueRef SpriteLayer_SetFlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""flip"")");
            bool flip = JSValueToBoolean(ctx, arguments[1 -1]);
            self->setFlipY(flip); return thisObject;
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
    JSValueRef SpriteLayer_StopMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopMovement(); return thisObject;
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
    JSValueRef SpriteLayer_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopSpinning(); return thisObject;
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
    JSValueRef SpriteLayer_StopGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopGrowing(); return thisObject;
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
    JSValueRef SpriteLayer_StopStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopStretching(); return thisObject;
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
    JSValueRef SpriteLayer_PauseSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->pauseSchedule(); return thisObject;
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
    JSValueRef SpriteLayer_ResumeSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->resumeSchedule(); return thisObject;
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
    JSValueRef SpriteLayer_CancelSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->cancelSchedule(); return thisObject;
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
    JSValueRef SpriteLayer_FlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->flipX(); return thisObject;
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
    JSValueRef SpriteLayer_FlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->flipY(); return thisObject;
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
    JSValueRef SpriteLayer_AndThen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->andThen(); return thisObject;
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
    JSValueRef SpriteLayer_IsFlippedX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->isFlippedX());
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
    JSValueRef SpriteLayer_IsFlippedY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->isFlippedY());
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
    JSValueRef SpriteLayer_IsSchedulePaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->isSchedulePaused());
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
    JSValueRef SpriteLayer_HasScheduledAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->hasScheduledAnimations());
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
    JSValueRef SpriteLayer_Wait(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->wait(durationSeconds); return thisObject;
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
    JSValueRef SpriteLayer_AddAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            self->mAnimatedScriptObj = thisObject;
            SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "IAnimationHelper" " object:") );
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            IAnimationHelper* helper = 0;
            if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IAnimationHelper_class()))
            {
                JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
                helper = IAnimationHelper_getCppObject(helper_);
            }
            if (!helper)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IAnimationHelper"" (""helper"")");
            self->addAnimationHelper(helper);
            return thisObject;
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
    JSValueRef SpriteLayer_RemoveAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            IAnimationHelper* helper = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
                helper = IAnimationHelper_getCppObject(helper_);
            }
            if (!helper)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""IAnimationHelper"" (""helper"")");
            self->removeAnimationHelper(helper);
            return thisObject;
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
    JSValueRef SpriteLayer_ClearAnimationHelpers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->clearAnimationHelpers();
            return thisObject;
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

    JSValueRef SpriteLayer_GetMyClassTag(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 theMyClassTag = self->getMyClassTag();
        return JSValueMakeNumber(ctx, theMyClassTag);
    }
    JSValueRef SpriteLayer_GetSerializedSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_SetOrigin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Point origin;
        auto origin_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], origin, exception);
        if (!origin_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*origin_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        self->setOrigin(origin);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_GetOrigin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point p = self->getOrigin();
        return JSC_PointToValue(ctx, p, exception);
    }
    JSValueRef SpriteLayer_SetAutoCenter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""autoCenter"")");
        bool autoCenter = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setAutoCenter(autoCenter);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_SetFixedMoveAxis(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""fixedAxis"")");
        bool fixedAxis = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setFixedMoveAxis(fixedAxis);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_SetZoom(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""zoomLevel"")");
        double zoomLevel = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setZoom(zoomLevel);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_GetZoom(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float zoom = self->getZoom();
        return JSValueMakeNumber(ctx, zoom);
    }
    JSValueRef SpriteLayer_ZoomTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""zoomLevel"")");
        double zoomLevel = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
        long easing = (argumentCount<3) ? EasingFuncRef::easeInOutQuad : (int32)floor(JSValueToNumber(ctx, arguments[3 -1], exception));
        pdg::Rect keepInRect;
        if (argumentCount < 4)
        {
            keepInRect = pdg::Rect(0,0);
        }
        else
        {
            auto keepInRect_isRect = JSC_ValueIsRect(ctx, arguments[4 -1], keepInRect, exception);
            if (!keepInRect_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*keepInRect_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 4, "Rect", arguments[4 -1]);
            }
        };
        pdg::Point centerOn;
        if (argumentCount < 5)
        {
            centerOn = pdg::Point(0,0);
        }
        else
        {
            auto centerOn_isPoint = JSC_ValueIsPoint(ctx, arguments[5 -1], centerOn, exception);
            if (!centerOn_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*centerOn_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 5, "Point", arguments[5 -1]);
            }
        };
        pdg::Point* centerOnPtr = (argumentCount >= 5) ? &centerOn : 0;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->zoomTo(zoomLevel, durationSeconds, gEasingFunctions[easing], keepInRect, centerOnPtr);
        }
        else
        {
            self->zoomTo(zoomLevel, durationSeconds);
        }
        return thisObject;
    }
    JSValueRef SpriteLayer_Zoom(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""deltaZoomLevel"")");
        double deltaZoomLevel = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
        long easing = (argumentCount<3) ? EasingFuncRef::easeInOutQuad : (int32)floor(JSValueToNumber(ctx, arguments[3 -1], exception));
        pdg::Rect keepInRect;
        if (argumentCount < 4)
        {
            keepInRect = pdg::Rect(0,0);
        }
        else
        {
            auto keepInRect_isRect = JSC_ValueIsRect(ctx, arguments[4 -1], keepInRect, exception);
            if (!keepInRect_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*keepInRect_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 4, "Rect", arguments[4 -1]);
            }
        };
        pdg::Point centerOn;
        if (argumentCount < 5)
        {
            centerOn = pdg::Point(0,0);
        }
        else
        {
            auto centerOn_isPoint = JSC_ValueIsPoint(ctx, arguments[5 -1], centerOn, exception);
            if (!centerOn_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*centerOn_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 5, "Point", arguments[5 -1]);
            }
        };
        pdg::Point* centerOnPtr = (argumentCount >= 5) ? &centerOn : 0;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->zoom(deltaZoomLevel, durationSeconds, gEasingFunctions[easing], keepInRect, centerOnPtr);
        }
        else
        {
            self->zoom(deltaZoomLevel, durationSeconds);
        }
        return thisObject;
    }
    JSValueRef SpriteLayer_LayerToPortPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortVector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_LayerToPortQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerVector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_PortToLayerQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
#endif

    JSValueRef SpriteLayer_CreateParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef SpriteLayer_GetParticleCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""flags"")");
        uint32 flags = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        self->setSerializationFlags(flags);
        return thisObject;
    }
    JSValueRef SpriteLayer_StartAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->startAnimations();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_StopAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->stopAnimations();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_Hide(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->hide();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_Show(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->show();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_IsHidden(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool hidden = self->isHidden();
        return JSValueMakeBoolean(ctx, hidden);
    }
    JSValueRef SpriteLayer_FadeIn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToFront();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_MoveToBack(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToBack();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_MoveWith(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        SpriteLayer* layer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef layer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            layer = SpriteLayer_getCppObject(layer_);
        }
        if (!layer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""layer"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""moveRatio"")");
        double moveRatio = (argumentCount<2) ? 1.0f : JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""zoomRatio"")");
        double zoomRatio = (argumentCount<3) ? 1.0f : JSValueToNumber(ctx, arguments[3 -1], exception);
        self->moveWith(layer, moveRatio, zoomRatio);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_IsSpriteBehind(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int zorder = self->getZOrder();
        return JSValueMakeNumber(ctx, zorder);
    }
    JSValueRef SpriteLayer_GetSpriteZOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
        int32 index = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->enableCollisions();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_DisableCollisions(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->disableCollisions();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_EnableCollisionsWithLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_SetKeepGravityDownward(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""keepItDownward"")");
        bool keepItDownward = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setKeepGravityDownward(keepItDownward);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_SetGravity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""gravity"")");
        double gravity = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""keepItDownward"")");
        bool keepItDownward = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
        self->setGravity(gravity, keepItDownward);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_SetDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""isStatic"")");
        bool isStatic = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setStaticLayer(isStatic);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_SetUseChipmunkPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""useIt"")");
        bool useIt = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setUseChipmunkPhysics(useIt);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SpriteLayer_GetSpace(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""eventCode"")");
        int32 eventCode = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef SpriteLayer_OnZoomComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_ZoomComplete);
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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
        SpriteLayer* self = static_cast<SpriteLayer*>(JSObjectGetPrivate(thisObject));
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

    void CleanupSpriteLayerScriptObject(JSObjectRef obj) { }

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
