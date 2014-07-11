// -----------------------------------------------
// Observer.h
// 
// Declaration of a class that manages observing
// a subject for changes, and being notified when
// that change happens
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_OBSERVER_H_INCLUDED
#define PDG_OBSERVER_H_INCLUDED

#include <vector>

namespace pdg {

class Subject;

class IObserver {
public:
    virtual void notify(Subject* subject=0) = 0;

    virtual ~IObserver() {}
};

class Subject {
public:
    void addObserver(IObserver* observer);
    void removeObserver(IObserver* observer);
    void notifyObservers();
protected:
    typedef std::vector< IObserver* > ObserverList;
    ObserverList mObservers;
};

} // close namespace pdg

#endif // PDG_OBSERVER_H_INCLUDED


