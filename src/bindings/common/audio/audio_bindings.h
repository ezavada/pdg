// -----------------------------------------------
// audio_bindings.h
//
// Header file that contains audio-related interface declarations
// for pdg classes that are exposed to scripting languages
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

// Include the interface declarations for audio classes

#ifdef PDG_GENERATING_DOCS
#include "../../tools/js_docs_macros.h"
namespace pdg {
#else

#undef THIS // eliminate warning about Windows duplicate Macro
#include "pdg_script_macros.h"
#include "../core/core_macros.h"

%#ifndef PDG_AUDIO_BINDINGS_H_INCLUDED
%#define PDG_AUDIO_BINDINGS_H_INCLUDED

%#include "pdg_project.h"

%#include "pdg_script_impl.h"
%#include "pdg_script.h"

%#ifndef PDG_NO_APP_FRAMEWORK
%#define PDG_NO_APP_FRAMEWORK
%#endif
%#include "pdg/framework.h"

%#include <cstdlib>

namespace pdg {

#endif //!PDG_GENERATING_DOCS

%#ifndef PDG_NO_SOUND
BINDING_CLASS(Sound)
  EMITTER_METHODS(Sound)
  PROPERTY(Sound, Volume)
  METHOD(Sound, Play)
  METHOD(Sound, Start)
  METHOD(Sound, Stop)
  METHOD(Sound, Pause)
  METHOD(Sound, Resume)
  METHOD(Sound, IsPaused)
  METHOD(Sound, SetLooping)
  METHOD(Sound, IsLooping)
  METHOD(Sound, SetPitch)
  METHOD(Sound, ChangePitch)
  METHOD(Sound, SetOffsetX)
  METHOD(Sound, ChangeOffsetX)
  METHOD(Sound, FadeOut)
  METHOD(Sound, FadeIn)
  METHOD(Sound, ChangeVolume)
  METHOD(Sound, Skip)
  METHOD(Sound, SkipTo)
DECL_END

SINGLETON_CLASS(SoundManager)
  METHOD(SoundManager, SetVolume)  // TODO: make property
  METHOD(SoundManager, SetMute)
  METHOD(SoundManager, Idle)
DECL_END
%#endif //! PDG_NO_SOUND


%#endif // PDG_AUDIO_BINDINGS_H_INCLUDED 

} // namespace pdg
