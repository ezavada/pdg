// -----------------------------------------------
// Button.h
// 
// Definitions for drawing a button
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_BUTTON_H_INCLUDED
#define PDG_BUTTON_H_INCLUDED

#include <string.h>

#include "pdg/framework.h"


namespace pdg {


class View;
//class ToolTipCtrl;

class Button : public View, public Subject
{
public:

    // make button size match rectangle
    Button(Controller* controller, const Rect frame, int buttonID, 
            int resourceTextID = -1, short substring = -1, 
            int styleId = -1);
            
    // make button size match image
    Button(Controller* controller, const Point& topLeftPoint, int buttonID, 
            int resourceTextID = -1, short substring = -1, 
            int styleId = -1);
    
	~Button();

	void setText(const char *);
	void setTextFromResource(int resourceID, short substring);
	void setClickSound(Sound* clickSound);
	void setAttributes(const ControlAttributes& attributes);
	const ControlAttributes& getAttributes() const { return mAttributes; }
	void playClickSound() const { mAttributes.playClick(); }

	void drawSelf() override;
	void drawStandardButtonBackground();
	void setClickState(bool clicked) { mIsButtonPressed = clicked; draw(); }
	bool doMouseDown(const MouseInfo* mi, int id, int part) override;
	bool doMouseUp(const MouseInfo* mi, int id, int part) override;
	bool doLeftClick(const MouseInfo* mi, int id, int part) override;
//    bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled

 	// to display tooltips	
	void showToolTip(int nArea, Point pts,Rect & rToolRect);
	bool IsMouseInToolArea(Point pts,Rect & rToolRect);
	void setToolTipText(std::string sText);
	void doMouseMove(const MouseInfo *mi, int id, int part) override;
	void doMouseLeave(const MouseInfo *mi, int id, int part) override;

private:
    void initializeButton(int resourceTextID, short substring);
    void finishInitButton();
	void updateLayout();
    ResourceManager& mResMgr;
	std::string  mText;
	int mButtonID;
	int mStyleId;
	bool mIsButtonPressed;
	bool mIsHovered;
	ControlAttributes mAttributes;
// for tooltip window
	bool mIsToolTipEnabled;
	//ToolTipCtrl*	mToolTipCtrl;		
	int				nHasChangedAreaHit;
	Point   mTextBaselineCenterPoint;
	int     mButtonTextSize;
};

} // end namespace pdg

#endif // PDG_BUTTON_H_INCLUDED
