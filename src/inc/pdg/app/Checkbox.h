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


class Checkbox : public View, public Subject
{
public:

	enum ClickIDs
	{
		CLICK_ID_CHECKBOX
	};

    Checkbox(Controller* controller, const Rect& viewArea);
	~Checkbox();

	void drawSelf() override;
	void calcClickableAreas();
	bool isChecked() { return mIsChecked; }
	void setChecked(bool checked) { mIsChecked = checked; }
	void setString(const std::string& str);
	void setTextSize(int pointSize) { mTextSize = pointSize; }
	void doClick(int part);
	bool doLeftClick(const MouseInfo* mi, int id, int part) override;
	void setClickSound(Sound* clickSound);
	void setAttributes(const ControlAttributes& attributes);
	const ControlAttributes& getAttributes() const { return mAttributes; }

protected:
	bool mIsChecked;
	std::string mString;
	int  mTextSize;
	ControlAttributes mAttributes;
};

} // end namespace pdg


#endif // PDG_CHECKBOX_H_INCLUDED
