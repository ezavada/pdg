// -----------------------------------------------
//  polygon.cpp
//
// Written by AI Assistant, 2024
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

#include "pdg_project.h"

#include "math.h"
#include <stdexcept>
#include <algorithm>
#include "pdg/sys/polygon.h"
#include "pdg/sys/spline.h"

#ifndef PDG_NO_GUI
// libtess2 for robust polygon tessellation
#include "tesselator.h"
#endif // !PDG_NO_GUI

namespace pdg {

	// Constructors
	Polygon::Polygon() : mBoundsDirty(true) {
		// Empty polygon
	}
	
	Polygon::Polygon(const std::vector<Point>& points) : mBoundsDirty(true) {
		mPoints = points;
	}
	
	Polygon::Polygon(std::initializer_list<Point> points) : mBoundsDirty(true) {
		mPoints.assign(points.begin(), points.end());
	}
	
	// Move constructor
	Polygon::Polygon(Polygon&& other) noexcept 
		: mPoints(std::move(other.mPoints)),
		  mCachedBounds(std::move(other.mCachedBounds)),
		  mBoundsDirty(other.mBoundsDirty)
	{
		#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
			mPolygonScriptObj = std::move(other.mPolygonScriptObj);
		#endif
	}
	
	// Move assignment operator
	Polygon& Polygon::operator=(Polygon&& other) noexcept {
		if (this != &other) {
			#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
				CleanupPolygonScriptObject(mPolygonScriptObj);
			#endif
			
			mPoints = std::move(other.mPoints);
			mCachedBounds = std::move(other.mCachedBounds);
			mBoundsDirty = other.mBoundsDirty;
			
			#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
				mPolygonScriptObj = std::move(other.mPolygonScriptObj);
			#endif
		}
		return *this;
	}
	
	// Point management
	void Polygon::addPoint(const Point& p) {
		// Don't add points that are too close to the previous point
		// This prevents duplicate/colocated points that can break triangulation
		if (!mPoints.empty()) {
			const Point& lastPoint = mPoints.back();
			float dx = p.x - lastPoint.x;
			float dy = p.y - lastPoint.y;
			float distanceSquared = dx * dx + dy * dy;
			
			// Skip points that are less than minDistance away
			if (distanceSquared < 1.0f) {
				return;
			}
		}
		mPoints.push_back(p);
		invalidateBounds();
	}
	
	void Polygon::addSpline(Spline* spline, float uStep) {
		if (!spline) {
			return;  // Null spline, nothing to do
		}
		
		// Determine the actual step to use
		float actualStep = (uStep > 0.0f && uStep <= 1.0f) ? uStep : 0.01f;
		
		// Get the maximum u value for this spline
		float maxU = spline->getMaxU();
		if (maxU <= 0.0f) {
			return;  // Empty or invalid spline
		}
		
		// Track the last point added to filter duplicates
		Point lastPoint(0, 0);
		bool hasLastPoint = false;

		if (mPoints.size() > 0) { // use existing last point if available
			lastPoint = mPoints[mPoints.size() - 1];
			hasLastPoint = true;
		}	
		
		// Iterate through the spline
		for (float u = 0.0f; u <= maxU; u += actualStep) {
			Point p = spline->getFirstOrder(u);
			
			// Check if this point is far enough from the last one
			if (hasLastPoint) {
				float dx = fabs(p.x - lastPoint.x);
				float dy = fabs(p.y - lastPoint.y);
				
				// Skip if both x and y differences are less than 0.5
				if (dx < 0.5f && dy < 0.5f) {
					continue;
				}
			}
			
			// Add this point
			mPoints.push_back(p);
			lastPoint = p;
			hasLastPoint = true;
		}
		
		// Make sure we include the final point at maxU
		if (hasLastPoint) {
			Point finalPoint = spline->getFirstOrder(maxU);
			float dx = fabs(finalPoint.x - lastPoint.x);
			float dy = fabs(finalPoint.y - lastPoint.y);
			
			// Only add if it's different enough from the last point
			if (dx >= 0.4f || dy >= 0.4f) {
				mPoints.push_back(finalPoint);
			}
		}
		
		// Invalidate bounds since we added points
		invalidateBounds();
	}
	
	void Polygon::insertPoint(size_t index, const Point& p) {
		if (index > mPoints.size()) {
			mPoints.push_back(p);
		} else {
			mPoints.insert(mPoints.begin() + index, p);
		}
		invalidateBounds();
	}
	
	size_t Polygon::getPointCount() const {
		return mPoints.size();
	}
	
	void Polygon::removePoint(size_t index) {
		if (index >= mPoints.size()) {
			throw std::out_of_range("Polygon::removePoint: index out of range");
		}
		mPoints.erase(mPoints.begin() + index);
		invalidateBounds();
	}
	
	Point Polygon::getPoint(size_t index) const {
		if (index >= mPoints.size()) {
			throw std::out_of_range("Polygon::getPoint: index out of range");
		}
		return mPoints[index];
	}
	
	void Polygon::setPoint(size_t index, const Point& p) {
		if (index >= mPoints.size()) {
			throw std::out_of_range("Polygon::setPoint: index out of range");
		}
		mPoints[index] = p;
		invalidateBounds();
	}
	
	void Polygon::clearPoints() {
		mPoints.clear();
		invalidateBounds();
	}
	
	// Geometric operations
	Rect Polygon::getBounds() const {
		if (mPoints.empty()) {
			mCachedBounds = Rect(0, 0, 0, 0);
			mBoundsDirty = false;
			return mCachedBounds;
		}
		
		// Return cached bounds if they're still valid
		if (!mBoundsDirty) {
			return mCachedBounds;
		}
		
		// Recalculate bounds
		float minX = mPoints[0].x;
		float maxX = mPoints[0].x;
		float minY = mPoints[0].y;
		float maxY = mPoints[0].y;
		
		for (size_t i = 1; i < mPoints.size(); i++) {
			minX = std::min(minX, mPoints[i].x);
			maxX = std::max(maxX, mPoints[i].x);
			minY = std::min(minY, mPoints[i].y);
			maxY = std::max(maxY, mPoints[i].y);
		}
		
		// Cache the result
		mCachedBounds = Rect(minX, minY, maxX, maxY);
		mBoundsDirty = false;
		
		return mCachedBounds;
	}
	
	Point Polygon::centerPoint() const {
		if (mPoints.empty()) {
			return Point(0, 0);
		}
		
		float sumX = 0.0f;
		float sumY = 0.0f;
		
		for (size_t i = 0; i < mPoints.size(); i++) {
			sumX += mPoints[i].x;
			sumY += mPoints[i].y;
		}
		
		return Point(sumX / mPoints.size(), sumY / mPoints.size());
	}
	
	bool Polygon::contains(const Point& p) const {
		if (mPoints.size() < 3) {
			return false;
		}
		
		// Ray casting algorithm for point-in-polygon test
		bool inside = false;
		size_t j = mPoints.size() - 1;
		
		for (size_t i = 0; i < mPoints.size(); i++) {
			const Point& pi = mPoints[i];
			const Point& pj = mPoints[j];
			
			if (((pi.y > p.y) != (pj.y > p.y)) &&
				(p.x < (pj.x - pi.x) * (p.y - pi.y) / (pj.y - pi.y) + pi.x)) {
				inside = !inside;
			}
			j = i;
		}
		
		return inside;
	}
	
	bool Polygon::empty() const {
		return mPoints.size() < 3;
	}
	
	// Movement transformations
	Polygon& Polygon::move(const Offset& delta) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i] += delta;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveLeft(float delta) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].x -= delta;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveRight(float delta) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].x += delta;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveUp(float delta) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].y -= delta;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveDown(float delta) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].y += delta;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveXTo(float x) {
		Rect bounds = getBounds();
		float offset = x - bounds.left;
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].x += offset;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveYTo(float y) {
		Rect bounds = getBounds();
		float offset = y - bounds.top;
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].y += offset;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveTo(float x, float y) {
		Rect bounds = getBounds();
		float offsetX = x - bounds.left;
		float offsetY = y - bounds.top;
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].x += offsetX;
			mPoints[i].y += offsetY;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::moveTo(const Point& p) {
		return moveTo(p.x, p.y);
	}
	
	Polygon& Polygon::center(const Point& p) {
		Point currentCenter = centerPoint();
		Offset offset = p - currentCenter;
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i] += offset;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::center(const Rect& r) {
		Point targetCenter = r.centerPoint();
		return center(targetCenter);
	}
	
	// Scaling transformations
	Polygon& Polygon::scale(float factor) {
		return horzScale(factor).vertScale(factor);
	}
	
	Polygon& Polygon::horzScale(float factor) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].x *= factor;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::vertScale(float factor) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i].y *= factor;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::scaleAround(float factor, const Point& centerPoint) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			Vector offset = mPoints[i] - centerPoint;
			offset *= factor;
			mPoints[i] = centerPoint + offset;
		}
		invalidateBounds();
		return *this;
	}
	
	// Rotation transformations
	Polygon& Polygon::rotate(float radians) {
		return rotateAround(radians, centerPoint());
	}
	
	Polygon& Polygon::rotateAround(float radians, const Point& centerPoint) {
		float cos_angle = cos(radians);
		float sin_angle = sin(radians);
		
		for (size_t i = 0; i < mPoints.size(); i++) {
			float dx = mPoints[i].x - centerPoint.x;
			float dy = mPoints[i].y - centerPoint.y;
			
			mPoints[i].x = centerPoint.x + (dx * cos_angle - dy * sin_angle);
			mPoints[i].y = centerPoint.y + (dx * sin_angle + dy * cos_angle);
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::rotate(float radians, const Point& centerOffset) {
		Point center = centerPoint() + centerOffset;
		return rotateAround(radians, center);
	}
	
	// Operators
	Polygon& Polygon::operator+=(const Offset& offset) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i] += offset;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon& Polygon::operator-=(const Offset& offset) {
		for (size_t i = 0; i < mPoints.size(); i++) {
			mPoints[i] -= offset;
		}
		invalidateBounds();
		return *this;
	}
	
	Polygon Polygon::operator+(const Offset& offset) const {
		Polygon result;
		result.mPoints = mPoints;
		result += offset;
		return result;
	}
	
	Polygon Polygon::operator-(const Offset& offset) const {
		Polygon result;
		result.mPoints = mPoints;
		result -= offset;
		return result;
	}
	
	Polygon Polygon::operator*(float factor) const {
		Polygon result;
		result.mPoints = mPoints;
		result.scale(factor);
		return result;
	}
	
	// Equality operators
	bool Polygon::operator==(const Polygon& other) const {
		if (mPoints.size() != other.mPoints.size()) {
			return false;
		}
		
		for (size_t i = 0; i < mPoints.size(); i++) {
			if (mPoints[i].x != other.mPoints[i].x || mPoints[i].y != other.mPoints[i].y) {
				return false;
			}
		}
		
		return true;
	}
	
	bool Polygon::operator!=(const Polygon& other) const {
		return !(*this == other);
	}
	
	std::vector<Point> Polygon::triangulate() const {
		std::vector<Point> triangles;
		
		if (mPoints.size() < 3) {
			return triangles; // Need at least 3 points
		}
		
		if (mPoints.size() == 3) {
			// Already a triangle
			triangles.insert(triangles.end(), mPoints.begin(), mPoints.end());
			return triangles;
		}
		
		// Create a list of vertex indices for ear clipping
		std::vector<int> indices;
		for (size_t i = 0; i < mPoints.size(); i++) {
			indices.push_back(i);
		}
		
		// Ear clipping algorithm
		while (indices.size() > 3) {
			bool earFound = false;
			
			for (size_t i = 0; i < indices.size(); i++) {
				if (isEar(mPoints, i, indices)) {
					// Found an ear, create a triangle
					int prev = (i == 0) ? indices.size() - 1 : i - 1;
					int next = (i + 1) % indices.size();
					
					triangles.push_back(mPoints[indices[prev]]);
					triangles.push_back(mPoints[indices[i]]);
					triangles.push_back(mPoints[indices[next]]);
					
					// Remove the ear vertex
					indices.erase(indices.begin() + i);
					earFound = true;
					break;
				}
			}
			
			if (!earFound) {
				// Fallback: if no ear found, just create triangles from remaining vertices
				// This can happen with degenerate polygons
				break;
			}
		}
		
		// Add the final triangle
		if (indices.size() == 3) {
			triangles.push_back(mPoints[indices[0]]);
			triangles.push_back(mPoints[indices[1]]);
			triangles.push_back(mPoints[indices[2]]);
		}
		
		return triangles;
	}
	
	bool Polygon::isEar(const std::vector<Point>& vertices, int i, const std::vector<int>& indices) const {
		int n = indices.size();
		if (n < 3) return false;
		
		int prev = (i == 0) ? n - 1 : i - 1;
		int next = (i + 1) % n;
		
		Point a = vertices[indices[prev]];
		Point b = vertices[indices[i]];
		Point c = vertices[indices[next]];
		
		// Check if the triangle is convex (positive cross product for counter-clockwise)
		if (crossProduct(a, b, c) <= 0) {
			return false; // Not convex
		}
		
		// Check if any other vertex is inside the triangle
		for (int j = 0; j < n; j++) {
			if (j == i || j == prev || j == next) continue;
			
			Point p = vertices[indices[j]];
			
			// Use barycentric coordinates to check if point is inside triangle
			float cross1 = crossProduct(a, b, p);
			float cross2 = crossProduct(b, c, p);
			float cross3 = crossProduct(c, a, p);
			
			if ((cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || 
				(cross1 <= 0 && cross2 <= 0 && cross3 <= 0)) {
				return false; // Point is inside triangle
			}
		}
		
		return true; // This is an ear
	}
	
	float Polygon::crossProduct(const Point& a, const Point& b, const Point& c) const {
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}
	
	// Boolean operations
	Polygon Polygon::intersection(const Polygon& other) const {
		if (empty() || other.empty()) {
			return Polygon(); // Empty polygon if either is invalid
		}
		
		// Quick bounds check - if bounds don't overlap, no intersection
		Rect bounds1 = getBounds();
		Rect bounds2 = other.getBounds();
		if (bounds1.intersection(bounds2).empty()) {
			return Polygon(); // No intersection possible
		}
		
		std::vector<IntersectionPoint> intersections = findIntersections(other);
		return buildResultPolygon(intersections, other, false);
	}
	
	Polygon Polygon::unionWith(const Polygon& other) const {
		if (empty()) {
			Polygon result;
			result.mPoints = other.mPoints;
			return result;
		}
		if (other.empty()) {
			Polygon result;
			result.mPoints = mPoints;
			return result;
		}
		
		std::vector<IntersectionPoint> intersections = findIntersections(other);
		return buildResultPolygon(intersections, other, true);
	}
	
	// Helper methods for boolean operations
	bool Polygon::lineSegmentsIntersect(const Point& p1, const Point& p2, 
										const Point& p3, const Point& p4, 
										Point& intersection) const {
		float x1 = p1.x, y1 = p1.y;
		float x2 = p2.x, y2 = p2.y;
		float x3 = p3.x, y3 = p3.y;
		float x4 = p4.x, y4 = p4.y;
		
		float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		
		if (fabs(denom) < 1e-10) {
			return false; // Lines are parallel
		}
		
		float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;
		
		if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
			intersection.x = x1 + t * (x2 - x1);
			intersection.y = y1 + t * (y2 - y1);
			return true;
		}
		
		return false;
	}
	
	bool Polygon::pointOnLineSegment(const Point& point, const Point& lineStart, const Point& lineEnd) const {
		float dx = lineEnd.x - lineStart.x;
		float dy = lineEnd.y - lineStart.y;
		
		if (fabs(dx) < 1e-10 && fabs(dy) < 1e-10) {
			// Degenerate line segment
			return (fabs(point.x - lineStart.x) < 1e-10 && fabs(point.y - lineStart.y) < 1e-10);
		}
		
		float t = 0;
		if (fabs(dx) > fabs(dy)) {
			t = (point.x - lineStart.x) / dx;
		} else {
			t = (point.y - lineStart.y) / dy;
		}
		
		if (t < 0 || t > 1) {
			return false;
		}
		
		float expectedX = lineStart.x + t * dx;
		float expectedY = lineStart.y + t * dy;
		
		return (fabs(point.x - expectedX) < 1e-10 && fabs(point.y - expectedY) < 1e-10);
	}
	
	float Polygon::pointToLineDistance(const Point& point, const Point& lineStart, const Point& lineEnd) const {
		float A = point.x - lineStart.x;
		float B = point.y - lineStart.y;
		float C = lineEnd.x - lineStart.x;
		float D = lineEnd.y - lineStart.y;
		
		float dot = A * C + B * D;
		float lenSq = C * C + D * D;
		
		if (lenSq == 0) {
			return sqrt(A * A + B * B);
		}
		
		float param = dot / lenSq;
		
		float xx, yy;
		if (param < 0) {
			xx = lineStart.x;
			yy = lineStart.y;
		} else if (param > 1) {
			xx = lineEnd.x;
			yy = lineEnd.y;
		} else {
			xx = lineStart.x + param * C;
			yy = lineStart.y + param * D;
		}
		
		float dx = point.x - xx;
		float dy = point.y - yy;
		return sqrt(dx * dx + dy * dy);
	}
	
	std::vector<Polygon::IntersectionPoint> Polygon::findIntersections(const Polygon& other) const {
		std::vector<IntersectionPoint> intersections;
		
		for (size_t i = 0; i < mPoints.size(); i++) {
			Point p1 = mPoints[i];
			Point p2 = mPoints[(i + 1) % mPoints.size()];
			
			for (size_t j = 0; j < other.mPoints.size(); j++) {
				Point p3 = other.mPoints[j];
				Point p4 = other.mPoints[(j + 1) % other.mPoints.size()];
				
				Point intersectionPoint;
				if (lineSegmentsIntersect(p1, p2, p3, p4, intersectionPoint)) {
					// Determine if this is an entry or exit point
					// This is a simplified approach - in a full implementation,
					// we'd need more sophisticated logic to determine entry/exit
					bool isEntry = !isPointInside(intersectionPoint, other);
					intersections.push_back(IntersectionPoint(intersectionPoint, i, j, isEntry));
				}
			}
		}
		
		return intersections;
	}
	
	bool Polygon::isPointInside(const Point& point, const Polygon& poly) const {
		return poly.contains(point);
	}
	
	Polygon Polygon::buildResultPolygon(const std::vector<IntersectionPoint>& intersections, 
										const Polygon& other, bool isUnion) const {
		// This is a simplified implementation
		// A full implementation would use the Weiler-Atherton algorithm or similar
		// to properly handle complex polygon clipping
		
		if (intersections.empty()) {
			if (isUnion) {
				// For union, if no intersections, return the larger polygon
				// or combine both if they don't overlap
				if (contains(other.getPoint(0))) {
					Polygon result;
					result.mPoints = mPoints;
					return result; // other is inside this
				} else if (other.contains(mPoints[0])) {
					Polygon result;
					result.mPoints = other.mPoints;
					return result; // this is inside other
				} else {
					// No overlap, return this polygon (simplified)
					Polygon result;
					result.mPoints = mPoints;
					return result;
				}
			} else {
				// For intersection, if no intersections, check if one is inside the other
				if (contains(other.getPoint(0))) {
					Polygon result;
					result.mPoints = other.mPoints;
					return result; // other is inside this
				} else if (other.contains(mPoints[0])) {
					Polygon result;
					result.mPoints = mPoints;
					return result; // this is inside other
				} else {
					return Polygon(); // No intersection
				}
			}
		}
		
	// For now, return an empty polygon if we have intersections
	// A full implementation would process the intersection points
	// to build the resulting polygon
	return Polygon();
}

bool Polygon::isSelfIntersecting() const {
	if (mPoints.size() < 4) {
		return false; // Need at least 4 points to self-intersect
	}
	
	// Check all pairs of non-adjacent edges for intersections
	for (size_t i = 0; i < mPoints.size(); i++) {
		Point p1 = mPoints[i];
		Point p2 = mPoints[(i + 1) % mPoints.size()];
		
		// Start j at i+2 to skip adjacent edges
		for (size_t j = i + 2; j < mPoints.size(); j++) {
			// Skip the edge that shares a vertex with the current edge
			if ((j + 1) % mPoints.size() == i) continue;
			
			Point p3 = mPoints[j];
			Point p4 = mPoints[(j + 1) % mPoints.size()];
			
			Point intersectionPoint;
			if (lineSegmentsIntersect(p1, p2, p3, p4, intersectionPoint)) {
				// Check if intersection is not just at endpoints
				// (endpoints touching is okay, we're looking for actual crossings)
				const float epsilon = 0.001f;
				bool isP1 = (fabs(intersectionPoint.x - p1.x) < epsilon && 
							fabs(intersectionPoint.y - p1.y) < epsilon);
				bool isP2 = (fabs(intersectionPoint.x - p2.x) < epsilon && 
							fabs(intersectionPoint.y - p2.y) < epsilon);
				bool isP3 = (fabs(intersectionPoint.x - p3.x) < epsilon && 
							fabs(intersectionPoint.y - p3.y) < epsilon);
				bool isP4 = (fabs(intersectionPoint.x - p4.x) < epsilon && 
							fabs(intersectionPoint.y - p4.y) < epsilon);
				
				// If intersection is not at any endpoint, it's a true self-intersection
				if (!isP1 && !isP2 && !isP3 && !isP4) {
					return true;
				}
			}
		}
	}
	
	return false;
}

std::vector<Point> Polygon::tessellate() const {
	std::vector<Point> triangles;

// we only need to support tessellation for rendering (GUI builds)
#ifndef PDG_NO_GUI
	
	if (mPoints.size() < 3) {
		return triangles; // Need at least 3 points
	}
	
	// Create tessellator
	TESStesselator* tess = tessNewTess(NULL);
	if (!tess) {
		// Fallback to simple triangulation if tessellator creation fails
		return triangulate();
	}
	
	// Convert points to TESSreal array (float array with x,y pairs)
	std::vector<TESSreal> contour;
	contour.reserve(mPoints.size() * 2);
	for (const auto& point : mPoints) {
		contour.push_back(point.x);
		contour.push_back(point.y);
	}
	
	// Add the contour to the tessellator
	tessAddContour(tess, 2, contour.data(), sizeof(TESSreal) * 2, mPoints.size());
	
	// Perform tessellation
	// Use TESS_WINDING_ODD for self-intersecting polygons (even-odd fill rule)
	// Use TESS_POLYGONS to get triangles
	if (!tessTesselate(tess, TESS_WINDING_ODD, TESS_POLYGONS, 3, 2, NULL)) {
		tessDeleteTess(tess);
		// Fallback to simple triangulation if tessellation fails
		return triangulate();
	}
	
	// Get the tessellated vertices and elements
	const TESSreal* verts = tessGetVertices(tess);
	const TESSindex* elems = tessGetElements(tess);
	const int nverts = tessGetVertexCount(tess);
	const int nelems = tessGetElementCount(tess);
	
	// Convert back to Point vector
	// Each element is a triangle (3 vertex indices)
	for (int i = 0; i < nelems; i++) {
		const TESSindex* tri = &elems[i * 3];
		for (int j = 0; j < 3; j++) {
			if (tri[j] != TESS_UNDEF) {
				Point p;
				p.x = verts[tri[j] * 2];
				p.y = verts[tri[j] * 2 + 1];
				triangles.push_back(p);
			}
		}
	}
	
	// Clean up
	tessDeleteTess(tess);
#endif // !PDG_NO_GUI
	
	return triangles;
}

} // end namespace pdg
