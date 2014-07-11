// -----------------------------------------------
// TouchController.h
// 
// Definition of a class that manages views and
// handles keyboard and mouse events
//
// Copyright (c) 2010, Dream Rock Studios, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_TOUCHCONTROLLER_H_INCLUDED
#define PDG_TOUCHCONTROLLER_H_INCLUDED

#include "pdg/app/ModalController.h"

// larger means faster decay - TODO make these configurable
#define FLICK_DECAY_FACTOR 3.0f
#define FLICK_MAX_MOUSE_UNMOVED_MS 200

// TODO make this configurable
#define	FLICK_FRAME_RATE 16 

namespace pdg {

class TouchController : public pdg::ModalController {

public:
	TouchController(Application* theApp, bool wantKeyUpDown = true, bool wantKeyPress = true, bool wantMouseEnterLeave = true, bool wantAll = false);
	
	virtual bool doMouseDown(const pdg::MouseInfo *mi, pdg::View* view, int id, int part);
	virtual bool doMouseUp(const pdg::MouseInfo *mi, pdg::View* view, int id, int part);
	virtual void doMouseMove(const pdg::MouseInfo *mi, pdg::View* view, int id, int part);	
	virtual void removeView(const View* view);
	
	virtual bool doTouch( const pdg::MouseInfo *mi, pdg::View* view, int id, int part);
	virtual bool doTap( const pdg::MouseInfo *mi, pdg::View* view, int id, int part);	
	virtual bool doTouchMove( const pdg::Point& delta, bool flick, pdg::View* view, int id, int part);
	virtual bool doSwipeMove( const pdg::Point& delta, pdg::View* view, int id, int part);
	virtual bool doPinchMove( const pdg::Point& delta1, const pdg::Point& delta2, float distance, float deltaDistance, pdg::View* view, int id, int part);
	virtual bool doSnapback(uint32 msSinceLastSnapback, uint32 msSinceMouseUp, pdg::View* view, int id, int part);
		
	virtual bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled
	
	void stopFlick();
	
protected:
	bool mMouseDown, mLastMousePositionRecorded;
	Point mLastMousePosition;
	MouseInfo mMouseDownInfo;
	
private:
	PointT<float> mFlickVelocity;
	View* mFlickView;
	View* mSnapbackView;
	int mFlickPart;
	int mFlickID;
	int mSnapbackID;
	int mSnapbackPart;
	uint32 mLastMovedMs;
	uint32 mLastSnapbackMs;
	uint32 mLastMouseUpMs;
	
};


} // end namespace pdg


#endif // PDG_TOUCHCONTROLLER_H_INCLUDED


