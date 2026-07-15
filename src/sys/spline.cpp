// -----------------------------------------------
//  Spline.cpp
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

#include "pdg_project.h"

#include "math.h"
#include "pdg/sys/spline.h"

namespace pdg {
	
	// Constructor - initialize member variables
	Spline::Spline(int type) : mType(type), mLooping(false), mCurrentSegment(0), mBoundsDirty(true) {
		for (int i = 0; i < 4; i++) {
			mCurrentSegmentIndices[i] = i;
		}
		if (!isMultiSegmentSplineType()) {
			mLooping = true;
		}
	}
	
	// Move constructor
	Spline::Spline(Spline&& other) noexcept 
		: mType(other.mType), 
		  mPoints(std::move(other.mPoints)), 
		  mLooping(other.mLooping),
		  mCurrentSegment(other.mCurrentSegment),
		  mCachedBounds(std::move(other.mCachedBounds)),
		  mBoundsDirty(other.mBoundsDirty)
	{
		// Move the current segment indices
		for (int i = 0; i < 4; i++) {
			mCurrentSegmentIndices[i] = other.mCurrentSegmentIndices[i];
		}
		
		#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
			mSplineScriptObj = std::move(other.mSplineScriptObj);
		#endif
	}
	
	// Move assignment operator
	Spline& Spline::operator=(Spline&& other) noexcept {
		if (this != &other) {
			#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
				CleanupSplineScriptObject(mSplineScriptObj);
			#endif
			
			mType = other.mType;
			mPoints = std::move(other.mPoints);
			mLooping = other.mLooping;
			mCurrentSegment = other.mCurrentSegment;
			mCachedBounds = std::move(other.mCachedBounds);
			mBoundsDirty = other.mBoundsDirty;
			
			// Move the current segment indices
			for (int i = 0; i < 4; i++) {
				mCurrentSegmentIndices[i] = other.mCurrentSegmentIndices[i];
			}
			
			#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
				mSplineScriptObj = std::move(other.mSplineScriptObj);
			#endif
		}
		return *this;
	}
	
	// Check if this spline type is valid for multi-segment operations
	bool Spline::isMultiSegmentSplineType() const {
		// Exclude Hermite and TCB for now - they need special tangent handling
		return (mType != SPLINE_HERMITE && mType != SPLINE_TCB);
	}
	
	// Get number of points needed per segment (after first segment)
	int Spline::getPointsPerSegment() const {
		switch (mType) {
			case SPLINE_CUBIC_BEZIER:
				return 3;  // Shares endpoint, adds 3 new points per segment
			
			case SPLINE_CARDINAL:
			case SPLINE_UNIFORM_B:
			case SPLINE_NATURAL_CUBIC:
				return 1;  // Sliding window, adds 1 point per segment
			
			default:
				return 3;  // Default to Bezier behavior
		}
	}
	
	// Get the number of complete segments in the spline
	int Spline::getSegmentCount() const {
		int pointCount = mPoints.size();
		if (pointCount < 4) {
			return 0;  // Need at least 4 points for one segment
		}
		
		switch (mType) {
			case SPLINE_CUBIC_BEZIER:
				// First segment uses 4 points, each additional segment adds 3
				return 1 + ((pointCount - 4) / 3);
			
			case SPLINE_CARDINAL:
			case SPLINE_UNIFORM_B:
			case SPLINE_NATURAL_CUBIC:
				// Sliding window: n points = n-3 segments
				return pointCount - 3;
			
			default:
				return 1;
		}
	}
	
	// Get maximum valid u parameter value
	float Spline::getMaxU() const {
		return (float)getSegmentCount();
	}
	
	// Get bounding rectangle of the spline
	Rect Spline::getBounds() const {
		if (mPoints.empty()) {
			mCachedBounds = Rect(0, 0, 0, 0);
			mBoundsDirty = false;
			return mCachedBounds;
		}
		
		// Return cached bounds if they're still valid
		if (!mBoundsDirty) {
			return mCachedBounds;
		}
		
		// Recalculate bounds from control points
		float minX = mPoints[0].x;
		float maxX = mPoints[0].x;
		float minY = mPoints[0].y;
		float maxY = mPoints[0].y;
		
		for (const auto& point : mPoints) {
			minX = std::min(minX, point.x);
			maxX = std::max(maxX, point.x);
			minY = std::min(minY, point.y);
			maxY = std::max(maxY, point.y);
		}
		
		// Cache the result
		mCachedBounds = Rect(minX, minY, maxX, maxY);
		mBoundsDirty = false;
		
		return mCachedBounds;
	}
	
	// Get total number of points stored
	int Spline::getPointCount() const {
		return (int)mPoints.size();
	}
	
	// Update internal indices to point to the correct segment
	void Spline::updateSegmentIndices(int segmentNum) {
		if (mPoints.size() < 4 || segmentNum < 0) {
			return;
		}
		
		mCurrentSegment = segmentNum;
		
		switch (mType) {
			case SPLINE_CUBIC_BEZIER:
				// Bezier: segment 0 = [0,1,2,3], segment 1 = [3,4,5,6], etc.
				mCurrentSegmentIndices[0] = segmentNum * 3;
				mCurrentSegmentIndices[1] = segmentNum * 3 + 1;
				mCurrentSegmentIndices[2] = segmentNum * 3 + 2;
				mCurrentSegmentIndices[3] = segmentNum * 3 + 3;
				break;
			
			case SPLINE_CARDINAL:
			case SPLINE_UNIFORM_B:
			case SPLINE_NATURAL_CUBIC:
				// Sliding window: segment 0 = [0,1,2,3], segment 1 = [1,2,3,4], etc.
				mCurrentSegmentIndices[0] = segmentNum;
				mCurrentSegmentIndices[1] = segmentNum + 1;
				mCurrentSegmentIndices[2] = segmentNum + 2;
				mCurrentSegmentIndices[3] = segmentNum + 3;
				break;
			
			default:
				// Default to Bezier behavior
				mCurrentSegmentIndices[0] = segmentNum * 3;
				mCurrentSegmentIndices[1] = segmentNum * 3 + 1;
				mCurrentSegmentIndices[2] = segmentNum * 3 + 2;
				mCurrentSegmentIndices[3] = segmentNum * 3 + 3;
				break;
		}
		
		// Clamp indices to valid range
		for (int i = 0; i < 4; i++) {
			if (mCurrentSegmentIndices[i] >= mPoints.size()) {
				mCurrentSegmentIndices[i] = mPoints.size() - 1;
			}
		}
	}
	
	Point Spline::getFirstOrder(float u) const {
		int segmentCount = getSegmentCount();
		if (segmentCount == 0 || u < 0.0f) {
			return Point(0, 0);  // Error case
		}
		
		// Clamp to valid range
		float maxU = (float)segmentCount;
		if (u > maxU) {
			u = maxU;
		}
		
		// Determine which segment and local parameter
		int segmentNum = (int)floor(u);
		float localU = u - (float)segmentNum;
		
		// Handle exact endpoint case (u = N exactly)
		if (segmentNum >= segmentCount) {
			segmentNum = segmentCount - 1;
			localU = 1.0f;
		}
		
		// Update indices to point to correct segment
		const_cast<Spline*>(this)->updateSegmentIndices(segmentNum);
		
		float X,Y;
		float s, u2, u3, t, t2, t3;
		float tension, continuity, bias, a, b, c, d;
		float h1, h2, m1, m2;
		
		// Use localU for evaluation within the segment
		u = localU;
		
		switch (mType) {
			case SPLINE_HERMITE:
				// Hermite spline: H(u) = h1(u)*p1 + h2(u)*p2 + h3(u)*t1 + h4(u)*t2
				// PDG uses parameter order: (p1, p2, t1, t2)
				// where p1, p2 are positions and t1, t2 are tangent vectors
				X = mPoints[mCurrentSegmentIndices[0]].x * (2*u*u*u - 3*u*u + 1);
				X += mPoints[mCurrentSegmentIndices[1]].x * (-2*u*u*u + 3*u*u);
				X += mPoints[mCurrentSegmentIndices[2]].x * (u*u*u - 2*u*u + u);
				X += mPoints[mCurrentSegmentIndices[3]].x * (u*u*u - u*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (2*u*u*u - 3*u*u + 1);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (-2*u*u*u + 3*u*u);
				Y += mPoints[mCurrentSegmentIndices[2]].y * (u*u*u - 2*u*u + u);
				Y += mPoints[mCurrentSegmentIndices[3]].y * (u*u*u - u*u);
				break;
				
			case SPLINE_CARDINAL:
				// Cardinal spline (Catmull-Rom) with tension parameter = 0.5
				s = 0.5f; // tension parameter
				X = mPoints[mCurrentSegmentIndices[0]].x * (-s*u*u*u + 2*s*u*u - s*u);
				X += mPoints[mCurrentSegmentIndices[1]].x * ((2-s)*u*u*u + (s-3)*u*u + 1);
				X += mPoints[mCurrentSegmentIndices[2]].x * ((s-2)*u*u*u + (3-2*s)*u*u + s*u);
				X += mPoints[mCurrentSegmentIndices[3]].x * (s*u*u*u - s*u*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (-s*u*u*u + 2*s*u*u - s*u);
				Y += mPoints[mCurrentSegmentIndices[1]].y * ((2-s)*u*u*u + (s-3)*u*u + 1);
				Y += mPoints[mCurrentSegmentIndices[2]].y * ((s-2)*u*u*u + (3-2*s)*u*u + s*u);
				Y += mPoints[mCurrentSegmentIndices[3]].y * (s*u*u*u - s*u*u);
				break;
				
			case SPLINE_UNIFORM_B:
				// Uniform B-spline cubic basis functions
				u2 = u * u;
				u3 = u * u2;
				t = 1.0f - u;
				t2 = t * t;
				t3 = t * t2;
				
				X = mPoints[mCurrentSegmentIndices[0]].x * (t3 / 6.0f);
				X += mPoints[mCurrentSegmentIndices[1]].x * ((3*u3 - 6*u2 + 4) / 6.0f);
				X += mPoints[mCurrentSegmentIndices[2]].x * ((-3*u3 + 3*u2 + 3*u + 1) / 6.0f);
				X += mPoints[mCurrentSegmentIndices[3]].x * (u3 / 6.0f);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (t3 / 6.0f);
				Y += mPoints[mCurrentSegmentIndices[1]].y * ((3*u3 - 6*u2 + 4) / 6.0f);
				Y += mPoints[mCurrentSegmentIndices[2]].y * ((-3*u3 + 3*u2 + 3*u + 1) / 6.0f);
				Y += mPoints[mCurrentSegmentIndices[3]].y * (u3 / 6.0f);
				break;
				
			case SPLINE_CUBIC_BEZIER:
				// Cubic Bezier spline (4 control points: P0, P1, P2, P3)
				u2 = u * u;
				u3 = u * u2;
				t = 1.0f - u;
				t2 = t * t;
				t3 = t * t2;
				
				X = mPoints[mCurrentSegmentIndices[0]].x * t3;
				X += mPoints[mCurrentSegmentIndices[1]].x * (3 * t2 * u);
				X += mPoints[mCurrentSegmentIndices[2]].x * (3 * t * u2);
				X += mPoints[mCurrentSegmentIndices[3]].x * u3;
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * t3;
				Y += mPoints[mCurrentSegmentIndices[1]].y * (3 * t2 * u);
				Y += mPoints[mCurrentSegmentIndices[2]].y * (3 * t * u2);
				Y += mPoints[mCurrentSegmentIndices[3]].y * u3;
				break;
				
			case SPLINE_TCB:
				// Kochanek-Bartels (TCB) spline with tension, continuity, bias parameters
				// Using default values: tension=0, continuity=0, bias=0 (Cardinal spline)
				tension = 0.0f;   // -1 to 1, controls tightness
				continuity = 0.0f; // -1 to 1, controls continuity at knots
				bias = 0.0f;      // -1 to 1, controls direction of curve
				
				// Calculate TCB parameters
				a = (1 - tension) * (1 + continuity) * (1 + bias) / 2.0f;
				b = (1 - tension) * (1 - continuity) * (1 - bias) / 2.0f;
				c = (1 - tension) * (1 + continuity) * (1 - bias) / 2.0f;
				d = (1 - tension) * (1 - continuity) * (1 + bias) / 2.0f;
				
				X = mPoints[mCurrentSegmentIndices[0]].x * (2*u*u*u - 3*u*u + 1);
				X += mPoints[mCurrentSegmentIndices[1]].x * (-2*u*u*u + 3*u*u);
				X += (mPoints[mCurrentSegmentIndices[1]].x - mPoints[mCurrentSegmentIndices[0]].x) * a * (u*u*u - 2*u*u + u);
				X += (mPoints[mCurrentSegmentIndices[2]].x - mPoints[mCurrentSegmentIndices[1]].x) * b * (u*u*u - 2*u*u + u);
				X += (mPoints[mCurrentSegmentIndices[2]].x - mPoints[mCurrentSegmentIndices[1]].x) * c * (u*u*u - u*u);
				X += (mPoints[mCurrentSegmentIndices[3]].x - mPoints[mCurrentSegmentIndices[2]].x) * d * (u*u*u - u*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (2*u*u*u - 3*u*u + 1);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (-2*u*u*u + 3*u*u);
				Y += (mPoints[mCurrentSegmentIndices[1]].y - mPoints[mCurrentSegmentIndices[0]].y) * a * (u*u*u - 2*u*u + u);
				Y += (mPoints[mCurrentSegmentIndices[2]].y - mPoints[mCurrentSegmentIndices[1]].y) * b * (u*u*u - 2*u*u + u);
				Y += (mPoints[mCurrentSegmentIndices[2]].y - mPoints[mCurrentSegmentIndices[1]].y) * c * (u*u*u - u*u);
				Y += (mPoints[mCurrentSegmentIndices[3]].y - mPoints[mCurrentSegmentIndices[2]].y) * d * (u*u*u - u*u);
				break;
				
			case SPLINE_NATURAL_CUBIC:
				// Natural cubic spline - ensures continuous second derivatives
				// NOTE: This uses a simplified local implementation. In the future, we may want to
				// recalculate the entire spline's tangents globally whenever any segment changes,
				// to ensure true C2 continuity across all segments.
				// Simplified implementation using finite differences for tangents
				h1 = 1.0f; // assuming uniform spacing
				h2 = 1.0f;
				
				// Calculate natural cubic spline coefficients
				m1 = (mPoints[mCurrentSegmentIndices[2]].y - mPoints[mCurrentSegmentIndices[0]].y) / (2.0f * h1);
				m2 = (mPoints[mCurrentSegmentIndices[3]].y - mPoints[mCurrentSegmentIndices[1]].y) / (2.0f * h2);
				
				// Hermite form with calculated tangents
				X = mPoints[mCurrentSegmentIndices[0]].x * (2*u*u*u - 3*u*u + 1);
				X += mPoints[mCurrentSegmentIndices[1]].x * (-2*u*u*u + 3*u*u);
				X += m1 * (u*u*u - 2*u*u + u);
				X += m2 * (u*u*u - u*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (2*u*u*u - 3*u*u + 1);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (-2*u*u*u + 3*u*u);
				Y += m1 * (u*u*u - 2*u*u + u);
				Y += m2 * (u*u*u - u*u);
				break;
				
		}
		return PointT<float>(X,Y);
	}
	
	
	Point Spline::getSecondOrder(float u) const {
		int segmentCount = getSegmentCount();
		if (segmentCount == 0 || u < 0.0f) {
			return Point(0, 0);  // Error case
		}
		
		// Clamp to valid range
		float maxU = (float)segmentCount;
		if (u > maxU) {
			u = maxU;
		}
		
		// Determine which segment and local parameter
		int segmentNum = (int)floor(u);
		float localU = u - (float)segmentNum;
		
		// Handle exact endpoint case (u = N exactly)
		if (segmentNum >= segmentCount) {
			segmentNum = segmentCount - 1;
			localU = 1.0f;
		}
		
		// Update indices to point to correct segment
		const_cast<Spline*>(this)->updateSegmentIndices(segmentNum);
		
		float X,Y;
		float s, u2;
		float tension, continuity, bias, a, b, c, d;
		float h1, h2, m1, m2;
		float u3, t, t2, t3;
		
		// Use localU for evaluation within the segment
		u = localU;
		
		switch (mType) {
			case SPLINE_HERMITE:
				// Derivative of Hermite spline
				X = mPoints[mCurrentSegmentIndices[0]].x * (6*u*u - 6*u);
				X += mPoints[mCurrentSegmentIndices[1]].x * (-6*u*u + 6*u);
				X += mPoints[mCurrentSegmentIndices[2]].x * (3*u*u - 4*u + 1);
				X += mPoints[mCurrentSegmentIndices[3]].x * (3*u*u - 2*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (6*u*u - 6*u);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (-6*u*u + 6*u);
				Y += mPoints[mCurrentSegmentIndices[2]].y * (3*u*u - 4*u + 1);
				Y += mPoints[mCurrentSegmentIndices[3]].y * (3*u*u - 2*u);
				break;
				
			case SPLINE_CARDINAL:
				// Second derivative of Cardinal spline (Catmull-Rom)
				s = 0.5f; // tension parameter
				X = mPoints[mCurrentSegmentIndices[0]].x * (-3*s*u*u + 4*s*u - s);
				X += mPoints[mCurrentSegmentIndices[1]].x * (3*(2-s)*u*u + 2*(s-3)*u);
				X += mPoints[mCurrentSegmentIndices[2]].x * (3*(s-2)*u*u + 2*(3-2*s)*u + s);
				X += mPoints[mCurrentSegmentIndices[3]].x * (3*s*u*u - 2*s*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (-3*s*u*u + 4*s*u - s);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (3*(2-s)*u*u + 2*(s-3)*u);
				Y += mPoints[mCurrentSegmentIndices[2]].y * (3*(s-2)*u*u + 2*(3-2*s)*u + s);
				Y += mPoints[mCurrentSegmentIndices[3]].y * (3*s*u*u - 2*s*u);
				break;
			
			case SPLINE_UNIFORM_B:
				// Second derivative of Uniform B-spline
				u2 = u * u;
				X = mPoints[mCurrentSegmentIndices[0]].x * ((3*u*u - 6*u + 3) / 6.0f);
				X += mPoints[mCurrentSegmentIndices[1]].x * ((9*u*u - 12*u) / 6.0f);
				X += mPoints[mCurrentSegmentIndices[2]].x * ((-9*u*u + 6*u + 3) / 6.0f);
				X += mPoints[mCurrentSegmentIndices[3]].x * (3*u*u / 6.0f);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * ((3*u*u - 6*u + 3) / 6.0f);
				Y += mPoints[mCurrentSegmentIndices[1]].y * ((9*u*u - 12*u) / 6.0f);
				Y += mPoints[mCurrentSegmentIndices[2]].y * ((-9*u*u + 6*u + 3) / 6.0f);
				Y += mPoints[mCurrentSegmentIndices[3]].y * (3*u*u / 6.0f);
				break;
				
			case SPLINE_CUBIC_BEZIER:
				// Second derivative of Cubic Bezier spline
				u2 = u * u;
				u3 = u * u2;
				t = 1.0f - u;
				t2 = t * t;
				t3 = t * t2;
				
				X = mPoints[mCurrentSegmentIndices[0]].x * (6*t);
				X += mPoints[mCurrentSegmentIndices[1]].x * (6*t - 12*u);
				X += mPoints[mCurrentSegmentIndices[2]].x * (12*u - 6*t);
				X += mPoints[mCurrentSegmentIndices[3]].x * (6*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (6*t);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (6*t - 12*u);
				Y += mPoints[mCurrentSegmentIndices[2]].y * (12*u - 6*t);
				Y += mPoints[mCurrentSegmentIndices[3]].y * (6*u);
				break;
				
			case SPLINE_TCB:
				// Second derivative of TCB spline
				tension = 0.0f;
				continuity = 0.0f;
				bias = 0.0f;
				
				a = (1 - tension) * (1 + continuity) * (1 + bias) / 2.0f;
				b = (1 - tension) * (1 - continuity) * (1 - bias) / 2.0f;
				c = (1 - tension) * (1 + continuity) * (1 - bias) / 2.0f;
				d = (1 - tension) * (1 - continuity) * (1 + bias) / 2.0f;
				
				X = mPoints[mCurrentSegmentIndices[0]].x * (6*u - 6);
				X += mPoints[mCurrentSegmentIndices[1]].x * (-6*u + 6);
				X += (mPoints[mCurrentSegmentIndices[1]].x - mPoints[mCurrentSegmentIndices[0]].x) * a * (3*u*u - 4*u + 1);
				X += (mPoints[mCurrentSegmentIndices[2]].x - mPoints[mCurrentSegmentIndices[1]].x) * b * (3*u*u - 4*u + 1);
				X += (mPoints[mCurrentSegmentIndices[2]].x - mPoints[mCurrentSegmentIndices[1]].x) * c * (3*u*u - 2*u);
				X += (mPoints[mCurrentSegmentIndices[3]].x - mPoints[mCurrentSegmentIndices[2]].x) * d * (3*u*u - 2*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (6*u - 6);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (-6*u + 6);
				Y += (mPoints[mCurrentSegmentIndices[1]].y - mPoints[mCurrentSegmentIndices[0]].y) * a * (3*u*u - 4*u + 1);
				Y += (mPoints[mCurrentSegmentIndices[2]].y - mPoints[mCurrentSegmentIndices[1]].y) * b * (3*u*u - 4*u + 1);
				Y += (mPoints[mCurrentSegmentIndices[2]].y - mPoints[mCurrentSegmentIndices[1]].y) * c * (3*u*u - 2*u);
				Y += (mPoints[mCurrentSegmentIndices[3]].y - mPoints[mCurrentSegmentIndices[2]].y) * d * (3*u*u - 2*u);
				break;
				
			case SPLINE_NATURAL_CUBIC:
				// Second derivative of Natural cubic spline
				h1 = 1.0f;
				h2 = 1.0f;
				m1 = (mPoints[mCurrentSegmentIndices[2]].y - mPoints[mCurrentSegmentIndices[0]].y) / (2.0f * h1);
				m2 = (mPoints[mCurrentSegmentIndices[3]].y - mPoints[mCurrentSegmentIndices[1]].y) / (2.0f * h2);
				
				X = mPoints[mCurrentSegmentIndices[0]].x * (6*u - 6);
				X += mPoints[mCurrentSegmentIndices[1]].x * (-6*u + 6);
				X += m1 * (3*u*u - 4*u + 1);
				X += m2 * (3*u*u - 2*u);
				
				Y = mPoints[mCurrentSegmentIndices[0]].y * (6*u - 6);
				Y += mPoints[mCurrentSegmentIndices[1]].y * (-6*u + 6);
				Y += m1 * (3*u*u - 4*u + 1);
				Y += m2 * (3*u*u - 2*u);
				break;
				
		}
		return PointT<float>(X,Y);
	}
	
	// High-level segment API
	void Spline::addSegment(Point p1, Point p2, Point p3, Point p4) {
		if (mPoints.empty()) {
			// First segment - add all 4 points
			mPoints.push_back(p1);
			mPoints.push_back(p2);
			mPoints.push_back(p3);
			mPoints.push_back(p4);
			updateSegmentIndices(0);
		} else {
			// Additional segments - adjust points for continuity and add based on spline type
			Point lastEndpoint = mPoints[mPoints.size() - 1];
			
			// Calculate delta to make p1 match the last endpoint
			Point delta(lastEndpoint.x - p1.x, lastEndpoint.y - p1.y);
			
			// Shift all incoming points by the delta
			p2.x += delta.x;
			p2.y += delta.y;
			p3.x += delta.x;
			p3.y += delta.y;
			p4.x += delta.x;
			p4.y += delta.y;
			
			// Add points based on spline type
			switch (mType) {
				case SPLINE_CUBIC_BEZIER:
					// Bezier: endpoint is shared, add 3 new points
					mPoints.push_back(p2);
					mPoints.push_back(p3);
					mPoints.push_back(p4);
					break;
				
				case SPLINE_CARDINAL:
				case SPLINE_UNIFORM_B:
				case SPLINE_NATURAL_CUBIC:
					// Sliding window: add 1 new point (p4)
					// Note: p2 and p3 are ignored for sliding window splines
					// For these types, user should call addPoint directly for more control
					mPoints.push_back(p4);
					break;
				
				default:
					// Default to Bezier behavior
					mPoints.push_back(p2);
					mPoints.push_back(p3);
					mPoints.push_back(p4);
					break;
			}
		}
		
		// Invalidate bounds since we added points
		invalidateBounds();
	}
	
	// Low-level point API
	void Spline::addPoint(Point p) {
		mPoints.push_back(p);
		invalidateBounds();
	}
	
	Point Spline::getPoint(int pointIndex) const {
		if (pointIndex < 0 || pointIndex >= (int)mPoints.size()) {
			return Point(0, 0);  // Return zero point for invalid index
		}
		return mPoints[pointIndex];
	}
	
	void Spline::setPoint(int pointIndex, Point p) {
		if (pointIndex >= 0 && pointIndex < (int)mPoints.size()) {
			mPoints[pointIndex] = p;
			invalidateBounds();
		}
	}
	
} // end namespace pdg
