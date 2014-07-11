// -----------------------------------------------
// TouchController.cpp
// 
// Implementation of a base class to manage views
// and handle events
//
// Written by Ed Zavada, 2010-2012
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

#include "pdg/framework.h"

#include "timerids.h"

#include "pdg/app/TouchController.h"

namespace pdg {

	
TouchController::TouchController(Application* app, bool wantKeyUpDown, bool wantKeyPress, 
									 bool wantMouseEnterLeave, bool wantAll) 
 : pdg::ModalController(app,wantKeyUpDown,wantKeyPress,wantMouseEnterLeave,wantAll) {
     mMouseDown = false;
     mLastMousePositionRecorded = false;
     mSnapbackView = 0;
	 mFlickView = 0;
	 getApplication().getEventManager().addHandler(this, pdg::eventType_Timer);   // we want timer events now
}
	
	
void TouchController::removeView(const View* view) {
	
	// Cancel any flick events related to this view.
	if (view == mFlickView) {
		getApplication().getTimerManager().cancelTimer(PDG_FLICK_DECAY_TIMER);
		mFlickView = 0;  // and our flick view is not a valid pointer anymore
	}
	// Cancel any snapback events related to this view
	if (view == mSnapbackView) {
		getApplication().getTimerManager().cancelTimer(PDG_DRAG_SNAPBACK_TIMER);
		mSnapbackView = 0;
	}
	// if there are no more timer events pending for this view then stop listening for timer event
//	if (!mFlickView && !mSnapbackView) {
//		getApplication().getEventManager().removeHandler(this, pdg::eventType_Timer);   // we don't want timer events anymore
//	}
	
	Controller::removeView(view);
}
	
	
bool TouchController::doMouseDown(const pdg::MouseInfo *mi, pdg::View* view, int id, int part) {	
	mMouseDown = true;
	bool handled = doTouch(mi,view,id,part);
	mLastMousePositionRecorded = false;
	mMouseDownInfo = *mi;	
	mFlickView = view;
	mFlickID = id;
	mFlickPart = part;
	mFlickVelocity = PointT<float>(0.0f,0.0f);
	getApplication().getTimerManager().cancelTimer(PDG_FLICK_DECAY_TIMER);
	getApplication().getTimerManager().cancelTimer(PDG_DRAG_SNAPBACK_TIMER);
	return handled;
}

	
bool TouchController::doMouseUp(const pdg::MouseInfo *mi, pdg::View* view, int id, int part) {
	
	bool handled = false;
	
	if ( mLastMousePositionRecorded ) {
		// add momentum to the scroll and check to see if it is out of bounds
		getApplication().getTimerManager().startTimer(PDG_FLICK_DECAY_TIMER, FLICK_FRAME_RATE, pdg::timer_Repeating);
		getApplication().getTimerManager().startTimer(PDG_DRAG_SNAPBACK_TIMER, FLICK_FRAME_RATE, pdg::timer_Repeating);
		mLastSnapbackMs = 0;
		mLastMouseUpMs = pdg::OS::getMilliseconds();
		mSnapbackView = view;
		mSnapbackID = id;
		mSnapbackPart = part;

	//		getApplication().getEventManager().addHandler(this, pdg::eventType_Timer);   // we want timer events now
		
	} else {
		// user didn't move finger, must be a tap
		handled = doTap(mi,view,id,part);
	}
	
	mMouseDown = false;
	mLastMousePositionRecorded = false;
	
	return handled;
}
	
void TouchController::doMouseMove(const pdg::MouseInfo *mi, pdg::View* view, int id, int part) {
	TODO("Implement calls to doPinchMove() and doSwipeMove()");
	uint32 now = pdg::OS::getMilliseconds();
	if( mMouseDown ) {
		if( mLastMousePositionRecorded ) {
			Point delta = mi->mousePos;
			delta -= mLastMousePosition;
			doTouchMove(delta, false, view, id, part);
			uint32 timeSinceLastMouseMoved = now - mLastMovedMs;
			if (timeSinceLastMouseMoved < 1) timeSinceLastMouseMoved = 1;
			mFlickVelocity.x = (float)delta.x / (float)timeSinceLastMouseMoved;  // pixels per millisecond
			mFlickVelocity.y = (float)delta.y / (float)timeSinceLastMouseMoved;  // pixels per millisecond
		}
		mLastMousePosition = mi->mousePos;
		mLastMousePositionRecorded = true;
	} 
	
	mLastMovedMs = now;
}
	
void TouchController::stopFlick() {
	getApplication().getTimerManager().cancelTimer(PDG_FLICK_DECAY_TIMER);
	mFlickView = 0; // we are no longer tracking this view
}

bool TouchController::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {
	if (mActive) {
		if (inEventType == pdg::eventType_Timer) {
			pdg::TimerInfo* ti = static_cast<pdg::TimerInfo*> (inEventData);
			if (ti->id == PDG_FLICK_DECAY_TIMER) {
				uint32 elapsedSinceLastFire = ti->millisec - mLastMovedMs;
				float pixelDeltaX = mFlickVelocity.x * elapsedSinceLastFire;
				float pixelDeltaY = mFlickVelocity.y * elapsedSinceLastFire;
				if ( (std::abs(pixelDeltaX) > 1.0f) || (std::abs(pixelDeltaY) > 1.0f) ) {
					mLastMovedMs = ti->millisec;
					Point pixelDelta(pixelDeltaX, pixelDeltaY);
					doTouchMove(pixelDelta, true, mFlickView, mFlickID, mFlickPart);
					// reduce the flick velocity
					mFlickVelocity.x -= ((FLICK_DECAY_FACTOR * mFlickVelocity.x * (float)elapsedSinceLastFire) / 1000.0f);
					mFlickVelocity.y -= ((FLICK_DECAY_FACTOR * mFlickVelocity.y * (float)elapsedSinceLastFire) / 1000.0f);
				} else if (elapsedSinceLastFire > 100) {
					// we are moving less than one pixel per 10th of a second, so stop doing this
					stopFlick();
				}
				return true;
			} else if (ti->id == PDG_DRAG_SNAPBACK_TIMER) {
				uint32 elapsedSinceMouseUp = ti->millisec - mLastMouseUpMs;
				uint32 elapsedSinceLastSnapback = ti->millisec - mLastSnapbackMs;
				mLastSnapbackMs = ti->millisec;
				if (doSnapback(elapsedSinceLastSnapback, elapsedSinceMouseUp, mSnapbackView, mSnapbackID, mSnapbackPart)) {
					// snapback is completed, end it
					getApplication().getTimerManager().cancelTimer(PDG_DRAG_SNAPBACK_TIMER);
					mSnapbackView = 0;
				}
				return true;
			}
		}
	}
	return Controller::handleEvent(inEmitter, inEventType, inEventData);
}	
	
bool TouchController::doTouchMove( const pdg::Point& delta, bool flick, pdg::View* view, int id, int part) {
	// override to respond to flick telemetry
	return false;
}

bool TouchController::doTouch( const pdg::MouseInfo *mi, pdg::View* view, int id, int part) {
	// override to respond to touch
	return false;
}
	
bool TouchController::doTap( const pdg::MouseInfo *mi, pdg::View* view, int id, int part) {
	// override to recieve taps
	return false;
}

bool TouchController::doSwipeMove( const pdg::Point& delta, pdg::View* view, int id, int part) {
	// override to recieve swipe 
	return false;
}	

bool TouchController::doPinchMove( const pdg::Point& delta1, const pdg::Point& delta2, float distance, float deltaDistance, pdg::View* view, int id, int part) {
	return false;
}

bool TouchController::doSnapback(uint32 msSinceLastSnapback, uint32 msSinceMouseUp, pdg::View* view, int id, int part) {
	// override to do snapback action, returning false while snapback is incomplete
	// return true once snapback has been completed
	return true;
}
	
} // namespace pdg
