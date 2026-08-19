// -----------------------------------------------
// Dialog.cpp
//
// Implementation of a class to manage views
// and handle events for a dialog
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

#include "pdg/app/Dialog.h"
#include "pdg/app/Button.h"
#include "pdg/app/View.h"
#include "pdg/sys/attributes.h"

#define PART_DIALOG_BKGRND      1
#define DIALOG_BKGRND_VIEW_ID   -100

#define DEFAULT_DIALOG_BORDER_WIDTH    1

namespace pdg {

class DialogBackgroundView : public View {
public:
    DialogBackgroundView(Dialog* dialog, const Rect aRect, const ControlAttributes& attributes,
                         Color borderColor = PDG_BLACK_COLOR, Color fillColor = PDG_WHITE_COLOR,
                         int borderWidth = DEFAULT_DIALOG_BORDER_WIDTH )
        : View(dialog, aRect),
        mBorderColor(borderColor),
        mFillColor(fillColor),
        mBorderWidth(borderWidth) {
		mAttributes.merge(attributes);
        mViewArea.grow(borderWidth);
        addClickablePart(globalToLocal(mViewArea), PART_DIALOG_BKGRND);
    }

    void drawSelf() {
		const ControlStateAttributes& themed = mAttributes.state(ControlState::Normal);
		if (themed.hasDrawRoutine || themed.hasImage || themed.hasDrawing) {
			mAttributes.draw(*mPort, mViewArea, ControlState::Normal);
			return;
        }
        mPort->drawRect(mViewArea, Attributes().fillColor(mFillColor));
        mPort->drawRect(mViewArea, Attributes().lineColor(mBorderColor).lineThickness(mBorderWidth));
//        mController->viewRedrawn();
    }

protected:
    Color mBorderColor;
    Color mFillColor;
    int   mBorderWidth;
	ControlAttributes mAttributes;
};



Dialog::Dialog(Controller* parentController, int width, int height, uint32 flags, int okButtonId, int cancelButtonId)
 : Controller(&parentController->getApplication()),
   mButtonWithMouseDown(0),
   mOkButtonId(okButtonId),
   mCancelButtonId(cancelButtonId),
   mFlags(flags),
   mViewVisibilitySave(0),
   mParentController(parentController)
{
	// Set Dialog Rect here
	Rect dialogRect(width, height);
	setDialogRect(dialogRect);

    // create the background view
    if (flags & dialog_CreateBackground) {
        View* bkgnd = new DialogBackgroundView(this, mDialogRect,
			parentController->getTopController().getControlAttributes(ControlType::Dialog));
        addView(bkgnd, DIALOG_BKGRND_VIEW_ID);
    }

    parentController->addChild(this);   // this will do a setParent on us to set our mParent member
    mParent->childActivated(this);
    if (!(flags & dialog_NonModal)) {
        mParent->setActive(false);  // deactivate the parent if this is a modal dialog
    }

    // we want to get port resized events so we can recenter ourselves
    EventManager& emgr = mApp->getEventManager();
    emgr.addHandler(this, eventType_PortResized);
}

Dialog::~Dialog() {
    // do an addRef() to ensure that the removal of handlers won't call
    // delete again on this object. Since we are already deleting, the
    // addRef() is harmless, the object will be deleted anyway
    addRef();
    EventManager& emgr = mApp->getEventManager();
    emgr.removeHandler(this, eventType_PortResized);
}


bool Dialog::doMouseDown(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something when mouse button transistions from up to down
    // clicks are generally handled in doLeftClick() or doRightClick()
    if (view && ((id == mOkButtonId) || (id == mCancelButtonId))) {
        Button* button = static_cast<Button*>(view);
        button->setClickState(true);
        mButtonWithMouseDown = button;
    }
	return true;
}

bool Dialog::doMouseUp(const MouseInfo *mi, View* view, int id, int part) {
    // override to do something when mouse button transistions from down to up
    // clicks are generally handled in doLeftClick() or doRightClick()
    if (mButtonWithMouseDown) {
		mButtonWithMouseDown->playClickSound();
        mButtonWithMouseDown->setClickState(false);
        mButtonWithMouseDown = 0;
    }
    return false;   // we haven't handled this completely, let the doClick() methods be called
}

bool Dialog::doLeftClick(const MouseInfo *mi, View* view, int id, int part) {
	if ( id == mOkButtonId ) {
	    doClose(kAccepted);
	} else if ( ( mCancelButtonId != -1) && (id == mCancelButtonId) ) {
	    doClose(kCancelled);
	} else if ( id == DIALOG_BKGRND_VIEW_ID ) {
	    // do nothing if click was in the background
	}
	return true;
}

// following return true if handled
bool Dialog::doKeyPress(const KeyPressInfo* ki, View* view, int id, int part) {
    View* button = 0;
    if ( ( mOkButtonId != -1) && (ki->unicode == key_Return) ) {   // <enter>
        button = getUntypedView(mOkButtonId);
        if (button && button->isEnabled()) {    // can't press disabled button, even with key equivalent
    	    doClose(kAccepted);
    	    return true;
	    }
    } else if ( ( mCancelButtonId != -1) && ( ki->unicode == key_Escape ) ) {    // <esc>
        button = getUntypedView(mCancelButtonId);
        if (button && button->isEnabled()) {    // can't press disabled button, even with key equivalent
            doClose(kCancelled);
	        return true;
	    }
    }
    return Controller::doKeyPress(ki, view, id, part);
}

// recenter if our port was resized
void Dialog::portWasResized(Port* resizedPort) {
    // recalculate the location of the dialog
    Point topLeft;
    int width = mDialogRect.width();
    int height = mDialogRect.height();

	Rect drawingArea = resizedPort->getDrawingArea();
	Rect presentationArea = getTopController().getDialogPresentationArea(resizedPort);
	topLeft.x = presentationArea.left + (presentationArea.width() - width) / 2;
	if (topLeft.x < drawingArea.left + 20) {
		// If the preferred area is too narrow, center in the full drawing area.
		topLeft.x = drawingArea.left + (drawingArea.width() - width) / 2;
	}

    if (mFlags & dialog_Centered) {
        topLeft.y = (resizedPort->getDrawingArea().height() - height) / 2;
    } else {
        topLeft.y = (resizedPort->getDrawingArea().height() - height) / 3;
    }

    // now that we have the new position, move everything to it
    Point offsetPt = topLeft - mDialogRect.leftTop();
    mDialogRect.moveRight(offsetPt.x);
    mDialogRect.moveDown(offsetPt.y);

	ViewList::iterator itr;
//	int i=0;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
        View* view = val.first;
		Rect& vr = view->getModifiableViewAreaRect();
        vr.moveRight(offsetPt.x);
        vr.moveDown(offsetPt.y);
	}
}

void Dialog::doClose(bool cancelled) {
    if (mParent && mParent->attemptChildClose(this, cancelled)) {  // make sure the parent is willing to let us close
		// We check this after attemptChildClose in case parent was deleted as a result of the child being closed.
		// If this happens, the parent pointer gets set to zero in the controller destructor.
		Controller *parent = mParent;
        delete this;
		if (parent) {
			parent->setActive(true);    // reactivate the parent
		}
    }
}

// Shows dialog after it was hidden
void Dialog::showDialog()
{
    if (!mViewVisibilitySave) {
        return;     // we never hid this dialog
    }

	ViewList::iterator itr;
	int i=0;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
        View* view = val.first;
		if (mViewVisibilitySave[i++])
		{
			view->show();
		}
	}

	delete [] mViewVisibilitySave;
	mViewVisibilitySave = 0;

}

// Hides dialog from view but doesn't close it.
void Dialog::hideDialog()
{
	if (mViewVisibilitySave) // Don't hide if we are already hidden, it will overwrite our view visibility array.
	{
		return;
	}

	ViewList::iterator itr;
	int i=0;
	mViewVisibilitySave = new bool[mViews.size()];
    CHECK_NEW(mViewVisibilitySave, bool[]);
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
        View* view = val.first;
		mViewVisibilitySave[i++] = view->isVisible();
		if (view->isVisible())
		{
			view->hide();
		}
	}

}

void Dialog::setDialogRect(const Rect& dialogRect)
{
    // calculate the location of the dialog
    Point topLeft;
    Port* port = getApplication().getGraphicsManager().getMainPort();
    if (port) {

		Rect drawingArea = port->getDrawingArea();
		Rect presentationArea = mParentController->getTopController().getDialogPresentationArea(port);
		topLeft.x = presentationArea.left + (presentationArea.width() - dialogRect.width()) / 2;
		if (topLeft.x < drawingArea.left + 20) {
			// If the preferred area is too narrow, center in the full drawing area.
			topLeft.x = drawingArea.left + (drawingArea.width() - dialogRect.width()) / 2;
		}

        if (mFlags & dialog_Centered) {
            topLeft.y = (port->getDrawingArea().height() - dialogRect.height()) / 2;
        } else {
            topLeft.y = (port->getDrawingArea().height() - dialogRect.height()) / 3;
        }
    }
    Rect area(topLeft, dialogRect.width(), dialogRect.height());
    mDialogRect = area;
}

} // namespace pdg
