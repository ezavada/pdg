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
#include "ViewUtils.h"
#include "pdg/sys/attributes.h"

#ifndef MESSAGE_TEXT_COLOR
  #define MESSAGE_TEXT_COLOR PDG_BLACK_COLOR
#endif

namespace pdg {


const int BORDER_SPACER		= 10;
const int MESSAGE_TEXT_SIZE  = 18;

MessageView::MessageView(Controller* controller, const Rect& viewRect, std::string& message) :
	View(controller, viewRect), mMessageString(message)
{
}

MessageView::~MessageView()
{
}


void MessageView::drawSelf()
{
	// Fill in header text
	Rect textArea = Rect(BORDER_SPACER, BORDER_SPACER, mViewArea.width() - BORDER_SPACER, mViewArea.height() - BORDER_SPACER);
	
	// Draw string
	app::drawMultilineText(mPort, mMessageString.c_str(), MESSAGE_TEXT_SIZE, MESSAGE_TEXT_COLOR, localToGlobal(textArea));
}

} // namespace pdg
