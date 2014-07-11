/*
 *  test.h
 *  Parthenon
 *
 *  Created by Ed Zavada on 4/10/10.
 *  Copyright 2010 Dream Rock Studios, LLC. All rights reserved.
 *
 */

//#include <cppunit/Test.h>

#include "pdg/framework.h"

class MyHandler : public pdg::IEventHandler {
    virtual bool handleEvent(pdg::EventEmitter* inEmitter, long inEventType, void* inEventData) throw();	
};

class MyCollisionHandler : public pdg::IEventHandler {
    virtual bool handleEvent(pdg::EventEmitter* inEmitter, long inEventType, void* inEventData) throw();	
};

class BoundsHelper : public pdg::IAnimationHelper {
    virtual bool animate(pdg::Animated* what, uint32 msElapsed);
    virtual bool ownedByAnimated() { return false; } // we will just have one since we don't track state
};

class MyDrawHelper : public pdg::ISpriteDrawHelper {
    virtual bool draw(pdg::Sprite* sprite, pdg::Port* port);
};

class MyCollideHelper : public pdg::ISpriteCollideHelper {
    virtual bool allowCollision(pdg::Sprite* sprite, pdg::Sprite* withSprite);
};

void do_Init();
void do_Idle();
bool do_ErasePort();

