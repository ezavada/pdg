// -----------------------------------------------
// Application.h
// 
// Definition of a class that manages primary
// application functionality
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_APPLICATION_H_INCLUDED
#define PDG_APPLICATION_H_INCLUDED

#include "pdg/sys/core.h"
#include "pdg/sys/refcounted.h"
#include "pdg/sys/events.h"
#include "pdg/sys/resource.h"

#include <exception>


namespace pdg {


class no_manager : public std::exception {
	virtual const char* what() const throw() { return "no_manager"; }
};

class Application : public RefCountedImpl< IEventHandler > {
public:

    enum AppStates {
        state_Initializing = 0,
        state_Cleanup,
        state_Splash,
        state_Credits,
        state_About,
        state_Running,
        
        state_UserStates
    };

    // following return true if handled
    virtual bool doKeyDown(const KeyInfo* ki);
    virtual bool doKeyUp(const KeyInfo* ki); 
    virtual bool doKeyPress(const KeyPressInfo* ki);

    virtual void initialize(int argc, const char** argv);   // cmd line args
    virtual void cleanup();

    virtual void doSplash();
    virtual void doCredits();
    virtual void doAbout();
    
    int          getState() { return mAppState; }
    void         setState(int appState);    // does enterState, leaveState transitions

    // accessors for the various managers
    EventManager&       getEventManager() throw(no_manager)    { if (!mEventMgr) throw no_manager(); return *mEventMgr; }
    ResourceManager&    getResourceManager() throw(no_manager) { if (!mResourceMgr) throw no_manager(); return *mResourceMgr; }
    TimerManager&       getTimerManager() throw(no_manager)    { if (!mTimerMgr) throw no_manager(); return *mTimerMgr; }
    NetworkManager&     getNetworkManager() throw(no_manager)  { if (!mNetMgr) throw no_manager(); return *mNetMgr; }
    SoundManager  &     getSoundManager() throw(no_manager)    { if (!mSoundMgr) throw no_manager(); return *mSoundMgr; }
    GraphicsManager&    getGraphicsManager() throw(no_manager) { if (!mGraphicsMgr) throw no_manager(); return *mGraphicsMgr; }
    LogManager&       getLogManager() throw(no_manager)      { if (!mLogMgr) throw no_manager(); return *mLogMgr; }
	ConfigManager&    getConfigManager() throw(no_manager)   { if (!mConfigMgr) throw no_manager(); return *mConfigMgr; }
    
protected:
    virtual void enterState(int newState, int oldState);
    virtual void leaveState(int oldState, int newState);
    
    virtual bool handleEvent(long inEventType, void* inEventData) throw();  // return true if completely handled
    // the managers that we use for this app, we own the globals
    EventManager*    mEventMgr;
    ResourceManager* mResourceMgr;
    TimerManager*    mTimerMgr;
    NetworkManager*  mNetMgr;
    SoundManager*    mSoundMgr;
	GraphicsManager* mGraphicsMgr;
	LogManager*      mLogMgr;
	ConfigManager*   mConfigMgr;
    int     mAppState;      // application state
    bool    mSkipSplash;    // should we go straight to run state after initializing?

    Application(EventManager* eventMgr, ResourceManager* resMgr);
    virtual ~Application();
};

} // end namespace pdg

#endif // PDG_APPLICATION_H_INCLUDED


