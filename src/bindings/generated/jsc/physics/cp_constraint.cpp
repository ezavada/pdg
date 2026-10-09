// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/cp_constraint.cpp
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

#include <sstream>
#include <cmath>
#include <cstdlib>

namespace pdg
{

    JSObjectRef cpConstraint_newFromCpp(JSContextRef ctx, cpConstraint* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, cpConstraint_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, cpConstraint_class());
        ;
        return obj;
    }

    JSObjectRef cpConstraint_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* cppObj = New_cpConstraint(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "cpConstraint" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, cpConstraint_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, cpConstraint_class());
        ;
        return obj;
    }

    JSClassRef cpConstraint_class()
    {
        static JSStaticValue cpConstraint_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction cpConstraint_staticFunctions[] =
        {
            { "get""Type", cpConstraint_GetType, kJSPropertyAttributeDontDelete },
            { "activateBodies", cpConstraint_ActivateBodies, kJSPropertyAttributeDontDelete },
            { "get""Impulse", cpConstraint_GetImpulse, kJSPropertyAttributeDontDelete },
            { "get""MaxForce", cpConstraint_GetMaxForce, kJSPropertyAttributeDontDelete },
            { "set""MaxForce", cpConstraint_SetMaxForce, kJSPropertyAttributeDontDelete },
            { "get""ErrorBias", cpConstraint_GetErrorBias, kJSPropertyAttributeDontDelete },
            { "set""ErrorBias", cpConstraint_SetErrorBias, kJSPropertyAttributeDontDelete },
            { "get""MaxBias", cpConstraint_GetMaxBias, kJSPropertyAttributeDontDelete },
            { "set""MaxBias", cpConstraint_SetMaxBias, kJSPropertyAttributeDontDelete },
            { "get""Sprite", cpConstraint_GetSprite, kJSPropertyAttributeDontDelete },
            { "get""OtherSprite", cpConstraint_GetOtherSprite, kJSPropertyAttributeDontDelete },
            { "get""Anchor", cpConstraint_GetAnchor, kJSPropertyAttributeDontDelete },
            { "set""Anchor", cpConstraint_SetAnchor, kJSPropertyAttributeDontDelete },
            { "get""OtherAnchor", cpConstraint_GetOtherAnchor, kJSPropertyAttributeDontDelete },
            { "set""OtherAnchor", cpConstraint_SetOtherAnchor, kJSPropertyAttributeDontDelete },
            { "get""PinDist", cpConstraint_GetPinDist, kJSPropertyAttributeDontDelete },
            { "set""PinDist", cpConstraint_SetPinDist, kJSPropertyAttributeDontDelete },
            { "get""SpringStiffness", cpConstraint_GetSpringStiffness, kJSPropertyAttributeDontDelete },
            { "set""SpringStiffness", cpConstraint_SetSpringStiffness, kJSPropertyAttributeDontDelete },
            { "get""SpringDamping", cpConstraint_GetSpringDamping, kJSPropertyAttributeDontDelete },
            { "set""SpringDamping", cpConstraint_SetSpringDamping, kJSPropertyAttributeDontDelete },
            { "get""SlideMinDist", cpConstraint_GetSlideMinDist, kJSPropertyAttributeDontDelete },
            { "set""SlideMinDist", cpConstraint_SetSlideMinDist, kJSPropertyAttributeDontDelete },
            { "get""SlideMaxDist", cpConstraint_GetSlideMaxDist, kJSPropertyAttributeDontDelete },
            { "set""SlideMaxDist", cpConstraint_SetSlideMaxDist, kJSPropertyAttributeDontDelete },
            { "get""GrooveStart", cpConstraint_GetGrooveStart, kJSPropertyAttributeDontDelete },
            { "set""GrooveStart", cpConstraint_SetGrooveStart, kJSPropertyAttributeDontDelete },
            { "get""GrooveEnd", cpConstraint_GetGrooveEnd, kJSPropertyAttributeDontDelete },
            { "set""GrooveEnd", cpConstraint_SetGrooveEnd, kJSPropertyAttributeDontDelete },
            { "get""SpringRestLength", cpConstraint_GetSpringRestLength, kJSPropertyAttributeDontDelete },
            { "set""SpringRestLength", cpConstraint_SetSpringRestLength, kJSPropertyAttributeDontDelete },
            { "get""RotarySpringRestAngle", cpConstraint_GetRotarySpringRestAngle, kJSPropertyAttributeDontDelete },
            { "set""RotarySpringRestAngle", cpConstraint_SetRotarySpringRestAngle, kJSPropertyAttributeDontDelete },
            { "get""MinAngle", cpConstraint_GetMinAngle, kJSPropertyAttributeDontDelete },
            { "set""MinAngle", cpConstraint_SetMinAngle, kJSPropertyAttributeDontDelete },
            { "get""MaxAngle", cpConstraint_GetMaxAngle, kJSPropertyAttributeDontDelete },
            { "set""MaxAngle", cpConstraint_SetMaxAngle, kJSPropertyAttributeDontDelete },
            { "get""RatchetAngle", cpConstraint_GetRatchetAngle, kJSPropertyAttributeDontDelete },
            { "set""RatchetAngle", cpConstraint_SetRatchetAngle, kJSPropertyAttributeDontDelete },
            { "get""RatchetPhase", cpConstraint_GetRatchetPhase, kJSPropertyAttributeDontDelete },
            { "set""RatchetPhase", cpConstraint_SetRatchetPhase, kJSPropertyAttributeDontDelete },
            { "get""RatchetInterval", cpConstraint_GetRatchetInterval, kJSPropertyAttributeDontDelete },
            { "set""RatchetInterval", cpConstraint_SetRatchetInterval, kJSPropertyAttributeDontDelete },
            { "get""GearRatio", cpConstraint_GetGearRatio, kJSPropertyAttributeDontDelete },
            { "set""GearRatio", cpConstraint_SetGearRatio, kJSPropertyAttributeDontDelete },
            { "get""GearInitialAngle", cpConstraint_GetGearInitialAngle, kJSPropertyAttributeDontDelete },
            { "set""GearInitialAngle", cpConstraint_SetGearInitialAngle, kJSPropertyAttributeDontDelete },
            { "get""MotorSpinRate", cpConstraint_GetMotorSpinRate, kJSPropertyAttributeDontDelete },
            { "set""MotorSpinRate", cpConstraint_SetMotorSpinRate, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "CpConstraint";
            definition.staticFunctions = cpConstraint_staticFunctions;
            definition.staticValues = cpConstraint_staticValues;
            definition.callAsConstructor = cpConstraint_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef cpConstraint_GetType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        const char* theType = (const char*)cpConstraintGetUserData(self);
        return JSC_MakeValueFromCString(ctx, theType);
    };

    JSValueRef cpConstraint_GetImpulse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theImpulse = cpConstraintGetImpulse(self);
        return JSValueMakeNumber(ctx, theImpulse);
    }
    JSValueRef cpConstraint_GetMaxForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theMaxForce = cpConstraintGetMaxForce(self);
        return JSValueMakeNumber(ctx, theMaxForce);
    }
    JSValueRef cpConstraint_SetMaxForce(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMaxForce"")");
        double theMaxForce = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpConstraintSetMaxForce(self, theMaxForce);
        return thisObject;
    }
    JSValueRef cpConstraint_GetErrorBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theErrorBias = cpConstraintGetErrorBias(self);
        return JSValueMakeNumber(ctx, theErrorBias);
    }
    JSValueRef cpConstraint_SetErrorBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theErrorBias"")");
        double theErrorBias = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpConstraintSetErrorBias(self, theErrorBias);
        return thisObject;
    }
    JSValueRef cpConstraint_GetMaxBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theMaxBias = cpConstraintGetMaxBias(self);
        return JSValueMakeNumber(ctx, theMaxBias);
    }
    JSValueRef cpConstraint_SetMaxBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMaxBias"")");
        double theMaxBias = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpConstraintSetMaxBias(self, theMaxBias);
        return thisObject;
    }
    JSValueRef cpConstraint_ActivateBodies(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));;
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpConstraintActivateBodies(self);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef cpConstraint_GetSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));;
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpBody* body = cpConstraintGetBodyA(self);
        Sprite* sprite = (Sprite*) cpBodyGetUserData(body);
        if (!sprite) return JSValueMakeNull(ctx);
        if (!sprite->mSpriteScriptObj)
        {
            return Sprite_newFromCpp(ctx, sprite);
        }
        else
        {
            return sprite->mSpriteScriptObj;
        };
    }
    JSValueRef cpConstraint_GetOtherSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));;
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpBody* body = cpConstraintGetBodyB(self);
        Sprite* otherSprite = (Sprite*) cpBodyGetUserData(body);
        if (!otherSprite) return JSValueMakeNull(ctx);
        if (!otherSprite->mSpriteScriptObj)
        {
            return Sprite_newFromCpp(ctx, otherSprite);
        }
        else
        {
            return otherSprite->mSpriteScriptObj;
        };
    }
    JSValueRef cpConstraint_GetAnchor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpVect anchor;
        if (cpConstraintIsPinJoint(self))
        {
            anchor = cpPinJointGetAnchorA(self);
        }
        else if (cpConstraintIsSlideJoint(self))
        {
            anchor = cpSlideJointGetAnchorA(self);
        }
        else if (cpConstraintIsPivotJoint(self))
        {
            anchor = cpPivotJointGetAnchorA(self);
        }
        else if (cpConstraintIsDampedSpring(self))
        {
            anchor = cpDampedSpringGetAnchorA(self);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        }
        pdg::Offset theAnchor(anchor.x, anchor.y);
        return JSC_OffsetToValue(ctx, theAnchor, exception);
    }

    JSValueRef cpConstraint_SetAnchor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Offset theAnchor;
        auto theAnchor_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], theAnchor, exception);
        if (!theAnchor_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*theAnchor_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        cpVect anchor = cpv(theAnchor.x, theAnchor.y);
        if (cpConstraintIsPinJoint(self))
        {
            cpPinJointSetAnchorA(self, anchor);
        }
        else if (cpConstraintIsSlideJoint(self))
        {
            cpSlideJointSetAnchorA(self, anchor);
        }
        else if (cpConstraintIsPivotJoint(self))
        {
            cpPivotJointSetAnchorA(self, anchor);
        }
        else if (cpConstraintIsDampedSpring(self))
        {
            cpDampedSpringSetAnchorA(self, anchor);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setAnchor() not valid for constraint type "
                << "unsupported joint";
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << msg.str().c_str() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        return thisObject;
    }

    JSValueRef cpConstraint_GetOtherAnchor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpVect anchor;
        if (cpConstraintIsPinJoint(self))
        {
            anchor = cpPinJointGetAnchorB(self);
        }
        else if (cpConstraintIsSlideJoint(self))
        {
            anchor = cpSlideJointGetAnchorB(self);
        }
        else if (cpConstraintIsPivotJoint(self))
        {
            anchor = cpPivotJointGetAnchorB(self);
        }
        else if (cpConstraintIsGrooveJoint(self))
        {
            anchor = cpGrooveJointGetAnchorB(self);
        }
        else if (cpConstraintIsDampedSpring(self))
        {
            anchor = cpDampedSpringGetAnchorB(self);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        }
        pdg::Offset theOtherAnchor(anchor.x, anchor.y);
        return JSC_OffsetToValue(ctx, theOtherAnchor, exception);
    }

    JSValueRef cpConstraint_SetOtherAnchor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Offset theOtherAnchor;
        auto theOtherAnchor_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], theOtherAnchor, exception);
        if (!theOtherAnchor_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*theOtherAnchor_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        cpVect anchor = cpv(theOtherAnchor.x, theOtherAnchor.y);
        if (cpConstraintIsPinJoint(self))
        {
            cpPinJointSetAnchorB(self, anchor);
        }
        else if (cpConstraintIsSlideJoint(self))
        {
            cpSlideJointSetAnchorB(self, anchor);
        }
        else if (cpConstraintIsPivotJoint(self))
        {
            cpPivotJointSetAnchorB(self, anchor);
        }
        else if (cpConstraintIsGrooveJoint(self))
        {
            cpGrooveJointSetAnchorB(self, anchor);
        }
        else if (cpConstraintIsDampedSpring(self))
        {
            cpDampedSpringSetAnchorB(self, anchor);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setOtherAnchor() not valid for constraint type "
                << "unsupported joint";
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << msg.str().c_str() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        return thisObject;
    }

    JSValueRef cpConstraint_GetPinDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsPinJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat thePinDist = cpPinJointGetDist(self);
        return JSValueMakeNumber(ctx, thePinDist);
    }
    JSValueRef cpConstraint_SetPinDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""thePinDist"")");
        double thePinDist = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsPinJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "PinDist" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpPinJointSetDist(self, thePinDist);
        return thisObject;
    }
    JSValueRef cpConstraint_GetSlideMinDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsSlideJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theSlideMinDist = cpSlideJointGetMin(self);
        return JSValueMakeNumber(ctx, theSlideMinDist);
    }
    JSValueRef cpConstraint_SetSlideMinDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSlideMinDist"")");
        double theSlideMinDist = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsSlideJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "SlideMinDist" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpSlideJointSetMin(self, theSlideMinDist);
        return thisObject;
    }
    JSValueRef cpConstraint_GetSlideMaxDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsSlideJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theSlideMaxDist = cpSlideJointGetMax(self);
        return JSValueMakeNumber(ctx, theSlideMaxDist);
    }
    JSValueRef cpConstraint_SetSlideMaxDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSlideMaxDist"")");
        double theSlideMaxDist = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsSlideJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "SlideMaxDist" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpSlideJointSetMax(self, theSlideMaxDist);
        return thisObject;
    }
    JSValueRef cpConstraint_GetGrooveStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsGrooveJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpVect v = cpGrooveJointGetGrooveA(self);
        pdg::Offset theGrooveStart(v.x, v.y);
        return JSC_OffsetToValue(ctx, theGrooveStart, exception);
    }
    JSValueRef cpConstraint_SetGrooveStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Offset theGrooveStart;
        auto theGrooveStart_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], theGrooveStart, exception);
        if (!theGrooveStart_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*theGrooveStart_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        if (!cpConstraintIsGrooveJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "GrooveStart" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpGrooveJointSetGrooveA(self, cpv(theGrooveStart.x, theGrooveStart.y));
        return thisObject;
    }

    JSValueRef cpConstraint_GetGrooveEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsGrooveJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpVect v = cpGrooveJointGetGrooveB(self);
        pdg::Offset theGrooveEnd(v.x, v.y);
        return JSC_OffsetToValue(ctx, theGrooveEnd, exception);
    }
    JSValueRef cpConstraint_SetGrooveEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Offset theGrooveEnd;
        auto theGrooveEnd_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], theGrooveEnd, exception);
        if (!theGrooveEnd_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*theGrooveEnd_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        if (!cpConstraintIsGrooveJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "GrooveEnd" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpGrooveJointSetGrooveB(self, cpv(theGrooveEnd.x, theGrooveEnd.y));
        return thisObject;
    }

    JSValueRef cpConstraint_GetSpringRestLength(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsDampedSpring(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theSpringRestLength = cpDampedSpringGetRestLength(self);
        return JSValueMakeNumber(ctx, theSpringRestLength);
    }
    JSValueRef cpConstraint_SetSpringRestLength(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSpringRestLength"")");
        double theSpringRestLength = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsDampedSpring(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "SpringRestLength" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpDampedSpringSetRestLength(self, theSpringRestLength);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRotarySpringRestAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsDampedRotarySpring(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theRotarySpringRestAngle = cpDampedRotarySpringGetRestAngle(self);
        return JSValueMakeNumber(ctx, theRotarySpringRestAngle);
    }
    JSValueRef cpConstraint_SetRotarySpringRestAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRotarySpringRestAngle"")");
        double theRotarySpringRestAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsDampedRotarySpring(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "RotarySpringRestAngle" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpDampedRotarySpringSetRestAngle(self, theRotarySpringRestAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetMinAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsRotaryLimitJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theMinAngle = cpRotaryLimitJointGetMin(self);
        return JSValueMakeNumber(ctx, theMinAngle);
    }
    JSValueRef cpConstraint_SetMinAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMinAngle"")");
        double theMinAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsRotaryLimitJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "MinAngle" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpRotaryLimitJointSetMin(self, theMinAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetMaxAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsRotaryLimitJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theMaxAngle = cpRotaryLimitJointGetMax(self);
        return JSValueMakeNumber(ctx, theMaxAngle);
    }
    JSValueRef cpConstraint_SetMaxAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMaxAngle"")");
        double theMaxAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsRotaryLimitJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "MaxAngle" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpRotaryLimitJointSetMax(self, theMaxAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRatchetAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsRatchetJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theRatchetAngle = cpRatchetJointGetAngle(self);
        return JSValueMakeNumber(ctx, theRatchetAngle);
    }
    JSValueRef cpConstraint_SetRatchetAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRatchetAngle"")");
        double theRatchetAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsRatchetJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "RatchetAngle" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpRatchetJointSetAngle(self, theRatchetAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRatchetPhase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsRatchetJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theRatchetPhase = cpRatchetJointGetPhase(self);
        return JSValueMakeNumber(ctx, theRatchetPhase);
    }
    JSValueRef cpConstraint_SetRatchetPhase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRatchetPhase"")");
        double theRatchetPhase = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsRatchetJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "RatchetPhase" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpRatchetJointSetPhase(self, theRatchetPhase);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRatchetInterval(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsRatchetJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theRatchetInterval = cpRatchetJointGetRatchet(self);
        return JSValueMakeNumber(ctx, theRatchetInterval);
    }
    JSValueRef cpConstraint_SetRatchetInterval(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRatchetInterval"")");
        double theRatchetInterval = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsRatchetJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "RatchetInterval" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpRatchetJointSetRatchet(self, theRatchetInterval);
        return thisObject;
    }
    JSValueRef cpConstraint_GetGearRatio(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsGearJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theGearRatio = cpGearJointGetRatio(self);
        return JSValueMakeNumber(ctx, theGearRatio);
    }
    JSValueRef cpConstraint_SetGearRatio(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theGearRatio"")");
        double theGearRatio = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsGearJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "GearRatio" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpGearJointSetRatio(self, theGearRatio);
        return thisObject;
    }
    JSValueRef cpConstraint_GetGearInitialAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsGearJoint(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theGearInitialAngle = cpGearJointGetPhase(self);
        return JSValueMakeNumber(ctx, theGearInitialAngle);
    }
    JSValueRef cpConstraint_SetGearInitialAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theGearInitialAngle"")");
        double theGearInitialAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsGearJoint(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "GearInitialAngle" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpGearJointSetPhase(self, theGearInitialAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetMotorSpinRate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (!cpConstraintIsSimpleMotor(self))
        {
            return JSValueMakeUndefined(ctx);
        };
        cpFloat theMotorSpinRate = cpSimpleMotorGetRate(self);
        return JSValueMakeNumber(ctx, theMotorSpinRate);
    }
    JSValueRef cpConstraint_SetMotorSpinRate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMotorSpinRate"")");
        double theMotorSpinRate = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!cpConstraintIsSimpleMotor(self))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "cpConstraint.set" "MotorSpinRate" "() not valid for this constraint type" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
            return JSValueMakeUndefined(ctx);
        };
        cpSimpleMotorSetRate(self, theMotorSpinRate);
        return thisObject;
    }
    JSValueRef cpConstraint_GetSpringStiffness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpFloat theSpringStiffness;
        if (cpConstraintIsDampedSpring(self))
        {
            theSpringStiffness = cpDampedSpringGetStiffness(self);
        }
        else if (cpConstraintIsDampedRotarySpring(self))
        {
            theSpringStiffness = cpDampedRotarySpringGetStiffness(self);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
#ifndef PDG_USING_JAVASCRIPT_CORE
            return;
#endif
        };
        return JSValueMakeNumber(ctx, theSpringStiffness);
    }

    JSValueRef cpConstraint_SetSpringStiffness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSpringStiffness"")");
        double theSpringStiffness = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (cpConstraintIsDampedSpring(self))
        {
            cpDampedSpringSetStiffness(self, theSpringStiffness);
        }
        else if (cpConstraintIsDampedRotarySpring(self))
        {
            cpDampedRotarySpringSetStiffness(self, theSpringStiffness);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setSpringStiffness() not valid for constraint type "
                << "unsupported joint";
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << msg.str().c_str() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        return thisObject;
    }

    JSValueRef cpConstraint_GetSpringDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpFloat theSpringDamping;
        if (cpConstraintIsDampedSpring(self))
        {
            theSpringDamping = cpDampedSpringGetDamping(self);
        }
        else if (cpConstraintIsDampedRotarySpring(self))
        {
            theSpringDamping = cpDampedRotarySpringGetDamping(self);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
#ifndef PDG_USING_JAVASCRIPT_CORE
            return;
#endif
        };
        return JSValueMakeNumber(ctx, theSpringDamping);
    }

    JSValueRef cpConstraint_SetSpringDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSpringDamping"")");
        double theSpringDamping = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (cpConstraintIsDampedSpring(self))
        {
            cpDampedSpringSetDamping(self, theSpringDamping);
        }
        else if (cpConstraintIsDampedRotarySpring(self))
        {
            cpDampedRotarySpringSetDamping(self, theSpringDamping);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setSpringDamping() not valid for constraint type "
                << "unsupported joint";
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << msg.str().c_str() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        return thisObject;
    }

    cpConstraint* New_cpConstraint(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        s_SavedError.str(""); s_SavedError.clear();
        s_SavedError << "CpConstraint cannot be created directly, it is only returned from certain Sprite calls.";
        s_HaveSavedError = true;
        return 0;
    }

}
