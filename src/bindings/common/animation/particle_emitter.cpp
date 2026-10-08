// -----------------------------------------------
// particle_emitter.cpp
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
%#include <cmath>
%#include <limits>

namespace pdg {

%#ifdef PDG_USING_JAVASCRIPT_CORE
static void ParticleEmitter_finalize(JSObjectRef object) {
    auto* value=static_cast<ParticleEmitter*>(JSObjectGetPrivate(object)); if (!value) return;
    value->mParticleEmitterScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mISerializableScriptObj=nullptr;
    JSObjectSetPrivate(object,nullptr); value->release();
}
%#define PARTICLEEMITTER_SAVE(cppObj,obj) cppObj->mParticleEmitterScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mISerializableScriptObj=obj
%#else
%#define PARTICLEEMITTER_SAVE(cppObj,obj) cppObj->mParticleEmitterScriptObj.Reset(isolate,obj); cppObj->mParticleEmitterScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mISerializableScriptObj.Reset(isolate,obj); cppObj->mISerializableScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(ParticleEmitter, PARTICLEEMITTER_SAVE(cppObj,obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("ParticleEmitter", ParticleEmitter, AnimatedBase, ParticleEmitter_finalize, , ,
        HAS_ANIMATED_METHODS(ParticleEmitter)
        HAS_METHOD(ParticleEmitter, "setParticleTemplate", SetParticleTemplate)
        HAS_METHOD(ParticleEmitter, "hasParticleTemplate", HasParticleTemplate)
        HAS_METHOD(ParticleEmitter, "setEmissionRate", SetEmissionRate)
        HAS_METHOD(ParticleEmitter, "getEmissionRate", GetEmissionRate)
        HAS_METHOD(ParticleEmitter, "setParticleSpeed", SetParticleSpeed)
        HAS_METHOD(ParticleEmitter, "getMinParticleSpeed", GetMinParticleSpeed)
        HAS_METHOD(ParticleEmitter, "getMaxParticleSpeed", GetMaxParticleSpeed)
        HAS_METHOD(ParticleEmitter, "setSpread", SetSpread)
        HAS_METHOD(ParticleEmitter, "getSpread", GetSpread)
        HAS_METHOD(ParticleEmitter, "setVelocityInheritance", SetVelocityInheritance)
        HAS_METHOD(ParticleEmitter, "getVelocityInheritance", GetVelocityInheritance)
        HAS_METHOD(ParticleEmitter, "setSeed", SetSeed)
        HAS_METHOD(ParticleEmitter, "getSeed", GetSeed)
        HAS_METHOD(ParticleEmitter, "startEmitting", StartEmitting)
        HAS_METHOD(ParticleEmitter, "stopEmitting", StopEmitting)
        HAS_METHOD(ParticleEmitter, "isEmitting", IsEmitting)
        HAS_METHOD(ParticleEmitter, "emit", Emit)
        HAS_METHOD(ParticleEmitter, "getLayer", GetLayer)
        HAS_METHOD(ParticleEmitter, "getParticle", GetParticle)
        HAS_METHOD(ParticleEmitter, "animate", Animate)
    );
    END
ANIMATED_BASE_CLASS_IMPL(ParticleEmitter)
CLEANUP_IMPL(ParticleEmitter)
%#ifdef PDG_USING_JAVASCRIPT_CORE
ParticleEmitter* New_ParticleEmitter(SCRIPT_ARGS) { return new ParticleEmitter(); }
%#else
ParticleEmitterWrap::ParticleEmitterWrap(SCRIPT_ARGS) : cppPtr_(New_ParticleEmitter(args)) {}
ParticleEmitterWrap::~ParticleEmitterWrap() { if (cppPtr_) { cppPtr_->mParticleEmitterScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr; } }
ParticleEmitter* New_ParticleEmitter(SCRIPT_ARGS) {
    if (s_ParticleEmitter_InNewFromCpp) return nullptr;
    auto* isolate=args.GetIsolate(); auto* cppObj=new ParticleEmitter(); cppObj->addRef();
    PARTICLEEMITTER_SAVE(cppObj,args.This()); return cppObj;
}
%#endif
%#undef PARTICLEEMITTER_SAVE
METHOD_IMPL(ParticleEmitter, HasParticleTemplate)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasParticleTemplate()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetEmissionRate)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getEmissionRate()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetMinParticleSpeed)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMinParticleSpeed()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetMaxParticleSpeed)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMaxParticleSpeed()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetSpread)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getSpread()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetVelocityInheritance)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getVelocityInheritance()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetSeed)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getSeed()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, IsEmitting)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isEmitting()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, Animate)
    METHOD_SIGNATURE("advance a detached object in simulation seconds", boolean, 1, (number seconds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seconds); RETURN_BOOL(self->animate(seconds)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetLayer)
    METHOD_SIGNATURE("", [object SpriteLayer*], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getLayer(); RETURN_CPP_OBJECT(result,SpriteLayer); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetEmissionRate)
    METHOD_SIGNATURE("Set the continuous emission rate.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setEmissionRate(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetSpread)
    METHOD_SIGNATURE("Set the full angular emission spread.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setSpread(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetVelocityInheritance)
    METHOD_SIGNATURE("Set initial velocity inheritance.", [this], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setVelocityInheritance(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetParticleTemplate)
    METHOD_SIGNATURE("Capture the configuration for future emissions.", [this], 1, ([object Particle const&] particle));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,particle,Particle); self->setParticleTemplate(*particle); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetParticleSpeed)
    METHOD_SIGNATURE("Set initial particle speed.", [this], 1, (number minimum, number maximum = minimum));
    try { REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1,minimum); OPTIONAL_NUMBER_ARG(2,maximum,minimum); self->setParticleSpeed(minimum,maximum); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, StartEmitting)
    METHOD_SIGNATURE("Enable continuous emission.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->startEmitting(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, StopEmitting)
    METHOD_SIGNATURE("Stop continuous emission.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->stopEmitting(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetSeed)
    METHOD_SIGNATURE("Reset emission randomness.", [this], 1, ([number uint] seed));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seed); if (!std::isfinite(seed) || seed < 0 || seed > UINT32_MAX || std::floor(seed) != seed) throw std::invalid_argument("Expected uint32 seed"); self->setSeed(static_cast<uint32_t>(seed)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, Emit)
    METHOD_SIGNATURE("", number, 0, ([number uint] count = 1));
    try { OPTIONAL_NUMBER_ARG(1,count,1); if (!std::isfinite(count) || count < 0 || count > UINT32_MAX || std::floor(count) != count) throw std::invalid_argument("Expected uint32 count"); RETURN_UINT32(self->emit(static_cast<uint32_t>(count))); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetParticle)
    METHOD_SIGNATURE("", [object Particle*], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getParticle(); RETURN_CPP_OBJECT(result,Particle); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

} // namespace pdg

/* @pdg-member
{
  "name": "ParticleEmitter.ParticleEmitter",
  "type": "constructor",
  "params": [],
  "returns": "object ParticleEmitter",
  "brief": "Create a ParticleEmitter instance."
}
*/
