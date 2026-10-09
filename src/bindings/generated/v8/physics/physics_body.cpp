// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/physics_body.cpp
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
    PhysicsBody* New_PhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args) { return nullptr; }
    static void PhysicsBody_finalize(JSObjectRef object)
    {
        auto* body=static_cast<PhysicsBody*>(JSObjectGetPrivate(object));
        if(body) {body->mPhysicsBodyScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
    }
#define BODY_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsBodyScriptObj=obj
#else
#define BODY_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsBodyScriptObj.Reset(isolate,obj);cppObj->mPhysicsBodyScriptObj.SetWeak()
    PhysicsBodyWrap::PhysicsBodyWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(nullptr) {}
    PhysicsBodyWrap::~PhysicsBodyWrap()
    {
        if(cppPtr_) {cppPtr_->mPhysicsBodyScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
    }
#endif
    static bool s_PhysicsBody_InNewFromCpp = false;

    void PhysicsBodyWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_PhysicsBody_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "PhysicsBody" " cannot be instantiated with 'new'. Use the factory function: pdg." "Sprite.setupPhysicsBody or Part.setupPhysicsBody" "()"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        PhysicsBodyWrap* objWrapper = new PhysicsBodyWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Local<v8::Object> PhysicsBodyWrap::NewFromCpp(v8::Isolate* isolate, PhysicsBody* cppObj)
    {
        s_PhysicsBody_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_PhysicsBody_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_PhysicsBody_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(instance);
        {
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            BODY_SAVE_WEAK(cppObj,obj);cppObj->addRef();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_PhysicsBody_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> PhysicsBodyWrap::constructorTpl_;

    void PhysicsBodyWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "PhysicsBody").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetConstraintCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetConstraintCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetConstraintCount, v8::Local<v8::Value>(), GetConstraintCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getConstraintCount").ToLocalChecked(), GetConstraintCount_Tpl);
        v8::Local<v8::Signature> CreatePinJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreatePinJoint_Tpl =
            v8::FunctionTemplate::New(isolate, CreatePinJoint, v8::Local<v8::Value>(), CreatePinJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createPinJoint").ToLocalChecked(), CreatePinJoint_Tpl);
        v8::Local<v8::Signature> CreatePivotJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreatePivotJoint_Tpl =
            v8::FunctionTemplate::New(isolate, CreatePivotJoint, v8::Local<v8::Value>(), CreatePivotJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createPivotJoint").ToLocalChecked(), CreatePivotJoint_Tpl);
        v8::Local<v8::Signature> CreateSlideJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateSlideJoint_Tpl =
            v8::FunctionTemplate::New(isolate, CreateSlideJoint, v8::Local<v8::Value>(), CreateSlideJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createSlideJoint").ToLocalChecked(), CreateSlideJoint_Tpl);
        v8::Local<v8::Signature> CreateGrooveJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateGrooveJoint_Tpl =
            v8::FunctionTemplate::New(isolate, CreateGrooveJoint, v8::Local<v8::Value>(), CreateGrooveJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createGrooveJoint").ToLocalChecked(), CreateGrooveJoint_Tpl);
        v8::Local<v8::Signature> CreateSpring_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateSpring_Tpl =
            v8::FunctionTemplate::New(isolate, CreateSpring, v8::Local<v8::Value>(), CreateSpring_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createSpring").ToLocalChecked(), CreateSpring_Tpl);
        v8::Local<v8::Signature> CreateRotarySpring_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateRotarySpring_Tpl =
            v8::FunctionTemplate::New(isolate, CreateRotarySpring, v8::Local<v8::Value>(), CreateRotarySpring_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createRotarySpring").ToLocalChecked(), CreateRotarySpring_Tpl);
        v8::Local<v8::Signature> CreateRotaryLimit_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateRotaryLimit_Tpl =
            v8::FunctionTemplate::New(isolate, CreateRotaryLimit, v8::Local<v8::Value>(), CreateRotaryLimit_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createRotaryLimit").ToLocalChecked(), CreateRotaryLimit_Tpl);
        v8::Local<v8::Signature> CreateRatchet_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateRatchet_Tpl =
            v8::FunctionTemplate::New(isolate, CreateRatchet, v8::Local<v8::Value>(), CreateRatchet_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createRatchet").ToLocalChecked(), CreateRatchet_Tpl);
        v8::Local<v8::Signature> CreateGear_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateGear_Tpl =
            v8::FunctionTemplate::New(isolate, CreateGear, v8::Local<v8::Value>(), CreateGear_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createGear").ToLocalChecked(), CreateGear_Tpl);
        v8::Local<v8::Signature> CreateMotor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateMotor_Tpl =
            v8::FunctionTemplate::New(isolate, CreateMotor, v8::Local<v8::Value>(), CreateMotor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createMotor").ToLocalChecked(), CreateMotor_Tpl);
        v8::Local<v8::Signature> GetConstraint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetConstraint_Tpl =
            v8::FunctionTemplate::New(isolate, GetConstraint, v8::Local<v8::Value>(), GetConstraint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getConstraint").ToLocalChecked(), GetConstraint_Tpl);
        v8::Local<v8::Signature> Disconnect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Disconnect_Tpl =
            v8::FunctionTemplate::New(isolate, Disconnect, v8::Local<v8::Value>(), Disconnect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disconnect").ToLocalChecked(), Disconnect_Tpl);
        v8::Local<v8::Signature> SetDriveTarget_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetDriveTarget_Tpl =
            v8::FunctionTemplate::New(isolate, SetDriveTarget, v8::Local<v8::Value>(), SetDriveTarget_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setDriveTarget").ToLocalChecked(), SetDriveTarget_Tpl);
        v8::Local<v8::Signature> ClearDrive_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearDrive_Tpl =
            v8::FunctionTemplate::New(isolate, ClearDrive, v8::Local<v8::Value>(), ClearDrive_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearDrive").ToLocalChecked(), ClearDrive_Tpl);
        v8::Local<v8::Signature> IsDriveEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsDriveEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, IsDriveEnabled, v8::Local<v8::Value>(), IsDriveEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isDriveEnabled").ToLocalChecked(), IsDriveEnabled_Tpl);
        v8::Local<v8::Signature> GetDriveState_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDriveState_Tpl =
            v8::FunctionTemplate::New(isolate, GetDriveState, v8::Local<v8::Value>(), GetDriveState_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getDriveState").ToLocalChecked(), GetDriveState_Tpl);
        v8::Local<v8::Signature> GetMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetMode, v8::Local<v8::Value>(), GetMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMode").ToLocalChecked(), GetMode_Tpl);
        v8::Local<v8::Signature> SetMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMode_Tpl =
            v8::FunctionTemplate::New(isolate, SetMode, v8::Local<v8::Value>(), SetMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMode").ToLocalChecked(), SetMode_Tpl);
        v8::Local<v8::Signature> GetMass_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMass_Tpl =
            v8::FunctionTemplate::New(isolate, GetMass, v8::Local<v8::Value>(), GetMass_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMass").ToLocalChecked(), GetMass_Tpl);
        v8::Local<v8::Signature> SetMass_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMass_Tpl =
            v8::FunctionTemplate::New(isolate, SetMass, v8::Local<v8::Value>(), SetMass_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMass").ToLocalChecked(), SetMass_Tpl);
        v8::Local<v8::Signature> GetMomentOfInertia_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMomentOfInertia_Tpl =
            v8::FunctionTemplate::New(isolate, GetMomentOfInertia, v8::Local<v8::Value>(), GetMomentOfInertia_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMomentOfInertia").ToLocalChecked(), GetMomentOfInertia_Tpl);
        v8::Local<v8::Signature> SetMomentOfInertia_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMomentOfInertia_Tpl =
            v8::FunctionTemplate::New(isolate, SetMomentOfInertia, v8::Local<v8::Value>(), SetMomentOfInertia_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMomentOfInertia").ToLocalChecked(), SetMomentOfInertia_Tpl);
        v8::Local<v8::Signature> GetLinearDamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLinearDamping_Tpl =
            v8::FunctionTemplate::New(isolate, GetLinearDamping, v8::Local<v8::Value>(), GetLinearDamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLinearDamping").ToLocalChecked(), GetLinearDamping_Tpl);
        v8::Local<v8::Signature> SetLinearDamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLinearDamping_Tpl =
            v8::FunctionTemplate::New(isolate, SetLinearDamping, v8::Local<v8::Value>(), SetLinearDamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setLinearDamping").ToLocalChecked(), SetLinearDamping_Tpl);
        v8::Local<v8::Signature> GetAngularDamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAngularDamping_Tpl =
            v8::FunctionTemplate::New(isolate, GetAngularDamping, v8::Local<v8::Value>(), GetAngularDamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAngularDamping").ToLocalChecked(), GetAngularDamping_Tpl);
        v8::Local<v8::Signature> SetAngularDamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAngularDamping_Tpl =
            v8::FunctionTemplate::New(isolate, SetAngularDamping, v8::Local<v8::Value>(), SetAngularDamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAngularDamping").ToLocalChecked(), SetAngularDamping_Tpl);
        v8::Local<v8::Signature> GetFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFriction_Tpl =
            v8::FunctionTemplate::New(isolate, GetFriction, v8::Local<v8::Value>(), GetFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFriction").ToLocalChecked(), GetFriction_Tpl);
        v8::Local<v8::Signature> SetFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFriction_Tpl =
            v8::FunctionTemplate::New(isolate, SetFriction, v8::Local<v8::Value>(), SetFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFriction").ToLocalChecked(), SetFriction_Tpl);
        v8::Local<v8::Signature> GetRestitution_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRestitution_Tpl =
            v8::FunctionTemplate::New(isolate, GetRestitution, v8::Local<v8::Value>(), GetRestitution_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRestitution").ToLocalChecked(), GetRestitution_Tpl);
        v8::Local<v8::Signature> SetRestitution_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRestitution_Tpl =
            v8::FunctionTemplate::New(isolate, SetRestitution, v8::Local<v8::Value>(), SetRestitution_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setRestitution").ToLocalChecked(), SetRestitution_Tpl);
        v8::Local<v8::Signature> SetBreakAngularSpeed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetBreakAngularSpeed_Tpl =
            v8::FunctionTemplate::New(isolate, SetBreakAngularSpeed, v8::Local<v8::Value>(), SetBreakAngularSpeed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setBreakAngularSpeed").ToLocalChecked(), SetBreakAngularSpeed_Tpl);
        v8::Local<v8::Signature> GetBreakAngularSpeed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBreakAngularSpeed_Tpl =
            v8::FunctionTemplate::New(isolate, GetBreakAngularSpeed, v8::Local<v8::Value>(), GetBreakAngularSpeed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBreakAngularSpeed").ToLocalChecked(), GetBreakAngularSpeed_Tpl);
        v8::Local<v8::Signature> GetBreakAngularSpeedReference_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBreakAngularSpeedReference_Tpl =
            v8::FunctionTemplate::New(isolate, GetBreakAngularSpeedReference, v8::Local<v8::Value>(), GetBreakAngularSpeedReference_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBreakAngularSpeedReference").ToLocalChecked(), GetBreakAngularSpeedReference_Tpl);
        v8::Local<v8::Signature> GetAngularVelocity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAngularVelocity_Tpl =
            v8::FunctionTemplate::New(isolate, GetAngularVelocity, v8::Local<v8::Value>(), GetAngularVelocity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAngularVelocity").ToLocalChecked(), GetAngularVelocity_Tpl);
        v8::Local<v8::Signature> SetAngularVelocity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAngularVelocity_Tpl =
            v8::FunctionTemplate::New(isolate, SetAngularVelocity, v8::Local<v8::Value>(), SetAngularVelocity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAngularVelocity").ToLocalChecked(), SetAngularVelocity_Tpl);
        v8::Local<v8::Signature> GetSpeed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpeed_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpeed, v8::Local<v8::Value>(), GetSpeed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpeed").ToLocalChecked(), GetSpeed_Tpl);
        v8::Local<v8::Signature> SetSpeed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpeed_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpeed, v8::Local<v8::Value>(), SetSpeed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSpeed").ToLocalChecked(), SetSpeed_Tpl);
        v8::Local<v8::Signature> GetSolver_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSolver_Tpl =
            v8::FunctionTemplate::New(isolate, GetSolver, v8::Local<v8::Value>(), GetSolver_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSolver").ToLocalChecked(), GetSolver_Tpl);
        v8::Local<v8::Signature> GetAngularMomentum_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAngularMomentum_Tpl =
            v8::FunctionTemplate::New(isolate, GetAngularMomentum, v8::Local<v8::Value>(), GetAngularMomentum_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAngularMomentum").ToLocalChecked(), GetAngularMomentum_Tpl);
        v8::Local<v8::Signature> GetMovementDirectionInRadians_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMovementDirectionInRadians_Tpl =
            v8::FunctionTemplate::New(isolate, GetMovementDirectionInRadians, v8::Local<v8::Value>(), GetMovementDirectionInRadians_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMovementDirectionInRadians").ToLocalChecked(), GetMovementDirectionInRadians_Tpl);
        v8::Local<v8::Signature> IsPresent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsPresent_Tpl =
            v8::FunctionTemplate::New(isolate, IsPresent, v8::Local<v8::Value>(), IsPresent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isPresent").ToLocalChecked(), IsPresent_Tpl);
        v8::Local<v8::Signature> IsAttached_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAttached_Tpl =
            v8::FunctionTemplate::New(isolate, IsAttached, v8::Local<v8::Value>(), IsAttached_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAttached").ToLocalChecked(), IsAttached_Tpl);
        v8::Local<v8::Signature> GetState_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetState_Tpl =
            v8::FunctionTemplate::New(isolate, GetState, v8::Local<v8::Value>(), GetState_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getState").ToLocalChecked(), GetState_Tpl);
        v8::Local<v8::Signature> GetVelocity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetVelocity_Tpl =
            v8::FunctionTemplate::New(isolate, GetVelocity, v8::Local<v8::Value>(), GetVelocity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getVelocity").ToLocalChecked(), GetVelocity_Tpl);
        v8::Local<v8::Signature> SetVelocity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetVelocity_Tpl =
            v8::FunctionTemplate::New(isolate, SetVelocity, v8::Local<v8::Value>(), SetVelocity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setVelocity").ToLocalChecked(), SetVelocity_Tpl);
        v8::Local<v8::Signature> SetVelocityInRadians_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetVelocityInRadians_Tpl =
            v8::FunctionTemplate::New(isolate, SetVelocityInRadians, v8::Local<v8::Value>(), SetVelocityInRadians_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setVelocityInRadians").ToLocalChecked(), SetVelocityInRadians_Tpl);
        v8::Local<v8::Signature> Teleport_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Teleport_Tpl =
            v8::FunctionTemplate::New(isolate, Teleport, v8::Local<v8::Value>(), Teleport_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "teleport").ToLocalChecked(), Teleport_Tpl);
        v8::Local<v8::Signature> ApplyImpulse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyImpulse_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyImpulse, v8::Local<v8::Value>(), ApplyImpulse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyImpulse").ToLocalChecked(), ApplyImpulse_Tpl);
        v8::Local<v8::Signature> ApplyAngularImpulse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyAngularImpulse_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyAngularImpulse, v8::Local<v8::Value>(), ApplyAngularImpulse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyAngularImpulse").ToLocalChecked(), ApplyAngularImpulse_Tpl);
        v8::Local<v8::Signature> ApplyForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyForce_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyForce, v8::Local<v8::Value>(), ApplyForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyForce").ToLocalChecked(), ApplyForce_Tpl);
        v8::Local<v8::Signature> ApplyTorque_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyTorque_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyTorque, v8::Local<v8::Value>(), ApplyTorque_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyTorque").ToLocalChecked(), ApplyTorque_Tpl);
        v8::Local<v8::Signature> AddContinuousForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddContinuousForce_Tpl =
            v8::FunctionTemplate::New(isolate, AddContinuousForce, v8::Local<v8::Value>(), AddContinuousForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addContinuousForce").ToLocalChecked(), AddContinuousForce_Tpl);
        v8::Local<v8::Signature> AddContinuousTorque_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddContinuousTorque_Tpl =
            v8::FunctionTemplate::New(isolate, AddContinuousTorque, v8::Local<v8::Value>(), AddContinuousTorque_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addContinuousTorque").ToLocalChecked(), AddContinuousTorque_Tpl);
        v8::Local<v8::Signature> RemoveForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveForce_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveForce, v8::Local<v8::Value>(), RemoveForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeForce").ToLocalChecked(), RemoveForce_Tpl);
        v8::Local<v8::Signature> StopAllForces_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopAllForces_Tpl =
            v8::FunctionTemplate::New(isolate, StopAllForces, v8::Local<v8::Value>(), StopAllForces_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopAllForces").ToLocalChecked(), StopAllForces_Tpl);
        v8::Local<v8::Signature> StopMoving_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopMoving_Tpl =
            v8::FunctionTemplate::New(isolate, StopMoving, v8::Local<v8::Value>(), StopMoving_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopMoving").ToLocalChecked(), StopMoving_Tpl);
        v8::Local<v8::Signature> StopSpinning_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopSpinning_Tpl =
            v8::FunctionTemplate::New(isolate, StopSpinning, v8::Local<v8::Value>(), StopSpinning_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopSpinning").ToLocalChecked(), StopSpinning_Tpl);
        v8::Local<v8::Signature> Step_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Step_Tpl =
            v8::FunctionTemplate::New(isolate, Step, v8::Local<v8::Value>(), Step_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "step").ToLocalChecked(), Step_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }
#undef BODY_SAVE_WEAK

    void PhysicsBodyWrap::SetDriveTarget(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4, true);
                return;
            }; pdg::Point position;
            auto position_isPoint = v8_ValueIsPoint(isolate, args[1 -1], position);
            if (!position_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*position_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""radians"")");
                return;
            }
            double radians = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""maxForce"")");
                return;
            }
            double maxForce = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""maxTorque"")");
                return;
            }
            double maxTorque = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 5 && !args[5 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 5, "a number (""frequency"")");
                return;
            }
            double frequency = (args.Length()<5) ? 4.0 : args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if (args.Length() >= 6 && !args[6 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 6, "a number (""dampingRatio"")");
                return;
            }
            double dampingRatio = (args.Length()<6) ? 1.0 : args[6 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 7 && !args[7 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 7, "a number (""direction"")");
                return;
            }
            double direction = (args.Length()<7) ? static_cast<double>(rotationDirection_Shortest) : args[7 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(direction) || direction!=std::floor(direction) || direction<0 || direction>3)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer rotationDirection constant";
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
            self->setDriveTarget(position,radians,maxForce,maxTorque,frequency,dampingRatio,static_cast<int>(direction));
            { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::ClearDrive(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            self->clearDrive();
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

    void PhysicsBodyWrap::IsDriveEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isDriveEnabled()) ); return;
        };
    }

    void PhysicsBodyWrap::GetMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getMode()) ); return;
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

    void PhysicsBodyWrap::SetMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(value) || std::floor(value)!=value || value<1 || value>3)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a physicsBody mode";
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
            self->setMode(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getMass()) ); return;
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

    void PhysicsBodyWrap::SetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setMass(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetMomentOfInertia(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getMomentOfInertia()) ); return;
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

    void PhysicsBodyWrap::SetMomentOfInertia(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setMomentOfInertia(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetLinearDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getLinearDamping()) ); return;
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

    void PhysicsBodyWrap::SetLinearDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setLinearDamping(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetAngularDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getAngularDamping()) ); return;
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

    void PhysicsBodyWrap::SetAngularDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setAngularDamping(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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

    void PhysicsBodyWrap::SetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setFriction(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetRestitution(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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

    void PhysicsBodyWrap::SetRestitution(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setRestitution(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::SetBreakAngularSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (args.Length()>2)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected speed and optional reference body";
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
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""speed"")");
                return;
            }
            double speed = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            PhysicsBody* reference=nullptr;
            if (args.Length()>1 && !args[1]->IsNull() && !args[1]->IsUndefined())
            {
#ifdef PDG_USING_JAVASCRIPT_CORE
                if (!JSValueIsObjectOfClass(ctx,args[1],PhysicsBody_class()))
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected a PhysicsBody reference";
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
#else
                if (!PhysicsBodyWrap::GetTemplate(isolate)->HasInstance(args[1]))
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected a PhysicsBody reference";
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
#endif
                REQUIRE_CPP_OBJECT_ARG(2,body,PhysicsBody); reference=body;
            }
            self->setBreakAngularSpeed(speed,reference); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetBreakAngularSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Number::New(isolate, self->getBreakAngularSpeed()) ); return;
        };
    }

    void PhysicsBodyWrap::GetBreakAngularSpeedReference(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        auto* reference=self->getBreakAngularSpeedReference(); if (!reference)
        {
            args.GetReturnValue().SetNull(); return;
        };
        if (reference->mPhysicsBodyScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PhysicsBodyWrap::NewFromCpp(isolate, reference) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, reference->mPhysicsBodyScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void PhysicsBodyWrap::GetAngularVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getAngularVelocity()) ); return;
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

    void PhysicsBodyWrap::SetAngularVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setAngularVelocity(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getSpeed()) ); return;
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

    void PhysicsBodyWrap::SetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setSpeed(value); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::GetSolver(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getSolver()) ); return;
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

    void PhysicsBodyWrap::GetAngularMomentum(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getAngularMomentum()) ); return;
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

    void PhysicsBodyWrap::GetMovementDirectionInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getMovementDirectionInRadians()) ); return;
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

    void PhysicsBodyWrap::IsPresent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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

    void PhysicsBodyWrap::IsAttached(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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

    void PhysicsBodyWrap::GetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto velocity=self->getVelocity();
            {
                args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, velocity) ); return;
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

    void PhysicsBodyWrap::SetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if(args.Length()==2)
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setVelocity(x,y);
            }
            else
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                }; pdg::Vector velocity;
                auto velocity_isVector = v8_ValueIsVector(isolate, args[1 -1], velocity);
                if (!velocity_isVector.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*velocity_isVector)
                {
                    v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
                    return;
                };
                self->setVelocity(velocity);
            }
            { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::SetVelocityInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""speed"")");
                return;
            }
            double speed = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""direction"")");
                return;
            }
            double direction = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setVelocityInRadians(speed,direction); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::Teleport(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            }; pdg::Point position;
            auto position_isPoint = v8_ValueIsPoint(isolate, args[1 -1], position);
            if (!position_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*position_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""radians"")");
                return;
            }
            double radians = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->teleport(position,radians); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::ApplyImpulse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            }; pdg::Vector impulse;
            auto impulse_isVector = v8_ValueIsVector(isolate, args[1 -1], impulse);
            if (!impulse_isVector.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*impulse_isVector)
            {
                v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
                return;
            };
            if(args.Length()>1)
            {
                pdg::Point worldPoint;
                auto worldPoint_isPoint = v8_ValueIsPoint(isolate, args[2 -1], worldPoint);
                if (!worldPoint_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*worldPoint_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                    return;
                };
                self->applyImpulse(impulse,worldPoint);
            }
            else self->applyImpulse(impulse);
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

    void PhysicsBodyWrap::ApplyAngularImpulse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""impulse"")");
                return;
            }
            double impulse = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->applyAngularImpulse(impulse); { args.GetReturnValue().Set( args.This() ); return; };
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

    void PhysicsBodyWrap::ApplyForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            }; pdg::Vector force;
            auto force_isVector = v8_ValueIsVector(isolate, args[1 -1], force);
            if (!force_isVector.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*force_isVector)
            {
                v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
                return;
            };
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
                return;
            }
            double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""delay"")");
                return;
            }
            double delay = (args.Length()<3) ? 0.0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if(args.Length()>3)
            {
                pdg::Point point;
                auto point_isPoint = v8_ValueIsPoint(isolate, args[4 -1], point);
                if (!point_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*point_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 4, "Point", *args[4 -1]);
                    return;
                };
                {
                    args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->applyForce(force,point,seconds,delay)) ); return;
                };
            }
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->applyForce(force,seconds,delay)) ); return; };
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

    void PhysicsBodyWrap::ApplyTorque(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""torque"")");
                return;
            }
            double torque = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
                return;
            }
            double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""delay"")");
                return;
            }
            double delay = (args.Length()<3) ? 0.0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->applyTorque(torque,seconds,delay)) ); return; };
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

    void PhysicsBodyWrap::AddContinuousForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; pdg::Vector force;
            auto force_isVector = v8_ValueIsVector(isolate, args[1 -1], force);
            if (!force_isVector.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*force_isVector)
            {
                v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->addContinuousForce(force)) ); return;
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

    void PhysicsBodyWrap::AddContinuousTorque(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""torque"")");
                return;
            }
            double torque = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->addContinuousTorque(torque)) ); return; };
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

    void PhysicsBodyWrap::RemoveForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
            double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if(!std::isfinite(id) || id<0 || id>UINT32_MAX || std::floor(id)!=id)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a force ID";
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
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->removeForce(static_cast<uint32>(id))) ); return; };
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

    void PhysicsBodyWrap::StopAllForces(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopAllForces();
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

    void PhysicsBodyWrap::StopMoving(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopMoving();
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

    void PhysicsBodyWrap::StopSpinning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopSpinning();
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

    void PhysicsBodyWrap::Step(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""seconds"")");
                return;
            }
            double seconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if(self->isAttached())
            {
                std::ostringstream excpt_;
                excpt_ << "Owned bodies advance with their Sprite or Part";
                isolate->ThrowException( v8::Exception::Error( ([&]()
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
            self->step(seconds); args.GetReturnValue().SetUndefined();
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
    ;
    ;
    ;
    ;
    ;
    ;

    void PhysicsBodyWrap::GetState(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            }; const auto state=self->getState(); v8::Local<v8::Object> result=v8_ObjectCreateEmpty(isolate, 0);
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, state.x)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, state.y)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rotation").ToLocalChecked(), v8::Number::New(isolate, state.rotation)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "velocityX").ToLocalChecked(), v8::Number::New(isolate, state.velocityX)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "velocityY").ToLocalChecked(), v8::Number::New(isolate, state.velocityY)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "angularVelocity").ToLocalChecked(), v8::Number::New(isolate, state.angularVelocity)).ToChecked();
            { args.GetReturnValue().Set( result ); return; };
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

    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;

    void PhysicsBodyWrap::GetDriveState(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            }; const auto state=self->getDriveState(); v8::Local<v8::Object> result=v8_ObjectCreateEmpty(isolate, 0);
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "enabled").ToLocalChecked(), v8::Boolean::New(isolate, state.enabled)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, state.x)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, state.y)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rotation").ToLocalChecked(), v8::Number::New(isolate, state.rotation)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "maxForce").ToLocalChecked(), v8::Number::New(isolate, state.maxForce)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "maxTorque").ToLocalChecked(), v8::Number::New(isolate, state.maxTorque)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "frequency").ToLocalChecked(), v8::Number::New(isolate, state.frequency)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "dampingRatio").ToLocalChecked(), v8::Number::New(isolate, state.dampingRatio)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "forceX").ToLocalChecked(), v8::Number::New(isolate, state.forceX)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "forceY").ToLocalChecked(), v8::Number::New(isolate, state.forceY)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "torque").ToLocalChecked(), v8::Number::New(isolate, state.torque)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "positionError").ToLocalChecked(), v8::Number::New(isolate, state.positionError)).ToChecked();
            (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rotationError").ToLocalChecked(), v8::Number::New(isolate, state.rotationError)).ToChecked();
            { args.GetReturnValue().Set( result ); return; };
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

    void PhysicsBodyWrap::GetConstraintCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getConstraintCount()) ); return;
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

    void PhysicsBodyWrap::CreatePinJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
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
            } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); pdg::Point anchor;
            if (args.Length() < 2)
            {
                anchor = Point();
            }
            else
            {
                auto anchor_isPoint = v8_ValueIsPoint(isolate, args[2 -1], anchor);
                if (!anchor_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*anchor_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                    return;
                }
            }; pdg::Point otherAnchor;
            if (args.Length() < 3)
            {
                otherAnchor = Point();
            }
            else
            {
                auto otherAnchor_isPoint = v8_ValueIsPoint(isolate, args[3 -1], otherAnchor);
                if (!otherAnchor_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*otherAnchor_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                    return;
                }
            };
            auto* result=&self->createPinJoint(*other,anchor,otherAnchor); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreatePivotJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
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
            } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); pdg::Point anchor;
            if (args.Length() < 2)
            {
                anchor = Point();
            }
            else
            {
                auto anchor_isPoint = v8_ValueIsPoint(isolate, args[2 -1], anchor);
                if (!anchor_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*anchor_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                    return;
                }
            }; pdg::Point otherAnchor;
            if (args.Length() < 3)
            {
                otherAnchor = Point();
            }
            else
            {
                auto otherAnchor_isPoint = v8_ValueIsPoint(isolate, args[3 -1], otherAnchor);
                if (!otherAnchor_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*otherAnchor_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                    return;
                }
            };
            auto* result=&self->createPivotJoint(*other,anchor,otherAnchor); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateSlideJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 5)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 5, true);
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
            } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); pdg::Point anchor;
            auto anchor_isPoint = v8_ValueIsPoint(isolate, args[2 -1], anchor);
            if (!anchor_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*anchor_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                return;
            }; pdg::Point otherAnchor;
            auto otherAnchor_isPoint = v8_ValueIsPoint(isolate, args[3 -1], otherAnchor);
            if (!otherAnchor_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*otherAnchor_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                return;
            };
            if (!args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""minDistance"")");
                return;
            }
            double minDistance = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[5 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 5, "a number (""maxDistance"")");
                return;
            }
            double maxDistance = args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); auto* result=&self->createSlideJoint(*other,anchor,otherAnchor,minDistance,maxDistance); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateGrooveJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4, true);
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
            } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); pdg::Point start;
            auto start_isPoint = v8_ValueIsPoint(isolate, args[2 -1], start);
            if (!start_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*start_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                return;
            }; pdg::Point end;
            auto end_isPoint = v8_ValueIsPoint(isolate, args[3 -1], end);
            if (!end_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*end_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                return;
            }; pdg::Point otherAnchor;
            auto otherAnchor_isPoint = v8_ValueIsPoint(isolate, args[4 -1], otherAnchor);
            if (!otherAnchor_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*otherAnchor_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 4, "Point", *args[4 -1]);
                return;
            };
            auto* result=&self->createGrooveJoint(*other,start,end,otherAnchor); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateSpring(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 6)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 6, true);
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
            } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); pdg::Point anchor;
            auto anchor_isPoint = v8_ValueIsPoint(isolate, args[2 -1], anchor);
            if (!anchor_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*anchor_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                return;
            }; pdg::Point otherAnchor;
            auto otherAnchor_isPoint = v8_ValueIsPoint(isolate, args[3 -1], otherAnchor);
            if (!otherAnchor_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*otherAnchor_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                return;
            };
            if (!args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""restLength"")");
                return;
            }
            double restLength = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[5 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 5, "a number (""stiffness"")");
                return;
            }
            double stiffness = args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[6 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 6, "a number (""damping"")");
                return;
            }
            double damping = args[6 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); auto* result=&self->createSpring(*other,anchor,otherAnchor,restLength,stiffness,damping); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateRotarySpring(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4, true);
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
            REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""restAngle"")");
                return;
            }
            double restAngle = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""stiffness"")");
                return;
            }
            double stiffness = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""damping"")");
                return;
            }
            double damping = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); auto* result=&self->createRotarySpring(*other,restAngle,stiffness,damping); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateRotaryLimit(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 3)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 3, true);
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
            REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""minAngle"")");
                return;
            }
            double minAngle = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""maxAngle"")");
                return;
            }
            double maxAngle = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); auto* result=&self->createRotaryLimit(*other,minAngle,maxAngle); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateRatchet(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
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
            REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""interval"")");
                return;
            }
            double interval = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""phase"")");
                return;
            }
            double phase = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; auto* result=&self->createRatchet(*other,interval,phase); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateGear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
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
            REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""ratio"")");
                return;
            }
            double ratio = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""phase"")");
                return;
            }
            double phase = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; auto* result=&self->createGear(*other,ratio,phase); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::CreateMotor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 3)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 3, true);
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
            REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""radiansPerSecond"")");
                return;
            }
            double radiansPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""maxTorque"")");
                return;
            }
            double maxTorque = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); auto* result=&self->createMotor(*other,radiansPerSecond,maxTorque); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::GetConstraint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
                return;
            }
            double index = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(index)||index<0||index>4294967295.0||index!=std::floor(index))
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
            auto* result=&self->getConstraint(uint32_t(index)); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mPhysicsConstraintScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsConstraintWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsConstraintScriptObj );
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

    void PhysicsBodyWrap::Disconnect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsBodyWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsBodyWrap>(args.This());
        PhysicsBody* self = dynamic_cast<PhysicsBody*>(objWrapper->cppPtr_);

        ;
        try
        {
            if(args.Length()==0||args[0]->IsNull()) self->disconnect(); else
            {
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
                REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); self->disconnect(other);
            }
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

}
