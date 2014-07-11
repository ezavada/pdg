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
class ToolTipCtrl;

const int MAX_BUTTON_IMAGES = 3;
#define RES_DEFAULT_BUTTON_IMAGE	103

class Button : public View
{
public:

    // make button size match rectangle
    Button(Controller* controller, const Rect frame, int buttonID, 
            int resourceTextID = -1, short substring = -1, 
            int imageID = RES_DEFAULT_BUTTON_IMAGE);
            
    // make button size match image
    Button(Controller* controller, const Point& topLeftPoint, int buttonID, 
            int resourceTextID = -1, short substring = -1, 
            int imageID = RES_DEFAULT_BUTTON_IMAGE);
    
	~Button();

	void setText(const char *);
	void setTextFromResource(int resourceID, short substring);
	void setClickSound(Sound* clickSound);

	void loadImages();
	void loadDefaultImages();
	void drawSelf();
	void drawStandardButtonBackground();
	void setClickState(bool clicked) { mIsButtonPressed = clicked; draw(); }
//    bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled

 	// to display tooltips	
	void showToolTip(int nArea, Point pts,Rect & rToolRect);
	bool IsMouseInToolArea(Point pts,Rect & rToolRect);
	void setToolTipText(std::string sText);
	void doMouseMove(const MouseInfo *mi, int id, int part);  // override to do something when made visible
	void doMouseLeave(const MouseInfo *mi, int id, int part);

private:
    void initializeButton(int resourceTextID, short substring);
    void finishInitButton();
    ResourceManager& mResMgr;
	Image*  mpButtonImage[MAX_BUTTON_IMAGES];
	Sound* mpClickSound;
	std::string  mText;
	int mButtonID;
	int mImagesId;
	bool mIsButtonPressed;
// for tooltip window
	bool mIsToolTipEnabled;
	ToolTipCtrl*	mToolTipCtrl;		
	int				nHasChangedAreaHit;
	Point   mTextBaselineCenterPoint;
	int     mButtonTextSize;
};

} // end namespace pdg

#endif // PDG_BUTTON_H_INCLUDED

