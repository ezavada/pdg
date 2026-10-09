#ifndef PDG_PARTICLE_H_INCLUDED
#define PDG_PARTICLE_H_INCLUDED

#include "pdg/sys/animated.h"
#include "pdg/sys/eventemitter.h"
#include "pdg/sys/collider.h"
#include "pdg/sys/particleemitter.h"
#include <memory>
#include "pdg/sys/color.h"

namespace pdg {
class Drawing;
class Image;
class SpriteLayer;
class SpriteManager;
class ParticleEmitter;
class ParticleTrail;
/** Solid ribbon settings. Distances are layer units; times are simulation seconds. */
/** Pure ribbon settings, copied by Particle::setTrail and emitter templates.
 * @ingroup Animation
 * See Particle::setTrail for units, validation, and lifetime behavior.
 */
struct ParticleTrailOptions {
    double lifetime = .4;
    float width = 6, endWidth = 0;
    Color color = Color(1.f, .5f, 0.f, 1.f);
    float endOpacity = 0;
    double minDistance = 2, sampleInterval = 1.0/60.0;
    uint32 maxPoints = 32;
    double breakDistance = 256;
    void validate() const;
};

/** Lightweight whole-body artwork, animation and optional physics.
 * @ingroup Animation Physics
 * Layer factories return borrowed references. Retain native references with
 * addRef/release. Detached particles do not automatically advance. Lifetime and
 * animation durations are simulation seconds; zero lifetime disables expiry.
 * Expiry stops the owned emitter and removes the body from the physics world.
 * No parts, subsections, skeletons or attachment points are exposed.
 */
class Particle : public EventEmitter, public Animated<Particle> {
    friend class SpriteLayer;
    friend class SpriteManager;
    friend class ParticleEmitter;
public:
    Particle();
    ~Particle() override;
    Particle(const Particle&) = delete;
    Particle& operator=(const Particle&) = delete;
    PhysicsBodyRef<Particle> physics;
    ColliderRef<Particle> collider;
    ParticleEmitterRef emitter;
    PhysicsBody& setupPhysicsBody(double mass = 1, double momentOfInertia = 1);
    void removePhysicsBody();
    Collider& setupCollider();
    void removeCollider();
    ParticleEmitter& setupParticleEmitter();
    ParticleEmitter* getParticleEmitter() const { return emitter.get(); }
    void removeParticleEmitter();
    /// Configure a ribbon and clear its previous history; no renderer is needed to sample it.
    Particle& setTrail(const ParticleTrailOptions& options);
    Particle& clearTrail();
    /// Break the ribbon at the current position, e.g. when teleporting.
    Particle& breakTrail();
    bool hasTrail() const { return bool(mTrail); }
    uint32 getTrailPointCount() const;
    Particle& setImage(const Image& image);
    Particle& setDrawing(const Drawing& drawing);
    Particle& clearContent();
    bool hasContent() const { return bool(mDrawing); }
    Particle& setOpacity(float opacity);
    float getOpacity() const { return mOpacity; }
    Particle& fadeTo(float opacity, double seconds, EasingFunc easing = linearTween);
    Particle& fadeIn(double seconds, EasingFunc easing = linearTween) {
        if(recordOperation("fadeIn", captureAnimationArguments(seconds,easing))) return *this;
        return fadeTo(1,seconds,easing);
    }
    Particle& fadeOut(double seconds, EasingFunc easing = linearTween) {
        if(recordOperation("fadeOut", captureAnimationArguments(seconds,easing))) return *this;
        return fadeTo(0,seconds,easing);
    }
    Particle& setLifetime(double seconds);
    double getLifetime() const { return mLifetime; }
    double getAge() const { return mAge; }
    bool isAlive() const { return mAlive; }
    void expire();
    SpriteLayer* getLayer() const { return mLayer; }
    /// Explicit stepping is for detached particles; layer-owned ones step with their layer.
    bool animate(double seconds) override;
    /// Particles are transient; effect templates are captured by ParticleEmitter.
    uint32 getMyClassTag() const override { throw std::logic_error("Particles are transient and cannot be serialized"); }
    uint32 getSerializedSize(ISerializer*) const override { return getMyClassTag(); }
    void serialize(ISerializer*) const override { getMyClassTag(); }
    void deserialize(IDeserializer*) override { getMyClassTag(); }
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mParticleScriptObj;
#endif
private:
    std::shared_ptr<Particle> snapshot() const;
    void place(const Point& point, double rotation, const Vector& velocity);
    void advance(double seconds);
    void finish();
    void finishTrailStep();
    void syncPhysicsSolver();
    void draw();
    SpatialTransform transform() const;
    void locationChanged(const Offset&) override;
    void rotationChanged(float) override;
    void centerChanged(const Offset&) override;
    void animationValuesChanged() override;
    void validateProgrammedTransform() const override;
    std::vector<const float*> tweenFields() const override;
    SpriteLayer* mLayer = nullptr;
    std::shared_ptr<Drawing> mDrawing;
    std::unique_ptr<ParticleTrail> mTrail;
    bool mTrailStepping = false;
    float mOpacity = 1;
    double mLifetime = 1, mAge = 0, mStepSeconds = 0, mFrameSeconds = 0;
    bool mAlive = true;
};
}
#endif
