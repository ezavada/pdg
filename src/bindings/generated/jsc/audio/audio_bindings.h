// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/audio/audio_bindings.h
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



#ifndef PDG_AUDIO_BINDINGS_H_INCLUDED
#define PDG_AUDIO_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

namespace pdg
{

#ifndef PDG_NO_SOUND
    extern Sound* New_Sound(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Sound_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Sound_class();
    extern JSObjectRef Sound_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Sound* Sound_getCppObject(JSObjectRef obj)
    {
        return static_cast<Sound*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Sound_newFromCpp(JSContextRef, Sound*);

    extern JSValueRef Sound_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_GetVolume(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_SetVolume(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_Play(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_Start(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_Stop(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_Pause(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_Resume(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_IsPaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_SetLooping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_IsLooping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_SetPitch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_ChangePitch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_SetOffsetX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_ChangeOffsetX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_FadeOut(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_FadeIn(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_ChangeVolume(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_Skip(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Sound_SkipTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern SoundManager* New_SoundManager(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef SoundManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef SoundManager_class();
    extern JSObjectRef SoundManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline SoundManager* SoundManager_getCppObject(JSObjectRef obj)
    {
        return static_cast<SoundManager*>(JSObjectGetPrivate(obj));
    }
    extern SoundManager* SoundManager_getSingletonInstance();
    extern JSObjectRef SoundManager_getScriptSingletonInstance();

    extern JSValueRef SoundManager_SetVolume(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SoundManager_SetMute(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef SoundManager_Idle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
#endif

}
