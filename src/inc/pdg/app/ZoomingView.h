// -----------------------------------------------
// ZoomingView.h
// 
// Base class for Views that are scrollable and scalable
//
// Copyright (c) 2010, Ed Zavada & Dream Rock Studios, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_ZOOMING_VIEW_H_INCLUDED
#define PDG_ZOOMING_VIEW_H_INCLUDED

#include "pdg/app/ScrollingView.h"

namespace pdg {


class ZoomingView : public ScrollingView
{
public:

    ZoomingView(Controller* controller, const Rect& rect); // port taken from controller
    ZoomingView(Controller* controller, Port* port, const Rect& rect);
	virtual ~ZoomingView();

	void setMaxScale(float max) { mMaxScale = max; }
	void setMinScale(float min) { mMinScale = min; }
	
	// Scale the view (and relocate it if needed) to fit into the frame
	// Return true if the view was actually resized, false if it was unchanged
	bool fitViewAreaToFrame(Image::FitType fitType = Image::fit_FillKeepProportions); // scale the 

	void scaleView(float amount, pdg::Point center);
	
protected:

	Rect mUnscaledViewArea;
	float mMaxScale;
	float mMinScale;

private:

	// Disallow default construction 
	ZoomingView();
};

} // end namespace pdg


#endif // PDG_ZOOMING_VIEW_H_INCLUDED

