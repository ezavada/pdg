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
#include "pdg/app/ControlAttributes.h"

#include <string>

namespace pdg {

class RadioButton : public View, public Subject
{
public:

    RadioButton(Controller* controller, const Rect& viewArea, int resourceTextID, int numStrings);
	~RadioButton();

	void loadStrings(int resourceID, int numStrings);
	void setString(int index, const std::string& value);
	void calcClickableAreas();
	void drawSelf() override;
	int getSelectedIndex() { return mSelectedIndex; }
	void setSelectedIndex(int selected) { mSelectedIndex = selected; }
	void doClick(int part);
	bool doLeftClick(const MouseInfo* mi, int id, int part) override;
	void setAttributes(const ControlAttributes& attributes);
	void setClickSound(Sound* clickSound) { mAttributes.clickSound(clickSound); }
	const ControlAttributes& getAttributes() const { return mAttributes; }

private:
    ResourceManager& mResMgr;
	int mSelectedIndex;
	std::string* mStrings;
	int   mMaxStrings;
	ControlAttributes mAttributes;

};

} // close namespace pdg

#endif // PDG_RADIO_BUTTON_H_INCLUDED
