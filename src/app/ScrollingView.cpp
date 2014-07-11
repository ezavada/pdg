// -----------------------------------------------
// ScrollingView.cpp
// 
// Implementation for scrollable views
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

#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/sys/resource.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/os.h"
#include "pdg/app/ScrollingView.h"
#include "pdg/app/Controller.h"

namespace pdg {

ScrollingView::ScrollingView(Controller* controller, const Rect& rect, int viewBinding, BindType moveBinding)
 : View(controller, rect, viewBinding), mAutoAdjust(moveBinding)
{
	setViewFrame(rect);
}

ScrollingView::ScrollingView(Controller* controller, Port* port, const Rect& rect, int viewBinding, BindType moveBinding)
 : View(controller, port, rect, viewBinding), mAutoAdjust(moveBinding)
{
    setViewFrame(rect);
}

ScrollingView::~ScrollingView()
{

}

void ScrollingView::setViewFrame(const Rect& rect)
{
	mViewFrame = rect;
}


void ScrollingView::draw() { 
	
	TODO("Figure out why this clipping here doesn't work, but it does work if done within drawSelf()");
	
    // set up the clip rect
    Rect clipSave = mPort->getClipRect();
	Rect ourClip;
//	if (!clipSave.empty()) {
//		ourClip = mViewFrame.intersection(clipSave);
//	} else {
		ourClip = mViewFrame;
//	}
	if (!ourClip.empty() ) {  
		// don't draw if everything is clipped
//		mPort->setClipRect(ourClip);
		View::draw();
//		mPort->setClipRect(clipSave);
	}
}

bool ScrollingView::pointInViewVisibleArea(const Point& screenPoint)
{
	return mViewFrame.contains( screenPoint );
}

void ScrollingView::portResized(const Rect& oldDrawingArea, const Rect& newDrawingArea) {
	if (mBinding == 0) {
		return; // short circuit
	}
	Rect newViewFrame = mViewFrame;
	if (mBinding & bind_Left) {
		// bound to left, always change left to keep distance from left boundry
		newViewFrame.left = newDrawingArea.left + (mViewFrame.left - oldDrawingArea.left);
		if (mBinding & bind_Right) {
			// also bound to right, need to shrink or grow
			newViewFrame.right = newDrawingArea.right - (oldDrawingArea.right - mViewFrame.right );		
			// make sure we are within or min and max sizes
			if (mMaxWidth && mViewFrame.width() > mMaxWidth) {
				newViewFrame.setWidth( mMaxWidth );
			}
			if (mViewFrame.width() < mMinWidth) {
				newViewFrame.setWidth( mMinWidth );
			}
		} 
	} else if (mBinding & bind_Right) {
		// bound to right but not left, maintain width but move with right boundry
		newViewFrame.right = newDrawingArea.right - (oldDrawingArea.right - mViewFrame.right );		
		newViewFrame.left = newViewFrame.right - mViewFrame.width();
	}
	if (mBinding & bind_Top) {
		// bound to top, always change top to keep distance from top boundry
		newViewFrame.top = newDrawingArea.top + (mViewFrame.top - oldDrawingArea.top);
		if (mBinding & bind_Bottom) {
			// also bound to bottom, need to shrink or grow
			newViewFrame.bottom = newDrawingArea.bottom - (oldDrawingArea.bottom - mViewFrame.bottom );		
			// make sure we are within or min and max sizes
			if (mMaxHeight && mViewFrame.height() > mMaxHeight) {
				newViewFrame.setHeight( mMaxHeight );
			}
			if (mViewFrame.height() < mMinHeight) {
				newViewFrame.setHeight( mMinHeight );
			}
		} 
	} else if (mBinding & bind_Bottom) {
		// bound to bottom but not top, maintain height but move with bottom boundry
		newViewFrame.bottom = newDrawingArea.bottom - (oldDrawingArea.bottom - mViewFrame.bottom );		
		newViewFrame.top = newViewFrame.bottom - mViewFrame.height();
	}
	mViewFrame = newViewFrame;
}
	
	
// Move the view as needed so the frame is full of the view. If the frame is larger than 
// the view, then the view will bound within the frame according to the binding value passed in
// Return true if the view was actually moved, false if it was unchanged
bool ScrollingView::adjustViewAreaToFrame(BindType binding) {
	Rect r = mViewArea;
	// handle horizontal component
	// contrain the edges of the view area to the frame
	if (r.width() > mViewFrame.width()) {
		if (binding & bind_LimitX) {
			if (r.left > mViewFrame.left) {
				r.moveLeft(r.left - mViewFrame.left);
			} else if (r.right < mViewFrame.right) {
				r.moveRight(mViewFrame.right - r.right);
			}
		}
	} else {
		// view is smaller than frame: see if we have some kind of binding for that case 
		if ( (binding & bind_CenterX) == bind_CenterX) {
			long top = r.top;
			r.center(mViewFrame.centerPoint());
			r.moveYTo(top);
		} else if (binding & bind_Left) {
			r.moveXTo(mViewFrame.left);
		} else if (binding & bind_Right) {
			r.moveXTo(mViewFrame.right - mViewArea.width());
		}
	}
	// handle vertical component
	if (r.height() > mViewFrame.height()) {
		if (binding & bind_LimitY) {
			if (r.top > mViewFrame.top) {
				r.moveUp(r.top - mViewFrame.top);
			} else if (r.bottom < mViewFrame.bottom) {
				r.moveDown(mViewFrame.bottom - r.bottom);
			}
		}
	} else {
		// view is smaller than frame: see if we have some kind of binding for that case 
		if ( (binding & bind_CenterY) == bind_CenterY) {
			long left = r.left;
			r.center(mViewFrame.centerPoint());
			r.moveXTo(left);
		} else if (binding & bind_Top) {
			r.moveYTo(mViewFrame.top);
		} else if (binding & bind_Bottom) {
			r.moveYTo(mViewFrame.bottom - mViewArea.height());
		}
	}
	// finish up
	if (r == mViewArea) {
		return false; // no changes were made
	} else {
		mViewArea = r;
		return true;
	}
}


void ScrollingView::moveView(long deltaX, long deltaY) {
	mViewArea.moveRight(deltaX);
	mViewArea.moveDown(deltaY);
	if (mAutoAdjust != bind_None) {
		adjustViewAreaToFrame(mAutoAdjust);
	}
}
	
	
} // namespace pdg
