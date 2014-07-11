// -----------------------------------------------
// MessageDialog.h
// 
// Definition of a class that manages views,
// keyboard and mouse events for a simple dialog
// that shows a text message
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_MESSAGE_DIALOG_H_INCLUDED
#define PDG_MESSAGE_DIALOG_H_INCLUDED

#include "pdg/app/Dialog.h"

namespace pdg {

class GameController;
class ResourceList;

class MessageDialog : public Dialog {
public:
	enum VIEW_IDS
	{
	    // views
		VIEW_ID_MESSAGE_VIEW  = 1,
		VIEW_ID_BORDER = 2,
		
		// buttons
		// don't add anything but buttons in this section
		VIEW_FIRST_BUTTON_ID,  // add new buttons below this entry
		VIEW_ID_BUTTON_1,
		VIEW_ID_BUTTON_2,
		VIEW_LAST_BUTTON_ID     // add new buttons above this entry
		
	};

	enum BUTTON_TEXT
	{
		NONE,
		OK,
		CANCEL,
		YES,
		NO,
		SAVE,
		LOAD
	};

    MessageDialog(Controller* parentController, std::string& message, BUTTON_TEXT button1 = NONE, BUTTON_TEXT button2 = NONE);
	MessageDialog(Controller* parentController, std::string& message, std::string& buttonText1, std::string& buttonText2);

	int getButtonClickedId(); // Tells which button was clicked VIEW_ID_BUTTON_1 or VIEW_ID_BUTTON_2
	
	int getMessageCode() { return mMessageCode; }
	void setMessageCode(int msgCode) {mMessageCode = msgCode;}

protected:    
    virtual bool doLeftClick(const MouseInfo *mi, View* view, int id, int part);

	void setupDialog(std::string& message, std::string& buttonText1, std::string& buttonText2);
	void getTextForButton(std::string& buttonStr, BUTTON_TEXT button);

    ResourceManager& mResMgr;
	int mButtonClickedId;
	int mMessageCode;
};

} // close namespace pdg

#endif // PDG_MESSAGE_DIALOG_H_INCLUDED


