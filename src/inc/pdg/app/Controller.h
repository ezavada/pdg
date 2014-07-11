// -----------------------------------------------
// Controller.h
// 
// Definition of a class that manages views and
// handles keyboard and mouse events
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_CONTROLLER_H_INCLUDED
#define PDG_CONTROLLER_H_INCLUDED

#include <vector>

#include "pdg/sys/platform.h"
#include "pdg/sys/core.h"
#include "pdg/sys/refcounted.h"
#include "pdg/sys/events.h"
#include "pdg/app/Application.h"

#if defined (COMPILER_MSVC) && (COMPILER_MSVC < 1300)
	#define GETVIEW(controller, type, id) dynamic_cast<type*>(controller->getUntypedView(id))
#else
	#define GETVIEW(controller, type, id) controller->getView<type>(id)
#endif


namespace pdg {

enum {
	kDrawWhileInactive = true,
	kDontDrawWhileInactive = false,
	kWantKeyUpDownEvents = true,
	kDontWantKeyUpDownEvents = false,
	kWantKeyPressEvents = true,
	kDontWantKeyPressEvents = false,
	kWantMouseEnterLeaveEvents = true,
	kDontWantMouseEnterLeaveEvents = false,
	kWantAllEvents = true,
	kDontWantAllEvents = false
};

class View;
class Port;

class Controller : public RefCountedImpl< IEventHandler > {
public:
	virtual void addView(const View* view, int id = -1); // assigning an id is optional
	virtual void addViewBehind(const View* view, int id = -1); // behind all other views, id is optional
	virtual void removeView(const View* view);

	void removeView(int id) { removeView(getUntypedView(id)); }	
	void removeAllViews();  // remove absolutely all the views from the controller
	
	View* getUntypedView(int id); // will only fetch views that were assigned non-zero id

    template <class T> T* getView(int id) { return dynamic_cast<T*>(getUntypedView(id)); }

	Application& getApplication() throw(no_manager) { if (!mApp) throw no_manager(); return *mApp; }
	
	Controller& getTopController(); // traverse the parents until a controller with no parent is found and return it

    virtual bool startDrawing();    // don't do any redraws for a while, we are drawing
    virtual void doneDrawing(bool wasDrawing);     // do needed redraws now, we are done drawing
    
	virtual void redraw();      // standard redraw of all views in this controller
	
    virtual void viewRedrawn(View* view); // one or more views in this controller were redrawn, fix children
	virtual void redrawAll();   // redraw entire controller heirarchy

	virtual void redrawSelf(Rect areaAffected = Rect(0,0));  // don't call, just extend if needed to draw special stuff

	virtual bool doMouseDown(const MouseInfo *mi, View* view, int id, int part);
	virtual bool doMouseUp(const MouseInfo *mi, View* view, int id, int part);

	virtual void doMouseEnter(const MouseInfo *mi, View* view, int id, int part);
	virtual void doMouseLeave(const MouseInfo *mi, View* view, int id, int part);
	virtual void doMouseMove(const MouseInfo *mi, View* view, int id, int part);

    virtual bool doLeftClick(const MouseInfo *mi, View* view, int id, int part);
    virtual bool doRightClick(const MouseInfo *mi, View* view, int id, int part);
    virtual bool doDoubleClick(const MouseInfo *mi, View* view, int id, int part, int clickCount);
    
	virtual bool doDragMove(const MouseInfo *mi, View* view, int id, int part);
	virtual bool doDragIn(const MouseInfo* mi, View* view, int id, int part, View* targetView, int targetId, int targetPart);
	virtual bool doDragOut(const MouseInfo* mi, View* view, int id, int part, View* targetView, int targetId, int targetPart);
	virtual bool startBeingDragTarget(const MouseInfo* mi, View* view, int id, int part, View* draggedView, int draggedId, int draggedPart);
    virtual bool stopBeingDragTarget(const MouseInfo* mi, View* view, int id, int part, View* draggedView, int draggedId, int draggedPart);
	virtual bool doDragComplete(const MouseInfo *mi, View* view, int id, int part);
	
    virtual void portWasResized(Port* resizedPort);
    
    // for a controller we own trying to close
    virtual bool attemptChildClose(Controller* child, bool cancelled);
    // for a controller we own becoming active
    virtual void childActivated(Controller* child);

    // tell a controller it has a new child
    virtual void addChild(Controller* child);
    
    // tell a controller the child has left home
    virtual void removeChild(Controller* child);

    // an inactive Controller doesn't get input events (mouse, keyboard). Controllers are active by default.
    virtual void setActive(bool active);
    bool         isActive() { return mActive; }
    
    // following return true if handled
    virtual bool doKeyDown(const KeyInfo* ki, View* view, int id, int part);    // view is where mouse is located
    virtual bool doKeyUp(const KeyInfo* ki, View* view, int id, int part); 
    virtual bool doKeyPress(const KeyPressInfo* ki, View* view, int id, int part);

    virtual bool handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw();  // return true if completely handled

    Controller(Application* theApp, bool wantKeyUpDown = true, bool wantKeyPress = true, bool wantMouseEnterLeave = true, bool wantAll = false, bool drawInactive = true);
    virtual ~Controller();

protected:    

	typedef std::pair< View*, int > idViewPair;
	typedef std::vector< idViewPair > ViewList;
	typedef std::vector< Controller* > Children;

    Application* mApp;
    ViewList    mViews;
    Children    mChildren;
    Controller* mParent;
    Port*       mPort;  // the primary port this controller controls. Subclasses could add additional ports if needed.
    View*       mLastClicked;
    int         mClickCount;
    bool        mRightClick;
    bool        mActive;
    bool        mDrawing;
    bool        mWantsAllEvents;
	bool        mDrawInactive;
	View *		mViewOnLastMouseMoved;// last view on which mouse moved
	int			mLasthitViewID;
	int			mLasthitViewPart;
	Rect		mCachedPortDrawingArea;
    
private:
    void    setParent(Controller* parent) { mParent = parent; } // only call from add/removeChild(), thus it is private
};


} // end namespace pdg


#endif // PDG_CONTROLLER_H_INCLUDED


