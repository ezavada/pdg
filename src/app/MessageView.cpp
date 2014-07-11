// -----------------------------------------------
// MessageView.cpp
// 
// Implementation for drawing a card selection dialog
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

#include "pdg/framework.h"
#include "pdg/app/MessageView.h"

#ifndef PDG_ALLOW_DEPRECATED_CALLS
#error You must define PDG_ALLOW_DEPRECATED_CALLS in your project to use MessageView.cpp
#endif

// TODO: remove these catan specific things
#if (defined(CATAN_CLIENT) || defined(CATAN_STANDALONE))
  #include "CatanUIConsts.h"  // for colors
  #define MESSAGE_BACKGROUND_COLOR CATAN_PARCHMENT_COLOR
#endif 

#ifndef MESSAGE_BACKGROUND_COLOR
  #define MESSAGE_BACKGROUND_COLOR PDG_WHITE_COLOR
#endif
#ifndef MESSAGE_TEXT_COLOR
  #define MESSAGE_TEXT_COLOR PDG_BLACK_COLOR
#endif

namespace pdg {


const int BORDER_SPACER		= 10;
const int MESSAGE_TEXT_SIZE  = 18;

MessageView::MessageView(Controller* controller, const Rect& viewRect, std::string& message) :
	View(controller, viewRect), mMessageString(message)
{
	loadImages();
}

MessageView::~MessageView()
{
}


void MessageView::loadImages()
{

}
	
void MessageView::drawSelf()
{
	mPort->fillRect(mViewArea, MESSAGE_BACKGROUND_COLOR);
	// Fill in header text
	Rect textArea = Rect(BORDER_SPACER, BORDER_SPACER, mViewArea.width() - BORDER_SPACER, mViewArea.height() - BORDER_SPACER);
	
	// Draw string
	this->drawMultilineText(mMessageString.c_str(), MESSAGE_TEXT_SIZE, MESSAGE_TEXT_COLOR, localToGlobal(textArea));
}

} // namespace pdg
