// -----------------------------------------------
// diceView.cpp
// 
// Implementation for managing animated dice 
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

#include "pdg/app/Dice.h"
#include "pdg/app/DiceView.h"
#include "pdg/app/Controller.h"
#include "pdg/sys/os.h"
#include "pdg/sys/resource.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/attributes.h"
#include "pdg/sys/imagestrip.h"

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
  #include "BoardView.h"
  #include "game.h"
#endif

namespace pdg {

const int RES_DICE_ANIM_NAMES = 200;

const float diceAnimX = 0.345f;
const float diceAnimY = 0.500f;

DiceView::DiceView(Controller* controller, const Rect& rect, 
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
                   ::Game* game, 
#endif
                   Dice* theDice, View* normalBkgndView, View *animBkgndView)
	:  View(controller, rect), 
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
		mpGame(game),
#endif
		mEventMgr(controller->getApplication().getEventManager()), 
	    mTimerMgr(controller->getApplication().getTimerManager()), 
	    mResMgr(controller->getApplication().getResourceManager()), 
 	    mRolling(false), 
        mAnimRect(DICE_ANIM_FRAME_WIDTH * 2, DICE_ANIM_FRAME_HEIGHT),
		mClipRect(DICE_ANIM_FRAME_WIDTH * 2 + 60, DICE_ANIM_FRAME_HEIGHT + 20),
	    mBackgroundView(normalBkgndView), 
	    mAnimBackgroundView(animBkgndView),
	    mCanStopRolling(true),
        mWaitForCanStopRolling(false),
        mRolledLongEnough(false),
        mDiceTextSize(DICE_SUM_TEXT_SIZE),
        mDiceTextSpace(DICE_SUM_TEXT_SPACE)
{
	float f = (float)mPort->getDrawingArea().width() / 1280.0f;
    mDiceTextSize = (int)((float)mDiceTextSize * f);
    mDiceTextSpace = (int)((float)mDiceTextSpace * f);
	
    if (!mAnimBackgroundView) {
        mAnimBackgroundView = mBackgroundView;
    }
	mDice = theDice;
	mDice->addObserver(this);
	mDiceXY[0].x = 0;
	mDiceXY[0].y = 0;
	mDiceXY[1].x = mViewArea.width()/2;
	mDiceXY[1].y = 0;

    mAnimRect.center(Point((long)((float)mPort->getDrawingArea().width() * diceAnimX), (long)((float)mPort->getDrawingArea().height() * diceAnimY)));
    mClipRect.center(Point((long)((float)mPort->getDrawingArea().width() * diceAnimX), (long)((float)mPort->getDrawingArea().height() * diceAnimY)));

	mDiceAnimXY[0].x = mAnimRect.left;
	mDiceAnimXY[0].y = mAnimRect.top;
	mDiceAnimXY[1].x = mAnimRect.left + DICE_ANIM_FRAME_WIDTH;
	mDiceAnimXY[1].y = mAnimRect.top;
	addClickablePart(globalToLocal(mViewArea),CLICK_ID_MOUSEMOVE);	// to display tooltip
	// No timer event handling - using real-time animation instead
}

DiceView::~DiceView() {
    // we aren't observing this anymore
    mDice->removeObserver(this);
    // do an addRef() to ensure that the removal of handlers won't call 
    // delete again on this object. Since we are already deleting, the 
    // addRef() is harmless, the object will be deleted anyway
    RefCountedImpl<IEventHandler>::addRef();
	// No timer event handling to remove - using real-time animation instead
	
	// Release Dice Images
	for (int i=0; i<DICE_IMAGE_NUM; i++) {
		if (mDiceImage[i]) {
			mDiceImage[i]->release();
			mDiceImage[i] = 0;
		}
	}
}

void
DiceView::reset() {
	mRolling = false;
	mCanStopRolling = true;
	mWaitForCanStopRolling = false;
	mRolledLongEnough = false;
	// No timer cancellation needed - using real-time animation instead
}

void
DiceView::loadImages() {
	// Load Dice images
	loadImageArray(mResMgr, mDiceImage, RES_DICE_ANIM_NAMES, DICE_IMAGE_NUM);
	if (mDiceImage[DICE_IDX]) {
		static_cast<ImageStrip*>(mDiceImage[DICE_IDX])->setNumFrames(DICE_NUM_SIDES);  // six sided dice
	}
	if (mDiceImage[DICE_ANIM_IDX]) {
		static_cast<ImageStrip*>(mDiceImage[DICE_ANIM_IDX])->setFrameWidth(DICE_ANIM_FRAME_WIDTH);
	}
	if (mDiceImage[DICE_LARGE_IDX]) {
		static_cast<ImageStrip*>(mDiceImage[DICE_LARGE_IDX])->setFrameWidth(DICE_ANIM_FRAME_WIDTH);
	}
  #ifdef CATAN_SCALABLE
	if (mDiceImage[DICE_IDX]) {
	    float f = (float)mPort->getDrawingArea().width() / 1280.0f;
    	if (mDiceImage[DICE_IDX]) {
            Image* temp = mDiceImage[DICE_IDX]->createImageScaled(f, f);
            mDiceImage[DICE_IDX]->release();
            mDiceImage[DICE_IDX] = temp;
        }
	}
  #endif
}


void
DiceView::drawSelf() {
//    mPort->frameRect(mAnimRect, PDG_CYAN_COLOR);

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
	if (mpGame->getState() != ::Game::STATE_PLAYING) {
		return;
	}
#endif

	if (mRolling) {
		// Real-time animation based on current time
		long currentTime = pdg::OS::getMilliseconds();
		long elapsed = currentTime - mRollStartTime;
		
		// Calculate animation frame based on elapsed time (40ms per frame)
		int frame0 = (elapsed / 40) % DICE_ANIM_FRAME_NUM;
		int frame1 = (frame0 + 1) % DICE_ANIM_FRAME_NUM;
		
		// Draw animation frames
		if (mDiceImage[DICE_ANIM_IDX]) {
			mDiceImage[DICE_ANIM_IDX]->drawFrame(mDiceAnimXY[0], frame0);
			mDiceImage[DICE_ANIM_IDX]->drawFrame(mDiceAnimXY[1], frame1);
		}
		
		// Check if we should stop rolling
		if (elapsed >= 800) {  // 800ms duration
			if (!mWaitForCanStopRolling || mCanStopRolling) {
				stopRolling();
			} else {
				mRolledLongEnough = true;
			}
		}
	} else if (mDiceImage[DICE_IDX]) {
		// Draw final dice values
		mDiceImage[DICE_IDX]->drawFrame(localToGlobal(mDiceXY[0]), mDice->val(0) - 1);
		mDiceImage[DICE_IDX]->drawFrame(localToGlobal(mDiceXY[1]), mDice->val(1) - 1);

		// Draw Dice Sum text
		const Style textStyle = static_cast<Style>(textStyle_Bold + textStyle_Centered);
		int diceSum = mDice->val(0) + mDice->val(1);
		char text[12];
		Point diceTextLoc(mDiceXY[1].x-3, mDiceXY[1].y + mDiceImage[DICE_IDX]->height + mDiceTextSpace);
		std::snprintf(text, 12, "%2d", diceSum);
        MAKE_STRING_BUFFER_SAFE(text, 12);
    	mPort->drawText(text, localToGlobal(diceTextLoc), Attributes().textSize(mDiceTextSize).textStyle(textStyle).fillColor(PDG_WHITE_COLOR));
	}
}


void
DiceView::roll(bool inWaitForCanStopRolling) {
	if (!mRolling) {
		mWaitForCanStopRolling = inWaitForCanStopRolling;
		mCanStopRolling = false;
		mRolledLongEnough = false;
		mRollStartTime = pdg::OS::getMilliseconds();  // Set start time for real-time animation
		mRolling = true;
	}
}

void
DiceView::notify(Subject*) {
    // State-only observer - no immediate drawing
    // Just update the rolling state, drawing will happen on next frame
    roll();
}

void 
DiceView::canStopRolling() {
    mCanStopRolling = true;
    if (mRolledLongEnough) {    // we have been rolling long enough, stop already!
        stopRolling();
    }
}

void
DiceView::stopRolling() {
	// No timer usage - just stop rolling
	// The final result will be shown in the next frame's drawSelf() call
}

bool
DiceView::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw()
{
    // No timer event handling - using real-time animation instead
    return false;
}

void DiceView::eraseDiceText()
{
	// No immediate drawing - text will be redrawn on next frame
}

// check if the mouse on the diceview
bool DiceView::IsMouseOnDiceView(Point mousePts, Rect & rToolRect)
{
	rToolRect = mViewArea;
	return pointInViewArea(mousePts);
}

} // close namespace pdg

