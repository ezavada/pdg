// -----------------------------------------------
// PopupMenu.h
// 
// Definitions for drawing a PopupMenu
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_POPUP_MENU_H_INCLUDED
#define PDG_POPUP_MENU_H_INCLUDED

#include "pdg/framework.h"

#include <vector>
#include <list>

#define ITEM_SIZE_OFFSET		8
#define TEXT_WIDTH_OFFSET		10
#define IMAGE_HEIGHT_OFFSET		4
#define VIEW_HEIGHT_OFFSET		20
#define VIEW_WIDTH_OFFSET		12
#define VIEW_HSHIFT_OFFSET		3
#define MAX_ARROW_IMAGES		2
#define TEXT_LEFT_MARGIN		2
#define HIGHLIGHT_AREA_MARGIN	2
#define CLIP_TEXT				"..."
#define RES_MENU_IMAGES			143
#define TEXT_RESOURCE_ID_NONE	-1
#define MAX_MENU_WIDTH			200
// id's for scrolling
#define ITEM_UP_ARROW			1
#define ITEM_DOWN_ARROW			2
#define RES_PULL_ARROW 4

#define START_INDEX_NONE		-1
#define HOT_ITEM_NONE			-1

namespace pdg {

class ItemInfo
{
public:

	std::string mItemString;
	int mResourceID;
	int mItemID;
	Graphics::Style mStyle;

	ItemInfo(int itemID, std::string& text ,int resourceID = -1, Graphics::Style textStyle = (Graphics::Style)(Graphics::textStyle_Plain + Graphics::textStyle_LeftJustified))
	:mItemString(text.c_str()),mResourceID(resourceID),mItemID(itemID),mStyle(textStyle){}

	~ItemInfo() {}

	bool operator ==( const ItemInfo& item2)
	{
		if ( mItemString == item2.mItemString && mResourceID == item2.mResourceID && mItemID == item2.mItemID)
			return true;
		else
			return false;		
	}

	bool operator ==( const std::string& string2)
	{
		if(mItemString == string2)
			return true;
		else
			return false;
	}

	bool operator ==( int itemID)
	{
		if(mItemID == itemID)
			return true;
		else
			return false;
	}
};


class PopupMenu : public View
{
private:

    ResourceManager& mResMgr;
	typedef std::pair< Rect, ItemInfo > itemRectPair;
	typedef std::vector< itemRectPair > DrawableList;
	
	DrawableList mDrawableItemList;// list of rect and item viewable in view area.
	// in case of scrollable menu, the last rect will show, up and down arrows.

	// following variable will help in creating scrollable menu
	int mStartIndex; // It will store starting index of item viewable in view area
	
	// This variable helps for autosizing width of menu
	std::string mLongestText;

	std::list<ItemInfo> mItemList;
	Color mbkColor;
	Color mTextColor;
	Color mhighlightColor;
	int mHotItem; // item under selection
	int mTextSize;
	int mItemShowable;
	bool mNeedScrolling, mShowUpArrow, mShowDownArrow ;
	Point mOldScrollPos;
//	Image* mScrollImages[MAX_ARROW_IMAGES + MAX_ARROW_IMAGES];
	Image* mPullArrowImage;
	int mMinWidth;
	Rect mBaseRect;

public:

	PopupMenu(Controller* controller, Point topLeft = Point(0,0), Color bkColor = Color(0xCC,0xCC,0xCC), Color sTextColor = Color(0,0,0), Color highlightColor = Color(0,0,0xFF), int nTextSize = 14);
	PopupMenu(Controller* controller, Rect topLeft, Color bkColor = Color(0xCC,0xCC,0xCC), Color sTextColor = Color(0,0,0), Color highlightColor = Color(0,0,0xFF), int nTextSize = 14);
	~PopupMenu();

	int addMenuItem(int itemID, int resourceID,
		Graphics::Style textStyle = (Graphics::Style)(Graphics::textStyle_Plain + Graphics::textStyle_LeftJustified), int index = -1);

	int addMenuItem(int itemID, const char* text,
		Graphics::Style textStyle = (Graphics::Style)(Graphics::textStyle_Plain + Graphics::textStyle_LeftJustified), int index = -1);

	bool deleteMenuItemByItemID(int itemID);
	bool deleteMenuItemByIndex(int index);
	void deleteAllMenuItems();

	const char* getItemStringByItemID(int itemID);
	const char* getItemStringByIndex(int index);

	bool setStringByIndex(int index, const char* text);
	bool setStringByItemID(int itemID, const char* text);
	bool setStringByIndex(int index, int resourceID);
	bool setStringByItemID(int itemID, int resourceID);

	int getIndex(int itemID);
	int getIndex(const char* text);

	void drawSelf();     
	void showSelf(); 
	void doMouseMove(const MouseInfo *mi, int id, int part);
	void doMouseLeave(const MouseInfo *mi,int id, int part);
	void doMouseEnter(const MouseInfo *mi,int id, int part);
	int  getPartClicked(const Point& screenPoint); // returns itemID of part clicked.
	void scrollMenu(int nItems); // scroll menu by nItems up or down. If +ve scroll down, -ve scroll up.
	void sanitiseViewArea();
	void setTextSize(int nSize);
	void hide();

protected:
	void loadImages();
	void loadString(std::string& aString,int resourceID, int numStrings);
	void addDrawableItemPart(const Rect& rect, ItemInfo& item);
	void calcClickableAreas();
	void setLongestText();
};

} // close namespace pdg

#endif // PDG_POPUP_MENU_H_INCLUDED

