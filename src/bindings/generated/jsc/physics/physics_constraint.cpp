// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/physics_constraint.cpp
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

    static JSStringRef symbol_x = 0;
    static JSStringRef symbol_y = 0;

#ifdef PDG_USING_JAVASCRIPT_CORE
    PhysicsConstraint* New_PhysicsConstraint(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return nullptr; }
    static void PhysicsConstraint_finalize(JSObjectRef object)
    {
        auto* body=static_cast<PhysicsConstraint*>(JSObjectGetPrivate(object));
        if(body) {body->mPhysicsConstraintScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
    }
#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj=obj
#else
#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj.Reset(isolate,obj);cppObj->mPhysicsConstraintScriptObj.SetWeak()
    PhysicsConstraintWrap::PhysicsConstraintWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(nullptr) {}
    PhysicsConstraintWrap::~PhysicsConstraintWrap()
    {
        if(cppPtr_) {cppPtr_->mPhysicsConstraintScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
    }
#endif
    static bool s_PhysicsConstraint_InNewFromCpp = false;

    JSObjectRef PhysicsConstraint_newFromCpp(JSContextRef ctx, PhysicsConstraint* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, PhysicsConstraint_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, PhysicsConstraint_class());
        PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj);cppObj->addRef();
        return obj;
    }

    JSObjectRef PhysicsConstraint_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_PhysicsConstraint_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "PhysicsConstraint" " cannot be instantiated with \\'new\\'. Use the factory function: pdg." "PhysicsBody.createPinJoint and other constraint factories" "()')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        PhysicsConstraint* cppObj = New_PhysicsConstraint(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to create C++ native " "PhysicsConstraint" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, PhysicsConstraint_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, PhysicsConstraint_class());
        return obj;
    }

    JSClassRef PhysicsConstraint_class()
    {

        static JSStaticValue PhysicsConstraint_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction PhysicsConstraint_staticFunctions[] =
        {
            { "isActive", PhysicsConstraint_IsActive, kJSPropertyAttributeDontDelete },
            { "isBroken", PhysicsConstraint_IsBroken, kJSPropertyAttributeDontDelete },
            { "getCollideBodies", PhysicsConstraint_GetCollideBodies, kJSPropertyAttributeDontDelete },
            { "getType", PhysicsConstraint_GetType, kJSPropertyAttributeDontDelete },
            { "getMaxForce", PhysicsConstraint_GetMaxForce, kJSPropertyAttributeDontDelete },
            { "getBreakForce", PhysicsConstraint_GetBreakForce, kJSPropertyAttributeDontDelete },
            { "getImpulse", PhysicsConstraint_GetImpulse, kJSPropertyAttributeDontDelete },
            { "getForce", PhysicsConstraint_GetForce, kJSPropertyAttributeDontDelete },
            { "setCollideBodies", PhysicsConstraint_SetCollideBodies, kJSPropertyAttributeDontDelete },
            { "setMaxForce", PhysicsConstraint_SetMaxForce, kJSPropertyAttributeDontDelete },
            { "setBreakForce", PhysicsConstraint_SetBreakForce, kJSPropertyAttributeDontDelete },
            { "getBodyA", PhysicsConstraint_GetBodyA, kJSPropertyAttributeDontDelete },
            { "getBodyB", PhysicsConstraint_GetBodyB, kJSPropertyAttributeDontDelete },
            { "getAnchorA", PhysicsConstraint_GetAnchorA, kJSPropertyAttributeDontDelete },
            { "getAnchorB", PhysicsConstraint_GetAnchorB, kJSPropertyAttributeDontDelete },
            { "setAnchorA", PhysicsConstraint_SetAnchorA, kJSPropertyAttributeDontDelete },
            { "setAnchorB", PhysicsConstraint_SetAnchorB, kJSPropertyAttributeDontDelete },
            { "setAnchors", PhysicsConstraint_SetAnchors, kJSPropertyAttributeDontDelete },
            { "getGrooveStart", PhysicsConstraint_GetGrooveStart, kJSPropertyAttributeDontDelete },
            { "getGrooveEnd", PhysicsConstraint_GetGrooveEnd, kJSPropertyAttributeDontDelete },
            { "setGroove", PhysicsConstraint_SetGroove, kJSPropertyAttributeDontDelete },
            { "getMinAngle", PhysicsConstraint_GetMinAngle, kJSPropertyAttributeDontDelete },
            { "getMaxAngle", PhysicsConstraint_GetMaxAngle, kJSPropertyAttributeDontDelete },
            { "setAngleLimits", PhysicsConstraint_SetAngleLimits, kJSPropertyAttributeDontDelete },
            { "disconnect", PhysicsConstraint_Disconnect, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = PhysicsConstraint_finalize;
            definition.className = "PhysicsConstraint";
            definition.staticFunctions = PhysicsConstraint_staticFunctions;
            definition.staticValues = PhysicsConstraint_staticValues;
            definition.callAsConstructor = PhysicsConstraint_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
#undef PHYSICSCONSTRAINT_SAVE_WEAK

    JSValueRef PhysicsConstraint_IsActive(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isActive());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_IsBroken(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isBroken());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetCollideBodies(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->getCollideBodies());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getType());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetMaxForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMaxForce());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetBreakForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getBreakForce());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetImpulse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getImpulse());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getForce());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetCollideBodies(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""value"")");
            bool value = JSValueToBoolean(ctx, arguments[1 -1]); self->setCollideBodies(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetMaxForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); self->setMaxForce(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetBreakForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); self->setBreakForce(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetBodyA(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=&self->getBodyA(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsBodyScriptObj)
            {
                return PhysicsBody_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsBodyScriptObj;
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
    JSValueRef PhysicsConstraint_GetBodyB(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=&self->getBodyB(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsBodyScriptObj)
            {
                return PhysicsBody_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsBodyScriptObj;
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

#ifdef PDG_USING_JAVASCRIPT_CORE
#define CONSTRAINT_VALUE_MISSING(value) (!(value) || (exception && *exception))
#else
#define CONSTRAINT_VALUE_MISSING(value) ((value).IsEmpty())
#endif

    JSValueRef PhysicsConstraint_GetAnchorA(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto result=self->getAnchorA(); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetAnchorB(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto result=self->getAnchorB(); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetAnchorA(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if(!JSValueIsObject(ctx, arguments[1 -1]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto anchor_object=JSValueToObject(ctx, arguments[1 -1], exception); auto anchor_x=JSObjectGetProperty(ctx, anchor_object, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), exception); if(CONSTRAINT_VALUE_MISSING(anchor_x))
            {
                return JSValueMakeNull(ctx);
            }
            auto anchor_y=JSObjectGetProperty(ctx, anchor_object, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), exception); if(CONSTRAINT_VALUE_MISSING(anchor_y))
            {
                return JSValueMakeNull(ctx);
            }
            if(!JSValueIsNumber(ctx, anchor_x) || !JSValueIsNumber(ctx, anchor_y) || !std::isfinite(JSValueToNumber(ctx, anchor_x, exception)) || !std::isfinite(JSValueToNumber(ctx, anchor_y, exception)))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected finite Point coordinates" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            pdg::Point anchor(JSValueToNumber(ctx, anchor_x, exception),JSValueToNumber(ctx, anchor_y, exception)); self->setAnchorA(anchor); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetAnchorB(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if(!JSValueIsObject(ctx, arguments[1 -1]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto anchor_object=JSValueToObject(ctx, arguments[1 -1], exception); auto anchor_x=JSObjectGetProperty(ctx, anchor_object, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), exception); if(CONSTRAINT_VALUE_MISSING(anchor_x))
            {
                return JSValueMakeNull(ctx);
            }
            auto anchor_y=JSObjectGetProperty(ctx, anchor_object, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), exception); if(CONSTRAINT_VALUE_MISSING(anchor_y))
            {
                return JSValueMakeNull(ctx);
            }
            if(!JSValueIsNumber(ctx, anchor_x) || !JSValueIsNumber(ctx, anchor_y) || !std::isfinite(JSValueToNumber(ctx, anchor_x, exception)) || !std::isfinite(JSValueToNumber(ctx, anchor_y, exception)))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected finite Point coordinates" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            pdg::Point anchor(JSValueToNumber(ctx, anchor_x, exception),JSValueToNumber(ctx, anchor_y, exception)); self->setAnchorB(anchor); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetAnchors(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); if(!JSValueIsObject(ctx, arguments[1 -1]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto a_object=JSValueToObject(ctx, arguments[1 -1], exception); auto a_x=JSObjectGetProperty(ctx, a_object, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), exception); if(CONSTRAINT_VALUE_MISSING(a_x))
            {
                return JSValueMakeNull(ctx);
            }
            auto a_y=JSObjectGetProperty(ctx, a_object, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), exception); if(CONSTRAINT_VALUE_MISSING(a_y))
            {
                return JSValueMakeNull(ctx);
            }
            if(!JSValueIsNumber(ctx, a_x) || !JSValueIsNumber(ctx, a_y) || !std::isfinite(JSValueToNumber(ctx, a_x, exception)) || !std::isfinite(JSValueToNumber(ctx, a_y, exception)))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected finite Point coordinates" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            pdg::Point a(JSValueToNumber(ctx, a_x, exception),JSValueToNumber(ctx, a_y, exception)); if(!JSValueIsObject(ctx, arguments[2 -1]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto b_object=JSValueToObject(ctx, arguments[2 -1], exception); auto b_x=JSObjectGetProperty(ctx, b_object, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), exception); if(CONSTRAINT_VALUE_MISSING(b_x))
            {
                return JSValueMakeNull(ctx);
            }
            auto b_y=JSObjectGetProperty(ctx, b_object, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), exception); if(CONSTRAINT_VALUE_MISSING(b_y))
            {
                return JSValueMakeNull(ctx);
            }
            if(!JSValueIsNumber(ctx, b_x) || !JSValueIsNumber(ctx, b_y) || !std::isfinite(JSValueToNumber(ctx, b_x, exception)) || !std::isfinite(JSValueToNumber(ctx, b_y, exception)))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected finite Point coordinates" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            pdg::Point b(JSValueToNumber(ctx, b_x, exception),JSValueToNumber(ctx, b_y, exception)); self->setAnchors(a,b); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetGrooveStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto result=self->getGrooveStart(); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetGrooveEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto result=self->getGrooveEnd(); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetGroove(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); if(!JSValueIsObject(ctx, arguments[1 -1]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto a_object=JSValueToObject(ctx, arguments[1 -1], exception); auto a_x=JSObjectGetProperty(ctx, a_object, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), exception); if(CONSTRAINT_VALUE_MISSING(a_x))
            {
                return JSValueMakeNull(ctx);
            }
            auto a_y=JSObjectGetProperty(ctx, a_object, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), exception); if(CONSTRAINT_VALUE_MISSING(a_y))
            {
                return JSValueMakeNull(ctx);
            }
            if(!JSValueIsNumber(ctx, a_x) || !JSValueIsNumber(ctx, a_y) || !std::isfinite(JSValueToNumber(ctx, a_x, exception)) || !std::isfinite(JSValueToNumber(ctx, a_y, exception)))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected finite Point coordinates" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            pdg::Point a(JSValueToNumber(ctx, a_x, exception),JSValueToNumber(ctx, a_y, exception)); if(!JSValueIsObject(ctx, arguments[2 -1]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto b_object=JSValueToObject(ctx, arguments[2 -1], exception); auto b_x=JSObjectGetProperty(ctx, b_object, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), exception); if(CONSTRAINT_VALUE_MISSING(b_x))
            {
                return JSValueMakeNull(ctx);
            }
            auto b_y=JSObjectGetProperty(ctx, b_object, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), exception); if(CONSTRAINT_VALUE_MISSING(b_y))
            {
                return JSValueMakeNull(ctx);
            }
            if(!JSValueIsNumber(ctx, b_x) || !JSValueIsNumber(ctx, b_y) || !std::isfinite(JSValueToNumber(ctx, b_x, exception)) || !std::isfinite(JSValueToNumber(ctx, b_y, exception)))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected finite Point coordinates" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            pdg::Point b(JSValueToNumber(ctx, b_x, exception),JSValueToNumber(ctx, b_y, exception)); self->setGroove(a,b); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

#undef CONSTRAINT_VALUE_MISSING
    JSValueRef PhysicsConstraint_GetMinAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMinAngle());
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_GetMaxAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMaxAngle());
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_SetAngleLimits(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""lo"")");
            double lo = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""hi"")");
            double hi = JSValueToNumber(ctx, arguments[2 -1], exception); self->setAngleLimits(lo,hi); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef PhysicsConstraint_Disconnect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        PhysicsConstraint* self = static_cast<PhysicsConstraint*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->disconnect(); return JSValueMakeUndefined(ctx);
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
