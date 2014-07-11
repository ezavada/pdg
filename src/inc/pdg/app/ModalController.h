// -----------------------------------------------
// ModalController.h
// 
// Definition of a class that manages views and
// handles keyboard and mouse events
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_MODALCONTROLLER_H_INCLUDED
#define PDG_MODALCONTROLLER_H_INCLUDED

#include "pdg/app/Controller.h"

namespace pdg {

class View;
class Port;

	class ModalController : public pdg::Controller {
public:
	virtual void redrawAll();   // redraw entire controller heirarchy depth first, active controllers only	
	ModalController(Application* theApp, bool wantKeyUpDown = true, bool wantKeyPress = true, bool wantMouseEnterLeave = true, bool wantAll = false);
};


} // end namespace pdg


#endif // PDG_MODALCONTROLLER_H_INCLUDED


