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
#include "pdg/framework.h"
#include "timerids.h"

#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
  #include "CatanUIConsts.h"
#endif

#ifndef SCROLLBAR_SLIDER_BG_COLOR
#define SCROLLBAR_SLIDER_BG_COLOR Color(76, 100, 126)
#endif

namespace pdg {

const int SCROLLBAR_CLICK_PAUSE_MSTIME = 250;
const int SCROLLBAR_REPEATER_MSTIME = 40;
const int SCROLLBAR_TRACKER_MSTIME = 30;

const int RES_DEFAULT_VERTICAL_SCROLLBAR_IMAGES = 123;
const int RES_DEFAULT_HORIZONTAL_SCROLLBAR_IMAGES = 135;

const Rect goodRangeOffset(-50, -50, 50, 50);       // x,y

// NOTE: This scrollbar class was written close to the Java 1.5 Scrollbar class.
//       To learn about the parameters to this contructor goto:
//       http://java.sun.com/j2se/1.5.0/docs/api/java/awt/Scrollbar.html
Scrollbar::Scrollbar(Controller* controller, const Rect& scrollBarRect, Orientation orientation, int initValue, int visibleAmount, int rangeSize) 
: View(controller, scrollBarRect),
	mEventMgr(controller->getApplication().getEventManager()), 
	mResMgr(controller->getApplication().getResourceManager()), 
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
	// Load default images for now. 
	// Call loadImages explictly after you create the scrollbar and pass in 
	// a different resource ID for different scrollbar images.
	if(mOrientation == HORIZONTAL)
	{
		loadImages(RES_DEFAULT_HORIZONTAL_SCROLLBAR_IMAGES);
	}
	else if( (mOrientation == VERTICAL) || (mOrientation == VERTICAL_UP_IS_BIGGER) )
	{
		loadImages(RES_DEFAULT_VERTICAL_SCROLLBAR_IMAGES);
	}

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

void Scrollbar::loadImages(int scrollbarImagesResourceID)
{
	// Load scroll bar images
//	loadImageArray(mResMgr, mpScrollBarImages, scrollbarImagesResourceID, MAX_SCROLL_BAR_IMAGES);

	// Calc areas
	calcClickableAreas();
}

void Scrollbar::calcClickableAreas()
{
	Point sliderAreaTLPoint;
	Point sliderAreaBRPoint;
	Point viewAreaTLPoint;
	Point viewAreaBRPoint;

	if(mOrientation == HORIZONTAL)
	{
		// Calc right button areas
		if(mpScrollBarImages[SCROLL_UP])
		{
			viewAreaBRPoint = Point(mViewArea.width(), mpScrollBarImages[SCROLL_UP]->height);
			mUpButtonPoint = Point(mViewArea.width(), 0);
			mUpButtonPoint.x -= mpScrollBarImages[SCROLL_UP]->width;
			Point botImagePoint = mUpButtonPoint;
			botImagePoint.x += mpScrollBarImages[SCROLL_UP]->width;
			botImagePoint.y += mpScrollBarImages[SCROLL_UP]->height;
			Rect imageRect(mUpButtonPoint, botImagePoint);
			this->addClickablePart(imageRect, CLICK_ID_SCROLL_UP);

			sliderAreaBRPoint = mUpButtonPoint;
			sliderAreaBRPoint.y += mpScrollBarImages[SCROLL_UP]->height;
		}

		// Calc left button areas
		if(mpScrollBarImages[SCROLL_DOWN])
		{
			mDownButtonPoint = Point(0, 0);
			viewAreaTLPoint = mDownButtonPoint;
			Point botImagePoint = mDownButtonPoint;
			botImagePoint.x += mpScrollBarImages[SCROLL_DOWN]->width;
			botImagePoint.y += mpScrollBarImages[SCROLL_DOWN]->height;
			Rect imageRect(mDownButtonPoint, botImagePoint);
			this->addClickablePart(imageRect, CLICK_ID_SCROLL_DOWN);

			sliderAreaTLPoint = mDownButtonPoint;
			sliderAreaTLPoint.x += mpScrollBarImages[SCROLL_DOWN]->width; 
		}
	}
	else if( (mOrientation == VERTICAL) || (mOrientation == VERTICAL_UP_IS_BIGGER) )
	{
		// Calc top button areas
		if(mpScrollBarImages[SCROLL_UP])
		{
			mUpButtonPoint = Point(0,0);
			viewAreaTLPoint = mUpButtonPoint;
			Point botImagePoint = mUpButtonPoint;
			botImagePoint.x += mpScrollBarImages[SCROLL_UP]->width;
			botImagePoint.y += mpScrollBarImages[SCROLL_UP]->height;
			Rect imageRect(mUpButtonPoint, botImagePoint);
			this->addClickablePart(imageRect, CLICK_ID_SCROLL_UP);

			sliderAreaTLPoint = mUpButtonPoint;
			sliderAreaTLPoint.y += mpScrollBarImages[SCROLL_UP]->height; 
		}

		// Calc bottom button areas
		if(mpScrollBarImages[SCROLL_DOWN])
		{
			mDownButtonPoint = Point(0, mViewArea.height());
			viewAreaBRPoint = Point(mpScrollBarImages[SCROLL_DOWN]->width, mViewArea.height());
			Point botImagePoint = mDownButtonPoint;
			botImagePoint.x += mpScrollBarImages[SCROLL_DOWN]->width;
			mDownButtonPoint.y -= mpScrollBarImages[SCROLL_DOWN]->height;
			Rect imageRect(mDownButtonPoint, botImagePoint);
			this->addClickablePart(imageRect, CLICK_ID_SCROLL_DOWN);

			sliderAreaBRPoint = mDownButtonPoint;
			sliderAreaBRPoint.x += mpScrollBarImages[SCROLL_DOWN]->width; 
		}
	}

	// set new view area
	Rect newViewArea(viewAreaTLPoint, viewAreaBRPoint);
	this->setViewArea(localToGlobal(newViewArea));

	mSliderArea = Rect(sliderAreaTLPoint, sliderAreaBRPoint);
	this->addClickablePart(mSliderArea, CLICK_ID_SLIDER_AREA);

    // choose the starting location for the slider
    if (mOrientation == VERTICAL) 
    {
	    mSliderPoint = mSliderArea.rightTop();
	} 
	else 
	{
	    mSliderPoint = mSliderArea.rightBottom();
	}
	
	if(	mpScrollBarImages[SCROLL_SLIDER])
	{
		mSliderPoint.x -= mpScrollBarImages[SCROLL_SLIDER]->width;
		mSliderPoint.y -= mpScrollBarImages[SCROLL_SLIDER]->height;
	}
}

void Scrollbar::drawSelf()
{
	// draw top button
	if(mScrollUpClicked)
	{
		if(mpScrollBarImages[SCROLL_UP_CLICKED])
		{
			mpScrollBarImages[SCROLL_UP_CLICKED]->draw(localToGlobal(mUpButtonPoint));
		}
	}
	else
	{
		if(mpScrollBarImages[SCROLL_UP])
		{
			mpScrollBarImages[SCROLL_UP]->draw(localToGlobal(mUpButtonPoint));
		}
	}

	// draw bottom button
	if(mScrollDownClicked)
	{
		if(mpScrollBarImages[SCROLL_DOWN_CLICKED])
		{
			mpScrollBarImages[SCROLL_DOWN_CLICKED]->draw(localToGlobal(mDownButtonPoint));
		}
	}
	else
	{
		if(mpScrollBarImages[SCROLL_DOWN])
		{
			mpScrollBarImages[SCROLL_DOWN]->draw(localToGlobal(mDownButtonPoint));
		}
	}

	// draw grey slider area
	mPort->fillRect(localToGlobal(mSliderArea), SCROLLBAR_SLIDER_BG_COLOR);

	int scrollRange = mMaxRange - mMinRange;
	int sliderPos = 0;
	int sliderTravelHeight = 0;
	if(mpScrollBarImages[SCROLL_SLIDER])
	{
		// Compute Current Position if slider is moving
		if(mScrollSliderClicked)
		{
			if (mOrientation == HORIZONTAL)
			{
				sliderPos = mSliderPoint.x - mSliderArea.left;
				sliderTravelHeight = mSliderArea.width() - mpScrollBarImages[SCROLL_SLIDER]->width;
			}
			else if (mOrientation == VERTICAL)
			{
				sliderPos = mSliderPoint.y - mSliderArea.top;
				sliderTravelHeight = mSliderArea.height() - mpScrollBarImages[SCROLL_SLIDER]->height;
			}
			else if (mOrientation == VERTICAL_UP_IS_BIGGER)
			{
				sliderPos = mSliderArea.bottom - mpScrollBarImages[SCROLL_SLIDER]->height - mSliderPoint.y;
				sliderTravelHeight = mSliderArea.height() - mpScrollBarImages[SCROLL_SLIDER]->height;
			}
			mCurrentPosition = (int)(((float)sliderPos / (float)sliderTravelHeight) * scrollRange);
		}
		// Otherwise Compute Slider Position based on current position
		else
		{
			if (mOrientation == HORIZONTAL)
			{
				sliderPos = mCurrentPosition - mMinRange;
				sliderTravelHeight = mSliderArea.width() - mpScrollBarImages[SCROLL_SLIDER]->width;
				mSliderPoint.x = mSliderArea.left;
				mSliderPoint.x += (int)(((float)sliderPos / (float)scrollRange) * sliderTravelHeight);
			}
			else if (mOrientation == VERTICAL)
			{
				sliderPos = mCurrentPosition - mMinRange;
				sliderTravelHeight = mSliderArea.height() - mpScrollBarImages[SCROLL_SLIDER]->height;
				mSliderPoint.y = mSliderArea.top;
				mSliderPoint.y += (int)(((float)sliderPos / (float)scrollRange) * sliderTravelHeight);
			}
			else if (mOrientation == VERTICAL_UP_IS_BIGGER)
			{
				sliderPos = mCurrentPosition - mMinRange;
				sliderTravelHeight = mSliderArea.height() - mpScrollBarImages[SCROLL_SLIDER]->height;
				mSliderPoint.y = mSliderArea.bottom - mpScrollBarImages[SCROLL_SLIDER]->height;
				mSliderPoint.y -= (int)(((float)sliderPos / (float)scrollRange) * sliderTravelHeight);
			}
		}

		// draw the slider
		mpScrollBarImages[SCROLL_SLIDER]->draw(localToGlobal(mSliderPoint));
	}
	/*char text[20];
	std::snprintf(text, 20, "CurrPos=%d", mCurrentPosition);
    MAKE_STRING_BUFFER_SAFE(text, 20);
	Point textPt = mSliderArea.rightBottom() - Point(150,40);
	Point tl = textPt;
	tl = tl - Point(0, 20);
	Point br = textPt;
	br = br + Point(90, 0);
	Rect hi(tl, br);
	mPort->fillRect(localToGlobal(hi), PDG_WHITE_COLOR); 
	mPort->drawText(text, localToGlobal(textPt), 12);
	
	this->drawClickableParts();
	Rect viewArea(0,0,mViewArea.width(),mViewArea.height());
	mPort->frameRect(localToGlobal(viewArea), PDG_RED_COLOR);
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

	// Find thumb/slider area
	Rect thumbArea(0, 0);
	if(mpScrollBarImages[SCROLL_SLIDER])
	{
		Point thumbDim(mpScrollBarImages[SCROLL_SLIDER]->width, mpScrollBarImages[SCROLL_SLIDER]->height);
		Point sliderPt = mSliderPoint;
		thumbArea = Rect( mSliderPoint, sliderPt + thumbDim);
	}

	// Find slider areas
	Rect upperSliderArea = mSliderArea;
	Rect lowerSliderArea = mSliderArea;

	if(mOrientation == HORIZONTAL)
	{
		upperSliderArea.left = thumbArea.right + 1;
		lowerSliderArea.right = thumbArea.left - 1;
	}
	else if(mOrientation == VERTICAL)
	{
		upperSliderArea.bottom = thumbArea.top - 1;
		lowerSliderArea.top = thumbArea.bottom + 1;
	}

	// Check to see if the clicked point is above, on, or below the slider.
	if(upperSliderArea.contains(clickPoint))
	{
		mScrollUpFullWindowClicked = true;
		scrollUpFullWindow();
		mTimerMgr.startTimer(PDG_SCROLLBAR_CLICK_PAUSE, SCROLLBAR_CLICK_PAUSE_MSTIME, timer_OneShot, UserData::makeUserDataFromPointer(this, data_DoNothing) );
	}
	else if(thumbArea.contains(clickPoint))
	{
		mScrollSliderClicked = true;
		mOldMousePoint = mSliderStartTrackPoint = clickPoint;
		if(mOrientation == HORIZONTAL)
		{
			mSliderStartTrackHeight = mSliderStartTrackPoint.x - mSliderPoint.x;
		}
		else if(mOrientation == VERTICAL)
		{
			mSliderStartTrackHeight = mSliderStartTrackPoint.y - mSliderPoint.y;
		}
		mTimerMgr.startTimer(PDG_SCROLLBAR_TRACKER, SCROLLBAR_TRACKER_MSTIME, timer_Repeating, UserData::makeUserDataFromPointer(this, data_DoNothing) );
	}
	else if(lowerSliderArea.contains(clickPoint))
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
	
	if( newMousePoint != mOldMousePoint )
	{
		if(mpScrollBarImages[SCROLL_SLIDER])
		{
			// The mouse moved, check to see if the mouse is in a good range otherwise 
			// go back to our point where the user started.
			Rect goodRangeRect = this->mSliderArea;
			goodRangeRect = goodRangeRect + goodRangeOffset;
			//mPort->frameRect(localToGlobal(goodRangeRect), PDG_GREEN_COLOR);
			if(!goodRangeRect.contains(newMousePoint))
			{
				newMousePoint = mSliderStartTrackPoint;
			}
			else
			{
				// Check to see if the point is above or below the slider area...if so clamp it
				if(mOrientation == HORIZONTAL)
				{
					int absLeft = this->mSliderArea.left + mSliderStartTrackHeight;
					int absRight = this->mSliderArea.right - (mpScrollBarImages[SCROLL_SLIDER]->width - mSliderStartTrackHeight);
					if(newMousePoint.x < absLeft)
					{
						newMousePoint.x = absLeft;
					}
					else if(newMousePoint.x > absRight)
					{
						newMousePoint.x = absRight;
					}
					mSliderPoint.x = newMousePoint.x - mSliderStartTrackHeight;
				}
				else if ( (mOrientation == VERTICAL) || (mOrientation == VERTICAL_UP_IS_BIGGER))
				{
					int absTop = this->mSliderArea.top + mSliderStartTrackHeight;
					int absBottom = this->mSliderArea.bottom - (mpScrollBarImages[SCROLL_SLIDER]->height - mSliderStartTrackHeight);
					if(newMousePoint.y < absTop)
					{
						newMousePoint.y = absTop;
					}
					else if(newMousePoint.y > absBottom)
					{
						newMousePoint.y = absBottom;
					}
					mSliderPoint.y = newMousePoint.y - mSliderStartTrackHeight;
				}
			}
		}

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
		if(this == (Scrollbar*)(ti->userData))
		{
			switch( ti->id )
			{
			case PDG_SCROLLBAR_CLICK_PAUSE:
				mTimerMgr.startTimer(PDG_SCROLLBAR_REPEATER, SCROLLBAR_REPEATER_MSTIME, timer_Repeating, UserData::makeUserDataFromPointer(this, data_DoNothing) );
				handled = true;
				break;

			case PDG_SCROLLBAR_REPEATER:
				if( mScrollUpClicked )
				{
					scrollUp();
				}
				else if( mScrollDownClicked )
				{
					scrollDown();
				}
				else if( mScrollUpFullWindowClicked )
				{
					scrollUpFullWindow();
				}
				else if( mScrollDownFullWindowClicked )
				{
					scrollDownFullWindow();
				}

				handled = true;
				break;

			case PDG_SCROLLBAR_TRACKER:
				if( mScrollSliderClicked )
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
	if(mScrollUpClicked)
	{
		scrollUpReleased();
	}

	if(mScrollDownClicked)
	{
		scrollDownReleased();
	}

	if(mScrollSliderClicked || mScrollDownFullWindowClicked || mScrollUpFullWindowClicked)
	{
		scrollSliderAreaReleased();
	}
	return true;
}

bool Scrollbar::doMouseDown(const MouseInfo *mi, int id, int part)
{
	if(part == Scrollbar::CLICK_ID_SCROLL_UP)
	{
		scrollUpPressed();
	}
	else if(part == Scrollbar::CLICK_ID_SCROLL_DOWN)
	{
		scrollDownPressed();
	}
	else if(part == Scrollbar::CLICK_ID_SLIDER_AREA)
	{
		Point clickPoint = mi->mousePos;
		scrollSliderAreaPressed(clickPoint);
	}
	return true;
}

} // namespace pdg
