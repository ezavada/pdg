// -----------------------------------------------
// sound.cpp
//
// Implementation file for Sound bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"

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
    //MARK: Sound Manager
    // ========================================================================================
    
    SINGLETON_MANAGER_INITIALIZER_IMPL(SoundManager, "snd")
        EXPORT_CLASS_SYMBOLS("SoundManager", SoundManager, , ,
            // method section
            HAS_METHOD(SoundManager, "setVolume", SetVolume)
            HAS_METHOD(SoundManager, "setMute", SetMute)
        );
        END
    METHOD_IMPL(SoundManager, SetVolume)
        METHOD_SIGNATURE("0.0 - silent to 1.0 - full volume", undefined, 1, (number level));
        REQUIRE_ARG_COUNT(1);
        REQUIRE_NUMBER_ARG(1, level);
        self->setVolume(level);
        NO_RETURN;
        END
    METHOD_IMPL(SoundManager, SetMute)
        METHOD_SIGNATURE("", undefined, 1, (boolean muted));
        REQUIRE_ARG_COUNT(1);
        REQUIRE_BOOL_ARG(1, muted);
        self->setMute(muted);
        NO_RETURN;
        END
    
    // FUNCTION_IMPL(GetSoundManager)
    // 	METHOD_SIGNATURE("", [object SoundManager], 0, ()); 
    //     RETURN( SoundManager_getScriptSingletonInstance() );
    //     END
    
    CPP_SINGLETON_CONSTRUCTOR_IMPL(SoundManager)

%#endif //!PDG_NO_SOUND

} // pdg namespace

