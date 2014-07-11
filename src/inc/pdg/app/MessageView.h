// -----------------------------------------------
// MessageView.h
// 
// Definitions for a view that can draw a text message
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_MESSAGEVIEW_H_INCLUDED
#define PDG_MESSAGEVIEW_H_INCLUDED

#include "pdg/app/View.h"

#include <string>

namespace pdg {

class MessageView : public View
{
public:

	MessageView(Controller* controller, const Rect& viewRect, std::string& message);
	~MessageView();

	void loadImages();
	void drawSelf();

private:
	std::string mMessageString;
};

} // close namespace pdg

#endif // PDG_MESSAGEVIEW_H_INCLUDED

