// -----------------------------------------------
// collider.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>
%#include <cmath>
%#include <limits>

namespace pdg {

#include "physics_object_impl_macros.h"

%#ifdef PDG_USING_JAVASCRIPT_CORE
Collider* New_Collider(SCRIPT_ARGS) { return nullptr; }
static void Collider_finalize(JSObjectRef object) {
    auto* body=static_cast<Collider*>(JSObjectGetPrivate(object));
    if(body) {body->mColliderScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
}
%#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj=obj
%#else
%#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj.Reset(isolate,obj);cppObj->mColliderScriptObj.SetWeak()
ColliderWrap::ColliderWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
ColliderWrap::~ColliderWrap() {
    if(cppPtr_) {cppPtr_->mColliderScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
}
%#endif


WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(Collider, "Sprite.setupCollider or Part.setupCollider",
    COLLIDER_SAVE_WEAK(cppObj,obj);cppObj->addRef())
    EXPORT_FINALIZED_CLASS_SYMBOLS("Collider", Collider, Collider_finalize, , ,
        HAS_METHOD(Collider, "setWantsContactEvents", SetWantsContactEvents)
        HAS_METHOD(Collider, "getWantsContactEvents", GetWantsContactEvents)
        HAS_METHOD(Collider, "setFriction", SetFriction)
        HAS_METHOD(Collider, "setRestitution", SetRestitution)
        HAS_METHOD(Collider, "getFriction", GetFriction)
        HAS_METHOD(Collider, "getRestitution", GetRestitution)
        HAS_METHOD(Collider, "useBodyMaterial", UseBodyMaterial)
        HAS_METHOD(Collider, "isPresent", IsPresent)
        HAS_METHOD(Collider, "isAttached", IsAttached)
        HAS_METHOD(Collider, "isEnabled", IsEnabled)
        HAS_METHOD(Collider, "isSensor", IsSensor)
        HAS_METHOD(Collider, "getId", GetId)
        HAS_METHOD(Collider, "getCategory", GetCategory)
        HAS_METHOD(Collider, "getCollisionMask", GetCollisionMask)
        HAS_METHOD(Collider, "getGroup", GetGroup)
        HAS_METHOD(Collider, "getShapeCount", GetShapeCount)
        HAS_METHOD(Collider, "setEnabled", SetEnabled)
        HAS_METHOD(Collider, "setSensor", SetSensor)
        HAS_METHOD(Collider, "setCategory", SetCategory)
        HAS_METHOD(Collider, "setCollisionMask", SetCollisionMask)
        HAS_METHOD(Collider, "setGroup", SetGroup)
        HAS_METHOD(Collider, "getPhysicsBody", GetPhysicsBody)
        HAS_METHOD(Collider, "setCircle", SetCircle)
        HAS_METHOD(Collider, "addCircle", AddCircle)
        HAS_METHOD(Collider, "setCapsule", SetCapsule)
        HAS_METHOD(Collider, "addCapsule", AddCapsule)
        HAS_METHOD(Collider, "getCapsuleStart", GetCapsuleStart)
        HAS_METHOD(Collider, "getCapsuleEnd", GetCapsuleEnd)
        HAS_METHOD(Collider, "getCapsuleRadius", GetCapsuleRadius)
        HAS_METHOD(Collider, "setBox", SetBox)
        HAS_METHOD(Collider, "addBox", AddBox)
        HAS_METHOD(Collider, "clearShapes", ClearShapes)
        HAS_METHOD(Collider, "useOwnerPhysics", UseOwnerPhysics)
        HAS_METHOD(Collider, "setPhysicsBody", SetPhysicsBody)
        HAS_METHOD(Collider, "getBounds", GetBounds)
        HAS_METHOD(Collider, "contains", Contains)
        HAS_METHOD(Collider, "overlaps", Overlaps)
        HAS_METHOD(Collider, "removeShape", RemoveShape)
        HAS_METHOD(Collider, "getShapeId", GetShapeId)
        HAS_METHOD(Collider, "getContactError", GetContactError)
        HAS_METHOD(Collider, "addPolygon", AddPolygon)
        HAS_METHOD(Collider, "setPolygon", SetPolygon)
        HAS_METHOD(Collider, "setImageMask", SetImageMask)
        HAS_METHOD(Collider, "addImageMask", AddImageMask)
        HAS_METHOD(Collider, "getGeometrySource", GetGeometrySource)
        HAS_METHOD(Collider, "isSourceShape", IsSourceShape)
        HAS_METHOD(Collider, "getShapeName", GetShapeName)
        HAS_METHOD(Collider, "getShapeType", GetShapeType)
        HAS_METHOD(Collider, "getCircleRadius", GetCircleRadius)
        HAS_METHOD(Collider, "setContactHandler", SetContactHandler)
        HAS_METHOD(Collider, "setCollisionFilter", SetCollisionFilter)

    );
    END
%#undef COLLIDER_SAVE_WEAK

METHOD_IMPL(Collider, IsPresent)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isPresent()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, IsAttached)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isAttached()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, IsEnabled)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isEnabled()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, IsSensor)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isSensor()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetId)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getId()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCategory)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getCategory()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCollisionMask)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getCollisionMask()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetGroup)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getGroup()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetShapeCount)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getShapeCount()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetEnabled)
    METHOD_SIGNATURE("Enable or suspend participation in collision worlds.", [this], 1, (boolean value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,value); self->setEnabled(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetSensor)
    METHOD_SIGNATURE("Choose overlap-only contact reporting.", [this], 1, (boolean value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,value); self->setSensor(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCategory)
    METHOD_SIGNATURE("Set this collider's category bits.", [this], 1, ([number uint] value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } self->setCategory(uint32_t(value)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCollisionMask)
    METHOD_SIGNATURE("Set the categories this collider accepts.", [this], 1, ([number uint] value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } self->setCollisionMask(uint32_t(value)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetGroup)
    METHOD_SIGNATURE("Set an optional collision exclusion group.", [this], 1, ([number uint] value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } self->setGroup(uint32_t(value)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetPhysicsBody)
    METHOD_SIGNATURE("", [object PhysicsBody&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->getPhysicsBody(); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCircle)
    METHOD_SIGNATURE("Replace all geometry with one circle.", [this], 1, (number radius, [object Point const&] center = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1,radius); OPTIONAL_POINT_ARG(2,center,Point()); self->setCircle(radius,center); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddCircle)
    METHOD_SIGNATURE("", [number uint], 1, (number radius, [object Point const&] center = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1,radius); OPTIONAL_POINT_ARG(2,center,Point()); RETURN_NUMBER(self->addCircle(radius,center)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCapsule)
    METHOD_SIGNATURE("Replace all geometry with one capsule.", [this], 3, ([object Point const&] start, [object Point const&] end, number radius));
    try { REQUIRE_ARG_COUNT(3); REQUIRE_POINT_ARG(1,start); REQUIRE_POINT_ARG(2,end); REQUIRE_NUMBER_ARG(3,radius); self->setCapsule(start,end,radius); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddCapsule)
    METHOD_SIGNATURE("", [number uint], 3, ([object Point const&] start, [object Point const&] end, number radius));
    try { REQUIRE_ARG_COUNT(3); REQUIRE_POINT_ARG(1,start); REQUIRE_POINT_ARG(2,end); REQUIRE_NUMBER_ARG(3,radius); RETURN_NUMBER(self->addCapsule(start,end,radius)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCapsuleStart)
    METHOD_SIGNATURE("", [object Point], 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        auto result=self->getCapsuleStart(uint32_t(value)); RETURN_POINT(result);
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCapsuleEnd)
    METHOD_SIGNATURE("", [object Point], 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        auto result=self->getCapsuleEnd(uint32_t(value)); RETURN_POINT(result);
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCapsuleRadius)
    METHOD_SIGNATURE("", number, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        RETURN_NUMBER(self->getCapsuleRadius(uint32_t(value)));
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetBox)
    METHOD_SIGNATURE("Replace all geometry with one rectangle.", [this], 1, ([object Rect const&] bounds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1,bounds); self->setBox(bounds); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddBox)
    METHOD_SIGNATURE("", [number uint], 1, ([object Rect const&] bounds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1,bounds); RETURN_NUMBER(self->addBox(bounds)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, ClearShapes)
    METHOD_SIGNATURE("Remove every collision shape.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->clearShapes(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, UseOwnerPhysics)
    METHOD_SIGNATURE("Restore the owner's current body association.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->useOwnerPhysics(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetPhysicsBody)
    METHOD_SIGNATURE("Associate these shapes with an explicit compound body.", [this], 1, ([object PhysicsBody&] body));
    try { REQUIRE_ARG_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,body,PhysicsBody); self->setPhysicsBody(*body); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetBounds)
    METHOD_SIGNATURE("", [object Rect], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto bounds=self->getBounds(); RETURN_RECT(bounds); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, Contains)
    METHOD_SIGNATURE("", boolean, 1, ([object Point const&] worldPoint));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_POINT_ARG(1,point); RETURN_BOOL(self->contains(point)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, Overlaps)
    METHOD_SIGNATURE("", boolean, 1, ([object Collider const&] other));
    try { REQUIRE_ARG_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],false)) { THROW_TYPE_ERR("Expected a Collider"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,Collider); RETURN_BOOL(self->overlaps(*other)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, RemoveShape)
    METHOD_SIGNATURE("", boolean, 1, ([number uint] id));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id)) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } RETURN_BOOL(self->removeShape(uint32_t(id))); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetShapeId)
    METHOD_SIGNATURE("", [number uint], 1, ([number uint] id));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id)) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } RETURN_NUMBER(self->getShapeId(uint32_t(id))); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetContactError)
    METHOD_SIGNATURE("", string, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_STRING(self->getContactError().c_str()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddPolygon)
    METHOD_SIGNATURE("", [number uint], 1, ({ array vertices | [object Polygon const&] polygon }));
    try { REQUIRE_ARG_COUNT(1); std::vector<Point> points;
%#ifdef PDG_USING_JAVASCRIPT_CORE
        if(!JSValueIsArray(ctx,ARGV[0])) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=VAL2OBJ(ARGV[0]); auto lengthName=JSStringCreateWithUTF8CString("length");
        auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
        const double length=VAL2NUM(lengthValue);
        if(length<3||length>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<unsigned(length);++i) { auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#else
        if(!ARGV[0]->IsArray()) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=ARGV[0].As<v8::Array>();
        if(array->Length()<3||array->Length()>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<array->Length();++i) { v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#endif
        RETURN_NUMBER(self->addPolygon(points)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetPolygon)
    METHOD_SIGNATURE("Replace all geometry with one polygon.", [this], 1, ({ array vertices | [object Polygon const&] polygon }));
    try { REQUIRE_ARG_COUNT(1); std::vector<Point> points;
%#ifdef PDG_USING_JAVASCRIPT_CORE
        if(!JSValueIsArray(ctx,ARGV[0])) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=VAL2OBJ(ARGV[0]); auto lengthName=JSStringCreateWithUTF8CString("length");
        auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
        const double length=VAL2NUM(lengthValue);
        if(length<3||length>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<unsigned(length);++i) { auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#else
        if(!ARGV[0]->IsArray()) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=ARGV[0].As<v8::Array>();
        if(array->Length()<3||array->Length()>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<array->Length();++i) { v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#endif
        self->setPolygon(points); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
DECLARE_SYMBOL(collider); DECLARE_SYMBOL(other); DECLARE_SYMBOL(shape); DECLARE_SYMBOL(otherShape);
DECLARE_SYMBOL(phase); DECLARE_SYMBOL(penetration); DECLARE_SYMBOL(point); DECLARE_SYMBOL(normal);
DECLARE_SYMBOL(impulse); DECLARE_SYMBOL(sensor);
struct ColliderScriptCallback {
%#ifdef PDG_USING_JAVASCRIPT_CORE
    JSGlobalContextRef context;
    JSObjectRef function;
    ColliderScriptCallback(JSContextRef ctx, JSObjectRef callback)
        : context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))),function(callback) { JSValueProtect(context,function); }
    ~ColliderScriptCallback() { JSValueUnprotect(context,function);JSGlobalContextRelease(context); }
%#else
    v8::Isolate* isolate;
    v8::Global<v8::Context> context;
    v8::Global<v8::Function> function;
    ColliderScriptCallback(v8::Isolate* engine,v8::Local<v8::Function> callback)
        : isolate(engine),context(engine,engine->GetCurrentContext()),function(engine,callback) {}
%#endif
    bool invoke(const Collider& a,const Collider& b,const ColliderContact* contact) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
        JSContextRef ctx=context;JSValueRef error=nullptr;JSValueRef* exception=&error;
        auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj?c->mColliderScriptObj:Collider_newFromCpp(ctx,c); };
        auto event=JSObjectMake(ctx,nullptr,nullptr);
%#else
        v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
        auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj.IsEmpty()?ColliderWrap::NewFromCpp(isolate,c):v8::Local<v8::Object>::New(isolate,c->mColliderScriptObj); };
        auto event=v8::Object::New(isolate);
%#endif
        VALUE argv[2]={object(a),object(b)};
        if(contact) {
            Point point=contact->point;Vector normal=contact->normal,impulse=contact->impulse;
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(collider),argv[0]);
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(other),argv[1]);
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(shape),NUM2VAL(contact->shape));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(otherShape),NUM2VAL(contact->otherShape));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(phase),NUM2VAL(contact->phase));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(penetration),NUM2VAL(contact->penetration));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(point),POINT2VAL(point));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(normal),VECTOR2VAL(normal));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(impulse),VECTOR2VAL(impulse));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(sensor),BOOL2VAL(contact->sensor));
            argv[0]=event;
        }
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result=JSObjectCallAsFunction(ctx,function,nullptr,contact?1:2,argv,exception);
        if(error) throw std::runtime_error("Collider callback failed");
        if(!contact&&!JSValueIsBoolean(ctx,result)) throw std::runtime_error("Collision filter must return a boolean");
        return contact || JSValueToBoolean(ctx,result);
%#else
        v8::Local<v8::Value> result;
        if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),contact?1:2,argv).ToLocal(&result)) {
            v8::String::Utf8Value message(isolate,catcher.Exception());
            throw std::runtime_error(*message?*message:"Collider callback failed");
        }
        if(!contact&&!result->IsBoolean()) throw std::runtime_error("Collision filter must return a boolean");
        return contact || result->BooleanValue(isolate);
%#endif
    }
};
METHOD_IMPL(Collider, SetContactHandler)
    METHOD_SIGNATURE("Install a contact listener.", [this], 1, (function callback));
    try { REQUIRE_ARG_COUNT(1);
        if(VALUE_IS_NULL(ARGV[0])) { self->setContactHandler({}); RETURN_THIS; }
        REQUIRE_FUNCTION_ARG(1,func);
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
%#else
        auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
%#endif
        self->setContactHandler([callback](const ColliderContact& c) { callback->invoke(*c.collider,*c.other,&c); }); RETURN_THIS;
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, SetCollisionFilter)
    METHOD_SIGNATURE("Filter contacts independently of owner type.", [this], 1, (function callback));
    try { REQUIRE_ARG_COUNT(1);
        if(VALUE_IS_NULL(ARGV[0])) { self->setCollisionFilter({}); RETURN_THIS; }
        REQUIRE_FUNCTION_ARG(1,func);
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
%#else
        auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
%#endif
        self->setCollisionFilter([callback](const Collider& a,const Collider& b) { return callback->invoke(a,b,nullptr); }); RETURN_THIS;
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetGeometrySource)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_INTEGER(self->getGeometrySource()); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, IsSourceShape)
    METHOD_SIGNATURE("", boolean, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); RETURN_BOOL(self->isSourceShape(id));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetShapeName)
    METHOD_SIGNATURE("", string, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); auto name=self->getShapeName(id); RETURN_STRING(name.c_str());
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetShapeType)
    METHOD_SIGNATURE("", number, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); RETURN_INTEGER(self->getShapeType(id));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetCircleRadius)
    METHOD_SIGNATURE("", number, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); RETURN_NUMBER(self->getCircleRadius(id));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, SetImageMask)
    METHOD_SIGNATURE("Copy opaque image pixels into collision geometry.", [this], 2, ([object Image&] image, [object Rect const&] localBounds, [number int] alphaThreshold = 128));
    try { REQUIRE_ARG_MIN_COUNT(2); REQUIRE_CPP_OBJECT_ARG(1,image,Image); REQUIRE_RECT_ARG(2,bounds); OPTIONAL_NUMBER_ARG(3,threshold,128); if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold) { THROW_RANGE_ERR("Expected an integer alpha threshold from 1 to 255"); RETURN_NULL; } self->setImageMask(*image,bounds,threshold); RETURN_THIS; }
    catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, AddImageMask)
    METHOD_SIGNATURE("", [number uint], 2, ([object Image&] image, [object Rect const&] localBounds, [number int] alphaThreshold = 128));
    try { REQUIRE_ARG_MIN_COUNT(2); REQUIRE_CPP_OBJECT_ARG(1,image,Image); REQUIRE_RECT_ARG(2,bounds); OPTIONAL_NUMBER_ARG(3,threshold,128); if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold) { THROW_RANGE_ERR("Expected an integer alpha threshold from 1 to 255"); RETURN_NULL; } RETURN_NUMBER(self->addImageMask(*image,bounds,threshold)); }
    catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

METHOD_IMPL(Collider, SetWantsContactEvents)
    METHOD_SIGNATURE("Enable contact events on the owning Sprite.", [this], 1, (boolean wanted));
    REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,wanted); self->setWantsContactEvents(wanted); RETURN_THIS;
    END
METHOD_IMPL(Collider, GetWantsContactEvents)
    METHOD_SIGNATURE("whether owner contact events are requested", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->getWantsContactEvents());
    END
METHOD_IMPL(Collider, SetFriction)
    METHOD_SIGNATURE("Override this collider's contact friction.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setFriction(value); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetRestitution)
    METHOD_SIGNATURE("Override this collider's restitution.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setRestitution(value); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetFriction)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getFriction()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetRestitution)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getRestitution()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, UseBodyMaterial)
    METHOD_SIGNATURE("Clear both per-collider material overrides.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->useBodyMaterial(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END

} // namespace pdg

/* @pdg-contract
{
  "name": "Collider.addPolygon",
  "value": {
    "params": {
      "vertices": {
        "items": {
          "type": "object Point"
        }
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Collider.setPolygon",
  "value": {
    "params": {
      "vertices": {
        "items": {
          "type": "object Point"
        }
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Collider.setContactHandler",
  "value": {
    "params": {
      "callback": {
        "schema": "ColliderContactCallback",
        "nullable": true
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Collider.setCollisionFilter",
  "value": {
    "params": {
      "callback": {
        "schema": "ColliderFilterCallback",
        "nullable": true
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "ColliderContact",
  "value": {
    "kind": "record",
    "fields": {
      "collider": {
        "type": "object Collider"
      },
      "other": {
        "type": "object Collider"
      },
      "shape": {
        "type": "number"
      },
      "otherShape": {
        "type": "number"
      },
      "phase": {
        "type": "number"
      },
      "penetration": {
        "type": "number"
      },
      "point": {
        "type": "object Point"
      },
      "normal": {
        "type": "object Vector"
      },
      "impulse": {
        "type": "object Vector"
      },
      "sensor": {
        "type": "boolean"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "ColliderContactCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "contact",
        "schema": "ColliderContact"
      }
    ],
    "returns": {
      "type": "void"
    }
  }
}
*/

/* @pdg-schema
{
  "name": "ColliderFilterCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "collider",
        "type": "object Collider"
      },
      {
        "name": "other",
        "type": "object Collider"
      }
    ],
    "returns": {
      "type": "boolean"
    },
    "synchronous": true
  }
}
*/
