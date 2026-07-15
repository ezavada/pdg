// -----------------------------------------------
// pdg_v8_support.cpp
// 
// Stuff to support Javascript V8 bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
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

#include "pdg_v8_support.h"
#include "pdg_script_macros.h"
#include "memblock.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>

namespace pdg {

namespace v8script {

jswrap::ObjectWrap* safe_unwrap_object_wrap(v8::Local<v8::Object> handle) {
    if (handle.IsEmpty() || (handle->InternalFieldCount() <= 0)) {
        return 0;
    }
    void* ptr = handle->GetAlignedPointerFromInternalField(0);
    if (!ptr) {
        return 0;
    }
    return static_cast<jswrap::ObjectWrap*>(ptr);
}

jswrap::ObjectWrap* safe_unwrap_object_wrap_or_prototype(v8::Isolate* isolate, v8::Local<v8::Value> val, v8::Local<v8::Object>* script_obj) {
    if (val.IsEmpty() || !val->IsObject()) {
        return 0;
    }
    v8::Local<v8::Object> obj = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
    if (script_obj) {
        *script_obj = obj;
    }
    jswrap::ObjectWrap* wrap = safe_unwrap_object_wrap(obj);
    if (wrap) {
        return wrap;
    }
    v8::Local<v8::Value> protoVal = obj->GetPrototypeV2();
    if (protoVal.IsEmpty() || !protoVal->IsObject()) {
        return 0;
    }
    return safe_unwrap_object_wrap(protoVal->ToObject(isolate->GetCurrentContext()).ToLocalChecked());
}

} // end namespace v8script

static v8::Local<v8::Value>  MakeCppOffset(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Offset &o, bool canFail = false);
static v8::Local<v8::Value>  MakeCppPoint(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Point &p, bool canFail = false);
//static v8::Local<v8::Value>  MakeCppVector(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Vector &v, bool canFail = false);
static v8::Local<v8::Value>  MakeCppRect(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Rect &r, bool canFail = false);
static v8::Local<v8::Value>  MakeCppRect(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::RotatedRect &r, bool canFail = false);
static v8::Local<v8::Value>  MakeCppQuad(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Quad &q, bool canFail = false);
static v8::Local<v8::Value>  MakeCppColor(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Color &c, bool canFail = false);

#define X_Symbol _V8_STR("x")
#define Y_Symbol _V8_STR("y")
#define Top_Symbol _V8_STR("top")
#define Left_Symbol _V8_STR("left")
#define Bottom_Symbol _V8_STR("bottom")
#define Right_Symbol _V8_STR("right")
#define Height_Symbol _V8_STR("height")
#define Width_Symbol _V8_STR("width")
#define TopLeft_Symbol _V8_STR("topLeft")
#define BottomRight_Symbol _V8_STR("bottomRight")
#define Radians_Symbol _V8_STR("radians")
#define CenterOffset_Symbol _V8_STR("centerOffset")
#define Points_Symbol _V8_STR("points")

#define Red_Symbol _V8_STR("red")
#define Green_Symbol _V8_STR("green")
#define Blue_Symbol _V8_STR("blue")
#define Alpha_Symbol _V8_STR("alpha")

v8::Persistent<v8::Object> gOffsetPrototype;
v8::Persistent<v8::Object> gPointPrototype;
v8::Persistent<v8::Object> gVectorPrototype;
v8::Persistent<v8::Object> gRectPrototype;
v8::Persistent<v8::Object> gRotatedRectPrototype;
v8::Persistent<v8::Object> gQuadPrototype;
v8::Persistent<v8::Object> gColorPrototype;
v8::Persistent<v8::Object> gMemBlockPrototype;
v8::Persistent<v8::Object> gNetServerPrototype;
v8::Persistent<v8::Object> gNetClientPrototype;
v8::Persistent<v8::Object> gNetConnectionPrototype;

const char* v8_GetFunctionName(v8::Local<v8::Function> func) {
    static std::string result_;
    v8::String::Utf8Value funcNameStr(func->GetIsolate(), func->GetName()->ToString(func->GetIsolate()->GetCurrentContext()).ToLocalChecked());
    result_ = *funcNameStr;
    return result_.c_str();
}

const char* v8_GetFunctionFileAndLine(v8::Local<v8::Function> func) {
    static std::string result_;
    v8::String::Utf8Value resNameStr(func->GetIsolate(), func->GetScriptOrigin().ResourceName()->ToString(func->GetIsolate()->GetCurrentContext()).ToLocalChecked());
    result_ = *resNameStr;
    
    // Add line number if available
    int lineNumber = func->GetScriptLineNumber();
    if (lineNumber != v8::Function::kLineOffsetNotFound) {
        result_ += ":";
        result_ += std::to_string(lineNumber + 1); // Convert from 0-based to 1-based line numbering
    }
    
    return result_.c_str();
}

const char* v8_GetObjectClassName(v8::Local<v8::Object> obj) {
    static std::string result_;
    v8::String::Utf8Value nameStr(obj->GetIsolate(), obj->GetConstructorName());
    result_ = *nameStr;
    return result_.c_str();
}

void v8_ThrowArgCountException(v8::Isolate* isolate, int argc, int requiredCount, bool allowExtra) {
	std::ostringstream excpt_s;
	excpt_s << "argument count mismatch: expected ";
	if (allowExtra) {
		excpt_s << "at least ";
	}
	excpt_s << requiredCount << ", but got ";
	if (allowExtra) {
		excpt_s << "only ";
	}
	excpt_s << argc << " arguments.";
	THROW_ERR( excpt_s.str().c_str() );
}

void v8_ThrowArgTypeException(v8::Isolate* isolate, int argn, const char* mustBeStr, v8::Value* valp) {
	std::ostringstream excpt_s;
    excpt_s << "argument " << argn << " must be ";
    if (valp && valp->IsUndefined()) {
    	excpt_s << "an object of type " << mustBeStr << ", but got undefined. Did you pass in \""
    		<< mustBeStr << "()\" instead of \"new " << mustBeStr << "()\"?";
    } else {
    	excpt_s << mustBeStr << ".";
    }
	THROW_TYPE_ERR( excpt_s.str().c_str() );
}

// these let us set a prototype that will be used when an object of a particulr JavaScript class is created
void v8_SetOffsetPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gOffsetPrototype.Reset(isolate, obj);
}

void v8_SetPointPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gPointPrototype.Reset(isolate, obj);
}

void v8_SetVectorPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gVectorPrototype.Reset(isolate, obj);
}

void v8_SetRectPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gRectPrototype.Reset(isolate, obj);
}

void v8_SetRotatedRectPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gRotatedRectPrototype.Reset(isolate, obj);
}

void v8_SetQuadPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gQuadPrototype.Reset(isolate, obj);
}

void v8_SetColorPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gColorPrototype.Reset(isolate, obj);
}

void v8_SetMemBlockPrototype(v8::Local<v8::Object> obj) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
	gMemBlockPrototype.Reset(isolate, obj);
}

v8::Local<v8::Object> v8_MakeJavascriptOffset(v8::Isolate* isolate, pdg::Offset& o) {
    v8::EscapableHandleScope scope(isolate);
  	v8::Local<v8::Object> obj = v8::Object::New(isolate);
    v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gOffsetPrototype);
    if (!gOffsetPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
	obj->Set(isolate->GetCurrentContext(), X_Symbol, NUM2VAL(o.x)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Y_Symbol, NUM2VAL(o.y)).ToChecked();
  	return scope.Escape(obj);
}

v8::Local<v8::Object> v8_MakeJavascriptPoint(v8::Isolate* isolate, pdg::Point& p) {
    v8::EscapableHandleScope scope(isolate);
  	v8::Local<v8::Object> obj = v8::Object::New(isolate);
    v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gPointPrototype);
  	if (!gPointPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
	obj->Set(isolate->GetCurrentContext(), X_Symbol, NUM2VAL(p.x)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Y_Symbol, NUM2VAL(p.y)).ToChecked();
  	return scope.Escape(obj);
}


v8::Local<v8::Object> v8_MakeJavascriptVector(v8::Isolate* isolate, pdg::Vector& v) {
    v8::EscapableHandleScope scope(isolate);
  	v8::Local<v8::Object> obj = v8::Object::New(isolate);
    v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gVectorPrototype);
  	if (!gVectorPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
	obj->Set(isolate->GetCurrentContext(), X_Symbol, NUM2VAL(v.x)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Y_Symbol, NUM2VAL(v.y)).ToChecked();
  	return scope.Escape(obj);
}

v8::Local<v8::Object> v8_MakeJavascriptRect(v8::Isolate* isolate, pdg::Rect& r) {
    v8::EscapableHandleScope scope(isolate);
  	v8::Local<v8::Object> obj = v8::Object::New(isolate);
    v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gRectPrototype);
  	if (!gRectPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Left_Symbol, NUM2VAL(r.left)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Top_Symbol, NUM2VAL(r.top)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Right_Symbol, NUM2VAL(r.right)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Bottom_Symbol, NUM2VAL(r.bottom)).ToChecked();
  	return scope.Escape(obj);
}

v8::Local<v8::Object> v8_MakeJavascriptRect(v8::Isolate* isolate, pdg::RotatedRect& r) {
    v8::EscapableHandleScope scope(isolate);
  	v8::Local<v8::Object> obj = v8::Object::New(isolate);
    v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gRotatedRectPrototype);
  	if (!gRotatedRectPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Left_Symbol, NUM2VAL(r.left)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Top_Symbol, NUM2VAL(r.top)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Right_Symbol, NUM2VAL(r.right)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Bottom_Symbol, NUM2VAL(r.bottom)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Radians_Symbol, NUM2VAL(r.radians)).ToChecked();
	v8::Local<v8::Object> r_p_ = v8_MakeJavascriptOffset(isolate, r.centerOffset);
	obj->Set(isolate->GetCurrentContext(), CenterOffset_Symbol, r_p_).ToChecked();
  	return scope.Escape(obj);
}

v8::Local<v8::Object> v8_MakeJavascriptQuad(v8::Isolate* isolate, pdg::Quad& q) {
    v8::EscapableHandleScope scope(isolate);
  	v8::Local<v8::Array> arr = v8::Array::New(isolate);
  	v8::Local<v8::Object> obj = v8::Object::New(isolate);
    v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gQuadPrototype);
  	if (!gQuadPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
  	for (int i = 0; i<4; i++) {
		v8::Local<v8::Object> q_p_ = v8_MakeJavascriptPoint(isolate, q.points[i]);
		arr->Set(isolate->GetCurrentContext(), v8::Integer::New(isolate, i), q_p_).ToChecked();
	}
	obj->Set(isolate->GetCurrentContext(), Points_Symbol, arr).ToChecked();
  	return scope.Escape(obj);
}

v8::Local<v8::Object> v8_MakeJavascriptColor(v8::Isolate* isolate, pdg::Color& c) {
    v8::EscapableHandleScope scope(isolate);
	v8::Local<v8::Object> obj = v8::Object::New(isolate);
	v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gColorPrototype);
	if (!gColorPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Red_Symbol, NUM2VAL(c.red)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Green_Symbol, NUM2VAL(c.green)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Blue_Symbol, NUM2VAL(c.blue)).ToChecked();
	obj->Set(isolate->GetCurrentContext(), Alpha_Symbol, NUM2VAL(c.alpha)).ToChecked();
	return scope.Escape(obj);
}

v8::Local<v8::Object> v8_MakeJavascriptMemBlock(v8::Isolate* isolate, pdg::MemBlock& mb) {
    v8::EscapableHandleScope scope(isolate);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    v8::Local<v8::Object> proto = v8::Local<v8::Object>::New(isolate, gMemBlockPrototype);
    if (!gMemBlockPrototype.IsEmpty()) obj->SetPrototypeV2(isolate->GetCurrentContext(), proto).ToChecked();
    return scope.Escape(obj);
}

v8::Local<v8::Value> MakeCppOffset(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Offset& o, bool canFail) {
    v8::EscapableHandleScope scope(isolate);
	if (val->IsArray()) {
		v8::Local<v8::Array> arr_ = v8::Local<v8::Array>::Cast(val);
		if (arr_->Length() == 2) {
			// convert 2 element array to point assuming x,y order
			o.x = arr_->Get(isolate->GetCurrentContext(), 0).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			o.y = arr_->Get(isolate->GetCurrentContext(), 1).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Point from Array must be: 2 Numbers [x, y]");
		}
	} else if (val->IsObject()) {
		// convert object with "x" and "y" values
		v8::Local<v8::Object> obj_ = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
		if (obj_->Has(isolate->GetCurrentContext(), X_Symbol).ToChecked() && obj_->Has(isolate->GetCurrentContext(), Y_Symbol).ToChecked()) {
			o.x = obj_->Get(isolate->GetCurrentContext(), X_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			o.y = obj_->Get(isolate->GetCurrentContext(), Y_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Point from Object must be: {x:Number, y:Number}");
		}
	} else {
		return scope.Escape( BOOL2VAL(false) );
  	}
//	SCRIPT_DEBUG_ONLY( OS::_DOUT( "Point: (x:%.1f, y:%.1f)", o.x, o.y); )
	return scope.Escape( BOOL2VAL(true) );
}

v8::Local<v8::Value> MakeCppPoint(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Point& p, bool canFail) {
	return MakeCppOffset(isolate, val, p, canFail);
}

// v8::Local<v8::Value> MakeCppVector(v8::Local<v8::Value> val, pdg::Vector& v, bool canFail) {
// 	return MakeCppOffset(val, v, canFail);
// }
// 

v8::Local<v8::Value> MakeCppRect(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Rect& r, bool canFail) {
    v8::EscapableHandleScope scope(isolate);
  	pdg::Point p;
	if (val->IsArray()) {
		v8::Local<v8::Array> arr_ = v8::Local<v8::Array>::Cast(val);
		if (arr_->Length() == 2) {
			// convert 2 element array of points assuming leftTop, rightBottom order
			v8::Local<v8::Value> resVal = MakeCppPoint(isolate, arr_->Get(isolate->GetCurrentContext(), 0).ToLocalChecked(), p, canFail);
			if (resVal->IsTrue()) {
				r.left = p.x;
				r.top = p.y;			
				resVal = MakeCppPoint(isolate, arr_->Get(isolate->GetCurrentContext(), 1).ToLocalChecked(), p, canFail);
				if (!resVal->IsTrue()) {
				    return scope.Escape(resVal);
				}
				r.right = p.x;
				r.bottom = p.y;
			} else {
				// convert 2 element array to width, height
				r.top = 0;
				r.left = 0;
				r.right = arr_->Get(isolate->GetCurrentContext(), 0).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
				r.bottom = arr_->Get(isolate->GetCurrentContext(), 1).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			}
		} else if (arr_->Length() == 4) {
			// convert 4 element array to left, top, right, bottom (ie: x1, y1, x2, y2)
			r.left = arr_->Get(isolate->GetCurrentContext(), 0).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			r.top = arr_->Get(isolate->GetCurrentContext(), 1).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			r.right = arr_->Get(isolate->GetCurrentContext(), 2).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			r.bottom = arr_->Get(isolate->GetCurrentContext(), 3).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Rect from Array must be: 2 points [topLeft, botRight], or "
					"2 Numbers [width, height], or 4 Numbers [left, top, right, bottom]");
		}
	} else if (val->IsObject()) {
		v8::Local<v8::Object> obj_ = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
		if (obj_->Has(isolate->GetCurrentContext(), Top_Symbol).ToChecked() && obj_->Has(isolate->GetCurrentContext(), Left_Symbol).ToChecked() 
		  && obj_->Has(isolate->GetCurrentContext(), Right_Symbol).ToChecked() && obj_->Has(isolate->GetCurrentContext(), Bottom_Symbol).ToChecked()) {
			// convert object with "top" "left" "right" and "bottom" values
			r.left = obj_->Get(isolate->GetCurrentContext(), Left_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			r.top = obj_->Get(isolate->GetCurrentContext(), Top_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			r.right = obj_->Get(isolate->GetCurrentContext(), Right_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			r.bottom = obj_->Get(isolate->GetCurrentContext(), Bottom_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
		} else if (obj_->Has(isolate->GetCurrentContext(), Width_Symbol).ToChecked() && obj_->Has(isolate->GetCurrentContext(), Height_Symbol).ToChecked()) {
			// convert object with "width" and "height" values (and optional "topleft")
			if (obj_->Has(isolate->GetCurrentContext(), TopLeft_Symbol).ToChecked()) {
				v8::Local<v8::Value> resVal = MakeCppPoint(isolate, obj_->Get(isolate->GetCurrentContext(), TopLeft_Symbol).ToLocalChecked(), p, canFail);
				if (!resVal->IsTrue()) {
				    return scope.Escape(resVal);
				}
				r.left = p.x;
				r.top = p.y;
			} else {
				r.left = 0;
				r.top = 0;
			}
			r.setWidth( obj_->Get(isolate->GetCurrentContext(), Width_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked() );
			r.setHeight( obj_->Get(isolate->GetCurrentContext(), Height_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked() );
		} else if (obj_->Has(isolate->GetCurrentContext(), TopLeft_Symbol).ToChecked() && obj_->Has(isolate->GetCurrentContext(), BottomRight_Symbol).ToChecked()) {
			// convert object with "topleft" and "bottomright" values
			v8::Local<v8::Value> resVal = MakeCppPoint(isolate, obj_->Get(isolate->GetCurrentContext(), TopLeft_Symbol).ToLocalChecked(), p, canFail);
			if (!resVal->IsTrue()) {
				return scope.Escape(resVal);
			}
			r.left = p.x;
			r.top = p.y;
			resVal = MakeCppPoint(isolate, obj_->Get(isolate->GetCurrentContext(), BottomRight_Symbol).ToLocalChecked(), p, canFail);
			if (!resVal->IsTrue()) {
			    return scope.Escape(resVal);
			}
			r.right = p.x;
			r.bottom = p.y;
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Rect from Object must be: \n"
				"  { top:n, right:n, bottom:n, left:n [, radians:n] }, or \n"
				"  { height:n, width:n [, topleft : {x:n, y:n} ] [, radians:n] }, or \n"
				"  { topleft: {x:n, y:n}, bottomright: {x:n, y:n} [, radians:n] }" );
		}
	} else {
		return scope.Escape( BOOL2VAL(false) );
	}
// 	SCRIPT_DEBUG_ONLY( OS::_DOUT( "Rect: (t:%.1f, l:%.1f, r:%.1f, b:%.1f)",
// 			r.top, r.left, r.right, r.bottom ); )
	return scope.Escape( BOOL2VAL(true) );
}

v8::Local<v8::Value> MakeCppRect(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::RotatedRect& rr, bool canFail) {
    v8::EscapableHandleScope scope(isolate);
  	pdg::Rect r;
  	if (MakeCppRect(isolate, val, r, canFail)->IsTrue()) {
  		// always accept a rectangle as a Quad
  		rr = pdg::RotatedRect(r);
  		// check for optional rotation
  		if (val->IsObject()) {
			v8::Local<v8::Object> obj_ = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
			if (obj_->Has(isolate->GetCurrentContext(), Radians_Symbol).ToChecked()) {
				float radians = obj_->Get(isolate->GetCurrentContext(), Radians_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
				rr.radians = radians;
			}
			pdg::Point centerPtOffset;
			if (obj_->Has(isolate->GetCurrentContext(), CenterOffset_Symbol).ToChecked()) {
				MakeCppPoint(isolate, obj_->Get(isolate->GetCurrentContext(), CenterOffset_Symbol).ToLocalChecked(), centerPtOffset, canFail);
			}
			rr.centerOffset = centerPtOffset;
		}
  	} else if (canFail) {
		return scope.Escape( BOOL2VAL(false) );
  	} else {
		THROW_SYNTAX_ERR("Rect from Object must be: \n"
			"  { top:n, right:n, bottom:n, left:n [, radians:n] [, centeroffset: Point] }, or \n"
			"  { height:n, width:n [, topleft : {x:n, y:n} ] [, radians:n] [, centeroffset: Point] }, or \n"
			"  { topleft: {x:n, y:n}, bottomright: {x:n, y:n} [, radians:n] [, centeroffset: Point] }" );
  	}
// 	SCRIPT_DEBUG_ONLY( OS::_DOUT( "RotatedRect: (t:%.1f, l:%.1f, r:%.1f, b:%.1f, r:%.1f, co.x:%.1f, co.y:%.1f)",
// 			rr.top, rr.left, rr.right, rr.bottom, rr.radians, rr.centerOffset.x, rr.centerOffset.y ); )
	return scope.Escape( BOOL2VAL(true) );
}
  	
v8::Local<v8::Value> MakeCppQuad(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Quad& q, bool canFail) {
    v8::EscapableHandleScope scope(isolate);
  	pdg::Rect r;
  	if (MakeCppRect(isolate, val, r, canFail)->IsTrue()) {
  		// always accept a rectangle as a Quad
  		q = pdg::Quad(r);
  		// check for optional rotation
  		if (val->IsObject()) {
			v8::Local<v8::Object> obj_ = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
			if (obj_->Has(isolate->GetCurrentContext(), Radians_Symbol).ToChecked()) {
				float radians = obj_->Get(isolate->GetCurrentContext(), Radians_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
				pdg::Point centerPtOffset;
				if (obj_->Has(isolate->GetCurrentContext(), CenterOffset_Symbol).ToChecked()) {
					MakeCppPoint(isolate, obj_->Get(isolate->GetCurrentContext(), CenterOffset_Symbol).ToLocalChecked(), centerPtOffset, canFail);
				}
				q.rotate(radians, centerPtOffset);
			}
		}
  	} else if (val->IsArray()) {
		v8::Local<v8::Array> arr_ = v8::Local<v8::Array>::Cast(val);
		if (arr_->Length() == 4) {
			// convert array of points into quad
			v8::Local<v8::Value> resVal;
			for (int i = 0; i < 4; i++) {
				resVal = MakeCppPoint(isolate, arr_->Get(isolate->GetCurrentContext(), i).ToLocalChecked(), q.points[i], canFail);
				if (!resVal->IsTrue())  {
				    return scope.Escape(resVal);
				}
			}
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Quad from Array must be: Array[4] of points");
		}
	} else if (val->IsObject()) {
		// Handle JavaScript pdg.Quad() object with points property
		v8::Local<v8::Object> obj_ = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
		if (obj_->Has(isolate->GetCurrentContext(), Points_Symbol).ToChecked()) {
			v8::Local<v8::Value> pointsVal = obj_->Get(isolate->GetCurrentContext(), Points_Symbol).ToLocalChecked();
			if (pointsVal->IsArray()) {
				v8::Local<v8::Array> pointsArr = v8::Local<v8::Array>::Cast(pointsVal);
				if (pointsArr->Length() == 4) {
					// convert array of points into quad
					v8::Local<v8::Value> resVal;
					for (int i = 0; i < 4; i++) {
						resVal = MakeCppPoint(isolate, pointsArr->Get(isolate->GetCurrentContext(), i).ToLocalChecked(), q.points[i], canFail);
						if (!resVal->IsTrue()) {
							return scope.Escape(resVal);
						}
					}
				} else if (canFail) {
					return scope.Escape( BOOL2VAL(false) );
				} else {
					THROW_SYNTAX_ERR("Quad points array must have exactly 4 points");
				}
			} else if (canFail) {
				return scope.Escape( BOOL2VAL(false) );
			} else {
				THROW_SYNTAX_ERR("Quad points property must be an array");
			}
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Quad object must have a points property");
		}
	} else {
		return scope.Escape( BOOL2VAL(false) );
	}
// 	SCRIPT_DEBUG_ONLY( OS::_DOUT( "Quad: (%.1f, %.1f), (%.1f, %.1f), (%.1f, %.1f), (%.1f, %.1f)",
// 			q.points[0].x, q.points[0].y, q.points[1].x, q.points[1].y, 
// 			q.points[2].x, q.points[2].y, q.points[3].x, q.points[3].y ); )
	return scope.Escape( BOOL2VAL(true) );
}

v8::Local<v8::Value> MakeCppColor(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Color& c, bool canFail) {
    v8::EscapableHandleScope scope(isolate);
  	if (val->IsUint32()) {
		// convert uint32 to color by breaking apart elements
		c = val->Uint32Value(isolate->GetCurrentContext()).ToChecked();
  	} else if (val->IsArray()) {
		// convert 3 or 4 element array to color assuming RGBA order
		v8::Local<v8::Array> arr_ = v8::Local<v8::Array>::Cast(val);
		if (arr_->Length() == 3 || arr_->Length() == 4) {
			c.red = arr_->Get(isolate->GetCurrentContext(), 0).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			c.green = arr_->Get(isolate->GetCurrentContext(), 1).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			c.blue = arr_->Get(isolate->GetCurrentContext(), 2).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			if (arr_->Length() == 4) {
				c.alpha = arr_->Get(isolate->GetCurrentContext(), 3).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			} else {
				c.alpha = 1.0f;
			}
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Color from Array must be: 3 or 4 Numbers [red, green, blue] or "
					"[red, green, blue, alpha]");
		}
	} else if (val->IsString()) {
		v8::String::Utf8Value strVal(isolate, val->ToString(isolate->GetCurrentContext()).ToLocalChecked());
		const char* str = *strVal;
		if (str[0] == '#') {
			// convert string with #hhhhhh or #hhh (css style) value
			int red = 0, green = 0, blue = 0;
			if (str[4] == 0) {  // 3 char str
				if (sscanf(str, "#%1x%1x%1x", &red, &green, &blue) == 3) {
					red = (red << 8) & red;
					green = (green << 8) & green;
					blue = (blue << 8) & blue;
				}
			} else if (str[7] == 0) { // 7 char str
				sscanf(str, "#%2x%2x%2x", &red, &green, &blue);
			} else {
				THROW_SYNTAX_ERR("Color from String must be: '#rgb', '#rrggbb', or css color name" );
			}
			c = Color(red, green, blue);
		} else {
			// convert string with standard css color names 
			const int NUM_COLORS = 147;
			const char* colorNames[NUM_COLORS] = {
				"aliceblue", "antiquewhite", "aqua", "aquamarine", "azure", "beige", "bisque", "black",
				"blanchedalmond", "blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse",
				"chocolate", "coral", "cornflowerblue", "cornsilk", "crimson", "cyan", "darkblue",
				"darkcyan", "darkgoldenrod", "darkgray", "darkgreen", "darkgrey", "darkkhaki",
				"darkmagenta", "darkolivegreen", "darkorange", "darkorchid", "darkred", "darksalmon",
				"darkseagreen", "darkslateblue", "darkslategray", "darkslategrey", "darkturquoise",
				"darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue",
				"firebrick", "floralwhite", "forestgreen", "fuchsia", "gainsboro", "ghostwhite",
				"gold", "goldenrod", "gray", "green", "greenyellow", "grey", "honeydew", "hotpink",
				"indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen",
				"lemonchiffon", "lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow",
				"lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen",
				"lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow",
				"lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue",
				"mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen",
				"mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose",
				"moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange",
				"orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred",
				"papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red",
				"rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen",
				"seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey",
				"snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise",
				"violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen"
			};
			uint32 colorValues[NUM_COLORS] = {
				0xf0f8ff, 0xfaebd7, 0x00ffff, 0x7fffd4, 0xf0ffff, 0xf5f5dc, 0xffe4c4, 0x000000,
				0xffebcd, 0x0000ff, 0x8a2be2, 0xa52a2a, 0xdeb887, 0x5f9ea0, 0x7fff00, 0xd2691e,
				0xff7f50, 0x6495ed, 0xfff8dc, 0xdc143c, 0x00ffff, 0x00008b, 0x008b8b, 0xb8860b,
				0xa9a9a9, 0x006400, 0xa9a9a9, 0xbdb76b, 0x8b008b, 0x556b2f, 0xff8c00, 0x9932cc,
				0x8b0000, 0xe9967a, 0x8fbc8f, 0x483d8b, 0x2f4f4f, 0x2f4f4f, 0x00ced1, 0x9400d3,
				0xff1493, 0x00bfff, 0x696969, 0x696969, 0x1e90ff, 0xb22222, 0xfffaf0, 0x228b22,
				0xff00ff, 0xdcdcdc, 0xf8f8ff, 0xffd700, 0xdaa520, 0x808080, 0x008000, 0xadff2f,
				0x808080, 0xf0fff0, 0xff69b4, 0xcd5c5c, 0x4b0082, 0xfffff0, 0xf0e68c, 0xe6e6fa,
				0xfff0f5, 0x7cfc00, 0xfffacd, 0xadd8e6, 0xf08080, 0xe0ffff, 0xfafad2, 0xd3d3d3,
				0x90ee90, 0xd3d3d3, 0xffb6c1, 0xffa07a, 0x20b2aa, 0x87cefa, 0x778899, 0x778899,
				0xb0c4de, 0xffffe0, 0x00ff00, 0x32cd32, 0xfaf0e6, 0xff00ff, 0x800000, 0x66cdaa,
				0x0000cd, 0xba55d3, 0x9370db, 0x3cb371, 0x7b68ee, 0x00fa9a, 0x48d1cc, 0xc71585,
				0x000080, 0xf5fffa, 0xffe4e1, 0xffe4b5, 0xffdead, 0x000080, 0xfdf5e6, 0x808000,
				0x6b8e23, 0xffa500, 0xff4500, 0xda70d6, 0xeee8aa, 0x98fb98, 0xafeeee, 0xdb7093,
				0xffefd5, 0xffdab9, 0xcd853f, 0xffc0cb, 0xdda0dd, 0xb0e0e6, 0x800080, 0xff0000,
				0xbc8f8f, 0x4169e1, 0x8b4513, 0xfa8072, 0xf4a460, 0x2e8b57, 0xfff5ee, 0xa0522d,
				0xc0c0c0, 0x87ceeb, 0x6a5acd, 0x708090, 0x708090, 0xfffafa, 0x00ff7f, 0x4682b4,
				0xd2b48c, 0x008080, 0xd8bfd8, 0xff6347, 0x40e0d0, 0xee82ee, 0xf5deb3, 0xffffff,
				0xf5f5f5, 0xffff00, 0x9acd32
			};
			bool found = false;
			for (int i = 0; i<NUM_COLORS; i++) {
				if (strcmp(str, colorNames[i]) == 0) {
					c = colorValues[i] | 0xff000000;
					found = true;
					break;
				}
			}
			if (!found) {
				if (canFail) {
			        return scope.Escape( BOOL2VAL(false) );
				} else {
					std::ostringstream msg;
					msg << "Invalid color name \"" << str << "\". Valid names are:";
					for (int i = 0; i<NUM_COLORS; i++) {
						msg << " " << colorNames[i];
					}
					THROW_RANGE_ERR(msg.str().c_str());
				}
			}
		}
	} else if (val->IsObject()) {
		// convert object with "red" "green" "blue" and optional "alpha" values
		v8::Local<v8::Object> obj_ = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
		if (obj_->Has(isolate->GetCurrentContext(), Red_Symbol).ToChecked() && obj_->Has(isolate->GetCurrentContext(), Green_Symbol).ToChecked() 
		  && obj_->Has(isolate->GetCurrentContext(), Blue_Symbol).ToChecked()) {
			c.red = obj_->Get(isolate->GetCurrentContext(), Red_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			c.green = obj_->Get(isolate->GetCurrentContext(), Green_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			c.blue = obj_->Get(isolate->GetCurrentContext(), Blue_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			if (obj_->Has(isolate->GetCurrentContext(), Alpha_Symbol).ToChecked()) {
				c.alpha = obj_->Get(isolate->GetCurrentContext(), Alpha_Symbol).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			} else {
				c.alpha = 1.0f;
			}
		} else if (canFail) {
			return scope.Escape( BOOL2VAL(false) );
		} else {
			THROW_SYNTAX_ERR("Color from Object must be: { red:n, green:n, blue:n [, alpha:n] }" );
		}
	} else {
		return scope.Escape( BOOL2VAL(false) );
	}
// 	SCRIPT_DEBUG_ONLY( OS::_DOUT( "Color: (r:%.1f, g:%.1f, b:%.1f, a:%.1f)", 
// 			c.red, c.green, c.blue, c.alpha ); )
	return scope.Escape( BOOL2VAL(true) );
}

bool v8_ValueIsOffset(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::Offset o;
	return MakeCppOffset(isolate, val, o, true)->IsTrue();
}

bool v8_ValueIsPoint(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	return v8_ValueIsOffset(isolate, val);
}

bool v8_ValueIsVector(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	return v8_ValueIsOffset(isolate, val);
}

bool v8_ValueIsRect(v8::Isolate* isolate, v8::Local<v8::Value> val, bool arrayCheck) {
	pdg::Rect r;
	return MakeCppRect(isolate, val, r, true)->IsTrue();
}

bool v8_ValueIsRotatedRect(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::RotatedRect rr;
	return MakeCppRect(isolate, val, rr, true)->IsTrue();
}

bool v8_ValueIsQuad(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::Quad q;
	return MakeCppQuad(isolate, val, q, true)->IsTrue();
}

bool v8_ValueIsColor(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::Color c;
	return MakeCppColor(isolate, val, c, true)->IsTrue();
}

bool v8_ValueIsSpline(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	if (!val->IsObject()) return false;
	v8::Local<v8::Object> obj = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
	return obj->InternalFieldCount() > 0;
}

Offset  	
v8_ValueToOffset(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::Offset o;
	MakeCppOffset(isolate, val, o, true);
	return o;
}

Point  		
v8_ValueToPoint(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	return v8_ValueToOffset(isolate, val);
}

Vector  	
v8_ValueToVector(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	return v8_ValueToOffset(isolate, val);
}

Rect  		
v8_ValueToRect(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::Rect r;
	MakeCppRect(isolate, val, r, true);
	return r;
}

RotatedRect 
v8_ValueToRotatedRect(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::RotatedRect rr;
	MakeCppRect(isolate, val, rr, true);
	return rr;
}

Quad  		
v8_ValueToQuad(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::Quad q;
	MakeCppQuad(isolate, val, q, true);
	return q;
}

Color  		
v8_ValueToColor(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	pdg::Color c;
	MakeCppColor(isolate, val, c, true);
	return c;
}

Spline*		
v8_ValueToSpline(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	if (!val->IsObject()) return nullptr;
	v8::Local<v8::Object> obj = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
	if (obj->InternalFieldCount() > 0) {
		return static_cast<pdg::Spline*>(obj->GetAlignedPointerFromInternalField(0));
	}
	return nullptr;
}

v8::Local<v8::Object> v8_ObjectCreateEmpty(v8::Isolate* isolate, void* privateDataPtr) {
    v8::EscapableHandleScope scope(isolate);
  	v8::Local<v8::Object> obj;
  	if (privateDataPtr) {
		v8::Local<v8::ObjectTemplate> t = v8::ObjectTemplate::New(isolate); 
        t->SetInternalFieldCount(1);
        obj = t->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
        assert(obj->InternalFieldCount() > 0);
  		obj->SetAlignedPointerInInternalField(0, privateDataPtr);
  	} else {
  		obj = v8::Object::New(isolate);
  	}
	return scope.Escape( obj );
}

static std::unique_ptr<v8::Platform> g_v8_platform;

// Implementation of the global V8 platform access function
v8::Platform* v8_GetPlatform() {
    return g_v8_platform.get();
}

void v8_SetPlatform(v8::Platform* platform) {
    g_v8_platform = std::unique_ptr<v8::Platform>(platform);
}

} // end namespace pdg
