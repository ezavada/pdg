// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/collider.cpp
//    $PDG_ROOT/src/bindings/javascript/v8/pdg_script_macros.h
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

#define PDG_COMPILING_SCRIPT_IMPL

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>
#include <cmath>
#include <limits>

namespace pdg
{

#ifdef PDG_USING_JAVASCRIPT_CORE
    static bool collisionArgumentIs(JSContextRef ctx, JSValueRef value, bool body)
    {
        return JSValueIsObjectOfClass(ctx, value, body ? PhysicsBody_class() : Collider_class());
    }
#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(ctx, value, body)
#else
    static bool collisionArgumentIs(v8::Isolate* isolate, v8::Local<v8::Value> value, bool body)
    {
        return (body ? PhysicsBodyWrap::GetTemplate(isolate) : ColliderWrap::GetTemplate(isolate))->HasInstance(value);
    }
#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(isolate, value, body)
#endif

#ifdef PDG_USING_JAVASCRIPT_CORE
    Collider* New_Collider(const v8::FunctionCallbackInfo<v8::Value>& args) { return nullptr; }
    static void Collider_finalize(JSObjectRef object)
    {
        auto* body=static_cast<Collider*>(JSObjectGetPrivate(object));
        if(body) {body->mColliderScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
    }
#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj=obj
#else
#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj.Reset(isolate,obj);cppObj->mColliderScriptObj.SetWeak()
    ColliderWrap::ColliderWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(nullptr) {}
    ColliderWrap::~ColliderWrap()
    {
        if(cppPtr_) {cppPtr_->mColliderScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
    }
#endif

    static bool s_Collider_InNewFromCpp = false;

    void ColliderWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_Collider_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "Collider" " cannot be instantiated with 'new'. Use the factory function: pdg." "Sprite.setupCollider or Part.setupCollider" "()"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        ColliderWrap* objWrapper = new ColliderWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Local<v8::Object> ColliderWrap::NewFromCpp(v8::Isolate* isolate, Collider* cppObj)
    {
        s_Collider_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Collider_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Collider_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(instance);
        {
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            COLLIDER_SAVE_WEAK(cppObj,obj);cppObj->addRef();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_Collider_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ColliderWrap::constructorTpl_;

    void ColliderWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Collider").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> SetWantsContactEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsContactEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsContactEvents, v8::Local<v8::Value>(), SetWantsContactEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setWantsContactEvents").ToLocalChecked(), SetWantsContactEvents_Tpl);
        v8::Local<v8::Signature> GetWantsContactEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsContactEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsContactEvents, v8::Local<v8::Value>(), GetWantsContactEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getWantsContactEvents").ToLocalChecked(), GetWantsContactEvents_Tpl);
        v8::Local<v8::Signature> SetFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFriction_Tpl =
            v8::FunctionTemplate::New(isolate, SetFriction, v8::Local<v8::Value>(), SetFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFriction").ToLocalChecked(), SetFriction_Tpl);
        v8::Local<v8::Signature> SetRestitution_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRestitution_Tpl =
            v8::FunctionTemplate::New(isolate, SetRestitution, v8::Local<v8::Value>(), SetRestitution_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setRestitution").ToLocalChecked(), SetRestitution_Tpl);
        v8::Local<v8::Signature> GetFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFriction_Tpl =
            v8::FunctionTemplate::New(isolate, GetFriction, v8::Local<v8::Value>(), GetFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFriction").ToLocalChecked(), GetFriction_Tpl);
        v8::Local<v8::Signature> GetRestitution_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRestitution_Tpl =
            v8::FunctionTemplate::New(isolate, GetRestitution, v8::Local<v8::Value>(), GetRestitution_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRestitution").ToLocalChecked(), GetRestitution_Tpl);
        v8::Local<v8::Signature> UseBodyMaterial_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UseBodyMaterial_Tpl =
            v8::FunctionTemplate::New(isolate, UseBodyMaterial, v8::Local<v8::Value>(), UseBodyMaterial_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "useBodyMaterial").ToLocalChecked(), UseBodyMaterial_Tpl);
        v8::Local<v8::Signature> IsPresent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsPresent_Tpl =
            v8::FunctionTemplate::New(isolate, IsPresent, v8::Local<v8::Value>(), IsPresent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isPresent").ToLocalChecked(), IsPresent_Tpl);
        v8::Local<v8::Signature> IsAttached_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAttached_Tpl =
            v8::FunctionTemplate::New(isolate, IsAttached, v8::Local<v8::Value>(), IsAttached_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAttached").ToLocalChecked(), IsAttached_Tpl);
        v8::Local<v8::Signature> IsEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, IsEnabled, v8::Local<v8::Value>(), IsEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isEnabled").ToLocalChecked(), IsEnabled_Tpl);
        v8::Local<v8::Signature> IsSensor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsSensor_Tpl =
            v8::FunctionTemplate::New(isolate, IsSensor, v8::Local<v8::Value>(), IsSensor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isSensor").ToLocalChecked(), IsSensor_Tpl);
        v8::Local<v8::Signature> GetId_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetId_Tpl =
            v8::FunctionTemplate::New(isolate, GetId, v8::Local<v8::Value>(), GetId_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getId").ToLocalChecked(), GetId_Tpl);
        v8::Local<v8::Signature> GetCategory_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCategory_Tpl =
            v8::FunctionTemplate::New(isolate, GetCategory, v8::Local<v8::Value>(), GetCategory_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCategory").ToLocalChecked(), GetCategory_Tpl);
        v8::Local<v8::Signature> GetCollisionMask_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollisionMask_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollisionMask, v8::Local<v8::Value>(), GetCollisionMask_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCollisionMask").ToLocalChecked(), GetCollisionMask_Tpl);
        v8::Local<v8::Signature> GetGroup_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGroup_Tpl =
            v8::FunctionTemplate::New(isolate, GetGroup, v8::Local<v8::Value>(), GetGroup_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGroup").ToLocalChecked(), GetGroup_Tpl);
        v8::Local<v8::Signature> GetShapeCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetShapeCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetShapeCount, v8::Local<v8::Value>(), GetShapeCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getShapeCount").ToLocalChecked(), GetShapeCount_Tpl);
        v8::Local<v8::Signature> SetEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, SetEnabled, v8::Local<v8::Value>(), SetEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setEnabled").ToLocalChecked(), SetEnabled_Tpl);
        v8::Local<v8::Signature> SetSensor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSensor_Tpl =
            v8::FunctionTemplate::New(isolate, SetSensor, v8::Local<v8::Value>(), SetSensor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSensor").ToLocalChecked(), SetSensor_Tpl);
        v8::Local<v8::Signature> SetCategory_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCategory_Tpl =
            v8::FunctionTemplate::New(isolate, SetCategory, v8::Local<v8::Value>(), SetCategory_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCategory").ToLocalChecked(), SetCategory_Tpl);
        v8::Local<v8::Signature> SetCollisionMask_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollisionMask_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollisionMask, v8::Local<v8::Value>(), SetCollisionMask_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCollisionMask").ToLocalChecked(), SetCollisionMask_Tpl);
        v8::Local<v8::Signature> SetGroup_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGroup_Tpl =
            v8::FunctionTemplate::New(isolate, SetGroup, v8::Local<v8::Value>(), SetGroup_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setGroup").ToLocalChecked(), SetGroup_Tpl);
        v8::Local<v8::Signature> GetPhysicsBody_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPhysicsBody_Tpl =
            v8::FunctionTemplate::New(isolate, GetPhysicsBody, v8::Local<v8::Value>(), GetPhysicsBody_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPhysicsBody").ToLocalChecked(), GetPhysicsBody_Tpl);
        v8::Local<v8::Signature> SetCircle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCircle_Tpl =
            v8::FunctionTemplate::New(isolate, SetCircle, v8::Local<v8::Value>(), SetCircle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCircle").ToLocalChecked(), SetCircle_Tpl);
        v8::Local<v8::Signature> AddCircle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddCircle_Tpl =
            v8::FunctionTemplate::New(isolate, AddCircle, v8::Local<v8::Value>(), AddCircle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addCircle").ToLocalChecked(), AddCircle_Tpl);
        v8::Local<v8::Signature> SetCapsule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCapsule_Tpl =
            v8::FunctionTemplate::New(isolate, SetCapsule, v8::Local<v8::Value>(), SetCapsule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCapsule").ToLocalChecked(), SetCapsule_Tpl);
        v8::Local<v8::Signature> AddCapsule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddCapsule_Tpl =
            v8::FunctionTemplate::New(isolate, AddCapsule, v8::Local<v8::Value>(), AddCapsule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addCapsule").ToLocalChecked(), AddCapsule_Tpl);
        v8::Local<v8::Signature> GetCapsuleStart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCapsuleStart_Tpl =
            v8::FunctionTemplate::New(isolate, GetCapsuleStart, v8::Local<v8::Value>(), GetCapsuleStart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCapsuleStart").ToLocalChecked(), GetCapsuleStart_Tpl);
        v8::Local<v8::Signature> GetCapsuleEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCapsuleEnd_Tpl =
            v8::FunctionTemplate::New(isolate, GetCapsuleEnd, v8::Local<v8::Value>(), GetCapsuleEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCapsuleEnd").ToLocalChecked(), GetCapsuleEnd_Tpl);
        v8::Local<v8::Signature> GetCapsuleRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCapsuleRadius_Tpl =
            v8::FunctionTemplate::New(isolate, GetCapsuleRadius, v8::Local<v8::Value>(), GetCapsuleRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCapsuleRadius").ToLocalChecked(), GetCapsuleRadius_Tpl);
        v8::Local<v8::Signature> SetBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetBox_Tpl =
            v8::FunctionTemplate::New(isolate, SetBox, v8::Local<v8::Value>(), SetBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setBox").ToLocalChecked(), SetBox_Tpl);
        v8::Local<v8::Signature> AddBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddBox_Tpl =
            v8::FunctionTemplate::New(isolate, AddBox, v8::Local<v8::Value>(), AddBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addBox").ToLocalChecked(), AddBox_Tpl);
        v8::Local<v8::Signature> ClearShapes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearShapes_Tpl =
            v8::FunctionTemplate::New(isolate, ClearShapes, v8::Local<v8::Value>(), ClearShapes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearShapes").ToLocalChecked(), ClearShapes_Tpl);
        v8::Local<v8::Signature> UseOwnerPhysics_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UseOwnerPhysics_Tpl =
            v8::FunctionTemplate::New(isolate, UseOwnerPhysics, v8::Local<v8::Value>(), UseOwnerPhysics_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "useOwnerPhysics").ToLocalChecked(), UseOwnerPhysics_Tpl);
        v8::Local<v8::Signature> SetPhysicsBody_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPhysicsBody_Tpl =
            v8::FunctionTemplate::New(isolate, SetPhysicsBody, v8::Local<v8::Value>(), SetPhysicsBody_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPhysicsBody").ToLocalChecked(), SetPhysicsBody_Tpl);
        v8::Local<v8::Signature> GetBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetBounds, v8::Local<v8::Value>(), GetBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBounds").ToLocalChecked(), GetBounds_Tpl);
        v8::Local<v8::Signature> Contains_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Contains_Tpl =
            v8::FunctionTemplate::New(isolate, Contains, v8::Local<v8::Value>(), Contains_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "contains").ToLocalChecked(), Contains_Tpl);
        v8::Local<v8::Signature> Overlaps_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Overlaps_Tpl =
            v8::FunctionTemplate::New(isolate, Overlaps, v8::Local<v8::Value>(), Overlaps_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "overlaps").ToLocalChecked(), Overlaps_Tpl);
        v8::Local<v8::Signature> RemoveShape_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveShape_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveShape, v8::Local<v8::Value>(), RemoveShape_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeShape").ToLocalChecked(), RemoveShape_Tpl);
        v8::Local<v8::Signature> GetShapeId_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetShapeId_Tpl =
            v8::FunctionTemplate::New(isolate, GetShapeId, v8::Local<v8::Value>(), GetShapeId_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getShapeId").ToLocalChecked(), GetShapeId_Tpl);
        v8::Local<v8::Signature> GetContactError_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetContactError_Tpl =
            v8::FunctionTemplate::New(isolate, GetContactError, v8::Local<v8::Value>(), GetContactError_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getContactError").ToLocalChecked(), GetContactError_Tpl);
        v8::Local<v8::Signature> AddPolygon_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddPolygon_Tpl =
            v8::FunctionTemplate::New(isolate, AddPolygon, v8::Local<v8::Value>(), AddPolygon_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addPolygon").ToLocalChecked(), AddPolygon_Tpl);
        v8::Local<v8::Signature> SetPolygon_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPolygon_Tpl =
            v8::FunctionTemplate::New(isolate, SetPolygon, v8::Local<v8::Value>(), SetPolygon_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPolygon").ToLocalChecked(), SetPolygon_Tpl);
        v8::Local<v8::Signature> SetImageMask_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetImageMask_Tpl =
            v8::FunctionTemplate::New(isolate, SetImageMask, v8::Local<v8::Value>(), SetImageMask_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setImageMask").ToLocalChecked(), SetImageMask_Tpl);
        v8::Local<v8::Signature> AddImageMask_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddImageMask_Tpl =
            v8::FunctionTemplate::New(isolate, AddImageMask, v8::Local<v8::Value>(), AddImageMask_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addImageMask").ToLocalChecked(), AddImageMask_Tpl);
        v8::Local<v8::Signature> GetGeometrySource_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGeometrySource_Tpl =
            v8::FunctionTemplate::New(isolate, GetGeometrySource, v8::Local<v8::Value>(), GetGeometrySource_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGeometrySource").ToLocalChecked(), GetGeometrySource_Tpl);
        v8::Local<v8::Signature> IsSourceShape_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsSourceShape_Tpl =
            v8::FunctionTemplate::New(isolate, IsSourceShape, v8::Local<v8::Value>(), IsSourceShape_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isSourceShape").ToLocalChecked(), IsSourceShape_Tpl);
        v8::Local<v8::Signature> GetShapeName_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetShapeName_Tpl =
            v8::FunctionTemplate::New(isolate, GetShapeName, v8::Local<v8::Value>(), GetShapeName_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getShapeName").ToLocalChecked(), GetShapeName_Tpl);
        v8::Local<v8::Signature> GetShapeType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetShapeType_Tpl =
            v8::FunctionTemplate::New(isolate, GetShapeType, v8::Local<v8::Value>(), GetShapeType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getShapeType").ToLocalChecked(), GetShapeType_Tpl);
        v8::Local<v8::Signature> GetCircleRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCircleRadius_Tpl =
            v8::FunctionTemplate::New(isolate, GetCircleRadius, v8::Local<v8::Value>(), GetCircleRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCircleRadius").ToLocalChecked(), GetCircleRadius_Tpl);
        v8::Local<v8::Signature> SetContactHandler_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetContactHandler_Tpl =
            v8::FunctionTemplate::New(isolate, SetContactHandler, v8::Local<v8::Value>(), SetContactHandler_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setContactHandler").ToLocalChecked(), SetContactHandler_Tpl);
        v8::Local<v8::Signature> SetCollisionFilter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollisionFilter_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollisionFilter, v8::Local<v8::Value>(), SetCollisionFilter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCollisionFilter").ToLocalChecked(), SetCollisionFilter_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }
#undef COLLIDER_SAVE_WEAK

    void ColliderWrap::IsPresent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isPresent()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::IsAttached(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isAttached()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::IsEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isEnabled()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::IsSensor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isSensor()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetId(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getId()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetCategory(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getCategory()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetCollisionMask(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getCollisionMask()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetGroup(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getGroup()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetShapeCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getShapeCount()) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""value"")");
                return;
            }
            bool value = args[1 -1]->BooleanValue(isolate); self->setEnabled(value);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetSensor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""value"")");
                return;
            }
            bool value = args[1 -1]->BooleanValue(isolate); self->setSensor(value);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetCategory(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned 32-bit integer";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->setCategory(uint32_t(value));
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetCollisionMask(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned 32-bit integer";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->setCollisionMask(uint32_t(value));
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetGroup(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned 32-bit integer";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->setGroup(uint32_t(value));
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetPhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&self->getPhysicsBody(); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mPhysicsBodyScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsBodyWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsBodyScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetCircle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radius"")");
                return;
            }
            double radius = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); pdg::Point center;
            if (args.Length() < 2)
            {
                center = Point();
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[2 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                    return;
                }
            };
            self->setCircle(radius,center);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::AddCircle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radius"")");
                return;
            }
            double radius = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); pdg::Point center;
            if (args.Length() < 2)
            {
                center = Point();
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[2 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                    return;
                }
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->addCircle(radius,center)) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetCapsule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 3)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 3);
                return;
            }; pdg::Point start;
            auto start_isPoint = v8_ValueIsPoint(isolate, args[1 -1], start);
            if (!start_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*start_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }; pdg::Point end;
            auto end_isPoint = v8_ValueIsPoint(isolate, args[2 -1], end);
            if (!end_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*end_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                return;
            };
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""radius"")");
                return;
            }
            double radius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setCapsule(start,end,radius);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::AddCapsule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 3)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 3);
                return;
            }; pdg::Point start;
            auto start_isPoint = v8_ValueIsPoint(isolate, args[1 -1], start);
            if (!start_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*start_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }; pdg::Point end;
            auto end_isPoint = v8_ValueIsPoint(isolate, args[2 -1], end);
            if (!end_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*end_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                return;
            };
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""radius"")");
                return;
            }
            double radius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->addCapsule(start,end,radius)) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetCapsuleStart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned shape ID";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto result=self->getCapsuleStart(uint32_t(value)); { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return; };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetCapsuleEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned shape ID";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto result=self->getCapsuleEnd(uint32_t(value)); { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return; };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetCapsuleRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned shape ID";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->getCapsuleRadius(uint32_t(value))) ); return; };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; pdg::Rect bounds;
            auto bounds_isRect = v8_ValueIsRect(isolate, args[1 -1], bounds);
            if (!bounds_isRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*bounds_isRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
                return;
            };
            self->setBox(bounds);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::AddBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; pdg::Rect bounds;
            auto bounds_isRect = v8_ValueIsRect(isolate, args[1 -1], bounds);
            if (!bounds_isRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*bounds_isRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->addBox(bounds)) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::ClearShapes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->clearShapes();
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::UseOwnerPhysics(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->useOwnerPhysics();
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetPhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if(!COLLISION_ARGUMENT_IS(args[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a PhysicsBody";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            REQUIRE_CPP_OBJECT_ARG(1,body,PhysicsBody); self->setPhysicsBody(*body);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto bounds=self->getBounds();
            {
                args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, bounds) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::Contains(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; pdg::Point point;
            auto point_isPoint = v8_ValueIsPoint(isolate, args[1 -1], point);
            if (!point_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*point_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->contains(point)) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::Overlaps(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if(!COLLISION_ARGUMENT_IS(args[0],false))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Collider";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            REQUIRE_CPP_OBJECT_ARG(1,other,Collider);
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->overlaps(*other)) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::RemoveShape(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned 32-bit integer";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->removeShape(uint32_t(id))) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetShapeId(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned 32-bit integer";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getShapeId(uint32_t(id))) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetContactError(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, self->getContactError().c_str()).ToLocalChecked() ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::AddPolygon(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; std::vector<Point> points;
#ifdef PDG_USING_JAVASCRIPT_CORE
            if(!JSValueIsArray(ctx,args[0]))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an array of Points";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto array=args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto lengthName=JSStringCreateWithUTF8CString("length");
            auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
            const double length=lengthValue->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if(length<3||length>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected 3 to 4096 vertices";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            for(unsigned i=0;i<unsigned(length);++i)
            {
                auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = v8_ValueIsPoint(isolate, value, point); if (!isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected a Point vertex";
                    isolate->ThrowException( v8::Exception::TypeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                points.push_back(point);
            }
#else
            if(!args[0]->IsArray())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an array of Points";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto array=args[0].As<v8::Array>();
            if(array->Length()<3||array->Length()>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected 3 to 4096 vertices";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            for(unsigned i=0;i<array->Length();++i)
            {
                v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = v8_ValueIsPoint(isolate, value, point); if (!isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected a Point vertex";
                    isolate->ThrowException( v8::Exception::TypeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                points.push_back(point);
            }
#endif
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->addPolygon(points)) ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetPolygon(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; std::vector<Point> points;
#ifdef PDG_USING_JAVASCRIPT_CORE
            if(!JSValueIsArray(ctx,args[0]))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an array of Points";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto array=args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto lengthName=JSStringCreateWithUTF8CString("length");
            auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
            const double length=lengthValue->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if(length<3||length>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected 3 to 4096 vertices";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            for(unsigned i=0;i<unsigned(length);++i)
            {
                auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = v8_ValueIsPoint(isolate, value, point); if (!isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected a Point vertex";
                    isolate->ThrowException( v8::Exception::TypeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                points.push_back(point);
            }
#else
            if(!args[0]->IsArray())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an array of Points";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto array=args[0].As<v8::Array>();
            if(array->Length()<3||array->Length()>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected 3 to 4096 vertices";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            for(unsigned i=0;i<array->Length();++i)
            {
                v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = v8_ValueIsPoint(isolate, value, point); if (!isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected a Point vertex";
                    isolate->ThrowException( v8::Exception::TypeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                points.push_back(point);
            }
#endif
            self->setPolygon(points); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    ; ; ; ;
    ; ; ; ;
    ; ;
    struct ColliderScriptCallback
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSGlobalContextRef context;
        JSObjectRef function;
        ColliderScriptCallback(JSContextRef ctx, JSObjectRef callback)
            : context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))),function(callback) { JSValueProtect(context,function); }
        ~ColliderScriptCallback() { JSValueUnprotect(context,function);JSGlobalContextRelease(context); }
#else
        v8::Isolate* isolate;
        v8::Global<v8::Context> context;
        v8::Global<v8::Function> function;
        ColliderScriptCallback(v8::Isolate* engine,v8::Local<v8::Function> callback)
            : isolate(engine),context(engine,engine->GetCurrentContext()),function(engine,callback) {}
#endif
        bool invoke(const Collider& a,const Collider& b,const ColliderContact* contact)
        {
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSContextRef ctx=context;JSValueRef error=nullptr;JSValueRef* exception=&error;
            auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj?c->mColliderScriptObj:Collider_newFromCpp(ctx,c); };
            auto event=JSObjectMake(ctx,nullptr,nullptr);
#else
            v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
            auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj.IsEmpty()?ColliderWrap::NewFromCpp(isolate,c):v8::Local<v8::Object>::New(isolate,c->mColliderScriptObj); };
            auto event=v8::Object::New(isolate);
#endif
            v8::Local<v8::Value> argv[2]={object(a),object(b)};
            if(contact)
            {
                Point point=contact->point;Vector normal=contact->normal,impulse=contact->impulse;
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collider").ToLocalChecked(), argv[0]).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "other").ToLocalChecked(), argv[1]).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "shape").ToLocalChecked(), v8::Number::New(isolate, contact->shape)).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "otherShape").ToLocalChecked(), v8::Number::New(isolate, contact->otherShape)).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "phase").ToLocalChecked(), v8::Number::New(isolate, contact->phase)).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "penetration").ToLocalChecked(), v8::Number::New(isolate, contact->penetration)).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "point").ToLocalChecked(), v8_MakeJavascriptPoint(isolate, point)).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "normal").ToLocalChecked(), v8_MakeJavascriptVector(isolate, normal)).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "impulse").ToLocalChecked(), v8_MakeJavascriptVector(isolate, impulse)).ToChecked();
                (void)event->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "sensor").ToLocalChecked(), v8::Boolean::New(isolate, contact->sensor)).ToChecked();
                argv[0]=event;
            }
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto result=JSObjectCallAsFunction(ctx,function,nullptr,contact?1:2,argv,exception);
            if(error) throw std::runtime_error("Collider callback failed");
            if(!contact&&!JSValueIsBoolean(ctx,result)) throw std::runtime_error("Collision filter must return a boolean");
            return contact || JSValueToBoolean(ctx,result);
#else
            v8::Local<v8::Value> result;
            if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),contact?1:2,argv).ToLocal(&result))
            {
                v8::String::Utf8Value message(isolate,catcher.Exception());
                throw std::runtime_error(*message?*message:"Collider callback failed");
            }
            if(!contact&&!result->IsBoolean()) throw std::runtime_error("Collision filter must return a boolean");
            return contact || result->BooleanValue(isolate);
#endif
        }
    };

    void ColliderWrap::SetContactHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if(args[0]->IsNull())
            {
                self->setContactHandler(
                {
                }
                );
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
                return;
            }
            v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
#else
            auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
#endif
            self->setContactHandler([callback](const ColliderContact& c)
            {
                callback->invoke(*c.collider,*c.other,&c);
            }
            );
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetCollisionFilter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if(args[0]->IsNull())
            {
                self->setCollisionFilter(
                {
                }
                );
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
                return;
            }
            v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
#else
            auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
#endif
            self->setCollisionFilter([callback](const Collider& a,const Collider& b)
            {
                return callback->invoke(a,b,nullptr);
            }
            );
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetGeometrySource(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Integer::New(isolate, self->getGeometrySource()) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::IsSourceShape(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned shape ID";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto id=uint32_t(value); { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isSourceShape(id)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetShapeName(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned shape ID";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto id=uint32_t(value); auto name=self->getShapeName(id); { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, name.c_str()).ToLocalChecked() ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetShapeType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned shape ID";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto id=uint32_t(value); { args.GetReturnValue().Set( v8::Integer::New(isolate, self->getShapeType(id)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetCircleRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an unsigned shape ID";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto id=uint32_t(value); { args.GetReturnValue().Set( v8::Number::New(isolate, self->getCircleRadius(id)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetImageMask(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            }; REQUIRE_CPP_OBJECT_ARG(1,image,Image); pdg::Rect bounds;
            auto bounds_isRect = v8_ValueIsRect(isolate, args[2 -1], bounds);
            if (!bounds_isRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*bounds_isRect)
            {
                v8_ThrowArgTypeException(isolate, 2, "Rect", *args[2 -1]);
                return;
            };
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""threshold"")");
                return;
            }
            double threshold = (args.Length()<3) ? 128 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer alpha threshold from 1 to 255";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->setImageMask(*image,bounds,threshold);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::AddImageMask(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            }; REQUIRE_CPP_OBJECT_ARG(1,image,Image); pdg::Rect bounds;
            auto bounds_isRect = v8_ValueIsRect(isolate, args[2 -1], bounds);
            if (!bounds_isRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*bounds_isRect)
            {
                v8_ThrowArgTypeException(isolate, 2, "Rect", *args[2 -1]);
                return;
            };
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""threshold"")");
                return;
            }
            double threshold = (args.Length()<3) ? 128 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer alpha threshold from 1 to 255";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->addImageMask(*image,bounds,threshold)) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetWantsContactEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wanted"")");
            return;
        }
        bool wanted = args[1 -1]->BooleanValue(isolate); self->setWantsContactEvents(wanted); { args.GetReturnValue().Set( args.This() ); return; };
    }

    void ColliderWrap::GetWantsContactEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Boolean::New(isolate, self->getWantsContactEvents()) ); return;
        };
    }

    void ColliderWrap::SetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setFriction(value);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::SetRestitution(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setRestitution(value);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getFriction()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::GetRestitution(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getRestitution()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ColliderWrap::UseBodyMaterial(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ColliderWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ColliderWrap>(args.This());
        Collider* self = dynamic_cast<Collider*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->useBodyMaterial();
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

}
