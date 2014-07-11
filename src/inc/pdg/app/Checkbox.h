// -----------------------------------------------
// Checkbox.h
// 
// Definitions for drawing a Checkbox
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_CHECKBOX_H_INCLUDED
#define PDG_CHECKBOX_H_INCLUDED

#include "pdg/framework.h"


namespace pdg {


class Checkbox : public View
{
public:

	enum ClickIDs
	{
		CLICK_ID_CHECKBOX
	};

    Checkbox(Controller* controller, const Rect& viewArea);
	~Checkbox();

	void loadImages();
	void drawSelf();
	void calcClickableAreas();
	bool isChecked() { return mIsChecked; }
	void setChecked(bool checked) { mIsChecked = checked; }
	void setString(const std::string& str);
	void setTextSize(int pointSize) { mTextSize = pointSize; }
	void doClick(int part);
	void setClickSound(Sound* clickSound);

protected:
	enum CBImages
	{
		OPEN,
		CLOSED,
		NUM_CHECKBOX_IMAGES
	};

    ResourceManager& mResMgr;
	Image* mpCheckboxImages[NUM_CHECKBOX_IMAGES];
	Sound* mpClickSound;

	bool mIsChecked;
	std::string mString;
	int  mTextSize;
};

} // end namespace pdg


#endif // PDG_CHECKBOX_H_INCLUDED

