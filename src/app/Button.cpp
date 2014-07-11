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

#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/sys/os.h"
#include "pdg/app/Button.h"
#include "pdg/app/View.h"

#ifndef PDG_ALLOW_DEPRECATED_CALLS
#error You must define PDG_ALLOW_DEPRECATED_CALLS in your project to use Button.cpp
#endif

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
  #include "ToolTipCtrl.h"
  #include "CatanUIConsts.h"
  #define BUTTON_COLOR           CATAN_BUTTON_COLOR
  #define BUTTON_PRESSED_COLOR   CATAN_BOARD_BKG_COLOR
#endif 

#include "timerids.h"

#ifndef BUTTON_COLOR
   #define BUTTON_COLOR          Color(255, 207, 82)
   #define BUTTON_PRESSED_COLOR  Color(255, 239, 173)
#endif // !defined BUTTON_COLOR

namespace pdg {

const int BUTTON_NOT_PRESSED     = 0;
const int BUTTON_PRESSED         = 1;
const int BUTTON_DISABLED        = 2;

const int BUTTON_SIZE_X			 = 90;
const int BUTTON_SIZE_Y			 = 28;
const int BUTTON_TEXT_SIZE       = 14;  // 14 pt lettering on buttons
const int SMALL_BUTTON_TEXT_SIZE = 11;
const int TEXT_V_OFFSET          = 18;
const int SMALL_TEXT_V_OFFSET    = 14;
const int buttonTextStyle = Graphics::textStyle_Bold + Graphics::textStyle_Centered;

Button::Button(Controller* controller, const Rect frame, int buttonID, int resourceTextID, short substring, int imageID) 
: View(controller, frame),
  mResMgr(controller->getApplication().getResourceManager()), 
  mpClickSound(0),
  mText(""), 
  mButtonID(buttonID), 
  mImagesId(imageID), 
  mIsButtonPressed(false),
  mIsToolTipEnabled(false),
  mToolTipCtrl(0)
{
    initializeButton(resourceTextID, substring);

	// Resize images to fit
	scaleImageArrayToFit(mpButtonImage, MAX_BUTTON_IMAGES, frame);

	finishInitButton();
}

Button::Button(Controller* controller, const Point& topLeftPoint, int buttonID, int resourceTextID, short substring, int imageID) 
: View(controller, Rect(0, 0)),
  mResMgr(controller->getApplication().getResourceManager()), 
  mText(""), 
  mButtonID(buttonID), 
  mImagesId(imageID), 
  mIsButtonPressed(false),
  mIsToolTipEnabled(false),
  mToolTipCtrl(0)
{
    initializeButton(resourceTextID, substring);

	// Reset view area
	if( mpButtonImage[BUTTON_PRESSED])
	{
		int width = mpButtonImage[BUTTON_PRESSED]->width;
		int height = mpButtonImage[BUTTON_PRESSED]->height;
		Rect viewArea(topLeftPoint.x, topLeftPoint.y, topLeftPoint.x + width, topLeftPoint.y + height);
		setViewArea(viewArea);
    }

	finishInitButton();
}

void Button::initializeButton(int resourceTextID, short substring) {
	// If the deafult images haven't been loaded yet....load them...this will only happen once.
	loadDefaultImages();

	// if the user didn't pass in any imageID we will use the default buttons
	// which should be already loaded
	if(mImagesId == RES_DEFAULT_BUTTON_IMAGE)
	{
		loadImageArray(mResMgr, mpButtonImage, RES_DEFAULT_BUTTON_IMAGE, MAX_BUTTON_IMAGES);
	}
	else
	{
		loadImageArray(mResMgr, mpButtonImage, mImagesId, MAX_BUTTON_IMAGES);
	}

	// Set the button text
	if(resourceTextID != -1) 
	{
		setTextFromResource(resourceTextID, substring);	// if substring is -1, it will be 
    }
}

void Button::finishInitButton() {
	// Set clickable part
	Rect viewArea(mViewArea.width(), mViewArea.height());
	addClickablePart(viewArea, mButtonID);

	mButtonTextSize = mViewArea.height()/2-1;
	mTextBaselineCenterPoint.x = mViewArea.width()/2;
	int textHeight = mPort->getCurrentFont(buttonTextStyle)->getFontHeight(mButtonTextSize, buttonTextStyle);
	mTextBaselineCenterPoint.y = textHeight + (mViewArea.height() - textHeight)/4;
}

Button::~Button()
{
    // unload the button images
    unloadImage(mpButtonImage[BUTTON_NOT_PRESSED]);
    unloadImage(mpButtonImage[BUTTON_PRESSED]);
    unloadImage(mpButtonImage[BUTTON_DISABLED]);
    mpClickSound = 0;
}

void Button::loadDefaultImages()
{
}

void Button::setClickSound(Sound* clickSound)
{
    mpClickSound = clickSound;
}

void Button::setTextFromResource(int resourceID, short substring)
{
    std::string text;
    mResMgr.getString(text, resourceID, substring);
    setText(text.c_str());
}

void Button::setText(const char* text)
{
	if( text )
	{
		mText = text;
	}
	else
	{
		mText = "";
	}
}



void Button::drawSelf()
{
	// Draw button image
	Point topLeftPoint( 0, 0 );
	Image* buttonImage = 0;

    Color buttonTextColor;

	if( mIsEnabled )
	{
		buttonTextColor = PDG_WHITE_COLOR;
		if( mIsButtonPressed )
		{
			buttonImage = mpButtonImage[BUTTON_PRESSED];
		}
		else
		{
			buttonImage = mpButtonImage[BUTTON_NOT_PRESSED];
		}
	}
	else
	{
		buttonImage = mpButtonImage[BUTTON_DISABLED];
		buttonTextColor = PDG_GRAY_30_COLOR;	
	}

	if( buttonImage )
	{
//	    if (mText.length()%2 == 1) {
//	        drawStandardButtonBackground();
//	    } else {
		    buttonImage->draw(localToGlobal(topLeftPoint));
//		}

/*		int buttonTextSize = buttonImage->height/2;
		Point textBaselineCenterPoint( buttonImage->width/2, 0);
		textBaselineCenterPoint.y += buttonImage->height - mPort->getFontHeight(buttonTextSize, buttonTextStyle);
		if(buttonImage->height < mpDefaultButtonImage[BUTTON_PRESSED]->height)
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
		mPort->drawText(mText.c_str(), localToGlobal(mTextBaselineCenterPoint), mButtonTextSize, buttonTextStyle, buttonTextColor);
	}

	//this->drawClickableParts();
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
    
    mPort->fillRoundRect(r, BUTTON_RADIUS, c[6]);
    Rect clipSave = mPort->getClipRect();
    Rect newClip;
    
    r.bottom -=4;
    newClip = clipSave.intersection(r); // intersect old clip with this new one
    mPort->setClipRect(newClip);
    r.bottom += 4;
    
    mPort->frameRoundRect(r, BUTTON_RADIUS, PDG_GRAY_40_COLOR);
    if (!mIsButtonPressed) {
        r.shrink(1);
        mPort->frameRoundRect(r, BUTTON_RADIUS, c[0]);
        r.shrink(1);
        mPort->frameRoundRect(r, BUTTON_RADIUS, c[1]);
        r.shrink(1);
        mPort->frameRoundRect(r, BUTTON_RADIUS, c[2]);
        r.grow(3);
    }
    
    r.top += 5;
    r.left += 5;
    newClip = clipSave.intersection(r); // intersect old clip with this new one
    mPort->setClipRect(newClip);
    r.top -= 5;
    r.left -= 5;

    mPort->frameRoundRect(r, BUTTON_RADIUS, PDG_GRAY_70_COLOR);
    r.shrink(1);
    mPort->frameRoundRect(r, BUTTON_RADIUS - 2.0f, c[3]);
    mPort->frameRoundRect(r, BUTTON_RADIUS - 1.0f, c[3]);
    r.shrink(1);
    mPort->frameRoundRect(r, BUTTON_RADIUS - 2.0f, c[4]);
    mPort->frameRoundRect(r, BUTTON_RADIUS - 1.0f, c[4]);
    r.shrink(1);
    mPort->frameRoundRect(r, BUTTON_RADIUS - 2.0f, c[5]);
    r.grow(3);

    r = mViewArea;
    r.top = r.bottom - 4;
    r.bottom += 1;
    newClip = clipSave.intersection(r);
    mPort->setClipRect(newClip);
    r.top = mViewArea.top;
    r.bottom -= 1;
    
    mPort->frameRoundRect(r, BUTTON_RADIUS, PDG_BLACK_COLOR);

    // restore original clip rect
    mPort->setClipRect(clipSave);
}

// handler shows all the tooltips for button
void Button::doMouseMove(const MouseInfo *mi,  int id, int part)
{
	if(!mIsToolTipEnabled)
		return ;
	Point mousePts = mi->mousePos;
	Rect rToolRect;
	if(mousePts.x>0 && mousePts.y>0){	// the points are not outside the wnd area
		int nArea = IsMouseInToolArea(mousePts,rToolRect);//IsPointInPlayerNameArea(mousePts);// check if pts lie anywhere in our tooltip area
		if(nArea){
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
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
	if(nArea > -1 && (nArea != nHasChangedAreaHit)){// mouse area has change, show tooltip with changed text
		// we got a new hit
		if(mToolTipCtrl !=0){
			mToolTipCtrl->show(rToolRect);// display the tooltip
			nHasChangedAreaHit = nArea;
		}
	}else if(nArea==-1){// hit was no where, hide the tooltip window
		if(mToolTipCtrl !=0)
		mToolTipCtrl->hide();
		nHasChangedAreaHit=-1;
	}
#endif
}

void Button::setToolTipText(std::string sText)
{
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
	mIsToolTipEnabled = true;
	nHasChangedAreaHit =-1;
	mToolTipCtrl = new ToolTipCtrl(mController,sText);
	CHECK_NEW(mToolTipCtrl, ToolTipCtrl);
#endif
}

} // namespace pdg
