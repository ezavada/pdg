// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/physics_constraint.cpp
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

    ;
    ;

#ifdef PDG_USING_JAVASCRIPT_CORE
    PhysicsConstraint* New_PhysicsConstraint(const v8::FunctionCallbackInfo<v8::Value>& args) { return nullptr; }
    static void PhysicsConstraint_finalize(JSObjectRef object)
    {
        auto* body=static_cast<PhysicsConstraint*>(JSObjectGetPrivate(object));
        if(body) {body->mPhysicsConstraintScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
    }
#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj=obj
#else
#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj.Reset(isolate,obj);cppObj->mPhysicsConstraintScriptObj.SetWeak()
    PhysicsConstraintWrap::PhysicsConstraintWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(nullptr) {}
    PhysicsConstraintWrap::~PhysicsConstraintWrap()
    {
        if(cppPtr_) {cppPtr_->mPhysicsConstraintScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
    }
#endif
    static bool s_PhysicsConstraint_InNewFromCpp = false;

    void PhysicsConstraintWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_PhysicsConstraint_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "PhysicsConstraint" " cannot be instantiated with 'new'. Use the factory function: pdg." "PhysicsBody.createPinJoint and other constraint factories" "()"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        PhysicsConstraintWrap* objWrapper = new PhysicsConstraintWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Local<v8::Object> PhysicsConstraintWrap::NewFromCpp(v8::Isolate* isolate, PhysicsConstraint* cppObj)
    {
        s_PhysicsConstraint_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_PhysicsConstraint_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_PhysicsConstraint_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(instance);
        {
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj);cppObj->addRef();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_PhysicsConstraint_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> PhysicsConstraintWrap::constructorTpl_;

    void PhysicsConstraintWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "PhysicsConstraint").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> IsActive_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsActive_Tpl =
            v8::FunctionTemplate::New(isolate, IsActive, v8::Local<v8::Value>(), IsActive_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isActive").ToLocalChecked(), IsActive_Tpl);
        v8::Local<v8::Signature> IsBroken_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsBroken_Tpl =
            v8::FunctionTemplate::New(isolate, IsBroken, v8::Local<v8::Value>(), IsBroken_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isBroken").ToLocalChecked(), IsBroken_Tpl);
        v8::Local<v8::Signature> GetCollideBodies_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollideBodies_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollideBodies, v8::Local<v8::Value>(), GetCollideBodies_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCollideBodies").ToLocalChecked(), GetCollideBodies_Tpl);
        v8::Local<v8::Signature> GetType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetType_Tpl =
            v8::FunctionTemplate::New(isolate, GetType, v8::Local<v8::Value>(), GetType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getType").ToLocalChecked(), GetType_Tpl);
        v8::Local<v8::Signature> GetMaxForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMaxForce_Tpl =
            v8::FunctionTemplate::New(isolate, GetMaxForce, v8::Local<v8::Value>(), GetMaxForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMaxForce").ToLocalChecked(), GetMaxForce_Tpl);
        v8::Local<v8::Signature> GetBreakForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBreakForce_Tpl =
            v8::FunctionTemplate::New(isolate, GetBreakForce, v8::Local<v8::Value>(), GetBreakForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBreakForce").ToLocalChecked(), GetBreakForce_Tpl);
        v8::Local<v8::Signature> GetImpulse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetImpulse_Tpl =
            v8::FunctionTemplate::New(isolate, GetImpulse, v8::Local<v8::Value>(), GetImpulse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getImpulse").ToLocalChecked(), GetImpulse_Tpl);
        v8::Local<v8::Signature> GetForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetForce_Tpl =
            v8::FunctionTemplate::New(isolate, GetForce, v8::Local<v8::Value>(), GetForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getForce").ToLocalChecked(), GetForce_Tpl);
        v8::Local<v8::Signature> SetCollideBodies_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollideBodies_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollideBodies, v8::Local<v8::Value>(), SetCollideBodies_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCollideBodies").ToLocalChecked(), SetCollideBodies_Tpl);
        v8::Local<v8::Signature> SetMaxForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMaxForce_Tpl =
            v8::FunctionTemplate::New(isolate, SetMaxForce, v8::Local<v8::Value>(), SetMaxForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMaxForce").ToLocalChecked(), SetMaxForce_Tpl);
        v8::Local<v8::Signature> SetBreakForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetBreakForce_Tpl =
            v8::FunctionTemplate::New(isolate, SetBreakForce, v8::Local<v8::Value>(), SetBreakForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setBreakForce").ToLocalChecked(), SetBreakForce_Tpl);
        v8::Local<v8::Signature> GetBodyA_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBodyA_Tpl =
            v8::FunctionTemplate::New(isolate, GetBodyA, v8::Local<v8::Value>(), GetBodyA_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBodyA").ToLocalChecked(), GetBodyA_Tpl);
        v8::Local<v8::Signature> GetBodyB_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBodyB_Tpl =
            v8::FunctionTemplate::New(isolate, GetBodyB, v8::Local<v8::Value>(), GetBodyB_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBodyB").ToLocalChecked(), GetBodyB_Tpl);
        v8::Local<v8::Signature> GetAnchorA_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnchorA_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnchorA, v8::Local<v8::Value>(), GetAnchorA_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnchorA").ToLocalChecked(), GetAnchorA_Tpl);
        v8::Local<v8::Signature> GetAnchorB_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnchorB_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnchorB, v8::Local<v8::Value>(), GetAnchorB_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnchorB").ToLocalChecked(), GetAnchorB_Tpl);
        v8::Local<v8::Signature> SetAnchorA_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnchorA_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnchorA, v8::Local<v8::Value>(), SetAnchorA_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnchorA").ToLocalChecked(), SetAnchorA_Tpl);
        v8::Local<v8::Signature> SetAnchorB_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnchorB_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnchorB, v8::Local<v8::Value>(), SetAnchorB_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnchorB").ToLocalChecked(), SetAnchorB_Tpl);
        v8::Local<v8::Signature> SetAnchors_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnchors_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnchors, v8::Local<v8::Value>(), SetAnchors_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnchors").ToLocalChecked(), SetAnchors_Tpl);
        v8::Local<v8::Signature> GetGrooveStart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGrooveStart_Tpl =
            v8::FunctionTemplate::New(isolate, GetGrooveStart, v8::Local<v8::Value>(), GetGrooveStart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGrooveStart").ToLocalChecked(), GetGrooveStart_Tpl);
        v8::Local<v8::Signature> GetGrooveEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGrooveEnd_Tpl =
            v8::FunctionTemplate::New(isolate, GetGrooveEnd, v8::Local<v8::Value>(), GetGrooveEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGrooveEnd").ToLocalChecked(), GetGrooveEnd_Tpl);
        v8::Local<v8::Signature> SetGroove_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGroove_Tpl =
            v8::FunctionTemplate::New(isolate, SetGroove, v8::Local<v8::Value>(), SetGroove_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setGroove").ToLocalChecked(), SetGroove_Tpl);
        v8::Local<v8::Signature> GetMinAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMinAngle_Tpl =
            v8::FunctionTemplate::New(isolate, GetMinAngle, v8::Local<v8::Value>(), GetMinAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMinAngle").ToLocalChecked(), GetMinAngle_Tpl);
        v8::Local<v8::Signature> GetMaxAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMaxAngle_Tpl =
            v8::FunctionTemplate::New(isolate, GetMaxAngle, v8::Local<v8::Value>(), GetMaxAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMaxAngle").ToLocalChecked(), GetMaxAngle_Tpl);
        v8::Local<v8::Signature> SetAngleLimits_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAngleLimits_Tpl =
            v8::FunctionTemplate::New(isolate, SetAngleLimits, v8::Local<v8::Value>(), SetAngleLimits_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAngleLimits").ToLocalChecked(), SetAngleLimits_Tpl);
        v8::Local<v8::Signature> Disconnect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Disconnect_Tpl =
            v8::FunctionTemplate::New(isolate, Disconnect, v8::Local<v8::Value>(), Disconnect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disconnect").ToLocalChecked(), Disconnect_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }
#undef PHYSICSCONSTRAINT_SAVE_WEAK

    void PhysicsConstraintWrap::IsActive(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isActive()) ); return;
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

    void PhysicsConstraintWrap::IsBroken(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isBroken()) ); return;
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

    void PhysicsConstraintWrap::GetCollideBodies(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->getCollideBodies()) ); return;
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

    void PhysicsConstraintWrap::GetType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getType()) ); return;
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

    void PhysicsConstraintWrap::GetMaxForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getMaxForce()) ); return;
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

    void PhysicsConstraintWrap::GetBreakForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getBreakForce()) ); return;
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

    void PhysicsConstraintWrap::GetImpulse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getImpulse()) ); return;
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

    void PhysicsConstraintWrap::GetForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getForce()) ); return;
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

    void PhysicsConstraintWrap::SetCollideBodies(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

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
            bool value = args[1 -1]->BooleanValue(isolate); self->setCollideBodies(value);
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

    void PhysicsConstraintWrap::SetMaxForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setMaxForce(value);
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

    void PhysicsConstraintWrap::SetBreakForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setBreakForce(value);
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

    void PhysicsConstraintWrap::GetBodyA(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&self->getBodyA(); if (!result)
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

    void PhysicsConstraintWrap::GetBodyB(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&self->getBodyB(); if (!result)
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

#ifdef PDG_USING_JAVASCRIPT_CORE
#define CONSTRAINT_VALUE_MISSING(value) (!(value) || (exception && *exception))
#else
#define CONSTRAINT_VALUE_MISSING(value) ((value).IsEmpty())
#endif

    void PhysicsConstraintWrap::GetAnchorA(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto result=self->getAnchorA();
            {
                args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return;
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

    void PhysicsConstraintWrap::GetAnchorB(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto result=self->getAnchorB();
            {
                args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return;
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

    void PhysicsConstraintWrap::SetAnchorA(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if(!args[1 -1]->IsObject())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Point";
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
            auto anchor_object=args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto anchor_x=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = anchor_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(anchor_x))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto anchor_y=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = anchor_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(anchor_y))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if(!anchor_x->IsNumber() || !anchor_y->IsNumber() || !std::isfinite(anchor_x->NumberValue(isolate->GetCurrentContext()).ToChecked()) || !std::isfinite(anchor_y->NumberValue(isolate->GetCurrentContext()).ToChecked()))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected finite Point coordinates";
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
            pdg::Point anchor(anchor_x->NumberValue(isolate->GetCurrentContext()).ToChecked(),anchor_y->NumberValue(isolate->GetCurrentContext()).ToChecked()); self->setAnchorA(anchor);
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

    void PhysicsConstraintWrap::SetAnchorB(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if(!args[1 -1]->IsObject())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Point";
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
            auto anchor_object=args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto anchor_x=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = anchor_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(anchor_x))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto anchor_y=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = anchor_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(anchor_y))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if(!anchor_x->IsNumber() || !anchor_y->IsNumber() || !std::isfinite(anchor_x->NumberValue(isolate->GetCurrentContext()).ToChecked()) || !std::isfinite(anchor_y->NumberValue(isolate->GetCurrentContext()).ToChecked()))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected finite Point coordinates";
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
            pdg::Point anchor(anchor_x->NumberValue(isolate->GetCurrentContext()).ToChecked(),anchor_y->NumberValue(isolate->GetCurrentContext()).ToChecked()); self->setAnchorB(anchor);
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

    void PhysicsConstraintWrap::SetAnchors(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            };
            if(!args[1 -1]->IsObject())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Point";
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
            auto a_object=args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto a_x=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = a_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(a_x))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto a_y=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = a_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(a_y))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if(!a_x->IsNumber() || !a_y->IsNumber() || !std::isfinite(a_x->NumberValue(isolate->GetCurrentContext()).ToChecked()) || !std::isfinite(a_y->NumberValue(isolate->GetCurrentContext()).ToChecked()))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected finite Point coordinates";
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
            pdg::Point a(a_x->NumberValue(isolate->GetCurrentContext()).ToChecked(),a_y->NumberValue(isolate->GetCurrentContext()).ToChecked()); if(!args[2 -1]->IsObject())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Point";
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
            auto b_object=args[2 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto b_x=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = b_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(b_x))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto b_y=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = b_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(b_y))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if(!b_x->IsNumber() || !b_y->IsNumber() || !std::isfinite(b_x->NumberValue(isolate->GetCurrentContext()).ToChecked()) || !std::isfinite(b_y->NumberValue(isolate->GetCurrentContext()).ToChecked()))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected finite Point coordinates";
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
            pdg::Point b(b_x->NumberValue(isolate->GetCurrentContext()).ToChecked(),b_y->NumberValue(isolate->GetCurrentContext()).ToChecked()); self->setAnchors(a,b);
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

    void PhysicsConstraintWrap::GetGrooveStart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto result=self->getGrooveStart();
            {
                args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return;
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

    void PhysicsConstraintWrap::GetGrooveEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto result=self->getGrooveEnd();
            {
                args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return;
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

    void PhysicsConstraintWrap::SetGroove(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            };
            if(!args[1 -1]->IsObject())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Point";
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
            auto a_object=args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto a_x=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = a_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(a_x))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto a_y=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = a_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(a_y))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if(!a_x->IsNumber() || !a_y->IsNumber() || !std::isfinite(a_x->NumberValue(isolate->GetCurrentContext()).ToChecked()) || !std::isfinite(a_y->NumberValue(isolate->GetCurrentContext()).ToChecked()))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected finite Point coordinates";
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
            pdg::Point a(a_x->NumberValue(isolate->GetCurrentContext()).ToChecked(),a_y->NumberValue(isolate->GetCurrentContext()).ToChecked()); if(!args[2 -1]->IsObject())
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Point";
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
            auto b_object=args[2 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked(); auto b_x=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = b_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(b_x))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto b_y=([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = b_object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }
            ()); if(CONSTRAINT_VALUE_MISSING(b_y))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if(!b_x->IsNumber() || !b_y->IsNumber() || !std::isfinite(b_x->NumberValue(isolate->GetCurrentContext()).ToChecked()) || !std::isfinite(b_y->NumberValue(isolate->GetCurrentContext()).ToChecked()))
            {
                std::ostringstream excpt_;
                excpt_ << "Expected finite Point coordinates";
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
            pdg::Point b(b_x->NumberValue(isolate->GetCurrentContext()).ToChecked(),b_y->NumberValue(isolate->GetCurrentContext()).ToChecked()); self->setGroove(a,b);
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

#undef CONSTRAINT_VALUE_MISSING

    void PhysicsConstraintWrap::GetMinAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getMinAngle()) ); return;
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

    void PhysicsConstraintWrap::GetMaxAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getMaxAngle()) ); return;
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

    void PhysicsConstraintWrap::SetAngleLimits(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""lo"")");
                return;
            }
            double lo = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""hi"")");
                return;
            }
            double hi = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setAngleLimits(lo,hi);
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

    void PhysicsConstraintWrap::Disconnect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        PhysicsConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PhysicsConstraintWrap>(args.This());
        PhysicsConstraint* self = dynamic_cast<PhysicsConstraint*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->disconnect(); args.GetReturnValue().SetUndefined();
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
