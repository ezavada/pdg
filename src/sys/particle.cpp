#include "pdg/sys/particle.h"
#include <numbers>
#include "particletrail.h"
#include "pdg/sys/particleemitter.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/drawing.h"
#include "pdg/sys/image.h"
#include "pdg/sys/events.h"
#include "pdg/sys/attributes.h"
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace pdg {
namespace {
// Register the pure configuration value so named scripts remain portable.
[[maybe_unused]] const bool trailCodecRegistered=[] {
    registerAnimationValueCodec({typeid(ParticleTrailOptions), "pdg.ParticleTrailOptions.v1",
        [](const std::any& value, ISerializer* writer, bool writing) {
            const auto& o=std::any_cast<const ParticleTrailOptions&>(value);o.validate();
            uint32 size=0;
            for(double n : {o.lifetime,double(o.width),double(o.endWidth),double(o.endOpacity),o.minDistance,o.sampleInterval,o.breakDistance,double(o.maxPoints)}) {
                size+=writer->sizeof_d(n);if(writing)writer->serialize_d(n);
            }
            size+=writer->sizeof_color(o.color);if(writing)writer->serialize_color(o.color);return size;
        },
        [](IDeserializer* reader)->std::any {
            ParticleTrailOptions o;
            o.lifetime=reader->deserialize_d();o.width=reader->deserialize_d();o.endWidth=reader->deserialize_d();o.endOpacity=reader->deserialize_d();
            o.minDistance=reader->deserialize_d();o.sampleInterval=reader->deserialize_d();o.breakDistance=reader->deserialize_d();
            const double count=reader->deserialize_d();
            if(!std::isfinite(count) || count<2 || count>4096 || std::floor(count)!=count)throw std::runtime_error("Invalid serialized trail capacity");
            o.maxPoints=static_cast<uint32>(count);o.color=reader->deserialize_color();o.validate();return o;
        }});
    return true;
}();
void nonnegative(double value, const char* name) {
    if (!std::isfinite(value) || value < 0) throw std::invalid_argument(name);
}
template<class T> struct Hold {
    T* value;
    explicit Hold(T* p, bool managed = true) : value(managed ? p : nullptr) { if (value) value->addRef(); }
    ~Hold() { if (value) value->release(); }
};
#ifdef PDG_USE_CHIPMUNK_PHYSICS
// A particle owns only a body, with no Sprite or rig adapter.
class ParticleBodySolver final : public PhysicsBody::Solver {
    cpBody* body;
public:
    explicit ParticleBodySolver(cpSpace* space) : body(cpBodyNew(1, 1)) {
        if (cpSpaceIsLocked(space)) { cpBodyFree(body); throw std::logic_error("Create bodies outside locked physics callbacks"); }
        cpSpaceAddBody(space, body);
    }
    ~ParticleBodySolver() override {
        auto* space = cpBodyGetSpace(body);
        if (space && cpSpaceIsLocked(space)) {
            cpSpaceAddPostStepCallback(space, [](cpSpace* world, void* key, void*) {
                auto* b = static_cast<cpBody*>(key); cpSpaceRemoveBody(world, b); cpBodyFree(b);
            }, body, nullptr);
        } else { if (space) cpSpaceRemoveBody(space, body); cpBodyFree(body); }
    }
    void* nativeBody() const override { return body; }
    PhysicsBodyState readState() const override {
        auto p = cpBodyGetPosition(body), v = cpBodyGetVelocity(body);
        return {p.x, p.y, cpBodyGetAngle(body), v.x, v.y, cpBodyGetAngularVelocity(body)};
    }
    void writeState(const PhysicsBodyState& state) override {
        auto before = readState();
        bool moved = before.x != state.x || before.y != state.y || before.rotation != state.rotation;
        if (moved) { cpBodySetPosition(body, cpv(state.x, state.y)); cpBodySetAngle(body, state.rotation); }
        if (cpBodyGetType(body) != CP_BODY_TYPE_STATIC) {
            if (before.velocityX != state.velocityX || before.velocityY != state.velocityY)
                cpBodySetVelocity(body, cpv(state.velocityX, state.velocityY));
            if (before.angularVelocity != state.angularVelocity) cpBodySetAngularVelocity(body, state.angularVelocity);
        }
        if (moved) if (auto* space = cpBodyGetSpace(body))
            if (!cpSpaceIsLocked(space)) cpSpaceReindexShapesForBody(space, body);
    }
    void addForce(double x, double y, double torque) override {
        if (x != 0 || y != 0) cpBodySetForce(body, cpvadd(cpBodyGetForce(body), cpv(x, y)));
        if (torque != 0) cpBodySetTorque(body, cpBodyGetTorque(body)+torque);
    }
    void configure(const PhysicsBody& settings) override {
        auto type = settings.getMode() == physicsBody_Static ? CP_BODY_TYPE_STATIC :
            settings.getMode() == physicsBody_Kinematic ? CP_BODY_TYPE_KINEMATIC : CP_BODY_TYPE_DYNAMIC;
        if (cpBodyGetType(body) != type) {
            if (cpSpaceIsLocked(cpBodyGetSpace(body))) throw std::logic_error("Change body modes outside locked physics callbacks");
            cpBodySetType(body, type);
        }
        if (type == CP_BODY_TYPE_DYNAMIC) { cpBodySetMass(body, settings.getMass()); cpBodySetMoment(body, settings.getMomentOfInertia()); }
    }
};
#endif
}

Particle::Particle() {
    mWidth = mHeight = 1;
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mParticleScriptObj);
#endif
}
Particle::~Particle() { removeParticleEmitter(); removeCollider(); removePhysicsBody(); }
Particle& Particle::setLifetime(double seconds) {
    if(recordOperation("setLifetime", captureAnimationArguments(seconds))) return *this;
    nonnegative(seconds, "Particle lifetime must be finite and nonnegative"); mLifetime = seconds; return *this;
}
Particle& Particle::setOpacity(float opacity) {
    if(recordOperation("setOpacity", captureAnimationArguments(opacity))) return *this;
    validateUnrecordedOperation("Particle opacity command");
    validateImmediateOperation();
    if (!std::isfinite(opacity) || opacity < 0 || opacity > 1) throw std::invalid_argument("Opacity must be between zero and one");
    cancelAnimation(&mOpacity); mOpacity = opacity; return *this;
}
Particle& Particle::fadeTo(float opacity, double seconds, EasingFunc easing) {
    if(recordOperation("fadeTo", captureAnimationArguments(opacity, seconds, easing))) return *this;
    validateUnrecordedOperation("Particle opacity command");
    validateAnimationDuration(seconds);
    if (!std::isfinite(opacity) || opacity < 0 || opacity > 1 || !easing) throw std::invalid_argument("Invalid opacity or easing");
    beginAnimationRequest(); scheduleAnimation(&mOpacity, opacity, seconds, easing); finishAnimationRequest(); return *this;
}
std::vector<const float*> Particle::tweenFields() const {
    auto result = AnimatedBase::tweenFields(); result.push_back(&mOpacity); return result;
}
Particle& Particle::setDrawing(const Drawing& drawing) {
    if(recordOperation("setDrawing", captureAnimationArguments(drawing))) return *this;
    auto content = drawing.share(); auto bounds = content->getBounds();
    setSize(bounds.width(), bounds.height()); mDrawing = std::move(content); return *this;
}
Particle& Particle::setImage(const Image& image) {
    if(recordOperation("setImage", captureAnimationArguments(image))) return *this;
#ifndef PDG_NO_GUI
    auto content = std::shared_ptr<Drawing>(Drawing::create());
    auto& source = const_cast<Image&>(image);
    Rect bounds(0, 0, source.getWidth(), source.getHeight());
    std::unique_ptr<ElementRef> element(content->addImage(bounds, image, Attributes()));
    return setDrawing(*content);
#else
    throw std::logic_error("Particle image content requires a GUI build");
#endif
}
Particle& Particle::clearContent() {
    if(recordOperation("clearContent", captureAnimationArguments())) return *this;
    mDrawing.reset();
    return *this;
}
SpatialTransform Particle::transform() const {
    auto result = SpatialTransform::fromTRS(mLocation.x + mCenterOffset.x, mLocation.y + mCenterOffset.y, mFacing, mScaleX, mScaleY);
    result.tx -= result.a*mCenterOffset.x + result.c*mCenterOffset.y;
    result.ty -= result.b*mCenterOffset.x + result.d*mCenterOffset.y;
    return result;
}
void Particle::locationChanged(const Offset&) {
    if(mTrail && !mTrailStepping)mTrail->reset(mLocation,mOpacity);
    animationValuesChanged();
}
void Particle::rotationChanged(float) { animationValuesChanged(); }
void Particle::centerChanged(const Offset&) { animationValuesChanged(); }
void Particle::animationValuesChanged() {
    if (physics.isPresent()) physics->setOwnerTransform(mLocation + mCenterOffset, mFacing);
}
void Particle::validateProgrammedTransform() const {
    if (physics.isPresent() && physics.getMode() == physicsBody_Dynamic)
        throw std::logic_error("Dynamic motion belongs to PhysicsBody; use physics velocity/forces or change its mode before programming movement/spin");
}
PhysicsBody& Particle::setupPhysicsBody(double mass, double inertia) {
    if (physics.isPresent()) { physics->configureMass(mass, inertia); return physics; }
    auto body = std::make_unique<PhysicsBody>(mass, inertia);
    body->teleport(mLocation + mCenterOffset, mFacing);
    body->setPublisher([this](const PhysicsBodyState& state) {
        if (physics.getMode() == physicsBody_Dynamic) cancelProgrammedMotion();
        mLocation = Point(state.x - mCenterOffset.x, state.y - mCenterOffset.y); mFacing = state.rotation;
    });
    body->setWorldProvider([this]() -> const void* { return mLayer; });
    body->mBreakPublisher = [this](const PhysicsBodyBreakInfo& info) {
        Hold<Particle> retained(this, refs > 0);
        postEvent(eventType_ParticleBreak, const_cast<PhysicsBodyBreakInfo*>(&info));
    };
    body->addRef(); physics.mBody = body.release();
    try { syncPhysicsSolver(); } catch (...) { removePhysicsBody(); throw; }
    cancelProgrammedMotion(); return physics;
}
void Particle::removePhysicsBody() {
    if (!physics.isPresent()) return;
    auto* old = physics.mBody;
    old->disconnect(); old->setOwnerPolicy({}, {}); old->setPublisher({}); old->detachSolver();
    physics.mBody = &PhysicsBody::NoPhysics; old->release();
}
void Particle::syncPhysicsSolver() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (!physics.isPresent()) return;
    if (mLayer && mAlive && mLayer->mUseChipmunkPhysics) {
        if (physics.getSolver() != physicsSolver_Chipmunk)
            physics->attachSolver(std::make_unique<ParticleBodySolver>(mLayer->getSpace()));
    } else if (physics.getSolver() == physicsSolver_Chipmunk) physics->detachSolver();
#endif
}
Collider& Particle::setupCollider() {
    if (collider.isPresent()) return collider;
    auto result = std::make_unique<Collider>();
    result->attach([this] { return transform(); }, [this]() -> PhysicsBody& { return physics; },
                   [this]() -> const void* { return mLayer; });
    result->setEventSink([this](const ColliderContact& contact) {
        Hold<Particle> retained(this, refs > 0);
        postEvent(eventType_ColliderContact, const_cast<ColliderContact*>(&contact));
    });
    result->addRef(); collider.mCollider = result.release(); return collider;
}
void Particle::removeCollider() {
    if (!collider.isPresent()) return;
    auto* old = collider.mCollider; collider.mCollider = &Collider::NoCollider; old->detach(); old->release();
}
ParticleEmitter& Particle::setupParticleEmitter() {
    if (!emitter.mEmitter) { emitter.mEmitter = new ParticleEmitter(); emitter.mEmitter->addRef(); emitter.mEmitter->mParticle = this; }
    return *emitter.mEmitter;
}
void Particle::removeParticleEmitter() {
    if (!emitter.mEmitter) return;
    auto* old = emitter.mEmitter; emitter.mEmitter = nullptr; old->mParticle = nullptr; old->stopEmitting(); old->release();
}
void ParticleTrailOptions::validate() const {
    nonnegative(lifetime,"Trail lifetime must be positive and finite");
    nonnegative(sampleInterval,"Trail sample interval must be positive and finite");
    nonnegative(width,"Trail width must be nonnegative and finite");
    nonnegative(endWidth,"Trail end width must be nonnegative and finite");
    nonnegative(minDistance,"Trail minimum distance must be nonnegative and finite");
    nonnegative(breakDistance,"Trail break distance must be nonnegative and finite");
    if(lifetime<=0 || sampleInterval<.0001 || maxPoints<2 || maxPoints>4096)
        throw std::invalid_argument("Trail requires positive lifetime, sampleInterval >= 0.0001, and 2..4096 maxPoints");
    for(float value : {endOpacity,color.red,color.green,color.blue,color.alpha})
        if(!std::isfinite(value) || value<0 || value>1)throw std::invalid_argument("Trail colors and opacity must be in [0,1]");
}
Particle& Particle::setTrail(const ParticleTrailOptions& options) {
    options.validate();
    if(recordOperation("setTrail",captureAnimationArguments(options)))return *this;
    auto trail=std::make_unique<ParticleTrail>(options);
    trail->reset(mLocation,mOpacity);mTrail=std::move(trail);return *this;
}
Particle& Particle::clearTrail() {
    if(recordOperation("clearTrail",captureAnimationArguments()))return *this;
    mTrail.reset();return *this;
}
Particle& Particle::breakTrail() {
    if(recordOperation("breakTrail",captureAnimationArguments()))return *this;
    if(mTrail)mTrail->reset(mLocation,mOpacity);
    return *this;
}
uint32 Particle::getTrailPointCount() const { return mTrail && !mTrail->empty() ? static_cast<uint32>(mTrail->count) : 0; }
void Particle::expire() {
    if (!mAlive) return;
    Hold<Particle> retained(this, refs > 0); mAlive = false; mTrailStepping=false;
    if (emitter.mEmitter) emitter.mEmitter->stopEmitting();
    if (mLayer) {
        if(mTrail)mLayer->retireParticleTrail(std::move(mTrail));
        mLayer->removeParticle(this);
    }
    else { mTrail.reset(); if (physics.isPresent()) physics.disconnect(); if (collider.isPresent()) collider->syncNative(nullptr); syncPhysicsSolver(); }
}
void Particle::advance(double seconds) {
    mFrameSeconds=seconds;
    mStepSeconds = mAlive ? (mLifetime > 0 ? std::min(seconds, std::max(0.0, mLifetime - mAge)) : seconds) : 0;
    if (!mAlive) return;
    if(mTrail && !mTrail->initialized)mTrail->reset(mLocation,mOpacity);
    mTrailStepping=true;
    try {
    if (emitter.mEmitter && mStepSeconds > 0) emitter.mEmitter->beginStep();
    if (physics.isPresent()) physics->beginKinematicStep();
    AnimatedBase::animate(mStepSeconds);
    if (physics.isPresent() && physics.getSolver() == physicsSolver_Basic) {
        physics->prepareKinematicStep(mStepSeconds); physics->step(mStepSeconds); physics->finishKinematicStep();
    }
    mAge += mStepSeconds;
    } catch (...) { mTrailStepping=false; throw; }
}
void Particle::finishTrailStep() {
    if(!mTrailStepping)return;
    mTrailStepping=false;
    if(mTrail && mAlive) {
        mTrail->advance(mStepSeconds,mLocation,mOpacity);
        mTrail->age(std::max(0.0,mFrameSeconds-mStepSeconds));
    }
}
void Particle::finish() {
    finishTrailStep();
    if (!mAlive) return;
    if (emitter.mEmitter && mStepSeconds > 0 && mLayer) {
        Hold<ParticleEmitter> retained(emitter.mEmitter); emitter.mEmitter->advance(mStepSeconds);
    }
    if (mLifetime > 0 && mAge >= mLifetime) expire();
    mStepSeconds = 0;
}
bool Particle::animate(double seconds) {
    nonnegative(seconds, "Particle step must be finite and nonnegative");
    if (mLayer) throw std::logic_error("Layer-owned particles advance with their layer");
    Hold<Particle> retained(this, refs > 0); advance(seconds); finish(); return mAlive;
}
std::shared_ptr<Particle> Particle::snapshot() const {
    auto* copy = new Particle(); copy->addRef();
    std::shared_ptr<Particle> result(copy, [](Particle* p) { p->release(); });
    copy->mDrawing = mDrawing; copy->mLifetime = mLifetime;
    if(mTrail)copy->mTrail=std::make_unique<ParticleTrail>(mTrail->options);
    if (physics.isPresent()) {
        auto& b = copy->setupPhysicsBody(physics.getMass(), physics.getMomentOfInertia());
        const auto& source = *physics.operator->();
        b.setMode(source.getMode()).setLinearDamping(source.getLinearDamping()).setAngularDamping(source.getAngularDamping())
            .setFriction(source.getFriction()).setRestitution(source.getRestitution()).setAngularVelocity(source.getAngularVelocity());
        b.setBreakAngularSpeed(source.getBreakAngularSpeedReference() ? 0 : source.getBreakAngularSpeed());
        b.mForces = source.mForces; b.mNextForce = source.mNextForce;
        b.mDrive = source.mDrive;
        b.mDrive.forceX = b.mDrive.forceY = b.mDrive.torque = 0;
    }
    if (collider.isPresent()) {
        auto& c = copy->setupCollider(); const auto& source = *collider.operator->();
        c.mShapes = source.shapes(); c.mNextShape = source.mNextShape;
        c.mEnabled = source.mEnabled; c.mSensor = source.mSensor;
        c.mCategory = source.mCategory; c.mMask = source.mMask; c.mGroup = source.mGroup;
        c.mFriction = source.mFriction; c.mRestitution = source.mRestitution;
        c.mWantsContactEvents = source.mWantsContactEvents;
    }
    copy->copyAnimationStateFrom(*this);
    copy->animationValuesChanged();
    if (emitter.mEmitter) copy->setupParticleEmitter().copyConfiguration(*emitter.mEmitter);
    return result;
}
void Particle::place(const Point& point, double rotation, const Vector& velocity) {
    if (!std::isfinite(point.x) || !std::isfinite(point.y) || !std::isfinite(rotation) ||
        !std::isfinite(velocity.x) || !std::isfinite(velocity.y))
        throw std::invalid_argument("Emission transform and velocity exceed the supported coordinate range");
    for (auto& a : mAnimations) {
        double offset = 0;
        if (a.spawnRelative && a.value == &mLocation.x) offset = point.x - mLocation.x;
        if (a.spawnRelative && a.value == &mLocation.y) offset = point.y - mLocation.y;
        if (a.relativeRotation && !a.resolveRotation && a.value == &mFacing) offset = rotation - mFacing;
        a.beginVal += offset; a.targetVal += offset;
    }
    rebaseScriptState(point-mLocation,static_cast<float>(rotation-mFacing));
    mLocation = point; mFacing = rotation;
    if (physics.isPresent()) {
        physics->teleport(point + mCenterOffset, rotation); physics->setVelocity(velocity);
    } else { mDeltaXPerMs = velocity.x / 1000; mDeltaYPerMs = velocity.y / 1000; }
}
void Particle::draw() {
#ifndef PDG_NO_GUI
    if (!mLayer || !mAlive || !mLayer->getSpritePort()) return;
    if(mTrail)drawParticleTrail(*mLayer->getSpritePort(),*mTrail,mLayer->getViewTransform());
    if (!mDrawing || mOpacity <= 0) return;
    if (!mLayer->getSpritePort()) return;
    Port::ScreenDrawingScope screenDrawing(*mLayer->getSpritePort());
    auto bounds = mDrawing->getBounds();
    const double sx = bounds.width() ? mWidth / bounds.width() : 1;
    const double sy = bounds.height() ? mHeight / bounds.height() : 1;
    auto root = transform();
    auto point = [&](double x, double y) {
        x = (x - (bounds.left + bounds.right) * .5) * sx;
        y = (y - (bounds.top + bounds.bottom) * .5) * sy;
        if (mFlipX) x = -x; if (mFlipY) y = -y;
        return mLayer->layerToPort(root.transformPoint(Point(x, y)));
    };
    auto o = point(0, 0), x = point(1, 0), y = point(0, 1);
    glm::mat3 matrix(1); matrix[0] = glm::vec3(x.x-o.x,x.y-o.y,0);
    matrix[1] = glm::vec3(y.x-o.x,y.y-o.y,0); matrix[2] = glm::vec3(o.x,o.y,1);
    Attributes attributes; attributes.setTransform(matrix).lineOpacity(mOpacity).fillOpacity(mOpacity);
    mDrawing->drawTransformed(mLayer->getSpritePort(), attributes, true);
#endif
}

ParticleEmitter::ParticleEmitter() {
    setSeed(mSeed);
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mParticleEmitterScriptObj);
#endif
}
ParticleEmitter& ParticleEmitter::setParticleTemplate(const Particle& particle) {
    if(recordOperation("setParticleTemplate", captureAnimationArguments(particle))) return *this;
    mTemplate = particle.snapshot(); return *this;
}
ParticleEmitter& ParticleEmitter::setEmissionRate(double rate) {
    if(recordOperation("setEmissionRate", captureAnimationArguments(rate))) return *this;
    nonnegative(rate, "Emission rate must be finite and nonnegative"); mRate = rate; return *this;
}
ParticleEmitter& ParticleEmitter::setParticleSpeed(double minimum, double maximum) {
    if(recordOperation("setParticleSpeed", captureAnimationArguments(minimum, maximum))) return *this;
    nonnegative(minimum, "Particle speed must be finite and nonnegative");
    nonnegative(maximum, "Particle speed must be finite and nonnegative");
    if (minimum > maximum) throw std::invalid_argument("Minimum particle speed exceeds maximum");
    mMinSpeed = minimum; mMaxSpeed = maximum; return *this;
}
ParticleEmitter& ParticleEmitter::setSpread(double radians) {
    if(recordOperation("setSpread", captureAnimationArguments(radians))) return *this;
    nonnegative(radians, "Spread must be finite and nonnegative");
    if (radians > 2 * std::numbers::pi) throw std::invalid_argument("Spread cannot exceed a full turn");
    mSpread = radians; return *this;
}
ParticleEmitter& ParticleEmitter::setVelocityInheritance(double fraction) {
    if(recordOperation("setVelocityInheritance", captureAnimationArguments(fraction))) return *this;
    nonnegative(fraction, "Velocity inheritance must be finite and nonnegative"); mInheritance = fraction; return *this;
}
ParticleEmitter& ParticleEmitter::setSeed(uint32_t seed) {
    if(recordOperation("setSeed", captureAnimationArguments(seed))) return *this;
    mSeed = seed;
    mRandom = uint64_t(seed) + 1;
    return *this;
}
double ParticleEmitter::randomUnit() {
    mRandom = mRandom * UINT64_C(6364136223846793005) + UINT64_C(1442695040888963407);
    return double(mRandom >> 32) / 4294967296.0;
}
ParticleEmitter& ParticleEmitter::startEmitting() {
    if(recordOperation("startEmitting", captureAnimationArguments())) return *this;
    mEmitting = true;
    return *this;
}
ParticleEmitter& ParticleEmitter::stopEmitting() {
    if(recordOperation("stopEmitting", captureAnimationArguments())) return *this;
    mEmitting = false;
    mRemainder = 0;
    return *this;
}
SpriteLayer* ParticleEmitter::getLayer() const { return mParticle ? mParticle->getLayer() : mLayer; }
Point ParticleEmitter::worldPosition() const { return mParticle ? mParticle->transform().transformPoint(mLocation) : mLocation; }
void ParticleEmitter::beginStep() { mStepOrigin = worldPosition(); mHaveStepOrigin = true; }
void ParticleEmitter::copyConfiguration(const ParticleEmitter& source) {
    copyAnimationStateFrom(source); mTemplate = source.mTemplate;
    mRate = source.mRate; mMinSpeed = source.mMinSpeed; mMaxSpeed = source.mMaxSpeed;
    mSpread = source.mSpread; mInheritance = source.mInheritance;
    mEmitting = source.mEmitting; mRemainder = 0; setSeed(source.mSeed);
}
uint32_t ParticleEmitter::emit(uint32_t count) {
    if (!count) return 0;
    auto* layer = getLayer();
    if (!layer || !mTemplate) throw std::logic_error("Emission requires a layer and particle template");
    if (mParticle && !mParticle->isAlive()) return 0;
    count = std::min<uint32_t>(count, layer->getMaxParticles() > layer->getParticleCount() ?
        layer->getMaxParticles() - layer->getParticleCount() : 0);
    Point position = mLocation; double facing = mFacing;
    Vector inherited(getMovement());
    if (mParticle) {
        auto frame = mParticle->transform(); position = frame.transformPoint(mLocation);
        facing = std::atan2(frame.b*std::cos(mFacing) + frame.d*std::sin(mFacing),
                            frame.a*std::cos(mFacing) + frame.c*std::sin(mFacing));
        auto velocity = mParticle->physics.isPresent() ? mParticle->physics.getVelocity() : Vector(mParticle->getMovement());
        const double omega = mParticle->physics.isPresent() ? mParticle->physics.getAngularVelocity() : mParticle->getSpin();
        const auto offset = position - (mParticle->getLocation() + mParticle->getCenterOffset());
        inherited = Vector(velocity.x - omega * offset.y + frame.a*inherited.x + frame.c*inherited.y,
                           velocity.y + omega * offset.x + frame.b*inherited.x + frame.d*inherited.y);
    }
    if (mUseStepVelocity) inherited = mStepVelocity;
    for (uint32_t i = 0; i < count; ++i) {
        double angle = facing + (randomUnit() - .5) * mSpread;
        double speed = mMinSpeed + randomUnit() * (mMaxSpeed - mMinSpeed);
        auto particle = mTemplate->snapshot();
        particle->place(position, angle, Vector(std::cos(angle)*speed + inherited.x*mInheritance,
                                               std::sin(angle)*speed + inherited.y*mInheritance));
        layer->addParticle(particle.get());
    }
    return count;
}
void ParticleEmitter::advance(double seconds) {
    if (!mHaveStepOrigin) beginStep();
    AnimatedBase::animate(seconds);
    const auto end = worldPosition();
    mStepVelocity = seconds > 0 ? Vector((end.x-mStepOrigin.x)/seconds, (end.y-mStepOrigin.y)/seconds) : Vector();
    mHaveStepOrigin = false;
    if (!mEmitting || !mTemplate || !getLayer() || seconds == 0) return;
    const long double amount = mRemainder + static_cast<long double>(seconds) * mRate;
    const auto whole = std::floor(amount + 1e-12L);
    mRemainder = double(std::max(0.0L, amount - whole));
    if (whole > 0) {
        mUseStepVelocity = true;
        try { emit(static_cast<uint32_t>(std::min(whole, static_cast<long double>(UINT32_MAX)))); }
        catch (...) { mUseStepVelocity = false; throw; }
        mUseStepVelocity = false;
    }
}
bool ParticleEmitter::animate(double seconds) {
    nonnegative(seconds, "Emitter step must be finite and nonnegative");
    if (getLayer()) throw std::logic_error("Layer-owned emitters advance with their layer");
    AnimatedBase::animate(seconds); return mEmitting;
}
}

namespace pdg {
#include "animation-operations-particle.inc"
}

namespace pdg {
#include "animation-operations-particleemitter.inc"
}
