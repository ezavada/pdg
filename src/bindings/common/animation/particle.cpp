// -----------------------------------------------
// particle.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "animation_impl_macros.h"
#include "../core/core_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>
%#include "../../common/animation/particle_trail_options.h"

namespace pdg {

// Lightweight particles and point emitters.
%#ifdef PDG_USING_JAVASCRIPT_CORE
static void Particle_finalize(JSObjectRef object) {
    auto* value=static_cast<Particle*>(JSObjectGetPrivate(object)); if (!value) return;
    value->mParticleScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mISerializableScriptObj=nullptr; value->mEventEmitterScriptObj=nullptr;
    JSObjectSetPrivate(object,nullptr); value->release();
}
%#define PARTICLE_SAVE(cppObj,obj) cppObj->mParticleScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mISerializableScriptObj=obj; cppObj->mEventEmitterScriptObj=obj
%#else
%#define PARTICLE_SAVE(cppObj,obj) cppObj->mParticleScriptObj.Reset(isolate,obj); cppObj->mParticleScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mISerializableScriptObj.Reset(isolate,obj); cppObj->mISerializableScriptObj.SetWeak(); cppObj->mEventEmitterScriptObj.Reset(isolate,obj); cppObj->mEventEmitterScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(Particle, PARTICLE_SAVE(cppObj,obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("Particle", Particle, AnimatedBase, Particle_finalize, , ,
        HAS_ANIMATED_METHODS(Particle)
        HAS_EMITTER_METHODS(Particle)
        HAS_METHOD(Particle, "_readPhysics", ReadPhysics)
        HAS_METHOD(Particle, "setupPhysicsBody", SetupPhysicsBody)
        HAS_METHOD(Particle, "removePhysicsBody", RemovePhysicsBody)
        HAS_METHOD(Particle, "_readCollider", ReadCollider)
        HAS_METHOD(Particle, "setupCollider", SetupCollider)
        HAS_METHOD(Particle, "removeCollider", RemoveCollider)
        HAS_METHOD(Particle, "setupParticleEmitter", SetupParticleEmitter)
        HAS_METHOD(Particle, "getParticleEmitter", GetParticleEmitter)
        HAS_METHOD(Particle, "removeParticleEmitter", RemoveParticleEmitter)
        HAS_METHOD(Particle, "setTrail", SetTrail)
        HAS_METHOD(Particle, "clearTrail", ClearTrail)
        HAS_METHOD(Particle, "breakTrail", BreakTrail)
        HAS_METHOD(Particle, "hasTrail", HasTrail)
        HAS_METHOD(Particle, "getTrailPointCount", GetTrailPointCount)
        HAS_METHOD(Particle, "clearContent", ClearContent)
        HAS_METHOD(Particle, "hasContent", HasContent)
        HAS_METHOD(Particle, "setOpacity", SetOpacity)
        HAS_METHOD(Particle, "getOpacity", GetOpacity)
        HAS_METHOD(Particle, "fadeTo", FadeTo)
        HAS_METHOD(Particle, "setLifetime", SetLifetime)
        HAS_METHOD(Particle, "getLifetime", GetLifetime)
        HAS_METHOD(Particle, "getAge", GetAge)
        HAS_METHOD(Particle, "isAlive", IsAlive)
        HAS_METHOD(Particle, "expire", Expire)
        HAS_METHOD(Particle, "getLayer", GetLayer)
        HAS_METHOD(Particle, "animate", Animate)
%#ifndef PDG_NO_GUI CR
        HAS_METHOD(Particle, "setImage", SetImage)
        HAS_METHOD(Particle, "setDrawing", SetDrawing)
%#endif CR
    );
    END
ANIMATED_BASE_CLASS_IMPL(Particle)
EMITTER_BASE_CLASS_IMPL(Particle)
CLEANUP_IMPL(Particle)
%#ifdef PDG_USING_JAVASCRIPT_CORE
Particle* New_Particle(SCRIPT_ARGS) { return new Particle(); }
%#else
ParticleWrap::ParticleWrap(SCRIPT_ARGS) : cppPtr_(New_Particle(args)) {}
ParticleWrap::~ParticleWrap() { if (cppPtr_) { cppPtr_->mParticleScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset(); cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr; } }
Particle* New_Particle(SCRIPT_ARGS) {
    if (s_Particle_InNewFromCpp) return nullptr;
    auto* isolate=args.GetIsolate(); auto* cppObj=new Particle(); cppObj->addRef();
    PARTICLE_SAVE(cppObj,args.This()); return cppObj;
}
%#endif
%#undef PARTICLE_SAVE
METHOD_IMPL(Particle, SetTrail)
    METHOD_SIGNATURE("Configure a bounded, fading ribbon trail; replaces its history.", [this], 1, ([object ParticleTrailOptions const&] options));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_OBJECT_ARG(1,options);
        auto get=[&](const char* name) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
            auto key=JSStringCreateWithUTF8CString(name); auto result=JSObjectGetProperty(ctx,options,key,exception); JSStringRelease(key);
            if(exception && *exception) { throw std::invalid_argument("Unable to read trail option"); } return result;
%#else
            v8::Local<v8::Value> result;
            if(!options->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,name).ToLocalChecked()).ToLocal(&result)) { throw std::invalid_argument("Unable to read trail option"); } return result;
%#endif
        };
        auto number=[&](const char* key,double fallback) { auto value=get(key); if(VALUE_IS_UNDEFINED(value))return fallback; if(!VALUE_IS_NUMBER(value)) { throw std::invalid_argument("Expected numeric trail option"); } return double(VAL2NUM(value)); };
        auto color=[&](Color fallback) {auto value=get("color");if(VALUE_IS_UNDEFINED(value))return fallback; Color result;auto ok=VALUE_IS_COLOR(value,result);if(!ok.has_value() || !*ok) { throw std::invalid_argument("Expected trail Color"); }return result;};
        self->setTrail(readParticleTrailOptions(number,color)); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Particle, ClearTrail)
    METHOD_SIGNATURE("", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->clearTrail(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Particle, BreakTrail)
    METHOD_SIGNATURE("", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->breakTrail(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Particle, HasTrail)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasTrail()); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Particle, GetTrailPointCount)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_UINT32(self->getTrailPointCount()); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Particle, HasContent)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasContent()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetOpacity)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getOpacity()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetLifetime)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getLifetime()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetAge)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getAge()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, IsAlive)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isAlive()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, Animate)
    METHOD_SIGNATURE("advance a detached object in simulation seconds", boolean, 1, (number seconds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seconds); RETURN_BOOL(self->animate(seconds)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetLayer)
    METHOD_SIGNATURE("", [object SpriteLayer*], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getLayer(); RETURN_CPP_OBJECT(result,SpriteLayer); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetOpacity)
    METHOD_SIGNATURE("Set whole-particle opacity.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setOpacity(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetLifetime)
    METHOD_SIGNATURE("Set the lifetime in simulation seconds.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setLifetime(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, ClearContent)
    METHOD_SIGNATURE("Remove the artwork.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->clearContent(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, RemoveCollider)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removeCollider(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, RemovePhysicsBody)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removePhysicsBody(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, RemoveParticleEmitter)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removeParticleEmitter(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, Expire)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->expire(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, ReadPhysics)
    METHOD_SIGNATURE("", [object PhysicsBody&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&static_cast<PhysicsBody&>(self->physics); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetupPhysicsBody)
    METHOD_SIGNATURE("", [object PhysicsBody&], 0, (number mass = 1, number momentOfInertia = 1));
    try { OPTIONAL_NUMBER_ARG(1,mass,1); OPTIONAL_NUMBER_ARG(2,inertia,1); auto* result=&self->setupPhysicsBody(mass,inertia); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, ReadCollider)
    METHOD_SIGNATURE("", [object Collider&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&static_cast<Collider&>(self->collider); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetupCollider)
    METHOD_SIGNATURE("", [object Collider&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupCollider(); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetupParticleEmitter)
    METHOD_SIGNATURE("", [object ParticleEmitter&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupParticleEmitter(); RETURN_CPP_OBJECT(result,ParticleEmitter); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetParticleEmitter)
    METHOD_SIGNATURE("", [object ParticleEmitter*], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getParticleEmitter(); RETURN_CPP_OBJECT(result,ParticleEmitter); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, FadeTo)
    METHOD_SIGNATURE("Schedule a whole-particle fade.", [this], 2, (number opacity, number seconds, [number int] easing = linearTween));
    try { REQUIRE_ARG_MIN_COUNT(2); if (ARGC>3) { REQUIRE_ARG_COUNT(3); } REQUIRE_NUMBER_ARG(1,opacity); REQUIRE_NUMBER_ARG(2,seconds); OPTIONAL_NUMBER_ARG(3,easing,static_cast<int>(EasingFuncRef::linearTween)); if (!std::isfinite(easing) || easing < 0 || easing >= NUM_EASING_FUNCTIONS || std::floor(easing)!=easing) { throw std::invalid_argument("Unknown easing"); } self->fadeTo(opacity,seconds,gEasingFunctions[static_cast<int>(easing)]); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
%#ifndef PDG_NO_GUI
METHOD_IMPL(Particle, SetImage)
    METHOD_SIGNATURE("Assign whole-particle Image artwork.", [this], 1, ([object Image const&] content));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,content,Image); self->setImage(*content); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetDrawing)
    METHOD_SIGNATURE("Assign whole-particle Drawing artwork.", [this], 1, ([object Drawing const&] content));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,content,Drawing); self->setDrawing(*content); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
%#endif

} // namespace pdg

/* @pdg-member
{
  "name": "Particle.Particle",
  "type": "constructor",
  "params": [],
  "returns": "object Particle",
  "brief": "Create a Particle instance."
}
*/

/* @pdg-schema
{
  "name": "ParticleTrailOptions",
  "value": {
    "kind": "record",
    "native_binding": {"type":"pdg::ParticleTrailOptions"},
    "fields": {
      "lifetime": {
        "type": "number",
        "optional": true,
        "description": "History lifetime in simulation seconds (default 0.4)."
      },
      "width": {
        "type": "number",
        "optional": true,
        "description": "Width at the head in layer units (default 6)."
      },
      "endWidth": {
        "type": "number",
        "optional": true,
        "description": "Width at the oldest end (default 0)."
      },
      "endOpacity": {
        "type": "number",
        "optional": true,
        "description": "Opacity multiplier at the oldest end, 0..1 (default 0)."
      },
      "minDistance": {
        "type": "number",
        "optional": true,
        "description": "Minimum distance between stored samples (default 2)."
      },
      "sampleInterval": {
        "type": "number",
        "optional": true,
        "description": "Sampling interval in simulation seconds, at least 0.0001 (default 1/60)."
      },
      "maxPoints": {
        "type": "number",
        "optional": true,
        "description": "History capacity, integer 2..4096 (default 32)."
      },
      "breakDistance": {
        "type": "number",
        "optional": true,
        "description": "Per-step displacement that resets history; 0 disables (default 256)."
      },
      "color": {
        "one_of": [{"type":"object Color"},{"type":"string"},{"type":"number"}],
        "optional": true,
        "description": "Trail color, CSS color name or packed RGBA (default orange)."
      }
    }
  }
}
*/
// @pdg-contract {"name":"Particle.setTrail","value":{"params":{"options":{"schema":"ParticleTrailOptions"}}}}
