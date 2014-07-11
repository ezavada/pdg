// -----------------------------------------------
// PopupMenu.cpp
// 
// Implementation for drawing a PopupMenu
//
// Written by Alan Davies and Ed Zavada, 2004-2012
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

#include "pdg/app/PopupMenu.h"

#ifndef PDG_ALLOW_DEPRECATED_CALLS
#error You must define PDG_ALLOW_DEPRECATED_CALLS in your project to use PopupMenu.cpp
#endif

namespace pdg {

PopupMenu::PopupMenu(Controller* controller, Point topLeft, Color bkColor, Color sTextColor, Color highlightColor, int nTextSize)
: View(controller, Rect(0,0,0,0)),
mResMgr(controller->getApplication().getResourceManager()),
mbkColor(bkColor),mTextColor(sTextColor),mhighlightColor(highlightColor),mTextSize(nTextSize), mPullArrowImage(0)
{
	mStartIndex = START_INDEX_NONE;
	mHotItem = HOT_ITEM_NONE;
	mNeedScrolling = false;
	mShowUpArrow = false;
	mShowDownArrow = false;
	mOldScrollPos = Point(0,0);

	mViewArea.left = topLeft.x;
	mViewArea.top = topLeft.y;

    mMinWidth = 0;
    
	loadImages();
}

PopupMenu::PopupMenu(Controller* controller, Rect area, Color bkColor, Color sTextColor, Color highlightColor, int nTextSize)
: View(controller, Rect(0,0,0,0)),
mResMgr(controller->getApplication().getResourceManager()),
mbkColor(bkColor),mTextColor(sTextColor),mhighlightColor(highlightColor),mTextSize(nTextSize), mPullArrowImage(0)
{
	mStartIndex = START_INDEX_NONE;
	mHotItem = HOT_ITEM_NONE;
	mNeedScrolling = false;
	mShowUpArrow = false;
	mShowDownArrow = false;
	mOldScrollPos = Point(0,0);

	mViewArea.left = area.left;
	mViewArea.top = area.top;

    mMinWidth = area.width();
    
    mBaseRect = area;

	loadImages();
}

PopupMenu::~PopupMenu()
{
}

void PopupMenu::sanitiseViewArea()
{
    // figure out how big we need to be
	int fontHeight = mPort->getCurrentFont()->getFontHeight(mTextSize) + ITEM_SIZE_OFFSET;
	int requiredWidth = TEXT_WIDTH_OFFSET + mPort->getTextWidth(mLongestText.c_str(),mTextSize,(Graphics::Style)(Graphics::textStyle_Bold + Graphics::textStyle_Italic + Graphics::textStyle_Underline),mLongestText.length()); 
    if (mMinWidth && (requiredWidth < mMinWidth)) {
        requiredWidth = mMinWidth;
    }
	if ( (requiredWidth > MAX_MENU_WIDTH) || (requiredWidth <= 0)) {
		requiredWidth = MAX_MENU_WIDTH;
	}
    int requiredHeight = mItemList.size() * fontHeight;

    // always start from where the item is located    
    mViewArea = mBaseRect;

    // now adjust width and height to accomodate items
	mViewArea.setWidth(requiredWidth);
	mViewArea.setHeight(requiredHeight);

    // sanitize the rectangle

	Rect parentGlobalRect = mPort->getDrawingArea();

// first check height and width of view area is less than mPort->getDrawingArea()
// if not reduce it to fit in mPort->getDrawingArea()
	if (!parentGlobalRect.contains(mViewArea))
	{
// check if width and/or height of menu view is more than mPort->getDrawingArea()
		int parentHeight = parentGlobalRect.height();
		int parentWidth = parentGlobalRect.width();
		
		int viewHeight = mViewArea.height();
		int viewWidth = mViewArea.width();
		
		if(parentHeight < viewHeight) // adjust menu view Height
		{
			mViewArea.setHeight(parentHeight);
		}
		if(parentWidth < viewWidth) // adjust menu view width
		{
			mViewArea.setWidth(parentWidth - VIEW_WIDTH_OFFSET);
		}

// check if menu view is crossing bottom boundaries of mPort->getDrawingArea(),
// if yes, shift it up.

		if (mViewArea.bottom > parentGlobalRect.bottom) // menu view is crossing left boundary of parent
		{
			int vShift = (mViewArea.bottom - parentGlobalRect.bottom);
			mViewArea.moveUp(vShift);
		}

// check if menu view is crossing left/right boundaries of mPort->getDrawingArea(),
// if yes, shift it left or right.

		if (mViewArea.left < parentGlobalRect.left) // menu view is crossing left boundary of parent
		{
			int hShift = (parentGlobalRect.left - mViewArea.left) + VIEW_HSHIFT_OFFSET;
			mViewArea.moveRight(hShift);
		}
		if (mViewArea.right > parentGlobalRect.right) // menu view is crossing right boundary of parent
		{
			int hShift = (mViewArea.right - parentGlobalRect.right) + VIEW_HSHIFT_OFFSET;
			mViewArea.moveLeft(hShift);
		}
	}

// do we need scrollable menu?
	mItemShowable = mViewArea.height() / fontHeight;
	if ((unsigned)mItemShowable < mItemList.size()) {
		mNeedScrolling = true;
	} else {
	    mNeedScrolling = false;
	}

	if (mItemShowable * fontHeight < mViewArea.height()) {
	    mViewArea.setHeight(mItemShowable * fontHeight);
	}
}

void PopupMenu::scrollMenu(int nItems) 
{
/*	if(mNeedScrolling)
	{
		if(nItems < 0)
		{
			for(int i = nItems; i< 0 && mStartIndex != 1; i++)
				mStartIndex -= 1;
		}
		else if(nItems > 0)
		{
			for(int i = 1; i <= nItems && ( mItemList.size()  != (mStartIndex - 1) + (mItemShowable) ) ; i++)
				mStartIndex += 1;
		}
	} */
// recalculate clickable area, set need to draw up/down or both arrows
	showSelf();
// draw menu with new items
	draw();
}

void PopupMenu::drawSelf()
{
	if(mDrawableItemList.size() == 0)
	{
		return;
	}

	Point leftTop,rightTop,leftBottom,rightBottom; // used to draw border for menu
//	if(!mNeedScrolling)
	{
		itemRectPair val = mDrawableItemList.front();
		Rect tempRect = localToGlobal(val.first);
	
		leftTop = Point(tempRect.left,tempRect.top);
		rightTop = Point(tempRect.right,tempRect.top);

		val = mDrawableItemList.back();
		tempRect = localToGlobal(val.first);

		leftBottom = Point(tempRect.left,tempRect.bottom);
		rightBottom = Point(tempRect.right,tempRect.bottom);
	}
/*	else // menu is scrollable 
	{
// leftTop and rightTop are points of first item in mDrawableItemList
		itemRectPair val = mDrawableItemList.front();
		Rect tempRect = localToGlobal(val.first);
		leftTop = Point(tempRect.left,tempRect.top);
		rightTop = Point(tempRect.right,tempRect.top);
// to draw boder for menu
// leftBottom are points of rect whose id is ITEM_UP_ARROW 
		tempRect = localToGlobal(View::getClickableRectFromID(ITEM_UP_ARROW));
		leftBottom = Point(tempRect.left,tempRect.bottom);
// and rightBottom are points of rect whose id is ITEM_DOWN_ARROW
		tempRect = localToGlobal(View::getClickableRectFromID(ITEM_DOWN_ARROW));
		rightBottom = Point(tempRect.right,tempRect.bottom);
	} */

// draw menu items
	DrawableList::iterator itr;
	for(itr = mDrawableItemList.begin(); itr != mDrawableItemList.end(); itr++)
	{
		itemRectPair val = *itr;
		Rect tempRect = localToGlobal(val.first);
		ItemInfo item = val.second;

// to highlight item
		if(mHotItem == item.mItemID)
		{
			mPort->fillRect(tempRect,mbkColor);
			tempRect.shrink(HIGHLIGHT_AREA_MARGIN);
			mPort->fillRect(tempRect,mhighlightColor);
		}
		else
		{
			mPort->fillRect(tempRect,mbkColor);
			tempRect.shrink(HIGHLIGHT_AREA_MARGIN);
		}
		// Draw down arrow if this if the first item
		if(itr == mDrawableItemList.begin())
		{
			if(mPullArrowImage)
			{
				Point arrowPt(tempRect.right - mPullArrowImage->width - 2, 
					(tempRect.height() - mPullArrowImage->height)/2 + tempRect.top);
//				mPullArrowImage->draw(arrowPt);
			}
		}
// draw item vertically centered
		int fontHeight = mPort->getCurrentFont(item.mStyle)->getFontHeight(mTextSize,item.mStyle);
		Point textPoint(tempRect.left,tempRect.top); 
		textPoint.y = textPoint.y + fontHeight - (tempRect.height() - fontHeight)/2 ;
		textPoint.x += HIGHLIGHT_AREA_MARGIN + TEXT_LEFT_MARGIN;
// check if text is crossing width of menu, if yes, draw cliped text
		int fontWidth = mPort->getTextWidth(item.mItemString.c_str(),mTextSize,item.mStyle,item.mItemString.length());
		if(fontWidth > mViewArea.width() - HIGHLIGHT_AREA_MARGIN + TEXT_LEFT_MARGIN)
		{
			int clipTextWidth = mPort->getTextWidth(CLIP_TEXT,mTextSize,item.mStyle);
			int drawableTextWidth = mViewArea.width() - clipTextWidth - (HIGHLIGHT_AREA_MARGIN *4) - TEXT_LEFT_MARGIN;
			std::string aString;
			for(unsigned int i=0; i< item.mItemString.length(); i++)
			{
				aString = item.mItemString.substr(0,i);
				fontWidth = mPort->getTextWidth(aString.c_str(),mTextSize,item.mStyle,aString.length());
				if(fontWidth >= drawableTextWidth)
					break;
			}
			aString += CLIP_TEXT;
			mPort->drawText(aString.c_str(), textPoint, mTextSize,item.mStyle,mTextColor);
		}
		else
			mPort->drawText(item.mItemString.c_str(), textPoint, mTextSize,item.mStyle,mTextColor);
	}

/*	if(mNeedScrolling && mScrollImages[0] && mScrollImages[1] && mScrollImages[2] && mScrollImages[3])
	{
// for up arrow
		Rect tempRect = localToGlobal(View::getClickableRectFromID(ITEM_UP_ARROW));
			mPort->fillRect(tempRect,mbkColor);
		if(mShowUpArrow) // draw enabled up arrow
		{
			Point imagePoint = tempRect.leftTop(); 
			imagePoint.x += (tempRect.width() - mScrollImages[0]->width) /2 ;
			imagePoint.y += (tempRect.height() - mScrollImages[0]->height) /2;
			mScrollImages[0]->draw(imagePoint);
		}
		else // draw disabled up arrow
		{
			Point imagePoint = tempRect.leftTop(); 
			imagePoint.x += (tempRect.width() - mScrollImages[1]->width) /2 ;
			imagePoint.y += (tempRect.height() - mScrollImages[1]->height) /2;
			mScrollImages[1]->draw(imagePoint);
		}

// for down arrow
		tempRect = localToGlobal(View::getClickableRectFromID(ITEM_DOWN_ARROW));
		mPort->fillRect(tempRect,mbkColor);
		if(mShowDownArrow) // draw enabled down arrow
		{
			Point imagePoint = tempRect.leftTop(); 
			imagePoint.x += (tempRect.width() - mScrollImages[2]->width) /2 ;
			imagePoint.y += (tempRect.height() - mScrollImages[2]->height) /2;
			mScrollImages[2]->draw(imagePoint);
		}
		else // draw disabled down arrow
		{
			Point imagePoint = tempRect.leftTop(); 
			imagePoint.x += (tempRect.width() - mScrollImages[3]->width) /2 ;
			imagePoint.y += (tempRect.height() - mScrollImages[3]->height) /2;
			mScrollImages[3]->draw(imagePoint);
		}
	} */

	if(mItemList.size() > 0)// draw menu border
	{
		mPort->drawLine(leftTop,rightTop, PDG_GRAY_50_COLOR);
		mPort->drawLine(leftTop,leftBottom, PDG_GRAY_50_COLOR);
		mPort->drawLine(rightTop,rightBottom, PDG_BLACK_COLOR);
		mPort->drawLine(leftBottom,rightBottom, PDG_BLACK_COLOR);
	}
}

void PopupMenu::calcClickableAreas()
{
	int fontHeight = mPort->getCurrentFont()->getFontHeight(mTextSize) + ITEM_SIZE_OFFSET;

	std::list<ItemInfo>::iterator itr;
	Point itemTLPoint(mViewArea.left,mViewArea.top);
	Point itemBRPoint(mViewArea.right,mViewArea.top+fontHeight);

// clear previous list of clickablepart
	mClickableParts.clear();
// clear previous list of drawable items
	mDrawableItemList.clear();

// for menu items
/*	if(mNeedScrolling)
	{
// advance in itemlist till we will not reach the item representing start index.
		itr = mItemList.begin();
		for( int i=1; i< mStartIndex; itr++,i++) {}
// now we are at items which need to be shown
		for( int i=1; i <= mItemShowable && itr != mItemList.end(); itr++, i++)
		{
			Rect clickArea(itemTLPoint, itemBRPoint);
			ItemInfo item = *itr;
			this->addClickablePart(globalToLocal(clickArea),item.mItemID);
			addDrawableItemPart(globalToLocal(clickArea),item);
			itemTLPoint.y += fontHeight;
			itemBRPoint.y += fontHeight;
		}
	}
	else */
	{
// advance in itemlist till we will not reach the item representing start index.
		itr = mItemList.begin();
		for( int i=1; i< mStartIndex; itr++,i++) {}
// now we are at items which need to be shown
		for( int i=1; i <= mItemShowable && itr != mItemList.end(); itr++, i++)
		{
			Rect clickArea(itemTLPoint, itemBRPoint);
			ItemInfo item = *itr;
			this->addClickablePart(globalToLocal(clickArea),item.mItemID);
			addDrawableItemPart(globalToLocal(clickArea),item);
			itemTLPoint.y += fontHeight;
			itemBRPoint.y += fontHeight;
		}
	}

// for up and down arrow
/*	if(mNeedScrolling && mScrollImages[0])
	{
// we are advanced points by font height, as here we are dealing with images. 
// add image height to itemTLPoint to get new bottom,right points
		itemBRPoint.y = itemTLPoint.y + mScrollImages[0]->height + IMAGE_HEIGHT_OFFSET;
		itemBRPoint.x = itemTLPoint.x + (mViewArea.width() / MAX_ARROW_IMAGES);
// add rect for up arrow
		Rect clickArea(itemTLPoint, itemBRPoint);
		this->addClickablePart(globalToLocal(clickArea), ITEM_UP_ARROW);
		itemTLPoint.x = itemBRPoint.x;
		itemBRPoint.x = mViewArea.right;
		this->addClickablePart(globalToLocal(Rect(itemTLPoint, itemBRPoint)),ITEM_DOWN_ARROW);

	} */
}

void PopupMenu::showSelf()
{

	sanitiseViewArea();

	if (mStartIndex == START_INDEX_NONE) { // function called first time
		mStartIndex = 1;
    }

// do we need to show up/down or both arrow(s)	
// by setting true does not mean we need to draw up/down or both arrows
// it also depends on mNeedScrolling. If mNeedScrolling is true then we will draw enabled 
// or disabled arrow images depending on mShowUpArrow, mShowDownArrow's value.
// true - draw enabled arrow, false - draw disabled arrow

	if (mStartIndex > 1) {
		mShowUpArrow = true;
	} else {
		mShowUpArrow = false;
    }

	if ((unsigned)mItemShowable < mItemList.size())
	{
		if (mStartIndex > 1)
		{
			if((int)mItemList.size()  == (mStartIndex - 1) + (mItemShowable)) {
				mShowDownArrow = false;
			} else {
				mShowDownArrow = true;
		    }
		}
		else
		{
			mShowDownArrow = true;
	    }
	}
	else
	{
		mShowDownArrow = false;
    }

// update clickablepart list
	calcClickableAreas();

	mHotItem = getPartClicked(OS::getMouse());
}	

void PopupMenu::loadImages()
{
//	loadImageArray(mResMgr, mScrollImages, RES_MENU_IMAGES, MAX_ARROW_IMAGES + MAX_ARROW_IMAGES);
	mPullArrowImage = loadImage(mResMgr, RES_MENU_IMAGES, RES_PULL_ARROW);
}

void PopupMenu::setLongestText()
{
    FIXME("if this is for width calculation purposes, it won't work correctly because we aren't using monospaced fonts");
	mLongestText = "";
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++)
	{
		ItemInfo item = *itr;
		if (mLongestText.length() < item.mItemString.length()) {
			mLongestText = item.mItemString;
	    }
	}
}

void PopupMenu::loadString(std::string& aString,int resourceID, int numSubstr)
{
	mResMgr.getString(aString, resourceID, numSubstr);	
}

int PopupMenu::addMenuItem(int itemID, const char* text, Graphics::Style textStyle, int index)
{
// itemID must be greater than 2, we are using 1 for ITEM_UP_ARROW and 2 for ITEM_DOWN_ARROW for scrolling purpose
	if (itemID <= 2) {
		return 0;
	}

// Make sure the text style is always left justified, Otherwise text will be drawn 
// outside menu area
	if (Graphics::textStyle_Centered == (textStyle & Graphics::textStyle_Centered)) {
		textStyle = (Graphics::Style)(textStyle & (~Graphics::textStyle_Centered));
	}
	if (Graphics::textStyle_RightJustified == (textStyle & Graphics::textStyle_RightJustified)) {
		textStyle = (Graphics::Style)(textStyle & (~Graphics::textStyle_RightJustified));
	}


	std::string aString(text);
// find the longest text in menu
	if (mLongestText.length() < aString.length()) {
		mLongestText = aString;
	}

	if (index < 0 || (unsigned)index >= mItemList.size()) // append item
	{
		ItemInfo tempItem(itemID,aString,TEXT_RESOURCE_ID_NONE,textStyle);
		mItemList.push_back(tempItem);
// return index of newly inserted menu item
		return mItemList.size();
	}
	if (index == 0)
	{
		ItemInfo tempItem(itemID,aString,TEXT_RESOURCE_ID_NONE,textStyle);
		mItemList.push_front(tempItem);
// return index of newly inserted menu item
		return 1;
	}
	std::list<ItemInfo>::iterator itr;
	int nCount = 0;
// iterate through the list till we will not reach the given index
	for (itr = mItemList.begin(); nCount != index && itr != mItemList.end(); itr++,nCount++) {}
	
// insert menu item
	ItemInfo tempItem(itemID,aString,TEXT_RESOURCE_ID_NONE,textStyle);
	mItemList.insert(itr,tempItem);

// return index of newly inserted menu item
	return nCount+1;
}

int PopupMenu::addMenuItem(int itemID, int resourceID, Graphics::Style textStyle, int index)
{
// itemID must be greater than 2, we are using 1 for ITEM_UP_ARROW and 2 for ITEM_DOWN_ARROW for scrolling purpose
	if (itemID <= 2) {
		return 0;
	}

// Make sure the text style is always left justified, Otherwise text will be drawn 
// outside menu area
	if (Graphics::textStyle_Centered == (textStyle & Graphics::textStyle_Centered)) {
		textStyle = (Graphics::Style)(textStyle & (~Graphics::textStyle_Centered));
	}
	if (Graphics::textStyle_RightJustified == (textStyle & Graphics::textStyle_RightJustified)) {
		textStyle = (Graphics::Style)(textStyle & (~Graphics::textStyle_RightJustified));
	}


	std::string aString;

	loadString(aString,resourceID,-1);
// find the longest text in menu
	if (mLongestText.length() < aString.length()) {
		mLongestText = aString;
	}

	if (index < 0 || (unsigned)index >= mItemList.size()) // append item
	{
		ItemInfo tempItem(itemID,aString,resourceID,textStyle);
		mItemList.push_back(tempItem);
// return index of newly inserted menu item
		return mItemList.size();
	}
	if (index == 0)
	{
		ItemInfo tempItem(itemID,aString,resourceID,textStyle);
		mItemList.push_front(tempItem);
// return index of newly inserted menu item
		return 1;
	}
	std::list<ItemInfo>::iterator itr;
	int nCount = 0;
// iterate through the list till we will not reach the given index
	for (itr = mItemList.begin(); nCount != index && itr != mItemList.end(); itr++,nCount++) {}
	
// insert menu item
	ItemInfo tempItem(itemID,aString,resourceID,textStyle);
	mItemList.insert(itr,tempItem);

	// return index of newly inserted menu item
	return nCount+1;
}

bool PopupMenu::deleteMenuItemByItemID(int itemID)
{ 
	bool retval = false;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++)
	{
		ItemInfo item = *itr;
		if (item == itemID)
		{
			mItemList.erase(itr);
// if we deleted longest text in menu, find the second longest text
			if (mLongestText.length() == item.mItemString.length()) {
				setLongestText();
			}
			retval = true;
			break;
		}
	}
	return retval;
}

bool PopupMenu::deleteMenuItemByIndex(int index)
{
	bool retval = false;
	int count = 1;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++, count++)
	{
		ItemInfo item = *itr;
		if (index == count)
		{
			mItemList.erase(itr);
// if we deleted longest text in menu, find the second longest text
			if (mLongestText.length() == item.mItemString.length()) {
				setLongestText();
			}
			retval = true;
			break;
		}
	}
	return retval;
}

void PopupMenu::deleteAllMenuItems()
{
	mItemList.clear();
}

const char* PopupMenu::getItemStringByIndex(int index)
{
	int count = 1;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++, count++)
	{
		if (index == count)
		{
			ItemInfo item = *itr;
			return item.mItemString.c_str();						
		}
	}
	return NULL;
}

const char* PopupMenu::getItemStringByItemID(int itemID)
{
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++)
	{
		if (*itr == itemID)
		{
			return (*itr).mItemString.c_str();						
		}
	}
	return NULL;
}

bool PopupMenu::setStringByIndex(int index, const char* text)
{
	bool retval = false;
	int count = 1;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++, count++)
	{
		if (index == count)
		{
			(*itr).mItemString = std::string(text);
// set longest text in menu
			if (mLongestText.length() == (*itr).mItemString.length()) {
				mLongestText = (*itr).mItemString;
			}
			retval = true;
			break;
		}
	}
	return retval;
}

bool PopupMenu::setStringByItemID(int itemID, const char* text)
{
	bool retval = false;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++)
	{
		ItemInfo item = *itr;
		if (item == itemID)
		{
			(*itr).mItemString = std::string(text);
// set longest text in menu
			if (mLongestText.length() == (*itr).mItemString.length()) {
				mLongestText = (*itr).mItemString;
            }
			retval = true;
			break;			
		}
	}
	return retval;
}

bool PopupMenu::setStringByIndex(int index, int resourceID)
{
	bool retval = false;
	int count = 1;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++, count++)
	{
		if (index == count)
		{
			std::string aString;
			mResMgr.getString(aString, resourceID, -1);
			(*itr).mItemString = aString;
// set longest text in menu
			if (mLongestText.length() == (*itr).mItemString.length()) {
				mLongestText = (*itr).mItemString;
			}
			retval = true;
			break;
		}
	}
	return retval;
}

bool PopupMenu::setStringByItemID(int itemID, int resourceID)
{
	bool retval = false;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++)
	{
		ItemInfo item = *itr;
		if (item == itemID)
		{
			std::string aString;
			mResMgr.getString(aString, resourceID, -1);
			(*itr).mItemString = aString;
// set longest text in menu
			if (mLongestText.length() == (*itr).mItemString.length()) {
				mLongestText = (*itr).mItemString;
			}
			retval = true;
			break;
		}
	}
	return retval;
}

int PopupMenu::getIndex(int itemID)
{
	int retval = -1;
	int count = 1;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++, count++)
	{
		ItemInfo item = *itr;
		if (item == itemID)
		{
			retval = count;
			break;
		}
	}
	return retval;
}

int PopupMenu::getIndex(const char* text)
{
	int retval = -1;
	int count = 1;
	std::list<ItemInfo>::iterator itr;
	for (itr = mItemList.begin(); itr != mItemList.end(); itr++, count++)
	{
		if ((*itr).mItemString == std::string(text))
		{
			retval = count;
			break;
		}
	}
	return retval;
}

void PopupMenu::setTextSize(int nSize)
{
	assert(nSize > 0);
	mTextSize = nSize;
}

void PopupMenu::doMouseMove(const MouseInfo *mi, int id, int part)
{
	if (mi->leftButton)
	{
		if (mNeedScrolling) // && mScrollImages[0])
		{
			Point mousePoint = globalToLocal(mi->mousePos);
			if ( mViewArea.contains(localToGlobal(mousePoint)) )
			{
				if (mOldScrollPos.y < mousePoint.y) // scroll menu down
				{
					int menuScrolledBy = mousePoint.y - mOldScrollPos.y;
					int nInvisibleItem = mItemList.size() - mItemShowable;
					int scrollImageHeight = 0; //(mScrollImages[0]->height + IMAGE_HEIGHT_OFFSET) * 4;
					int oneScrollPt = (mViewArea.height() - scrollImageHeight)/nInvisibleItem;
					if (menuScrolledBy > oneScrollPt)
					{
						int scrollBy;
						// if all items are scrolled down, then scrolling should not happen
						if ( (int)mItemList.size()  != (mStartIndex - 1 + mItemShowable) )
						{
							scrollBy = (mousePoint.y / oneScrollPt) - (mStartIndex - 1);		
							mOldScrollPos = globalToLocal(mi->mousePos);
							scrollMenu(scrollBy);
						}
					}
					// if mouse is at last item of menu and last menu item 
					// is not last item of list we need to scroll menu downward
					else if ( (int)mItemList.size()  != (mStartIndex - 1 + mItemShowable))
					{
						Rect rect = View::getClickableRectFromID(part);
						itemRectPair val = mDrawableItemList.back();
						Rect tempRect = val.first;
						if (tempRect == rect)
						{
							if (mHotItem != part) {		
								mHotItem = part;
							}
							scrollMenu(1);
						}
					}
				}
				else if (mOldScrollPos.y > mousePoint.y) // scroll menu up
				{
					int menuScrolledBy = mOldScrollPos.y - mousePoint.y;
					int nInvisibleItem = mItemList.size() - mItemShowable;
					int scrollImageHeight = 0; //(mScrollImages[0]->height + IMAGE_HEIGHT_OFFSET) * 4;
					int oneScrollPt = (mViewArea.height() - scrollImageHeight)/nInvisibleItem;
					if (menuScrolledBy > oneScrollPt)
					{
						int scrollBy = (mousePoint.y / oneScrollPt) - (mStartIndex - 1);
						mOldScrollPos = globalToLocal(mi->mousePos);
						scrollMenu(scrollBy);
					}
					// if mouse is at first item of menu and first menu item 
					// is not first item of list we need to scroll menu upward
					else if (mStartIndex != 1)
					{
						Rect rect = View::getClickableRectFromID(part);
						itemRectPair val = mDrawableItemList.front();
						Rect tempRect = val.first;
						if (tempRect == rect)
						{
							if (mHotItem != part) {		
								mHotItem = part;
							}
							scrollMenu(-1);
						}
					}
				}
			}
		}
	}
	else
	{
		mOldScrollPos = globalToLocal(mi->mousePos);
		if (mHotItem != part)
		{
			mHotItem = part;
			draw();
		}
	}
}
void PopupMenu::doMouseLeave(const MouseInfo *mi,int id, int part)
{
	mHotItem = getPartClicked(OS::getMouse());
	draw();
}

void PopupMenu::doMouseEnter(const MouseInfo *mi,int id, int part)
{
}

int  PopupMenu::getPartClicked(const Point& screenPoint)
{
	return View::getPartClicked(screenPoint);
}

void PopupMenu::addDrawableItemPart(const Rect& rect, ItemInfo& item)
{
// Add the ID and ItemInfo pair to our list
	itemRectPair val( rect, item );
	mDrawableItemList.push_back( val );
}
void PopupMenu::hide()
{
	
	View::hide();
}

} // namespace pdg

