// -----------------------------------------------
// Dialog.h
// 
// Definition of a class that manages views and
// handles keyboard and mouse events in a dialog
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_DIALOG_H_INCLUDED
#define PDG_DIALOG_H_INCLUDED

#include "pdg/app/Controller.h"


namespace pdg {


class Button;

// A Dialog expects to only have two buttons, ok and cancel, although they can be named however
// you want. The cancel button is not required, but if it is provided it will have a key 
// equivalent of <esc>. The <enter> key always acts as an ok button. Both OK and Cancel will call
// the doClose() method, which will dismiss the dialog.
//
// When creating a Dialog, a background view of the width and height desired specified 
// will be created and automatically added to the Controller. If the center parameter is set, the
// dialog will be centered on the screen, otherwise it will be in the dialog position (centered
// horizontally, and about 2/3 of the way up the screen vertically).
//
// You will need to create and add all of the dialog's Views yourself, including the okay and
// cancel Buttons, and add them to the dialog using addView(). 
//
// For drawing in the Dialog, you should use the View::localToGlobal() so that you can write code
// that deals with 0,0 as the top left of the dialog's view area. Likewise, for click handling
// and such you should use View::globalToLocal() to go from screen coordinates to the dialog
// relative coordinates.
//
// Typically, you would override the parent Controller's attemptChildClose() to do behavior specific 
// to your dialog, such as get result info. You can also override the doClose() method for the same
// reason, but you must call the base class though so the dialog will be correctly dismissed. 
// You can return false from attemptChildClose (or skip calling the base class) if you weren't ready to
// close, for example if the user hasn't filled in all the required info.
//
// If you need more than two buttons, override the doMouseDown method to check for the additional
// button ids, set their Views to the clicked state, and set mButtonWithMouseDown to the button
// in question. See Dialog::doMouseDown for an example

class Dialog : public Controller {
public:

    enum {
        kCancelled = true,
        kAccepted = false
    };
    
    enum {
        dialog_Centered             = (1 << 0),
        dialog_CreateBackground     = (1 << 1),
        dialog_ReservedFlag         = (1 << 2),
        dialog_NonModal             = (1 << 3),
        dialog_Standard             = (dialog_Centered | dialog_CreateBackground)
    };
  
    Dialog(Controller* parentController, int width, int height, uint32 flags, int okButtonId, int cancelButtonId = -1);
    virtual ~Dialog();

	virtual bool doMouseDown(const MouseInfo *mi, View* view, int id, int part);
	virtual bool doMouseUp(const MouseInfo *mi, View* view, int id, int part);

    virtual bool doLeftClick(const MouseInfo *mi, View* view, int id, int part);
    
    // following return true if handled
    virtual bool doKeyPress(const KeyPressInfo* ki, View* view, int id, int part);
    
    // recenter if our port was resized
    virtual void portWasResized(Port* resizedPort);
    
    virtual void doClose(bool cancelled);

	// Shows dialog after it was hidden
	void showDialog();
	// Hides dialog from view but doesn't close it.
	void hideDialog();
	// Returns true if the dialog is not hidden.
	bool isVisible() { return (mViewVisibilitySave == 0); } 
	// Sets the position and size of the dialog
	void setDialogRect(const Rect& dialogRect);
	// Gets the position and size of the dialog
	const Rect& getDialogRect() { return mDialogRect; }

    
protected:
 
	Button*     mButtonWithMouseDown;
	int         mOkButtonId;
	int         mCancelButtonId;
	uint32      mFlags;
	bool*       mViewVisibilitySave;
	Controller* mParentController;

private:

	Rect        mDialogRect;
};

} // end namespace pdg


#endif // PDG_DIALOG_H_INCLUDED


