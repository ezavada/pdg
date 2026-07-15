// -----------------------------------------------
// port.h
//
// graphics drawing port functionality
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


#ifndef PDG_PORT_H_INCLUDED
#define PDG_PORT_H_INCLUDED

#ifndef PDG_NO_GUI

#include "pdg_project.h"

#include "pdg/sys/global_types.h"
#include "pdg/sys/coordinates.h"
#include "pdg/sys/color.h"
#include "pdg/sys/image.h"
#include "pdg/sys/imagestrip.h"
#include "pdg/sys/font.h"
#include "pdg/sys/spline.h"
#include "pdg/sys/polygon.h"
#include "pdg/sys/renderer.h"

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

namespace pdg {

//! \defgroup Graphics
//! Collection of classes, types and constants that are used for drawing

class Image;

// -----------------------------------------------------------------------------------
//! Graphics
//! A collection of static enumerations that are used when drawing
//! \ingroup Graphics
// -----------------------------------------------------------------------------------

//extended drawing, with line thickness and opacity
//thickness: width of line (0 - 255), 0 means no line



// -----------------------------------------------------------------------------------
//! Port
//! An area in which drawing is done, a viewport. This could be a full screen drawing
//! context or a window.
//! \ingroup Graphics
// -----------------------------------------------------------------------------------

class Port : public Renderer {
public:

    // Renderer interface implementation
    virtual void drawLine(const Point& from, const Point& to, const Attributes& attrs) override;
    virtual void drawRect(const Rect& rect, const Attributes& attrs) override;
    virtual void drawQuad(const Quad& quad, const Attributes& attrs) override;
    virtual void drawPolygon(const Polygon& polygon, const Attributes& attrs) override;
    virtual void drawSpline(const Spline& spline, const Attributes& attrs) override;
    virtual void drawEllipse(const Point& center, float xRadius, float yRadius, const Attributes& attrs) override;
    virtual void drawArc(const Point& center, float xRadius, float yRadius, float startAngle, float endAngle, const Attributes& attrs) override;

    // New Renderer interface methods
    virtual void drawImage(Image* img, const Point& loc, const Attributes& attrs) override;
    virtual void drawImage(Image* img, const Rect& rect, const Attributes& attrs) override;
    virtual void drawImage(Image* img, const Quad& quad, const Attributes& attrs) override;
    virtual void drawDrawing(const Drawing& drawing, const Point& loc, const Attributes& attrs) override;
    virtual void drawDrawing(const Drawing& drawing, const Rect& rect, const Attributes& attrs) override;
    virtual void drawText(const char* text, const Point& loc, const Attributes& attrs) override;
    virtual void drawText(const char* text, const Rect& rect, const Attributes& attrs) override;
    virtual void drawSphere(const Point& center, float radius, const Attributes& attrs) override;

    Rect     getDrawingArea();
    Rect     getClipRect();
    void     setClipRect(const Rect& rect);

    int      getTextWidth(const char* text, int size,
                            uint32 style = textStyle_Plain,
                            int len = -1);

	// returns the current font used to draw
	Font*    getCurrentFont(uint32 style = textStyle_Plain);

    // set the font used for this port
	// with no params it sets the font to the default font for the port, which is Arial
    void     setFont(Font* font = 0);

    // set the name of the font used for a particular style of text in this port
    // does not affect what font is used for any other styles
	// passing nil for font resets the font for that style to the default font, which is Arial
    void     setFontForStyle(Font* font, uint32 style);

    // set a factor by which all font sizes are enlarged or reduced
    // > 1.0 is enlarge, < 1.0 is reduce, 1.0 is no scaling
    void     setFontScalingFactor(float scaleBy);

	// start tracking a particular area for mouse enter/leave events
	// when the mouse enters that area, a mouse enter event will be generated
	// when the mouse leaves that area, a mouse leave event will be generated
	// userData is passed back in the enter and leave events
	// returns a reference that can be used to stop the tracking
	int      startTrackingMouse(const Rect& rect, void* userData = 0);

	// stop tracking the mouse for a particular tracking rectangle
	void     stopTrackingMouse(int trackingRef);

	void        setCursor(Image* cursorImage, const Point& hotSpot);
	Image*      getCursor();
	void        resetCursor();

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	SCRIPT_OBJECT_REF mPortScriptObj;
#endif

#ifndef PDG_INTERNAL_LIB
protected:
#endif
/// @cond INTERNAL
    Port(); // protected constructor, Ports can't be created directly
    virtual ~Port(); // protected destructor, Ports can't be deleted directly
    bool mClipChanged;
/// @endcond

private:
	// image drawing
	
    //! draws image at given location
	void     drawImage(Image* img, const Point& loc);
    //! draws image into a given rectangle, scaling as needed
	void     drawImage(Image* img, const Rect& r);
    //! draws image into a given rectangle, scaling as specified to fit, with optional clipping
	void     drawImage(Image* img, const Rect& r, FitType fitType, bool clipOverflow = false);
    //! draws image at given location, scaling if necessary to fit
	void     drawImage(Image* img, const RotatedRect& rr);
    //! draws image into a given quad-polygon, mapping each of the corners to the corresponding points
	void     drawImage(Image* img, const Quad& quad);	

    //! draws single frame of multiframe image at given location
	void     drawImage(ImageStrip* img, int frame, const Point& loc);
    //! draws single frame of multiframe image into a given rectangle, scaling as needed
	void     drawImage(ImageStrip* img, int frame, const Rect& r);
    //! draws single frame of multiframe image into a given rectangle, scaling as specified to fit, with optional clipping
	void     drawImage(ImageStrip* img, int frame, const Rect& r, FitType fitType, bool clipOverflow = false);
    //! draws single frame of multiframe image at given location, scaling if necessary to fit
	void     drawImage(ImageStrip* img, int frame, const RotatedRect& rr);
    //! draws single frame of multiframe image into a given quad-polygon, mapping each of the corners to the corresponding points
	void     drawImage(ImageStrip* img, int frame, const Quad& quad);	

	// texture drawing


//! draws image as texture filling given area, replicating as needed to fill entire area (deprecated)
   void    drawTexture(Image* img, const Rect& r); // Deprecated
   //! draws single frame of multiframe image as texture filling given area, replicating as needed to fill entire area (deprecated)
   void    drawTexture(ImageStrip* img, int frame, const Rect& r); // Deprecated
   //! draws image as texture wrapped around a sphere (deprecated)
   void    drawTexturedSphere(Image* img, const Point& loc, float radius, float rotation = 0.0f, const Offset& polarOffsetRadians = Offset(0,0), const Offset& lightOffsetRadians = Offset(0,0), const Color& ambientLight = Color(0.5f, 0.5f, 0.5f, 1.0f));
   //! draws single frame of multiframe image as texture wrapped around a sphere (deprecated)
   void    drawTexturedSphere(ImageStrip* img, int frame, const Point& loc, float radius, float rotation = 0.0f, const Offset& polarOffsetRadians = Offset(0,0), const Offset& lightOffsetRadians = Offset(0,0), const Color& ambientLight = Color(0.5f, 0.5f, 0.5f, 1.0f));
   //! draws a solid colored sphere with 3D lighting
   void    drawColoredSphere(const Color& color, const Point& loc, float radius, float rotation = 0.0f, const Offset& polarOffsetRadians = Offset(0,0), const Offset& lightOffsetRadians = Offset(0,0), const Color& ambientLight = Color(0.5f, 0.5f, 0.5f, 1.0f));

   //! draws texture on a polygon with proper texture coordinate mapping (deprecated)
   void    drawTexturedPolygon(Image* img, const Polygon& transformedPolygon, const Polygon& untransformedPolygon, const Rect& bounds, FitType fitType = fit_Fill);

   // text drawing and measurement

   // private (deprecated) methods
   void     drawText(const char* text, const Point& loc, int size,
                           uint32 style = textStyle_Plain,
                           Color rgba = PDG_BLACK_COLOR);

    // private (deprecated) methods
   void	 drawText(const char* text, const Rect& r, int size,
                           uint32 style = textStyle_Plain,
                           Color rgba = PDG_BLACK_COLOR);
   void	 drawText(const char* text, const RotatedRect& rr, int size,
                           uint32 style = textStyle_Plain,
                           Color rgba = PDG_BLACK_COLOR);
   void	 drawText(const char* text, const Quad& quad, int size,
                           uint32 style = textStyle_Plain,
                           Color rgba = PDG_BLACK_COLOR);


};

inline void
Port::drawImage(Image* img, const Rect& r) {
	drawImage(img, (const Quad)r);
}

inline void 
Port::drawImage(Image* img, const RotatedRect& rr) {
	drawImage(img, (const Quad)rr);
}

inline void
Port::drawImage(ImageStrip* img, int frame, const Rect& r) {
	drawImage(img, frame, (const Quad)r);
}

inline void 
Port::drawImage(ImageStrip* img, int frame, const RotatedRect& rr) {
	drawImage(img, frame, (const Quad)rr);
}

inline void 
Port::drawText(const char* text, const Rect& r, int size, uint32 style, Color rgba) {
	drawText(text, (const Quad)r, size, style, rgba);
}

inline void 
Port::drawText(const char* text, const RotatedRect& rr, int size, uint32 style, Color rgba) {
	drawText(text, (const Quad)rr, size, style, rgba);
}


} // end namespace pdg

#endif // PDG_NO_GUI

#endif // PDG_PORT_H_INCLUDED

