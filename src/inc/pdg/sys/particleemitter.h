#ifndef PDG_PARTICLE_EMITTER_H_INCLUDED
#define PDG_PARTICLE_EMITTER_H_INCLUDED

#include "pdg/sys/animated.h"
#include <memory>
#include <cstdint>

namespace pdg {
class Particle;
class SpriteLayer;
/** Point emitter. Facing zero is +X; positive rotation is clockwise.
 * @ingroup Animation
 * Layer factories and Particle::setupParticleEmitter return borrowed references.
 * An owned emitter uses its particle's local frame; emitted particles immediately
 * become independent members of the layer. Templates share artwork, but each
 * emission has independent animation, physics and child-emitter state.
 */
class ParticleEmitter : public Animated<ParticleEmitter> {
    friend class Particle;
    friend class SpriteLayer;
public:
    ParticleEmitter();
    ~ParticleEmitter() override = default;
    ParticleEmitter(const ParticleEmitter&) = delete;
    ParticleEmitter& operator=(const ParticleEmitter&) = delete;
    ParticleEmitter& setParticleTemplate(const Particle& particle);
    bool hasParticleTemplate() const { return bool(mTemplate); }
    ParticleEmitter& setEmissionRate(double particlesPerSecond);
    double getEmissionRate() const { return mRate; }
    ParticleEmitter& setParticleSpeed(double speed) {
        if(recordOperation("setParticleSpeed", captureAnimationArguments(speed))) return *this;
        return setParticleSpeed(speed, speed);
    }
    ParticleEmitter& setParticleSpeed(double minimum, double maximum);
    double getMinParticleSpeed() const { return mMinSpeed; }
    double getMaxParticleSpeed() const { return mMaxSpeed; }
    ParticleEmitter& setSpread(double radians);
    double getSpread() const { return mSpread; }
    ParticleEmitter& setVelocityInheritance(double fraction);
    double getVelocityInheritance() const { return mInheritance; }
    ParticleEmitter& setSeed(uint32_t seed);
    uint32_t getSeed() const { return mSeed; }
    ParticleEmitter& startEmitting();
    ParticleEmitter& stopEmitting();
    bool isEmitting() const { return mEmitting; }
    /// Returns the actual count; capacity overflow is dropped. Requires a layer and template.
    uint32_t emit(uint32_t count = 1);
    SpriteLayer* getLayer() const;
    Particle* getParticle() const { return mParticle; }
    bool animate(double seconds) override;
    /// Emitters are transient; capture their configuration through a Particle template.
    uint32 getMyClassTag() const override { throw std::logic_error("Particle emitters are transient and cannot be serialized"); }
    uint32 getSerializedSize(ISerializer*) const override { return getMyClassTag(); }
    void serialize(ISerializer*) const override { getMyClassTag(); }
    void deserialize(IDeserializer*) override { getMyClassTag(); }
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mParticleEmitterScriptObj;
#endif
private:
    void copyConfiguration(const ParticleEmitter& source);
    void advance(double seconds);
    Point worldPosition() const;
    void beginStep();
    double randomUnit();
    SpriteLayer* mLayer = nullptr;
    Particle* mParticle = nullptr;
    std::shared_ptr<const Particle> mTemplate;
    double mRate = 0, mMinSpeed = 0, mMaxSpeed = 0, mSpread = 0, mInheritance = 0;
    double mRemainder = 0;
    uint32_t mSeed = 1;
    uint64_t mRandom = 1;
    bool mEmitting = false;
    Point mStepOrigin;
    Vector mStepVelocity;
    bool mHaveStepOrigin = false, mUseStepVelocity = false;
};
/** Read-only optional association. Reading it never creates an emitter.
 * @ingroup Animation
 */
class ParticleEmitterRef {
    friend class Particle;
    ParticleEmitter* mEmitter = nullptr;
    ParticleEmitterRef() = default;
public:
    ParticleEmitterRef(const ParticleEmitterRef&) = delete;
    ParticleEmitterRef& operator=(const ParticleEmitterRef&) = delete;
    explicit operator bool() const { return mEmitter != nullptr; }
    ParticleEmitter* operator->() const { return mEmitter; }
    ParticleEmitter* get() const { return mEmitter; }
};
}
#endif
