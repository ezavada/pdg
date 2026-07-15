// -----------------------------------------------
// sound-mgr-macosx.cpp
// 
// Sound Manager functionality
//
// Written by Ed Zavada, 2004-2012
// Copyright (c) 2012, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------


#include "pdg_project.h"

#include "sound-mgr-macosx.h"
#include "sound-macosx.h"
#include "pdg/sys/resource.h"
#include "pdg-lib.h"

namespace pdg {

MemStats gSoundStats;

SoundManagerMac::SoundManagerMac() {
}

SoundManagerMac::~SoundManagerMac() {
    SoundsList::reverse_iterator it = mSounds.rbegin();
    while (it != mSounds.rend()) {
        (*it)->release();
        ++it;
    }
}

// set volume for all sounds. Individual sounds may have separate volumes, but they are 
// treated as a relative volume with this being max
// 1.0 is max, 0.0 is silent
void    
SoundManagerMac::setVolume(float level) {
}

// turn on and off the playing of sounds altogether. setMute(false) restores all sounds 
// to previous levels
void    
SoundManagerMac::setMute(bool muted) {
}

// give time to the sound layer to do anything it may need to do, such as refilling buffers
void    
SoundManagerMac::idle() {
    SoundsList::iterator it = mSounds.begin();
    while (it != mSounds.end()) {
        mSoundsItemDeleted = false;
        SoundMac* sound = static_cast<SoundMac*>(*it);
        if (sound) {
            sound->idle();
        }
        if (mSoundsItemDeleted) { // something in idle caused list item to be deleted
            continue;
        }
        ++it;
    }
    
    // Process deferred audio cleanup to prevent resource leaks
    DeferredAudioCleanup::getInstance().processCleanup();
}

// check if we're in shutdown mode (uses pdg_LibIsQuitting())
bool
SoundManagerMac::isShuttingDown() const {
    return pdg_LibIsQuitting();
}

// stop all currently playing sounds
void
SoundManagerMac::stopAllSounds() {
    // Make a copy of the sounds list to avoid issues when sounds remove themselves
    SoundsList sounds = mSounds;
    SoundsList::iterator it;
    
    // Set all volumes to 0 to prevent pops/clicks
    for (it = sounds.begin(); it != sounds.end(); ++it) {
        if (*it) {
            (*it)->setVolume(0.0f);
        }
    }
    
    // Wait for volume change to propagate through the audio pipeline
    // This prevents buffer repeating and pops when we flush
    PosixAPI::usleep(500 * 1000); // 500ms
    
    // Now stop all sounds (this will flush buffers and stop immediately during shutdown)
    for (it = sounds.begin(); it != sounds.end(); ++it) {
        if (*it) {
            (*it)->stop();
        }
    }
}

// inform the Sound Manager there is a new sound playing
void
SoundManagerMac::soundPlaying(Sound* sound) {
    sound->addRef();
    mSounds.push_back(sound);   // track the sound
}

// inform the Sound Manager there is a new sound playing
void
SoundManagerMac::soundStopped(Sound* sound) {
    SoundsList::iterator it = mSounds.begin();
    while (it != mSounds.end()) {
        if (*it == sound) {
            mSounds.erase(it);
            sound->release();
            mSoundsItemDeleted = true; // in case we were idling when this happened
            break;
        }
        ++it;
    }
}

// create a Sound Manager object
SoundManager* SoundManager::createSingletonInstance() {
	SoundManager* sndMgr = new SoundManagerMac();
	return sndMgr;
}

} // end namespace pdg


