// -----------------------------------------------
// ListBox.h
// 
// Definitions for drawing a ListBox
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_LIST_BOX_H_INCLUDED
#define PDG_LIST_BOX_H_INCLUDED

#include "pdg/app/View.h"

namespace pdg {

class Scrollbar;

class ListBox : public View
{
public:

	enum ClickIds
	{
		VIEW_ID_LIST_BOX_SCROLLBAR,
		VIEW_ID_SELECTION_START
	};

	enum SelectionIds
	{
		NO_SELECTION = -1
	};

    ListBox(Controller* controller, const Rect& viewArea, int textLines, const Color& bkcolor, const Color& htcolor);
	~ListBox();

	void addToList(const char* text, const Color& fgcolor = PDG_BLACK_COLOR ); //, const Color& bgcolor
	void clear(); // Clears all entries in list box
	void loadImages();
	void calcClickableAreas();
	virtual void drawSelf();
	int getSelectedIndex() { return mSelectedIndex; }
	void doClick(int part);

	virtual void notify(Subject* subject);
	const char* getTextFromIndex(int index);
	bool doKeyPress(const KeyPressInfo* ki, View* view, int id, int part);
	
private:
	class ListBoxLine
	{
	public:
		ListBoxLine() {}
		~ListBoxLine() {}

		char* text;
		Color fgcolor;
		Color bgcolor;
	};

    ResourceManager& mResMgr;
	Controller* mParentController;

	int mSelectedIndex;
	std::vector<ListBoxLine> mListText;
	Scrollbar* mScrollbar;
	int mWindowTopLineIndex;
	int mVisibleTextLines;
	Color mHtColor;
	Color mBkColor;
};

} // close namespace pdg

#endif // PDG_LIST_BOX_H_INCLUDED

