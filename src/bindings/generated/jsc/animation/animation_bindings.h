// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/animation_bindings.h
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



#ifndef PDG_NO_GUI
#endif

#ifndef PDG_ANIMATION_BINDINGS_H_INCLUDED
#define PDG_ANIMATION_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

namespace pdg
{

    extern IAnimationHelper* New_IAnimationHelper(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef IAnimationHelper_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef IAnimationHelper_class();
    extern JSObjectRef IAnimationHelper_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline IAnimationHelper* IAnimationHelper_getCppObject(JSObjectRef obj)
    {
        return static_cast<IAnimationHelper*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef IAnimationHelper_newFromCpp(JSContextRef, IAnimationHelper*);

    extern AnimatedBase* New_AnimatedBase(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef AnimatedBase_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef AnimatedBase_class();
    extern JSObjectRef AnimatedBase_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline AnimatedBase* AnimatedBase_getCppObject(JSObjectRef obj)
    {
        return static_cast<AnimatedBase*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef AnimatedBase_newFromCpp(JSContextRef, AnimatedBase*);

    extern JSValueRef AnimatedBase_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedBase_Animate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Particle* New_Particle(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Particle_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Particle_class();
    extern JSObjectRef Particle_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Particle* Particle_getCppObject(JSObjectRef obj)
    {
        return static_cast<Particle*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Particle_newFromCpp(JSContextRef, Particle*);

    extern JSValueRef Particle_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ReadPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetupPhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_RemovePhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ReadCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetupCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_RemoveCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetupParticleEmitter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetParticleEmitter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_RemoveParticleEmitter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_ClearContent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_HasContent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_FadeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetLifetime(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetLifetime(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetAge(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_IsAlive(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_Expire(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_GetLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_Animate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef Particle_SetImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Particle_SetDrawing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif

    extern ParticleEmitter* New_ParticleEmitter(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef ParticleEmitter_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef ParticleEmitter_class();
    extern JSObjectRef ParticleEmitter_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline ParticleEmitter* ParticleEmitter_getCppObject(JSObjectRef obj)
    {
        return static_cast<ParticleEmitter*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef ParticleEmitter_newFromCpp(JSContextRef, ParticleEmitter*);

    extern JSValueRef ParticleEmitter_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetParticleTemplate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_HasParticleTemplate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetEmissionRate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetEmissionRate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetParticleSpeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetMinParticleSpeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetMaxParticleSpeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetSpread(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetSpread(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetVelocityInheritance(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetVelocityInheritance(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_SetSeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetSeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_StartEmitting(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_StopEmitting(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_IsEmitting(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_Emit(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_GetParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ParticleEmitter_Animate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Collider* New_Collider(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Collider_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Collider_class();
    extern JSObjectRef Collider_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Collider* Collider_getCppObject(JSObjectRef obj)
    {
        return static_cast<Collider*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Collider_newFromCpp(JSContextRef, Collider*);

    extern JSValueRef Collider_SetFriction(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetRestitution(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetFriction(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetRestitution(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_UseBodyMaterial(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern JSValueRef Collider_SetWantsContactEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetWantsContactEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_IsPresent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_IsAttached(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_IsEnabled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_IsSensor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetId(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetCategory(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetCollisionMask(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetGroup(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetShapeCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetEnabled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetSensor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetCategory(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetCollisionMask(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetGroup(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetPhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetCircle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_AddCircle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetCapsule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_AddCapsule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetCapsuleStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetCapsuleEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetCapsuleRadius(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_AddBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_ClearShapes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_UseOwnerPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetPhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_Contains(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_Overlaps(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_RemoveShape(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetShapeId(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetContactError(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_AddPolygon(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetPolygon(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetImageMask(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_AddImageMask(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetGeometrySource(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_IsSourceShape(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetShapeName(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetShapeType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_GetCircleRadius(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetContactHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Collider_SetCollisionFilter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern PhysicsConstraint* New_PhysicsConstraint(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef PhysicsConstraint_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef PhysicsConstraint_class();
    extern JSObjectRef PhysicsConstraint_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline PhysicsConstraint* PhysicsConstraint_getCppObject(JSObjectRef obj)
    {
        return static_cast<PhysicsConstraint*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef PhysicsConstraint_newFromCpp(JSContextRef, PhysicsConstraint*);

    extern JSValueRef PhysicsConstraint_IsActive(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_IsBroken(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetCollideBodies(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetMaxForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetBreakForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetImpulse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetCollideBodies(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetMaxForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetBreakForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetBodyA(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetBodyB(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetAnchorA(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetAnchorB(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetAnchorA(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetAnchorB(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetAnchors(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetGrooveStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetGrooveEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetGroove(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetMinAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_GetMaxAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_SetAngleLimits(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsConstraint_Disconnect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern PhysicsBody* New_PhysicsBody(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef PhysicsBody_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef PhysicsBody_class();
    extern JSObjectRef PhysicsBody_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline PhysicsBody* PhysicsBody_getCppObject(JSObjectRef obj)
    {
        return static_cast<PhysicsBody*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef PhysicsBody_newFromCpp(JSContextRef, PhysicsBody*);

    extern JSValueRef PhysicsBody_GetConstraintCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreatePinJoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreatePivotJoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateSlideJoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateGrooveJoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateSpring(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateRotarySpring(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateRotaryLimit(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateRatchet(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateGear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_CreateMotor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetConstraint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_Disconnect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetDriveTarget(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_ClearDrive(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_IsDriveEnabled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetDriveState(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetMass(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetMass(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetMomentOfInertia(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetMomentOfInertia(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetLinearDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetLinearDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetAngularDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetAngularDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetFriction(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetFriction(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetRestitution(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetRestitution(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetBreakAngularSpeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetBreakAngularSpeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetBreakAngularSpeedReference(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetAngularVelocity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetAngularVelocity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetSpeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetSpeed(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetSolver(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetAngularMomentum(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetMovementDirectionInRadians(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_IsPresent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_IsAttached(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetState(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_GetVelocity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetVelocity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_SetVelocityInRadians(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_Teleport(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_ApplyImpulse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_ApplyAngularImpulse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_ApplyForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_ApplyTorque(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_AddContinuousForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_AddContinuousTorque(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_RemoveForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_StopAllForces(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_StopMoving(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef PhysicsBody_Step(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Part* New_Part(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Part_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Part_class();
    extern JSObjectRef Part_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Part* Part_getCppObject(JSObjectRef obj)
    {
        return static_cast<Part*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Part_newFromCpp(JSContextRef, Part*);

    extern JSValueRef Part_ReadCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetupCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetupFrameCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetupAnimationCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_RemoveCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ReadPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetupPhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_RemovePhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern JSValueRef Part_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_Animate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetId(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetName(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_IsAttached(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetBoneId(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_IsBoundToBone(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_BindToBone(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_UnbindFromBone(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetParentPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetParentPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SolveIK(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetIKTarget(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ClearIKTarget(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_HasIKTarget(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_IsIKTargetReached(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetIKError(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetIKLimits(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ClearIKLimits(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_HasIKLimits(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetIKMinAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetIKMaxAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetIKDriveTarget(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_IsIKDriven(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_AttachSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetAttachedSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_DetachSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetAttachmentError(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_BindToAnimationBinding(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_BindToAnimationSocket(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetAnimationBindingName(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetAnimationSocketName(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_ClearContent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_HasContent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_GetContentBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef Part_SetDrawing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Part_SetImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif

#ifndef PDG_NO_GUI
    extern ISpriteDrawHelper* New_ISpriteDrawHelper(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef ISpriteDrawHelper_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef ISpriteDrawHelper_class();
    extern JSObjectRef ISpriteDrawHelper_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline ISpriteDrawHelper* ISpriteDrawHelper_getCppObject(JSObjectRef obj)
    {
        return static_cast<ISpriteDrawHelper*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef ISpriteDrawHelper_newFromCpp(JSContextRef, ISpriteDrawHelper*);
#endif

    extern Sprite* New_Sprite(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Sprite_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Sprite_class();
    extern JSObjectRef Sprite_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Sprite* Sprite_getCppObject(JSObjectRef obj)
    {
        return static_cast<Sprite*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Sprite_newFromCpp(JSContextRef, Sprite*);

    extern JSValueRef Sprite_ReadCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetupCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemoveCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ReadPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetupPhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemovePhysicsBody(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern JSValueRef Sprite_GetAttachmentPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetupFrameCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetupAnimationCollider(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetFrameCollisionMask(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_CreatePart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_TransferPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_FindPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetPartCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetPartNames(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemovePart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ClearParts(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetSerializedSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_Serialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_Deserialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetMyClassTag(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetWantsAnimLoopEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetWantsAnimLoopEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetWantsAnimEndEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetWantsAnimEndEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetWantsCollideWallEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetWantsCollideWallEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetFrameRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetFrame(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetCurrentFrame(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetFrameCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StartFrameAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StopFrameAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AddFramesImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifdef PDG_SPRITER_SUPPORT
    extern JSValueRef Sprite_SeekAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_TransitionToAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsAnimationTransitioning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationTransitionProgress(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AddAnimationIK(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationIKTarget(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationIKResult(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AddAnimationModifier(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemoveAnimationModifier(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ClearAnimationModifiers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationModifierError(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationSource(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationSource(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsAnimationDrawingSupported(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationDebugDraw(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationDebugDraw(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SupportsAnimationPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetupAnimationPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetupPhysicsFromAnimationRig(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AttachAnimationPhysicsPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_DetachAnimationPhysicsPart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsAnimationPhysicsPartAttached(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationPhysicsRoot(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationPhysicsRoot(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ClearAnimationPhysicsRoot(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationPhysicsSetupWarnings(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationPhysicsMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationPhysicsMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationPhysicsDriveSettings(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationPhysicsDriveSettings(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_DisableAnimationPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsAnimationPhysicsEnabled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AddAnimationDrawable(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemoveAnimationDrawable(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ClearAnimationDrawables(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationDrawableEnabled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationDrawableError(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationDrawBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_EnableAnimationPose(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_DisableAnimationPose(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsAnimationPoseEnabled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationRigError(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationBoneNames(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationBindingNames(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationBoneTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationBindingTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetAnimationBoneTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ClearAnimationBoneTransforms(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationPose(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SampleAnimationPose(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_HasAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StartAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ApplyCharacterMap(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemoveCharacterMap(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_RemoveAllCharacterMaps(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAppliedCharacterMaps(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_EnableSpriterEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AreSpriterEventsEnabled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_BlendToAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsBlending(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetBlendProgress(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_PauseAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ResumeAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_StopAnimation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsAnimationPlaying(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsAnimationPaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationProgress(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAnimationName(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_HasAttachPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAttachPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_AttachSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_ActivateSubEntity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_DetachSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetAttachedSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetSpriterCollisionBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsSpriterCollisionActive(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetSpriterCollisionBoxCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetSpriterCollisionBoxName(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
#ifndef PDG_NO_GUI
    extern JSValueRef Sprite_GetWantsMouseOverEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetWantsMouseOverEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetWantsClickEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetWantsClickEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetMouseDetectMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetMouseDetectMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetWantsOffscreenEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetWantsOffscreenEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetDrawHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetPostDrawHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef Sprite_ChangeFramesImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OffsetFrameCenters(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetFrameCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_FadeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_FadeIn(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_FadeOut(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_IsBehind(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetZOrder(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_MoveBehind(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_MoveInFrontOf(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_MoveToFront(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_MoveToBack(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_SetUserData(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_FreeUserData(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_GetLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern JSValueRef Sprite_On(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnCollideSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnCollideWall(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnOffscreen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnOnscreen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnExitLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnAnimationLoop(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnAnimationEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnAnimationPhysicsRecoveryComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnAnimationBlendComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnFadeComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnFadeInComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnFadeOutComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnMouseEnter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnMouseLeave(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnMouseDown(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnMouseUp(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sprite_OnMouseClick(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern SpriteLayer* New_SpriteLayer(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef SpriteLayer_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef SpriteLayer_class();
    extern JSObjectRef SpriteLayer_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline SpriteLayer* SpriteLayer_getCppObject(JSObjectRef obj)
    {
        return static_cast<SpriteLayer*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef SpriteLayer_newFromCpp(JSContextRef, SpriteLayer*);

    extern JSValueRef SpriteLayer_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetSerializedSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Serialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Deserialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetMyClassTag(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_CreateParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_AddParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveAllParticles(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetParticleCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetNthParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetMaxParticles(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetMaxParticles(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_CreateParticleEmitter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveParticleEmitter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveAllParticleEmitters(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetSerializationFlags(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_StartAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_StopAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Hide(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Show(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_IsHidden(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_FadeIn(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_FadeOut(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_MoveBehind(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_MoveInFrontOf(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_MoveToFront(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_MoveToBack(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetZOrder(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_MoveWith(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_FindSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetNthSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetSpriteZOrder(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_IsSpriteBehind(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_HasSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_AddSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveAllSprites(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_EnableCollisions(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_DisableCollisions(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_EnableCollisionsWithLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_DisableCollisionsWithLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_CreateSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef SpriteLayer_GetSpritePort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetSpritePort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetOrigin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetOrigin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetZoom(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetZoom(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_Zoom(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ZoomTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetAutoCenter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetFixedMoveAxis(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_LayerToPortPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_LayerToPortOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_LayerToPortVector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_LayerToPortRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_LayerToPortQuad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_PortToLayerPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_PortToLayerOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_PortToLayerVector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_PortToLayerRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_PortToLayerQuad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    extern JSValueRef SpriteLayer_SetUseChipmunkPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetStaticLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetGravity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetKeepGravityDownward(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_SetDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_GetSpace(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
#ifdef PDG_SPRITER_SUPPORT
    extern JSValueRef SpriteLayer_CreateSpriteFromSpriter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_CreateSpriteFromSpriterFile(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_CreateSpriteFromSpriterEntity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_ApplyCharacterMapToAll(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_RemoveCharacterMapFromAll(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_EnableSpriterEvents(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef SpriteLayer_On(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnCollideSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnCollideWall(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnOffscreen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnOnscreen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnExitLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnAnimationLoop(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnAnimationEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnFadeComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnFadeInComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnFadeOutComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnMouseEnter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnMouseLeave(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnMouseDown(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnMouseUp(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnMouseClick(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnErasePort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnPreDrawLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnPostDrawLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnDrawPortComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnAnimationStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnPreAnimateLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnPostAnimateLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnAnimationComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnZoomComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnLayerFadeInComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SpriteLayer_OnLayerFadeOutComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern TileLayer* New_TileLayer(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef TileLayer_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef TileLayer_class();
    extern JSObjectRef TileLayer_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline TileLayer* TileLayer_getCppObject(JSObjectRef obj)
    {
        return static_cast<TileLayer*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef TileLayer_newFromCpp(JSContextRef, TileLayer*);

    extern JSValueRef TileLayer_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetSerializedSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Serialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Deserialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetMyClassTag(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_CreateParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_AddParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveAllParticles(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetParticleCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetNthParticle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetMaxParticles(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetMaxParticles(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_CreateParticleEmitter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveParticleEmitter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveAllParticleEmitters(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetSerializationFlags(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_StartAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_StopAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Hide(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Show(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_IsHidden(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_FadeIn(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_FadeOut(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_MoveBehind(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_MoveInFrontOf(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_MoveToFront(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_MoveToBack(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetZOrder(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_MoveWith(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_FindSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetNthSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetSpriteZOrder(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_IsSpriteBehind(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_HasSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_AddSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_RemoveAllSprites(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_EnableCollisions(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_DisableCollisions(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_EnableCollisionsWithLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_DisableCollisionsWithLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_CreateSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef TileLayer_GetSpritePort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetSpritePort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetOrigin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetOrigin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetZoom(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetZoom(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_Zoom(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_ZoomTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetAutoCenter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetFixedMoveAxis(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_LayerToPortPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_LayerToPortOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_LayerToPortVector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_LayerToPortRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_LayerToPortQuad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_PortToLayerPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_PortToLayerOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_PortToLayerVector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_PortToLayerRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_PortToLayerQuad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    extern JSValueRef TileLayer_SetUseChipmunkPhysics(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetStaticLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetGravity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetKeepGravityDownward(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetSpace(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef TileLayer_GetWorldSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetWorldSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetWorldBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_DefineTileSet(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_LoadMapData(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetMapData(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetTileSetImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetTileSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetTileTypeAt(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_GetTileTypeAndFacingAt(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_SetTileTypeAt(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_CheckCollision(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_On(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnCollideSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnCollideWall(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnOffscreen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnOnscreen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnExitLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnAnimationLoop(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnAnimationEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnFadeComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnFadeInComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnFadeOutComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnMouseEnter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnMouseLeave(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnMouseDown(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnMouseUp(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnMouseClick(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnErasePort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnPreDrawLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnPostDrawLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnDrawPortComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnAnimationStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnPreAnimateLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnPostAnimateLayer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnAnimationComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnZoomComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnLayerFadeInComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TileLayer_OnLayerFadeOutComplete(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif

}
