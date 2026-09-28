// Particle browser handles retain native objects independently of layer ownership.
#ifndef PDG_EM_PARTICLES_H
#define PDG_EM_PARTICLES_H
#include "pdg/sys/particle.h"
#include "pdg/sys/particleemitter.h"

#define ParticleLayer_Extra \
    .function("_createParticle", emscripten::optional_override([](pdg::SpriteLayer& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(p.createParticle()); }); })) \
    .function("_createParticleEmitter", emscripten::optional_override([](pdg::SpriteLayer& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(p.createParticleEmitter()); }); })) \
    .function("_getNthParticle", emscripten::optional_override([](pdg::SpriteLayer& p,uint32_t i) { return pdg::browserRetain(p.getNthParticle(i)); })) \
    .function("_addParticle", emscripten::optional_override([](pdg::SpriteLayer& p,std::shared_ptr<pdg::Particle> value) { pdg::browserPartCall([&] { p.addParticle(value.get()); }); })) \
    .function("_removeParticle", emscripten::optional_override([](pdg::SpriteLayer& p,std::shared_ptr<pdg::Particle> value) { pdg::browserPartCall([&] { p.removeParticle(value.get()); }); })) \
    .function("_removeParticleEmitter", emscripten::optional_override([](pdg::SpriteLayer& p,std::shared_ptr<pdg::ParticleEmitter> value) { pdg::browserPartCall([&] { p.removeParticleEmitter(value.get()); }); })) \
    .function("removeAllParticles", &pdg::SpriteLayer::removeAllParticles) \
    .function("removeAllParticleEmitters", &pdg::SpriteLayer::removeAllParticleEmitters) \
    .function("getParticleCount", &pdg::SpriteLayer::getParticleCount) \
    .function("getMaxParticles", &pdg::SpriteLayer::getMaxParticles) \
    .function("_setMaxParticles", emscripten::optional_override([](pdg::SpriteLayer& p,uint32_t n) { p.setMaxParticles(n); }))

EMSCRIPTEN_BINDINGS(pdg_particles) {
    using namespace emscripten; using namespace pdg;
    class_<Particle, base<AnimatedBase>>("Particle")
        .smart_ptr_constructor("ParticleHandle", +[] { return browserRetain(new Particle()); })
        .function("_getNativeIdentity", optional_override([](const Particle& p) { return reinterpret_cast<uintptr_t>(&p); }))
        .function("_getLayerIdentity", optional_override([](const Particle& p) { return reinterpret_cast<uintptr_t>(p.getLayer()); }))
        .function("animate", optional_override([](Particle& p,double seconds) { return browserPartCall([&] { return p.animate(seconds); }); }))
        .function("_addNativeEventBridge", optional_override([](Particle& p,long type,const val& self) { emscriptenEventEmitterAddBridge(p,type,self); }))
        .function("getAge", optional_override([](Particle& p) { return browserPartCall([&] { return p.getAge(); }); }))
        .function("getLifetime", optional_override([](Particle& p) { return browserPartCall([&] { return p.getLifetime(); }); }))
        .function("getOpacity", optional_override([](Particle& p) { return browserPartCall([&] { return p.getOpacity(); }); }))
        .function("isAlive", optional_override([](Particle& p) { return browserPartCall([&] { return p.isAlive(); }); }))
        .function("hasContent", optional_override([](Particle& p) { return browserPartCall([&] { return p.hasContent(); }); }))
        .function("removePhysicsBody", optional_override([](Particle& p) { return browserPartCall([&] { return p.removePhysicsBody(); }); }))
        .function("removeCollider", optional_override([](Particle& p) { return browserPartCall([&] { return p.removeCollider(); }); }))
        .function("removeParticleEmitter", optional_override([](Particle& p) { return browserPartCall([&] { return p.removeParticleEmitter(); }); }))
        .function("expire", optional_override([](Particle& p) { return browserPartCall([&] { return p.expire(); }); }))
        .function("_setOpacity", optional_override([](Particle& p,double v) { browserPartCall([&] { p.setOpacity(v); }); }))
        .function("_setLifetime", optional_override([](Particle& p,double v) { browserPartCall([&] { p.setLifetime(v); }); }))
        .function("_readPhysics", optional_override([](Particle& p) { return browserPartCall([&] { return browserRetain(&static_cast<PhysicsBody&>(p.physics)); }); }))
        .function("_readCollider", optional_override([](Particle& p) { return browserPartCall([&] { return browserRetain(&static_cast<Collider&>(p.collider)); }); }))
        .function("_setupCollider", optional_override([](Particle& p) { return browserPartCall([&] { return browserRetain(&p.setupCollider()); }); }))
        .function("_setupParticleEmitter", optional_override([](Particle& p) { return browserPartCall([&] { return browserRetain(&p.setupParticleEmitter()); }); }))
        .function("_getParticleEmitter", optional_override([](Particle& p) { return browserPartCall([&] { return browserRetain(p.getParticleEmitter()); }); }))
        .function("_setupPhysicsBody", optional_override([](Particle& p,double mass,double inertia) { return browserPartCall([&] { return browserRetain(&p.setupPhysicsBody(mass,inertia)); }); }))
        .function("_fadeTo", optional_override([](Particle& p,float opacity,double seconds,int easing) { browserPartCall([&] {
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Unknown easing");
            p.fadeTo(opacity,seconds,gEasingFunctions[easing]);
        }); }))
        .function("_clearContent", optional_override([](Particle& p) { p.clearContent(); }))
#ifndef PDG_NO_GUI
        .function("_setDrawing", optional_override([](Particle& p,const Drawing& drawing) { browserPartCall([&] { p.setDrawing(drawing); }); }))
        .function("_setImage", optional_override([](Particle& p,const Image& image) { browserPartCall([&] { p.setImage(image); }); }))
#endif
        ;
    class_<ParticleEmitter, base<AnimatedBase>>("ParticleEmitter")
        .smart_ptr_constructor("ParticleEmitterHandle", +[] { return browserRetain(new ParticleEmitter()); })
        .function("_getNativeIdentity", optional_override([](const ParticleEmitter& p) { return reinterpret_cast<uintptr_t>(&p); }))
        .function("_getLayerIdentity", optional_override([](const ParticleEmitter& p) { return reinterpret_cast<uintptr_t>(p.getLayer()); }))
        .function("animate", optional_override([](ParticleEmitter& p,double seconds) { return browserPartCall([&] { return p.animate(seconds); }); }))
        .function("getEmissionRate", &ParticleEmitter::getEmissionRate)
        .function("getMinParticleSpeed", &ParticleEmitter::getMinParticleSpeed)
        .function("getMaxParticleSpeed", &ParticleEmitter::getMaxParticleSpeed)
        .function("getSpread", &ParticleEmitter::getSpread)
        .function("getVelocityInheritance", &ParticleEmitter::getVelocityInheritance)
        .function("getSeed", &ParticleEmitter::getSeed)
        .function("isEmitting", &ParticleEmitter::isEmitting)
        .function("hasParticleTemplate", &ParticleEmitter::hasParticleTemplate)
        .function("_setEmissionRate", optional_override([](ParticleEmitter& p,double value) { browserPartCall([&] { p.setEmissionRate(value); }); }))
        .function("_setSpread", optional_override([](ParticleEmitter& p,double value) { browserPartCall([&] { p.setSpread(value); }); }))
        .function("_setVelocityInheritance", optional_override([](ParticleEmitter& p,double value) { browserPartCall([&] { p.setVelocityInheritance(value); }); }))
        .function("_setSeed", optional_override([](ParticleEmitter& p,uint32_t value) { browserPartCall([&] { p.setSeed(value); }); }))
        .function("_startEmitting", optional_override([](ParticleEmitter& p) { p.startEmitting(); }))
        .function("_stopEmitting", optional_override([](ParticleEmitter& p) { p.stopEmitting(); }))
        .function("_setParticleTemplate", optional_override([](ParticleEmitter& p,const Particle& value) { browserPartCall([&] { p.setParticleTemplate(value); }); }))
        .function("_setParticleSpeed", optional_override([](ParticleEmitter& p,double lo,double hi) { browserPartCall([&] { p.setParticleSpeed(lo,hi); }); }))
        .function("_emit", optional_override([](ParticleEmitter& p,uint32_t count) { return browserPartCall([&] { return p.emit(count); }); }))
        .function("_getParticle", optional_override([](ParticleEmitter& p) { return browserRetain(p.getParticle()); }))
        ;
    constant("eventType_ParticleBreak",eventType_ParticleBreak);
}
#endif
