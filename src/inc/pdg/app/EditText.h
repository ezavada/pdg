// -----------------------------------------------
// EditText.h
// 
// Definitions for drawing a edit view
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_EDITTEXT_H_INCLUDED
#define PDG_EDITTEXT_H_INCLUDED

#include "pdg/framework.h"
#include <string>

#define LEFT_MARGIN			3
#define RIGHT_MARGIN		3
#define TEXT_HEIGHT_OFFSET	4

namespace pdg {

class EditText : public RefCountedImpl<IEventHandler>, public View
{
public:
	enum ClickIDs
	{
		CLICK_ID_EDITBOXVIEW	= 1002
	};
private:

    ResourceManager& mResMgr;
	Color mbkColor;
	Color mTextColor;	
	int mFontSize;
	Graphics::Style mStyle;
	bool mbShowCaret;
	bool mbHasFocus;
//	bool mbIsDragging;
	utf16string mText;
	utf16string mAllowedKeys;
	utf16string mBlockedKeys;
	int caretPos;
	Point highlightStartPoint;
	Point highlightEndPoint;
	int highlightStartCharIndex;
	int highlightEndCharIndex;
public:

	EditText(Controller* controller, Rect viewArea, int resourceID, int fontSize = 10,
	            Color bkColor = Color(0xFF,0xFF,0xFF), Color sTextColor = Color(0x00,0x00,0x00), 
	            Graphics::Style textStyle = (Graphics::Style)(Graphics::textStyle_Plain + Graphics::textStyle_LeftJustified));
	~EditText();
	void drawSelf();     
	void getText(std::string& outString);
	void setFilter(const char* allowedKeys, const char* blockedKeys);
	void setBufMax(uint16 maxChars) { mMaxChars = maxChars; }
	uint16 getBufMax() { return mMaxChars; }
	bool doKeyPress(const KeyPressInfo* ki, View* view, int id, int part);
	bool hasFocus(){return mbHasFocus;}
	void setFocus(bool bFocus = true);	
	void setText(const char *text);
	void selectAll();
	void doMouseMove(const MouseInfo *mi, int id, int part);
	bool doMouseDown(const MouseInfo *mi, int id, int part) ;
	bool doMouseUp(const MouseInfo *mi, int id, int part) ;
	bool doDoubleClick(const MouseInfo *mi, int id, int part, int clickCount);
protected:
	EventManager& mEventMgr;
    TimerManager& mTimerMgr;
	pdg::log mLogMgr;
	
	uint16	mMaxChars;	// The max number of characters to accept in this edit control

	void loadString(std::string& aString,int resourceID, int numStrings);
	void drawBorder();	
	bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled
	void drawCaret();
	bool canFitInDisplayArea(const KeyPressInfo* ki);
};

} // close namespace pdg

#endif // PDG_EDITTEXT_H_INCLUDED

