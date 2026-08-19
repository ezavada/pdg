// -----------------------------------------------
// Scrollbar.cpp
// 
// Implementation of a Scrollbar
//
// Written by Alan Davies and Ed Zavada, 2004-2012
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

#include "pdg/app/Scrollbar.h"
#include "ViewUtils.h"
#include "pdg/framework.h"
#include "pdg/sys/attributes.h"
#include "timerids.h"

#include <algorithm>

#ifndef SCROLLBAR_SLIDER_BG_COLOR
#define SCROLLBAR_SLIDER_BG_COLOR Color(76, 100, 126)
#endif

namespace pdg {

const int SCROLLBAR_CLICK_PAUSE_MSTIME = 250;
const int SCROLLBAR_REPEATER_MSTIME = 40;
const int SCROLLBAR_TRACKER_MSTIME = 30;

const Rect goodRangeOffset(-50, -50, 50, 50);       // x,y

// NOTE: This scrollbar class was written close to the Java 1.5 Scrollbar class.
//       To learn about the parameters to this contructor goto:
//       http://java.sun.com/j2se/1.5.0/docs/api/java/awt/Scrollbar.html
Scrollbar::Scrollbar(Controller* controller, const Rect& scrollBarRect, Orientation orientation, int initValue, int visibleAmount, int rangeSize) 
: View(controller, scrollBarRect),
	mEventMgr(controller->getApplication().getEventManager()), 
	mTimerMgr(controller->getApplication().getTimerManager()),   
	mOrientation(orientation),
	mSliderStartTrackHeight(0),
	mMinRange(0),
	mMaxRange(rangeSize - visibleAmount),
	mStepSize(1),
	mPageSize(visibleAmount),
	mCurrentPosition(initValue),
	mScrollUpClicked(false), 
	mScrollDownClicked(false), 
	mScrollUpFullWindowClicked(false), 
	mScrollDownFullWindowClicked(false), 
	mScrollSliderClicked(false)
{
	mAttributes
		.stateAttributes(ControlState::Normal, Attributes().fillColor(SCROLLBAR_SLIDER_BG_COLOR))
		.stateAttributes(ControlState::Decrement, Attributes().fillColor(PDG_GRAY_20_COLOR).lineColor(PDG_GRAY_40_COLOR))
		.stateAttributes(ControlState::DecrementPressed, Attributes().fillColor(PDG_GRAY_40_COLOR).lineColor(PDG_BLACK_COLOR))
		.stateAttributes(ControlState::Increment, Attributes().fillColor(PDG_GRAY_20_COLOR).lineColor(PDG_GRAY_40_COLOR))
		.stateAttributes(ControlState::IncrementPressed, Attributes().fillColor(PDG_GRAY_40_COLOR).lineColor(PDG_BLACK_COLOR))
		.stateAttributes(ControlState::Thumb, Attributes().fillColor(PDG_WHITE_COLOR).lineColor(PDG_BLACK_COLOR).roundedCorners(3));
	mAttributes.merge(controller->getTopController().getControlAttributes(
		ControlType::Scrollbar, static_cast<int>(mOrientation)));
	calcClickableAreas();

	mEventMgr.addHandler(this, eventType_Timer);    // we need to start handling timer events
}

Scrollbar::~Scrollbar()
{
	// do an addRef() to ensure that the removal of handlers won't call 
    // delete again on this object. Since we are already deleting, the 
    // addRef() is harmless, the object will be deleted anyway
    RefCountedImpl<IEventHandler>::addRef();
	mEventMgr.removeHandler(this, eventType_Timer);    // remove ourselves from the handler queue
}

void Scrollbar::setAttributes(const ControlAttributes& attributes)
{
	mAttributes.merge(attributes);
	calcClickableAreas();
}

float Scrollbar::decrementExtent() const
{
	Image* image = mAttributes.state(ControlState::Decrement).image;
	if (image) return mOrientation == HORIZONTAL ? image->width : image->height;
	return mOrientation == HORIZONTAL ? mViewArea.height() : mViewArea.width();
}

float Scrollbar::incrementExtent() const
{
	Image* image = mAttributes.state(ControlState::Increment).image;
	if (image) return mOrientation == HORIZONTAL ? image->width : image->height;
	return mOrientation == HORIZONTAL ? mViewArea.height() : mViewArea.width();
}

Point Scrollbar::thumbDimensions() const
{
	Image* image = mAttributes.state(ControlState::Thumb).image;
	if (image) return Point(image->width, image->height);
	if (mOrientation == HORIZONTAL) {
		return Point(std::min(mViewArea.height(), mSliderArea.width()), mViewArea.height());
	}
	return Point(mViewArea.width(), std::min(mViewArea.width(), mSliderArea.height()));
}

Rect Scrollbar::thumbRect() const
{
	return Rect(mSliderPoint, thumbDimensions().x, thumbDimensions().y);
}

void Scrollbar::calcClickableAreas()
{
	removeClickablePart(CLICK_ID_SCROLL_UP);
	removeClickablePart(CLICK_ID_SCROLL_DOWN);
	removeClickablePart(CLICK_ID_SLIDER_AREA);
	const float dec = decrementExtent();
	const float inc = incrementExtent();
	if (mOrientation == HORIZONTAL) {
		mDownButtonPoint = Point(0, 0);
		mUpButtonPoint = Point(mViewArea.width() - inc, 0);
		addClickablePart(Rect(mDownButtonPoint, dec, mViewArea.height()), CLICK_ID_SCROLL_DOWN);
		addClickablePart(Rect(mUpButtonPoint, inc, mViewArea.height()), CLICK_ID_SCROLL_UP);
		mSliderArea = Rect(dec, 0, mViewArea.width() - inc, mViewArea.height());
	} else {
		mUpButtonPoint = Point(0, 0);
		mDownButtonPoint = Point(0, mViewArea.height() - inc);
		addClickablePart(Rect(mUpButtonPoint, mViewArea.width(), dec), CLICK_ID_SCROLL_UP);
		addClickablePart(Rect(mDownButtonPoint, mViewArea.width(), inc), CLICK_ID_SCROLL_DOWN);
		mSliderArea = Rect(0, dec, mViewArea.width(), mViewArea.height() - inc);
	}
	addClickablePart(mSliderArea, CLICK_ID_SLIDER_AREA);
	updateSliderPointFromValue();
}

void Scrollbar::updateSliderPointFromValue()
{
	const Point thumb = thumbDimensions();
	const float range = std::max(1, mMaxRange - mMinRange);
	const float ratio = std::max(0.0f, std::min(1.0f,
		static_cast<float>(mCurrentPosition - mMinRange) / range));
	if (mOrientation == HORIZONTAL) {
		mSliderPoint = Point(mSliderArea.left + ratio * std::max(0.0f, mSliderArea.width() - thumb.x), mSliderArea.top);
	} else if (mOrientation == VERTICAL) {
		mSliderPoint = Point(mSliderArea.left, mSliderArea.top + ratio * std::max(0.0f, mSliderArea.height() - thumb.y));
	} else {
		mSliderPoint = Point(mSliderArea.left, mSliderArea.bottom - thumb.y - ratio * std::max(0.0f, mSliderArea.height() - thumb.y));
	}
}

void Scrollbar::drawArrow(const Rect& area, bool increment)
{
	const Point center((area.left + area.right) / 2, (area.top + area.bottom) / 2);
	const float radius = std::max(2.0f, std::min(area.width(), area.height()) / 4);
	Attributes line = Attributes().lineColor(PDG_BLACK_COLOR).lineThickness(2);
	if (mOrientation == HORIZONTAL) {
		const float direction = increment ? 1.0f : -1.0f;
		mPort->drawLine(localToGlobal(Point(center.x - direction * radius, center.y - radius)),
			localToGlobal(Point(center.x + direction * radius, center.y)), line);
		mPort->drawLine(localToGlobal(Point(center.x + direction * radius, center.y)),
			localToGlobal(Point(center.x - direction * radius, center.y + radius)), line);
	} else {
		const float direction = increment ? 1.0f : -1.0f;
		mPort->drawLine(localToGlobal(Point(center.x - radius, center.y - direction * radius)),
			localToGlobal(Point(center.x, center.y + direction * radius)), line);
		mPort->drawLine(localToGlobal(Point(center.x, center.y + direction * radius)),
			localToGlobal(Point(center.x + radius, center.y - direction * radius)), line);
	}
}

void Scrollbar::drawSelf()
{
	const float dec = decrementExtent();
	const float inc = incrementExtent();
	Rect decrementRect = mOrientation == HORIZONTAL
		? Rect(mDownButtonPoint, dec, mViewArea.height())
		: Rect(mUpButtonPoint, mViewArea.width(), dec);
	Rect incrementRect = mOrientation == HORIZONTAL
		? Rect(mUpButtonPoint, inc, mViewArea.height())
		: Rect(mDownButtonPoint, mViewArea.width(), inc);
	mAttributes.draw(*mPort, localToGlobal(mSliderArea), ControlState::Normal);
	ControlState decrementState = mScrollDownClicked && mOrientation == HORIZONTAL
		? ControlState::DecrementPressed : (mScrollUpClicked && mOrientation != HORIZONTAL
			? ControlState::DecrementPressed : ControlState::Decrement);
	ControlState incrementState = mScrollUpClicked && mOrientation == HORIZONTAL
		? ControlState::IncrementPressed : (mScrollDownClicked && mOrientation != HORIZONTAL
			? ControlState::IncrementPressed : ControlState::Increment);
	mAttributes.draw(*mPort, localToGlobal(decrementRect), decrementState);
	mAttributes.draw(*mPort, localToGlobal(incrementRect), incrementState);
	if (!mAttributes.state(decrementState).image) drawArrow(decrementRect, false);
	if (!mAttributes.state(incrementState).image) drawArrow(incrementRect, true);
	if (!mScrollSliderClicked) updateSliderPointFromValue();
	mAttributes.draw(*mPort, localToGlobal(thumbRect()), ControlState::Thumb);
	/*char text[20];
	std::snprintf(text, 20, "CurrPos=%d", mCurrentPosition);
    MAKE_STRING_BUFFER_SAFE(text, 20);
	Point textPt = mSliderArea.rightBottom() - Point(150,40);
	Point tl = textPt;
	tl = tl - Point(0, 20);
	Point br = textPt;
	br = br + Point(90, 0);
	Rect hi(tl, br);
	mPort->drawRect(localToGlobal(hi), Attributes().fillColor(PDG_WHITE_COLOR)); 
	mPort->drawText(text, localToGlobal(textPt), Attributes().textSize(12));
	
	this->drawClickableParts();
	Rect viewArea(0,0,mViewArea.width(),mViewArea.height());
	mPort->drawRect(localToGlobal(viewArea), Attributes().lineColor(PDG_RED_COLOR).lineThickness(1));
	*/
}


void Scrollbar::scrollUp()
{
	if (mOrientation == VERTICAL)
	{
    	mCurrentPosition -= mStepSize;
    	if (mCurrentPosition < mMinRange)
    	{
    		mCurrentPosition = mMinRange;
    	}
	}
	else 
	{
    	mCurrentPosition += mStepSize;
    	if (mCurrentPosition > mMaxRange)
    	{
    		mCurrentPosition = mMaxRange;
    	}
	}
	drawSelf();

	// Tell our observers we changed.
	notifyObservers();
}

void Scrollbar::scrollUpPressed()
{
	mScrollUpClicked = true;

	scrollUp();

	mTimerMgr.startTimer(PDG_SCROLLBAR_CLICK_PAUSE, SCROLLBAR_CLICK_PAUSE_MSTIME, timer_OneShot, UserData::makeUserDataFromPointer(this, data_DoNothing) );
}

void Scrollbar::scrollUpReleased()
{
	mScrollUpClicked = false;
	
	drawSelf();

	mTimerMgr.cancelTimer(PDG_SCROLLBAR_CLICK_PAUSE);
	mTimerMgr.cancelTimer(PDG_SCROLLBAR_REPEATER);
}

void Scrollbar::scrollDown()
{
	if (mOrientation == VERTICAL)
	{
    	mCurrentPosition += mStepSize;
    	if (mCurrentPosition > mMaxRange)
    	{
    		mCurrentPosition = mMaxRange;
    	}
	}
	else 
	{
    	mCurrentPosition -= mStepSize;
    	if (mCurrentPosition < mMinRange)
    	{
    		mCurrentPosition = mMinRange;
    	}
	}
	drawSelf();

	// Tell our observers we changed.
	notifyObservers();
}

void Scrollbar::scrollDownPressed()
{
	mScrollDownClicked = true;

	scrollDown();

	mTimerMgr.startTimer(PDG_SCROLLBAR_CLICK_PAUSE, SCROLLBAR_CLICK_PAUSE_MSTIME, timer_OneShot, UserData::makeUserDataFromPointer(this, data_DoNothing) );
}

void Scrollbar::scrollDownReleased()
{
	mScrollDownClicked = false;

	drawSelf();

	mTimerMgr.cancelTimer(PDG_SCROLLBAR_CLICK_PAUSE);
	mTimerMgr.cancelTimer(PDG_SCROLLBAR_REPEATER);
}

void Scrollbar::scrollSliderAreaPressed(Point& clickPoint)
{
	// Change mouse point back to working local coordinates
	clickPoint = globalToLocal(clickPoint);

	Rect thumbArea = thumbRect();

	// Find slider areas
	Rect upperSliderArea = mSliderArea;
	Rect lowerSliderArea = mSliderArea;

	if (mOrientation == HORIZONTAL)
	{
		upperSliderArea.left = thumbArea.right + 1;
		lowerSliderArea.right = thumbArea.left - 1;
	}
	else if (mOrientation == VERTICAL)
	{
		upperSliderArea.bottom = thumbArea.top - 1;
		lowerSliderArea.top = thumbArea.bottom + 1;
	}

	// Check to see if the clicked point is above, on, or below the slider.
	if (upperSliderArea.contains(clickPoint))
	{
		mScrollUpFullWindowClicked = true;
		scrollUpFullWindow();
		mTimerMgr.startTimer(PDG_SCROLLBAR_CLICK_PAUSE, SCROLLBAR_CLICK_PAUSE_MSTIME, timer_OneShot, UserData::makeUserDataFromPointer(this, data_DoNothing) );
	}
	else if (thumbArea.contains(clickPoint))
	{
		mScrollSliderClicked = true;
		mOldMousePoint = mSliderStartTrackPoint = clickPoint;
		if (mOrientation == HORIZONTAL)
		{
			mSliderStartTrackHeight = mSliderStartTrackPoint.x - mSliderPoint.x;
		}
		else if (mOrientation == VERTICAL)
		{
			mSliderStartTrackHeight = mSliderStartTrackPoint.y - mSliderPoint.y;
		}
		mTimerMgr.startTimer(PDG_SCROLLBAR_TRACKER, SCROLLBAR_TRACKER_MSTIME, timer_Repeating, UserData::makeUserDataFromPointer(this, data_DoNothing) );
	}
	else if (lowerSliderArea.contains(clickPoint))
	{
		mScrollDownFullWindowClicked = true;
		scrollDownFullWindow();
		mTimerMgr.startTimer(PDG_SCROLLBAR_CLICK_PAUSE, SCROLLBAR_CLICK_PAUSE_MSTIME, timer_OneShot, UserData::makeUserDataFromPointer(this, data_DoNothing) );
	}
}

void Scrollbar::scrollSliderAreaReleased()
{
	mScrollDownFullWindowClicked = false;
	mScrollUpFullWindowClicked = false;
	mScrollSliderClicked = false;

	mTimerMgr.cancelTimer(PDG_SCROLLBAR_CLICK_PAUSE);
	mTimerMgr.cancelTimer(PDG_SCROLLBAR_REPEATER);
	mTimerMgr.cancelTimer(PDG_SCROLLBAR_TRACKER);
}

void Scrollbar::scrollUpFullWindow()
{
	if (mOrientation == VERTICAL)
	{
    	mCurrentPosition -= mPageSize;
    	if (mCurrentPosition < mMinRange)
    	{
    		mCurrentPosition = mMinRange;
    	}
	}
	else 
	{
    	mCurrentPosition += mPageSize;
    	if (mCurrentPosition > mMaxRange)
    	{
    		mCurrentPosition = mMaxRange;
    	}
	}
	drawSelf();
	// Tell our observers we changed.
	notifyObservers();
}

void Scrollbar::scrollDownFullWindow()
{
	if (mOrientation == VERTICAL)
	{
    	mCurrentPosition += mPageSize;
    	if (mCurrentPosition > mMaxRange)
    	{
    		mCurrentPosition = mMaxRange;
    	}
	}
	else 
	{
    	mCurrentPosition -= mPageSize;
    	if (mCurrentPosition < mMinRange)
    	{
    		mCurrentPosition = mMinRange;
    	}
	}
	drawSelf();
	// Tell our observers we changed.
	notifyObservers();
}

void Scrollbar::trackScrollSlider()
{
	Point newMousePoint = globalToLocal(OS::getMouse());
	
	if ( newMousePoint != mOldMousePoint )
	{
		const Point thumb = thumbDimensions();
		// The mouse moved, check to see if the mouse is in a good range otherwise
		// go back to our point where the user started.
		Rect goodRangeRect = this->mSliderArea;
		goodRangeRect = goodRangeRect + goodRangeOffset;
		if (!goodRangeRect.contains(newMousePoint))
		{
			newMousePoint = mSliderStartTrackPoint;
		}
		else
		{
			if (mOrientation == HORIZONTAL)
			{
				const float absLeft = mSliderArea.left + mSliderStartTrackHeight;
				const float absRight = mSliderArea.right - (thumb.x - mSliderStartTrackHeight);
				newMousePoint.x = std::max(absLeft, std::min(absRight, newMousePoint.x));
				mSliderPoint.x = newMousePoint.x - mSliderStartTrackHeight;
			}
			else
			{
				const float absTop = mSliderArea.top + mSliderStartTrackHeight;
				const float absBottom = mSliderArea.bottom - (thumb.y - mSliderStartTrackHeight);
				newMousePoint.y = std::max(absTop, std::min(absBottom, newMousePoint.y));
				mSliderPoint.y = newMousePoint.y - mSliderStartTrackHeight;
			}
		}

		float ratio = 0.0f;
		if (mOrientation == HORIZONTAL) {
			ratio = (mSliderPoint.x - mSliderArea.left) /
				std::max(1.0f, mSliderArea.width() - thumb.x);
		} else if (mOrientation == VERTICAL) {
			ratio = (mSliderPoint.y - mSliderArea.top) /
				std::max(1.0f, mSliderArea.height() - thumb.y);
		} else {
			ratio = (mSliderArea.bottom - thumb.y - mSliderPoint.y) /
				std::max(1.0f, mSliderArea.height() - thumb.y);
		}
		mCurrentPosition = mMinRange + static_cast<int>(ratio * (mMaxRange - mMinRange));

		mOldMousePoint = newMousePoint;

		draw();

		// Tell our observers we changed.
		notifyObservers();
	}
}

bool Scrollbar::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw()  // return true if completely handled
{
    using namespace std;
    bool handled = false;

//  OS::_DOUT( "EventHandler %s\n", mName.c_str() );

    if (inEventType == eventType_Timer)
	{
        TimerInfo* ti = static_cast<TimerInfo*>(inEventData);
//		OS::_DOUT( " got eventType_Timer: id [%d] ms [%d]\n", ti->inID, ti->inMillisec );
		if (this == (Scrollbar*)(ti->userData))
		{
			switch( ti->id )
			{
			case PDG_SCROLLBAR_CLICK_PAUSE:
				mTimerMgr.startTimer(PDG_SCROLLBAR_REPEATER, SCROLLBAR_REPEATER_MSTIME, timer_Repeating, UserData::makeUserDataFromPointer(this, data_DoNothing) );
				handled = true;
				break;

			case PDG_SCROLLBAR_REPEATER:
				if ( mScrollUpClicked )
				{
					scrollUp();
				}
				else if ( mScrollDownClicked )
				{
					scrollDown();
				}
				else if ( mScrollUpFullWindowClicked )
				{
					scrollUpFullWindow();
				}
				else if ( mScrollDownFullWindowClicked )
				{
					scrollDownFullWindow();
				}

				handled = true;
				break;

			case PDG_SCROLLBAR_TRACKER:
				if ( mScrollSliderClicked )
				{
					trackScrollSlider();
				}
				handled = true;
				break;
			}
		}
	}
	return handled;

}

bool Scrollbar::doMouseUp(const MouseInfo *mi, int id, int part)
{
	if (mScrollUpClicked)
	{
		scrollUpReleased();
	}

	if (mScrollDownClicked)
	{
		scrollDownReleased();
	}

	if (mScrollSliderClicked || mScrollDownFullWindowClicked || mScrollUpFullWindowClicked)
	{
		scrollSliderAreaReleased();
	}
	return true;
}

bool Scrollbar::doMouseDown(const MouseInfo *mi, int id, int part)
{
	if (part == Scrollbar::CLICK_ID_SCROLL_UP)
	{
		scrollUpPressed();
	}
	else if (part == Scrollbar::CLICK_ID_SCROLL_DOWN)
	{
		scrollDownPressed();
	}
	else if (part == Scrollbar::CLICK_ID_SLIDER_AREA)
	{
		Point clickPoint = mi->mousePos;
		scrollSliderAreaPressed(clickPoint);
	}
	return true;
}

} // namespace pdg
