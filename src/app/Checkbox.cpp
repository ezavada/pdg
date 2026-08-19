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
#include "pdg/sys/attributes.h"
#include "ViewUtils.h"

#include <algorithm>
#include <cmath>


namespace pdg {

const int CHECKBOX_TEXT_SIZE = 16;
const int SPACE_BETWEEN_BOX_AND_TEXT = 5;
const int SPACE_UP_FROM_BOTTOM = 5;
const Style checkboxTextStyle = textStyle_Bold;

Checkbox::Checkbox(Controller* controller, const Rect& viewArea) :
	View(controller, viewArea),
	mIsChecked(false),
	mString(""),
	mTextSize(CHECKBOX_TEXT_SIZE)
{
	mAttributes
		.stateForeground(ControlState::Normal, PDG_BLACK_COLOR)
		.stateForeground(ControlState::Selected, PDG_BLACK_COLOR)
		.stateForeground(ControlState::Disabled, PDG_GRAY_30_COLOR)
		.stateForeground(ControlState::SelectedDisabled, PDG_GRAY_30_COLOR);
	mAttributes.merge(mController->getTopController().getControlAttributes(ControlType::Checkbox));
	calcClickableAreas();
}

Checkbox::~Checkbox()
{
}
	
void Checkbox::setClickSound(Sound* clickSound)
{
    mAttributes.clickSound(clickSound);
}

void Checkbox::setAttributes(const ControlAttributes& attributes)
{
	mAttributes.merge(attributes);
	calcClickableAreas();
}

void Checkbox::calcClickableAreas()
{
	removeClickablePart(CLICK_ID_CHECKBOX);
	Rect clickArea(mViewArea.width(), mViewArea.height());
	addClickablePart(clickArea, CLICK_ID_CHECKBOX);
}

void Checkbox::drawSelf()
{
	ControlState state = isChecked()
		? (mIsEnabled ? ControlState::Selected : ControlState::SelectedDisabled)
		: (mIsEnabled ? ControlState::Normal : ControlState::Disabled);
	const ControlStateAttributes& visual = mAttributes.state(state);
	const ControlStateAttributes& normal = mAttributes.state(ControlState::Normal);
	Image* image = visual.hasImage ? visual.image : normal.image;
	Font* font = mPort->getCurrentFont(checkboxTextStyle);
	const float ascent = font->getFontAscent(mTextSize, checkboxTextStyle);
	const float descent = font->getFontDescent(mTextSize, checkboxTextStyle);
	const float glyphHeight = ascent + descent;
	const int baseline = static_cast<int>(std::lround(
		(mViewArea.height() - glyphHeight) * 0.5f + ascent));
	const int defaultBoxSize = std::max(1, static_cast<int>(std::lround(ascent)));
	int boxWidth = image ? image->width : defaultBoxSize;
	int boxHeight = image ? image->height : defaultBoxSize;
	Point checkPt(0, image ? (mViewArea.height() - boxHeight) / 2 : baseline - boxHeight);
	Rect checkRect(checkPt, boxWidth, boxHeight);
	mAttributes.draw(*mPort, localToGlobal(checkRect), state);
	if (!image && !visual.hasDrawing && !visual.hasDrawRoutine) {
		Color markColor = visual.hasForeground ? visual.foreground : normal.foreground;
		Rect globalCheckRect = localToGlobal(checkRect);
		mPort->drawRect(globalCheckRect, Attributes().fillColor(PDG_WHITE_COLOR)
			.lineColor(markColor).lineThickness(1.0f));
		if (isChecked()) {
			const Point left(globalCheckRect.left + boxWidth * 0.20f,
				globalCheckRect.top + boxHeight * 0.52f);
			const Point middle(globalCheckRect.left + boxWidth * 0.43f,
				globalCheckRect.top + boxHeight * 0.76f);
			const Point right(globalCheckRect.left + boxWidth * 0.82f,
				globalCheckRect.top + boxHeight * 0.25f);
			mPort->drawLine(left, middle, Attributes().lineColor(markColor).lineThickness(2.0f));
			mPort->drawLine(middle, right, Attributes().lineColor(markColor).lineThickness(2.0f));
		}
	}

	Point textPt(0, 0);
	// Draw Text if there is any
	if (!mString.empty())
	{
		textPt.x = boxWidth + SPACE_BETWEEN_BOX_AND_TEXT;
		textPt.y = baseline;
		Color textColor = visual.hasForeground ? visual.foreground : normal.foreground;
		mPort->drawText(mString.c_str(), localToGlobal(textPt), Attributes().textSize(mTextSize).textStyle(checkboxTextStyle).fillColor(textColor));
	}
	//this->drawClickableParts();
}

void Checkbox::doClick(int part)
{
	if (part == CLICK_ID_CHECKBOX)
	{
		mIsChecked = !mIsChecked;
		mAttributes.playClick();
		notifyObservers();
	}
}

bool Checkbox::doLeftClick(const MouseInfo* mi, int id, int part)
{
	(void)mi;
	(void)id;
	if (!mIsEnabled || part != CLICK_ID_CHECKBOX) return false;
	doClick(part);
	draw();
	return true;
}

void Checkbox::setString(const std::string& str) 
{ 
	mString = str; 
	int textWidth = mPort->getTextWidth(mString.c_str(), mTextSize, checkboxTextStyle);
	Rect newClickArea(mViewArea);
	Image* image = mAttributes.state(ControlState::Normal).image;
	Font* font = mPort->getCurrentFont(checkboxTextStyle);
	int defaultBoxSize = std::max(1, static_cast<int>(std::lround(
		font->getFontAscent(mTextSize, checkboxTextStyle))));
	int boxWidth = image ? image->width : defaultBoxSize;
	int boxHeight = image ? image->height : defaultBoxSize;
	int fontHeight = static_cast<int>(std::ceil(
		font->getFontAscent(mTextSize, checkboxTextStyle) +
		font->getFontDescent(mTextSize, checkboxTextStyle)));
	newClickArea.bottom = newClickArea.top + std::max(boxHeight, fontHeight + SPACE_UP_FROM_BOTTOM);
	newClickArea.right = newClickArea.left + boxWidth;
	newClickArea.right += SPACE_BETWEEN_BOX_AND_TEXT + textWidth;
	setViewArea(newClickArea);
	//remove and re-add clickable part
	removeClickablePart(CLICK_ID_CHECKBOX);
	newClickArea = newClickArea - newClickArea.leftTop();
	addClickablePart(newClickArea, CLICK_ID_CHECKBOX);
}

} // close namespace pdg
