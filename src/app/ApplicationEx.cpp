// -----------------------------------------------
// Application.cpp
// 
// Implementation of an application class
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

#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/sys/platform.h"
#include "pdg/sys/os.h"
#include "pdg/app/ApplicationEx.h"
#include "timerids.h"

namespace pdg {

bool Application::doKeyDown(const KeyInfo* ki) {
    // do something to handle a key state transition from up to down
    // application wide handler for things not associated with a particular
    // view, such as a global magnifying glass or a hold down for help key
    
    // for example, here we handle the user hitting a key to skip
    // past the splash or credits screens
    if (mAppState == state_Splash) {
	    DEBUG_ONLY( OS::_DOUT("Application::doKeyDown (state_Splash), cancel PDG_APP_STARTUP_TIMER [%d]", PDG_APP_STARTUP_TIMER); )
        mTimerMgr->cancelTimer(PDG_APP_STARTUP_TIMER);
        setState(state_Credits);
    } else if (mAppState == state_Credits) {
	    DEBUG_ONLY( OS::_DOUT("Application::doKeyDown (state_Credits), cancel PDG_APP_STARTUP_TIMER [%d]", PDG_APP_STARTUP_TIMER); )
        mTimerMgr->cancelTimer(PDG_APP_STARTUP_TIMER);
        setState(state_Running);
    }

    return false;
}

bool Application::doKeyUp(const KeyInfo* ki) {
    // do something to handle a key state transition from down to up
    // application wide handler for things not associated with a particular
    // view, such as a global magnifying glass or a hold down for help key
    return false;
}
 
bool Application::doKeyPress(const KeyPressInfo* ki) {
    // do something to handle a key press that generates a character (including non-printing)
    // application wide handler for things not associated with a particular
    // view, such as key shortcuts for menus
    return false;
}


void Application::initialize(int argc, const char** argv) {
    // cmd line arguments?

    if (!mSkipSplash) {
        bool doSplash = true;
        for (int i = 1; i<argc; i++) {
            if (std::strcmp(argv[i], "-nosplash") == 0) {
                DEBUG_ONLY( OS::_DOUT("App: skipping slash screen as specified by -nosplash"); )
                doSplash = false;   // don't do splash if they pass -nosplash on the command line
            }
        } 
        if (doSplash) {
            // set the timer that will trigger the splash screen
 			DEBUG_ONLY( OS::_DOUT("Application::initialize, start PDG_APP_STARTUP_TIMER [%d]", PDG_APP_STARTUP_TIMER); )
            mTimerMgr->startTimer(PDG_APP_STARTUP_TIMER, 0); // one shot timer will fire next time through event loop
        } else {
            setState(state_Running);
        }
    } else {
        setState(state_Running);
    }
}

void Application::cleanup() {
    // override to undo anything you did in initialize() call
}


void Application::doSplash() {
	DEBUG_ONLY( OS::_DOUT("Application::doSplash, start PDG_APP_STARTUP_TIMER [%d]", PDG_APP_STARTUP_TIMER); )
    // override to do something to show splash screen at startup
    // in particular, you should not call the base doSplash()
    // but instead set an APP_STARTUP_TIMER for the number of ms you want
    // the splash screen to remain up
    // alternatively, you can do setState(state_whatever) based on a user
    // keypress
    mEventMgr->addHandler(this, eventType_Timer); // will be removed in the handler
    mTimerMgr->startTimer(PDG_APP_STARTUP_TIMER, 0); // one shot timer will fire next time through event loop
}

void Application::doCredits() {
    // override to do something to show credits at startup
	DEBUG_ONLY( OS::_DOUT("Application::doCredits, start APP_STARTUP_TIMER [%d]", PDG_APP_STARTUP_TIMER); )
    mEventMgr->addHandler(this, eventType_Timer);
    mTimerMgr->startTimer(PDG_APP_STARTUP_TIMER, 0); // one shot timer will fire next time through event loop
}

void Application::doAbout() {
    // override to do something when user gets information about the app
}

void Application::setState(int appState) {
	DEBUG_ONLY( OS::_DOUT("Application::setState(%d)", appState); )
    int oldState = mAppState;
    leaveState(oldState, appState); // state transitions within leaveState() will be transitory
    oldState = mAppState;           // and will hide the state we were leaving from the final enterState()
    mAppState = appState; 
    enterState(appState, oldState); // this allows futher state transitions within enterState()
}

void Application::enterState(int newState, int oldState) {
    // override to handle additional state transitions
    // typically this is used to setup the new state
    // calling setState() from within enterState() is allowed, and will
    // produce another complete state leave/enter cycle
    if (newState == state_Credits) {
        doCredits();
    } else if (newState == state_Splash) {
        doSplash();
    } else if (newState == state_About) {
        doAbout();
    }
}

void Application::leaveState(int oldState, int newState) {
    // override to handle additional state transitions
    // typically this is used to cleanup after a state, kill state specific timers, etc...
    // calling setState() within leaveState will produce a transitory state that is
    // exited as soon as it is entered
    // transitory states do NOT get leaveState calls as they are exited
}

bool Application::handleEvent(long inEventType, void* inEventData) throw() {
    if (inEventType == eventType_Startup) {
        StartupInfo* si = static_cast<StartupInfo*>(inEventData);
        // save all the managers
        mNetMgr = si->networkMgr;
        mLogMgr = si->logMgr;
        mTimerMgr = si->timerMgr;
        mSoundMgr = si->soundMgr;
        mGraphicsMgr = si->graphicsMgr;
        mConfigMgr = si->configMgr;
        // now initialize the app
        initialize(si->startupParamCount, si->startupParam);
        return true;
    } else if (inEventType == eventType_Shutdown) {
        mAppState = state_Cleanup;  // we don't do setState here
        cleanup();
        delete this;    // delete ourselves, the framework is halting
        return true;
    } else if (inEventType == eventType_KeyDown) {
        KeyInfo* ki = static_cast<KeyInfo*>(inEventData);
        return doKeyDown(ki);
    } else if (inEventType == eventType_KeyUp) {
        KeyInfo* ki = static_cast<KeyInfo*>(inEventData);
        return doKeyUp(ki);
    } else if (inEventType == eventType_KeyPress) {
        KeyPressInfo* kpi = static_cast<KeyPressInfo*>(inEventData);
        return doKeyPress(kpi);
    } else if (inEventType == eventType_Timer) {
        // timers used for startup sequencing: splash and credits screens
        TimerInfo* ti = static_cast<TimerInfo*>(inEventData);
        if (ti->id == PDG_APP_STARTUP_TIMER) {
  			DEBUG_ONLY( OS::_DOUT("Application::handleEvent, got APP_STARTUP_TIMER [%d]", PDG_APP_STARTUP_TIMER); )
            mEventMgr->removeHandler(this, eventType_Timer); // the doSplash() etc.. methods must
                                                            // add this as a handler again if they
                                                            // want to use a timer
            if (mAppState == state_Initializing) {
                setState(state_Splash);
            } else if (mAppState == state_Splash) {
                setState(state_Credits);
            } else if (mAppState == state_Credits) {
                setState(state_Running);
            }
            return true; // we removed a handler from within handleEvent(), we MUST return true
        }
    }
    return false;
}

Application::Application(EventManager* eventMgr, ResourceManager* resMgr) 
 : mEventMgr(eventMgr), mResourceMgr(resMgr), mTimerMgr(0), mNetMgr(0), mSoundMgr(0), 
   mGraphicsMgr(0), mLogMgr(0), mConfigMgr(0), mAppState(state_Initializing), mSkipSplash(false) {
    mEventMgr->addHandler(this, eventType_Startup);
    mEventMgr->addHandler(this, eventType_Shutdown);
    mEventMgr->addHandler(this, eventType_KeyDown);
    mEventMgr->addHandler(this, eventType_KeyUp);
    mEventMgr->addHandler(this, eventType_KeyPress);
    mEventMgr->addHandler(this, eventType_Timer);
}

Application::~Application() {
    // do an addRef() to ensure that the removal of handlers won't call 
    // delete again on this object. Since we are already deleting, the 
    // addRef() is harmless, the object will be deleted anyway
    addRef();
    mEventMgr->removeHandler(this, eventType_Startup);
    mEventMgr->removeHandler(this, eventType_Shutdown);
    mEventMgr->removeHandler(this, eventType_KeyDown);
    mEventMgr->removeHandler(this, eventType_KeyUp);
    mEventMgr->removeHandler(this, eventType_KeyPress);
    mEventMgr->removeHandler(this, eventType_Timer);
}

} // close namespace pdg
