// -----------------------------------------------
//  polygon.h
//
// Written by Ed Zavada, 2025
// Copyright (c) 2024, Dream Rock Studios, LLC
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

#ifndef PDG_POLYGON_H_INCLUDED
#define PDG_POLYGON_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/coordinates.h"
#include "pdg/sys/global_types.h"
#include <vector>

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
  #include "pdg_script_bindings.h"
#endif

namespace pdg {
	
	typedef PointT<float> Point;
	
	// Forward declarations
	class Spline;
	
	class Polygon
	{
	public:	
		// Constructors
		Polygon();
		Polygon(const std::vector<Point>& points);
		Polygon(std::initializer_list<Point> points);
		~Polygon() {
          #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
            #ifndef PDG_NO_GUI
                CleanupPolygonScriptObject(mPolygonScriptObj);
            #endif
          #endif
        };
        
        // Move constructor and assignment operator
        Polygon(Polygon&& other) noexcept;
        Polygon& operator=(Polygon&& other) noexcept;
        
        // Delete copy constructor and assignment operator
        Polygon(const Polygon&) = delete;
        Polygon& operator=(const Polygon&) = delete;
		
		// Point management
		void addPoint(const Point& p);
		void addSpline(Spline* spline, float uStep = 0.01f);
		void insertPoint(size_t index, const Point& p);
		void removePoint(size_t index);
		size_t getPointCount() const;
		Point getPoint(size_t index) const;
		void setPoint(size_t index, const Point& p);
		void clearPoints();
		
		// Geometric operations
		Rect getBounds() const;
		Point centerPoint() const;
		bool contains(const Point& p) const;
		bool empty() const;
		
		// Movement transformations
		Polygon& move(const Offset& offset);
		Polygon& moveLeft(float delta);
		Polygon& moveRight(float delta);
		Polygon& moveUp(float delta);
		Polygon& moveDown(float delta);
		Polygon& moveXTo(float x);
		Polygon& moveYTo(float y);
		Polygon& moveTo(float x, float y);
		Polygon& moveTo(const Point& p);
		Polygon& center(const Point& p);
		Polygon& center(const Rect& r);
		
		// Scaling transformations
		Polygon& scale(float factor);
		Polygon& horzScale(float factor);
		Polygon& vertScale(float factor);
		Polygon& scaleAround(float factor, const Point& centerPoint);
		
		// Rotation transformations
		Polygon& rotate(float radians);
		Polygon& rotateAround(float radians, const Point& centerPoint);
		Polygon& rotate(float radians, const Point& centerOffset);
		
		// Operators (using Offset for consistency with other coordinate classes)
		Polygon& operator+=(const Offset& offset);
		Polygon& operator-=(const Offset& offset);
		Polygon operator+(const Offset& offset) const;
		Polygon operator-(const Offset& offset) const;
		Polygon operator*(float factor) const;
		
		// Equality operators
		bool operator==(const Polygon& other) const;
		bool operator!=(const Polygon& other) const;
		
	// Triangulation for rendering
	std::vector<Point> triangulate() const;
	std::vector<Point> tessellate() const;  // Uses libtess2 for robust tessellation
	
	// Polygon analysis
	bool isSelfIntersecting() const;  // Check if polygon has self-intersections
	
	// Boolean operations
	Polygon intersection(const Polygon& other) const;
	Polygon unionWith(const Polygon& other) const;
		
	  #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
		SCRIPT_OBJECT_REF mPolygonScriptObj;
	  #endif
		
	private:
		std::vector<Point> mPoints;
		
		// Bounds caching
		mutable Rect mCachedBounds;
		mutable bool mBoundsDirty;
		
		void invalidateBounds() const { mBoundsDirty = true; }
		
		// Helper methods for triangulation
		bool isEar(const std::vector<Point>& vertices, int i, const std::vector<int>& indices) const;
		float crossProduct(const Point& a, const Point& b, const Point& c) const;
		
		// Helper methods for boolean operations
		struct IntersectionPoint {
			Point point;
			size_t edge1Index;
			size_t edge2Index;
			bool isEntry;
			IntersectionPoint(const Point& p, size_t e1, size_t e2, bool entry) 
				: point(p), edge1Index(e1), edge2Index(e2), isEntry(entry) {}
		};
		
		bool lineSegmentsIntersect(const Point& p1, const Point& p2, 
								   const Point& p3, const Point& p4, 
								   Point& intersection) const;
		bool pointOnLineSegment(const Point& point, const Point& lineStart, const Point& lineEnd) const;
		float pointToLineDistance(const Point& point, const Point& lineStart, const Point& lineEnd) const;
		std::vector<IntersectionPoint> findIntersections(const Polygon& other) const;
		bool isPointInside(const Point& point, const Polygon& poly) const;
		Polygon buildResultPolygon(const std::vector<IntersectionPoint>& intersections, 
								   const Polygon& other, bool isUnion) const;
	};	
	
} // end namespace pdg

#endif // PDG_POLYGON_H_INCLUDED
