// -----------------------------------------------
// View.cpp
//
// Implementation for base class View
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

#include "pdg/sys/resource.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/os.h"
#include "pdg/sys/attributes.h"
#include "pdg/app/View.h"
#include "pdg/app/Controller.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace pdg {

View::View(Controller* controller, const Rect& rect, int binding)
 : mController(controller),
   mPort(controller->getApplication().getGraphicsManager().getMainPort()), // get port from Controller
   mVisible(true), mIsEnabled(true), mIsDraggable(false), mWantsMouseOvers(false),
   mBinding(binding)
{
	setViewArea(rect);
	setMinSize(0, 0);
	setMaxSize(0, 0);
}

View::View(Controller* controller, Port* port, const Rect& rect, int binding)
 : mController(controller),
   mPort(port),
   mVisible(true), mIsEnabled(true), mIsDraggable(false), mWantsMouseOvers(false),
   mBinding(binding)
{
    setViewArea(rect);
	setMinSize(0, 0);
	setMaxSize(0, 0);
}

View::~View() {
    setParentView(nullptr);
    for (View* child : mChildViews) child->mParentView = nullptr;
    releaseRenderSurface();
}

void View::releaseRenderSurface() {
    if (mRenderImage) { mRenderImage->release(); mRenderImage = nullptr; }
    if (mRenderPort) { GraphicsManager::instance().closeGraphicsPort(mRenderPort); mRenderPort = nullptr; }
}

void View::setParentView(View* parent) {
    if (parent && parent->mController != mController) throw std::invalid_argument("Parent and child must share a Controller");
    for (View* ancestor = parent; ancestor; ancestor = ancestor->mParentView)
        if (ancestor == this) throw std::invalid_argument("View parenting cannot contain cycles");
    if (mParentView == parent) return;
    if (mParentView) {
        auto& siblings = mParentView->mChildViews;
        std::erase(siblings, this);
    }
    mParentView = parent;
    if (parent) parent->mChildViews.push_back(this);
}

View* View::getHitView(const Point& point, bool includeDisabled) {
    if (!isVisible() || !pointInViewVisibleArea(point)) return nullptr;
    for (auto it=mChildViews.rbegin(); it!=mChildViews.rend(); ++it)
        if (View* child=(*it)->getHitView(point,includeDisabled)) return child;
    return (includeDisabled || isEnabled()) && getPartClicked(point)!=CLICKED_PART_NONE ? this : nullptr;
}

glm::mat3 View::getLayoutTransform(bool includeParent) const {
    glm::mat3 normalize(1);
    if (mWidth == 0 || mHeight == 0) return glm::mat3(0);
    normalize[0][0] = 1 / mWidth; normalize[1][1] = 1 / mHeight;
    normalize[2][0] = -mViewArea.left / mWidth - 0.5f;
    normalize[2][1] = -mViewArea.top / mHeight - 0.5f;
    glm::mat3 matrix = AnimatedAttributesBase::getTransform() * normalize;
    return includeParent && mParentView ? mParentView->getLayoutTransform() * matrix : matrix;
}

float View::getDrawingTextWidth(const char* text, int size, uint32 style, int length) const {
    const Attributes attrs = getDrawingAttributes(Attributes().textSize(size).textStyle(style), true);
    style = attrs.getTextStyle();
    Font* saved = attrs.getFont() ? mPort->getCurrentFont(style) : nullptr;
    if (saved) saved->addRef();
    if (attrs.getFont()) mPort->setFontForStyle(attrs.getFont(), style);
    try {
        const float width = mPort->getTextWidth(text, attrs.getTextSize(), style, length);
        if (saved) { mPort->setFontForStyle(saved, style); saved->release(); }
        return width;
    } catch (...) {
        if (saved) { mPort->setFontForStyle(saved, style); saved->release(); }
        throw;
    }
}

void View::draw() {
    if (!isVisible() || !mPort) return;
    const Rect frame = getVisibleFrame();
    if (frame.empty() || mWidth == 0 || mHeight == 0) return;
    const glm::mat3 matrix = getLayoutTransform(false);
    Quad destination(frame);
    for (Point& p : destination.points) {
        auto v = matrix * glm::vec3(p.x, p.y, 1); p = Point(v.x, v.y);
    }
    Port* target = mPort;
    Port::ScreenDrawingScope screenDrawing(*target);
    const Rect savedClip = target->getClipRect();
    if (savedClip.intersection(destination.getBounds()).empty()) return;
    bool transformed = false;
    for (int c=0; c<3; ++c) for (int r=0; r<3; ++r)
        if (std::abs(matrix[c][r] - (c==r ? 1.0f : 0.0f)) > 0.00001f) transformed = true;
    if (transformed) {
        const int w = int(std::ceil(frame.width())), h = int(std::ceil(frame.height()));
        if (mRenderPort && (mRenderImage->getWidth()!=w || mRenderImage->getHeight()!=h)) releaseRenderSurface();
        if (!mRenderPort) {
            mRenderPort = GraphicsManager::instance().createOffscreenPort(Rect(w,h));
            if (!mRenderPort) throw std::runtime_error("Unable to create View rendering surface");
            mRenderImage = Image::createImageFromOffscreenPort(mRenderPort, false);
        }
        mRenderPort->setDrawingOrigin(frame.leftTop());
        mRenderPort->clear();
        mRenderPort->setClipRect(frame);
        for (int style=0; style<8; ++style) mRenderPort->setFontForStyle(target->getCurrentFont(style), style);
        mPort = mRenderPort;
    } else target->setClipRect(frame.intersection(savedClip));
    mDrawingLayout = true; setDrawingLayout(true);
    try {
        drawSelf();
        for (View* child : mChildViews) {
            Port* previous = child->setPort(mPort);
            try { child->draw(); } catch (...) { child->setPort(previous); throw; }
            child->setPort(previous);
        }
    } catch (...) {
        mDrawingLayout = false; setDrawingLayout(false); mPort = target; target->setClipRect(savedClip); throw;
    }
    mDrawingLayout = false; setDrawingLayout(false); mPort = target; target->setClipRect(savedClip);
    if (transformed) {
        // Crop fractional layout extents rather than stretching the rounded-up allocation.
        target->drawImage(mRenderImage, destination,
            Attributes().subsection(Rect(frame.width(), frame.height())));
    }
}

void View::hide() {
    bool wasVisible = mVisible;
    mVisible = false;
    if (wasVisible != mVisible) {
        hideSelf();
    }
}

void View::show() {
    bool wasVisible = mVisible;
    mVisible = true;
    if (wasVisible != mVisible) {
        showSelf();
    }
}

void View::setEnabled(bool enabled) {
    bool wasEnabled = mIsEnabled;
    mIsEnabled = enabled;
    if (wasEnabled != mIsEnabled) {
        // No immediate drawing - will be drawn on next frame
    }
}

void View::setDraggable(bool inIsDraggable) {
	mIsDraggable = inIsDraggable;
}
	
void View::setWantsMouseOvers(bool inWantsMouseOvers) {
	mWantsMouseOvers = inWantsMouseOvers;
}
	
void View::showSelf()
{
}

void View::hideSelf()
{
}

// doMouseDown is called whenever the mouse button goes down within the view
// Override to do something useful
bool View::doMouseDown(const MouseInfo *mi,  int id, int part)
{
	return false;
}

// Releases a press that began here, including outside release or cancellation.
// Override to do something useful
bool View::doMouseUp(const MouseInfo *mi, int id, int part)
{
	return false;
}
	
	// Receives hover motion and captured drag motion, including outside the view.
	// Override to do something useful
void View::doMouseMove(const MouseInfo *mi,  int id, int part)
{
}

	// doMouseEnter is called whenever the mouse enter the view, if the view wants mouseovers
	// Override to do something useful
void View::doMouseLeave(const MouseInfo *mi, int id, int part)
{
}

	// doMouseLeave is called whenever the mouse exits the view, if the view wants mouseovers
	// Override to do something useful
void View::doMouseEnter(const MouseInfo *mi,  int id, int part)
{
}


// ============================ Mouse Actions ============================
bool View::doLeftClick(const MouseInfo *mi, int id, int part)
{
	return false;
}
bool View::doRightClick(const MouseInfo *mi, int id, int part)
{
	return false;
}
bool View::doDoubleClick(const MouseInfo *mi, int id, int part, int clickCount)
{
	return false;
}

// ============================ Gestures	============================
// Gestures are only generated by a TouchController, the base Controller class will not generate them

// doTap is called when a finger goes up and down within the view
// return true if completely handled, or false if the tap can be passed on to other views
bool View::doTap( const MouseInfo *mi, int id, int part)
{
	return false;
}
	

// doTouchMove is called when a finger that went down in the view moves within the view, or
// after it was released within the view as part of a flick gesture (in which case flick will be true)
// NOTE: if the finger exits the view while still down, doTouchMove is no longer called. Then doDragMove 
// is called instead if the view is draggable
// return true if completely handled, or false if the tap can be passed on to other views
bool View::doTouchMove( const Point& delta, bool flick, int id, int part)
{
	return false;
}


// doSwipeMove happens when two or more fingers are down in the view and move in unison (ie, all in 
// the same direction)
// return true if completely handled, or false if the tap can be passed on to other views
bool View::doSwipeMove( const Point& delta, int fingerCount, int id, int part)
{
	return false;
}


// doPinchMove happens when two fingers are down in the view and move together or apart
// return true if completely handled, or false if the tap can be passed on to other views
bool View::doPinchMove( const Point& delta1, const Point& delta2, float distance, float deltaDistance, int id, int part)
{
	return false;
}


// ============================ Drag Actions ============================ 
// No drag actions will be called unless the view is set to be draggable

// doDragMove is called when the mouse when down within the view and is now moving while held down
// it will also be called when the TouchMove gesture exits the view, but the finger remains down
bool View::doDragMove(const MouseInfo *mi, int id, int part)
{
	return false;
}


// doDragIn is called when the mouse when down within the view and first moves over another view (the target view)
bool View::doDragIn(const MouseInfo* mi, int id, int part, View* targetView, int targetId, int targetPart)
{
	return false;
}


// doDragOut is called when the mouse when down within the view and first moves out of another view (the 
// target view). It is always preceeded by a doDragOut call
bool View::doDragOut(const MouseInfo* mi, int id, int part, View* targetView, int targetId, int targetPart)
{
	return false;
}


// startBeingDragTarget is called when the mouse went down in another view (the dragged view) and first moves 
// into this view
bool View::startBeingDragTarget(const MouseInfo* mi, int id, int part, View* draggedView, int draggedId, int draggedPart)
{
	return false;
}


// stopBeingDragTarget is called when the mouse went down in another view (the dragged view) and moves out
// of this view. It is always preceeded by a startBeingDragTarget call
bool View::stopBeingDragTarget(const MouseInfo* mi, int id, int part, View* draggedView, int draggedId, int draggedPart)
{
	return false;
}


// doDragComplete is called with the mouse is released after a series of drag related calls
bool View::doDragComplete(const MouseInfo *mi, int id, int part)
{
	return false;
}


void View::setViewArea(const Rect& rect)
{
    // Take a copy: callers may pass mViewArea itself.
    const Rect area = rect;
    setSize(area.width(), area.height());
    setLocation(area.centerPoint());
}

void View::syncViewArea() {
    const Rect previous = mViewArea;
    mViewArea = Rect(mWidth, mHeight);
    mViewArea.center(mLocation);
    if (mViewArea != previous) viewAreaChanged(previous);
}

void View::locationChanged(const Offset& delta) { AnimatedAttributesBase::locationChanged(delta); syncViewArea(); }
void View::sizeChanged(float w, float h) { AnimatedAttributesBase::sizeChanged(w, h); syncViewArea(); }
bool View::animate(double deltaSeconds) { return AnimatedAttributesBase::animate(deltaSeconds); }

void View::viewAreaChanged(const Rect& previous) {
    for (View* child : mChildViews) {
        const Rect old = child->getViewArea();
        const float sx = previous.width() ? mViewArea.width()/previous.width() : 1;
        const float sy = previous.height() ? mViewArea.height()/previous.height() : 1;
        child->setViewArea(Rect(mViewArea.left+(old.left-previous.left)*sx,
            mViewArea.top+(old.top-previous.top)*sy, mViewArea.left+(old.right-previous.left)*sx,
            mViewArea.top+(old.bottom-previous.top)*sy));
    }

    // Clickable geometry is local to the view; preserve its proportions on resize.
    const float sx = previous.width() ? mViewArea.width() / previous.width() : 1;
    const float sy = previous.height() ? mViewArea.height() / previous.height() : 1;
    for (auto& part : mClickableParts) {
        part.first.left *= sx; part.first.right *= sx;
        part.first.top *= sy; part.first.bottom *= sy;
    }
}

bool View::pointInViewArea(const Point& point) {
    const Point local = globalToLocal(point);
    return Rect(mViewArea.width(), mViewArea.height()).contains(local);
}

bool View::pointInViewVisibleArea(const Point& point) {
    if (mParentView && !mParentView->pointInViewVisibleArea(point)) return false;
    const Point layout = globalToLocal(point) + mViewArea.leftTop();
    return getVisibleFrame().contains(layout);
}

// if a view returns View::CLICKED_PART_NONE, it is not willing
// to handle the click, and other views can handle it
int View::getPartClicked(const Point& screenPoint)
{
	Point localPoint = globalToLocal(screenPoint);
	ClickableList::reverse_iterator itr;  // most recently added first
	int clickedPartID = CLICKED_PART_NONE;

	for(itr = mClickableParts.rbegin(); itr != mClickableParts.rend(); itr++)
	{
		idRectPair val = *itr;

		// Check to see if the point is in this rectangle
		if ( val.first.contains(localPoint) )
		{
			// Set the clickedPartID the id of this rect
			clickedPartID = val.second;
			break;
		}
	}

	return clickedPartID;
}

// if a view returns an empty rect, then it doesn't know about that part id
Rect View::getClickableRectFromID(int id)
{
	Rect rClickableRect(0,0);
	ClickableList::reverse_iterator itr;  // most recently added first
	for( itr = mClickableParts.rbegin(); itr != mClickableParts.rend(); itr++)
	{
		idRectPair val = *itr;
		// Check to see if the point is in this rectangle
		if (id==val.second)
		{
			rClickableRect = val.first;
			break;
		}
	}
	return rClickableRect;
}

void View::addClickablePart(const Rect& rect, int id)
{
	// Add the ID and name pair to our list
	idRectPair val( rect, id );
	mClickableParts.push_back( val );
}

void View::removeClickablePart(int id)
{
	ClickableList::iterator itr;
	for( itr = mClickableParts.begin(); itr != mClickableParts.end(); itr++)
	{
		idRectPair val = *itr;
		// Check to see if the point is in this rectangle
		if (id==val.second)
		{
			mClickableParts.erase(itr);
			break;
		}
	}
}



void View::drawClickableParts()
{
	// Used for debug purposes.
	ClickableList::reverse_iterator itr; // most recently added first

	for(itr = mClickableParts.rbegin(); itr != mClickableParts.rend(); itr++)
	{
		idRectPair val = *itr;
		Rect localArea = val.first;
	Rect globalArea = localToGlobal(localArea);
	int id = val.second;

	mPort->drawRect(globalArea, Attributes().lineColor(PDG_GREEN_COLOR).lineThickness(1));

	char text[128];
	std::snprintf(text, 128, "%d=ID", id);
        MAKE_STRING_BUFFER_SAFE(text, 128);
	mPort->drawText(text, globalArea.leftTop(), Attributes().textSize(12).textStyle(textStyle_Plain).fillColor(PDG_GREEN_COLOR));
	}
	
	mPort->drawRect(mViewArea, Attributes().fillColor(::pdg::Color(1.0f, 1.0f, 1.0f, 0.25f)));
}

void View::portResized(const Rect& oldDrawingArea, const Rect& newDrawingArea) {
	if (mBinding == 0) {
		//mViewArea = newDrawingArea;
		return; // short circuit
	}
	Rect newViewArea = mViewArea;
	if (mBinding & Bind::Left) {
		// bound to left, always change left to keep distance from left boundry
		newViewArea.left = newDrawingArea.left + (mViewArea.left - oldDrawingArea.left);
		if (mBinding & Bind::Right) {
			// also bound to right, need to shrink or grow
			newViewArea.right = newDrawingArea.right - (oldDrawingArea.right - mViewArea.right );		
			// make sure we are within or min and max sizes
			if (mMaxWidth && newViewArea.width() > mMaxWidth) {
				newViewArea.setWidth( mMaxWidth );
			}
			if (newViewArea.width() < mMinWidth) {
				newViewArea.setWidth( mMinWidth );
			}
		} 
	} else if (mBinding & Bind::Right) {
		// bound to right but not left, maintain width but move with right boundry
		newViewArea.right = newDrawingArea.right - (oldDrawingArea.right - mViewArea.right );		
		newViewArea.left = newViewArea.right - mViewArea.width();
	}
	if (mBinding & Bind::Top) {
		// bound to top, always change top to keep distance from top boundry
		newViewArea.top = newDrawingArea.top + (mViewArea.top - oldDrawingArea.top);
		if (mBinding & Bind::Bottom) {
			// also bound to bottom, need to shrink or grow
			newViewArea.bottom = newDrawingArea.bottom - (oldDrawingArea.bottom - mViewArea.bottom );		
			// make sure we are within or min and max sizes
			if (mMaxHeight && newViewArea.height() > mMaxHeight) {
				newViewArea.setHeight( mMaxHeight );
			}
			if (newViewArea.height() < mMinHeight) {
				newViewArea.setHeight( mMinHeight );
			}
		} 
	} else if (mBinding & Bind::Bottom) {
		// bound to bottom but not top, maintain height but move with bottom boundry
		newViewArea.bottom = newDrawingArea.bottom - (oldDrawingArea.bottom - mViewArea.bottom );		
		newViewArea.top = newViewArea.bottom - mViewArea.height();
	}
	setViewArea(newViewArea);
}

// coordinate transforms, local view coords --> global drawing coords
Point View::localToGlobal(Point point) {
    point += mViewArea.leftTop();
    if (mDrawingLayout) return point;
    const auto p = getLayoutTransform() * glm::vec3(point.x,point.y,1);
    return Point(p.x,p.y);
}

static Rect mappedRect(View& view, Rect rect, bool inverse) {
    Quad q(rect);
    for (auto& point : q.points) point = inverse ? view.globalToLocal(point) : view.localToGlobal(point);
    return q.getBounds();
}
Rect View::localToGlobal(Rect rect) { return mappedRect(*this, rect, false); }
Point View::globalToLocal(Point point) {
    const auto matrix = getLayoutTransform();
    if (std::abs(glm::determinant(matrix)) < 1e-10f)
        return Point(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    auto p = glm::inverse(matrix) * glm::vec3(point.x, point.y, 1);
    return Point(p.x-mViewArea.left,p.y-mViewArea.top);
}
Rect View::globalToLocal(Rect rect) { return mappedRect(*this, rect, true); }

    // ============================================ BEGIN DEPRECATED =====================================
#ifdef PDG_ALLOW_DEPRECATED_CALLS

	// returns pixel offset between top of rect passed in and top (not baseline) of next line that would be drawn with
	// normal line spacing. The typical use for this would be to call textArea.moveDown() by that pixel offset, and
	// then call drawMultilineText again for the next block/paragraph
	int View::drawMultilineText(const char* text, int size, Color color, const Rect& textArea, int style)
	{
		int len = std::strlen(text);
		int maxLineWidth = textArea.width();
		int charsLeftToDraw = len;
		int voffset = mPort->getCurrentFont(style)->getFontHeight(size, style) + mPort->getCurrentFont(style)->getFontLeading(size, style);
		int x = textArea.left;
		if (style & textStyle_Centered) {
			x += textArea.width()/2;
		} else if (style & textStyle_RightJustified) {
			x = textArea.right;
		}
		int y = textArea.top  + mPort->getCurrentFont(style)->getFontAscent(size, style);
		char* p = new char[len+2]; // create a temporary space for copying
		bool nospace = false;
		char* nextSeg = 0;
		do {
			if (!nextSeg) {
				nextSeg = (char*) std::strchr(text, '|'); // find any hard line breaks
				if (nextSeg) {
					// replace hard line break with nul character to terminate string
					*nextSeg = 0;
					//                --charsLeftToDraw;       // one less character to draw
				}
			}
			if (nextSeg) {
				len = std::strlen(text); // and our string length has changed
			}
			while (len && (maxLineWidth < mPort->getTextWidth(text, size, style, len))) {
				if (!nospace) {
					int len_save = len;
					// look for a space or a hypen to break on
					while (len > 0) {
						--len;
						if ((text[len] == ' ') || (text[len] == '-')) {
							break;
						}
					}
					if (len == 0) { // if we didn't find a space, start from the previous character
						len = len_save - 1;
						nospace = true;
					}
				} else {
					--len;
				}
			}
			if (len && !nospace) {  // if we found a break, we need to include the breaking character
				++len;              // in the line to draw
			}
		std::strncpy(p, text, len); // make a nul terminated copy of just the section we want to draw
		p[len] = 0;
		
		mPort->drawText(p, Point(x, y), Attributes().textSize(size).textStyle(style).fillColor(color));
		text += len;
			if (nextSeg && (text > nextSeg)) {
				// if we are at the location of a hard line break,
				// skip over the nul character we replaced it with
				*nextSeg = '|'; // restore the vertical bar
				text = ++nextSeg;
				nextSeg = 0;
			}
			charsLeftToDraw -= len;
			len = charsLeftToDraw;
			y += voffset;
		} while (charsLeftToDraw > 0);
		delete[] p;
		return (y - (textArea.top + mPort->getCurrentFont(style)->getFontAscent(size, style)));
	}
	
	
	Image* View::loadImage(ResourceManager& resMgr, int id, int idx, Color* transparentColor)
	{
		const char *artFileName;
		std::string buffer;
		Image* pImage = 0;
		
		// get the image name from the resources
		artFileName = resMgr.getString(buffer, id, idx);
		DEBUG_ONLY( if (!artFileName) {
			OS::_DOUT("Couldn't find filename for image resource id [%d] idx [%d]", id, idx);
		} )
		
		// load the hex art with that image name
		pImage = resMgr.getImage(artFileName);
		if (pImage)
		{
			pImage->setPort(mPort); // force them to use our drawing port
			if (transparentColor) {
				pImage->setTransparentColor( *transparentColor );
			}
		}
		else
		{
			DEBUG_ONLY( OS::_DOUT("Couldn't load image [%s] from resources", artFileName); )
		}
		
		return pImage;
	}
	
	void View::loadImageArray(ResourceManager& resMgr, Image* arr[], int id, int numImages, Color* transparentColor)
	{
		for (int i = 0; i < numImages; i++)
		{
			arr[i] = loadImage(resMgr, id, i, transparentColor);
		}
	}
	
	void View::unloadImage(Image* & imagePtr)
	{
		if (imagePtr) {
			imagePtr->release();
			imagePtr = 0;
		}
	}
	
	void View::unloadImageArray(Image* arr[], int numImages)
	{
		for (int i = 0; i < numImages; i++)
		{
			unloadImage(arr[i]);
		}
	}
	
	void View::scaleImage(Image*& image, float scaleBy, Image::FilterType filter)
	{
		Image* temp;
		if (image)
		{
			temp = image->createImageScaled(scaleBy, scaleBy, filter);
			image->release();
			image = temp;
		}
	}
	
	void View::scaleImageArray(Image* arr[], int numImages, float scaleBy, Image::FilterType filter)
	{
		for (int i = 0; i < numImages; i++) {
			if (arr[i]) {
				Image* newImage = arr[i]->createImageScaled(scaleBy, scaleBy, filter);
				arr[i]->release();
				arr[i] = newImage;
			}
		}
	}
	
	
	void View::scaleImageArrayToFit(Image* arr[], int numImages, Rect r, Image::FilterType filter)
	{
		for (int i = 0; i < numImages; i++) {
			if (arr[i]) {
				Image* newImage = arr[i]->createImageScaledToFit(r, fit_Fill, filter);
				arr[i]->release();
				arr[i] = newImage;
			}
		}
	}
	// ============================================ END DEPRECATED =====================================
#endif // PDG_ALLOW_DEPRECATED_CALLS
	

} // namespace pdg
