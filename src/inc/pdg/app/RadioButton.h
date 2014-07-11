// -----------------------------------------------
// RadioButton.h
// 
// Definitions for drawing a RadioButton
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_RADIO_BUTTON_H_INCLUDED
#define PDG_RADIO_BUTTON_H_INCLUDED

#include "pdg/app/View.h"

#define MAX_RADIO_IMAGES 2

namespace pdg {

class RadioButton : public View
{
public:

    RadioButton(Controller* controller, const Rect& viewArea, int resourceTextID, int numStrings);
	~RadioButton();

	void loadImages();
	void loadStrings(int resourceID, int numStrings);
	void calcClickableAreas();
	virtual void drawSelf();
	int getSelectedIndex() { return mSelectedIndex; }
	void setSelectedIndex(int selected) { mSelectedIndex = selected; }
	void doClick(int part);

private:
    ResourceManager& mResMgr;
	Image* mpRadioImages[MAX_RADIO_IMAGES];
	int mSelectedIndex;
	std::string* mStrings;
	int   mMaxStrings;

};

} // close namespace pdg

#endif // PDG_RADIO_BUTTON_H_INCLUDED

