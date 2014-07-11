// -----------------------------------------------
// Application.cpp
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
#include "pdg/app/Application.h"
#include "timerids.h"

namespace pdg {

bool Application::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {
    if (inEventType == eventType_Startup) {
        StartupInfo* si = static_cast<StartupInfo*>(inEventData);
        // now initialize the app
        initialize(si->startupParamCount, si->startupParam);
        return true;
    } else if (inEventType == eventType_Shutdown) {
        cleanup();
        delete this;    // delete ourselves, the framework is halting
        return true;
    } 
    return false;
}

Application::Application() {
    EventManager::instance().addHandler(this, eventType_Startup);
    EventManager::instance().addHandler(this, eventType_Shutdown);
}

Application::~Application() {
    // do an addRef() to ensure that the removal of handlers won't call 
    // delete again on this object. Since we are already deleting, the 
    // addRef() is harmless, the object will be deleted anyway
    addRef();
    EventManager::instance().removeHandler(this, eventType_Startup);
    EventManager::instance().removeHandler(this, eventType_Shutdown);
}

} // close namespace pdg
