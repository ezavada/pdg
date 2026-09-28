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

#include "color-utils.h"

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

//static v8::Local<v8::Value>  MakeCppVector(v8::Isolate* isolate, v8::Local<v8::Value> val, pdg::Vector &v, bool canFail = false);

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

std::optional<bool> v8_ValueIsOffset(v8::Isolate* isolate, v8::Local<v8::Value> val, Offset& value) {
    Point point;
    auto converted = v8_ValueIsPoint(isolate, val, point);
    if (converted.value_or(false)) value = Offset(point.x, point.y);
    return converted;
}

std::optional<bool> v8_ValueIsVector(v8::Isolate* isolate, v8::Local<v8::Value> val, Vector& value) {
    Point point;
    auto converted = v8_ValueIsPoint(isolate, val, point);
    if (converted.value_or(false)) value = Vector(point.x, point.y);
    return converted;
}

// A failed property read leaves the original JavaScript exception pending.
// Subsequent reads stop immediately, including reads of nested coordinate types.
class V8PropertyReader {
public:
    explicit V8PropertyReader(v8::Isolate* isolate) : isolate(isolate), context(isolate->GetCurrentContext()) {}
    template<size_t N> bool has(v8::Local<v8::Object> object, const char (&name)[N]) {
        if (failed) return false;
        bool present = false;
        auto key = v8::String::NewFromUtf8Literal(isolate, name, v8::NewStringType::kInternalized);
        if (!object->Has(context, key).To(&present)) failed = true;
        return present;
    }
    template<size_t N> v8::Local<v8::Value> get(v8::Local<v8::Object> object, const char (&name)[N]) {
        if (failed) return v8::Undefined(isolate);
        auto key = v8::String::NewFromUtf8Literal(isolate, name, v8::NewStringType::kInternalized);
        return read(object, key);
    }
    v8::Local<v8::Value> get(v8::Local<v8::Object> object, uint32_t index) { return read(object, index); }
    double number(v8::Local<v8::Value> value) {
        double result = 0;
        if (!failed && !value->NumberValue(context).To(&result)) failed = true;
        return result;
    }
    bool failed = false;
private:
    template<class Key> v8::Local<v8::Value> read(v8::Local<v8::Object> object, Key key) {
        v8::Local<v8::Value> value;
        if (!failed && object->Get(context, key).ToLocal(&value)) return value;
        failed = true;
        return v8::Undefined(isolate);
    }
    v8::Isolate* isolate;
    v8::Local<v8::Context> context;
};

std::optional<bool> v8_ValueIsRect(v8::Isolate* isolate, v8::Local<v8::Value> val, Rect& rect) {
    if (!val->IsObject()) return false;
    v8::HandleScope scope(isolate);
    V8PropertyReader read(isolate);
    auto object = val.As<v8::Object>();
    Rect result;
    if (val->IsArray()) {
        auto array = val.As<v8::Array>();
        if (array->Length() == 2) {
            auto first = read.get(object, 0);
            if (read.failed) return std::nullopt;
            Point topLeft, bottomRight;
            auto isPoint = v8_ValueIsPoint(isolate, first, topLeft);
            if (!isPoint.has_value()) return std::nullopt;
            if (*isPoint) {
                auto second = read.get(object, 1);
                if (read.failed) return std::nullopt;
                isPoint = v8_ValueIsPoint(isolate, second, bottomRight);
                if (!isPoint.value_or(false)) return isPoint;
                result = Rect(topLeft, bottomRight);
            } else {
                double width = read.number(first);
                double height = read.number(read.get(object, 1));
                result = Rect(width, height);
            }
        } else if (array->Length() == 4) {
            double left = read.number(read.get(object, 0));
            double top = read.number(read.get(object, 1));
            double right = read.number(read.get(object, 2));
            double bottom = read.number(read.get(object, 3));
            result = Rect(left, top, right, bottom);
        } else {
            return false;
        }
    } else if (read.has(object, "top") && read.has(object, "left") &&
               read.has(object, "right") && read.has(object, "bottom")) {
        double left = read.number(read.get(object, "left"));
        double top = read.number(read.get(object, "top"));
        double right = read.number(read.get(object, "right"));
        double bottom = read.number(read.get(object, "bottom"));
        result = Rect(left, top, right, bottom);
    } else if (read.has(object, "width") && read.has(object, "height")) {
        Point topLeft;
        if (read.has(object, "topLeft")) {
            auto corner = read.get(object, "topLeft");
            if (read.failed) return std::nullopt;
            auto isPoint = v8_ValueIsPoint(isolate, corner, topLeft);
            if (!isPoint.value_or(false)) return isPoint;
        }
        double width = read.number(read.get(object, "width"));
        double height = read.number(read.get(object, "height"));
        result = Rect(topLeft, width, height);
    } else if (read.has(object, "topLeft") && read.has(object, "bottomRight")) {
        auto corner = read.get(object, "topLeft");
        if (read.failed) return std::nullopt;
        Point topLeft, bottomRight;
        auto isPoint = v8_ValueIsPoint(isolate, corner, topLeft);
        if (!isPoint.value_or(false)) return isPoint;
        corner = read.get(object, "bottomRight");
        if (read.failed) return std::nullopt;
        isPoint = v8_ValueIsPoint(isolate, corner, bottomRight);
        if (!isPoint.value_or(false)) return isPoint;
        result = Rect(topLeft, bottomRight);
    } else {
        return read.failed ? std::optional<bool>() : false;
    }
    if (read.failed) return std::nullopt;
    rect = result;
    return true;
}

static std::optional<bool> v8_ReadRectRotation(v8::Isolate* isolate, v8::Local<v8::Object> object, RotatedRect& rect) {
    V8PropertyReader read(isolate);
    if (read.has(object, "radians")) rect.radians = read.number(read.get(object, "radians"));
    if (read.has(object, "centerOffset")) {
        auto center = read.get(object, "centerOffset");
        if (read.failed) return std::nullopt;
        auto isPoint = v8_ValueIsOffset(isolate, center, rect.centerOffset);
        if (!isPoint.value_or(false)) return isPoint;
    }
    if (read.failed) return std::nullopt;
    return true;
}

std::optional<bool> v8_ValueIsRotatedRect(v8::Isolate* isolate, v8::Local<v8::Value> val, RotatedRect& rect) {
    v8::HandleScope scope(isolate);
    Rect base;
    auto converted = v8_ValueIsRect(isolate, val, base);
    if (!converted.value_or(false)) return converted;
    RotatedRect result(base);
    converted = v8_ReadRectRotation(isolate, val.As<v8::Object>(), result);
    if (!converted.value_or(false)) return converted;
    rect = result;
    return true;
}

std::optional<bool> v8_ValueIsQuad(v8::Isolate* isolate, v8::Local<v8::Value> val, Quad& quad) {
    if (!val->IsObject()) return false;
    v8::HandleScope scope(isolate);
    V8PropertyReader read(isolate);
    auto object = val.As<v8::Object>();
    auto points = val;
    bool explicitPoints = false;
    if (!val->IsArray() && read.has(object, "points")) {
        points = read.get(object, "points");
        explicitPoints = true;
    }
    if (read.failed) return std::nullopt;
    if (points->IsArray() && points.As<v8::Array>()->Length() == 4) {
        auto array = points.As<v8::Object>();
        auto first = read.get(array, 0);
        if (read.failed) return std::nullopt;
        Quad result;
        auto isPoint = v8_ValueIsPoint(isolate, first, result.points[0]);
        if (!isPoint.has_value()) return std::nullopt;
        if (*isPoint) {
            for (uint32_t i = 1; i < 4; ++i) {
                auto value = read.get(array, i);
                if (read.failed) return std::nullopt;
                isPoint = v8_ValueIsPoint(isolate, value, result.points[i]);
                if (!isPoint.value_or(false)) return isPoint;
            }
            quad = result;
            return true;
        }
        if (explicitPoints) return false;
        double left = read.number(first);
        double top = read.number(read.get(array, 1));
        double right = read.number(read.get(array, 2));
        double bottom = read.number(read.get(array, 3));
        if (read.failed) return std::nullopt;
        RotatedRect rect(Rect(left, top, right, bottom));
        auto converted = v8_ReadRectRotation(isolate, object, rect);
        if (!converted.value_or(false)) return converted;
        quad = rect.radians == 0 ? Quad(static_cast<Rect>(rect)) : Quad(rect);
        return true;
    }
    if (explicitPoints) return false;
    RotatedRect rect;
    auto converted = v8_ValueIsRotatedRect(isolate, val, rect);
    if (!converted.value_or(false)) return converted;
    quad = rect.radians == 0 ? Quad(static_cast<Rect>(rect)) : Quad(rect);
    return true;
}

std::optional<bool> v8_ValueIsColor(v8::Isolate* isolate, v8::Local<v8::Value> val, Color& color) {
    if (val->IsUint32()) {
        color = Color(val.As<v8::Uint32>()->Value());
        return true;
    }
    v8::HandleScope scope(isolate);
    if (val->IsString()) {
        v8::String::Utf8Value text(isolate, val);
        if (!*text) return std::nullopt;
        return parseCssColor(std::string_view(*text, text.length()), color);
    }
    if (!val->IsObject()) return false;
    auto object = val.As<v8::Object>();
    V8PropertyReader read(isolate);
    Color result;
    if (val->IsArray()) {
        auto length = val.As<v8::Array>()->Length();
        if (length != 3 && length != 4) return false;
        result.red = read.number(read.get(object, 0));
        result.green = read.number(read.get(object, 1));
        result.blue = read.number(read.get(object, 2));
        if (length == 4) result.alpha = read.number(read.get(object, 3));
    } else if (read.has(object, "red") && read.has(object, "green") && read.has(object, "blue")) {
        result.red = read.number(read.get(object, "red"));
        result.green = read.number(read.get(object, "green"));
        result.blue = read.number(read.get(object, "blue"));
        if (read.has(object, "alpha")) result.alpha = read.number(read.get(object, "alpha"));
    } else {
        return read.failed ? std::optional<bool>() : false;
    }
    if (read.failed) return std::nullopt;
    color = result;
    return true;
}


bool v8_ValueIsSpline(v8::Isolate* isolate, v8::Local<v8::Value> val) {
	if (!val->IsObject()) return false;
	v8::Local<v8::Object> obj = val->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
	return obj->InternalFieldCount() > 0;
}



// Validate and convert together; nullopt preserves an exception from a getter
// or numeric conversion. Internalized keys belong to the current isolate.
std::optional<bool> v8_ValueIsPoint(v8::Isolate* isolate, v8::Local<v8::Value> val, Point& point) {
    if (!val->IsObject()) return false;
    v8::HandleScope scope(isolate);
    auto context = isolate->GetCurrentContext();
    auto object = val.As<v8::Object>();
    auto readNumber = [&](auto key, double& number) {
        v8::Local<v8::Value> value;
        return object->Get(context, key).ToLocal(&value) && value->NumberValue(context).To(&number);
    };
    double xNumber, yNumber;
    if (val->IsArray()) {
        if (val.As<v8::Array>()->Length() != 2) return false;
        if (!readNumber(0, xNumber) || !readNumber(1, yNumber))
            return std::nullopt;
    } else {
        auto xKey = v8::String::NewFromUtf8Literal(isolate, "x", v8::NewStringType::kInternalized);
        auto yKey = v8::String::NewFromUtf8Literal(isolate, "y", v8::NewStringType::kInternalized);
        auto hasX = object->Has(context, xKey);
        if (hasX.IsNothing()) return std::nullopt;
        if (!hasX.FromJust()) return false;
        auto hasY = object->Has(context, yKey);
        if (hasY.IsNothing()) return std::nullopt;
        if (!hasY.FromJust()) return false;
        if (!readNumber(xKey, xNumber) || !readNumber(yKey, yNumber))
            return std::nullopt;
    }
    point = Point(xNumber, yNumber);
    return true;
}





Rect v8_ValueToRect(v8::Isolate* isolate, v8::Local<v8::Value> val) {
    Rect result;
    auto converted = v8_ValueIsRect(isolate, val, result);
    if (converted.has_value() && !*converted) { v8_ThrowArgTypeException(isolate, 1, "Rect", *val); }
    return result;
}

RotatedRect v8_ValueToRotatedRect(v8::Isolate* isolate, v8::Local<v8::Value> val) {
    RotatedRect result;
    auto converted = v8_ValueIsRotatedRect(isolate, val, result);
    if (converted.has_value() && !*converted) { v8_ThrowArgTypeException(isolate, 1, "RotatedRect", *val); }
    return result;
}

Quad v8_ValueToQuad(v8::Isolate* isolate, v8::Local<v8::Value> val) {
    Quad result;
    auto converted = v8_ValueIsQuad(isolate, val, result);
    if (converted.has_value() && !*converted) { v8_ThrowArgTypeException(isolate, 1, "Quad", *val); }
    return result;
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
