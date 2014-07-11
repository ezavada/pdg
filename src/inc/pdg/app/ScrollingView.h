// -----------------------------------------------
// ScrollingView.h
// 
// Base class for Views that are scrollable
//
// Copyright (c) 2010, Ed Zavada & Dream Rock Studios, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_SCROLLING_VIEW_H_INCLUDED
#define PDG_SCROLLING_VIEW_H_INCLUDED

#include "pdg/app/View.h"

namespace pdg {


class ScrollingView : public View
{
public:

    enum BindType {
		bind_None	  = 0,
		bind_LimitX   = 1 << 1,                      // keep view X edges within frame X
		bind_LimitY   = 1 << 2,                      // keep view Y edges within frame Y
		bind_LimitXY  = bind_LimitX | bind_LimitY,   // limit view to keep it within frame at all times
        bind_Top      = 1 << 3,                      // when view smaller than frame, keep top edge of view aligned with top of frame
        bind_Bottom   = 1 << 4,                      // when view smaller than frame, keep bottom edge of view aligned with bottom of frame
        bind_CenterY  = bind_Top | bind_Bottom,      // when view smaller than frame, keep view centered vertically within frame
        bind_Left     = 1 << 5,                      // when view smaller than frame, keep left edge of view aligned with left of frame
        bind_Right    = 1 << 6,                      // when view smaller than frame, keep right edge of view aligned with right of frame
		bind_CenterX  = bind_Left | bind_Right,      // when view smaller than frame, keep view centered horizontally within frame
		bind_Centers  = bind_CenterX | bind_CenterY,
		bind_Default  = bind_LimitXY
    };
	
    ScrollingView(Controller* controller, const Rect& rect, int viewBinding = 0, BindType moveBinding = bind_Default); // port taken from controller
    ScrollingView(Controller* controller, Port* port, const Rect& rect, int viewBinding = 0, BindType moveBinding = bind_Default);
	virtual ~ScrollingView();

	virtual void draw();
	
	void setViewFrame(const Rect& rect);   // in global/port coordinates
	const Rect& getViewFrame() const { return mViewFrame; }  // in global/port coordinates
	Rect& getModifiableViewFrameRect() { return mViewFrame; } // in global/port coordinates
	
	virtual bool pointInViewVisibleArea(const Point& screenPoint); // in global/port coordinates
	
	virtual void portResized(const Rect& oldDrawingArea, const Rect& newDrawingArea);

	bool pointInViewFrame(const Point& screenPoint) { return mViewFrame.contains( screenPoint ); } // in global/port coordinates

	// set the automatic adjustments applied to the view after moving and/or scaling
	void setAutoAdjust(BindType moveBinding) { mAutoAdjust = moveBinding; }

	// Move the view as needed so the frame is full of the view. If the frame is larger than 
	// the view, then the view will bound within the frame according to the binding value passed in
	// Return true if the view was actually moved, false if it was unchanged
	bool adjustViewAreaToFrame(BindType moveBinding = bind_Centers);
	
	
	void moveView(long deltaX, long deltaY);
	
protected:

	Rect mViewFrame;
	BindType mAutoAdjust;

private:

	// Disallow default construction 
	ScrollingView();
};

} // end namespace pdg


#endif // PDG_SCROLLING_VIEW_H_INCLUDED
