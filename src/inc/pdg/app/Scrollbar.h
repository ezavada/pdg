// -----------------------------------------------
// Scrollbar.h
// 
// Definitions for drawing a Scrollbar
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_SCROLLBAR_H_INCLUDED
#define PDG_SCROLLBAR_H_INCLUDED

#include "pdg/app/View.h"
#include "pdg/app/Observer.h"
#include "pdg/sys/core.h"

namespace pdg {

class EventManager;
class ResourceManager;
class TimerManager;

class Scrollbar : public RefCountedImpl<IEventHandler>, public View, public Subject
{
public:
	enum Orientation
	{
		HORIZONTAL,
		VERTICAL,   // up is smaller
		VERTICAL_UP_IS_BIGGER
	};

	enum ClickIds
	{
		CLICK_ID_SCROLL_UP,
		CLICK_ID_SCROLL_DOWN,
		CLICK_ID_SLIDER_AREA
	};

	enum scrollImages
	{
		SCROLL_DOWN,
		SCROLL_UP,
		SCROLL_SLIDER,
		SCROLL_DOWN_CLICKED,
		SCROLL_UP_CLICKED,
		MAX_SCROLL_BAR_IMAGES
	};

	// NOTE: This scrollbar class was written close to the Java 1.5 Scrollbar class.
	//       To learn about the parameters to this contructor goto:
	//       http://java.sun.com/j2se/1.5.0/docs/api/java/awt/Scrollbar.html
    Scrollbar(Controller* controller, const Rect& scrollBarRect, Orientation orientation, int initValue, int visibleAmount, int rangeSize);
	~Scrollbar();

	void loadImages(int scrollbarImagesResourceID);
	void calcClickableAreas();
	void drawSelf();

	void drawScrollBar();
	void scrollUp();
	void scrollUpPressed();
	void scrollUpReleased();
	void scrollDown();
	void scrollDownPressed();
	void scrollDownReleased();
	void scrollSliderAreaPressed(Point& clickPoint);
	void scrollSliderAreaReleased();
	void scrollUpFullWindow();
	void scrollDownFullWindow();
	void trackScrollSlider();

	bool doMouseUp(const MouseInfo *mi, int id, int part);
	bool doMouseDown(const MouseInfo *mi, int id, int part);

	int  getCurrentPosition() { return mCurrentPosition; }
	int  getScrollRange() { return mMaxRange - mMinRange; }
	void setMaxRange(int range) { mMaxRange = range; }
	void setCurrentPosition(int position) { mCurrentPosition = (position <= mMaxRange) ? position : mMaxRange; }

	// From IEventHandler
    bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled

private:
    EventManager& mEventMgr;
    ResourceManager& mResMgr;
    TimerManager& mTimerMgr;

	Orientation mOrientation;
	Image* mpScrollBarImages[MAX_SCROLL_BAR_IMAGES];
	Point mUpButtonPoint;
	Point mDownButtonPoint;
	Rect  mSliderArea;

	Point mSliderStartTrackPoint;
	Point mOldMousePoint;
	int   mSliderStartTrackHeight;
	Point mSliderPoint;
	int   mMinRange;
	int   mMaxRange;
	int   mStepSize;
	int   mPageSize;
	int   mCurrentPosition;

	bool  mScrollUpClicked;
	bool  mScrollDownClicked;
	bool  mScrollUpFullWindowClicked;
	bool  mScrollDownFullWindowClicked;
	bool  mScrollSliderClicked;
};

} // close namespace pdg

#endif // PDG_SCROLLBAR_H_INCLUDED

