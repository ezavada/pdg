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

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
  #include "GameController.h"
  #include "BoardView.h"
#endif

#define PART_DIALOG_BKGRND      1
#define DIALOG_BKGRND_VIEW_ID   -100

#define CONTROL_DIVIDER_X		880.0f

#define BRIGHTEN(ch) if (ch < 0.5f) { ch += 0.5f; } else { ch = 1.0f; }
#define DARKEN(ch) if (ch > 0.5f) { ch -= 0.5f; } else { ch = 0.0f; }

#define DEFAULT_DIALOG_BORDER_WIDTH    7

namespace pdg {

class DialogBackgroundView : public View {
public:
    DialogBackgroundView(Dialog* dialog, const Rect aRect, Color borderColor = PDG_BLACK_COLOR,
                         Color fillColor = PDG_WHITE_COLOR, int borderWidth = DEFAULT_DIALOG_BORDER_WIDTH )
        : View(dialog, aRect),
        mBorderColor(borderColor),
        mFillColor(fillColor),
        mBorderWidth(borderWidth) {
        mViewArea.grow(borderWidth);
        addClickablePart(globalToLocal(mViewArea), PART_DIALOG_BKGRND);
    }

    void drawSelf() {
        mPort->fillRect(mViewArea, mFillColor);
        mPort->frameRectEx(mViewArea, mBorderWidth, Graphics::solidPat, 0, mBorderColor);
        Color ltLnColor = mBorderColor;
        BRIGHTEN(ltLnColor.red);
        BRIGHTEN(ltLnColor.green);
        BRIGHTEN(ltLnColor.blue);
        Color dkLnColor = mBorderColor;
        DARKEN(dkLnColor.red);
        DARKEN(dkLnColor.green);
        DARKEN(dkLnColor.blue);
        // light lines at top and left
        mPort->drawLine(mViewArea.leftTop(), mViewArea.rightTop(), ltLnColor);
        mPort->drawLine(mViewArea.leftTop(), mViewArea.leftBottom(), ltLnColor);
        // dark lines at bottom and right
        mPort->drawLine(mViewArea.leftBottom(), mViewArea.rightBottom(), dkLnColor);
        mPort->drawLine(mViewArea.rightTop(), mViewArea.rightBottom(), dkLnColor);
//        mController->viewRedrawn();
    }

protected:
    Color mBorderColor;
    Color mFillColor;
    int   mBorderWidth;
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
		View* bkgnd = new DialogBackgroundView(this, mDialogRect);
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
    if (view && (id == mOkButtonId) || (id == mCancelButtonId)) {
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
      // TODO: remove these catan specific things
      #if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
		GameController& gc = static_cast<GameController&>(getTopController());
#ifndef PDG_NO_SOUND
		gc.getSound(GameController::SND7_BUTTON_CLICK)->play();
#endif
        mButtonWithMouseDown->setClickState(false);
      #endif
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

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
	// If the water is being shown draw all dialogs over the center otherwise center over just board.
	GameController& gc = static_cast<GameController&>(getTopController());
	if(!gc.isGameBoardAndControlsHidden())
	{
	    long dividerX = (long)(CONTROL_DIVIDER_X * (float)resizedPort->getDrawingArea().width() / 1280.0f);
		topLeft.x = (dividerX - width) / 2;
	    if (topLeft.x < 20) {
	        // offsreen to left, so center on full window
		    topLeft.x = (resizedPort->getDrawingArea().width() - width) / 2;
	    }
	}
	else
#endif // CATAN_SPECIFIC
	{
		topLeft.x = (resizedPort->getDrawingArea().width() - width) / 2;
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
			parent->redraw();
		}
    }
}

// Shows dialog after it was hidden
void Dialog::showDialog()
{
    if (!mViewVisibilitySave) {
        return;     // we never hid this dialog
    }
	bool wasDrawing = startDrawing();

	ViewList::iterator itr;
	int i=0;
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
        View* view = val.first;
		if(mViewVisibilitySave[i++])
		{
			view->show();
		}
	}

	delete [] mViewVisibilitySave;
	mViewVisibilitySave = 0;

	doneDrawing(wasDrawing);
}

// Hides dialog from view but doesn't close it.
void Dialog::hideDialog()
{
	if(mViewVisibilitySave) // Don't hide if we are already hidden, it will overwrite our view visibility array.
	{
		return;
	}
	bool wasDrawing = startDrawing();

	ViewList::iterator itr;
	int i=0;
	mViewVisibilitySave = new bool[mViews.size()];
    CHECK_NEW(mViewVisibilitySave, bool[]);
	for(itr = mViews.begin(); itr != mViews.end(); itr++) {
		idViewPair val = *itr;
        View* view = val.first;
		mViewVisibilitySave[i++] = view->isVisible();
		if(view->isVisible())
		{
			view->hide();
		}
	}

	// Redraw background
	redrawAll();

	doneDrawing(wasDrawing);
}

void Dialog::setDialogRect(const Rect& dialogRect)
{
    // calculate the location of the dialog
    Point topLeft;
    Port* port = getApplication().getGraphicsManager().getMainPort();
    if (port) {

      // TODO: remove these catan specific things
      #if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
		// If the water is being shown draw all dialogs over the center otherwise center over just board.
	    GameController& gc = static_cast<GameController&>(mParentController->getTopController());
		if(!gc.isGameBoardAndControlsHidden())
		{
		    long dividerX = (long)(CONTROL_DIVIDER_X * (float)port->getDrawingArea().width() / 1280.0f);
			topLeft.x = (dividerX - dialogRect.width()) / 2;
		    if (topLeft.x < 20) {
		        // offsreen to left, so center on full window
			    topLeft.x = (port->getDrawingArea().width() - dialogRect.width()) / 2;
		    }
		}
		else
	  #endif // CATAN_SPECIFIC
		{
			topLeft.x = (port->getDrawingArea().width() - dialogRect.width()) / 2;
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
