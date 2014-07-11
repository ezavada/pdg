// -----------------------------------------------
// DiceView.h
// 
// header for DiceView class in PDG framework
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_DICEVIEW_H_INCLUDED
#define PDG_DICEVIEW_H_INCLUDED

#include "pdg/app/Dice.h"
#include "pdg/app/View.h"

#define DICE_IMAGE_NUM		3		// Three image files, small and large static die of 6 frames + anim with 15 frames
#define DICE_IDX			0		// The array index of the Image* for the static die image
#define DICE_ANIM_IDX		1		// The array index of the Image* for the animation image
#define DICE_LARGE_IDX		2		// The array index of the Image* for the large static dice
#define DICE_FRAME_NUM		6
#define DICE_ANIM_FRAME_NUM	15
#define DICE_ANIM_FRAME_WIDTH	60		// Current animation file has 40-pixel wide frames
#define DICE_ANIM_FRAME_HEIGHT  80
//#define DICE_FRAME_WIDTH	30
//#define DICE_FRAME_HEIGHT	30
#define DICE_NUM_SIDES      6
#define DICE_PAD			4

#define DICE_SUM_TEXT_SIZE  28
#define DICE_SUM_TEXT_SPACE 35

#ifdef CATAN_SCALABLE
    #define DICE_X				736		// X coordinate of dice draw
    #define DICE_Y				48		// Y coordinate of dice draw
//	#define DICE_ANIM_X			346		// 1/2 screen width - 1/2 dice width
//	#define DICE_ANIM_Y			416		// 1/2 screen height - 1/2 dice height
#else
    #define DICE_X				460		// X coordinate of dice draw
    #define DICE_Y				30		// Y coordinate of dice draw
//	#define DICE_ANIM_X			216		// 1/2 screen width - 1/2 dice width
//	#define DICE_ANIM_Y			260		// 1/2 screen height - 1/2 dice height
#endif

#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
class Game;
#endif

namespace pdg {

class ToolTipCtrl;

class DiceView : public RefCountedImpl<IEventHandler>, public View {
public:
	enum ClickIds
	{
		CLICK_ID_MOUSEMOVE
	};
	// From IEventHandler
    bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled

	// From View
	void loadImages();
	void drawSelf();
	void eraseDiceText();

	bool rolling() { return mRolling; }
	void roll(bool waitForCanStopRolling = false);
	
	void canStopRolling();
	void waitForCanStopRolling() { mWaitForCanStopRolling = true; }
	
	void stopRolling();
	
	void notify(Subject* subject);

	void reset();	// this method re-initializes the DiceView for new games

    DiceView(Controller* controller, const Rect& rect, Game* game, Dice* theDice, View* normalBkgndView, View *animBkgndView = 0);
	~DiceView();
	bool IsMouseOnDiceView(Point mousePts, Rect & rToolRect);// to check if mouse on the diceview area
protected:
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
	Game* mpGame;
#endif
    EventManager& mEventMgr;
    TimerManager& mTimerMgr;
    ResourceManager& mResMgr;
	Dice* mDice;
	bool mRolling;
	int mAnimIdx[MAX_DICE];
	Point mDiceXY[MAX_DICE];
	Point mDiceAnimXY[MAX_DICE];
	Image* mDiceImage[DICE_IMAGE_NUM];
	Rect mAnimRect;
	Rect mClipRect;		// New (11/7/04)
	View* mBackgroundView;
	View* mAnimBackgroundView;  // view while animating
	DiceView();
	bool mCanStopRolling;
	bool mWaitForCanStopRolling;
	bool mRolledLongEnough;
	int mDiceTextSize;
	int mDiceTextSpace; 
};

} // close namespace pdg

#endif // PDG_DICEVIEW_H_INCLUDED


