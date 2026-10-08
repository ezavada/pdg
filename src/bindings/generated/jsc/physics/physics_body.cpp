// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/physics_body.cpp
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_script_macros.h
//
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
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
    PhysicsBody* New_PhysicsBody(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return nullptr; }
    static void PhysicsBody_finalize(JSObjectRef object)
    {
        auto* body=static_cast<PhysicsBody*>(JSObjectGetPrivate(object));
        if(body) {body->mPhysicsBodyScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
    }
#define BODY_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsBodyScriptObj=obj
#else
#define BODY_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsBodyScriptObj.Reset(isolate,obj);cppObj->mPhysicsBodyScriptObj.SetWeak()
    PhysicsBodyWrap::PhysicsBodyWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(nullptr) {}
    PhysicsBodyWrap::~PhysicsBodyWrap()
    {
        if(cppPtr_) {cppPtr_->mPhysicsBodyScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
    }
#endif
    static bool s_PhysicsBody_InNewFromCpp = false;

    JSObjectRef PhysicsBody_newFromCpp(JSContextRef ctx, PhysicsBody* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, PhysicsBody_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, PhysicsBody_class());
        BODY_SAVE_WEAK(cppObj,obj);cppObj->addRef();
        return obj;
    }

    JSObjectRef PhysicsBody_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_PhysicsBody_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "PhysicsBody" " cannot be instantiated with \\'new\\'. Use the factory function: pdg." "Sprite.setupPhysicsBody or Part.setupPhysicsBody" "()')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        PhysicsBody* cppObj = New_PhysicsBody(argumentCount, arguments, exception);
        if (exception && *exception) return nullptr;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            std::ostringstream excpt_;
            excpt_ << "throw '" << s_SavedError.str().c_str() << "'";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        };
        if (!cppObj)
        {
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to create C++ native " "PhysicsBody" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, PhysicsBody_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, PhysicsBody_class());
        return obj;
    }

    JSClassRef PhysicsBody_class()
    {

        static JSStaticValue PhysicsBody_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction PhysicsBody_staticFunctions[] =
        {
            { "getConstraintCount", PhysicsBody_GetConstraintCount, kJSPropertyAttributeDontDelete },
            { "createPinJoint", PhysicsBody_CreatePinJoint, kJSPropertyAttributeDontDelete },
            { "createPivotJoint", PhysicsBody_CreatePivotJoint, kJSPropertyAttributeDontDelete },
            { "createSlideJoint", PhysicsBody_CreateSlideJoint, kJSPropertyAttributeDontDelete },
            { "createGrooveJoint", PhysicsBody_CreateGrooveJoint, kJSPropertyAttributeDontDelete },
            { "createSpring", PhysicsBody_CreateSpring, kJSPropertyAttributeDontDelete },
            { "createRotarySpring", PhysicsBody_CreateRotarySpring, kJSPropertyAttributeDontDelete },
            { "createRotaryLimit", PhysicsBody_CreateRotaryLimit, kJSPropertyAttributeDontDelete },
            { "createRatchet", PhysicsBody_CreateRatchet, kJSPropertyAttributeDontDelete },
            { "createGear", PhysicsBody_CreateGear, kJSPropertyAttributeDontDelete },
            { "createMotor", PhysicsBody_CreateMotor, kJSPropertyAttributeDontDelete },
            { "getConstraint", PhysicsBody_GetConstraint, kJSPropertyAttributeDontDelete },
            { "disconnect", PhysicsBody_Disconnect, kJSPropertyAttributeDontDelete },
            { "setDriveTarget", PhysicsBody_SetDriveTarget, kJSPropertyAttributeDontDelete },
            { "clearDrive", PhysicsBody_ClearDrive, kJSPropertyAttributeDontDelete },
            { "isDriveEnabled", PhysicsBody_IsDriveEnabled, kJSPropertyAttributeDontDelete },
            { "getDriveState", PhysicsBody_GetDriveState, kJSPropertyAttributeDontDelete },
            { "getMode", PhysicsBody_GetMode, kJSPropertyAttributeDontDelete },
            { "setMode", PhysicsBody_SetMode, kJSPropertyAttributeDontDelete },
            { "getMass", PhysicsBody_GetMass, kJSPropertyAttributeDontDelete },
            { "setMass", PhysicsBody_SetMass, kJSPropertyAttributeDontDelete },
            { "getMomentOfInertia", PhysicsBody_GetMomentOfInertia, kJSPropertyAttributeDontDelete },
            { "setMomentOfInertia", PhysicsBody_SetMomentOfInertia, kJSPropertyAttributeDontDelete },
            { "getLinearDamping", PhysicsBody_GetLinearDamping, kJSPropertyAttributeDontDelete },
            { "setLinearDamping", PhysicsBody_SetLinearDamping, kJSPropertyAttributeDontDelete },
            { "getAngularDamping", PhysicsBody_GetAngularDamping, kJSPropertyAttributeDontDelete },
            { "setAngularDamping", PhysicsBody_SetAngularDamping, kJSPropertyAttributeDontDelete },
            { "getFriction", PhysicsBody_GetFriction, kJSPropertyAttributeDontDelete },
            { "setFriction", PhysicsBody_SetFriction, kJSPropertyAttributeDontDelete },
            { "getRestitution", PhysicsBody_GetRestitution, kJSPropertyAttributeDontDelete },
            { "setRestitution", PhysicsBody_SetRestitution, kJSPropertyAttributeDontDelete },
            { "setBreakAngularSpeed", PhysicsBody_SetBreakAngularSpeed, kJSPropertyAttributeDontDelete },
            { "getBreakAngularSpeed", PhysicsBody_GetBreakAngularSpeed, kJSPropertyAttributeDontDelete },
            { "getBreakAngularSpeedReference", PhysicsBody_GetBreakAngularSpeedReference, kJSPropertyAttributeDontDelete },
            { "getAngularVelocity", PhysicsBody_GetAngularVelocity, kJSPropertyAttributeDontDelete },
            { "setAngularVelocity", PhysicsBody_SetAngularVelocity, kJSPropertyAttributeDontDelete },
            { "getSpeed", PhysicsBody_GetSpeed, kJSPropertyAttributeDontDelete },
            { "setSpeed", PhysicsBody_SetSpeed, kJSPropertyAttributeDontDelete },
            { "getSolver", PhysicsBody_GetSolver, kJSPropertyAttributeDontDelete },
            { "getAngularMomentum", PhysicsBody_GetAngularMomentum, kJSPropertyAttributeDontDelete },
            { "getMovementDirectionInRadians", PhysicsBody_GetMovementDirectionInRadians, kJSPropertyAttributeDontDelete },
            { "isPresent", PhysicsBody_IsPresent, kJSPropertyAttributeDontDelete },
            { "isAttached", PhysicsBody_IsAttached, kJSPropertyAttributeDontDelete },
            { "getState", PhysicsBody_GetState, kJSPropertyAttributeDontDelete },
            { "getVelocity", PhysicsBody_GetVelocity, kJSPropertyAttributeDontDelete },
            { "setVelocity", PhysicsBody_SetVelocity, kJSPropertyAttributeDontDelete },
            { "setVelocityInRadians", PhysicsBody_SetVelocityInRadians, kJSPropertyAttributeDontDelete },
            { "teleport", PhysicsBody_Teleport, kJSPropertyAttributeDontDelete },
            { "applyImpulse", PhysicsBody_ApplyImpulse, kJSPropertyAttributeDontDelete },
            { "applyAngularImpulse", PhysicsBody_ApplyAngularImpulse, kJSPropertyAttributeDontDelete },
            { "applyForce", PhysicsBody_ApplyForce, kJSPropertyAttributeDontDelete },
            { "applyTorque", PhysicsBody_ApplyTorque, kJSPropertyAttributeDontDelete },
            { "addContinuousForce", PhysicsBody_AddContinuousForce, kJSPropertyAttributeDontDelete },
            { "addContinuousTorque", PhysicsBody_AddContinuousTorque, kJSPropertyAttributeDontDelete },
            { "removeForce", PhysicsBody_RemoveForce, kJSPropertyAttributeDontDelete },
            { "stopAllForces", PhysicsBody_StopAllForces, kJSPropertyAttributeDontDelete },
            { "stopMoving", PhysicsBody_StopMoving, kJSPropertyAttributeDontDelete },
            { "stopSpinning", PhysicsBody_StopSpinning, kJSPropertyAttributeDontDelete },
            { "step", PhysicsBody_Step, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = PhysicsBody_finalize;
            definition.className = "PhysicsBody";
            definition.staticFunctions = PhysicsBody_staticFunctions;
            definition.staticValues = PhysicsBody_staticValues;
            definition.callAsConstructor = PhysicsBody_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
#undef BODY_SAVE_WEAK
    JSValueRef PhysicsBody_SetDriveTarget(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 4)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4, true); pdg::Point position;
            auto position_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], position, exception);
            if (!position_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*position_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""maxForce"")");
            double maxForce = JSValueToNumber(ctx, arguments[3 -1], exception); if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""maxTorque"")");
            double maxTorque = JSValueToNumber(ctx, arguments[4 -1], exception);
            if (argumentCount >= 5 && !JSValueIsNumber(ctx, arguments[5 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""frequency"")");
            double frequency = (argumentCount<5) ? 4.0 : JSValueToNumber(ctx, arguments[5 -1], exception); if (argumentCount >= 6 && !JSValueIsNumber(ctx, arguments[6 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 6, "a number (""dampingRatio"")");
            double dampingRatio = (argumentCount<6) ? 1.0 : JSValueToNumber(ctx, arguments[6 -1], exception);
            if (argumentCount >= 7 && !JSValueIsNumber(ctx, arguments[7 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 7, "a number (""direction"")");
            double direction = (argumentCount<7) ? static_cast<double>(rotationDirection_Shortest) : JSValueToNumber(ctx, arguments[7 -1], exception);
            if (!std::isfinite(direction) || direction!=std::floor(direction) || direction<0 || direction>3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an integer rotationDirection constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->setDriveTarget(position,radians,maxForce,maxTorque,frequency,dampingRatio,static_cast<int>(direction));
            return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_ClearDrive(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try { self->clearDrive(); return thisObject; }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_IsDriveEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isDriveEnabled());
    }
    JSValueRef PhysicsBody_GetMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMode());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value) || std::floor(value)!=value || value<1 || value>3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected a physicsBody mode" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->setMode(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetMass(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMass());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetMass(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setMass(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetMomentOfInertia(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMomentOfInertia());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetMomentOfInertia(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setMomentOfInertia(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetLinearDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getLinearDamping());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetLinearDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setLinearDamping(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetAngularDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getAngularDamping());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetAngularDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setAngularDamping(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetFriction(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getFriction());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetFriction(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setFriction(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetRestitution(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getRestitution());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetRestitution(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setRestitution(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetBreakAngularSpeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount>2)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected speed and optional reference body" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""speed"")");
            double speed = JSValueToNumber(ctx, arguments[1 -1], exception);
            PhysicsBody* reference=nullptr;
            if (argumentCount>1 && !JSValueIsNull(ctx, arguments[1]) && !JSValueIsUndefined(ctx, arguments[1]))
            {
#ifdef PDG_USING_JAVASCRIPT_CORE
                if (!JSValueIsObjectOfClass(ctx,arguments[1],PhysicsBody_class()))
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody reference" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
#else
                if (!PhysicsBodyWrap::GetTemplate(isolate)->HasInstance(arguments[1]))
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody reference" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
#endif
                PhysicsBody* body = 0;
                if (JSValueIsObject(ctx, arguments[2 -1]))
                {
                    JSObjectRef body_ = JSValueToObject(ctx, arguments[2 -1], exception);
                    body = PhysicsBody_getCppObject(body_);
                }
                if (!body)
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""PhysicsBody"" (""body"")"); reference=body;
            }
            self->setBreakAngularSpeed(speed,reference); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetBreakAngularSpeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getBreakAngularSpeed());
    }
    JSValueRef PhysicsBody_GetBreakAngularSpeedReference(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* reference=self->getBreakAngularSpeedReference(); if (!reference) return JSValueMakeNull(ctx);
        if (!reference->mPhysicsBodyScriptObj)
        {
            return PhysicsBody_newFromCpp(ctx, reference);
        }
        else
        {
            return reference->mPhysicsBodyScriptObj;
        };
    }
    JSValueRef PhysicsBody_GetAngularVelocity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getAngularVelocity());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetAngularVelocity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setAngularVelocity(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetSpeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getSpeed());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetSpeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->setSpeed(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetSolver(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getSolver());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetAngularMomentum(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getAngularMomentum());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetMovementDirectionInRadians(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMovementDirectionInRadians());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_IsPresent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isPresent());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_IsAttached(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isAttached());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetVelocity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto velocity=self->getVelocity(); return JSC_VectorToValue(ctx, velocity, exception);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetVelocity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if(argumentCount==2)
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception); self->setVelocity(x,y);
            }
            else
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Vector velocity;
                auto velocity_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], velocity, exception);
                if (!velocity_isVector.has_value()) { return JSValueMakeNull(ctx); }
                if (!*velocity_isVector)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
                };
                self->setVelocity(velocity);
            }
            return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_SetVelocityInRadians(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""speed"")");
            double speed = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""direction"")");
            double direction = JSValueToNumber(ctx, arguments[2 -1], exception); self->setVelocityInRadians(speed,direction); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_Teleport(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); pdg::Point position;
            auto position_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], position, exception);
            if (!position_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*position_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[2 -1], exception); self->teleport(position,radians); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_ApplyImpulse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); pdg::Vector impulse;
            auto impulse_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], impulse, exception);
            if (!impulse_isVector.has_value()) { return JSValueMakeNull(ctx); }
            if (!*impulse_isVector)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
            };
            if(argumentCount>1)
            {
                pdg::Point worldPoint;
                auto worldPoint_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], worldPoint, exception);
                if (!worldPoint_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*worldPoint_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
                };
                self->applyImpulse(impulse,worldPoint);
            } else self->applyImpulse(impulse); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_ApplyAngularImpulse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""impulse"")");
            double impulse = JSValueToNumber(ctx, arguments[1 -1], exception); self->applyAngularImpulse(impulse); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_ApplyForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); pdg::Vector force;
            auto force_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], force, exception);
            if (!force_isVector.has_value()) { return JSValueMakeNull(ctx); }
            if (!*force_isVector)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
            }; if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""delay"")");
            double delay = (argumentCount<3) ? 0.0 : JSValueToNumber(ctx, arguments[3 -1], exception);
            if(argumentCount>3)
            {
                pdg::Point point;
                auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[4 -1], point, exception);
                if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*point_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "Point", arguments[4 -1]);
                };
                return JSValueMakeNumber(ctx, self->applyForce(force,point,seconds,delay));
            }
            return JSValueMakeNumber(ctx, self->applyForce(force,seconds,delay));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_ApplyTorque(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""torque"")");
            double torque = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""delay"")");
            double delay = (argumentCount<3) ? 0.0 : JSValueToNumber(ctx, arguments[3 -1], exception); return JSValueMakeNumber(ctx, self->applyTorque(torque,seconds,delay));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_AddContinuousForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Vector force;
            auto force_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], force, exception);
            if (!force_isVector.has_value()) { return JSValueMakeNull(ctx); }
            if (!*force_isVector)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
            }; return JSValueMakeNumber(ctx, self->addContinuousForce(force));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_AddContinuousTorque(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""torque"")");
            double torque = JSValueToNumber(ctx, arguments[1 -1], exception); return JSValueMakeNumber(ctx, self->addContinuousTorque(torque));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_RemoveForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            double id = JSValueToNumber(ctx, arguments[1 -1], exception);
            if(!std::isfinite(id) || id<0 || id>UINT32_MAX || std::floor(id)!=id)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected a force ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            return JSValueMakeBoolean(ctx, self->removeForce(static_cast<uint32>(id)));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_StopAllForces(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->stopAllForces(); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_StopMoving(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->stopMoving(); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->stopSpinning(); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_Step(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception);
            if(self->isAttached())
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "Error" << "('" << "Error: " << "Owned bodies advance with their Sprite or Part" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->step(seconds); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    static JSStringRef symbol_x = 0;
    static JSStringRef symbol_y = 0;
    static JSStringRef symbol_rotation = 0;
    static JSStringRef symbol_velocityX = 0;
    static JSStringRef symbol_velocityY = 0;
    static JSStringRef symbol_angularVelocity = 0;
    JSValueRef PhysicsBody_GetState(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); const auto state=self->getState(); JSObjectRef result=JSC_ObjectCreateEmpty(ctx, 0);
            JSObjectSetProperty(ctx, result, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), JSValueMakeNumber(ctx, state.x), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), JSValueMakeNumber(ctx, state.y), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_rotation) ? symbol_rotation : symbol_rotation = JSStringCreateWithUTF8CString("rotation")), JSValueMakeNumber(ctx, state.rotation), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_velocityX) ? symbol_velocityX : symbol_velocityX = JSStringCreateWithUTF8CString("velocityX")), JSValueMakeNumber(ctx, state.velocityX), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_velocityY) ? symbol_velocityY : symbol_velocityY = JSStringCreateWithUTF8CString("velocityY")), JSValueMakeNumber(ctx, state.velocityY), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_angularVelocity) ? symbol_angularVelocity : symbol_angularVelocity = JSStringCreateWithUTF8CString("angularVelocity")), JSValueMakeNumber(ctx, state.angularVelocity), kJSPropertyAttributeNone, exception);
            return result;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    static JSStringRef symbol_enabled = 0;
    static JSStringRef symbol_maxForce = 0;
    static JSStringRef symbol_maxTorque = 0;
    static JSStringRef symbol_frequency = 0;
    static JSStringRef symbol_dampingRatio = 0;
    static JSStringRef symbol_forceX = 0;
    static JSStringRef symbol_forceY = 0;
    static JSStringRef symbol_torque = 0;
    static JSStringRef symbol_positionError = 0;
    static JSStringRef symbol_rotationError = 0;
    JSValueRef PhysicsBody_GetDriveState(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); const auto state=self->getDriveState(); JSObjectRef result=JSC_ObjectCreateEmpty(ctx, 0);
            JSObjectSetProperty(ctx, result, ((symbol_enabled) ? symbol_enabled : symbol_enabled = JSStringCreateWithUTF8CString("enabled")), JSValueMakeBoolean(ctx, state.enabled), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), JSValueMakeNumber(ctx, state.x), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), JSValueMakeNumber(ctx, state.y), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_rotation) ? symbol_rotation : symbol_rotation = JSStringCreateWithUTF8CString("rotation")), JSValueMakeNumber(ctx, state.rotation), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_maxForce) ? symbol_maxForce : symbol_maxForce = JSStringCreateWithUTF8CString("maxForce")), JSValueMakeNumber(ctx, state.maxForce), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_maxTorque) ? symbol_maxTorque : symbol_maxTorque = JSStringCreateWithUTF8CString("maxTorque")), JSValueMakeNumber(ctx, state.maxTorque), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_frequency) ? symbol_frequency : symbol_frequency = JSStringCreateWithUTF8CString("frequency")), JSValueMakeNumber(ctx, state.frequency), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_dampingRatio) ? symbol_dampingRatio : symbol_dampingRatio = JSStringCreateWithUTF8CString("dampingRatio")), JSValueMakeNumber(ctx, state.dampingRatio), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_forceX) ? symbol_forceX : symbol_forceX = JSStringCreateWithUTF8CString("forceX")), JSValueMakeNumber(ctx, state.forceX), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_forceY) ? symbol_forceY : symbol_forceY = JSStringCreateWithUTF8CString("forceY")), JSValueMakeNumber(ctx, state.forceY), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_torque) ? symbol_torque : symbol_torque = JSStringCreateWithUTF8CString("torque")), JSValueMakeNumber(ctx, state.torque), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_positionError) ? symbol_positionError : symbol_positionError = JSStringCreateWithUTF8CString("positionError")), JSValueMakeNumber(ctx, state.positionError), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, result, ((symbol_rotationError) ? symbol_rotationError : symbol_rotationError = JSStringCreateWithUTF8CString("rotationError")), JSValueMakeNumber(ctx, state.rotationError), kJSPropertyAttributeNone, exception);
            return result;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef PhysicsBody_GetConstraintCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getConstraintCount());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreatePinJoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); pdg::Point anchor;
            if (argumentCount < 2)
            {
                anchor = Point();
            }
            else
            {
                auto anchor_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], anchor, exception);
                if (!anchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*anchor_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
                }
            }; pdg::Point otherAnchor;
            if (argumentCount < 3)
            {
                otherAnchor = Point();
            }
            else
            {
                auto otherAnchor_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], otherAnchor, exception);
                if (!otherAnchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*otherAnchor_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
                }
            }; auto* result=&self->createPinJoint(*other,anchor,otherAnchor); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreatePivotJoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); pdg::Point anchor;
            if (argumentCount < 2)
            {
                anchor = Point();
            }
            else
            {
                auto anchor_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], anchor, exception);
                if (!anchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*anchor_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
                }
            }; pdg::Point otherAnchor;
            if (argumentCount < 3)
            {
                otherAnchor = Point();
            }
            else
            {
                auto otherAnchor_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], otherAnchor, exception);
                if (!otherAnchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*otherAnchor_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
                }
            }; auto* result=&self->createPivotJoint(*other,anchor,otherAnchor); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateSlideJoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 5)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 5, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); pdg::Point anchor;
            auto anchor_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], anchor, exception);
            if (!anchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*anchor_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            }; pdg::Point otherAnchor;
            auto otherAnchor_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], otherAnchor, exception);
            if (!otherAnchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*otherAnchor_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
            }; if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""minDistance"")");
            double minDistance = JSValueToNumber(ctx, arguments[4 -1], exception); if (argumentCount < 5 || !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""maxDistance"")");
            double maxDistance = JSValueToNumber(ctx, arguments[5 -1], exception); auto* result=&self->createSlideJoint(*other,anchor,otherAnchor,minDistance,maxDistance); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateGrooveJoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 4)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); pdg::Point start;
            auto start_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], start, exception);
            if (!start_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*start_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            }; pdg::Point end;
            auto end_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], end, exception);
            if (!end_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*end_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
            }; pdg::Point otherAnchor;
            auto otherAnchor_isPoint = JSC_ValueIsPoint(ctx, arguments[4 -1], otherAnchor, exception);
            if (!otherAnchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*otherAnchor_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 4, "Point", arguments[4 -1]);
            }; auto* result=&self->createGrooveJoint(*other,start,end,otherAnchor); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateSpring(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 6)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 6, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); pdg::Point anchor;
            auto anchor_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], anchor, exception);
            if (!anchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*anchor_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            }; pdg::Point otherAnchor;
            auto otherAnchor_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], otherAnchor, exception);
            if (!otherAnchor_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*otherAnchor_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
            }; if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""restLength"")");
            double restLength = JSValueToNumber(ctx, arguments[4 -1], exception); if (argumentCount < 5 || !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""stiffness"")");
            double stiffness = JSValueToNumber(ctx, arguments[5 -1], exception); if (argumentCount < 6 || !JSValueIsNumber(ctx, arguments[6 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 6, "a number (""damping"")");
            double damping = JSValueToNumber(ctx, arguments[6 -1], exception); auto* result=&self->createSpring(*other,anchor,otherAnchor,restLength,stiffness,damping); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateRotarySpring(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 4)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""restAngle"")");
            double restAngle = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""stiffness"")");
            double stiffness = JSValueToNumber(ctx, arguments[3 -1], exception); if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""damping"")");
            double damping = JSValueToNumber(ctx, arguments[4 -1], exception); auto* result=&self->createRotarySpring(*other,restAngle,stiffness,damping); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateRotaryLimit(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 3)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""minAngle"")");
            double minAngle = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""maxAngle"")");
            double maxAngle = JSValueToNumber(ctx, arguments[3 -1], exception); auto* result=&self->createRotaryLimit(*other,minAngle,maxAngle); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateRatchet(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""interval"")");
            double interval = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""phase"")");
            double phase = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception); auto* result=&self->createRatchet(*other,interval,phase); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateGear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""ratio"")");
            double ratio = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""phase"")");
            double phase = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception); auto* result=&self->createGear(*other,ratio,phase); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_CreateMotor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 3)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = PhysicsBody_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radiansPerSecond"")");
            double radiansPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""maxTorque"")");
            double maxTorque = JSValueToNumber(ctx, arguments[3 -1], exception); auto* result=&self->createMotor(*other,radiansPerSecond,maxTorque); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_GetConstraint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            double index = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(index)||index<0||index>4294967295.0||index!=std::floor(index))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned 32-bit integer" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } auto* result=&self->getConstraint(uint32_t(index)); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsConstraintScriptObj)
            {
                return PhysicsConstraint_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsConstraintScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsBody_Disconnect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsBody* self = static_cast<PhysicsBody*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if(argumentCount==0||JSValueIsNull(ctx, arguments[0])) self->disconnect(); else
            {
                if(!COLLISION_ARGUMENT_IS(arguments[0],true))
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                } PhysicsBody* other = 0;
                if (JSValueIsObject(ctx, arguments[1 -1]))
                {
                    JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                    other = PhysicsBody_getCppObject(other_);
                }
                if (!other)
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""other"")"); self->disconnect(other);
            }
            return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

}
