// -----------------------------------------------
// Button.cpp
// 
// Implementation of a button
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


#include "pdg/sys/os.h"
#include "pdg/app/Button.h"
#include "pdg/app/View.h"
#include "ViewUtils.h"

#include <cmath>

#include "timerids.h"

#ifndef BUTTON_COLOR
   #define BUTTON_COLOR          Color(255, 207, 82)
   #define BUTTON_PRESSED_COLOR  Color(255, 239, 173)
#endif // !defined BUTTON_COLOR

namespace pdg {

const int BUTTON_SIZE_X			 = 90;
const int BUTTON_SIZE_Y			 = 28;
const int BUTTON_TEXT_SIZE       = 14;  // 14 pt lettering on buttons
const int SMALL_BUTTON_TEXT_SIZE = 11;
const int TEXT_V_OFFSET          = 18;
const int SMALL_TEXT_V_OFFSET    = 14;
const int buttonTextStyle = textStyle_Bold + textStyle_Centered;

Button::Button(Controller* controller, const Rect frame, int buttonID, int resourceTextID, short substring, int styleId)
: View(controller, frame),
  mResMgr(controller->getApplication().getResourceManager()), 
  mText(""), 
  mButtonID(buttonID), 
  mStyleId(styleId),
  mIsButtonPressed(false),
  mIsHovered(false),
  mIsToolTipEnabled(false)
{
    initializeButton(resourceTextID, substring);

	finishInitButton();
}

Button::Button(Controller* controller, const Point& topLeftPoint, int buttonID, int resourceTextID, short substring, int styleId)
: View(controller, Rect(topLeftPoint, BUTTON_SIZE_X, BUTTON_SIZE_Y)),
  mResMgr(controller->getApplication().getResourceManager()), 
  mText(""), 
  mButtonID(buttonID), 
  mStyleId(styleId),
  mIsButtonPressed(false),
  mIsHovered(false),
  mIsToolTipEnabled(false)
{
    initializeButton(resourceTextID, substring);

	finishInitButton();
	const ControlStateAttributes& normal = mAttributes.state(ControlState::Normal);
	if (normal.hasImage && normal.image) {
		setViewArea(Rect(topLeftPoint, normal.image->width, normal.image->height));
		updateLayout();
	}
}

void Button::initializeButton(int resourceTextID, short substring) {
	// Set the button text
	if (resourceTextID != -1) 
	{
		setTextFromResource(resourceTextID, substring);	// if substring is -1, it will be 
    }
}

void Button::finishInitButton() {
	mAttributes
		.stateAttributes(ControlState::Normal, Attributes().fillColor(BUTTON_COLOR).lineColor(PDG_BLACK_COLOR).roundedCorners(7.0f))
		.stateAttributes(ControlState::Hovered, Attributes().fillColor(Color(255, 220, 120)).lineColor(PDG_BLACK_COLOR).roundedCorners(7.0f))
		.stateAttributes(ControlState::Pressed, Attributes().fillColor(BUTTON_PRESSED_COLOR).lineColor(PDG_BLACK_COLOR).roundedCorners(7.0f))
		.stateAttributes(ControlState::Disabled, Attributes().fillColor(PDG_GRAY_20_COLOR).lineColor(PDG_GRAY_40_COLOR).roundedCorners(7.0f))
		.stateForeground(ControlState::Normal, PDG_WHITE_COLOR)
		.stateForeground(ControlState::Pressed, PDG_WHITE_COLOR)
		.stateForeground(ControlState::Disabled, PDG_GRAY_30_COLOR);
	mAttributes.merge(mController->getTopController().getControlAttributes(ControlType::Button, mStyleId));
	updateLayout();
}


void Button::updateLayout() {
	// Set clickable part
	removeClickablePart(mButtonID);
	Rect viewArea(mViewArea.width(), mViewArea.height());
	addClickablePart(viewArea, mButtonID);

	mButtonTextSize = mViewArea.height()/2-1;
	mTextBaselineCenterPoint.x = mViewArea.width()/2;
	Font* font = mPort->getCurrentFont(buttonTextStyle);
	const float ascent = font->getFontAscent(mButtonTextSize, buttonTextStyle);
	const float descent = font->getFontDescent(mButtonTextSize, buttonTextStyle);
	// drawText takes a baseline. Center the glyph area, with a one-pixel optical
	// adjustment so button labels do not appear high in their backgrounds.
	mTextBaselineCenterPoint.y = static_cast<int>(std::lround(
		(mViewArea.height() - ascent - descent) * 0.5f + ascent)) + 1;
}

Button::~Button()
{
}

void Button::setClickSound(Sound* clickSound)
{
    mAttributes.clickSound(clickSound);
}

void Button::setAttributes(const ControlAttributes& attributes)
{
	mAttributes.merge(attributes);
}

void Button::setTextFromResource(int resourceID, short substring)
{
    std::string text;
    mResMgr.getString(text, resourceID, substring);
    setText(text.c_str());
}

void Button::setText(const char* text)
{
	if ( text )
	{
		mText = text;
	}
	else
	{
		mText = "";
	}
}

// doClick() no longer exists in new API, using doLeftClick instead
/*void Button::doClick(int part)
{
	if (part == mButtonID)
	{
	  #ifndef PDG_NO_SOUND
		if (mpClickSound) {
		    mpClickSound->play();
	  }
		#endif
		notifyObservers();
	}
}
*/

void Button::drawSelf()
{
	ControlState state = !mIsEnabled ? ControlState::Disabled
		: (mIsButtonPressed ? ControlState::Pressed
			: (mIsHovered ? ControlState::Hovered : ControlState::Normal));
	Rect buttonRect(mViewArea.width(), mViewArea.height());
	mAttributes.draw(*mPort, localToGlobal(buttonRect), state);

	const ControlStateAttributes& stateAttributes = mAttributes.state(state);
	const ControlStateAttributes& normalAttributes = mAttributes.state(ControlState::Normal);
	Color buttonTextColor = stateAttributes.hasForeground
		? stateAttributes.foreground : normalAttributes.foreground;
	if (!mText.empty())
	{
//	    if (mText.length()%2 == 1) {
//	        drawStandardButtonBackground();
//	    } else {
//		}

/*		int buttonTextSize = buttonImage->height/2;
		Point textBaselineCenterPoint( buttonImage->width/2, 0);
		textBaselineCenterPoint.y += buttonImage->height - mPort->getFontHeight(buttonTextSize, buttonTextStyle);
		if (buttonImage->height < mpDefaultButtonImage[BUTTON_PRESSED]->height)
		{
			size = SMALL_BUTTON_TEXT_SIZE;
			textBaselineCenterPoint.y = SMALL_TEXT_V_OFFSET;
		}
		else
		{
			size = BUTTON_TEXT_SIZE;
			textBaselineCenterPoint.y = TEXT_V_OFFSET;
		} */
		// Draw text over button
		mPort->drawText(mText.c_str(), localToGlobal(mTextBaselineCenterPoint), pdg::Attributes().textSize(mButtonTextSize).textStyle(buttonTextStyle).fillColor(buttonTextColor));
	}

	//this->drawClickableParts();
}

bool Button::doMouseDown(const MouseInfo* mi, int id, int part)
{
	(void)mi;
	(void)id;
	if (part != mButtonID || !mIsEnabled) return false;
	setClickState(true);
	return false;
}

bool Button::doMouseUp(const MouseInfo* mi, int id, int part)
{
	(void)mi;
	(void)id;
	(void)part;
	if (mIsButtonPressed) setClickState(false);
	return false;
}

bool Button::doLeftClick(const MouseInfo* mi, int id, int part)
{
	(void)mi;
	(void)id;
	if (part != mButtonID || !mIsEnabled) return false;
	mAttributes.playClick();
	notifyObservers();
	return true;
}

// gray 40
#define BT1_COLOR Color(1.000000f, 0.905882f, 0.678431f) // outermost
#define BT2_COLOR Color(1.000000f, 0.905882f, 0.611765f)
#define BT3_COLOR Color(1.000000f, 0.839216f, 0.419608f) // innermost

#define BB1_COLOR Color(0.223529f, 0.192157f, 0.062745f) // outermost
#define BB2_COLOR Color(0.419608f, 0.321569f, 0.129412f)
#define BB3_COLOR Color(0.807843f, 0.647059f, 0.258824f) // innermost

void Button::drawStandardButtonBackground() 
{
    #define BUTTON_RADIUS 7.0f
    
    Color c[7] = { BT1_COLOR, BT2_COLOR, BT3_COLOR, BB1_COLOR, BB2_COLOR, BB3_COLOR, BUTTON_COLOR };
    
    if ( !mIsEnabled) {
        for (int i = 0; i<7; i++) {
            c[i].convertToGrayscale();
        }
        c[6] = PDG_GRAY_20_COLOR;
    }
    
    Rect r = mViewArea;
    if (mIsButtonPressed) {
        c[6] = BUTTON_PRESSED_COLOR;
    }
    
    mPort->drawRect(r, pdg::Attributes().fillColor(c[6]).roundedCorners(BUTTON_RADIUS));
    Rect clipSave = mPort->getClipRect();
    Rect newClip;
    
    r.bottom -=4;
    newClip = clipSave.intersection(r); // intersect old clip with this new one
    mPort->setClipRect(newClip);
    r.bottom += 4;
    
    mPort->drawRect(r, pdg::Attributes().lineColor(PDG_GRAY_40_COLOR));
    if (!mIsButtonPressed) {
        r.shrink(1);
        mPort->drawRect(r, pdg::Attributes().lineColor(c[0]));
        r.shrink(1);
        mPort->drawRect(r, pdg::Attributes().lineColor(c[1]));
        r.shrink(1);
        mPort->drawRect(r, pdg::Attributes().lineColor(c[2]));
        r.grow(3);
    }
    
    r.top += 5;
    r.left += 5;
    newClip = clipSave.intersection(r); // intersect old clip with this new one
    mPort->setClipRect(newClip);
    r.top -= 5;
    r.left -= 5;

    mPort->drawRect(r, pdg::Attributes().lineColor(PDG_GRAY_70_COLOR));
    r.shrink(1);
    mPort->drawRect(r, pdg::Attributes().lineColor(c[3]));
    mPort->drawRect(r, pdg::Attributes().lineColor(c[3]));
    r.shrink(1);
    mPort->drawRect(r, pdg::Attributes().lineColor(c[4]));
    mPort->drawRect(r, pdg::Attributes().lineColor(c[4]));
    r.shrink(1);
    mPort->drawRect(r, pdg::Attributes().lineColor(c[5]));
    r.grow(3);

    r = mViewArea;
    r.top = r.bottom - 4;
    r.bottom += 1;
    newClip = clipSave.intersection(r);
    mPort->setClipRect(newClip);
    r.top = mViewArea.top;
    r.bottom -= 1;
    
    mPort->drawRect(r, pdg::Attributes().lineColor(PDG_BLACK_COLOR));

    // restore original clip rect
    mPort->setClipRect(clipSave);
}

// handler shows all the tooltips for button
void Button::doMouseMove(const MouseInfo *mi,  int id, int part)
{
	if (!mIsHovered) {
		mIsHovered = true;
		draw();
	}
	if (!mIsToolTipEnabled)
		return ;
	Point mousePts = mi->mousePos;
	Rect rToolRect;
	if (mousePts.x>0 && mousePts.y>0){	// the points are not outside the wnd area
		int nArea = IsMouseInToolArea(mousePts,rToolRect);//IsPointInPlayerNameArea(mousePts);// check if pts lie anywhere in our tooltip area
		if (nArea){
			showToolTip(nArea,mousePts,rToolRect);	// show the tooltip window, if it lies in tool area
			nHasChangedAreaHit = nArea;		// update the last hit
		}else{
			showToolTip(-1,mousePts,rToolRect);
			nHasChangedAreaHit=-1;
		}
	}else{
		showToolTip(-1,mousePts,rToolRect);
		nHasChangedAreaHit =-1;
	}
}

void Button::doMouseLeave(const MouseInfo *mi, int id, int part)
{
	if (mIsHovered) {
		mIsHovered = false;
		draw();
	}
//	showToolTip(-1,mousePts,Rect(0,0,0,0));
}

// find if the mouse point lies any tooltip area
bool Button::IsMouseInToolArea(Point pts,Rect & rToolRect)
{
	Rect viewArea(mViewArea.left+3, mViewArea.top+2, mViewArea.right, mViewArea.bottom-5);
	rToolRect = viewArea;
	return viewArea.contains(pts);
}

// display the tooltip if it lies on any area else hide it
void Button::showToolTip(int nArea, Point pts,Rect & rToolRect)
{
}

void Button::setToolTipText(std::string sText)
{
}

} // namespace pdg
