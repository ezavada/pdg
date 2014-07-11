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
#include "pdg/sys/log.h"
#include "pdg/sys/config.h"

#ifndef PDG_NO_SOUND
#include "pdg/sys/sound.h"
#endif
#ifndef PDG_NO_GUI
#include "pdg/sys/graphics.h"
#endif
#ifndef PDG_NO_NETWORK
#include "pdg/sys/network.h"
#endif

#include <exception>


namespace pdg {

class no_manager : public std::exception {
	virtual const char* what() const throw() { return "no_manager"; }
};

class Application : public RefCountedImpl< IEventHandler > {
public:

    virtual void initialize(int argc, const char** argv) = 0;   // cmd line args
    virtual void cleanup() = 0;

    // accessors for the various managers
    LogManager&         getLogManager()      { return LogManager::instance(); }
	ConfigManager&      getConfigManager()   { return ConfigManager::instance(); }
    EventManager&       getEventManager()    { return EventManager::instance(); }
    ResourceManager&    getResourceManager() { return ResourceManager::instance(); }
    TimerManager&       getTimerManager()    { return TimerManager::instance(); }
  #ifndef PDG_NO_NETWORK
    NetworkManager&     getNetworkManager()  { return NetworkManager::instance(); }
  #endif
  #ifndef PDG_NO_SOUND
    SoundManager  &     getSoundManager()    { return SoundManager::instance(); }
  #endif
  #ifndef PDG_NO_GUI
    GraphicsManager&    getGraphicsManager() { return GraphicsManager::instance(); }
  #endif
    
protected:
    
    virtual bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled
    // the managers that we use for this app, we own the globals

    Application();
    virtual ~Application();
};

} // end namespace pdg

#endif // PDG_APPLICATION_H_INCLUDED


