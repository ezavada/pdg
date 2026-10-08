// -----------------------------------------------
// coordinates.js
//
// Definitions for coordinate classes
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

// this is one of the few javascript files that are built-in
// to the pdg standalone app but also part of the pure 
// javascript implementation

// -----------------------------------------------------------------------------------
// Offset
// -----------------------------------------------------------------------------------
// An x and y offset in 2 dimensional space

// @pdg-class {"name":"Offset","native_binding":{"browser":{"generate":true,"kind":"value_object","binding_name":"_OffsetValue","type":"pdg::Offset","fields":["x","y"],"return_value":{"arguments":["$"]}}}}
class Offset {
	//! new Offset() create a point at the origin (0,0)
	//! new Offset(x,y): create a point and set its x & y values
	//! new Offset([x,y]): create a point and set its x & y values
	//! new Offset({x:x,y:y}): create a point and set its x & y values
/* @pdg-member
{
  "name": "Offset.Offset",
  "type": "constructor",
  "brief": "create and set x & y values",
  "returns": "object Offset",
  "params": [
    [],
    [
      {
        "name": "x",
        "type": "number"
      },
      {
        "name": "y",
        "type": "number"
      }
    ],
    [
      {
        "name": "xy",
        "type": "number[]"
      }
    ],
    [
      {
        "name": "xy",
        "type": "object"
      }
    ]
  ]
}
*/
	constructor(ix, iy) {
		if (arguments.length == 1) {
			if (ix === null) {
// @pdg-member {"name":"Offset.x","type":"number"}
// @pdg-member {"name":"Offset.y","type":"number"}
				this.x = 0; this.y = 0;
			} else if (ix instanceof Offset || typeof ix.x != "undefined") {
				// initializing from another Offset object
				this.x = ix.x; this.y = ix.y;
			} else if (ix instanceof Array) {
				this.x = ix[0]; this.y = ix[1];
			} else {
				this.x = 0; this.y = 0;
			}
		} else {
			this.x = (ix) ? ix : 0; this.y = (iy) ? iy : 0;
		}
	}

	// operators
	//! return true if this point is equal to the other
	// @pdg-member {"name":"Offset.equals","type":"function","brief":"return true if this point is equal to the other","params":[{"name":"offset","type":"object Offset"}],"returns":"boolean"}
	equals(offset) {
		return ((this.x == offset.x) && (this.y == offset.y));
	}
	// @pdg-member {"name":"Offset.notEquals","type":"function","brief":"return true if this point is not equal to the other","params":[{"name":"offset","type":"object Offset"}],"returns":"boolean"}
	notEquals(offset) {
		return ((this.x != offset.x) || (this.y != offset.y));
	}
	// @pdg-member {"name":"Offset.assign","type":"function","brief":"set this offset equal to the given offset","params":[{"name":"offset","type":"object Offset"}],"returns":"this"}
	assign(offset) {
		this.x = offset.x; this.y = offset.y; return this;
	}
	// unary operators:   myOffset.add(otherOffset)
	// @pdg-member {"name":"Offset.add","type":"function","brief":"add an offset to this one","params":[{"name":"offset","type":"object Offset"}],"returns":"this"}
	add(offset) {
		this.x += offset.x; this.y += offset.y; return this;
	}
	// @pdg-member {"name":"Offset.sub","type":"function","brief":"subtract an offset from this one","params":[{"name":"offset","type":"object Offset"}],"returns":"this"}
	sub(offset) {
		this.x -= offset.x; this.y -= offset.y; return this;
	}
	// @pdg-member {"name":"Offset.mul","type":"function","brief":"multiply this offset by the given one","params":[{"name":"offset","type":"object Offset"}],"returns":"this"}
	mul(offset) {
		this.x *= offset.x; this.y *= offset.y; return this;
	}
	// @pdg-member {"name":"Offset.div","type":"function","brief":"divide this offset by the given one","params":[{"name":"offset","type":"object Offset"}],"returns":"this"}
	div(offset) {
		this.x /= offset.x; this.y /= offset.y; return this;
	}
	// binary operators:   newOffset = myOffset.plus(otherOffset).plus(thirdOffset);
	// @pdg-member {"name":"Offset.plus","type":"function","brief":"return new offset that is this offset plus given offset","params":[{"name":"offset","type":"object Offset"}],"returns":"object Offset"}
	plus(offset) {
		var o = new Offset(this.x, this.y); return o.add(offset);
	}
	// @pdg-member {"name":"Offset.minus","type":"function","brief":"return new offset that is this offset minus given offset","params":[{"name":"offset","type":"object Offset"}],"returns":"object Offset"}
	minus(offset) {
		var o = new Offset(this.x, this.y); return o.sub(offset);
	}
	// @pdg-member {"name":"Offset.times","type":"function","brief":"return new offset that is this offset multiplied by given offset","params":[{"name":"offset","type":"object Offset"}],"returns":"object Offset"}
	times(offset) {
		var o = new Offset(this.x, this.y); return o.mul(offset);
	}
	// @pdg-member {"name":"Offset.dividedby","type":"function","brief":"return new offset that is this offset divided by given offset","params":[{"name":"offset","type":"object Offset"}],"returns":"object Offset"}
	dividedby(offset) {
		var o = new Offset(this.x, this.y); return o.div(offset);
	}
	// @pdg-member {"name":"Offset.vector","type":"function","brief":"return a new vector from this offset","params":[],"returns":"object Vector"}
	vector() {
		return new Vector(this.x, this.y);
	}
	toString() {
		return "Offset("+this.x+","+this.y+")";
	}
}

// -----------------------------------------------------------------------------------
// Point
// -----------------------------------------------------------------------------------
// A location in a 2 dimensional cartesian coordinate system

// @pdg-class {"name":"Point","native_binding":{"browser":{"generate":true,"kind":"value_object","binding_name":"_PointValue","type":"pdg::Point","fields":["x","y"],"return_value":{"arguments":["$"]}}}}
/* @pdg-member
{
  "name": "Point.Point",
  "type": "constructor",
  "brief": "create and set x & y values",
  "returns": "object Point",
  "params": [
    [],
    [
      {
        "name": "x",
        "type": "number"
      },
      {
        "name": "y",
        "type": "number"
      }
    ],
    [
      {
        "name": "xy",
        "type": "number[]"
      }
    ],
    [
      {
        "name": "xy",
        "type": "object"
      }
    ]
  ]
}
*/
// @pdg-member {"name":"Point.x","type":"number"}
// @pdg-member {"name":"Point.y","type":"number"}
class Point extends Offset {
	//! get distance from another point
	// @pdg-member {"name":"Point.distance","type":"function","brief":"get distance from another point","params":[{"name":"point","type":"object Point"}],"returns":"number"}
	distance(point) {
		var dx = point.x - this.x;
		var dy = point.y - this.y;
		return Math.sqrt( (dx * dx) + (dy * dy) );
	}
	//! get the offset of this point from another point, ie: A.offset(B) = B - A
	// @pdg-member {"name":"Point.offset","type":"function","brief":"get the offset of this point from another point","params":[{"name":"point","type":"object Point"}],"returns":"object Offset"}
	offset(point) {
		return new Offset(point.x - this.x, point.y - this.y);
	}
	toString() {
		return "Point("+this.x+","+this.y+")";
	}
}

// -----------------------------------------------------------------------------------
// Vector
// -----------------------------------------------------------------------------------
// 2 dimensional vector has magnitude and direction, useful for physics stuff

// @pdg-class {"name":"Vector","native_binding":{"browser":{"generate":true,"kind":"value_object","binding_name":"_VectorValue","type":"pdg::Vector","fields":["x","y"],"return_value":{"arguments":["$"]}}}}
/* @pdg-member
{
  "name": "Vector.Vector",
  "type": "constructor",
  "brief": "create and set x & y values",
  "returns": "object Vector",
  "params": [
    [],
    [
      {
        "name": "x",
        "type": "number"
      },
      {
        "name": "y",
        "type": "number"
      }
    ],
    [
      {
        "name": "xy",
        "type": "number[]"
      }
    ],
    [
      {
        "name": "xy",
        "type": "object"
      }
    ]
  ]
}
*/
// @pdg-member {"name":"Vector.x","type":"number"}
// @pdg-member {"name":"Vector.y","type":"number"}
class Vector extends Offset {
	//! get the unit vector of this vector, ie: A.unit() = (A.x / |A|, A.y / |A|)
	// @pdg-member {"name":"Vector.unit","type":"function","brief":"get the unit vector of this vector, ie: A.unit() = (A.x / |A|, A.y / |A|)","params":[],"returns":"object Vector"}
	unit() {
		var len = this.vectorLength();
		return new Vector(this.x / len, this.y / len);
	}
	//! get the normal of this vector (perpendicular to this vector), ie: A.normal() = (-A.y, A.x)
	// @pdg-member {"name":"Vector.normal","type":"function","brief":"get the normal of this vector, ie: A.normal() = (-A.y, A.x)","params":[],"returns":"object Vector"}
	normal() {
		return new Vector(-this.y, this.x);
	}
	//! get dot product for this vector with a 2nd vector
	// @pdg-member {"name":"Vector.dotProduct","type":"function","brief":"get dot product for this vector with a 2nd vector","params":[{"name":"vector","type":"object Vector"}],"returns":"number"}
	dotProduct(vector) {
		return (this.x * vector.x) + (this.y * vector.y);
	}
	//! get length as a vector (distance from origin)
	// @pdg-member {"name":"Vector.vectorLength","type":"function","brief":"get length as a vector (distance from origin)","params":[],"returns":"number"}
	vectorLength() {
		return Math.sqrt( (this.x * this.x) + (this.y * this.y) );
	}
	//! get angle (in radians) for this vector
	// @pdg-member {"name":"Vector.vectorAngle","type":"function","brief":"get angle (in radians) for this vector","params":[],"returns":"number"}
	vectorAngle() {
		return Math.atan2(this.y, this.x);
	}
	//! do a projection of a point onto the line defined by this vector, ie: A.projection(B) = ((A . B) / |B|^2) * B
	// @pdg-member {"name":"Vector.projection","type":"function","brief":"projection of a point onto the line defined by this vector, ie: A.projection(B) = ((A . B) / |B|^2) * B","params":[{"name":"point","type":"object Point"}],"returns":"object Point"}
	projection(point) {
		var dp = (this.x * point.x) + (this.y * point.y);
		var lenBSq = point.x * point.x + point.y * point.y;
		var projectionPt = new Point();
		projectionPt.x = (dp / lenBSq) * point.x;
		projectionPt.y = (dp/ lenBSq) * point.y;
		return projectionPt;
	}
	toString() {
		return "Vector("+this.x+","+this.y+")";
	}
}

// -----------------------------------------------------------------------------------
// Rect
// -----------------------------------------------------------------------------------
// 2 dimensional box where left and right sides are parallel to the y axis and 
// top and bottom sides are parallel to the x axis

// @pdg-class {"name":"Rect","native_binding":{"browser":{"generate":true,"kind":"value_object","binding_name":"_RectValue","type":"pdg::Rect","fields":["left","top","right","bottom"],"return_value":{"arguments":["$"]}}}}
class Rect {
	//! new Rect(): create an empty rectangle with origin at (0,0)
	//! new Rect(w,h): create a rectangle with origin at (0,0) and set its height and width values
	//! new Rect([Point] tl,[Point] br): create a rectangle given its top left and bottom right corner points
	//! new Rect([Point] tl,w,h): create a rectangle given its top teft corner point and a height and width
	//! new Rect(l,t,r,b): create a rectangle with left, top, right, and bottom coordinates (x1, y1, x2, y2) specified
/* @pdg-member
{
  "name": "Rect.Rect",
  "type": "constructor",
  "brief": "create a new Rect",
  "returns": "object Rect",
  "params": [
    [],
    [
      {
        "name": "w",
        "type": "number"
      },
      {
        "name": "h",
        "type": "number"
      }
    ],
    [
      {
        "name": "topLeft",
        "type": "object Point"
      },
      {
        "name": "w",
        "type": "number"
      },
      {
        "name": "h",
        "type": "number"
      }
    ],
    [
      {
        "name": "leftTop",
        "type": "object Point"
      },
      {
        "name": "rightBottom",
        "type": "object Point"
      }
    ],
    [
      {
        "name": "left",
        "type": "number"
      },
      {
        "name": "top",
        "type": "number"
      },
      {
        "name": "right",
        "type": "number"
      },
      {
        "name": "bottom",
        "type": "number"
      }
    ],
    [
      {
        "name": "source",
        "type": "object Rect"
      }
    ]
  ]
}
*/
	constructor(i1, i2, i3, i4) {
    		if (arguments.length == 1) {
				if (i1 === null) {
// @pdg-member {"name":"Rect.right","type":"number"}
// @pdg-member {"name":"Rect.bottom","type":"number"}
// @pdg-member {"name":"Rect.top","type":"number"}
// @pdg-member {"name":"Rect.left","type":"number"}
					this.left = 0; this.top = 0; this.right = 0; this.bottom = 0;
				} else if (i1 instanceof Array) {
    				this.left = i1[0]; this.top = i1[1]; this.right = i1[2]; this.bottom = i1[3];
    			} else if (i1 instanceof Rect || typeof i1.top != "undefined") {
    				this.assign(i1);
    			} else {
    				this.left = 0; this.top = 0; this.right = 0; this.bottom = 0;
    			}
    		} else if (arguments.length == 2) {
				if (i1 instanceof Point || typeof i1.x != "undefined") {
					// initializing from Point Objects
					this.left = i1.x; this.top = i1.y;
					if (i2 instanceof Point || typeof i2.x != "undefined") {
						this.right = i2.x; // 2nd param is rightBottom point
						this.bottom = i2.y;
					} else { // 2nd and 3rd params are width and height
						this.right = this.left + i2;
						this.bottom = this.top + i3;
					}
				} else { // 2 params: width and height
					this.left = 0; this.top = 0; this.right = i1; this.bottom = i2;
				}
    		} else if (arguments.length == 3) {
				// 3 params: top-left Point, width and height
				this.left = i1.x; this.top = i1.y;
				this.right = this.left + i2;
				this.bottom = this.top + i3;
			} else {
				this.left = (i1) ? i1 : 0; 
				this.top = (i2) ? i2 : 0;
				this.right = (i3) ? i3 : 0; 
				this.bottom = (i4) ? i4 : 0;
			}
		}

	//! return true if this rectangle is empty (no width or no height)
	// @pdg-member {"name":"Rect.empty","type":"function","brief":"return true if this rectangle is empty (no width or no height)","params":[],"returns":"boolean"}
	empty() {
		return ((this.right <= this.left) || (this.bottom <= this.top));
	}
	//! contains([Point] p) return true if the point is inside this rectangle
	//! contains([Rect] r) return true if the rectangle passed in is entirely inside this rectangle
	// @pdg-member {"name":"Rect.contains","type":"function","brief":"contains([Point] p) return true if the point is inside this rectangle; contains([Rect] r) return true if the rectangle passed in is entirely inside this rectangle","params":[[{"name":"r","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"boolean"}
	contains(o) {
		if (o instanceof Point || typeof o.x != "undefined") {
			return ((o.x >= this.left) && (o.x <= this.right) && (o.y >= this.top) && (o.y <= this.bottom));
		} else if (o instanceof Rect || typeof o.top != "undefined") {
			return (this.contains(o.leftTop()) && this.contains(o.rightTop())
					&& this.contains(o.leftBottom()) && this.contains(o.rightBottom()));
		}
	}
	//! return true if this rectangle overlaps the other rectangle at all (sharing an edge is not overlapping)
    // @pdg-member {"name":"Rect.overlaps","type":"function","brief":"return true if this rectangle overlaps the other rectangle at all (sharing an edge is not overlapping)","params":[{"name":"r","type":"object Rect"}],"returns":"boolean"}
    overlaps(r) { 
			return !this.intersection(r).empty();
		}
	// @pdg-member {"name":"Rect.leftTop","type":"function","brief":"get top left corner point of this rectangle","params":[],"returns":"object Point"}
	leftTop() {
			return new Point(this.left, this.top);
		}
	// @pdg-member {"name":"Rect.rightTop","type":"function","brief":"get top right corner point of this rectangle","params":[],"returns":"object Point"}
	rightTop() {
			return new Point(this.right, this.top);
		}
	// @pdg-member {"name":"Rect.leftBottom","type":"function","brief":"get bottom left corner point of this rectangle","params":[],"returns":"object Point"}
	leftBottom() {
			return new Point(this.left, this.bottom);
		}
	// @pdg-member {"name":"Rect.rightBottom","type":"function","brief":"get bottom right corner point of this rectangle","params":[],"returns":"object Point"}
	rightBottom() {
			return new Point(this.right, this.bottom);
		}
	// @pdg-member {"name":"Rect.centerPoint","type":"function","brief":"get center point of this rectangle","params":[],"returns":"object Point"}
	centerPoint() {
			return new Point((this.right - this.left)/2 + this.left, (this.bottom - this.top)/2 + this.top);
		}
	// @pdg-member {"name":"Rect.x1","type":"function","brief":"alias for Rect.left","params":[],"returns":"number"}
	x1() {
			return this.left;
		}
	// @pdg-member {"name":"Rect.y1","type":"function","brief":"alias for Rect.top","params":[],"returns":"number"}
	y1() {
			return this.top;
		}
	// @pdg-member {"name":"Rect.x2","type":"function","brief":"alias for Rect.right","params":[],"returns":"number"}
	x2() {
			return this.right;
		}
	// @pdg-member {"name":"Rect.y2","type":"function","brief":"alias for Rect.bottom","params":[],"returns":"number"}
	y2() {
			return this.bottom;
		}
	// @pdg-member {"name":"Rect.width","type":"function","brief":"get the width of this rectangle","params":[],"returns":"number"}
	width() {
			return this.right - this.left;
		}
	// @pdg-member {"name":"Rect.height","type":"function","brief":"get the height of this rectangle","params":[],"returns":"number"}
	height() {
			return this.bottom - this.top;
		}
	//! get a new rectangle that is the overlapping area of the the rectangles
// @pdg-contract {"name":"Rect.intersection","value":{"returns":{"type":"object Rect","ownership":"owned","description":"Return a new rectangle; leave this receiver unchanged."}}}
	// @pdg-member {"name":"Rect.intersection","type":"function","brief":"get a new rectangle that is the overlapping area of the the rectangles","params":[{"name":"r","type":"object Rect"}],"returns":"object Rect"}
	intersection(r) {
			var rd = new Rect();
			rd.left = (r.left < this.left) ? this.left : r.left;
			rd.top = (r.top < this.top) ? this.top : r.top;
			rd.right = (r.right > this.right) ? this.right : r.right;
			rd.bottom = (r.bottom > this.bottom) ? this.bottom : r.bottom;
			return rd;
		}
	//! get the smallest possible new rectangle that contains both rectangles
// @pdg-contract {"name":"Rect.unionWith","value":{"returns":{"type":"object Rect","ownership":"owned","description":"Return a new rectangle; leave this receiver unchanged."}}}
	// @pdg-member {"name":"Rect.unionWith","type":"function","brief":"get the smallest possible new rectangle that contains both rectangles","params":[{"name":"r","type":"object Rect"}],"returns":"object Rect"}
	unionWith(r) { 
			var rd = new Rect();
			rd.left = (r.left > this.left) ? this.left : r.left;
			rd.top = (r.top > this.top) ? this.top : r.top;
			rd.right = (r.right < this.right) ? this.right : r.right;
			rd.bottom = (r.bottom < this.bottom) ? this.bottom : r.bottom;
			return rd;
		}
	// @pdg-member {"name":"Rect.moveLeft","type":"function","brief":"move the rectangle to the left by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
	moveLeft(delta) { 
			this.left -= delta; this.right -= delta; 
			return this;
		}
	// @pdg-member {"name":"Rect.moveRight","type":"function","brief":"move the rectangle to the right by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
	moveRight(delta) { 
			this.left += delta; this.right += delta; 
			return this;
		}
	// @pdg-member {"name":"Rect.moveUp","type":"function","brief":"move the rectangle up by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
	moveUp(delta) { 
			this.top -= delta; this.bottom -= delta; 
			return this;
		}
	// @pdg-member {"name":"Rect.moveDown","type":"function","brief":"move the rectangle down by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
	moveDown(delta) { 
			this.top += delta; this.bottom += delta; 
			return this;
		}
	//! move the rectangle to a particular x location, leaving y unchanged
	// @pdg-member {"name":"Rect.moveXTo","type":"function","brief":"move the rectangle to a particular x location, leaving y unchanged","params":[{"name":"x","type":"number"}],"returns":"this"}
	moveXTo(x) { 
			var w = this.width(); this.left = x; this.setWidth(w); 
			return this;
		}
	//! move the rectangle to a particular y location, leaving x unchanged
	// @pdg-member {"name":"Rect.moveYTo","type":"function","brief":"move the rectangle to a particular y location, leaving x unchanged","params":[{"name":"y","type":"number"}],"returns":"this"}
	moveYTo(y) { 
			var h = this.height(); this.top = y; this.setHeight(h); 
			return this;
		}
	//! moveTo(x,y): the rectangle to a particular (x, y) location
	//! moveTo([Point] p): move the rectangle to a particular point
	// @pdg-member {"name":"Rect.moveTo","type":"function","brief":"moveTo(x,y): the rectangle to a particular (x, y) location; moveTo([Point] p): move the rectangle to a particular point","params":[[{"name":"x","type":"number"},{"name":"y","type":"number"}],[{"name":"p","type":"object Point"}]],"returns":"this"}
	moveTo(x, y) {
			if (x instanceof Point) {
				this.moveTo(p.x, p.y); 
			} else {
				var w = this.width(); this.left = x; this.setWidth(w);
				var h = this.height(); this.top = y; this.setHeight(h);
			}
			return this;
		}
	//! center([Point] p): move the rectangle to be centered over a particular point
	//! center([Rect] r): move the rectangle to be centered within/relative to another rectangle
	// @pdg-member {"name":"Rect.center","type":"function","brief":"center([Point] p): move the rectangle to be centered over a particular point; center([Rect] r): move the rectangle to be centered within/relative to another rectangle","params":[[{"name":"r","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"this"}
	center(r) { 
			if (r instanceof Point) {
				this.moveTo(r.x - this.width()/2, r.y - this.height()/2);
			} else {
				var x = (r.width() - this.width())/2 + r.left; 
				var y = (r.height() - this.height())/2 + r.top;
				this.moveTo(x, y); 
			}
			return this;
		}
	//! set the size (width & height) of the rectangle
	// @pdg-member {"name":"Rect.setSize","type":"function","brief":"set the size (width & height) of the rectangle","params":[{"name":"n","type":"number"}],"returns":"this"}
	setSize(n) { 
			this.setWidth(n); this.setHeight(n); 
			return this;
		}
	// @pdg-member {"name":"Rect.setWidth","type":"function","brief":"Set the width of this rectangle, keeping the left edge fixed","params":[{"name":"w","type":"number"}],"returns":"this"}
	setWidth(w) { 
			this.right = this.left + w; 
			return this;
		}
	// @pdg-member {"name":"Rect.setHeight","type":"function","brief":"Set the height of this rectangle, keeping the top edge fixed","params":[{"name":"h","type":"number"}],"returns":"this"}
	setHeight(h) { 
			this.bottom = this.top + h; 
			return this;
		}
	//! reduce the width of the rectangle while leaving the center point unchanged
	// @pdg-member {"name":"Rect.horzShrink","type":"function","brief":"reduce the width of the rectangle while leaving the center point unchanged","params":[{"name":"delta","type":"number"}],"returns":"this"}
	horzShrink(delta) { 
			this.left += delta; this.right -= delta; 
			return this;
		}
	//! reduce the height of the rectangle while leaving the center point unchanged
	// @pdg-member {"name":"Rect.vertShrink","type":"function","brief":"reduce the height of the rectangle while leaving the center point unchanged","params":[{"name":"delta","type":"number"}],"returns":"this"}
	vertShrink(delta) { 
			this.top += delta; this.bottom -= delta; 
			return this;
		}
	//! increase the width of the rectangle while leaving the center point unchanged
	// @pdg-member {"name":"Rect.horzGrow","type":"function","brief":"increase the width of the rectangle while leaving the center point unchanged","params":[{"name":"delta","type":"number"}],"returns":"this"}
	horzGrow(delta) { 
			this.left -= delta; this.right += delta; 
			return this;
		}
	//! increase the height of the rectangle while leaving the center point unchanged
	// @pdg-member {"name":"Rect.vertGrow","type":"function","brief":"increase the height of the rectangle while leaving the center point unchanged","params":[{"name":"delta","type":"number"}],"returns":"this"}
	vertGrow(delta) { 
			this.top -= delta; this.bottom += delta; 
			return this;
		}
	//! reduce the height and width of the rectangle while leaving the center point unchanged
	// @pdg-member {"name":"Rect.shrink","type":"function","brief":"reduce the height and width of the rectangle while leaving the center point unchanged","params":[{"name":"delta","type":"number"}],"returns":"this"}
	shrink(delta) { 
			this.horzShrink(delta); this.vertShrink(delta); 
			return this;
		}
	//! increase the height and width of the rectangle while leaving the center point unchanged
	// @pdg-member {"name":"Rect.grow","type":"function","brief":"increase the height and width of the rectangle while leaving the center point unchanged","params":[{"name":"delta","type":"number"}],"returns":"this"}
	grow(delta) { 
			this.horzGrow(delta); this.vertGrow(delta); 
			return this;
		}
	//! change the x coordinates of the rectangle by a multiplier
	// @pdg-member {"name":"Rect.horzScale","type":"function","brief":"change the x coordinates of the rectangle by a multiplier","params":[{"name":"f","type":"number"}],"returns":"this"}
	horzScale(f) { 
			this.right *= f; this.left *= f; 
			return this;
		}
	//! change the y coordinates of the rectangle by a multiplier
	// @pdg-member {"name":"Rect.vertScale","type":"function","brief":"change the y coordinates of the rectangle by a multiplier","params":[{"name":"f","type":"number"}],"returns":"this"}
	vertScale(f) { 
			this.top *= f; this.bottom *= f; 
			return this;
		}
	//! change the coordinates of the rectangle by a multiplier
	// @pdg-member {"name":"Rect.scale","type":"function","brief":"change the coordinates of the rectangle by a multiplier","params":[{"name":"f","type":"number"}],"returns":"this"}
	scale(f) { 
			this.horzScale(f); this.vertScale(f); 
			return this;
		}
	//! round the coordinates to closest whole number
	// @pdg-member {"name":"Rect.round","type":"function","brief":"round the coordinates to closest whole number","params":[],"returns":"this"}
	round() { 
			this.left = Math.round(this.left);
			this.top = Math.round(this.top);
			this.right = Math.round(this.right);
			this.bottom = Math.round(this.bottom);
			return this;
		}
		
	// @pdg-member {"name":"Rect.toQuad","type":"function","brief":"convert rectangle to a Quad","params":[],"returns":"object Quad"}
	toQuad() { 
			return new Quad(this); 
		}
		
	// @pdg-member {"name":"Rect.equals","type":"function","brief":"return true if this rectangle is equal to the given one","params":[{"name":"r2","type":"object Rect"}],"returns":"boolean"}
	equals(r2) {
			return ((this.left == r2.left) && (this.top == r2.top) && (this.right == r2.right) && (this.bottom == r2.bottom));
		}
	// @pdg-member {"name":"Rect.notEquals","type":"function","brief":"return true if this rectangle is not equal to the given one","params":[{"name":"r2","type":"object Rect"}],"returns":"boolean"}
	notEquals(r2) {
			return ((this.left != r2.left) || (this.top != r2.top) || (this.right != r2.right) || (this.bottom != r2.bottom));
		}
	// @pdg-member {"name":"Rect.assign","type":"function","brief":"set this rectangle equal to the given one","params":[{"name":"r2","type":"object Rect"}],"returns":"this"}
	assign(r2) {
			this.left = r2.left; this.top = r2.top; this.right = r2.right; this.bottom = r2.bottom;
			return this;
		}
		// unary operators:   myRect.add(otherRect)
		//! add([Point] p): offset this rectangle's location by adding x & y coordinates of the point
		//! add([Rect] r): add another rectangle to this one by adding corresponding coordinates
	// @pdg-member {"name":"Rect.add","type":"function","brief":"add([Point] p): offset this rectangle's location by adding x & y coordinates of the point; add([Rect] r): add another rectangle to this one by adding corresponding coordinates","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"this"}
	add(r2) {
			if (r2 instanceof Point) {
				this.left += r2.x; this.top += r2.y; this.right += r2.x; this.bottom += r2.y;
			} else {
				this.left += r2.left; this.top += r2.top; this.right += r2.right; this.bottom += r2.bottom;
			}
			return this;
		}
		//! sub([Point] p): offset this rectangle's location by subtracting x & y coordinates of the point
		//! sub([Rect] r): add another rectangle to this one by subtracting corresponding coordinates
	// @pdg-member {"name":"Rect.sub","type":"function","brief":"sub([Point] p): offset this rectangle's location by subtracting x & y coordinates of the point; sub([Rect] r): add another rectangle to this one by subtracting corresponding coordinates","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"this"}
	sub(r2) {
			if (r2 instanceof Point) {
				this.left -= r2.x; this.top -= r2.y; this.right -= r2.x; this.bottom -= r2.y;
			} else {
				this.left -= r2.left; this.top -= r2.top; this.right -= r2.right; this.bottom -= r2.bottom;
			}
			return this;
		}
		//! mul([Point] p): change this rectangle's location by multiplying by x & y coordinates of the point
		//! mul([Rect] r): change this rect by multiplying by corresponding coordinates of another rectangle
	// @pdg-member {"name":"Rect.mul","type":"function","brief":"mul([Point] p): change this rectangle's location by multiplying by x & y coordinates of the point; mul([Rect] r): change this rect by multiplying by corresponding coordinates of another rectangle","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"this"}
	mul(r2) {
			if (r2 instanceof Point) {
				this.left *= r2.x; this.top *= r2.y; this.right *= r2.x; this.bottom *= r2.y;
			} else {
				this.left *= r2.left; this.top *= r2.top; this.right *= r2.right; this.bottom *= r2.bottom;
			}
			return this;
		}
		//! div([Point] p): change this rectangle's location by dividing by x & y coordinates of the point
		//! div([Rect] r): change this rect by dividing by corresponding coordinates of another rectangle
	// @pdg-member {"name":"Rect.div","type":"function","brief":"div([Point] p): change this rectangle's location by dividing by x & y coordinates of the point; div([Rect] r): change this rect by dividing by corresponding coordinates of another rectangle","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"this"}
	div(r2) {
			if (r2 instanceof Point) {
				this.left /= r2.x; this.top /= r2.y; this.right /= r2.x; this.bottom /= r2.y;
			} else {
				this.left /= r2.left; this.top /= r2.top; this.right /= r2.right; this.bottom /= r2.bottom;
			}
			return this;
		}
		// binary operators:   newRect = myRect.plus(otherRect).plus(thirdRect);
// @pdg-contract {"name":"Rect.plus","value":{"returns":{"type":"object Rect","ownership":"owned","description":"Return a new rectangle; leave this receiver unchanged."}}}
	// @pdg-member {"name":"Rect.plus","type":"function","brief":"","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"object Rect"}
	plus(o) {
			var r = new Rect(this); return r.add(o);
		}
// @pdg-contract {"name":"Rect.minus","value":{"returns":{"type":"object Rect","ownership":"owned","description":"Return a new rectangle; leave this receiver unchanged."}}}
	// @pdg-member {"name":"Rect.minus","type":"function","brief":"","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"object Rect"}
	minus(o) {
			var r = new Rect(this); return r.sub(o);
		}
// @pdg-contract {"name":"Rect.times","value":{"returns":{"type":"object Rect","ownership":"owned","description":"Return a new rectangle; leave this receiver unchanged."}}}
	// @pdg-member {"name":"Rect.times","type":"function","brief":"","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"object Rect"}
	times(o) {
			var r = new Rect(this); return r.mul(o);
		}
// @pdg-contract {"name":"Rect.dividedby","value":{"returns":{"type":"object Rect","ownership":"owned","description":"Return a new rectangle; leave this receiver unchanged."}}}
	// @pdg-member {"name":"Rect.dividedby","type":"function","brief":"","params":[[{"name":"r2","type":"object Rect"}],[{"name":"p","type":"object Point"}]],"returns":"object Rect"}
	dividedby(o) {
			var r = new Rect(this); return r.div(o);
		}
	toString() {
			return "Rect {left:"+this.left+",top:"+this.top+",right:"+this.right+",bottom:"+this.bottom+"}";
		}
}

var lftTop = 0;
var rgtTop = 1;
var rgtBot = 2;
var lftBot = 3;

// -----------------------------------------------------------------------------------
// Quad
// -----------------------------------------------------------------------------------
// Quad is a class that provides support for dealing with 4 point
// ploygons in 2 dimensional space

// @pdg-class {"name":"Quad","native_binding":{"type":"pdg::Quad","browser":{"return_value":{"arguments":["points"]}}}}
class Quad {

	//! new Quad(): create an empty quad at 0,0
	//! new Quad([object Quad] q): copy from another quad
	//! new Quad([object Rect] r): create a quad from a rectangle
	//! new Quad([object RotatedRect r]): create a quad from a rotated rectangle
	//! new Quad([object Point] p1, [object Point] p2, [object Point] p3, [object Point] p4): create a quad given its corner points
	//! new Quad([object Point] p[4]): create a quad given an array of 4 points
/* @pdg-member
{
  "name": "Quad.Quad",
  "type": "constructor",
  "brief": "create a new Quad",
  "returns": "object Quad",
  "params": [
    [],
    [
      {
        "name": "q",
        "type": "object Quad"
      }
    ],
    [
      {
        "name": "r",
        "type": "object Rect"
      }
    ],
    [
      {
        "name": "r",
        "type": "object RotatedRect"
      }
    ],
    [
      {
        "name": "p1",
        "type": "object Point"
      },
      {
        "name": "p2",
        "type": "object Point"
      },
      {
        "name": "p3",
        "type": "object Point"
      },
      {
        "name": "p4",
        "type": "object Point"
      }
    ],
    [
      {
        "name": "p",
        "type": "object Point[]"
      }
    ]
  ]
}
*/
    constructor(i1, i2, i3, i4) {
// @pdg-member {"name":"Quad.points","type":"object Point[]"}
    		this.points = new Array();
			if (arguments.length == 1) {
				if (i1 === null) {
					for (var i = 0; i < 4; i++) {
						this.points[i] = new Point();
					}
				} else if (i1 instanceof Rect || typeof i1.top != "undefined") {
					// initializing from a Rect or RotatedRect
					this.points[lftTop] = new Point(i1.left, i1.top);
					this.points[rgtTop] = new Point(i1.right, i1.top);
					this.points[lftBot] = new Point(i1.left, i1.bottom);
					this.points[rgtBot] = new Point(i1.right, i1.bottom);
				} else if (i1 instanceof Quad) {
					for (var i = 0; i < 4; i++) {
						this.points[i] = new Point(i1.points[i]);
					}
				} else if (i1 instanceof Array) {
					for (var i = 0; i < 4; i++) {
						this.points[i] = new Point(i1[i]);
					}
				} else {
					for (var i = 0; i < 4; i++) {
						this.points[i] = new Point();
					}
				}
			} else if (arguments.length == 4) {
				// initializing from 4 points in order: leftTop, rightTop, rightBottom, leftBottom
				this.points[lftTop] = new Point(i1);
				this.points[rgtTop] = new Point(i2);
				this.points[rgtBot] = new Point(i3);
				this.points[lftBot] = new Point(i4);
			} else {
				for (var i = 0; i < 4; i++) {
					this.points[i] = new Point();
				}
			}
		}

	//! return a rectangle that bounds the quad
	// @pdg-member {"name":"Quad.getBounds","type":"function","brief":"return a rectangle that bounds the quad","params":[],"returns":"object Rect"}
	getBounds() {
			var r = new Rect(this.points[0].x, this.points[0].y, this.points[0].x, this.points[0].y);
			for (var i = 1; i<4; i++) {
				if (this.points[i].y < r.top) r.top = this.points[i].y;
				if (this.points[i].x < r.left) r.left = this.points[i].x;
				if (this.points[i].x > r.right) r.right = this.points[i].x;
				if (this.points[i].y > r.bottom) r.bottom = this.points[i].y;
			}
			return r;
		}
	//! return the calculated centerpoint of the quad
    // @pdg-member {"name":"Quad.centerPoint","type":"function","brief":"return the calculated centerpoint of the quad","params":[],"returns":"object Point"}
    centerPoint() {
			//	    sa(pa2.x) - sb(pb2.x) + pb2.y - pa2.y
			//	X = -------------------------------------
			//	               (sa - sb)
			var sa, sb;
			var pa1 = new Point(this.points[lftTop].x, this.points[lftTop].y);
			var pa2 = new Point(this.points[rgtBot].x, this.points[rgtBot].y);
			var pb1 = new Point(this.points[lftBot].x, this.points[lftBot].y);
			var pb2 = new Point(this.points[rgtTop].x, this.points[rgtTop].y);
			var tmp;
			if ( (pa2.y < pb2.y) && (pa1.x < pb2.x)) {
				// twisted around horizontal axis, swap for calculation
				tmp = new Point(pa2); pa2.assign(pb2); pb2.assign(tmp);
			}
			if ( (pa2.y > pb2.y) && (pa1.x > pb2.x)) {
				// twisted around vertical axis, swap for calculation
				tmp = new Point(pa1); pa1.assign(pb2); pb2.assign(tmp);
			}
			sa = (pa2.y - pa1.y)/(pa2.x - pa1.x);
			sb = (pb2.y - pb1.y)/(pb2.x - pb1.x);
			if (sa == sb) return this.getBounds().centerPoint();
			var x = ((sa * pa2.x) - (sb * pb2.x) + pb2.y - pa2.y) / (sa - sb);
			var y = (sa * (x - pa2.x)) + pa2.y;
			return new Point(x, y);
		}
	// @pdg-member {"name":"Quad.equals","type":"function","brief":"return true if this quad is equal to the given one","params":[{"name":"q2","type":"object Quad"}],"returns":"boolean"}
	equals(q2) {
			return (this.points[lftTop] == q2.points[lftTop]) && (this.points[rgtTop] == q2.points[rgtTop]) &&
				   (this.points[rgtBot] == q2.points[rgtBot]) && (this.points[lftBot] == q2.points[lftBot]);
		}
	// @pdg-member {"name":"Quad.notEquals","type":"function","brief":"return true if this quad is not equal to the given one","params":[{"name":"q2","type":"object Quad"}],"returns":"boolean"}
	notEquals(q2) {
			return (this.points[lftTop] != q2.points[lftTop]) || (this.points[rgtTop] != q2.points[rgtTop]) ||
				   (this.points[rgtBot] != q2.points[rgtBot]) || (this.points[lftBot] != q2.points[lftBot]);
		}
	//! Determines if the point is contained within this quad
	// @pdg-member {"name":"Quad.contains","type":"function","brief":"returns true if the point is contained within this quad","params":[{"name":"p","type":"object Point"}],"returns":"boolean"}
	contains(point) {
			// The test is just checking whether the point lies on the correct side of each rectangle edge.
			// if it does, then the point is inside the quad
			var x = point.x;
			var y = point.y;
			var ex = this.points[rgtTop].x - this.points[lftTop].x; 
			var ey = this.points[rgtTop].y - this.points[lftTop].y;
			var fx = this.points[lftBot].x - this.points[lftTop].x;
			var fy = this.points[lftBot].y - this.points[lftTop].y;
			if ( ((x - this.points[lftTop].x) * ex + (y - this.points[lftTop].y) * ey) < 0.0 ) return false;
			if ( ((x - this.points[rgtTop].x) * ex + (y - this.points[rgtTop].y) * ey) > 0.0 ) return false;
			if ( ((x - this.points[lftTop].x) * fx + (y - this.points[lftTop].y) * fy) < 0.0 ) return false;
			if ( ((x - this.points[lftBot].x) * fx + (y - this.points[lftBot].y) * fy) > 0.0 ) return false;
			return true;
		}
    // move the quad
	//! move the quad to the left by some amount
    // @pdg-member {"name":"Quad.moveLeft","type":"function","brief":"move the quad to the left by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
    moveLeft(delta) { 
    		this.points[0].x -= delta; this.points[1].x -= delta; this.points[2].x -= delta; this.points[3].x -= delta; 
			return this;
		}
	//! move the quad to the right by some amount
    // @pdg-member {"name":"Quad.moveRight","type":"function","brief":"move the quad to the right by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
    moveRight(delta) { 
    		this.points[0].x += delta; this.points[1].x += delta; this.points[2].x += delta; this.points[3].x += delta; 
			return this;
		}
	//! move the quad up by some amount
    // @pdg-member {"name":"Quad.moveUp","type":"function","brief":"move the quad up by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
    moveUp(delta) { 
    		this.points[0].y -= delta; this.points[1].y -= delta; this.points[2].y -= delta; this.points[3].y -= delta;
			return this;
		}
	//! move the quad down by some amount
    // @pdg-member {"name":"Quad.moveDown","type":"function","brief":"move the quad down by some amount","params":[{"name":"delta","type":"number"}],"returns":"this"}
    moveDown(delta) { 
    		this.points[0].y += delta; this.points[1].y += delta; this.points[2].y += delta; this.points[3].y += delta; 
			return this;
		}
	//! rotate(n): rotate the quad by a rotation in radians (around the calculated center point of the quad)
	//! rotate(n, [Offset] o): rotate the quad by a rotation in radians around an offset center point
	// @pdg-member {"name":"Quad.rotate","type":"function","brief":"rotate(n): rotate the quad by a rotation in radians (around the calculated center point of the quad); rotate(n, [Offset] o): rotate the quad by a rotation in radians around an offset center point","params":[{"name":"rotationRadians","type":"number"},{"name":"centerPtOffset","type":"object Offset","optional":true,"default_value":"Point(0,0)"}],"returns":"this"}
	rotate(rotationRadians, centerPtOffset) { 
			var center = this.centerPoint();
			if (centerPtOffset && typeof centerPtOffset.x != "undefined") {
				center.add(centerPtOffset);
			}
			// calc this.points with rotation
			var v = new Vector();
			for (var i = 0; i < 4; i++) {
				v.x = this.points[i].x - center.x;
				v.y = this.points[i].y - center.y;
				var len = v.vectorLength();
				var rot = v.vectorAngle();
				this.points[i].x = (len * Math.cos(rot + rotationRadians)) + center.x;
				this.points[i].y = (len * Math.sin(rot + rotationRadians)) + center.y;
			}
			return this;
		}
}


// -----------------------------------------------------------------------------------
// RotatedRectT template
// -----------------------------------------------------------------------------------
// RotatedRect is a class that provides support for dealing with rotating
// rectangles in 2 dimensional space.

// @pdg-class {"name":"RotatedRect","native_binding":{"type":"pdg::RotatedRect","browser":{"return_value":{"arguments":["$","radians","centerOffset"]}}}}
class RotatedRect extends Rect {
/* @pdg-member
{
  "name": "RotatedRect.RotatedRect",
  "type": "constructor",
  "brief": "create a new RotatedRect",
  "returns": "object RotatedRect",
  "params": [
    {
      "name": "rect",
      "type": "object Rect",
      "optional": true,
      "default_value": "Rect(0,0)"
    },
    {
      "name": "rotationRadians",
      "type": "number",
      "optional": true,
      "default_value": "0.0"
    },
    {
      "name": "cpOffset",
      "type": "object Offset",
      "optional": true,
      "default_value": "null"
    }
  ]
}
*/
// @pdg-member {"name":"RotatedRect.right","type":"number"}
// @pdg-member {"name":"RotatedRect.bottom","type":"number"}
// @pdg-member {"name":"RotatedRect.top","type":"number"}
// @pdg-member {"name":"RotatedRect.left","type":"number"}
    constructor(rect, rotationRadians, cpOffset) {
		if (arguments.length == 0) {
			super();
		} else if (arguments.length >= 1) {
			super(rect);
		}
		if (arguments.length >= 2) {
// @pdg-member {"name":"RotatedRect.radians","type":"number"}
			this.radians = rotationRadians;
		} else {
			this.radians = 0.0;
		}
// @pdg-member {"name":"RotatedRect.centerOffset","type":"object Point"}
		this.centerOffset = new Point(0, 0);
		if (typeof cpOffset != "undefined" && typeof cpOffset.x != "undefined") {
			this.centerOffset.assign(cpOffset);
		}
	}

	//! set an offset for point around which rotation is applied
	// @pdg-member {"name":"RotatedRect.setCenterOffset","type":"function","brief":"set an offset for point around which rotation is applied","params":[{"name":"cpOffset","type":"object Offset"}],"returns":"this"}
	setCenterOffset(cpOffset) { 
		this.centerOffset.assign(cpOffset); 
		return this;
	}
	//! set the rotation of this rectangle to a particular amount in radians
	// @pdg-member {"name":"RotatedRect.setRotation","type":"function","brief":"set the rotation of this rectangle to a particular amount in radians","params":[{"name":"rotationRadians","type":"number"},{"name":"cpOffset","type":"object Offset","optional":true,"default_value":"null"}],"returns":"this"}
	setRotation(rotationRadians, cpOffset) { 
			// Fix: Use this.radians instead of undefined radians variable
			this.radians = rotationRadians; 
			if (typeof cpOffset != "undefined" && typeof cpOffset.x != "undefined") {
				this.centerOffset.assign(cpOffset);
			}
			return this;
		}
	//! change the rotation of this rectangle by some number of radians
	// @pdg-member {"name":"RotatedRect.rotate","type":"function","brief":"change the rotation of this rectangle by some number of radians","params":[{"name":"rotateRadians","type":"number"}],"returns":"this"}
	rotate(rotateRadians) { 
			this.radians += rotateRadians; 
			return this;
		}
	//! create a Quad by applying the rectangle's rotation around the center point with offset
    // @pdg-member {"name":"RotatedRect.getQuad","type":"function","brief":"create a Quad by applying the rectangle's rotation around the center point with offset","params":[],"returns":"object Quad"}
    getQuad() {
			var fr = new Rect(this.left, this.top, this.right, this.bottom);
			var quad = new Quad(fr);
			if (this.radians == 0.0) return quad;
			var center = fr.centerPoint();
			var coff = new Offset(this.centerOffset.x, this.centerOffset.y);
			center.add(coff);
			// calc points with rotation
			var v = new Vector;
			for (var i = 0; i < 4; i++) {
				v.x = quad.points[i].x - center.x;
				v.y = quad.points[i].y - center.y;
				var len = v.vectorLength();
				var rot = v.vectorAngle();
				quad.points[i].x = (len * Math.cos(rot + this.radians)) + center.x;
				quad.points[i].y = (len * Math.sin(rot + this.radians)) + center.y;
			}
			return quad;
		}
}


// Make classes available globally
if (typeof global !== 'undefined') {
    global.Offset = Offset;
    global.Point = Point;
    global.Vector = Vector;
    global.Rect = Rect;
    global.Quad = Quad;
    global.RotatedRect = RotatedRect;
    global.lftTop = lftTop;
    global.rgtTop = rgtTop;
    global.rgtBot = rgtBot;
    global.lftBot = lftBot;
}

// Also make them available on the global object for compatibility
if (typeof globalThis !== 'undefined') {
    globalThis.Offset = Offset;
    globalThis.Point = Point;
    globalThis.Vector = Vector;
    globalThis.Rect = Rect;
    globalThis.Quad = Quad;
    globalThis.RotatedRect = RotatedRect;
    globalThis.lftTop = lftTop;
    globalThis.rgtTop = rgtTop;
    globalThis.rgtBot = rgtBot;
    globalThis.lftBot = lftBot;
}

// Also make them available on window for browser compatibility
if (typeof window !== 'undefined') {
    window.Offset = Offset;
    window.Point = Point;
    window.Vector = Vector;
    window.Rect = Rect;
    window.Quad = Quad;
    window.RotatedRect = RotatedRect;
    window.lftTop = lftTop;
    window.rgtTop = rgtTop;
    window.rgtBot = rgtBot;
    window.lftBot = lftBot;
}

if(!(typeof exports === 'undefined')) {
    exports.Offset = Offset;
    exports.Point = Point;
    exports.Vector = Vector;
    exports.Rect = Rect;
    exports.Quad = Quad;
    exports.RotatedRect = RotatedRect;
    exports.lftTop = lftTop;
    exports.rgtTop = rgtTop;
    exports.rgtBot = rgtBot;
    exports.lftBot = lftBot;
}

/* @pdg-schema
{
  "name": "XY",
  "value": {
    "kind": "record",
    "fields": {
      "x": {
        "type": "number"
      },
      "y": {
        "type": "number"
      }
    },
    "description": "A plain pair of coordinates accepted by geometry constructors."
  }
}
*/

/* @pdg-contract
{
  "name": "Point.Point",
  "value": {
    "params": {
      "xy": {
        "schema": "XY"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Offset.Offset",
  "value": {
    "params": {
      "xy": {
        "schema": "XY"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Vector.Vector",
  "value": {
    "params": {
      "xy": {
        "schema": "XY"
      }
    }
  }
}
*/
