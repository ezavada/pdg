// -----------------------------------------------
// Controller.cpp
// 
// Implementation of a base class to manage views
// and handle events
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

#include "pdg/sys/os.h"
#include "pdg/sys/platform.h"
#include "pdg/sys/graphics.h"
#include "pdg/app/Controller.h"
#include "pdg/app/View.h"

#define DBL_CLICK_TIME 250 // milliseconds allowed between clicks of a double-click

namespace pdg {

Controller::Controller(Application* app, bool wantKeyUpDown, bool wantKeyPress, 
                        bool wantMouseEnterLeave, bool wantAll, bool drawInactive) 
 : mApp(app), mViews(), mChildren(), mParent(0), 
   mPort(app->getGraphicsManager().getMainPort()),
   mLastClicked(0), mClickCount(0), 
   mRightClick(false), mActive(true), mDrawing(false), mWantsAllEvents(wantAll), mDrawInactive(drawInactive),
   mViewOnLastMouseMoved(0),
   mLasthitViewID(-1),
   mLasthitViewPart(-1) 
{
    EventManager& emgr = mApp->getEventManager();
    emgr.addHandler(this, eventType_MouseUp);       // we always get clicks
    emgr.addHandler(this, eventType_MouseDown);
	emgr.addHandler(this, eventType_MouseMove);
    if (wantKeyUpDown) {
        emgr.addHandler(this, eventType_KeyUp);
        emgr.addHandler(this, eventType_KeyDown);
    }
    if (wantKeyPress) {
        emgr.addHandler(this, eventType_KeyPress);
    }
    if (wantMouseEnterLeave) {
//		  emgr.addHandler(this, eventType_MouseEnter);
//        emgr.addHandler(this, eventType_MouseLeave);
    }
    if (wantAll) {
        emgr.addHandler(this, all_events);
    }
	if (mPort) {
		mCachedPortDrawingArea = mPort->getDrawingArea();
	}
}

Controller::~Controller() {
    // make sure our parent doesn't reference us anymore
    if (mParent) {
        mParent->removeChild(this);
    }
	// make sure our children don't reference us anymore
	Children::iterator citr;
	for(citr = mChildren.begin(); citr != mChildren.end(); citr++) {
		Controller* child = *citr;
        child->setParent(0);
	}
    // do an addRef() to ensure that the removal of handlers won't call 
    // delete again on this object. Since we are already deleting, the 
    // addRef() is harmless, the object will be deleted anyway
    addRef();
    EventManager& emgr = mApp->getEventManager();
    emgr.removeHandler(this, eventType_KeyUp);
    emgr.removeHandler(this, eventType_KeyDown);
    emgr.removeHandler(this, eventType_KeyPress);
//    emgr.removeHandler(this, eventType_MouseEnter);
//    emgr.removeHandler(this, eventType_MouseLeave);
    emgr.removeHandler(this, eventType_MouseUp);
    emgr.removeHandler(this, eventType_MouseDown);
	emgr.removeHandler(this, eventType_MouseMove);
    if (mWantsAllEvents) {
        emgr.removeHandler(this, all_events);
    }
    removeAllViews();
}


void Controller::addView(const View* view, int id) {
	// Add the ID and name pair to our list
#ifdef DEBUG
    if ((id != 0) && getUntypedView(id)) {
        OS::_DOUT("ERROR: Controller adding duplicate view id!");
    }
	ViewList::iterator itr;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
		if (val.first == view) {
            OS::_DOUT("ERROR: Controller adding duplicate view object!");
		}
	}
#endif // DEBUG
    if (view) { // don't add null views
    	idViewPair val( const_cast<View*>(view), id );
    	mViews.push_back( val );
    	view->addRef();
	}
}

void Controller::addViewBehind(const View* view, int id) {
	// Add the ID and name pair to our list
#ifdef DEBUG
    if ((id != 0) && getUntypedView(id)) {
        OS::_DOUT("ERROR: Controller adding duplicate view id!");
    }
	ViewList::iterator itr;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
		if (val.first == view) {
            OS::_DOUT("ERROR: Controller adding duplicate view object!");
		}
	}
#endif // DEBUG
    if (view) { // don't add null views
    	idViewPair val( const_cast<View*>(view), id );
    	mViews.insert( mViews.begin(), val );   // add behind all other views
    	view->addRef();
	}
}

void Controller::removeView(const View* view) {
	ViewList::iterator itr;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
		if (val.first == view) {
            mViews.erase(itr);
            view->release();
            return;
		}
	}
}

// remove absolutely all the views from the controller
void Controller::removeAllViews() {
    // release all the views
	ViewList::iterator itr;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
		View* view = val.first;
        view->release();
	}
    mViews.clear();
}


// will only fetch views that were assigned non-zero id
View* Controller::getUntypedView(int id) {
	ViewList::iterator itr;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
		if (val.second == id) {
		    return val.first;
		}
	}
    return 0;
} 

// don't do any redraws for a while, we are drawing
bool Controller::startDrawing() {
    bool result = mDrawing;
    mDrawing = true;
    return result;
}

// do needed redraws now, we are done drawing
void Controller::doneDrawing(bool wasDrawing) {
    if (mDrawing) {
        mDrawing = wasDrawing;
    }
    // only if we are really and truely done with the batch drawing do we
    // do the redraw of all the children
    if (!mDrawing) {
        viewRedrawn(0);
    }
}

// redraws any children or overlapping views if needed
void Controller::viewRedrawn(View* redrawnView) {
	if (!mDrawInactive && !mActive) return; // don't draw if we are inactive unless we draw while inactive
    // ignore if we are in the middle of a big redraw
    if (mDrawing) return;
	
//    Rect areaAffected;
//    if (redrawnView) {
//        areaAffected = redrawnView->getViewArea();
//    }
//    if (areaAffected.empty()) {
//        // if no area specified, assume everything is affected
//        DEBUG_ASSERT(mPort, "Drawing before mPort initialized!");
//        areaAffected = mPort->getDrawingArea();
//    }
    // first redraw all of our views that are on top of this one
    // draw back to front, so most recently added overlays oldest
    // ERZ, 6/23/04, need to add this back in at some point,
    // but for now it causes too many redraw problems
//    bool wasDrawing = mDrawing;
//    mDrawing = true;    // prevent infinite loops
//	ViewList::iterator itr;
//	bool passedRedrawnView = redrawnView ? false : true;    // if there wasn't one, we already passed it
//	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
//		idViewPair val = *itr;
//        View* view = val.first;
//        if (view == redrawnView) {
//            passedRedrawnView = true;
//        } else if (passedRedrawnView && view->isVisible()) {
//		    Rect viewRect = view->getViewArea();
//		    if (areaAffected.overlaps(viewRect)) {
//    			view->draw();
//			}
//		}
//	}
//    mDrawing = wasDrawing;
	
    // if the controller has children, then they may have been overdrawn by
    // what just happened, so redraw all the children in the affected area
	Children::iterator citr;
	for(citr = mChildren.begin(); citr != mChildren.end(); citr++) {
		Controller* child = *citr;
//        child->redrawSelf(areaAffected);
		child->redraw();
	}
}

// redraws everything in this controller hiearchy
void Controller::redrawAll() {
	if (!mDrawInactive && !mActive) return; // don't draw if we are inactive unless we draw while inactive
    if (mParent) {
        mParent->redrawAll(); // pass off to our parent if we have one
    } else {
        redraw();   // if not, start drawing ourself and our children
    }
}

// redraw ourself and our children
void Controller::redraw() {
	if (!mDrawInactive && !mActive) return; // don't draw if we are inactive unless we draw while inactive
    if (!mDrawing) {    // don't do this if we are being batched
        redrawSelf();
    	// now redraw any children
    	viewRedrawn(0);
	}
}

void Controller::redrawSelf(Rect areaAffected) {
	if (!mDrawInactive && !mActive) return; // don't draw if we are inactive unless we draw while inactive
    Rect clipSave = mPort->getClipRect();
    bool clipped = false;
    if (areaAffected.empty()) {
        // if no area specified, assume everything is affected
        areaAffected = mPort->getDrawingArea();
    } else if (!clipSave.empty()) {
        // if an affected area was specified, then make sure
        // we clip to the affected area so we don't accidentially
        // erase stuff we don't need to erase.
		Rect ourClip = areaAffected.intersection(clipSave);
		if (ourClip.empty()) return;   // there is nothin to draw, the clip rect turned up empty after
		                               // the intersection with the affected area
		
		mPort->setClipRect(ourClip);

		// test code here
//		mPort->frameRectEx(ourClip, 2, Graphics::solidPat, 0, PDG_WHITE_COLOR);
//		ourClip.shrink(2);
//		mPort->setClipRect(ourClip);
		
		clipped = true;
    }
    // draw back to front, so most recently added overlays oldest
	ViewList::iterator itr;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
        View* view = val.first;
		if(view->isVisible())
		{
		    Rect viewRect = view->getViewArea();
		    if (areaAffected.overlaps(viewRect)) {
    		    bool wasDrawing = mDrawing;
    		    mDrawing = true;
    			view->draw();
    			mDrawing = wasDrawing;
			}
		}
	}
	// restore the clip rect
	if (clipped) {
	    mPort->setClipRect(clipSave);
	}
}

bool Controller::doMouseDown(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something when mouse button transistions from up to down
	
    // clicks are generally handled in doLeftClick() or doRightClick()
	return false;
}

bool Controller::doMouseUp(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something when mouse button transistions from down to up
    // clicks are generally handled in doLeftClick() or doRightClick()
    // Return true from this method to completely swallow the mouse up event
    // and prevent any doClick method from being called
    // IF YOU DELETE THIS CONTROLLER FROM WITHIN THIS METHOD, YOU MUST RETURN TRUE!!!
    return false;
}

void Controller::doMouseEnter(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something when the mouse enters a view
    // check the MouseInfo struct to see if the mouse button is up or down
}

void Controller::doMouseLeave(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something when the mouse leaves a view
    // check the MouseInfo struct to see if the mouse button is up or down
//	if(view)
//	view->doMouseLeave(mi->mousePos, id, part);
}

void Controller::doMouseMove(const MouseInfo *mi, View* view, int id, int part){
//	if(view)
//	view->doMouseMove(mi->mousePos, id, part);
}

bool Controller::doLeftClick(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something with the left mouse button is clicked and released in the same part
	return false;
}

bool Controller::doRightClick(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something with the right mouse button is clicked and released in the same part
	return false;
}

bool Controller::doDoubleClick(const MouseInfo *mi, View* view, int id, int part, int clickCount) {
    // override to do something with the left mouse button is clicked and released twice (or more) in the same part
    // mClickCount is the number of successive rapid clicks, so mClickCount==2 is double click, 
    // mClickCount==3 is triple click, etc...
	// Treat double clicks as single clicks unless you override this function to handle them.
	return doLeftClick(mi, view, id, part);
}

// doDragMove is called when the mouse when down within the view and is now moving while held down
// it will also be called when the TouchMove gesture exits the view, but the finger remains down
bool Controller::doDragMove(const MouseInfo *mi, View* view, int id, int part)
{
	if (view) {
		return view->doDragMove(mi, id, part);
	} else {
		return false;
	}
}


// doDragIn is called when the mouse when down within the view and first moves over another view (the target view)
bool Controller::doDragIn(const MouseInfo* mi, View* view, int id, int part, View* targetView, int targetId, int targetPart)
{
	if (view) {
		return view->doDragIn(mi, id, part, targetView, targetId, targetPart);
	} else {
		return false;
	}
}


// doDragOut is called when the mouse when down within the view and first moves out of another view (the 
// target view). It is always preceeded by a doDragOut call
bool Controller::doDragOut(const MouseInfo* mi, View* view, int id, int part, View* targetView, int targetId, int targetPart)
{
	if (view) {
		return view->doDragOut(mi, id, part, targetView, targetId, targetPart);
	} else {
		return false;
	}
}

	
// startBeingDragTarget is called when the mouse went down in another view (the dragged view) and first moves 
// into this view
bool Controller::startBeingDragTarget(const MouseInfo* mi, View* view, int id, int part, View* draggedView, int draggedId, int draggedPart)
{
	if (view) {
		return view->startBeingDragTarget(mi, id, part, draggedView, draggedId, draggedPart);
	} else {
		return false;
	}
}
	
	
// stopBeingDragTarget is called when the mouse went down in another view (the dragged view) and moves out
// of this view. It is always preceeded by a startBeingDragTarget call
bool Controller::stopBeingDragTarget(const MouseInfo* mi, View* view, int id, int part, View* draggedView, int draggedId, int draggedPart)
{
	if (view) {
		return view->stopBeingDragTarget(mi, id, part, draggedView, draggedId, draggedPart);
	} else {
		return false;
	}
}
	
	
// doDragComplete is called with the mouse is released after a series of drag related calls
bool Controller::doDragComplete(const MouseInfo *mi, View* view, int id, int part)
{
	if (view) {
		return view->doDragComplete(mi, id, part);
	} else {
		return false;
	}
}
	
bool Controller::attemptChildClose(Controller* child, bool cancelled) {
    // override to do something when a child controller (one we own) is closed
    // usually the child is a Dialog, but it doesn't have to be
    return true;    // if we return false the child will not be allowed to close
}

void Controller::childActivated(Controller* child) {
    // override to do something when a child controller (one we own) is activated
    // usually the child is a Dialog, and we want to disable buttons
}

void Controller::addChild(Controller* child) {
    DEBUG_ONLY(
        Children::iterator itr;
    	for(itr = mChildren.begin(); itr != mChildren.end(); itr++) {
    		Controller* ctrl = *itr;
    		if (ctrl == child) {
                OS::_DOUT("ERROR: Controller [%p] attempt to add duplicate child [%p]", this, child);
                OS::_DEBUGGER("ERROR: Controller attempt to add duplicate child" );
                break;
    		}
    	}
	)
    mChildren.push_back(child);
	child->setParent(this);
}

void Controller::removeChild(Controller* child) {
    Children::iterator itr;
	for(itr = mChildren.begin(); itr != mChildren.end(); itr++) {
		Controller* ctrl = *itr;
		if (ctrl == child) {
            mChildren.erase(itr);
            child->setParent(0);
            return;
		}
	}
	DEBUG_ONLY(
        OS::_DOUT("ERROR: Controller [%p] attempt to remove non-child [%p]", this, child);
        OS::_DEBUGGER();
    )	    
}

// traverse the parents until a controller with no parent is found and return it
Controller& Controller::getTopController() {
    if (mParent) {
        return mParent->getTopController();
    } else {
        return *this;
    }
}


// an inactive Controller doesn't get input events (mouse, keyboard). Controllers are active by default.
void Controller::setActive(bool active) {
    mActive = active;
}

// following return true if handled
   // view is where mouse is located
bool Controller::doKeyDown(const KeyInfo* ki, View* view, int id, int part) {
    // override to do something when a key transitions from up to down
    return false;
} 
bool Controller::doKeyUp(const KeyInfo* ki, View* view, int id, int part) {
    // override to do something when a key transitions from down to up
    return false;
} 
bool Controller::doKeyPress(const KeyPressInfo* ki, View* view, int id, int part) {
    // override to do something when a keyboard character is generated
    return false;
}

void Controller::portWasResized(Port* resizedPort) {
	Rect oldDrawingArea = mCachedPortDrawingArea;
	Rect newDrawingArea = resizedPort->getDrawingArea();
    // give all our views a chance to adapt
	ViewList::iterator itr;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
		View* view = val.first;
		view->portResized(oldDrawingArea, newDrawingArea);
	}
	mCachedPortDrawingArea = newDrawingArea;

    // if the controller has children, then they may have been overdrawn by
    // what just happened, so redraw all the children in the affected area
	Children::iterator citr;
	for(citr = mChildren.begin(); citr != mChildren.end(); citr++) {
		Controller* child = *citr;
		//        child->redrawSelf(areaAffected);
		child->portWasResized(resizedPort);
	}
	
}
    
bool Controller::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {

    // we handle port resized events even when we are inactive
    if(inEventType == eventType_PortResized) {

        portWasResized(static_cast<PortResizeInfo*>(inEventData)->port);
        return false;   // we never handle a resized event completely ourselves, others must be informed of it
    
    }
    
    // don't handle any mouse or keyboard events if controller is inactive
    if (!mActive) return false;
    
    if (inEventType == eventType_Timer) return false; // we don't handle timer events, but lots
        // of controllers do and will call us, so we get called for tons of timer events that
        // we don't handle unless we bail now
    
    Point mpt = OS::getMouse();
    if ( (inEventType == eventType_MouseUp) || (inEventType == eventType_MouseDown) 
		|| (inEventType == eventType_MouseMove)) {
        // mouse event, mouse point is in the event
        mpt = static_cast<MouseInfo*>(inEventData)->mousePos;
    }
    // now find the view (if any) that has the mouse point
    View* hitView = 0;
    int hitViewID = 0;
    int hitViewPart = 0;
	ViewList::reverse_iterator itr;
	for(itr = mViews.rbegin(); itr != mViews.rend(); itr++) { // most recently added are checked first
		idViewPair val = *itr;
		View* view = val.first;
		if (view->isVisible()) {        // ignore invisible views
			if (view->isEnabled() || (inEventType == eventType_MouseMove)) {// ignore disabled views,except mousemove,need it to show tooltips
    			if (view->pointInViewVisibleArea(mpt)) {
					hitViewPart = view->getPartClicked(mpt);
					if (hitViewPart != View::CLICKED_PART_NONE) {   // a view must return a clicked part to get a click
        				hitView = view;
        				hitViewID = val.second;
						break;
    				}
    			}
			}
		}
	}
	
	// handle whatever kind of an event it was
    if ( (inEventType == eventType_MouseUp) || (inEventType == eventType_MouseDown)
		||(inEventType == eventType_MouseMove)){

        MouseInfo* mi = static_cast<MouseInfo*>(inEventData);
		bool handled = false;
        
        if (inEventType == eventType_MouseDown) {
        
            // mouse down, check for click count
            if ( (hitView == mLastClicked) && (mi->lastClickElapsed <= DBL_CLICK_TIME) ) {
                ++mClickCount;
            } else {
                mClickCount = 1;
                mLastClicked = hitView;
                mRightClick = mi->rightButton;
            }
            handled = doMouseDown(mi, hitView, hitViewID, hitViewPart);

		} else if (inEventType == eventType_MouseUp) {    // mouse up
            if (hitView != mLastClicked) {
                mClickCount = 0;    // do this here so click count will be correct for doMouseUp
            }
			handled = doMouseUp(mi, hitView, hitViewID, hitViewPart);
            if (!handled) {
                // after doMouseUp, do a click method if this was a complete click
                if (hitView == mLastClicked) {
                    if (mRightClick) {
                        handled = doRightClick(mi, hitView, hitViewID, hitViewPart);
                    } else if (mClickCount > 1) {
                        handled = doDoubleClick(mi, hitView, hitViewID, hitViewPart, mClickCount);
                    } else {
                        handled = doLeftClick(mi, hitView, hitViewID, hitViewPart);
                    }
                }
            }
        } else if (inEventType == eventType_MouseMove) { // check the mousemove event
		    //suraj add
			if ((mViewOnLastMouseMoved != hitView) || (hitViewID != hitViewID) ||
				(hitViewPart != mLasthitViewPart)) { // check if any part, ID, or view has changed
				if (mViewOnLastMouseMoved) {         // if changed, call the mouseleave for left place
					doMouseLeave(mi, mViewOnLastMouseMoved, mLasthitViewID, mLasthitViewPart);
				}
				if (hitView && (hitViewID > -1)) {    // if new view is valid than call mouse enter
					doMouseEnter(mi, hitView, hitViewID, hitViewPart);
				}
				mViewOnLastMouseMoved	=	hitView;	// update the new view for mouse
				mLasthitViewID			=	hitViewID;	// update the new ID for mouse
				mLasthitViewPart		=	hitViewPart;// update the new Part for mouse
			} else {
				if (hitView && (hitViewID > -1)) {      // if the mouse is moving , but no change in the place
					doMouseMove(mi, hitView, hitViewID, hitViewPart);   // than call mousemove
				}
			}
			handled = false;  // always propogating mouse moves as much as possible
		}

        // handling for non-modal dialogs and other types of nested controllers
        if ((hitView == 0) && mParent) {
            return mParent->handleEvent(inEmitter, inEventType, inEventData);
        }        

        return handled; // if any view reported hit, then we handled this event
   
    } else if (inEventType == eventType_KeyPress) {
    
        // key press, only handled if doKeyPress says we did
        return doKeyPress(static_cast<KeyPressInfo*>(inEventData), hitView, hitViewID, hitViewPart);
        
    } else if (inEventType == eventType_KeyDown) {
    
        // key down, only handled if doKeyDown says we did
        return doKeyDown(static_cast<KeyInfo*>(inEventData), hitView, hitViewID, hitViewPart);
        
    } else if (inEventType == eventType_KeyUp) {
    
        // key up, only handled if doKeyUp says we did
        return doKeyUp(static_cast<KeyInfo*>(inEventData), hitView, hitViewID, hitViewPart);
        
    }
	
    return false;  // we didn't handle this event
}

} // namespace pdg
