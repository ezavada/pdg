// -----------------------------------------------
// ListBox.cpp
// 
// Implementation for drawing a ListBox
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
#include "pdg/sys/os.h"   // for MAKE_STRING_BUFFER_SAFE

#include "pdg/app/ListBox.h"
#include "pdg/app/Scrollbar.h"
#include "pdg/app/Controller.h"

namespace pdg {

const int DESC_TEXT_SIZE = 12;
const int DESC_TEXT_DECENT = 3;
const Rect PROMPT_AREA_OFFSET(10, 5, -20, -5);  // x,y
const int HEADER_TEXT_SIZE = 18;            // FIXME: Hardcoded sizes
const char * CMD_BREAK2 = "@break";

#define RIGHT_MARGIN 4 
#define CLIP_TEXT "..."

ListBox::ListBox(Controller* controller, const Rect& viewArea, int textLines, const Color& bkcolor, const Color& htcolor)
: View(controller, viewArea),
	mResMgr(controller->getApplication().getResourceManager()),
	mParentController(controller),
	mSelectedIndex(NO_SELECTION), 
	mScrollbar(0),
	mWindowTopLineIndex(0),
	mVisibleTextLines(textLines),
	mHtColor(htcolor),
	mBkColor(bkcolor)
{
	loadImages();
	calcClickableAreas();
}

ListBox::~ListBox()
{
    // clean up all the memory used for the list
    while (mListText.size() > 0) {
        ListBoxLine textLine = mListText.back();
        mListText.pop_back();
        std::free(textLine.text);
    }
}

void ListBox::loadImages()
{
}

void ListBox::calcClickableAreas()
{
	// Reset the view area to the number of visible lines.
	Rect newViewArea(mViewArea.width(), mViewArea.height());
    Graphics::Style style = Graphics::textStyle_Plain;
	int voffset = mPort->getCurrentFont(style)->getFontHeight(DESC_TEXT_SIZE, style) + 
					mPort->getCurrentFont(style)->getFontLeading(DESC_TEXT_SIZE, style);
	newViewArea.bottom = voffset * mVisibleTextLines + 1;
	this->setViewArea(localToGlobal(newViewArea));

	// Create Scrollbar
	Rect scrollbarArea(mViewArea.width() - 16, 1, mViewArea.width(), mViewArea.height());
	mScrollbar = new Scrollbar(mController, localToGlobal(scrollbarArea), Scrollbar::VERTICAL, 0, mVisibleTextLines, 1);
	mParentController->addView(mScrollbar, ListBox::VIEW_ID_LIST_BOX_SCROLLBAR);

	// The ListBox will observe the scrollbar for changes.
	mScrollbar->addObserver(this);

	// Add clickable parts for selecting each line
	Point TLPoint(1, 1);
	Point BRPoint(mViewArea.width() - 17, 1+voffset);
	Rect clickArea(TLPoint, BRPoint);
	for(int i=0; i < mVisibleTextLines; i++)
	{
		addClickablePart(clickArea, VIEW_ID_SELECTION_START + i);
		clickArea.top += voffset;
		clickArea.bottom += voffset;
	}

}

void ListBox::drawSelf()
{

	// Erase old text
	Rect boxRect = Rect(mViewArea.width(), mViewArea.height());
	mPort->frameRect(localToGlobal(boxRect), PDG_BLACK_COLOR);
	boxRect.left +=1;
	boxRect.top +=1;
	boxRect.right -=0;
	boxRect.bottom -=0;
    mPort->fillRect(localToGlobal(boxRect), mBkColor);

	// draw scroll bar
	mScrollbar->draw();

    Graphics::Style style = Graphics::textStyle_Plain;
	int voffset = mPort->getCurrentFont(style)->getFontHeight(DESC_TEXT_SIZE, style) + 
					mPort->getCurrentFont(style)->getFontLeading(DESC_TEXT_SIZE, style);
	Point textPoint = Point(1, voffset-2);
	bool firstTime = true;

	std::vector<ListBoxLine>::iterator itr;
	int numLines = 0;
	for(itr = mListText.begin() + mWindowTopLineIndex; 
		itr != mListText.end() && numLines < mVisibleTextLines; 
		itr++, numLines++)
	{
		ListBoxLine& textLine = *itr;

		if (textLine.text) 
		{
		    if (textLine.text[0] == '@')
    		{
    			std::string command = CMD_BREAK2;
    			if (command == textLine.text)
    			{
    				if(!firstTime)
    				{
    					textPoint.y += 4;
    				}
    				else
    				{
    					firstTime = false;
    				}
    			}
    		}
    		else
    		{
    			Rect textRect(textPoint.x, textPoint.y - voffset + DESC_TEXT_DECENT, mViewArea.width() - 16, textPoint.y + DESC_TEXT_DECENT);
    			mPort->fillRect(localToGlobal(textRect), textLine.bgcolor);
    			Point textTextPoint = textPoint;
    			textTextPoint.x += 5; 
    			// clip text if exceeds view area
    			int fontWidth = mPort->getTextWidth(textLine.text,DESC_TEXT_SIZE,style,std::strlen(textLine.text));
    			
    			int scrollbarWidth = 0;
    			if(mScrollbar)
    				scrollbarWidth = mScrollbar->getViewArea().width();

    			if (fontWidth > mViewArea.width())
    			{
    				int clipTextWidth = mPort->getTextWidth(CLIP_TEXT,DESC_TEXT_SIZE,style);
    				int drawableTextWidth = mViewArea.width() - clipTextWidth - scrollbarWidth - RIGHT_MARGIN;
    				std::string aString("");
    				std::string textStr = textLine.text;
    				for(unsigned int i=0; i<= std::strlen(textLine.text); i++)
    				{
    					aString = textStr.substr(0,i);
    					fontWidth = mPort->getTextWidth(aString.c_str(),DESC_TEXT_SIZE,style,aString.length());
    					if(fontWidth >= drawableTextWidth)
    						break;
    				}
    				aString += CLIP_TEXT;
    				mPort->drawText(aString.c_str(), localToGlobal(textTextPoint), DESC_TEXT_SIZE, style, textLine.fgcolor);
               	}
    			else
    			{		
    				mPort->drawText(textLine.text, localToGlobal(textTextPoint), DESC_TEXT_SIZE, style, textLine.fgcolor);
    			}
    			textPoint.y += voffset;
    			firstTime = false;
    		}
		}
	}

	// Left in for debug purposes
	//Rect viewArea(0,0,mViewArea.height(), mViewArea.width());
    //mPort->frameRect(localToGlobal(viewArea), PDG_GREEN_COLOR);

	//this->drawClickableParts();
}

void ListBox::addToList(const char* text, const Color& fgcolor) //, const Color& bgcolor) 
{
    // add the text to the scrolling history buffer
	ListBoxLine textLine;
	uint32 len = std::strlen(text);
	textLine.text = (char*)std::malloc(len + 1);
	if (!textLine.text) { // if the malloc failed we abort the add
	    return;
	}
	std::strncpy(textLine.text, text, len+1);
	MAKE_STRING_BUFFER_SAFE(textLine.text, len+1);
	textLine.fgcolor = fgcolor;
	textLine.bgcolor = mBkColor;
	mListText.push_back(textLine);

	mScrollbar->setMaxRange(mListText.size()-1);
	mScrollbar->setCurrentPosition(0);
	draw();
}

void ListBox::doClick(int part)
{

	int startSelection = VIEW_ID_SELECTION_START;
	int endSelection = VIEW_ID_SELECTION_START + mVisibleTextLines;

	if ((part >= startSelection) && (part < endSelection)) {
		int selectedPart = part - VIEW_ID_SELECTION_START;
		int selectedIndex = selectedPart + mWindowTopLineIndex;
		if (selectedIndex < (int)mListText.size()) {
			// If there was already one selected deselect it
			if ((mSelectedIndex != NO_SELECTION) && (mSelectedIndex < (int)mListText.size())) {
				mListText[mSelectedIndex].bgcolor = mBkColor;
			}

			mSelectedIndex = selectedIndex;
			mListText[mSelectedIndex].bgcolor = mHtColor;
			draw();
		}
	}
}

void ListBox::notify(Subject* subject)
{
	// This notification is that the scrollbar changed.
	// Recompute top line index
	int scrollPos = mScrollbar->getCurrentPosition();
	int scrollRange = mScrollbar->getScrollRange();
	int extraLines = mListText.size() - mVisibleTextLines;
	float scrollRatio = (float)scrollPos / (float)scrollRange;

	// We have enough lines to start scrolling.
	if (extraLines > 0)
	{
		mWindowTopLineIndex = (int)((float)extraLines * scrollRatio);
	}
	else
	{
		mWindowTopLineIndex = 0;
	}
	View::notify(subject);
}

const char* ListBox::getTextFromIndex(int index)
{
	return mListText[index].text;
}

// Clears all entries in list box
void ListBox::clear() 
{ 
	mListText.clear(); 
	mSelectedIndex = NO_SELECTION;
	mWindowTopLineIndex = 0;
	mScrollbar->setCurrentPosition(0);
} 

bool ListBox::doKeyPress(const KeyPressInfo* ki, View* view, int id, int part)
{
	int startSelection = VIEW_ID_SELECTION_START;
//	int endSelection = VIEW_ID_SELECTION_START + mVisibleTextLines;

	if (ki->unicode == key_UpArrow) {
		if ((mSelectedIndex == mWindowTopLineIndex) && (mSelectedIndex > 0)) {
			mWindowTopLineIndex = mWindowTopLineIndex - 1;
	        if ((mSelectedIndex != NO_SELECTION) && (mSelectedIndex < (int)mListText.size())) {
			    mListText[mSelectedIndex].bgcolor = mBkColor;
			}
			mListText[--mSelectedIndex].bgcolor = mHtColor;
			draw();
		} else if ((startSelection - 1) < mSelectedIndex) {
	        if ((mSelectedIndex != NO_SELECTION) && (mSelectedIndex < (int)mListText.size())) {
			    mListText[mSelectedIndex].bgcolor = mBkColor;
			}
			mListText[--mSelectedIndex].bgcolor = mHtColor;
			draw();
		}
		return true;		   
    }
    else if (ki->unicode == key_DownArrow) {
		int currLastVisible = mWindowTopLineIndex + (mVisibleTextLines-1);
		if (mSelectedIndex < ((int)mListText.size() - 1)) { // make sure we are within the list limits
    		if ((mSelectedIndex == currLastVisible) && (mSelectedIndex >= (mVisibleTextLines - 1))) {
    			mWindowTopLineIndex = mWindowTopLineIndex+1;
	            if ((mSelectedIndex != NO_SELECTION) && (mSelectedIndex < (int)mListText.size())) {
    			    mListText[mSelectedIndex].bgcolor = mBkColor;
    			}
    			mListText[++mSelectedIndex].bgcolor = mHtColor;
    			draw();
    		} else if (currLastVisible>mSelectedIndex) {
	            if ((mSelectedIndex != NO_SELECTION) && (mSelectedIndex < (int)mListText.size())) {
    			    mListText[mSelectedIndex].bgcolor = mBkColor;
    			}
    			mListText[++mSelectedIndex].bgcolor = mHtColor;
    			draw();
    		}
    	}
		return true;
	} else if (ki->unicode == key_PageUp) {
		if (mListText.size() > 0) {
			mWindowTopLineIndex = 0;
			if (mSelectedIndex != NO_SELECTION) {
				mListText[mSelectedIndex].bgcolor = mBkColor;
			}
			mSelectedIndex = 0;
			mListText[mSelectedIndex].bgcolor = mHtColor;
		}
		draw();
		return true;
	}
	else if (ki->unicode == key_PageDown) {
		if (mListText.size() > 0) {
			mWindowTopLineIndex = (mListText.size() - 1) - (mVisibleTextLines - 1);
			if (mWindowTopLineIndex < 0) {
				mWindowTopLineIndex = 0;
			}
			if ((mSelectedIndex != NO_SELECTION) && (mSelectedIndex < (int)mListText.size())) {
				mListText[mSelectedIndex].bgcolor = mBkColor;
			}
			mSelectedIndex = mListText.size() - 1;
			if (mSelectedIndex != NO_SELECTION) {
				mListText[mSelectedIndex].bgcolor = mHtColor;
			}
		}
		draw();
		return true;
	}
	
	return true;
		
}

} // namespace pdg

