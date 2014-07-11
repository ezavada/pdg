// -----------------------------------------------
// dice.cpp
// 
// Implementation of Dice in PDG framework
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

#include <iostream>

#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/framework.h"
#include "pdg/app/Dice.h"

namespace pdg {

void
Dice::roll() {
    if (!mIgnoreNextRoll) {
    	for (int i=0; i<mNumDice; i++) {
    		mDie[i] = OS::gameCriticalRandom() % FACETS + 1;
    	}
    }
    mIgnoreNextRoll = false;
	notifyObservers();  // this will trigger roll animation on a gui game
}


bool
Dice::setNumDice(int n) {
	if ((n > 0) && (n < MAX_DICE)) {
		mNumDice = n;
		roll();
		return true;
	} else {
		return false;
	}
}


void
Dice::setVals(int num, int vals[], bool ignoreNextRoll) {
	for (int i=0; (i<num) && (i<MAX_DICE); i++) {
		mDie[i] = vals[i];
	}
	mIgnoreNextRoll = ignoreNextRoll;
	if (!ignoreNextRoll) {      // when ignoring the next roll, we are essentially priming the dice so that
	    notifyObservers();      // the give us the value we want when they are next rolled. But in all other
	}                           // cases, we want the notify observers because the dice changed so that means
}                               // they were "rolled". when ignoreNextRoll is set it's the roll() call that
                                // actually does the notifyObsevers and thus the roll animation
void
Dice::setNextRollMode(bool IgnoreNextRoll){
	mIgnoreNextRoll = IgnoreNextRoll;
}

} // close namespace pdg
