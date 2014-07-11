// -----------------------------------------------
// EditText.cpp
// 
// Implementation for drawing a edit view
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

#include "pdg/app/EditText.h"
#include "timerids.h"

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
#include "CatanUIConsts.h"
#define EDITTEXT_COLOR CATAN_BUTTON_COLOR
#endif

#ifndef EDITTEXT_COLOR
   #define EDITTEXT_COLOR          Color(255, 207, 82)
#endif // !defined BUTTON_COLOR

#define ID_EDIT_TEXT 1

namespace pdg {

EditText::EditText(Controller* controller, Rect viewArea, int resourceID,int fontSize, Color bkColor, Color sTextColor, Graphics::Style textStyle)
: View(controller, viewArea),
mResMgr(controller->getApplication().getResourceManager()),
mbkColor(bkColor),mTextColor(sTextColor),mFontSize(fontSize),mStyle(textStyle),
mEventMgr(controller->getApplication().getEventManager()), 
mTimerMgr(controller->getApplication().getTimerManager()),
mLogMgr(&controller->getApplication().getLogManager()) 
{
	mMaxChars = 32767;		// Set to unlimited by default
	mbShowCaret = false;
	mbHasFocus = false;
	highlightStartPoint = Point(0,0);
	highlightEndPoint = Point(0,0);
	highlightStartCharIndex = -1;
	highlightEndCharIndex = -1;

	mText.erase();
	mAllowedKeys.erase();
	mBlockedKeys.erase();
	// Make sure the text style is always left justified, Otherwise text will be drawn 
	// outside view area
	if(Graphics::textStyle_Centered == (mStyle & Graphics::textStyle_Centered)) {
		mStyle = (Graphics::Style)(mStyle & (~Graphics::textStyle_Centered));
	}
	if(Graphics::textStyle_RightJustified == (mStyle & Graphics::textStyle_RightJustified)) {
		mStyle = (Graphics::Style)(mStyle & (~Graphics::textStyle_RightJustified));
	}

	if(!mPort->getDrawingArea().contains(viewArea))
	{
		viewArea = mPort->getDrawingArea();
		viewArea.bottom = viewArea.top + mPort->getCurrentFont(mStyle)->getFontHeight(mFontSize,mStyle) + TEXT_HEIGHT_OFFSET;
		//viewArea.setHeight(mPort->getFontHeight(mFontSize,mStyle));
		View::setViewArea(viewArea);
	}
	else
	{
		viewArea.bottom = viewArea.top + mPort->getCurrentFont(mStyle)->getFontHeight(mFontSize,mStyle) + TEXT_HEIGHT_OFFSET;
		View::setViewArea(viewArea);
	}
	std::string aString("");
	mResMgr.getString(aString,resourceID);
	int nTextWidth = mPort->getTextWidth("W",mFontSize,mStyle,1); 
	int charViewable = ( mViewArea.width() - (LEFT_MARGIN + RIGHT_MARGIN) )  / nTextWidth;
	if(aString.length() > (unsigned)charViewable)
	{
		// trim extra characters
		aString = aString.substr(0,charViewable);
	}
	// convert string into UTF16 format
	OS::utf8to16(mText, aString);
	addClickablePart(globalToLocal(mViewArea),CLICK_ID_EDITBOXVIEW);
	caretPos = 0;
	mEventMgr.addHandler(this, eventType_Timer);    // we need to start handling timer events
	mTimerMgr.startTimer(PDG_START_CURSOR_BLINK, 500, timer_Repeating);
}

EditText::~EditText()
{
	mTimerMgr.cancelTimer(PDG_START_CURSOR_BLINK);
	// do an addRef() to ensure that the removal of handlers won't call 
    // delete again on this object. Since we are already deleting, the 
    // addRef() is harmless, the object will be deleted anyway
	RefCountedImpl<IEventHandler>::addRef();
	mEventMgr.removeHandler(this, eventType_Timer);    // remove ourselves from the handler queue
}

void EditText::setFilter(const char* allowedKeys, const char* blockedKeys)
{
	OS::utf8to16(mAllowedKeys, allowedKeys);
	OS::utf8to16(mBlockedKeys, blockedKeys);
}

bool EditText::doKeyPress(const KeyPressInfo* ki, View* view, int id, int part)
{
	if(ki->unicode == 0 && ki->alt == true) // work around for avoiding KeyPress
											// when main game window is minimised or maximised
	{
		return true;
	}

	bool movement = false;

	if( (ki->unicode == key_Backspace) /*|| (ki->unicode == key_Delete)*/ ) // backspace or delete key
	{
		if(-1 != highlightStartCharIndex)
		{
			if(highlightStartCharIndex < highlightEndCharIndex)
			{
				mText.erase(highlightStartCharIndex,highlightEndCharIndex - highlightStartCharIndex);
				caretPos = highlightStartCharIndex;	
				highlightStartCharIndex = -1;
				movement = true;
			}
			else
			{
                mText.erase(highlightEndCharIndex,highlightStartCharIndex - highlightEndCharIndex);
				caretPos = highlightEndCharIndex;	
				highlightStartCharIndex = -1;
				movement = true;
			}
		}
		else if(caretPos > 0)
		{
			mText.erase(caretPos-1,1);
			caretPos -= 1;
			movement = true;
		}
		else // caretPos is zero, nothing to delete
			return true;
	}

	if( (ki->unicode == key_Delete) ) // backspace or delete key
	{
		if(-1 != highlightStartCharIndex)
		{
			if(highlightStartCharIndex < highlightEndCharIndex)
			{
				mText.erase(highlightStartCharIndex,highlightEndCharIndex - highlightStartCharIndex);
				caretPos = highlightStartCharIndex;	
				highlightStartCharIndex = -1;
				movement = true;
			}
			else
			{
                mText.erase(highlightEndCharIndex,highlightStartCharIndex - highlightEndCharIndex);
				caretPos = highlightEndCharIndex;	
				highlightStartCharIndex = -1;
				movement = true;
			}

		}
		else if(caretPos >= 0 && mText.length() > 0)
		{
			mText.erase(caretPos,1);
			movement = true;
		}
		else // caretPos is zero, nothing to delete
			return true;
	}

	if (ki->unicode == key_Tab) { // tab, may eventually move to next field
	    return true;
	}
	
	if (ki->unicode == key_UpArrow || ki->unicode == key_Home) {
		if(ki->shift){
			if(-1 == highlightStartCharIndex)
			{
				highlightStartCharIndex = caretPos;
				highlightEndCharIndex = 0;
				highlightEndPoint.y = 0;
				utf16string str = mText.substr(0,highlightStartCharIndex);
				// convert str from UTF16 to UTF8
				std::string aString("");
				OS::utf16to8(aString, str);
				highlightStartPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
			}
			else
			{
				highlightEndCharIndex = 0;
				highlightEndPoint.y = 0;
			}
		}
		else
				highlightStartCharIndex = -1;
        
		caretPos = 0;
		movement = true;        
    }
	if (ki->unicode == key_DownArrow || ki->unicode == key_End) {
		if(ki->shift){
			if(-1 == highlightStartCharIndex)
			{
				highlightStartCharIndex = caretPos;
				highlightEndCharIndex =  mText.length();

				utf16string str = mText.substr(0,highlightStartCharIndex);
				// convert str from UTF16 to UTF8
				std::string aString("");
				OS::utf16to8(aString, str);
				highlightStartPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());

				str = mText.substr(0,highlightEndCharIndex);
				// convert str from UTF16 to UTF8
				aString = "";
				OS::utf16to8(aString, str);
				highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
			}
			else
			{
				highlightEndCharIndex =  mText.length();
				utf16string str = mText.substr(0,highlightEndCharIndex);
				// convert str from UTF16 to UTF8
				std::string aString = "";
				OS::utf16to8(aString, str);
				highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
			}
		}
		else
			highlightStartCharIndex = -1;

		caretPos = mText.length();
		movement = true;        
    }
    if (ki->unicode == key_LeftArrow){
		if (caretPos > 0){
			if(ki->shift){
                if(-1 == highlightStartCharIndex)
				{
					highlightStartCharIndex = caretPos;
					highlightEndCharIndex = caretPos - 1;

					utf16string str = mText.substr(0,highlightStartCharIndex);
					// convert str from UTF16 to UTF8
					std::string aString("");
					OS::utf16to8(aString, str);
					highlightStartPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());

					str = mText.substr(0,highlightEndCharIndex);
					// convert str from UTF16 to UTF8
					aString = "";
					OS::utf16to8(aString, str);
					highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
				}
				else
				{
					highlightEndCharIndex = caretPos-1;
					utf16string str = mText.substr(0,highlightEndCharIndex);
					// convert str from UTF16 to UTF8
					std::string aString("");
					OS::utf16to8(aString, str);
					highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
				}
			}
			else
				highlightStartCharIndex = -1;			
			caretPos -= 1;
    		movement = true;        			
		}
		else if(!ki->shift)
			highlightStartCharIndex = -1;
	}
    if (ki->unicode == key_RightArrow) {
        if ((unsigned)caretPos <= mText.length()) {
			if(ki->shift){
                if(-1 == highlightStartCharIndex)
				{
					highlightStartCharIndex = caretPos;
					highlightEndCharIndex = caretPos + 1;

					utf16string str = mText.substr(0,highlightStartCharIndex);
					// convert str from UTF16 to UTF8
					std::string aString("");
					OS::utf16to8(aString, str);
					highlightStartPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());

					str = mText.substr(0,highlightEndCharIndex);
					// convert str from UTF16 to UTF8
					aString = "";
					OS::utf16to8(aString, str);
					highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
				}
				else
				{
					highlightEndCharIndex = caretPos + 1;
					utf16string str = mText.substr(0,highlightEndCharIndex);
					// convert str from UTF16 to UTF8
					std::string aString = "";
					OS::utf16to8(aString, str);
					highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
				}
			}
			else
				highlightStartCharIndex = -1;
			caretPos += 1;
    		movement = true;        
		}
		else if(!ki->shift)
			highlightStartCharIndex = -1;
    }
    if (movement) {
        View::draw();
        return true;
    }
    
	if (ki->unicode < key_FirstPrintable) { // some other non-printable char from ASCII
	    return true;
	}
	
	// check pressed key in filter. Allowed filter has precedance over Blocked filter
	if(mAllowedKeys.npos == mAllowedKeys.find((utf16char)ki->unicode))
		if(mAllowedKeys.npos != mBlockedKeys.find((utf16char)ki->unicode))
			return true;

	// Before inserting, appending or prepending character, check whether the resulting string
	// would exceed the set character buffer maximum..
	if (mText.size() == getBufMax())
		return true;

	// and can fit in display area
	if(!canFitInDisplayArea(ki))
		return true; // does not fit in display area

	if(caretPos == 0) // add character at beginning
	{
		if(-1 != highlightStartCharIndex)
		{
			if(highlightStartCharIndex < highlightEndCharIndex)
			{
				mText.erase(highlightStartCharIndex,highlightEndCharIndex - highlightStartCharIndex);
				caretPos = highlightStartCharIndex;	
				highlightStartCharIndex = -1;
			}
			else
			{
                mText.erase(highlightEndCharIndex,highlightStartCharIndex - highlightEndCharIndex);
				caretPos = highlightEndCharIndex;	
				highlightStartCharIndex = -1;
			}
		}
		utf16string str;
		str = utf16char(ki->unicode);
		mText = str + mText;
		caretPos += 1;
	}
	else if((unsigned)caretPos >= mText.length()) // append character
	{
		if(-1 != highlightStartCharIndex)
		{
			if(highlightStartCharIndex < highlightEndCharIndex)
			{
				mText.erase(highlightStartCharIndex,highlightEndCharIndex - highlightStartCharIndex);
				highlightStartCharIndex = -1;
				caretPos = mText.length();
			}
			else
			{
                mText.erase(highlightEndCharIndex,highlightStartCharIndex - highlightEndCharIndex);
				highlightStartCharIndex = -1;
				caretPos = mText.length();
			}
		}
		mText += utf16char(ki->unicode);
		caretPos += 1;
	}
	else								// insert character at caret possition
	{
		if(-1 != highlightStartCharIndex)
		{
			if(highlightStartCharIndex < highlightEndCharIndex)
			{
				mText.erase(highlightStartCharIndex,highlightEndCharIndex - highlightStartCharIndex);
				caretPos = highlightStartCharIndex;	
				highlightStartCharIndex = -1;
			}
			else
			{
                mText.erase(highlightEndCharIndex,highlightStartCharIndex - highlightEndCharIndex);
				caretPos = highlightEndCharIndex;	
				highlightStartCharIndex = -1;
			}
		}

		utf16string str;
		str = utf16char(ki->unicode);
		mText.insert(caretPos,str);
		caretPos += 1;
	}
	View::draw();
//#ifdef DEBUG
//	{
//		std::string aString("");
//		OS::utf16to8(aString, mText);
//		OS::_DOUT( "mText [%s]", aString.c_str() );
//		//mLogMgr << "mText [" << aString.c_str() << "]";
//	}
//#endif
	return true;
}


void EditText::drawSelf()
{
	//Rect tempRect = localToGlobal(mViewArea);
	Rect tempRect = mViewArea;
	// convert mText from UTF16 to UTF8
	std::string aString("");
	OS::utf16to8(aString, mText);
	// fill text rect
	mPort->fillRect(tempRect,mbkColor);
	// draw text 
	Point textPoint = tempRect.leftTop();
	textPoint.x += LEFT_MARGIN;	// left
	textPoint.y = textPoint.y + mPort->getCurrentFont()->getFontHeight(mFontSize,mStyle);// + TEXT_HEIGHT_OFFSET/2; //top	
	if (-1 != highlightStartCharIndex ) {
		if(highlightStartCharIndex > highlightEndCharIndex)
		{
			Rect highlightRect = mViewArea;			
			highlightRect.left = LEFT_MARGIN + mViewArea.left + highlightEndPoint.y;
			highlightRect.right = mViewArea.left + LEFT_MARGIN + highlightStartPoint.y;
			mPort->fillRect(highlightRect,EDITTEXT_COLOR);
		}
		else if(highlightStartCharIndex < highlightEndCharIndex)
		{
			Rect highlightRect = mViewArea;
			highlightRect.left = LEFT_MARGIN + mViewArea.left + highlightStartPoint.y;
			highlightRect.right = LEFT_MARGIN + mViewArea.left + highlightEndPoint.y;
			mPort->fillRect(highlightRect,EDITTEXT_COLOR);
		}
	}
	mPort->drawText(aString.c_str(), textPoint, mFontSize,mStyle,mTextColor);
	// draw border
	drawBorder();	
	// draw caret
	drawCaret();
}

void EditText::drawCaret()
{
	// draw caret
	if (mbHasFocus && (highlightStartCharIndex == -1)) 	// draw caret only when there is no highlighting
	{
		utf16string str = mText.substr(0,caretPos);
		// convert str from UTF16 to UTF8
		std::string aString("");
		OS::utf16to8(aString, str);

		int nTextWidth = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length()); 
		Rect caretRect = mViewArea;
		caretRect.left = caretRect.left + nTextWidth + LEFT_MARGIN;
		caretRect.right = caretRect.left+1;
		caretRect.top += 1;
		caretRect.bottom -= 1;
		if(mbShowCaret)
			mPort->fillRect(caretRect);
		else
			mPort->fillRect(caretRect, mbkColor);
	}
}

void EditText::drawBorder()
{
	Point leftTop,rightTop,leftBottom,rightBottom; // used to draw border for edit view
	
	//Rect tempRect = localToGlobal(mViewArea);
	Rect tempRect = mViewArea;
	tempRect.grow(2);
	
	leftTop = Point(tempRect.left,tempRect.top);
	rightTop = Point(tempRect.right,tempRect.top);
	rightTop.x -= 2;
	leftBottom = Point(tempRect.left,tempRect.bottom);
	leftBottom.y -= 2;
	rightBottom = Point(tempRect.right,tempRect.bottom);

	mPort->drawLineEx(leftTop,rightTop,2,Graphics::solidPat,0, PDG_BLACK_COLOR);
	mPort->drawLineEx(leftTop,leftBottom,2,Graphics::solidPat,0,PDG_BLACK_COLOR);

/*	tempRect.shrink(2);
	leftTop = Point(tempRect.left,tempRect.top);
	rightTop = Point(tempRect.right,tempRect.top);
	leftBottom = Point(tempRect.left,tempRect.bottom);
	rightBottom = Point(tempRect.right,tempRect.bottom);

//	mPort->drawLineEx(rightTop,rightBottom,2,Graphics::solidPat,0,PDG_WHITE_COLOR,Graphics::halfTransparent);

	rightBottom.x += 1;

	//mPort->drawLineEx(leftBottom,rightBottom,2,Graphics::solidPat,0,PDG_WHITE_COLOR,Graphics::halfTransparent);*/
}

void EditText::setFocus(bool bFocus)
{
	mbHasFocus = bFocus;
	selectAll();
	draw();
}


// catch the time events here, and handle accordingly
bool EditText::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw()  // return true if completely handled
{
	bool handled = false;
	if (inEventType == eventType_Timer)
	{
		TimerInfo* ti = static_cast<TimerInfo*>(inEventData);
		if(mController->isActive() && (ti->id == PDG_START_CURSOR_BLINK))   // don't flash caret unless we are active
		{
			if(mbShowCaret)
			{
				mbShowCaret = false;
				//drawSelf();
				View::draw();
			}
			else
			{
				mbShowCaret = true;
				//drawSelf();
				View::draw();
			}
			handled = true;
		}
	}
	return handled;
}
bool EditText::canFitInDisplayArea(const KeyPressInfo* ki)
{
	utf16string strTemp;
	strTemp = mText;
	strTemp += utf16char(ki->unicode);
	std::string aString("");
	OS::utf16to8(aString, strTemp);
	if( (mViewArea.width()-LEFT_MARGIN-RIGHT_MARGIN) > mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length())) 
		return true; 
	else
		return false;
}

void EditText::getText(std::string& outString)
{
	OS::utf16to8(outString, mText);
}

void EditText::setText(const char *text)
{
	std::string aString = text;
	OS::utf8to16(mText, aString);
    selectAll();
	draw();
}
	
/*
void EditText::doMouseEnter(const MouseInfo *mi,int id, int part)
{
}

void EditText::doMouseLeave(const MouseInfo *mi,int id, int part)
{
	mbHasFocus = false;
	View::draw();
}
*/

void EditText::doMouseMove(const MouseInfo *mi, int id, int part)
{
	mbHasFocus = true;
	mbShowCaret = true;
	std::string UTF8str("");

	if(mi->leftButton)
	{
        if(mText.length() == 0)
		{
            caretPos = 0;
			highlightStartCharIndex = -1;
		}
		else
		{
            utf16string str;
			str.erase();
			if(-1 == highlightStartCharIndex)
				highlightStartCharIndex = caretPos;
			
			caretPos = 0;
			for(unsigned int i=0; i < mText.length(); i++)
			{
				str += mText.at(i);
				OS::utf16to8(UTF8str, str);
				if(mi->mousePos.x >= (mViewArea.left + LEFT_MARGIN + mPort->getTextWidth(UTF8str.c_str(),mFontSize,mStyle,UTF8str.length())))
					caretPos += 1;
				else
					break;
			}
			
			str = mText.substr(0,highlightStartCharIndex);
			// convert str from UTF16 to UTF8
			std::string aString("");
			OS::utf16to8(aString, str);
			highlightStartPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());

			highlightEndCharIndex = caretPos;
			str = mText.substr(0,highlightEndCharIndex);
			// convert str from UTF16 to UTF8
			aString = "";
			OS::utf16to8(aString, str);
			highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
		}
		// show caret at appropriate location
		View::draw();
	}
}

bool EditText::doMouseDown(const MouseInfo *mi, int id, int part) 
{
	mbHasFocus = true;
	mbShowCaret = true;
	std::string UTF8str("");
	if(mi->shift)
	{
		if(-1 == highlightStartCharIndex)
			highlightStartCharIndex = caretPos;
	}
	else
		highlightStartCharIndex = -1;		

	utf16string str;
	str.erase();
	caretPos = 0;
    
	for(unsigned int i=0; i < mText.length(); i++)
	{
		str += mText.at(i);
		OS::utf16to8(UTF8str, str);
		if(mi->mousePos.x >= (mViewArea.left + LEFT_MARGIN + mPort->getTextWidth(UTF8str.c_str(),mFontSize,mStyle,UTF8str.length())))
			caretPos += 1;
		else
			break;
	}
	str = mText.substr(0,highlightStartCharIndex);
	// convert str from UTF16 to UTF8
	std::string aString("");
	OS::utf16to8(aString, str);
	highlightStartPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());

	highlightEndCharIndex = caretPos;
	str = mText.substr(0,highlightEndCharIndex);
	// convert str from UTF16 to UTF8
	aString = "";
	OS::utf16to8(aString, str);
	highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
	// show caret at appropriate location
	View::draw();
	return true;
}

bool EditText::doMouseUp(const MouseInfo *mi, int id, int part) 
{
	std::string UTF8str("");
	
	if(mText.length() == 0)
	{
		caretPos = 0;
		highlightStartCharIndex = -1;
	}
	else 
	{
        utf16string str;
		str.erase();
		caretPos = 0;
        for(unsigned int i=0; i < mText.length(); i++)
		{
			str += mText.at(i);
			OS::utf16to8(UTF8str, str);
			if(mi->mousePos.x >= (mViewArea.left + LEFT_MARGIN + mPort->getTextWidth(UTF8str.c_str(),mFontSize,mStyle,UTF8str.length())))
				caretPos += 1;
			else
				break;
		}
		highlightEndCharIndex = caretPos;
		str = mText.substr(0,highlightEndCharIndex);
		// convert str from UTF16 to UTF8
		std::string aString("");
		OS::utf16to8(aString, str);		
		highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
	}
	// show caret at appropriate location
	View::draw();
	return true;
}

bool EditText::doDoubleClick(const MouseInfo *mi, int id, int part, int clickCount) 
{
	//int wordStartPos = -1;
	bool wordFound = false;
	bool newWord = false;
	mbHasFocus = true;
	mbShowCaret = true;
	std::string UTF8str("");
	utf16string str;
	str.erase();
	caretPos = 0;

	if(mText.length() == 0)
	{
		caretPos = 0;
		highlightStartCharIndex = -1;
	}
	else
	{
		highlightStartCharIndex = 0;
		unsigned int i;
        for(i=0; i < mText.length(); i++)
		{
			if(mText.at(i) == 0x20)
			{
				if(!wordFound)
                    wordFound = false;
				else
					newWord = true;
			}
			else
			{
				if(!wordFound || newWord)
				{
					highlightStartCharIndex = i;
                    wordFound = true;
					newWord = false;
				}
			}
			// Word starts with a non white characters
			// we will consider it as word till we will not find next character after  
			// one or more spaces
			str += mText.at(i);
			OS::utf16to8(UTF8str, str);
			if(mi->mousePos.x >= (mViewArea.left + LEFT_MARGIN + mPort->getTextWidth(UTF8str.c_str(),mFontSize,mStyle,UTF8str.length())))
				caretPos += 1;
			else
				break;
		}
		if(wordFound)
		{
			highlightEndCharIndex = caretPos;
			if(i >= mText.length())
				caretPos = highlightEndCharIndex = mText.length();	
			else
			{
				for(;i < mText.length() && mText.at(i) != 0x20; i++)
					caretPos = highlightEndCharIndex = i+1;
				if(i >= mText.length())
					caretPos = highlightEndCharIndex = mText.length();
				else
				{
					for(; i < mText.length() && mText.at(i) == 0x20; i++)
						caretPos = highlightEndCharIndex = i+1;
				}
			}
		}

		if(-1 != highlightStartCharIndex)
		{
			str = mText.substr(0,highlightStartCharIndex);
			// convert str from UTF16 to UTF8
			std::string aString("");
			OS::utf16to8(aString, str);
			highlightStartPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());

			str = mText.substr(0,highlightEndCharIndex);
			// convert str from UTF16 to UTF8
			aString = "";
			OS::utf16to8(aString, str);
			highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
			View::draw();
		}
	}
	return true;
}

void EditText::selectAll()
{
	if(mText.length() == 0)
	{
		caretPos = 0;
		highlightStartCharIndex = -1;
	}
	else
	{
        highlightStartCharIndex = 0;
		highlightStartPoint.y = 0;
	
		caretPos = highlightEndCharIndex = mText.length();		

		utf16string str = mText.substr(0,highlightEndCharIndex);
		// convert str from UTF16 to UTF8
		std::string aString("");
		OS::utf16to8(aString, str);
		highlightEndPoint.y = mPort->getTextWidth(aString.c_str(),mFontSize,mStyle,aString.length());
	}
	View::draw();
}

} // close namespace pdg
