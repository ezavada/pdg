#ifndef PDG_PHYSICS_BODY_H_INCLUDED
#define PDG_PHYSICS_BODY_H_INCLUDED

#include "pdg/sys/coordinates.h"
#include "pdg/sys/refcounted.h"
#include "pdg/sys/physicsconstraint.h"
#include <cstdint>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

namespace pdg {
class PhysicsConstraint;
class PhysicsBody;
/** Body angular-speed notification, in radians/second. @ingroup Physics */
struct PhysicsBodyBreakInfo {
    PhysicsBody* body = nullptr; ///< Source body, borrowed during the callback.
    PhysicsBody* referenceBody = nullptr; ///< Optional weak reference used for relative speed.
    double angularSpeed = 0; ///< Measured nonnegative speed, in radians/second.
    double breakAngularSpeed = 0; ///< Configured threshold, in radians/second.
};
enum PhysicsBodyMode : int {
    physicsBody_None = 0, physicsBody_Dynamic = 1,
    physicsBody_Kinematic = 2, physicsBody_Static = 3
};
enum PhysicsSolver : int { physicsSolver_None = 0, physicsSolver_Basic = 1, physicsSolver_Chipmunk = 2 };
using PhysicsForceId = uint32_t;
constexpr PhysicsForceId physicsForce_None = 0;

/** Physical state in distance units, radians and seconds. No animation rates.
 * @ingroup Physics
 */
struct PhysicsBodyState {
    double x = 0, y = 0, rotation = 0;
    double velocityX = 0, velocityY = 0, angularVelocity = 0;
};

/** Snapshot of an optional force-limited physical drive.
 * @ingroup Physics
 * Target coordinates are in the owning layer. Rotation is a resolved route in
 * radians, frequency is cycles/second, and dampingRatio is dimensionless.
 * Force/torque are the last applied drive contributions, excluding other loads.
 */
struct PhysicsDriveState {
    bool enabled = false;
    double x = 0, y = 0, rotation = 0;
    double maxForce = 0, maxTorque = 0, frequency = 0, dampingRatio = 0;
    double forceX = 0, forceY = 0, torque = 0;
    double positionError = 0, rotationError = 0;
};

/** Optional physical representation of a Sprite or Part.
 * @ingroup Physics
 * Impulse changes momentum immediately; force integrates over its lifetime in
 * seconds. Torque changes angular momentum over time, using moment of inertia.
 * Zero-duration forces/torques contribute nothing. Positive rotation is clockwise.
 * The basic solver integrates free motion and constant loads analytically,
 * including exponential damping. Contact friction is separate from damping.
 * World-space off-center forces capture their lever arm at submission.
 * In a shared solver, changed kinematic animation targets sweep during the solve;
 * contacts use that target velocity, then configured free velocity resumes.
 * Mounted Sprite bodies reject independent motion and changes out of kinematic
 * mode until detached. Dynamic ownership cancels programmed spatial motion.
 */
class PhysicsBody : public RefCountedObj {
public:
    explicit PhysicsBody(double mass = 1, double momentOfInertia = 1);
    ~PhysicsBody() override;
    PhysicsBody(const PhysicsBody&) = delete;
    PhysicsBody& operator=(const PhysicsBody&) = delete;
    void addRef() const noexcept override { if (isPresent()) RefCountedObj::addRef(); }
    void release() const noexcept override { if (isPresent()) RefCountedObj::release(); }
    static PhysicsBody NoPhysics;
    bool operator==(const PhysicsBody& other) const { return this == &other; }
    bool operator!=(const PhysicsBody& other) const { return !(*this == other); }
    bool isPresent() const { return mMode != physicsBody_None; }
    int getSolver() const { return mSolver ? physicsSolver_Chipmunk : (isPresent() ? physicsSolver_Basic : physicsSolver_None); }
    int getMode() const { return mMode; }
    PhysicsBody& setMode(int mode);
    PhysicsBodyState getState() const;
    PhysicsBody& teleport(const Point& position, double radians);
    Vector getVelocity() const { return Vector(getState().velocityX, getState().velocityY); }
    PhysicsBody& setVelocity(const Vector& velocity);
    double getSpeed() const;
    PhysicsBody& setSpeed(double speed);
    PhysicsBody& setVelocity(double x, double y) { return setVelocity(Vector(x,y)); }
    PhysicsBody& setVelocityInRadians(double speed, double direction);
    double getMovementDirectionInRadians() const;
    PhysicsBody& stopMoving() { return setVelocity(Vector(0,0)); }
    PhysicsBody& stopSpinning() { return setAngularVelocity(0); }
    double getAngularVelocity() const { return getState().angularVelocity; }
    PhysicsBody& setAngularVelocity(double radiansPerSecond);
    /// Notify when absolute (or reference-relative) angular speed exceeds this limit; zero disables.
    PhysicsBody& setBreakAngularSpeed(double radiansPerSecond, PhysicsBody* referenceBody = nullptr);
    double getBreakAngularSpeed() const { return mBreakAngularSpeed; }
    /// Borrow the optional reference body; null means absolute speed.
    PhysicsBody* getBreakAngularSpeedReference() const { return mBreakReference; }
    /// Native callback for bodies without a Sprite owner; callbacks are not serialized.
    PhysicsBody& setBreakHandler(std::function<void(const PhysicsBodyBreakInfo&)> handler);
    /// Assembly momentum includes spin and orbital motion about its center of mass.
    double getAngularMomentum() const;
    double getMass() const;
    PhysicsBody& setMass(double mass);
    /// Assembly inertia is the instantaneous sum about its center of mass.
    double getMomentOfInertia() const;
    PhysicsBody& setMomentOfInertia(double inertia);
    double getLinearDamping() const { return mLinearDamping; }
    PhysicsBody& setLinearDamping(double perSecond);
    double getAngularDamping() const { return mAngularDamping; }
    PhysicsBody& setAngularDamping(double perSecond);
    double getFriction() const { return mFriction; }
    PhysicsBody& setFriction(double coefficient);
    double getRestitution() const { return mRestitution; }
    PhysicsBody& setRestitution(double coefficient);
    PhysicsBody& applyImpulse(const Vector& impulse);
    PhysicsBody& applyImpulse(const Vector& impulse, const Point& worldPoint);
    PhysicsBody& applyAngularImpulse(double impulse);
    PhysicsForceId applyForce(const Vector& force, double durationSeconds, double delaySeconds = 0);
    PhysicsForceId applyForce(const Vector& force, const Point& worldPoint,
                             double durationSeconds, double delaySeconds = 0);
    PhysicsForceId applyTorque(double torque, double durationSeconds, double delaySeconds = 0);
    PhysicsForceId addContinuousForce(const Vector& force);
    PhysicsForceId addContinuousTorque(double torque);
    bool removeForce(PhysicsForceId id);
    PhysicsBody& stopAllForces();
    PhysicsBody& setDriveTarget(const Point& position, double radians, double maxForce,
        double maxTorque, double frequency = 4, double dampingRatio = 1,
        int direction = rotationDirection_Shortest);
    PhysicsBody& clearDrive();
    bool isDriveEnabled() const { return mDrive.enabled; }
    PhysicsDriveState getDriveState() const;
    /** Create a body-to-body constraint. Returned native references are borrowed. */
    PhysicsConstraint& createPinJoint(PhysicsBody& other, const Point& anchor = Point(), const Point& otherAnchor = Point());
    PhysicsConstraint& createSlideJoint(PhysicsBody& other, const Point& anchor, const Point& otherAnchor, double minDistance, double maxDistance);
    PhysicsConstraint& createPivotJoint(PhysicsBody& other, const Point& anchor = Point(), const Point& otherAnchor = Point());
    PhysicsConstraint& createGrooveJoint(PhysicsBody& other, const Point& start, const Point& end, const Point& otherAnchor);
    PhysicsConstraint& createSpring(PhysicsBody& other, const Point& anchor, const Point& otherAnchor, double restLength, double stiffness, double damping);
    PhysicsConstraint& createRotarySpring(PhysicsBody& other, double restAngle, double stiffness, double damping);
    PhysicsConstraint& createRotaryLimit(PhysicsBody& other, double minAngle, double maxAngle);
    PhysicsConstraint& createRatchet(PhysicsBody& other, double interval, double phase = 0);
    PhysicsConstraint& createGear(PhysicsBody& other, double ratio, double phase = 0);
    PhysicsConstraint& createMotor(PhysicsBody& other, double radiansPerSecond, double maxTorque);
    uint32_t getConstraintCount() const { return uint32_t(mConstraints.size()); }
    PhysicsConstraint& getConstraint(uint32_t index) const;
    /// Disconnect all constraints, or only those to the specified body.
    PhysicsBody& disconnect(PhysicsBody* other = nullptr);
    /** Advance a detached/basic body. Owners/worlds call this once per step. */
    void step(double deltaSeconds);

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mPhysicsBodyScriptObj;
#endif

    /// @cond INTERNAL
    // Solver storage is private to the engine. It does not own the Sprite.
    struct Solver {
        virtual ~Solver() = default;
        virtual PhysicsBodyState readState() const = 0;
        virtual void writeState(const PhysicsBodyState&) = 0;
        virtual void addForce(double x, double y, double torque) = 0;
        virtual void configure(const PhysicsBody&) = 0;
        virtual void* nativeBody() const { return nullptr; }
    };
    void* nativeBody() const { return mSolver ? mSolver->nativeBody() : nullptr; }
    void addSolverObserver(const void* key, std::function<void()> observer) { mSolverObservers[key]=std::move(observer); }
    void removeSolverObserver(const void* key) { mSolverObservers.erase(key); }
    void clearSolverObservers();
    static void checkBreakAngularSpeeds(const std::vector<PhysicsBody*>& bodies);
    static void prepareConstraints(const std::vector<PhysicsBody*>& bodies);
    static void solveConstraints(const std::vector<PhysicsBody*>& bodies, double seconds);
    bool permitsCollisionWith(const PhysicsBody& other) const;
    void applyConstraintAngularImpulse(double impulse);

    void applyContactImpulse(const Vector& impulse, const Point& worldPoint);
    void correctContactPosition(const Vector& delta);
    void attachSolver(std::unique_ptr<Solver> solver);
    void detachSolver();
    void setPublisher(std::function<void(const PhysicsBodyState&)> publish) {
        mPublish = std::move(publish);
        if (!mPublish) {
            mBreakPublisher = {};
            clearBreakReferences();
            mWorldProvider = {};
            mCoordinateMode = {}; mRigDrive = false;
            if (mDriveController) { mDrive = PhysicsDriveState(); mDriveController = nullptr; }
        }
    }
    void setWorldProvider(std::function<const void*()> provider) { mWorldProvider = std::move(provider); }
    const void* world() const { return mWorldProvider ? mWorldProvider() : nullptr; }
    bool isAttached() const { return bool(mPublish); }
    // Advances loads/velocities before a Chipmunk world step; never integrates
    // position as well. The world is the only Chipmunk position integrator.
    void prepareWorldStep(double deltaSeconds);
    void publishWorldStep();
    void setOwnerTransform(const Point& position, double radians);
    void setOwnerPolicy(std::function<void(int)> mode, std::function<void()> motion) {
        mValidateMode = std::move(mode); mValidateMotion = std::move(motion);
    }
    void beginKinematicStep();
    void prepareKinematicStep(double seconds);
    void finishKinematicStep();
    uint32 getSerializedSize(ISerializer*) const;
    void serialize(ISerializer*) const;
    void deserialize(IDeserializer*, int mode = -1);
    /// @endcond
private:
    uint32 snapshotRecord(ISerializer*, bool emit) const;
    friend class PhysicsConstraint;
    /// @cond INTERNAL
    friend class PhysicsGraphSnapshot;
    /// @endcond
    friend class Sprite;
    friend class Part;
    friend class AnimationPhysicsRig;
    friend class SpriteAnimationSnapshot;
    friend class Particle;
    void configureMass(double mass, double momentOfInertia);
    // Explicit assembly membership, never inferred by walking constraints. The
    // Sprite owns these components and clears membership before detaching them.
    std::vector<PhysicsBody*> mAssemblyBodies;
    PhysicsBody* mAssemblyRoot = nullptr;
    PhysicsBody* mAssemblyOwner = nullptr;
    void configureAssemblyMasses(const std::vector<double>& masses);
    void clearBreakReferences();
    bool sampleBreakAngularSpeed(PhysicsBodyBreakInfo& info);
    void dispatchBreak(const PhysicsBodyBreakInfo& info);
    double mBreakAngularSpeed = 0;
    PhysicsBody* mBreakReference = nullptr;
    std::vector<PhysicsBody*> mBreakDependents;
    bool mBreakNotified = false;
    uint64_t mBreakRevision = 0;
    std::function<void(const PhysicsBodyBreakInfo&)> mBreakHandler, mBreakPublisher;
    void* mDriveController = nullptr;
    bool mRigDrive = false;
    std::function<void(int)> mCoordinateMode;
    PhysicsBody& setDriveTargetImpl(const Point& position, double radians, double maxForce,
        double maxTorque, double frequency, double dampingRatio, int direction);
    std::function<const void*()> mWorldProvider;
    std::vector<PhysicsConstraint*> mConstraints;
    PhysicsConstraint& createConstraint(PhysicsBody& other, int type, const Point& anchor, const Point& otherAnchor,
        const Point& groove, double a, double b, double c);
    void syncState();
    void commitState(bool publish = true);
    void configureSolver();
    void integrateStep(double seconds, bool move);
    std::unique_ptr<Solver> mSolver;
    std::map<const void*, std::function<void()>> mSolverObservers;
    std::function<void(const PhysicsBodyState&)> mPublish;
    std::function<void(int)> mValidateMode;
    std::function<void()> mValidateMotion;
    PhysicsBodyState mKinematicStart, mKinematicTarget;
    bool mKinematicCaptured = false, mKinematicDriven = false;
    struct AbsentTag {};
    explicit PhysicsBody(AbsentTag);
    struct Force {
        PhysicsForceId id;
        double x, y, torque, remaining, delay;
    };
    PhysicsForceId addLoad(double x, double y, double torque, double seconds, double delay);
    bool ignores(const char* operation) const;
    int mMode = physicsBody_Dynamic;
    double mMass = 1, mInertia = 1;
    double mLinearDamping = 0, mAngularDamping = 0, mFriction = 0, mRestitution = 0;
    PhysicsBodyState mState;
    PhysicsDriveState mDrive;
    std::vector<Force> mForces;
    PhysicsForceId mNextForce = 1;
};
/** Read-only Sprite/Part reference property sharing PhysicsBody::NoPhysics until assigned.
 * @ingroup Physics
 * This stores only a body pointer, never physical state. Only the owner
 * can change the association through setupPhysicsBody()/removePhysicsBody().
 * Convert to PhysicsBody& and call addRef() to retain a body independently of its
 * owner; balance it with release(). The property itself always follows its owner.
 */
template<class Owner> class PhysicsBodyRef {
    friend Owner;
    PhysicsBody* mBody = &PhysicsBody::NoPhysics;
    PhysicsBodyRef() = default;
public:
    PhysicsBodyRef(const PhysicsBodyRef&) = delete;
    PhysicsBodyRef& operator=(PhysicsBody&) = delete;
    PhysicsBodyRef& operator=(const PhysicsBodyRef&) = delete;
    /// Borrow the currently associated body; call addRef() before retaining it independently.
    operator PhysicsBody&() const { return *mBody; }
    /// Borrow the current body pointer, including NoPhysics when absent.
    PhysicsBody* operator->() const { return mBody; }
    /// Compare the associated body identities, not their state values.
    template<class Other> bool operator==(const PhysicsBodyRef<Other>& other) const {
        return mBody == &static_cast<PhysicsBody&>(other);
    }
    /// Test whether the associated body identities differ.
    template<class Other> bool operator!=(const PhysicsBodyRef<Other>& other) const { return !(*this == other); }
    /// Compare associated PhysicsBody identity.
    bool operator==(const PhysicsBody& body) const { return mBody == &body; }
    /// Compare associated PhysicsBody identity.
    bool operator!=(const PhysicsBody& body) const { return !(*this == body); }
    /// Compare associated PhysicsBody identity.
    friend bool operator==(const PhysicsBody& body, const PhysicsBodyRef& ref) { return ref == body; }
    /// Compare associated PhysicsBody identity.
    friend bool operator!=(const PhysicsBody& body, const PhysicsBodyRef& ref) { return ref != body; }
    /// \copydoc PhysicsBody::addRef()
    void addRef() const { return mBody->addRef(); }
    /// \copydoc PhysicsBody::release()
    void release() const { return mBody->release(); }
    /// \copydoc PhysicsBody::isPresent()
    bool isPresent() const { return mBody->isPresent(); }
    /** Test whether the associated body publishes motion to an owner.
     * @return True while attached to a Sprite or Part; false for NoPhysics or a detached body.
     */
    bool isAttached() const { return mBody->isAttached(); }
    /// \copydoc PhysicsBody::getSolver()
    int getSolver() const { return mBody->getSolver(); }
    /// \copydoc PhysicsBody::getMode()
    int getMode() const { return mBody->getMode(); }
    /// \copydoc PhysicsBody::setMode(int)
    PhysicsBody& setMode(int mode) { return mBody->setMode(mode); }
    /// \copydoc PhysicsBody::getState()
    PhysicsBodyState getState() const { return mBody->getState(); }
    /// \copydoc PhysicsBody::teleport(const Point&, double)
    PhysicsBody& teleport(const Point& position, double radians) { return mBody->teleport(position, radians); }
    /// \copydoc PhysicsBody::getVelocity()
    Vector getVelocity() const { return mBody->getVelocity(); }
    /// \copydoc PhysicsBody::setVelocity(const Vector&)
    PhysicsBody& setVelocity(const Vector& velocity) { return mBody->setVelocity(velocity); }
    /// \copydoc PhysicsBody::setVelocity(double, double)
    PhysicsBody& setVelocity(double x, double y) { return mBody->setVelocity(x, y); }
    /// \copydoc PhysicsBody::getSpeed()
    double getSpeed() const { return mBody->getSpeed(); }
    /// \copydoc PhysicsBody::setSpeed(double)
    PhysicsBody& setSpeed(double speed) { return mBody->setSpeed(speed); }
    /// \copydoc PhysicsBody::setVelocityInRadians(double, double)
    PhysicsBody& setVelocityInRadians(double speed, double direction) { return mBody->setVelocityInRadians(speed, direction); }
    /// \copydoc PhysicsBody::getMovementDirectionInRadians()
    double getMovementDirectionInRadians() const { return mBody->getMovementDirectionInRadians(); }
    /// \copydoc PhysicsBody::stopMoving()
    PhysicsBody& stopMoving() { return mBody->stopMoving(); }
    /// \copydoc PhysicsBody::stopSpinning()
    PhysicsBody& stopSpinning() { return mBody->stopSpinning(); }
    /// \copydoc PhysicsBody::getAngularMomentum()
    double getAngularMomentum() const { return mBody->getAngularMomentum(); }
    /// \copydoc PhysicsBody::getAngularVelocity()
    double getAngularVelocity() const { return mBody->getAngularVelocity(); }
    /// \copydoc PhysicsBody::setAngularVelocity(double)
    PhysicsBody& setAngularVelocity(double radiansPerSecond) { return mBody->setAngularVelocity(radiansPerSecond); }
    /// \copydoc PhysicsBody::setBreakAngularSpeed(double, PhysicsBody*)
    PhysicsBody& setBreakAngularSpeed(double radiansPerSecond, PhysicsBody* referenceBody = nullptr) { return mBody->setBreakAngularSpeed(radiansPerSecond, referenceBody); }
    /// \copydoc PhysicsBody::getBreakAngularSpeed()
    double getBreakAngularSpeed() const { return mBody->getBreakAngularSpeed(); }
    /// \copydoc PhysicsBody::getBreakAngularSpeedReference()
    PhysicsBody* getBreakAngularSpeedReference() const { return mBody->getBreakAngularSpeedReference(); }
    /// \copydoc PhysicsBody::setBreakHandler
    PhysicsBody& setBreakHandler(std::function<void(const PhysicsBodyBreakInfo&)> handler) { return mBody->setBreakHandler(std::move(handler)); }
    /// \copydoc PhysicsBody::getMass()
    double getMass() const { return mBody->getMass(); }
    /// \copydoc PhysicsBody::setMass(double)
    PhysicsBody& setMass(double mass) { return mBody->setMass(mass); }
    /// \copydoc PhysicsBody::getMomentOfInertia()
    double getMomentOfInertia() const { return mBody->getMomentOfInertia(); }
    /// \copydoc PhysicsBody::setMomentOfInertia(double)
    PhysicsBody& setMomentOfInertia(double inertia) { return mBody->setMomentOfInertia(inertia); }
    /// \copydoc PhysicsBody::getLinearDamping()
    double getLinearDamping() const { return mBody->getLinearDamping(); }
    /// \copydoc PhysicsBody::setLinearDamping(double)
    PhysicsBody& setLinearDamping(double perSecond) { return mBody->setLinearDamping(perSecond); }
    /// \copydoc PhysicsBody::getAngularDamping()
    double getAngularDamping() const { return mBody->getAngularDamping(); }
    /// \copydoc PhysicsBody::setAngularDamping(double)
    PhysicsBody& setAngularDamping(double perSecond) { return mBody->setAngularDamping(perSecond); }
    /// \copydoc PhysicsBody::getFriction()
    double getFriction() const { return mBody->getFriction(); }
    /// \copydoc PhysicsBody::setFriction(double)
    PhysicsBody& setFriction(double coefficient) { return mBody->setFriction(coefficient); }
    /// \copydoc PhysicsBody::getRestitution()
    double getRestitution() const { return mBody->getRestitution(); }
    /// \copydoc PhysicsBody::setRestitution(double)
    PhysicsBody& setRestitution(double coefficient) { return mBody->setRestitution(coefficient); }
    /// \copydoc PhysicsBody::applyImpulse(const Vector&)
    PhysicsBody& applyImpulse(const Vector& impulse) { return mBody->applyImpulse(impulse); }
    /// \copydoc PhysicsBody::applyImpulse(const Vector&, const Point&)
    PhysicsBody& applyImpulse(const Vector& impulse, const Point& worldPoint) { return mBody->applyImpulse(impulse, worldPoint); }
    /// \copydoc PhysicsBody::applyAngularImpulse(double)
    PhysicsBody& applyAngularImpulse(double impulse) { return mBody->applyAngularImpulse(impulse); }
    /// \copydoc PhysicsBody::applyForce(const Vector&, double, double)
    PhysicsForceId applyForce(const Vector& force, double durationSeconds, double delaySeconds = 0) { return mBody->applyForce(force, durationSeconds, delaySeconds); }
    /// \copydoc PhysicsBody::applyForce(const Vector&, const Point&, double, double)
    PhysicsForceId applyForce(const Vector& force, const Point& worldPoint, double durationSeconds, double delaySeconds = 0) { return mBody->applyForce(force, worldPoint, durationSeconds, delaySeconds); }
    /// \copydoc PhysicsBody::applyTorque(double, double, double)
    PhysicsForceId applyTorque(double torque, double durationSeconds, double delaySeconds = 0) { return mBody->applyTorque(torque, durationSeconds, delaySeconds); }
    /// \copydoc PhysicsBody::addContinuousForce(const Vector&)
    PhysicsForceId addContinuousForce(const Vector& force) { return mBody->addContinuousForce(force); }
    /// \copydoc PhysicsBody::addContinuousTorque(double)
    PhysicsForceId addContinuousTorque(double torque) { return mBody->addContinuousTorque(torque); }
    /// \copydoc PhysicsBody::removeForce(PhysicsForceId)
    bool removeForce(PhysicsForceId id) { return mBody->removeForce(id); }
    /// \copydoc PhysicsBody::stopAllForces()
    PhysicsBody& stopAllForces() { return mBody->stopAllForces(); }
    /// \copydoc PhysicsBody::createPinJoint
    PhysicsConstraint& createPinJoint(PhysicsBody& other, const Point& anchor = Point(), const Point& otherAnchor = Point()) { return mBody->createPinJoint(other, anchor, otherAnchor); }
    /// \copydoc PhysicsBody::createSlideJoint
    PhysicsConstraint& createSlideJoint(PhysicsBody& other, const Point& anchor, const Point& otherAnchor, double minDistance, double maxDistance) { return mBody->createSlideJoint(other, anchor, otherAnchor, minDistance, maxDistance); }
    /// \copydoc PhysicsBody::createPivotJoint
    PhysicsConstraint& createPivotJoint(PhysicsBody& other, const Point& anchor = Point(), const Point& otherAnchor = Point()) { return mBody->createPivotJoint(other, anchor, otherAnchor); }
    /// \copydoc PhysicsBody::createGrooveJoint
    PhysicsConstraint& createGrooveJoint(PhysicsBody& other, const Point& start, const Point& end, const Point& otherAnchor) { return mBody->createGrooveJoint(other, start, end, otherAnchor); }
    /// \copydoc PhysicsBody::createSpring
    PhysicsConstraint& createSpring(PhysicsBody& other, const Point& anchor, const Point& otherAnchor, double restLength, double stiffness, double damping) { return mBody->createSpring(other, anchor, otherAnchor, restLength, stiffness, damping); }
    /// \copydoc PhysicsBody::createRotarySpring
    PhysicsConstraint& createRotarySpring(PhysicsBody& other, double restAngle, double stiffness, double damping) { return mBody->createRotarySpring(other, restAngle, stiffness, damping); }
    /// \copydoc PhysicsBody::createRotaryLimit
    PhysicsConstraint& createRotaryLimit(PhysicsBody& other, double minAngle, double maxAngle) { return mBody->createRotaryLimit(other, minAngle, maxAngle); }
    /// \copydoc PhysicsBody::createRatchet
    PhysicsConstraint& createRatchet(PhysicsBody& other, double interval, double phase = 0) { return mBody->createRatchet(other, interval, phase); }
    /// \copydoc PhysicsBody::createGear
    PhysicsConstraint& createGear(PhysicsBody& other, double ratio, double phase = 0) { return mBody->createGear(other, ratio, phase); }
    /// \copydoc PhysicsBody::createMotor
    PhysicsConstraint& createMotor(PhysicsBody& other, double radiansPerSecond, double maxTorque) { return mBody->createMotor(other, radiansPerSecond, maxTorque); }
    uint32_t getConstraintCount() const { return mBody->getConstraintCount(); }
    PhysicsConstraint& getConstraint(uint32_t index) const { return mBody->getConstraint(index); }
    PhysicsBody& disconnect(PhysicsBody* other = nullptr) { return mBody->disconnect(other); }
    /// \copydoc PhysicsBody::setDriveTarget(const Point&, double, double, double, double, double, int)
    PhysicsBody& setDriveTarget(const Point& position, double radians, double maxForce,
        double maxTorque, double frequency = 4, double dampingRatio = 1,
        int direction = rotationDirection_Shortest) {
        return mBody->setDriveTarget(position, radians, maxForce, maxTorque, frequency, dampingRatio, direction);
    }
    /// \copydoc PhysicsBody::clearDrive()
    PhysicsBody& clearDrive() { return mBody->clearDrive(); }
    /// \copydoc PhysicsBody::isDriveEnabled()
    bool isDriveEnabled() const { return mBody->isDriveEnabled(); }
    /// \copydoc PhysicsBody::getDriveState()
    PhysicsDriveState getDriveState() const { return mBody->getDriveState(); }
    /// \copydoc PhysicsBody::step(double)
    void step(double deltaSeconds) { return mBody->step(deltaSeconds); }
};
}
#endif
