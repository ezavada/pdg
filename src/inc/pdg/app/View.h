// -----------------------------------------------
// View.h
// 
// Base class for Views
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_VIEW_H_INCLUDED
#define PDG_VIEW_H_INCLUDED

#include "pdg/sys/coordinates.h"
#include "pdg/sys/refcounted.h"
#include "pdg/sys/events.h"
#include "pdg/sys/graphics.h"
#include "pdg/app/Observer.h"

#include <vector>


namespace pdg {


class ResourceManager;
class Controller;

class View : public RefCountedObj, public IObserver
{
public:

	enum ClickablePartsIDs
	{
		CLICKED_PART_NONE = -1
	};
	
	enum {
        bind_Top      = 1 << 3,   // when port shrinks or grows keep top edge of view a fixed distance from top of port
        bind_Bottom   = 1 << 4,   // when port shrinks or grows keep bottom edge of view a fixed distance from bottom of port
        bind_Left     = 1 << 5,   // when port shrinks or grows keep left edge of view a fixed distance from left side of port
        bind_Right    = 1 << 6,   // when port shrinks or grows keep right edge of view a fixed distance from right side of port
		grow_Horz	= bind_Left | bind_Right,  // when port shinks or grows, keep fixed distance from left and right of port, growing or shrinking view horizontally as needed
		grow_Vert	= bind_Top | bind_Bottom,  // when port shinks or grows, keep fixed distance from top and bottom of port, growing or shrinking view vertically as needed
		grow        = grow_Horz | grow_Vert     // keep fixed margins from the port edges, growing or shrinking as needed
	};

    View(Controller* controller, const Rect& rect, int viewBinding = 0); // port taken from controller
    View(Controller* controller, Port* port, const Rect& rect, int viewBinding = 0);
	virtual ~View();

	template <class T> T* getController() { return dynamic_cast<T*>(mController); }
	
	virtual void draw();
	
	virtual void drawSelf() = 0;

    virtual void hideSelf();  // override to do something when hidden
    virtual void showSelf();  // override to do something when made visible
	
// ============================ Mouse Primatives ============================
	// doMouseDown is called whenever the mouse button goes down within the view
	virtual bool doMouseDown(const MouseInfo *mi, int id, int part);
	
	// doMouseUp is called whenever the mouse button goes up within the view
	virtual bool doMouseUp(const MouseInfo *mi, int id, int part);
	
	// doMouseMove is called whenever the mouse moves within the view, if the view wants mouseovers
	virtual void doMouseMove(const MouseInfo *mi, int id, int part);
	
	// doMouseEnter is called whenever the mouse enter the view, if the view wants mouseovers
	virtual void doMouseEnter(const MouseInfo *mi, int id, int part);
	
	// doMouseLeave is called whenever the mouse exits the view, if the view wants mouseovers
	virtual void doMouseLeave(const MouseInfo *mi, int id, int part);

// ============================ Mouse Actions ============================
    virtual bool doLeftClick(const MouseInfo *mi, int id, int part);
    virtual bool doRightClick(const MouseInfo *mi, int id, int part);
	virtual bool doDoubleClick(const MouseInfo *mi, int id, int part, int clickCount);

// ============================ Gestures	============================
	// Gestures are only generated by a TouchController, the base Controller class will not generate them
	
	// doTap is called when a finger goes up and down within the view
	// return true if completely handled, or false if the tap can be passed on to other views
	virtual bool doTap( const MouseInfo *mi, int id, int part);
	
	// doTouchMove is called when a finger that went down in the view moves within the view, or
	// after it was released within the view as part of a flick gesture (in which case flick will be true)
	// NOTE: if the finger exits the view while still down, doTouchMove is no longer called. Then doDragMove 
	// is called instead if the view is draggable
	// return true if completely handled, or false if the tap can be passed on to other views
	virtual bool doTouchMove( const Point& delta, bool flick, int id, int part);
	
	// doSwipeMove happens when two or more fingers are down in the view and move in unison (ie, all in 
	// the same direction)
	// return true if completely handled, or false if the tap can be passed on to other views
	virtual bool doSwipeMove( const Point& delta, int fingerCount, int id, int part); 
	
	// doPinchMove happens when two fingers are down in the view and move together or apart
	// return true if completely handled, or false if the tap can be passed on to other views
	virtual bool doPinchMove( const Point& delta1, const Point& delta2, float distance, float deltaDistance, int id, int part);

// ============================ Drag Actions ============================ 
	// No drag actions will be called unless the view is set to be draggable
	
	// doDragMove is called when the mouse when down within the view and is now moving while held down
	// it will also be called when the TouchMove gesture exits the view, but the finger remains down
	virtual bool doDragMove(const MouseInfo *mi, int id, int part);
	
	// doDragIn is called when the mouse when down within the view and first moves over another view (the target view)
	virtual bool doDragIn(const MouseInfo* mi, int id, int part, View* targetView, int targetId, int targetPart);

	// doDragOut is called when the mouse when down within the view and first moves out of another view (the 
	// target view). It is always preceeded by a doDragOut call
	virtual bool doDragOut(const MouseInfo* mi, int id, int part, View* targetView, int targetId, int targetPart);

	// startBeingDragTarget is called when the mouse went down in another view (the dragged view) and first moves 
	// into this view
	virtual bool startBeingDragTarget(const MouseInfo* mi, int id, int part, View* draggedView, int draggedId, int draggedPart);

	// stopBeingDragTarget is called when the mouse went down in another view (the dragged view) and moves out
	// of this view. It is always preceeded by a startBeingDragTarget call
    virtual bool stopBeingDragTarget(const MouseInfo* mi, int id, int part, View* draggedView, int draggedId, int draggedPart);

	// doDragComplete is called with the mouse is released after a series of drag related calls
	virtual bool doDragComplete(const MouseInfo *mi, int id, int part);


    virtual void notify(Subject* subject);  // override to handle when a thing we are observing changes

	void setViewArea(const Rect& rect); // in global/port coordinates
	const Rect& getViewArea() const { return mViewArea; } // in global/port coordinates
	Rect& getModifiableViewAreaRect() { return mViewArea; } // in global/port coordinates
	
	virtual bool pointInViewVisibleArea(const Point& screenPoint); // in global/port coordinates
	
	bool pointInViewArea(const Point& screenPoint) { return mViewArea.contains(screenPoint); } // in global/port coordinates

	virtual int  getPartClicked(const Point& screenPoint); // in global/port coordinates
	virtual Rect getClickableRectFromID(int id);
	void addClickablePart(const Rect& rect, int id);
	void removeClickablePart(int id);

	void drawClickableParts();
	
	Port* getPort() { return mPort; }
	Port* setPort(Port* newPort) { Port* port = mPort; mPort = newPort; return port; }
	
	virtual void portResized(const Rect& oldDrawingArea, const Rect& newDrawingArea);

    void hide();
    void show();
    bool isVisible() { return mVisible; }
    bool isEnabled() { return mIsEnabled; }
	bool isDraggable() { return mIsDraggable; }
	bool wantsMouseOvers() { return mWantsMouseOvers; }
	void setEnabled(bool enabled);
	void setDraggable(bool isDraggable);
	void setWantsMouseOvers(bool wantsMouseOvers);
	
	// these are only used when resizing because the port size changed
	void setMinSize(PDG_BASE_COORD_TYPE minWidth, PDG_BASE_COORD_TYPE minHeight) { mMinWidth = minWidth; mMinHeight = minHeight; }
	void setMaxSize(PDG_BASE_COORD_TYPE maxWidth, PDG_BASE_COORD_TYPE maxHeight) { mMaxWidth = maxWidth; mMaxHeight = maxHeight; }
	
#ifdef PDG_ALLOW_DEPRECATED_CALLS
	// FIXME: drawMultilineText() belongs in port, not in view
	int drawMultilineText(const char* text, int size, Color color, const Rect& textArea, int style = Graphics::textStyle_Plain + Graphics::textStyle_Centered);
#endif

	// About Coordinate Systems:
	
	// The View Area is the area into which your view is expected to draw (this is not enforced, 
	// so it is possible to draw outside your view area) 
	// Note that Controllers won't check to see if mouse events outside the View Area affect the View
	
	// Local Coordinates are relative to top left of View Area (as returned by getViewArea() )
	
	// The port's Drawing Area is the drawable area in Global Coordinates that the Port supports (as returned by mPort->getDrawingArea() )
	// Global Coordinates are relative to top left of Port (same as top right of screen in full screen mode)
	
	// All drawing commands in a port take Global Coordinates
	
	// It is recommended that your drawing calculations all be done in Local Coordinates, then converted to global via
	// the localToGlobal() calls at the time that you call actual drawing methods of the Port
	
    // coordinate transforms, local view coords --> global drawing coords
    Point   localToGlobal(Point inPt);
    Rect    localToGlobal(Rect inRect);
    
    // coordinate transforms, global drawing coords --> local view coords
    Point   globalToLocal(Point inPt);
    Rect    globalToLocal(Rect inRect);
	
protected:

#ifdef PDG_ALLOW_DEPRECATED_CALLS
	// FIXME: these don't belong in view
	Image*  loadImage(ResourceManager& resMgr, int id, int idx = 0, Color* transparentColor = NULL);
	void    loadImageArray(ResourceManager& resMgr, Image* arr[], int id, int numImages, Color* transparentColor = NULL);
	void    unloadImage(Image* & imagePtr);
	void    unloadImageArray(Image* arr[], int numImages);

	// FIXME: these don't belong in view
	void    scaleImage(Image*& image, float scaleBy, Image::FilterType filter = Image::filter_Best);
    void    scaleImageArray(Image* arr[], int numImages, float scaleBy, Image::FilterType filter = Image::filter_Best);
    void    scaleImageArrayToFit(Image* arr[], int numImages, Rect r, Image::FilterType filter = Image::filter_Best);
#endif // PDG_ALLOW_DEPRECATED_CALLS

    Controller* mController;
    Port*   mPort;  // the graphics port in which this view is drawn
	Rect mViewArea;

	typedef std::pair< Rect, int > idRectPair;
	typedef std::vector< idRectPair > ClickableList;

	ClickableList mClickableParts;
    bool mVisible;
	bool mIsEnabled;
	bool mIsDraggable;
	bool mWantsMouseOvers;
	
	int mBinding;
	PDG_BASE_COORD_TYPE mMinWidth;
	PDG_BASE_COORD_TYPE mMinHeight;
	PDG_BASE_COORD_TYPE mMaxWidth;
	PDG_BASE_COORD_TYPE mMaxHeight;

private:

	// Disallow default construction 
	View();
};

} // end namespace pdg


#endif // PDG_VIEW_H_INCLUDED


