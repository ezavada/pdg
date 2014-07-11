// -----------------------------------------------
// Observer.cpp
// 
// Definition of a class that manages observing
// a subject for changes, and being notified when
// that change happens
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

#include "pdg/sys/os.h"
#include "pdg/app/Observer.h"

namespace pdg {

void 
Subject::addObserver(IObserver* observer) {
  #ifdef DEBUG
    // check for double adds
    ObserverList::iterator itr = mObservers.begin();
    while (itr != mObservers.end()) {
        DEBUG_ASSERT(*itr != observer, "Subject::addObserver added same observer twice");
        ++itr;
    }
  #endif
    mObservers.push_back(observer);
}

void 
Subject::removeObserver(IObserver* observer) {
    ObserverList::iterator itr = mObservers.begin();
    while (itr != mObservers.end()) {
        if (*itr == observer) {
            mObservers.erase(itr);
            break;
        }
        ++itr;
    }
}

void 
Subject::notifyObservers() {
    // most recently added is notified first
    ObserverList::reverse_iterator itr = mObservers.rbegin();
    while (itr != mObservers.rend()) {
        (*itr)->notify(this);
        ++itr;
    }
}

} // namespace pdg

