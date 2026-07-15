// -----------------------------------------------
//  Spline.h
//
// Written by Justin Holmes, 2010
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


#ifndef PDG_SPLINE_H_INCLUDED
#define PDG_SPLINE_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/coordinates.h"
#include "pdg/sys/global_types.h"
#include <vector>

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
  #include "pdg_script_bindings.h"
#endif 

#define SPLINE_HERMITE		1
#define SPLINE_CARDINAL		2
#define SPLINE_UNIFORM_B	3
#define SPLINE_CUBIC_BEZIER	4
#define SPLINE_TCB			5
#define SPLINE_NATURAL_CUBIC	6


namespace pdg {
	
	typedef PointT<float> Point;
	
	class Spline
	{
	public:	
		Spline(int type = SPLINE_CUBIC_BEZIER);
		~Spline() {
			#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
				#ifndef PDG_NO_GUI
					CleanupSplineScriptObject(mSplineScriptObj);
				#endif
			#endif
		};
		
		// Move constructor and assignment operator
		Spline(Spline&& other) noexcept;
		Spline& operator=(Spline&& other) noexcept;
		
		// Delete copy constructor and assignment operator
		Spline(const Spline&) = delete;
		Spline& operator=(const Spline&) = delete;
		
		// Evaluation - u parameter ranges from 0.0 to getMaxU()
		Point getFirstOrder(float u) const;
		Point getSecondOrder(float u) const;
		
		// High-level segment API
		void addSegment(Point p1, Point p2, Point p3, Point p4);
		
		// Low-level point API
		void addPoint(Point p);
		Point getPoint(int pointIndex) const;
		void setPoint(int pointIndex, Point p);
		int getPointCount() const;
		
		// Query methods
		float getMaxU() const;  // Maximum valid u parameter (equals number of segments)
		Rect getBounds() const;  // Get bounding rectangle of the spline

	  #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
		SCRIPT_OBJECT_REF mSplineScriptObj;
	  #endif
	private:
		int mType;
		std::vector< Point > mPoints;
		bool mLooping;
		unsigned long mCurrentSegmentIndices[4];  // Indices into mPoints for current segment
		int mCurrentSegment;  // Which segment (0, 1, 2...) is currently active
		
		// Bounds caching
		mutable Rect mCachedBounds;
		mutable bool mBoundsDirty;
		
		void invalidateBounds() const { mBoundsDirty = true; }
		
		// Internal helpers
		void updateSegmentIndices(int segmentNum);
		int getSegmentCount() const;
		int getPointsPerSegment() const;
		bool isMultiSegmentSplineType() const;
	};
	
}

#endif // SPLINE_H_INCLUDED
