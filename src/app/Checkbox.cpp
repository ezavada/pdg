// -----------------------------------------------
// Checkbox.cpp
// 
// Implementation for drawing a checkbox
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

#include "pdg/app/Checkbox.h"

#ifndef PDG_ALLOW_DEPRECATED_CALLS
#error You must define PDG_ALLOW_DEPRECATED_CALLS in your project to use Checkbox.cpp
#endif


namespace pdg {

const int RES_CHECKBOX_IMAGES = 127;

const int OPEN_CHECKBOX_OFFSET_Y = 8;
const int OPEN_CHECKBOX_WIDTH  = 19;
const int OPEN_CHECKBOX_HEIGHT = 19;
const int CHECKBOX_TEXT_SIZE = 16;
const int SPACE_BETWEEN_BOX_AND_TEXT = -3;
const int SPACE_UP_FROM_BOTTOM = 5;
const Graphics::Style checkboxTextStyle = Graphics::textStyle_Bold;

Checkbox::Checkbox(Controller* controller, const Rect& viewArea) :
	View(controller, viewArea),
	mResMgr(controller->getApplication().getResourceManager()),
	mpClickSound(0),
	mIsChecked(false),
	mString(""),
	mTextSize(CHECKBOX_TEXT_SIZE)
{
	loadImages();
	calcClickableAreas();
}

Checkbox::~Checkbox()
{
	unloadImageArray(mpCheckboxImages, NUM_CHECKBOX_IMAGES);
    mpClickSound = 0;
}


void Checkbox::loadImages()
{
	loadImageArray(mResMgr, mpCheckboxImages, RES_CHECKBOX_IMAGES, NUM_CHECKBOX_IMAGES);
}
	
void Checkbox::setClickSound(Sound* clickSound)
{
    mpClickSound = clickSound;
}

void Checkbox::calcClickableAreas()
{
	if(mpCheckboxImages[OPEN])
	{
		Rect clickArea(OPEN_CHECKBOX_WIDTH, OPEN_CHECKBOX_HEIGHT);
		clickArea = clickArea + Point(0, OPEN_CHECKBOX_OFFSET_Y);
		addClickablePart(clickArea, CLICK_ID_CHECKBOX);
	}
}

void Checkbox::drawSelf()
{
	Point checkPt(0,0);

	if(isChecked())
	{
		if(mpCheckboxImages[CLOSED])
		{
			mpCheckboxImages[CLOSED]->draw(localToGlobal(checkPt));
		}
	}
	else
	{
		if(mpCheckboxImages[OPEN])
		{
			mpCheckboxImages[OPEN]->draw(localToGlobal(checkPt));
		}
	}

	Point textPt(0, 0);
	// Draw Text if there is any
	if(!mString.empty())
	{
		if(mpCheckboxImages[OPEN])
		{
			textPt.x += mpCheckboxImages[OPEN]->width + SPACE_BETWEEN_BOX_AND_TEXT;
			textPt.y += mpCheckboxImages[OPEN]->height - SPACE_UP_FROM_BOTTOM;
		}

		mPort->drawText(mString.c_str(), localToGlobal(textPt), mTextSize, checkboxTextStyle);
	}
	//this->drawClickableParts();
}

void Checkbox::doClick(int part)
{
	if(part == CLICK_ID_CHECKBOX)
	{
		mIsChecked = !mIsChecked;
#ifndef PDG_NO_SOUND
		if (mpClickSound) {
		    mpClickSound->play();
		}
#endif
//		GameController& gc = static_cast<GameController&>(mController->getTopController());
//		gc.getSound(GameController::SND7_BUTTON_CLICK)->play();
		mController->redraw();
	}
}

void Checkbox::setString(const std::string& str) 
{ 
	mString = str; 
	int textWidth = mPort->getTextWidth(mString.c_str(), mTextSize, checkboxTextStyle);
	Rect newClickArea(mViewArea);
	if(mpCheckboxImages[OPEN])
	{
		newClickArea.bottom = newClickArea.top + mpCheckboxImages[OPEN]->height;
		newClickArea.right = newClickArea.left + mpCheckboxImages[OPEN]->width;
	}
	newClickArea.right += SPACE_BETWEEN_BOX_AND_TEXT + textWidth;
	setViewArea(newClickArea);
	//remove and re-add clickable part
	removeClickablePart(CLICK_ID_CHECKBOX);
	newClickArea = newClickArea - newClickArea.leftTop();
	addClickablePart(newClickArea, CLICK_ID_CHECKBOX);
}

} // close namespace pdg
