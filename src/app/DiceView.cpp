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

#include "pdg/msvcfix.h"  // fix non-standard MSVC
#include "pdg/framework.h"


#include "timerids.h"
#include "pdg/app/Dice.h"
#include "pdg/app/DiceView.h"
#include "pdg/sys/os.h"

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
  #include "BoardView.h"
  #include "game.h"
#endif

namespace pdg {

const int RES_DICE_ANIM_NAMES = 200;

const float diceAnimX = 0.345f;
const float diceAnimY = 0.500f;

DiceView::DiceView(Controller* controller, const Rect& rect, Game* game, Dice* theDice, View* normalBkgndView, View *animBkgndView)
	:  View(controller, rect), 
		mpGame(game),
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
	mEventMgr.addHandler(this, eventType_Timer);    // we need to start handling timer events
}

DiceView::~DiceView() {
    // we aren't observing this anymore
    mDice->removeObserver(this);
    // do an addRef() to ensure that the removal of handlers won't call 
    // delete again on this object. Since we are already deleting, the 
    // addRef() is harmless, the object will be deleted anyway
    RefCountedImpl<IEventHandler>::addRef();
	mEventMgr.removeHandler(this, eventType_Timer);    // remove ourselves from the handler queue
	
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
	mTimerMgr.cancelTimer(PDG_DICE_ANIM_FRAME_TIMER);
	mTimerMgr.cancelTimer(PDG_DICE_DURATION_TIMER);
}

void
DiceView::loadImages() {
	// Load Dice images
	loadImageArray(mResMgr, mDiceImage, RES_DICE_ANIM_NAMES, DICE_IMAGE_NUM);
	if (mDiceImage[DICE_IDX]) {
		mDiceImage[DICE_IDX]->setNumFrames(DICE_NUM_SIDES);  // six sided dice
	}
	if (mDiceImage[DICE_ANIM_IDX]) {
		mDiceImage[DICE_ANIM_IDX]->setFrameWidth(DICE_ANIM_FRAME_WIDTH);
	}
	if (mDiceImage[DICE_LARGE_IDX]) {
		mDiceImage[DICE_LARGE_IDX]->setFrameWidth(DICE_ANIM_FRAME_WIDTH);
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
	if (mpGame->getState() != Game::STATE_PLAYING) {
		return;
	}
#endif

	if (mDiceImage[DICE_IDX]) {
		// Erase old dice text
		eraseDiceText();
	
/*	    // draw dice drop shadow
	    Point p1;
	    p1.x = mDiceXY[0].x + 2;
	    p1.y = mDiceXY[0].y + mDiceImage[DICE_IDX]->height - 1;
	    Point p2;
	    p2.x = mDiceXY[1].x + mDiceImage[DICE_IDX]->frameWidth;
	    p2.y = p1.y;
	    mPort->drawLineEx(localToGlobal(p1), localToGlobal(p2), 3, Graphics::solidPat, 0, PDG_GRAY_90_COLOR);
        p1.x = p2.x;
        p1.y = mDiceXY[0].y + 2;
        p2.y++;
	    mPort->drawLineEx(localToGlobal(p1), localToGlobal(p2), 2, Graphics::solidPat, 0, PDG_GRAY_90_COLOR);
*/      
        // draw the dice themselves
		mDiceImage[DICE_IDX]->drawFrame(localToGlobal(mDiceXY[0]), mDice->val(0) - 1);
		mDiceImage[DICE_IDX]->drawFrame(localToGlobal(mDiceXY[1]), mDice->val(1) - 1);

		// Draw Dice Sum text
		const Graphics::Style textStyle = (Graphics::Style)(Graphics::textStyle_Bold + Graphics::textStyle_Centered);
		int diceSum = mDice->val(0) + mDice->val(1);
		char text[12];
		//Point diceTextLoc(mDiceXY[1].x, mDiceXY[1].y + mDiceImage[DICE_IDX]->height + mDiceTextSpace);
		Point diceTextLoc(mDiceXY[1].x-3, mDiceXY[1].y + mDiceImage[DICE_IDX]->height + mDiceTextSpace);
		std::snprintf(text, 12, "%2d", diceSum);
        MAKE_STRING_BUFFER_SAFE(text, 12);
/*	    int dropShadowAmount = mPort->getFontHeight(mDiceTextSize, textStyle)/8;
	    diceTextLoc.x += dropShadowAmount;
	    diceTextLoc.y += dropShadowAmount;
    	mPort->drawText(text, localToGlobal(diceTextLoc), mDiceTextSize, textStyle, PDG_GRAY_90_COLOR);
    	diceTextLoc.x -= dropShadowAmount;
    	diceTextLoc.y -= dropShadowAmount;
*/    	mPort->drawText(text, localToGlobal(diceTextLoc), mDiceTextSize, textStyle, PDG_WHITE_COLOR);
	}
}


void
DiceView::roll(bool inWaitForCanStopRolling) {
	if (!mRolling) {
		mTimerMgr.startTimer(PDG_DICE_ANIM_FRAME_TIMER, 40, timer_Repeating);
		mTimerMgr.startTimer(PDG_DICE_DURATION_TIMER, 800, timer_OneShot);
		mWaitForCanStopRolling = inWaitForCanStopRolling;
		mCanStopRolling = false;
		mRolledLongEnough = false;
		// Pick a random starting frame for each die animation
		for (int i=0; i<MAX_DICE; i++) {
			mAnimIdx[i] = OS::rand() % DICE_ANIM_FRAME_NUM;
		}
        Rect clipSave = mPort->getClipRect();
        bool clipped = false;
        if (clipSave == mPort->getDrawingArea()) {
		    mPort->setClipRect(mViewArea);
		    clipped = true;
		}
		mBackgroundView->draw();
//		mPort->fillRect(mViewArea, BACKGROUND_COLOR);
		if (clipped) {
		    mPort->setClipRect(clipSave);
		}
		eraseDiceText();
		mRolling = true;
	}
}

void
DiceView::notify(Subject*) {
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
	mTimerMgr.cancelTimer(PDG_DICE_ANIM_FRAME_TIMER);
	mTimerMgr.startTimer(PDG_DICE_ANIM_RESULT_TIMER, 500, timer_OneShot);
	if (mDiceImage[DICE_LARGE_IDX]) {
        Rect clipSave = mPort->getClipRect();
        bool clipped = false;
        if (clipSave == mPort->getDrawingArea()) {
		    mPort->setClipRect(mClipRect);
		    clipped = true;
		}
		mAnimBackgroundView->draw();
		mDiceImage[DICE_LARGE_IDX]->drawFrame(mDiceAnimXY[0], mDice->val(0) - 1);
		mDiceImage[DICE_LARGE_IDX]->drawFrame(mDiceAnimXY[1], mDice->val(1) - 1);
		if (clipped) {
		    mPort->setClipRect(clipSave);
		}
	}
}

bool
DiceView::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw()
{
    using namespace std;
    bool handled = false;

//  OS::_DOUT( "EventHandler %s\n", mName.c_str() );

    if (inEventType == eventType_Timer)
	{
        TimerInfo* ti = static_cast<TimerInfo*>(inEventData);
//		OS::_DOUT( " got eventType_Timer: id [%d] ms [%d]\n", ti->inID, ti->inMillisec );

		switch( ti->id )
		{
		case PDG_DICE_ANIM_FRAME_TIMER:
			if (mDiceImage[DICE_ANIM_IDX]) {
                Rect clipSave = mPort->getClipRect();
                bool clipped = false;
                if (clipSave == mPort->getDrawingArea()) {
        		    mPort->setClipRect(mClipRect);
        		    clipped = true;
        		}
				mAnimBackgroundView->draw();
				mDiceImage[DICE_ANIM_IDX]->drawFrame(mDiceAnimXY[0], mAnimIdx[0]);
				mDiceImage[DICE_ANIM_IDX]->drawFrame(mDiceAnimXY[1], mAnimIdx[1]);
				if (clipped) {
				    mPort->setClipRect(clipSave);
				}
			}
			mAnimIdx[0] = ++mAnimIdx[0] % DICE_ANIM_FRAME_NUM;
			mAnimIdx[1] = ++mAnimIdx[1] % DICE_ANIM_FRAME_NUM;
			handled = true;
			break;
		case PDG_DICE_DURATION_TIMER:
		    if (!mWaitForCanStopRolling || mCanStopRolling) {
		        stopRolling();
		    } else {
		        mRolledLongEnough = true;   // indicate that we've been rolling long enough to stop anytime we are told we can
		    }
/*			mTimerMgr.cancelTimer(DICE_ANIM_FRAME_TIMER);
			mTimerMgr.startTimer(DICE_ANIM_RESULT_TIMER, 500, timer_OneShot);
			if (mDiceImage[DICE_LARGE_IDX]) {
                Rect clipSave = mPort->getClipRect();
                bool clipped = false;
                if (clipSave == mPort->getDrawingArea()) {
        		    mPort->setClipRect(mAnimRect);
        		    clipped = true;
        		}
				mAnimBackgroundView->draw();
				mDiceImage[DICE_LARGE_IDX]->drawFrame(mDiceAnimXY[0], mDice->val(0) - 1);
				mDiceImage[DICE_LARGE_IDX]->drawFrame(mDiceAnimXY[1], mDice->val(1) - 1);
				if (clipped) {
				    mPort->setClipRect(clipSave);
				}
			} */
			handled = true;
			break;
		case PDG_DICE_ANIM_RESULT_TIMER:
		    {
            Rect clipSave = mPort->getClipRect();
            bool clipped = false;
            if (clipSave == mPort->getDrawingArea()) {
    		    mPort->setClipRect(mClipRect);
    		    clipped = true;
    		}
			mAnimBackgroundView->draw();
			if (clipped) {
			    mPort->setClipRect(clipSave);
			}
			mRolling = false;
			handled = true;
			draw();
			}
			break;
		}
	}
	return handled;
}

void DiceView::eraseDiceText()
{
	// Erase old dice Sum text

	Rect textArea(mDiceXY[0].x, mDiceXY[0].y, 
				  mDiceXY[1].x + mViewArea.width()/2 + 2, mDiceXY[0].y + mViewArea.height() + 2 + mDiceTextSpace);
    Rect clipSave = mPort->getClipRect();
    bool clipped = false;
    if (clipSave == mPort->getDrawingArea()) {
        mPort->setClipRect(localToGlobal(textArea));
	    clipped = true;
	}
    mBackgroundView->draw();
    
//	mPort->fillRect(localToGlobal(textArea), BACKGROUND_COLOR);
//    textArea.shrink(1);
//   	mPort->frameRect(localToGlobal(textArea), PDG_RED_COLOR);

	if (clipped) {
	    mPort->setClipRect(clipSave);
	}
}

// check if the mouse on the diceview
bool DiceView::IsMouseOnDiceView(Point mousePts, Rect & rToolRect)
{
	rToolRect = mViewArea;
	return pointInViewArea(mousePts);
}

} // close namespace pdg

