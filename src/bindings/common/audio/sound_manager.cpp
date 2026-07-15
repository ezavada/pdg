// -----------------------------------------------
// sound_manager.cpp
//
// Implementation file for SoundManager bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "../core/core_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
    
%#ifndef PDG_NO_SOUND

// ========================================================================================
//MARK: Sound
// ========================================================================================

WRAPPER_INITIALIZER_IMPL_CUSTOM(Sound, 
    OBJECT_SAVE(cppObj->mEventEmitterScriptObj, obj); 
    OBJECT_SAVE(cppObj->mSoundScriptObj, obj);
    cppObj->addRef() )
      EXPORT_CLASS_SYMBOLS("Sound", Sound, , ,
          // method section
          HAS_EMITTER_METHODS(Sound)
          HAS_PROPERTY(Sound, Volume)
          HAS_METHOD(Sound, "play", Play)
          HAS_METHOD(Sound, "start", Start)
          HAS_METHOD(Sound, "stop", Stop)
          HAS_METHOD(Sound, "pause", Pause)
          HAS_METHOD(Sound, "resume", Resume)
          HAS_METHOD(Sound, "isPaused", IsPaused)
          HAS_METHOD(Sound, "setLooping", SetLooping)
          HAS_METHOD(Sound, "isLooping", IsLooping)
            HAS_METHOD(Sound, "setPitch", SetPitch)
            HAS_METHOD(Sound, "changePitch", ChangePitch)
            HAS_METHOD(Sound, "setOffsetX", SetOffsetX)
            HAS_METHOD(Sound, "changeOffsetX", ChangeOffsetX)
          HAS_METHOD(Sound, "fadeOut", FadeOut)
          HAS_METHOD(Sound, "fadeIn", FadeIn)
          HAS_METHOD(Sound, "changeVolume", ChangeVolume)
          HAS_METHOD(Sound, "skip", Skip)
          HAS_METHOD(Sound, "skipTo", SkipTo)
      );
      END
  EMITTER_BASE_CLASS_IMPL(Sound)
  PROPERTY_IMPL(Sound, Volume, NUMBER)
  METHOD_IMPL(Sound, Play)
      METHOD_SIGNATURE("", undefined, 0, (number vol = 1.0, [number int] offsetX = 0, number pitch = 0, [number uint] fromMs = 0, [number int] lenMs = ENTIRE_LENGTH));
      OPTIONAL_NUMBER_ARG(1, vol, 1.0);
      OPTIONAL_INT32_ARG(2, offsetX, 0); 
      OPTIONAL_NUMBER_ARG(3, pitch, 0.0); 
      OPTIONAL_UINT32_ARG(4, fromMs, 0); 
      OPTIONAL_INT32_ARG(5, lenMs, -1); 
      self->play(vol, offsetX, pitch, fromMs, lenMs);
      NO_RETURN;
      END
  METHOD_IMPL(Sound, Start)
      METHOD_SIGNATURE("", undefined, 0, ());
      REQUIRE_ARG_COUNT(0);
      self->start();
      NO_RETURN;
      END
  METHOD_IMPL(Sound, Stop)
      METHOD_SIGNATURE("", undefined, 0, ());
      REQUIRE_ARG_COUNT(0);
      self->stop();
      NO_RETURN;
      END
  METHOD_IMPL(Sound, Pause)
      METHOD_SIGNATURE("", undefined, 0, ());
      REQUIRE_ARG_COUNT(0);
      self->pause();
      NO_RETURN;
      END
  METHOD_IMPL(Sound, Resume)
      METHOD_SIGNATURE("", undefined, 0, ());
      REQUIRE_ARG_COUNT(0);
      self->resume();
      NO_RETURN;
      END
  METHOD_IMPL(Sound, IsPaused)
      METHOD_SIGNATURE("", boolean, 0, ());
      REQUIRE_ARG_COUNT(0);
      bool result = self->isPaused();
      RETURN_BOOL(result);
      END
  METHOD_IMPL(Sound, SetLooping)
      METHOD_SIGNATURE("", Sound, 1, (boolean loopingOn));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_BOOL_ARG(1, loopingOn);
      self->setLooping(loopingOn);
      RETURN_THIS;
      END
  METHOD_IMPL(Sound, IsLooping)
      METHOD_SIGNATURE("", boolean, 0, ());
      REQUIRE_ARG_COUNT(0);
      bool result = self->isLooping();
      RETURN_BOOL(result);
      END
  METHOD_IMPL(Sound, SetPitch)
      METHOD_SIGNATURE("", Sound, 0, (number pitchOffset));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_NUMBER_ARG(1, pitchOffset);
      self->setPitch(pitchOffset);
      RETURN_THIS;
      END
  METHOD_IMPL(Sound, ChangePitch)
      METHOD_SIGNATURE("", undefined, 0, (number targetOffset, [number int] msDuration, [number int] easing = easeInOutQuad));
      REQUIRE_ARG_MIN_COUNT(2);
      REQUIRE_NUMBER_ARG(1, targetOffset);
      REQUIRE_INT32_ARG(2, msDuration);
      OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad);
      if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
          self->changePitch(targetOffset, msDuration, gEasingFunctions[easing]);
      } else {
          self->changePitch(targetOffset, msDuration);
      }
      NO_RETURN;
      END
  METHOD_IMPL(Sound, SetOffsetX)
      METHOD_SIGNATURE("", Sound, 0, ([number int] offsetX));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_INT32_ARG(1, offsetX);
      self->setOffsetX(offsetX);
      RETURN_THIS;
      END
  METHOD_IMPL(Sound, ChangeOffsetX)
      METHOD_SIGNATURE("", undefined, 0, ([number int] targetOffset, [number int] msDuration, [number int] easing = linearTween));
      REQUIRE_ARG_MIN_COUNT(2);
      REQUIRE_INT32_ARG(1, targetOffset);
      REQUIRE_INT32_ARG(2, msDuration);
      OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::linearTween);
      if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
          self->changePitch(targetOffset, msDuration, gEasingFunctions[easing]);
      } else {
          self->changePitch(targetOffset, msDuration);
      }
      NO_RETURN;
      END
  METHOD_IMPL(Sound, FadeOut)
      METHOD_SIGNATURE("", undefined, 1, ([number uint] fadeMs, [number int] easing = linearTween));
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_UINT32_ARG(1, fadeMs);
      OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween);
      if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
          self->fadeOut(fadeMs, gEasingFunctions[easing]);
      } else {
          self->fadeOut(fadeMs);
      }
      NO_RETURN;
      END
  METHOD_IMPL(Sound, FadeIn)
      METHOD_SIGNATURE("", undefined, 1, ([number uint] fadeMs, [number int] easing = linearTween));
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_UINT32_ARG(1, fadeMs);
      OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween);
      if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
          self->fadeIn(fadeMs, gEasingFunctions[easing]);
      } else {
          self->fadeIn(fadeMs);
      }
      NO_RETURN;
      END
  METHOD_IMPL(Sound, ChangeVolume)
      METHOD_SIGNATURE("", undefined, 2, (number level, [number uint] fadeMs, [number int] easing = linearTween));
      REQUIRE_ARG_MIN_COUNT(2);
      REQUIRE_NUMBER_ARG(1, level);
      REQUIRE_UINT32_ARG(2, fadeMs);
      OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::linearTween);
      if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
          self->changeVolume(level, fadeMs, gEasingFunctions[easing]);
      } else {
          self->changeVolume(level, fadeMs);
      }
      NO_RETURN;
      END
  METHOD_IMPL(Sound, Skip)
      METHOD_SIGNATURE("", Sound, 1, ([number int] skipMilliseconds));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_INT32_ARG(1, skipMilliseconds);
      self->skip(skipMilliseconds);
      RETURN_THIS;
      END
  METHOD_IMPL(Sound, SkipTo)
      METHOD_SIGNATURE("", Sound, 1, ([number uint] timeMs));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_UINT32_ARG(1, timeMs);
      self->skipTo(timeMs);
      RETURN_THIS;
      END
  
  CLEANUP_IMPL(Sound)
  
  CPP_MANAGED_CONSTRUCTOR_IMPL(Sound)
      SETUP_NON_SCRIPT_CALL;
      if (ARGC < 1) {
          return 0;
      } else if (HAVE_ONLY_ONE_NULL_ARG) {
          return Sound::createEmptySoundForIntrospection();
      } else if (!VALUE_IS_STRING(ARGV[0])) {
          SAVE_SYNTAX_ERR("argument 1 must be a string (filename)");
          return 0;
      } else {
          VALUE_TO_CSTRING(filename, ARGV[0]);
          Sound* snd = Sound::createSoundFromFile(filename);
          if (!snd) {
              SAVE_ERR("could not create Sound from file ["<<filename<<"]");
              return 0;
          } else {
              return snd;
          }
      }
      END
  
%#endif //! PDG_NO_SOUND

} // pdg namespace
