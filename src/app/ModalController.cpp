// -----------------------------------------------
// ModalController.cpp
// 
// Implementation of a base class to manage views
// and handle events
//
// Written by Nick Laiacona and Ed Zavada, 2010-2012
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

#include "pdg/app/ModalController.h"
#include "pdg/sys/graphics.h"

namespace pdg {

// redraw all of the views for active controllers, starting with
// our deepest descendents and working our way up.
void ModalController::redrawAll() {

	if (!isActive()) return;
	
	pdg::Controller::redrawAll();

#if 0
	// recursively traverse to the deepest controller child
	Children::iterator citr;
	for(citr = mChildren.begin(); citr != mChildren.end(); citr++) {
		Controller* child = *citr;
		if( child->isActive() ) 
			child->redrawAll();
	}
	
	// render this controller and all its views
	if( isActive() ) 
		redrawSelf(mPort->getDrawingArea());
#endif

}

ModalController::ModalController(Application* app, bool wantKeyUpDown, bool wantKeyPress, 
								 bool wantMouseEnterLeave, bool wantAll)
	: pdg::Controller(app,wantKeyUpDown,wantKeyPress,wantMouseEnterLeave,wantAll, kDontDrawWhileInactive) {
}

} // namespace pdg
