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
#include "pdg/sys/attributes.h"
#include "ViewUtils.h"

namespace pdg {

const int RADIO_TEXT_SIZE = 14;

RadioButton::RadioButton(Controller* controller, const Rect& viewArea, int resourceTextID, int numStrings)
: View(controller, viewArea),
	mResMgr(controller->getApplication().getResourceManager()),
	mSelectedIndex(0), mMaxStrings(numStrings)
{
	mStrings = new std::string[numStrings];
	mAttributes
		.stateForeground(ControlState::Normal, PDG_BLACK_COLOR)
		.stateForeground(ControlState::Selected, PDG_BLACK_COLOR)
		.stateForeground(ControlState::Disabled, PDG_GRAY_30_COLOR)
		.stateForeground(ControlState::SelectedDisabled, PDG_GRAY_30_COLOR);
	mAttributes.merge(mController->getTopController().getControlAttributes(ControlType::RadioButton));
	loadStrings(resourceTextID, numStrings);
	calcClickableAreas();
}

RadioButton::~RadioButton()
{
	delete [] mStrings;
}

void RadioButton::setAttributes(const ControlAttributes& attributes)
{
	mAttributes.merge(attributes);
}

void RadioButton::loadStrings(int resourceID, int numStrings)
{
	if (resourceID < 0) return;
	std::string aString;
	for(int i=0; i < numStrings; i++)
	{
		mResMgr.getString(aString, resourceID, i);
		mStrings[i] = aString;
	}
}

void RadioButton::setString(int index, const std::string& value)
{
	if (index >= 0 && index < mMaxStrings) mStrings[index] = value;
}

void RadioButton::calcClickableAreas()
{
	for (int i = 0; i < mMaxStrings; ++i) removeClickablePart(i);
	int buttonSpace = mViewArea.width() / mMaxStrings;
	Point buttonTLPoint(0,0);
	Point buttonBRPoint(buttonSpace-1, mViewArea.height());
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
		bool selected = i == mSelectedIndex;
		ControlState state = selected
			? (mIsEnabled ? ControlState::Selected : ControlState::SelectedDisabled)
			: (mIsEnabled ? ControlState::Normal : ControlState::Disabled);
		const ControlStateAttributes& visual = mAttributes.state(state);
		const ControlStateAttributes& normal = mAttributes.state(ControlState::Normal);
		Image* image = visual.hasImage ? visual.image : normal.image;
		int imageWidth = image ? image->width : 0;
		int imageHeight = image ? image->height : RADIO_TEXT_SIZE;
		Point imagePoint(buttonPoint.x, (mViewArea.height() - imageHeight) / 2);
		Rect imageRect(imagePoint, imageWidth, imageHeight);
		mAttributes.draw(*mPort, localToGlobal(imageRect), state);
		Color textColor = visual.hasForeground ? visual.foreground : normal.foreground;
		if (!image) {
			Point center = localToGlobal(Point(imagePoint.x + 7, imagePoint.y + 7));
			mPort->drawCircle(center, 7, Attributes().fillColor(PDG_WHITE_COLOR).lineColor(textColor));
			if (selected) mPort->drawCircle(center, 3, Attributes().fillColor(textColor));
			imageWidth = 14;
		}
		textPoint.x += imageWidth + 5;
		textPoint.y += (mViewArea.height() - fontHeight) / 2 + fontHeight;
		mPort->drawText(mStrings[i].c_str(), localToGlobal(textPoint), Attributes().textSize(RADIO_TEXT_SIZE).fillColor(textColor));
		buttonPoint.x += buttonSpace;
	}

	//this->drawClickableParts();
}

bool RadioButton::doLeftClick(const MouseInfo* mi, int id, int part)
{
	(void)mi;
	(void)id;
	if (!mIsEnabled || part < 0 || part >= mMaxStrings) return false;
	doClick(part);
	draw();
	return true;
}

void RadioButton::doClick(int part)
{
	if (part >= 0 && part < mMaxStrings)
	{
		mSelectedIndex = part;
		mAttributes.playClick();
		notifyObservers();
	}
}

} // namespace pdg
