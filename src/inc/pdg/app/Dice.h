// -----------------------------------------------
// Dice.h
// 
// Definitions for Dice object within PDG framework
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_DICE_H_INCLUDED
#define PDG_DICE_H_INCLUDED

#include "pdg/sys/os.h"
#include "pdg/app/Observer.h"

#define MAX_DICE		2		// How many dice
#define FACETS			6		// How many faces on die

namespace pdg {

class Dice : public Subject {
public:
    enum {
        kUseTheseValuesForNextRoll = true
    };
	void roll();
	int	 val(int n) { return (n<mNumDice) ? mDie[n] : 0; }
	bool setNumDice(int n);
	void setVals(int num, int vals[], bool ignoreNextRool = false);
// constructors
	Dice() : mNumDice(MAX_DICE), mIgnoreNextRoll(false) { roll(); }
	Dice(int n) : mNumDice(n), mIgnoreNextRoll(false) { roll(); }
	int getDiceNumber(){return mNumDice;}
	void setDiceNumber(int diceNumber){mNumDice =diceNumber;}
	void setNextRollMode(bool IgnoreNextRoll = false);
protected:
	int mNumDice;
	int mDie[MAX_DICE];
	bool mIgnoreNextRoll;
};

} // close namespace pdg

#endif // PDG_DICE_H_INCLUDED

