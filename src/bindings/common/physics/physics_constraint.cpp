// -----------------------------------------------
// physics_constraint.cpp
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

DECLARE_SYMBOL(x);
DECLARE_SYMBOL(y);

%#ifdef PDG_USING_JAVASCRIPT_CORE
PhysicsConstraint* New_PhysicsConstraint(SCRIPT_ARGS) { return nullptr; }
static void PhysicsConstraint_finalize(JSObjectRef object) {
    auto* body=static_cast<PhysicsConstraint*>(JSObjectGetPrivate(object));
    if(body) {body->mPhysicsConstraintScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
}
%#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj=obj
%#else
%#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj.Reset(isolate,obj);cppObj->mPhysicsConstraintScriptObj.SetWeak()
PhysicsConstraintWrap::PhysicsConstraintWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
PhysicsConstraintWrap::~PhysicsConstraintWrap() {
    if(cppPtr_) {cppPtr_->mPhysicsConstraintScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
}
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(PhysicsConstraint, "PhysicsBody.createPinJoint and other constraint factories",
    PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj);cppObj->addRef())
    EXPORT_FINALIZED_CLASS_SYMBOLS("PhysicsConstraint", PhysicsConstraint, PhysicsConstraint_finalize, , ,
        HAS_METHOD(PhysicsConstraint, "isActive", IsActive)
        HAS_METHOD(PhysicsConstraint, "isBroken", IsBroken)
        HAS_METHOD(PhysicsConstraint, "getCollideBodies", GetCollideBodies)
        HAS_METHOD(PhysicsConstraint, "getType", GetType)
        HAS_METHOD(PhysicsConstraint, "getMaxForce", GetMaxForce)
        HAS_METHOD(PhysicsConstraint, "getBreakForce", GetBreakForce)
        HAS_METHOD(PhysicsConstraint, "getImpulse", GetImpulse)
        HAS_METHOD(PhysicsConstraint, "getForce", GetForce)
        HAS_METHOD(PhysicsConstraint, "setCollideBodies", SetCollideBodies)
        HAS_METHOD(PhysicsConstraint, "setMaxForce", SetMaxForce)
        HAS_METHOD(PhysicsConstraint, "setBreakForce", SetBreakForce)
        HAS_METHOD(PhysicsConstraint, "getBodyA", GetBodyA)
        HAS_METHOD(PhysicsConstraint, "getBodyB", GetBodyB)
        HAS_METHOD(PhysicsConstraint, "getAnchorA", GetAnchorA)
        HAS_METHOD(PhysicsConstraint, "getAnchorB", GetAnchorB)
        HAS_METHOD(PhysicsConstraint, "setAnchorA", SetAnchorA)
        HAS_METHOD(PhysicsConstraint, "setAnchorB", SetAnchorB)
        HAS_METHOD(PhysicsConstraint, "setAnchors", SetAnchors)
        HAS_METHOD(PhysicsConstraint, "getGrooveStart", GetGrooveStart)
        HAS_METHOD(PhysicsConstraint, "getGrooveEnd", GetGrooveEnd)
        HAS_METHOD(PhysicsConstraint, "setGroove", SetGroove)
        HAS_METHOD(PhysicsConstraint, "getMinAngle", GetMinAngle)
        HAS_METHOD(PhysicsConstraint, "getMaxAngle", GetMaxAngle)
        HAS_METHOD(PhysicsConstraint, "setAngleLimits", SetAngleLimits)
        HAS_METHOD(PhysicsConstraint, "disconnect", Disconnect)
    );
    END
%#undef PHYSICSCONSTRAINT_SAVE_WEAK

METHOD_IMPL(PhysicsConstraint, IsActive)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isActive()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, IsBroken)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isBroken()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetCollideBodies)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->getCollideBodies()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetType)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getType()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetMaxForce)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMaxForce()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetBreakForce)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getBreakForce()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetImpulse)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getImpulse()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetForce)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getForce()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetCollideBodies)
    METHOD_SIGNATURE("Allow contacts between connected endpoints.", [this], 1, (boolean value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,value); self->setCollideBodies(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetMaxForce)
    METHOD_SIGNATURE("Set the maximum constraint force or torque.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setMaxForce(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetBreakForce)
    METHOD_SIGNATURE("Choose the force or torque that breaks this constraint.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setBreakForce(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetBodyA)
    METHOD_SIGNATURE("", [object PhysicsBody&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->getBodyA(); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetBodyB)
    METHOD_SIGNATURE("", [object PhysicsBody&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->getBodyB(); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
// Read coordinates once and reject coercion/defaulting by the legacy Point converter.
%#ifdef PDG_USING_JAVASCRIPT_CORE
%#define CONSTRAINT_VALUE_MISSING(value) (!(value) || (exception && *exception))
%#else
%#define CONSTRAINT_VALUE_MISSING(value) ((value).IsEmpty())
%#endif
#define REQUIRE_CONSTRAINT_POINT_ARG(n, name) \
    if(!VALUE_IS_OBJECT(ARGV[n-1])) { THROW_TYPE_ERR("Expected a Point"); RETURN_NULL; } \
    auto name##_object=VAL2OBJ(ARGV[n-1]); \
    auto name##_x=OBJECT_GET_PROPERTY(name##_object,SYMBOL(x)); \
    if(CONSTRAINT_VALUE_MISSING(name##_x)) { RETURN_NULL; } \
    auto name##_y=OBJECT_GET_PROPERTY(name##_object,SYMBOL(y)); \
    if(CONSTRAINT_VALUE_MISSING(name##_y)) { RETURN_NULL; } \
    if(!VALUE_IS_NUMBER(name##_x) || !VALUE_IS_NUMBER(name##_y) || \
       !std::isfinite(VAL2NUM(name##_x)) || !std::isfinite(VAL2NUM(name##_y))) { \
        THROW_TYPE_ERR("Expected finite Point coordinates"); RETURN_NULL; \
    } \
    pdg::Point name(VAL2NUM(name##_x),VAL2NUM(name##_y))
METHOD_IMPL(PhysicsConstraint, GetAnchorA)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getAnchorA(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetAnchorB)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getAnchorB(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAnchorA)
    METHOD_SIGNATURE("Move the connection point on body A.", [this], 1, ([object Point const&] anchor));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CONSTRAINT_POINT_ARG(1,anchor); self->setAnchorA(anchor); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAnchorB)
    METHOD_SIGNATURE("Move the connection point on body B.", [this], 1, ([object Point const&] anchor));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CONSTRAINT_POINT_ARG(1,anchor); self->setAnchorB(anchor); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAnchors)
    METHOD_SIGNATURE("Move both connection points atomically.", [this], 2, ([object Point const&] anchorA, [object Point const&] anchorB));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_CONSTRAINT_POINT_ARG(1,a); REQUIRE_CONSTRAINT_POINT_ARG(2,b); self->setAnchors(a,b); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetGrooveStart)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getGrooveStart(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetGrooveEnd)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getGrooveEnd(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetGroove)
    METHOD_SIGNATURE("Move both endpoints of a groove joint's track atomically.", [this], 2, ([object Point const&] start, [object Point const&] end));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_CONSTRAINT_POINT_ARG(1,a); REQUIRE_CONSTRAINT_POINT_ARG(2,b); self->setGroove(a,b); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
#undef REQUIRE_CONSTRAINT_POINT_ARG
%#undef CONSTRAINT_VALUE_MISSING
METHOD_IMPL(PhysicsConstraint, GetMinAngle)
    METHOD_SIGNATURE("rotary-limit angle in radians", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMinAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetMaxAngle)
    METHOD_SIGNATURE("rotary-limit angle in radians", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMaxAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAngleLimits)
    METHOD_SIGNATURE("Change both bounds of a rotary-limit constraint.", [this], 2, (number minAngle, number maxAngle));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_NUMBER_ARG(1,lo); REQUIRE_NUMBER_ARG(2,hi); self->setAngleLimits(lo,hi); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, Disconnect)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->disconnect(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

} // namespace pdg
