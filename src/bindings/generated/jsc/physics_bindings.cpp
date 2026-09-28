// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/physics_bindings.cpp
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

    JSObjectRef cpArbiter_newFromCpp(JSContextRef ctx, cpArbiter* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, cpArbiter_class(), cppObj);
        ;
        return obj;
    }

    JSObjectRef cpArbiter_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* cppObj = New_cpArbiter(argumentCount, arguments);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "cpArbiter" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, cpArbiter_class(), cppObj);
        ;
        return obj;
    }

    JSClassRef cpArbiter_class()
    {
        static JSStaticValue cpArbiter_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction cpArbiter_staticFunctions[] =
        {
            { "isFirstContact", cpArbiter_IsFirstContact, kJSPropertyAttributeDontDelete },
            { "get""Count", cpArbiter_GetCount, kJSPropertyAttributeDontDelete },
            { "get""Normal", cpArbiter_GetNormal, kJSPropertyAttributeDontDelete },
            { "get""PointA", cpArbiter_GetPointA, kJSPropertyAttributeDontDelete },
            { "get""PointB", cpArbiter_GetPointB, kJSPropertyAttributeDontDelete },
            { "get""Depth", cpArbiter_GetDepth, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "CpArbiter";
            definition.staticFunctions = cpArbiter_staticFunctions;
            definition.staticValues = cpArbiter_staticValues;
            definition.callAsConstructor = cpArbiter_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef cpArbiter_IsFirstContact(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpBool isFirst = cpArbiterIsFirstContact(self);
        return JSValueMakeBoolean(ctx, isFirst);
    }
    JSValueRef cpArbiter_GetCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theCount = cpArbiterGetCount(self);
        return JSValueMakeNumber(ctx, theCount);
    }
    JSValueRef cpArbiter_GetNormal(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpVect nv = cpArbiterGetNormal(self);
        pdg::Vector theNormal(nv.x, nv.y);
        return JSC_VectorToValue(ctx, theNormal, exception);
    }

    JSValueRef cpArbiter_GetPointA(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""i"")");
        int32 i = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        cpVect pt = cpArbiterGetPointA(self, i);
        pdg::Point thePointA(pt.x, pt.y);
        return JSC_PointToValue(ctx, thePointA, exception);
    }

    JSValueRef cpArbiter_GetPointB(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""i"")");
        int32 i = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        cpVect pt = cpArbiterGetPointB(self, i);
        pdg::Point thePointB(pt.x, pt.y);
        return JSC_PointToValue(ctx, thePointB, exception);
    }

    JSValueRef cpArbiter_GetDepth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""i"")");
        int32 i = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        cpFloat theDepth = cpArbiterGetDepth(self, i);
        return JSValueMakeNumber(ctx, theDepth);
    }

    CPP_UNMANAGED_CONSTRUCTOR_IMPL(cpArbiter, cppPtr_ = nullptr;
        )
        s_SavedError.str(""); s_SavedError.clear();
    s_SavedError << "CpArbiter cannot be created directly, it is only returned from certain Sprite calls.";
    s_HaveSavedError = true;
    return 0;
}


}

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
        ;
        return obj;
    }

    JSObjectRef cpConstraint_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* cppObj = New_cpConstraint(argumentCount, arguments);
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
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
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            anchor = cpPinJointGetAnchorA(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            anchor = cpSlideJointGetAnchorA(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            anchor = cpPivotJointGetAnchorA(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
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
        if (!JSC_ValueIsOffset(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        pdg::Offset theAnchor = JSC_ValueToOffset(ctx, arguments[1 -1], exception);
        cpVect anchor = cpv(theAnchor.x, theAnchor.y);
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            cpPinJointSetAnchorA(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            cpSlideJointSetAnchorA(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            cpPivotJointSetAnchorA(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetAnchorA(self, anchor);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setAnchor() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
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
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            anchor = cpPinJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            anchor = cpSlideJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            anchor = cpPivotJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") == 0)
        {
            anchor = cpGrooveJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
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
        if (!JSC_ValueIsOffset(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        pdg::Offset theOtherAnchor = JSC_ValueToOffset(ctx, arguments[1 -1], exception);
        cpVect anchor = cpv(theOtherAnchor.x, theOtherAnchor.y);
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            cpPinJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            cpSlideJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            cpPivotJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") == 0)
        {
            cpGrooveJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetAnchorB(self, anchor);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setOtherAnchor() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        return thisObject;
    }

    JSValueRef cpConstraint_GetPinDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""thePinDist"")");
        double thePinDist = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "PinDist" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpPinJointSetDist(self, thePinDist);
        return thisObject;
    }
    JSValueRef cpConstraint_GetSlideMinDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSlideMinDist"")");
        double theSlideMinDist = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "SlideMinDist" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpSlideJointSetMin(self, theSlideMinDist);
        return thisObject;
    }
    JSValueRef cpConstraint_GetSlideMaxDist(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSlideMaxDist"")");
        double theSlideMaxDist = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "SlideMaxDist" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpSlideJointSetMax(self, theSlideMaxDist);
        return thisObject;
    }
    JSValueRef cpConstraint_GetGrooveStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
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
        if (!JSC_ValueIsOffset(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        pdg::Offset theGrooveStart = JSC_ValueToOffset(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GrooveStart" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpGrooveJointSetGrooveA(self, cpv(theGrooveStart.x, theGrooveStart.y));
        return thisObject;
    }

    JSValueRef cpConstraint_GetGrooveEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
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
        if (!JSC_ValueIsOffset(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        pdg::Offset theGrooveEnd = JSC_ValueToOffset(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GrooveEnd" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpGrooveJointSetGrooveB(self, cpv(theGrooveEnd.x, theGrooveEnd.y));
        return thisObject;
    }

    JSValueRef cpConstraint_GetSpringRestLength(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSpringRestLength"")");
        double theSpringRestLength = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "SpringRestLength" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpDampedSpringSetRestLength(self, theSpringRestLength);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRotarySpringRestAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRotarySpringRestAngle"")");
        double theRotarySpringRestAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RotarySpringRestAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpDampedRotarySpringSetRestAngle(self, theRotarySpringRestAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetMinAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMinAngle"")");
        double theMinAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "MinAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpRotaryLimitJointSetMin(self, theMinAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetMaxAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMaxAngle"")");
        double theMaxAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "MaxAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpRotaryLimitJointSetMax(self, theMaxAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRatchetAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRatchetAngle"")");
        double theRatchetAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RatchetAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpRatchetJointSetAngle(self, theRatchetAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRatchetPhase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRatchetPhase"")");
        double theRatchetPhase = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RatchetPhase" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpRatchetJointSetPhase(self, theRatchetPhase);
        return thisObject;
    }
    JSValueRef cpConstraint_GetRatchetInterval(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theRatchetInterval"")");
        double theRatchetInterval = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RatchetInterval" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpRatchetJointSetRatchet(self, theRatchetInterval);
        return thisObject;
    }
    JSValueRef cpConstraint_GetGearRatio(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theGearRatio"")");
        double theGearRatio = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GearRatio" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpGearJointSetRatio(self, theGearRatio);
        return thisObject;
    }
    JSValueRef cpConstraint_GetGearInitialAngle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theGearInitialAngle"")");
        double theGearInitialAngle = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GearInitialAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        cpGearJointSetPhase(self, theGearInitialAngle);
        return thisObject;
    }
    JSValueRef cpConstraint_GetMotorSpinRate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Motor") != 0)
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
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theMotorSpinRate"")");
        double theMotorSpinRate = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "Motor") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "MotorSpinRate" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
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
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            theSpringStiffness = cpDampedSpringGetStiffness(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            theSpringStiffness = cpDampedRotarySpringGetStiffness(self);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        };
        return JSValueMakeNumber(ctx, theSpringStiffness);
    }

    JSValueRef cpConstraint_SetSpringStiffness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSpringStiffness"")");
        double theSpringStiffness = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetStiffness(self, theSpringStiffness);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            cpDampedRotarySpringSetStiffness(self, theSpringStiffness);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setSpringStiffness() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
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
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            theSpringDamping = cpDampedSpringGetDamping(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            theSpringDamping = cpDampedRotarySpringGetDamping(self);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        };
        return JSValueMakeNumber(ctx, theSpringDamping);
    }

    JSValueRef cpConstraint_SetSpringDamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpConstraint* self = static_cast<cpConstraint*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSpringDamping"")");
        double theSpringDamping = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetDamping(self, theSpringDamping);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            cpDampedRotarySpringSetDamping(self, theSpringDamping);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setSpringDamping() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " "TypeError" "('" "Type Error: " << msg.str().c_str() "')"), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx) ;
        };
        return thisObject;
    }

    CPP_UNMANAGED_CONSTRUCTOR_IMPL(cpConstraint, cppPtr_ = nullptr;
    )
    s_SavedError.str(""); s_SavedError.clear();
    s_SavedError << "CpConstraint cannot be created directly, it is only returned from certain Sprite calls.";
    s_HaveSavedError = true;
    return 0;
}


}

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

    JSObjectRef cpSpace_newFromCpp(JSContextRef ctx, cpSpace* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, cpSpace_class(), cppObj);
        ;
        return obj;
    }

    JSObjectRef cpSpace_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* cppObj = New_cpSpace(argumentCount, arguments);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "cpSpace" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, cpSpace_class(), cppObj);
        ;
        return obj;
    }

    JSClassRef cpSpace_class()
    {
        static JSStaticValue cpSpace_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction cpSpace_staticFunctions[] =
        {
            { "useSpatialHash", cpSpace_UseSpatialHash, kJSPropertyAttributeDontDelete },
            { "reindexStatic", cpSpace_ReindexStatic, kJSPropertyAttributeDontDelete },
            { "step", cpSpace_Step, kJSPropertyAttributeDontDelete },
            { "get""IdleSpeedThreshold", cpSpace_GetIdleSpeedThreshold, kJSPropertyAttributeDontDelete },
            { "set""IdleSpeedThreshold", cpSpace_SetIdleSpeedThreshold, kJSPropertyAttributeDontDelete },
            { "get""SleepTimeThreshold", cpSpace_GetSleepTimeThreshold, kJSPropertyAttributeDontDelete },
            { "set""SleepTimeThreshold", cpSpace_SetSleepTimeThreshold, kJSPropertyAttributeDontDelete },
            { "get""CollisionSlop", cpSpace_GetCollisionSlop, kJSPropertyAttributeDontDelete },
            { "set""CollisionSlop", cpSpace_SetCollisionSlop, kJSPropertyAttributeDontDelete },
            { "get""CollisionBias", cpSpace_GetCollisionBias, kJSPropertyAttributeDontDelete },
            { "set""CollisionBias", cpSpace_SetCollisionBias, kJSPropertyAttributeDontDelete },
            { "get""CollisionPersistence", cpSpace_GetCollisionPersistence, kJSPropertyAttributeDontDelete },
            { "set""CollisionPersistence", cpSpace_SetCollisionPersistence, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "CpSpace";
            definition.staticFunctions = cpSpace_staticFunctions;
            definition.staticValues = cpSpace_staticValues;
            definition.callAsConstructor = cpSpace_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef cpSpace_UseSpatialHash(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""dim"")");
        double dim = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""count"")");
        int32 count = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        cpSpaceUseSpatialHash(self, dim, count);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef cpSpace_ReindexStatic(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpSpaceReindexStatic(self);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef cpSpace_Step(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""dt"")");
        double dt = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceStep(self, dt);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef cpSpace_GetIdleSpeedThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theIdleSpeedThreshold = cpSpaceGetIdleSpeedThreshold(self);
        return JSValueMakeNumber(ctx, theIdleSpeedThreshold);
    }
    JSValueRef cpSpace_SetIdleSpeedThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theIdleSpeedThreshold"")");
        double theIdleSpeedThreshold = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetIdleSpeedThreshold(self, theIdleSpeedThreshold);
        return thisObject;
    }
    JSValueRef cpSpace_GetSleepTimeThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theSleepTimeThreshold = cpSpaceGetSleepTimeThreshold(self);
        return JSValueMakeNumber(ctx, theSleepTimeThreshold);
    }
    JSValueRef cpSpace_SetSleepTimeThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSleepTimeThreshold"")");
        double theSleepTimeThreshold = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetSleepTimeThreshold(self, theSleepTimeThreshold);
        return thisObject;
    }
    JSValueRef cpSpace_GetCollisionSlop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theCollisionSlop = cpSpaceGetCollisionSlop(self);
        return JSValueMakeNumber(ctx, theCollisionSlop);
    }
    JSValueRef cpSpace_SetCollisionSlop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theCollisionSlop"")");
        double theCollisionSlop = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetCollisionSlop(self, theCollisionSlop);
        return thisObject;
    }
    JSValueRef cpSpace_GetCollisionBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theCollisionBias = cpSpaceGetCollisionBias(self);
        return JSValueMakeNumber(ctx, theCollisionBias);
    }
    JSValueRef cpSpace_SetCollisionBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theCollisionBias"")");
        double theCollisionBias = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetCollisionBias(self, theCollisionBias);
        return thisObject;
    }
    JSValueRef cpSpace_GetCollisionPersistence(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theCollisionPersistence = cpSpaceGetCollisionPersistence(self);
        return JSValueMakeNumber(ctx, theCollisionPersistence);
    }
    JSValueRef cpSpace_SetCollisionPersistence(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theCollisionPersistence"")");
        double theCollisionPersistence = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetCollisionPersistence(self, theCollisionPersistence);
        return thisObject;
    }

    CPP_UNMANAGED_CONSTRUCTOR_IMPL(cpSpace, cppPtr_ = nullptr;
    )
    s_SavedError.str(""); s_SavedError.clear();
    s_SavedError << "CpSpace cannot be created directly, it is only returned from certain Sprite calls.";
    s_HaveSavedError = true;
    return 0;
}


}
