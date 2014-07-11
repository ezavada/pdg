// -----------------------------------------------
// MessageDialog.cpp
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

#include "pdg/app/MessageDialog.h"
#include "pdg/app/MessageView.h"
#include "pdg/app/Button.h"

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
#include "GameController.h"
#include "CatanDialogBorder.h"
#endif

#define RES_DIALOG_BUTTONS_STR_ID   1101
#define RES_OK_BUTTON               0
#define RES_CANCEL_BUTTON           1
#define RES_DONE_BUTTON             2
#define RES_OFFER_BUTTON            3
#define RES_PLAY_BUTTON             4
#define RES_YES_BUTTON				8
#define RES_NO_BUTTON				9
#define RES_SAVE_BUTTON				10
#define RES_LOAD_BUTTON				11

namespace pdg {

const int BUTTON_V_OFFSET = 15; // Space up from bottom of dialog to bottom of buttons
const int BUTTON_SPACE = 10; // Space in between Play and Cancel buttons
const int BUTTON_SIZE_X = 90;
const int BUTTON_SIZE_Y = 28;

MessageDialog::MessageDialog(Controller *parentController, std::string& message, BUTTON_TEXT button1, BUTTON_TEXT button2)
 : Dialog(parentController, 300, 150, dialog_Centered, VIEW_ID_BUTTON_1, VIEW_ID_BUTTON_2), // creates background
   mResMgr(parentController->getApplication().getResourceManager()),
   mButtonClickedId(-1)
{
	std::string buttonText1;
	std::string buttonText2;
	getTextForButton(buttonText1, button1);
	getTextForButton(buttonText2, button2);

	setupDialog(message, buttonText1, buttonText2);
}

MessageDialog::MessageDialog(Controller *parentController, std::string& message, std::string& buttonText1, std::string& buttonText2)
 : Dialog(parentController, 300, 150, dialog_Centered, VIEW_ID_BUTTON_1, VIEW_ID_BUTTON_2), // creates background
   mResMgr(parentController->getApplication().getResourceManager()),
   mButtonClickedId(-1)
{
	setupDialog(message, buttonText1, buttonText2);
}

void MessageDialog::setupDialog(std::string& message, std::string& buttonText1, std::string& buttonText2)
{
//	int resId = 0;	
//	int resSubId = 0;

	MessageView* messageView = new MessageView(this, getDialogRect(), message);
    addView(messageView, VIEW_ID_MESSAGE_VIEW);

	Rect messageViewArea = messageView->getViewArea();
	int middleX = messageViewArea.width() / 2;
	int middleY = messageViewArea.height() - BUTTON_V_OFFSET - BUTTON_SIZE_Y;
	Point middlePoint(middleX, middleY);

	if(!buttonText1.empty())
	{
		Point button1Point = middlePoint;
		if(!buttonText2.empty())
		{
			// setup for 2 buttons
			button1Point.x -= BUTTON_SIZE_X + BUTTON_SPACE/2;
		}
		else
		{
			// setup for 1 button
			button1Point.x -= BUTTON_SIZE_X/2;
		}
		// create button1
		Button* button1 = new Button(this, messageView->localToGlobal(button1Point), VIEW_ID_BUTTON_1);
		button1->setText(buttonText1.c_str());
		addView(button1, VIEW_ID_BUTTON_1);

		if(!buttonText2.empty())
		{
			Point button2Point = middlePoint;
			button2Point.x += BUTTON_SPACE/2;

			// create button2
			Button* button2 = new Button(this, messageView->localToGlobal(button2Point), VIEW_ID_BUTTON_2);
			button2->setText(buttonText2.c_str());
			addView(button2, VIEW_ID_BUTTON_2);
		}
	}

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
	// Draw Catan Scroll Border around dialog
	CatanDialogBorder* borderView = new CatanDialogBorder(this, getDialogRect());
	addView(borderView, VIEW_ID_BORDER);
#endif

	redraw();
}

void MessageDialog::getTextForButton(std::string& buttonStr, BUTTON_TEXT button)
{
	int resId = -1;
	int resSubId = -1;
	buttonStr = "";
	switch(button)
	{
	case OK:
		resId = RES_DIALOG_BUTTONS_STR_ID;
		resSubId = RES_OK_BUTTON;
		break;
	case CANCEL:
		resId = RES_DIALOG_BUTTONS_STR_ID;
		resSubId = RES_CANCEL_BUTTON;
		break;
	case YES:
		resId = RES_DIALOG_BUTTONS_STR_ID;
		resSubId = RES_YES_BUTTON;
		break;
	case NO:
		resId = RES_DIALOG_BUTTONS_STR_ID;
		resSubId = RES_NO_BUTTON;
		break;
	case SAVE:
		resId = RES_DIALOG_BUTTONS_STR_ID;
		resSubId = RES_SAVE_BUTTON;
		break;
	case LOAD:
		resId = RES_DIALOG_BUTTONS_STR_ID;
		resSubId = RES_LOAD_BUTTON;
		break;
	case NONE:
	default:
		resId = -1;
		resSubId = -1;
		break;
	}

	if(resId != -1 && resSubId != -1)
	{
		mResMgr.getString(buttonStr, resId, resSubId);
	}
}


bool MessageDialog::doLeftClick(const MouseInfo *mi, View* view, int id, int part) {
	if( id == VIEW_ID_MESSAGE_VIEW )
	{	
	}
	else if( id == VIEW_ID_BUTTON_1 )
	{
		mButtonClickedId = VIEW_ID_BUTTON_1;
	    Dialog::doLeftClick(mi, view, id, part);
        // WARNING: don't do anything after calling Dialog::doLeftClick, it can delete the object
	}
	else if( id == VIEW_ID_BUTTON_2 )
	{
		mButtonClickedId = VIEW_ID_BUTTON_2;
	    Dialog::doLeftClick(mi, view, id, part);
        // WARNING: don't do anything after calling Dialog::doLeftClick, it can delete the object
	}
	else {
	    return Dialog::doLeftClick(mi, view, id, part);
        // WARNING: don't do anything after calling Dialog::doLeftClick, it can delete the object
	}
	return true;
}

} // namespace pdg
