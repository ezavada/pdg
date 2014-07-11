// -----------------------------------------------
// RadioButton.cpp
// 
// Implementation for drawing a RadioButton
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

#include "pdg/app/RadioButton.h"
#include "pdg/app/Controller.h"

#ifndef PDG_ALLOW_DEPRECATED_CALLS
#error You must define PDG_ALLOW_DEPRECATED_CALLS in your project to use RadioButton.cpp
#endif

namespace pdg {

const int RES_RADIO_IMAGES = 136;

const int RADIO_OPEN = 0;
const int RADIO_CLOSED = 1;

const int RADIO_TEXT_SIZE = 14;

RadioButton::RadioButton(Controller* controller, const Rect& viewArea, int resourceTextID, int numStrings)
: View(controller, viewArea),
	mResMgr(controller->getApplication().getResourceManager()),
	mSelectedIndex(0), mMaxStrings(numStrings)
{
	mStrings = new std::string[numStrings];
	loadImages();
	loadStrings(resourceTextID, numStrings);
	calcClickableAreas();
}

RadioButton::~RadioButton()
{
	delete [] mStrings;
}

void RadioButton::loadImages()
{
	loadImageArray(mResMgr, mpRadioImages, RES_RADIO_IMAGES, MAX_RADIO_IMAGES);
}

void RadioButton::loadStrings(int resourceID, int numStrings)
{
	std::string aString;
	for(int i=0; i < numStrings; i++)
	{
		mResMgr.getString(aString, resourceID, i);
		mStrings[i] = aString;
	}
}

void RadioButton::calcClickableAreas()
{
	int buttonSpace = mViewArea.width() / mMaxStrings;
	int fontHeight = mPort->getCurrentFont()->getFontHeight(RADIO_TEXT_SIZE);
	Point buttonTLPoint(0,0);
	Point buttonBRPoint(buttonSpace-1, fontHeight);
	for(int i=0; i < mMaxStrings; i++)
	{
		Rect clickArea(buttonTLPoint, buttonBRPoint);
		this->addClickablePart(clickArea, i);
		buttonTLPoint.x += buttonSpace;
		buttonBRPoint.x += buttonSpace;
	}
}

void RadioButton::drawSelf()
{
	int buttonSpace = mViewArea.width() / mMaxStrings;
	Point buttonPoint(0,0);
	Point textPoint(0,0);
	int fontHeight = mPort->getCurrentFont()->getFontHeight(RADIO_TEXT_SIZE);

	for(int i=0; i < mMaxStrings; i++)
	{
		textPoint = buttonPoint;
		Point imagePoint = buttonPoint;
		if( i == mSelectedIndex )
		{
			if(mpRadioImages[RADIO_CLOSED])
			{
				imagePoint.y += (mViewArea.height() - mpRadioImages[RADIO_CLOSED]->height)/2;
				mpRadioImages[RADIO_CLOSED]->draw(localToGlobal(imagePoint));
				textPoint.x += mpRadioImages[RADIO_CLOSED]->width + 5;
				textPoint.y += fontHeight;
			}
		}
		else
		{
			if(mpRadioImages[RADIO_OPEN])
			{
				imagePoint.y += (mViewArea.height() - mpRadioImages[RADIO_OPEN]->height)/2;
				mpRadioImages[RADIO_OPEN]->draw(localToGlobal(imagePoint));
				textPoint.x += mpRadioImages[RADIO_OPEN]->width + 5;
				textPoint.y += fontHeight;
			}
		}

		mPort->drawText(mStrings[i].c_str(), localToGlobal(textPoint), RADIO_TEXT_SIZE);
		buttonPoint.x += buttonSpace;
	}

	//this->drawClickableParts();
}

void RadioButton::doClick(int part)
{
	if(part >= 0 && part < mMaxStrings)
	{
		mSelectedIndex = part;
	}
}

} // namespace pdg

