#include "snapshot-codec.h"
#include "pdg/sys/physicsbody.h"
#include "physics-snapshot-scope.h"
#include "physics-scaling.h"
#include "pdg/sys/physicsconstraint.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <mutex>
#include <set>
#include <stdexcept>
#include <string>

namespace pdg {
namespace {
void finite(double value) {
    if (!std::isfinite(value)) throw std::invalid_argument("Physical values must be finite");
}
void nonnegative(double value) { finite(value); if (value < 0) throw std::invalid_argument("Expected a nonnegative physical value or seconds duration"); }
void positive(double value) { finite(value); if (value <= 0) throw std::invalid_argument("Mass and moment of inertia must be positive"); }
void integrate(double& position, double& velocity, double acceleration, double damping, double seconds) {
    const double h = damping * seconds;
    // Stable analytic solution to dv/dt = acceleration - damping*velocity.
    double velocityArea, accelerationArea;
    if (std::abs(h) < 1e-4) {
        velocityArea = seconds * (1 - h/2 + h*h/6 - h*h*h/24);
        accelerationArea = seconds*seconds * (0.5 - h/6 + h*h/24 - h*h*h/120);
    } else {
        velocityArea = -std::expm1(-h) / damping;
        accelerationArea = (seconds - velocityArea) / damping;
    }
    position += velocity * velocityArea + acceleration * accelerationArea;
    velocity = velocity * std::exp(-h) + acceleration * velocityArea;
}
void valid(const PhysicsBodyState& state) {
    finite(state.x); finite(state.y); finite(state.rotation);
    finite(state.velocityX); finite(state.velocityY); finite(state.angularVelocity);
}
}
PhysicsBody::PhysicsBody(double mass, double inertia) : mMass(mass), mInertia(inertia) {
    positive(mass); positive(inertia);
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mPhysicsBodyScriptObj);
#endif
}
PhysicsBody::PhysicsBody(AbsentTag) : mMode(physicsBody_None), mMass(0), mInertia(0) {
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mPhysicsBodyScriptObj);
#endif
}
PhysicsBody::~PhysicsBody() { clearBreakReferences(); disconnect(); clearSolverObservers(); }
void PhysicsBody::clearSolverObservers() {
    auto observers=std::move(mSolverObservers);mSolverObservers.clear();
    for(auto& entry:observers)entry.second();
}
PhysicsBodyState PhysicsBody::getState() const { return mSolver ? mSolver->readState() : mState; }
void PhysicsBody::syncState() { mState = getState(); }
void PhysicsBody::commitState(bool publish) {
    if (mSolver) mSolver->writeState(mState);
    if (publish && mPublish) mPublish(mState);
}
void PhysicsBody::configureSolver() { if (mSolver) mSolver->configure(*this); }
void PhysicsBody::attachSolver(std::unique_ptr<Solver> solver) {
    if (!isPresent()) throw std::logic_error("NoPhysics cannot acquire a solver");
    syncState(); clearSolverObservers(); mSolver = std::move(solver); configureSolver(); commitState(false);
}
void PhysicsBody::detachSolver() {
    clearSolverObservers();
    syncState();
    // A post-step callback may remove the owner before the manager restores
    // a temporary kinematic sweep. Preserve configured velocity on detachment.
    if (mKinematicDriven && mMode == physicsBody_Kinematic) {
        mState.velocityX=mKinematicTarget.velocityX; mState.velocityY=mKinematicTarget.velocityY;
        mState.angularVelocity=mKinematicTarget.angularVelocity;
    }
    mKinematicCaptured=mKinematicDriven=false;
    mSolver.reset();
}
void PhysicsBody::applyContactImpulse(const Vector& impulse, const Point& point) {
    if (mMode != physicsBody_Dynamic) return;
    syncState(); mState.velocityX += impulse.x/mMass; mState.velocityY += impulse.y/mMass;
    mState.angularVelocity += ((point.x-mState.x)*impulse.y-(point.y-mState.y)*impulse.x)/mInertia;
    commitState(false);
}
void PhysicsBody::correctContactPosition(const Vector& delta) {
    if (mMode != physicsBody_Dynamic) return;
    syncState(); mState.x += delta.x; mState.y += delta.y; commitState();
}
PhysicsBody& PhysicsBody::setSpeed(double speed) {
    if (ignores("setSpeed")) return *this;
    nonnegative(speed); return setVelocityInRadians(speed, getMovementDirectionInRadians());
}
PhysicsBody& PhysicsBody::setVelocityInRadians(double speed, double direction) {
    if (ignores("setVelocityInRadians")) return *this;
    nonnegative(speed); finite(direction); return setVelocity(Vector(speed*std::cos(direction),speed*std::sin(direction)));
}
double PhysicsBody::getMovementDirectionInRadians() const {
    const auto s = getState(); return std::atan2(s.velocityY,s.velocityX);
}
PhysicsBody PhysicsBody::NoPhysics(AbsentTag{});
bool PhysicsBody::ignores(const char* operation) const {
    if (isPresent()) return false;
#if !defined(NDEBUG) || defined(PDG_TEST_FORCE_DEBUG_DIAGNOSTICS)
    // Diagnostics belong to the method, never to a shared mutable last owner.
    static std::mutex mutex;
    static std::set<std::string> reported;
    std::lock_guard<std::mutex> lock(mutex);
    if (reported.insert(operation).second)
        std::fprintf(stderr, "PDG NoPhysics: ignored %s; call setupPhysicsBody() first\n", operation);
#else
    (void)operation;
#endif
    return true;
}
PhysicsBody& PhysicsBody::setMode(int mode) {
    if (ignores("setMode")) return *this;
    if (mode < physicsBody_Dynamic || mode > physicsBody_Static) throw std::invalid_argument("Invalid physicsBody mode");
    if (mCoordinateMode) { mCoordinateMode(mode); return *this; }
    if (mDriveController && mode != physicsBody_Dynamic)
        throw std::logic_error("Release the owning animation or Part IK controller before changing its driven body mode");
    if (mValidateMode) mValidateMode(mode);
    syncState();
    const int previousMode = mMode;
    mMode = mode;
    try { configureSolver(); }
    catch (...) { mMode = previousMode; throw; }
    if (mode != physicsBody_Dynamic) { mForces.clear(); mDrive = PhysicsDriveState(); }
    if (mode == physicsBody_Static) mState.velocityX = mState.velocityY = mState.angularVelocity = 0;
    commitState();
    return *this;
}
PhysicsBody& PhysicsBody::teleport(const Point& p, double radians) {
    if (ignores("teleport")) return *this;
    finite(p.x); finite(p.y); finite(radians);
    if (mValidateMotion) mValidateMotion();
    syncState();
    mState.x = p.x; mState.y = p.y; mState.rotation = radians;
    commitState();
    return *this;
}
PhysicsBody& PhysicsBody::setVelocity(const Vector& velocity) {
    if (ignores("setVelocity")) return *this;
    finite(velocity.x); finite(velocity.y);
    if (mValidateMotion) mValidateMotion();
    syncState();
    if (mMode != physicsBody_Static) { mState.velocityX = velocity.x; mState.velocityY = velocity.y; }
    commitState(false);
    return *this;
}
double PhysicsBody::getSpeed() const { const auto state=getState(); return std::hypot(state.velocityX, state.velocityY); }
PhysicsBody& PhysicsBody::setAngularVelocity(double velocity) {
    if (ignores("setAngularVelocity")) return *this;
    finite(velocity); if (mValidateMotion) mValidateMotion();
    syncState(); if (mMode != physicsBody_Static) mState.angularVelocity = velocity;
    commitState(false); return *this;
}
PhysicsBody& PhysicsBody::setBreakAngularSpeed(double speed, PhysicsBody* reference) {
    if (ignores("setBreakAngularSpeed")) return *this;
    nonnegative(speed);
    if (reference && (reference == this || !reference->isPresent() || reference->world() != world()))
        throw std::invalid_argument("Angular-speed reference must be a different present body in the same world");
    if (!speed) reference = nullptr;
    if (speed == mBreakAngularSpeed && reference == mBreakReference) return *this;
    if (reference && reference != mBreakReference) reference->mBreakDependents.push_back(this);
    if (mBreakReference && reference != mBreakReference) {
        auto& list = mBreakReference->mBreakDependents;
        std::erase(list, this);
    }
    mBreakAngularSpeed = speed; mBreakReference = reference;
    mBreakNotified = false; ++mBreakRevision;
    return *this;
}
PhysicsBody& PhysicsBody::setBreakHandler(std::function<void(const PhysicsBodyBreakInfo&)> handler) {
    if (!ignores("setBreakHandler")) mBreakHandler = std::move(handler);
    return *this;
}
void PhysicsBody::clearBreakReferences() {
    if (mBreakReference) setBreakAngularSpeed(0);
    while (!mBreakDependents.empty()) mBreakDependents.back()->setBreakAngularSpeed(0);
}
bool PhysicsBody::sampleBreakAngularSpeed(PhysicsBodyBreakInfo& info) {
    if (!mBreakAngularSpeed) return false;
    if (mBreakReference && mBreakReference->world() != world()) { setBreakAngularSpeed(0); return false; }
    const double speed = std::abs(getAngularVelocity() - (mBreakReference ? mBreakReference->getAngularVelocity() : 0));
    if (speed <= mBreakAngularSpeed) { mBreakNotified = false; return false; }
    if (mBreakNotified) return false;
    info = {this, mBreakReference, speed, mBreakAngularSpeed};
    return true;
}
void PhysicsBody::dispatchBreak(const PhysicsBodyBreakInfo& info) {
    // Mark delivery here, not during batch sampling: a snapshot taken by an
    // earlier callback must not suppress another body's still-pending event.
    mBreakNotified = true;
    // Copy callbacks: an event handler can remove its owner/body or replace itself.
    const auto publish = mBreakPublisher, handler = mBreakHandler;
    if (publish) publish(info);
    if (handler) handler(info);
}
void PhysicsBody::checkBreakAngularSpeeds(const std::vector<PhysicsBody*>& bodies) {
    struct Pending { PhysicsBodyBreakInfo info; uint64_t revision; };
    std::vector<Pending> pending;
    // Sample every body before callbacks can change another body's velocity.
    // Only owner-associated heap bodies enter this world-level path.
    std::vector<std::shared_ptr<PhysicsBody>> retained;
    auto retain = [&](PhysicsBody* body) {
        body->addRef(); retained.emplace_back(body, [](PhysicsBody* b) { b->release(); });
    };
    for (auto* body : bodies) {
        PhysicsBodyBreakInfo info;
        if (!body->sampleBreakAngularSpeed(info)) continue;
        retain(body); if (info.referenceBody) retain(info.referenceBody);
        pending.push_back({info, body->mBreakRevision});
    }
    for (const auto& event : pending) {
        auto* body = event.info.body;
        if (body->isAttached() && body->mBreakRevision == event.revision && !body->mBreakNotified) body->dispatchBreak(event.info);
    }
}
// Explicit mass/inertia changes preserve velocity, not momentum.
// Validate both setup arguments before changing an existing owner-associated body.
void PhysicsBody::configureMass(double mass, double inertia) {
    if (!mAssemblyBodies.empty()) throw std::logic_error("Use physics.setMass() to change an active rig's total mass");
    positive(mass); positive(inertia);
    if (mAssemblyOwner) {
        long double total = mass;
        for (auto* body : mAssemblyOwner->mAssemblyBodies) if (body != this) total += body->mMass;
        positive(double(total));
    }
    const double oldMass = mMass, oldInertia = mInertia;
    mMass = mass; mInertia = inertia;
    try { configureSolver(); }
    catch (...) { mMass = oldMass; mInertia = oldInertia; throw; }
}
double PhysicsBody::getMass() const {
    if (mAssemblyBodies.empty()) return mMass;
    long double total = 0;
    for (auto* body : mAssemblyBodies) total += body->mMass;
    return double(total);
}
double PhysicsBody::getMomentOfInertia() const {
    if (mAssemblyBodies.empty()) return mInertia;
    long double mass=0, x=0, y=0;
    for (auto* body:mAssemblyBodies) {
        const auto s=body->getState(); mass+=body->mMass;
        x+=static_cast<long double>(body->mMass)*s.x; y+=static_cast<long double>(body->mMass)*s.y;
    }
    x/=mass; y/=mass;
    long double result=0;
    for (auto* body:mAssemblyBodies) {
        const auto s=body->getState();
        result+=body->mInertia+body->mMass*((s.x-x)*(s.x-x)+(s.y-y)*(s.y-y));
    }
    finite(double(result)); return double(result);
}
double PhysicsBody::getAngularMomentum() const {
    if (mAssemblyBodies.empty()) return mInertia*getAngularVelocity();
    long double mass=0, x=0, y=0, vx=0, vy=0;
    for (auto* body:mAssemblyBodies) {
        const auto s=body->getState(); mass+=body->mMass;
        x+=static_cast<long double>(body->mMass)*s.x; y+=static_cast<long double>(body->mMass)*s.y;
        vx+=static_cast<long double>(body->mMass)*s.velocityX; vy+=static_cast<long double>(body->mMass)*s.velocityY;
    }
    x/=mass; y/=mass; vx/=mass; vy/=mass;
    long double result=0;
    for (auto* body:mAssemblyBodies) {
        const auto s=body->getState();
        result+=static_cast<long double>(body->mInertia)*s.angularVelocity+
            body->mMass*((s.x-x)*(s.velocityY-vy)-(s.y-y)*(s.velocityX-vx));
    }
    finite(double(result)); return double(result);
}
void PhysicsBody::configureAssemblyMasses(const std::vector<double>& masses) {
    if (masses.size() != mAssemblyBodies.size()) throw std::invalid_argument("Invalid assembly mass distribution");
    std::vector<double> moments;
    moments.reserve(masses.size());
    long double total = 0;
    for (size_t i = 0; i < masses.size(); ++i) {
        positive(masses[i]); total += masses[i];
        double inertia = scaledPhysicalValue(mAssemblyBodies[i]->mInertia, masses[i], mAssemblyBodies[i]->mMass);
        positive(inertia); moments.push_back(inertia);
    }
    positive(double(total));
    // All values are checked before any component changes. Solver configure for
    // these edits only updates mass/moment; it does not change mode or topology.
    std::vector<std::pair<double,double>> old;
    for (auto* body : mAssemblyBodies) old.emplace_back(body->mMass,body->mInertia);
    try {
        for (size_t i = 0; i < masses.size(); ++i) {
            auto* body=mAssemblyBodies[i];body->mMass=masses[i];body->mInertia=moments[i];body->configureSolver();
        }
    } catch (...) {
        for (size_t i=0;i<old.size();++i) { auto* body=mAssemblyBodies[i];body->mMass=old[i].first;body->mInertia=old[i].second;body->configureSolver(); }
        throw;
    }
}
PhysicsBody& PhysicsBody::setMass(double mass) {
    if (ignores("setMass")) return *this;
    positive(mass);
    if (!mAssemblyBodies.empty()) {
        const double total = getMass();
        std::vector<double> masses;
        for (auto* body : mAssemblyBodies) masses.push_back(scaledPhysicalValue(body->mMass,mass,total));
        configureAssemblyMasses(masses);
    } else configureMass(mass, scaledPhysicalValue(mInertia,mass,mMass));
    return *this;
}
PhysicsBody& PhysicsBody::setMomentOfInertia(double inertia) {
    if (ignores("setMomentOfInertia")) return *this;
    if (!mAssemblyBodies.empty()) throw std::logic_error("Set moment of inertia on individual rig components");
    configureMass(mMass, inertia); return *this;
}
PhysicsBody& PhysicsBody::setLinearDamping(double value) { if (ignores("setLinearDamping")) return *this; nonnegative(value); mLinearDamping = value; return *this; }
PhysicsBody& PhysicsBody::setAngularDamping(double value) { if (ignores("setAngularDamping")) return *this; nonnegative(value); mAngularDamping = value; return *this; }
PhysicsBody& PhysicsBody::setFriction(double value) { if (ignores("setFriction")) return *this; nonnegative(value); mFriction = value; configureSolver(); return *this; }
PhysicsBody& PhysicsBody::setRestitution(double value) { if (ignores("setRestitution")) return *this; nonnegative(value); if (value > 1) throw std::invalid_argument("Restitution must be at most 1"); mRestitution = value; configureSolver(); return *this; }
PhysicsBody& PhysicsBody::applyImpulse(const Vector& impulse) {
    if (ignores("applyImpulse")) return *this;
    finite(impulse.x); finite(impulse.y);
    if (mAssemblyRoot) { mAssemblyRoot->applyImpulse(impulse); return *this; }
    if (mMode != physicsBody_Dynamic) return *this;
    syncState();
    auto next = mState;
    next.velocityX += impulse.x / mMass; next.velocityY += impulse.y / mMass;
    valid(next); mState = next; commitState(false); return *this;
}
PhysicsBody& PhysicsBody::applyImpulse(const Vector& impulse, const Point& point) {
    if (ignores("applyImpulseAtPoint")) return *this;
    finite(impulse.x); finite(impulse.y); finite(point.x); finite(point.y);
    if (mAssemblyRoot) { mAssemblyRoot->applyImpulse(impulse, point); return *this; }
    if (mMode != physicsBody_Dynamic) return *this;
    syncState();
    auto next = mState;
    next.velocityX += impulse.x / mMass; next.velocityY += impulse.y / mMass;
    next.angularVelocity += ((point.x - mState.x)*impulse.y - (point.y - mState.y)*impulse.x) / mInertia;
    valid(next); mState = next; commitState(false); return *this;
}
PhysicsBody& PhysicsBody::applyAngularImpulse(double impulse) {
    if (ignores("applyAngularImpulse")) return *this;
    finite(impulse);
    if (mAssemblyRoot) { mAssemblyRoot->applyAngularImpulse(impulse); return *this; }
    if (mMode != physicsBody_Dynamic) return *this;
    syncState();
    const double velocity = mState.angularVelocity + impulse / mInertia;
    finite(velocity); mState.angularVelocity = velocity; commitState(false); return *this;
}
PhysicsForceId PhysicsBody::addLoad(double x, double y, double torque, double seconds, double delay) {
    finite(x); finite(y); finite(torque); nonnegative(delay);
    if (seconds != -1) nonnegative(seconds); // Private sentinel; public continuous operations are explicit.
    if (seconds == 0 || (mAssemblyRoot ? mAssemblyRoot->mMode : mMode) != physicsBody_Dynamic) return physicsForce_None;
    if (mNextForce == physicsForce_None) throw std::overflow_error("Physical force ID space exhausted");
    mForces.push_back({mNextForce,x,y,torque,seconds,delay}); return mNextForce++;
}
PhysicsForceId PhysicsBody::applyForce(const Vector& force, double seconds, double delay) {
    if (ignores("applyForce")) return physicsForce_None;
    nonnegative(seconds); return addLoad(force.x,force.y,0,seconds,delay);
}
PhysicsForceId PhysicsBody::applyForce(const Vector& force, const Point& point, double seconds, double delay) {
    if (ignores("applyForceAtPoint")) return physicsForce_None;
    nonnegative(seconds); finite(point.x); finite(point.y); syncState();
    const auto origin=mAssemblyRoot ? mAssemblyRoot->getState() : mState;
    return addLoad(force.x,force.y,(point.x-origin.x)*force.y - (point.y-origin.y)*force.x,seconds,delay);
}
PhysicsForceId PhysicsBody::applyTorque(double torque, double seconds, double delay) {
    if (ignores("applyTorque")) return physicsForce_None;
    nonnegative(seconds); return addLoad(0,0,torque,seconds,delay);
}
PhysicsForceId PhysicsBody::addContinuousForce(const Vector& force) {
    if (ignores("addContinuousForce")) return physicsForce_None;
    return addLoad(force.x,force.y,0,-1,0);
}
PhysicsForceId PhysicsBody::addContinuousTorque(double torque) {
    if (ignores("addContinuousTorque")) return physicsForce_None;
    return addLoad(0,0,torque,-1,0);
}
bool PhysicsBody::removeForce(PhysicsForceId id) {
    if (ignores("removeForce")) return false;
    const auto old = mForces.size();
    std::erase_if(mForces, [id](const Force& force){return force.id==id;});
    return old != mForces.size();
}
PhysicsBody& PhysicsBody::stopAllForces() { if (ignores("stopAllForces")) return *this; if (mDriveController) throw std::logic_error("Release the owning animation or Part IK controller before stopping its physical drive"); mForces.clear(); mDrive = PhysicsDriveState(); return *this; }
PhysicsBody& PhysicsBody::setDriveTarget(const Point& position, double radians, double maxForce,
        double maxTorque, double frequency, double dampingRatio, int direction) {
    if (ignores("setDriveTarget")) return *this;
    if (mDriveController) throw std::logic_error("An animation or Part IK controller owns this drive; explicitly release it first");
    return setDriveTargetImpl(position,radians,maxForce,maxTorque,frequency,dampingRatio,direction);
}
PhysicsBody& PhysicsBody::setDriveTargetImpl(const Point& position, double radians, double maxForce,
    double maxTorque, double frequency, double dampingRatio, int direction) {
    finite(position.x); finite(position.y); finite(radians);
    nonnegative(maxForce); nonnegative(maxTorque); nonnegative(frequency); nonnegative(dampingRatio);
    if (frequency == 0) throw std::invalid_argument("Drive frequency must be positive");
    const double omega = 6.28318530717958647692 * frequency;
    finite(omega * omega); finite(2 * dampingRatio * omega);
    if (direction < rotationDirection_AsSpecified || direction > rotationDirection_CounterClockwise)
        throw std::invalid_argument("Expected an integer rotationDirection constant");
    if (mMode != physicsBody_Dynamic)
        throw std::logic_error("Physical drives require a dynamic body");
    if (mValidateMotion) mValidateMotion();
    const double angle = getState().rotation, turn = 6.28318530717958647692;
    double route = radians - angle;
    if (direction != rotationDirection_AsSpecified) {
        route = std::fmod(route, turn);
        if (direction == rotationDirection_Clockwise && route < 0) route += turn;
        if (direction == rotationDirection_CounterClockwise && route > 0) route -= turn;
        if (direction == rotationDirection_Shortest) {
            if (route > turn/2) route -= turn;
            if (route <= -turn/2) route += turn;
        }
    }
    finite(route); finite(angle + route);
    PhysicsDriveState drive;
    drive.enabled = true; drive.x = position.x; drive.y = position.y; drive.rotation = angle + route;
    drive.maxForce = maxForce; drive.maxTorque = maxTorque;
    drive.frequency = frequency; drive.dampingRatio = dampingRatio;
    mDrive = drive;
    return *this;
}
PhysicsBody& PhysicsBody::clearDrive() {
    if (mDriveController) throw std::logic_error("Release the owning animation or Part IK controller to release its physical drives");
    if (!ignores("clearDrive")) mDrive = PhysicsDriveState();
    return *this;
}
PhysicsDriveState PhysicsBody::getDriveState() const {
    auto drive = mDrive;
    if (drive.enabled) {
        const auto state = getState();
        drive.positionError = std::hypot(drive.x-state.x, drive.y-state.y);
        drive.rotationError = drive.rotation-state.rotation;
    }
    return drive;
}
void PhysicsBody::step(double seconds) {
    if (mSolver) throw std::logic_error("A Chipmunk body advances with its world");
    integrateStep(seconds, true);
    if (seconds > 0 && !world()) {
        PhysicsBodyBreakInfo info;
        if (sampleBreakAngularSpeed(info)) {
            struct Retained {
                PhysicsBody* body;
                explicit Retained(PhysicsBody* value) : body(value && value->isAttached() ? value : nullptr) { if (body) body->addRef(); }
                ~Retained() { if (body) body->release(); }
            } source(this), reference(info.referenceBody);
            dispatchBreak(info);
        }
    }
}
// Owner transforms are already published in AnimatedBase. Do not echo them back
// through its publisher, or interpret an internal mount target as a caller edit.
void PhysicsBody::setOwnerTransform(const Point& p, double radians) {
    if (!isPresent()) return;
    finite(p.x); finite(p.y); finite(radians);
    syncState(); mState.x=p.x; mState.y=p.y; mState.rotation=radians;
    commitState(false);
}
void PhysicsBody::beginKinematicStep() {
    mKinematicCaptured = mSolver && mMode == physicsBody_Kinematic;
    mKinematicDriven = false;
    if (mKinematicCaptured) mKinematicStart = getState();
}
void PhysicsBody::prepareKinematicStep(double seconds) {
    if (!mKinematicCaptured || !mSolver || mMode != physicsBody_Kinematic || seconds <= 0) return;
    mKinematicTarget = getState();
    const auto& a=mKinematicStart; const auto& b=mKinematicTarget;
    if (a.x==b.x && a.y==b.y && a.rotation==b.rotation) return;
    // Sweep to the programmed target during the solve. Contacts see the actual
    // target velocity; configured free velocity resumes after the target step.
    mState=a;
    mState.velocityX=(b.x-a.x)/seconds; mState.velocityY=(b.y-a.y)/seconds;
    mState.angularVelocity=(b.rotation-a.rotation)/seconds;
    valid(mState); mKinematicDriven=true; commitState(false);
}
void PhysicsBody::finishKinematicStep() {
    if (mKinematicDriven && mSolver && mMode==physicsBody_Kinematic) {
        mState=mKinematicTarget; commitState(false);
    }
    mKinematicCaptured=mKinematicDriven=false;
}
void PhysicsBody::publishWorldStep() { syncState(); if (mPublish) mPublish(mState); }
void PhysicsBody::prepareWorldStep(double seconds) { if (mSolver) integrateStep(seconds, false); }
void PhysicsBody::integrateStep(double seconds, bool move) {
    if (!isPresent()) return;
    nonnegative(seconds);
    // The assembly keeps the public IDs and lifetimes. Only its selected root
    // consumes them, once per step, alongside that body's independent loads.
    if (mAssemblyRoot) return;
    auto* assembly=mAssemblyOwner && mAssemblyOwner->mAssemblyRoot==this ? mAssemblyOwner : nullptr;
    syncState();
    auto next = mState; auto loads = mForces; auto drive = mDrive;
    auto assemblyLoads=assembly ? assembly->mForces : std::vector<Force>();
    const double driveStep = std::max(1.0/120.0, seconds/4096.0);
    double remaining = seconds;
    while (remaining > 0) {
        double dt = drive.enabled ? std::min(remaining, driveStep) : remaining;
        double x = 0, y = 0, torque = 0;
        auto accumulate=[&](const std::vector<Force>& pending) { for (const auto& force : pending) {
            if (force.delay > 0) dt = std::min(dt, force.delay);
            else {
                if (force.remaining >= 0) dt = std::min(dt, force.remaining);
                x += force.x; y += force.y; torque += force.torque;
            }
        }};
        accumulate(loads); accumulate(assemblyLoads);
        if (drive.enabled && !mRigDrive) {
            // Implicit spring/damper feedback avoids explosive high-stiffness
            // updates. Clamp the drive contribution before adding independent loads.
            const double omega = 6.28318530717958647692 * drive.frequency;
            const double stiffness = omega * omega, damping = 2 * drive.dampingRatio * omega;
            const double denominator = 1 + damping*dt + stiffness*dt*dt;
            drive.forceX = mMass * (stiffness*(drive.x-next.x) - damping*next.velocityX) / denominator;
            drive.forceY = mMass * (stiffness*(drive.y-next.y) - damping*next.velocityY) / denominator;
            const double magnitude = std::hypot(drive.forceX, drive.forceY);
            if (magnitude > drive.maxForce) {
                drive.forceX *= drive.maxForce/magnitude; drive.forceY *= drive.maxForce/magnitude;
            }
            drive.torque = std::clamp(mInertia * (stiffness*(drive.rotation-next.rotation)
                - damping*next.angularVelocity) / denominator, -drive.maxTorque, drive.maxTorque);
            finite(drive.forceX); finite(drive.forceY); finite(drive.torque);
            x += drive.forceX; y += drive.forceY; torque += drive.torque;
        }
        if (mMode == physicsBody_Dynamic) {
            integrate(next.x,next.velocityX,x/mMass,mLinearDamping,dt);
            integrate(next.y,next.velocityY,y/mMass,mLinearDamping,dt);
            integrate(next.rotation,next.angularVelocity,torque/mInertia,mAngularDamping,dt);
        } else if (mMode == physicsBody_Kinematic) {
            next.x += next.velocityX*dt; next.y += next.velocityY*dt; next.rotation += next.angularVelocity*dt;
        }
        auto advance=[&](std::vector<Force>& pending) { for (auto& force : pending) {
            if (force.delay > 0) force.delay = std::max(0.0, force.delay-dt);
            else if (force.remaining >= 0) force.remaining = std::max(0.0,force.remaining-dt);
        }
        std::erase_if(pending, [](const Force& force){return force.remaining == 0;});
        };
        advance(loads); advance(assemblyLoads);
        remaining = std::max(0.0,remaining-dt);
    }
    valid(next);
    if (!move) {
        if (mMode == physicsBody_Dynamic && seconds > 0) {
            // Let the world apply continuous loads during its velocity solve.
            // Writing these velocities before Chipmunk integrates positions
            // stretches joints on every tick, before constraints can react.
            // Preserve the integrated impulse (including damping and timed
            // loads) while adding to any forces supplied by rig controllers.
            mSolver->addForce(mMass*(next.velocityX-mState.velocityX)/seconds,
                mMass*(next.velocityY-mState.velocityY)/seconds,
                mInertia*(next.angularVelocity-mState.angularVelocity)/seconds);
            next.velocityX=mState.velocityX; next.velocityY=mState.velocityY;
            next.angularVelocity=mState.angularVelocity;
        }
        next.x=mState.x; next.y=mState.y; next.rotation=mState.rotation;
    }
    mState = next; mForces = std::move(loads); mDrive = drive;
    if (assembly) assembly->mForces=std::move(assemblyLoads);
    commitState(move);
}

uint32 PhysicsBody::getSerializedSize(ISerializer* ser) const { return snapshotRecord(ser,false); }
void PhysicsBody::serialize(ISerializer* ser) const { snapshotRecord(ser,true); }
uint32 PhysicsBody::snapshotRecord(ISerializer* ser, bool emit) const {
    if(mBreakHandler) throw std::runtime_error("Body snapshots cannot save break callbacks");
    if(mBreakReference && !PhysicsSnapshotScope::contains(ser, this)) throw std::runtime_error("Relative angular-speed thresholds require graph snapshots");
    if(mDriveController && !PhysicsSnapshotScope::contains(ser, this))throw std::runtime_error("Controlled physics bodies require controller graph snapshots");
    if(!mConstraints.empty() && !PhysicsSnapshotScope::contains(ser, this))throw std::runtime_error("Physics constraints require graph snapshots");
    SnapshotWriter out(ser,emit);
    out.byte(mMode); if (!isPresent()) return out.size();
    out.byte(2); // compact body record; all numeric payloads remain doubles
    const auto state=getState();
    out.real(mMass,1);out.real(mInertia,1);
    for (double value : {mLinearDamping,mAngularDamping,mFriction,mRestitution,
         state.x,state.y,state.rotation,state.velocityX,state.velocityY,state.angularVelocity}) out.real(value);
    if (out.flag(mDrive.enabled)) for (double value : {mDrive.x,mDrive.y,mDrive.rotation,mDrive.maxForce,
        mDrive.maxTorque,mDrive.frequency,mDrive.dampingRatio,mDrive.forceX,mDrive.forceY,mDrive.torque}) out.real(value);
    out.real(mBreakAngularSpeed); if (mBreakAngularSpeed) out.flag(mBreakNotified);
    out.optionalInteger(mNextForce,1);out.integer(mForces.size());
    for (const auto& load:mForces) {
        out.integer(load.id);
        for (double value:{load.x,load.y,load.torque}) out.real(value);
        out.real(load.remaining,-1);out.real(load.delay);
    }
    return out.size();
}
void PhysicsBody::deserialize(IDeserializer* des, int mode) {
    if (!isPresent()) throw std::logic_error("Cannot deserialize into NoPhysics");
    if (mDriveController || mCoordinateMode) throw std::logic_error("Release the owning animation or Part IK controller before restoring its body state");
    if(mode<0) mode=des->deserialize_1u();
    if (mode<physicsBody_Dynamic || mode>physicsBody_Static) throw std::runtime_error("Invalid physical body mode");
    if (mValidateMode) mValidateMode(mode);
    if (mValidateMotion) mValidateMotion();
    const auto revision = des->deserialize_1u();
    if (revision < 1 || revision > 2) throw std::runtime_error("Unsupported compact body record");
    SnapshotReader in(des);
    PhysicsBody replacement;
    replacement.setMass(in.real(1)); replacement.setMomentOfInertia(in.real(1));
    replacement.setLinearDamping(in.real()); replacement.setAngularDamping(in.real());
    replacement.setFriction(in.real()); replacement.setRestitution(in.real());
    auto& state=replacement.mState;
    state.x=in.real();state.y=in.real();state.rotation=in.real();
    state.velocityX=in.real();state.velocityY=in.real();state.angularVelocity=in.real();valid(state);
    const bool driven = in.flag();
    if (driven) {
        if (mode != physicsBody_Dynamic) throw std::runtime_error("Only dynamic bodies may have drives");
        const double x=in.real(), y=in.real(), rotation=in.real();
        const double force=in.real(), torque=in.real();
        const double frequency=in.real(), damping=in.real();
        replacement.setDriveTarget(Point(x,y),rotation,force,torque,frequency,damping,rotationDirection_AsSpecified);
        auto& drive = replacement.mDrive;
        drive.forceX=in.real(); drive.forceY=in.real(); drive.torque=in.real();
        finite(drive.forceX); finite(drive.forceY); finite(drive.torque);
        if (std::hypot(drive.forceX,drive.forceY) > drive.maxForce*(1+1e-12) || std::abs(drive.torque)>drive.maxTorque)
            throw std::runtime_error("Invalid physical drive load");
    }
    if (revision >= 2) {
        replacement.setBreakAngularSpeed(in.real());
        if (replacement.mBreakAngularSpeed) replacement.mBreakNotified = in.flag();
    }
    const auto nextForce=in.optionalInteger(1);
    const auto count=des->deserialize_uint();
    if(count>1000000) throw std::runtime_error("Invalid physical load count");
    for(uint32 i=0;i<count;++i) {
        const auto id=des->deserialize_uint();
        const double x=in.real(),y=in.real(),torque=in.real();
        const double remaining=in.real(-1),delay=in.real();
        if(!id || (nextForce && id>=nextForce) || remaining==0 ||
           std::any_of(replacement.mForces.begin(),replacement.mForces.end(),[&](const Force& force){return force.id==id;}))
            throw std::runtime_error("Invalid physical load ID or duration");
        replacement.addLoad(x,y,torque,remaining,delay);
        replacement.mForces.back().id=id;

    }
    setBreakAngularSpeed(replacement.mBreakAngularSpeed);
    mBreakNotified=replacement.mBreakNotified;
    mMass=replacement.mMass;mInertia=replacement.mInertia;mLinearDamping=replacement.mLinearDamping;
    mAngularDamping=replacement.mAngularDamping;mFriction=replacement.mFriction;mRestitution=replacement.mRestitution;
    mMode=mode;mState=state;mDrive=replacement.mDrive;mForces=std::move(replacement.mForces);mNextForce=nextForce;
    configureSolver();commitState();
}
}

#include "physicsconstraint.inc"
