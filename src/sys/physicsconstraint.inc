// Shared PhysicsBody constraint implementation. Included by physicsbody.cpp so
// the standalone basic-body contracts exercise the same implementation.
#ifdef PDG_USE_CHIPMUNK_PHYSICS
#include "chipmunk/chipmunk.h"
#endif
#include <set>
namespace pdg {
namespace {
void constraintFinite(double x) {
    if (!std::isfinite(x))
        throw std::invalid_argument("Constraint values must be finite");
}
void constraintPositive(double x) {
    constraintFinite(x);
    if (x < 0)
        throw std::invalid_argument("Constraint values must be nonnegative");
}
Point bodyPoint(const PhysicsBody &body, const Point &p) {
    const auto s = body.getState();
    const double c = std::cos(s.rotation), n = std::sin(s.rotation);
    return Point(s.x + c * p.x - n * p.y, s.y + n * p.x + c * p.y);
}
double constraintDistance(const Point &a, const Point &b) {
    return std::hypot(b.x - a.x, b.y - a.y);
}
} // namespace
struct PhysicsConstraint::Native {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    cpConstraint *joint = nullptr;
    PhysicsBody *a = nullptr;
    PhysicsBody *b = nullptr;
    const PhysicsConstraint *owner = nullptr;
    ~Native() {
        if (a)
            a->removeSolverObserver(owner);
        if (b)
            b->removeSolverObserver(owner);
        if (!joint)
            return;
        auto *space = cpConstraintGetSpace(joint);
        if (space && cpSpaceIsLocked(space)) {
            cpSpaceAddPostStepCallback(
                space,
                [](cpSpace *s, void *key, void *) {
                    auto *j = static_cast<cpConstraint *>(key);
                    cpSpaceRemoveConstraint(s, j);
                    cpConstraintFree(j);
                },
                joint, nullptr);
        } else {
            if (space)
                cpSpaceRemoveConstraint(space, joint);
            cpConstraintFree(joint);
        }
    }
#endif
};
PhysicsConstraint::PhysicsConstraint(PhysicsBody &a, PhysicsBody &b, int type, const Point &pa,
                                     const Point &pb, const Point &groove, double v1, double v2,
                                     double v3)
    : mA(&a), mB(&b), mType(type), mAnchorA(pa), mAnchorB(pb), mGroove(groove), mValue1(v1),
      mValue2(v2), mValue3(v3) {
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mPhysicsConstraintScriptObj);
#endif
}
PhysicsConstraint::~PhysicsConstraint() = default;
PhysicsBody &PhysicsConstraint::getBodyA() const {
    return mA ? *mA : PhysicsBody::NoPhysics;
}
PhysicsBody &PhysicsConstraint::getBodyB() const {
    return mB ? *mB : PhysicsBody::NoPhysics;
}
Point PhysicsConstraint::getAnchorA() const {
    if (mType < constraint_Pin || mType > constraint_Spring || mType == constraint_Groove)
        throw std::logic_error("Anchor A requires a pin, slide, pivot or spring; use groove endpoints for a groove");
    return mAnchorA;
}
Point PhysicsConstraint::getAnchorB() const {
    if (mType < constraint_Pin || mType > constraint_Spring)
        throw std::logic_error("Anchors require a linear constraint");
    return mAnchorB;
}
PhysicsConstraint& PhysicsConstraint::setAnchorA(const Point& anchor) {
    return setAnchors(anchor, getAnchorB());
}
PhysicsConstraint& PhysicsConstraint::setAnchorB(const Point& anchor) {
    getAnchorB();
    constraintFinite(anchor.x); constraintFinite(anchor.y);
    if (mAnchorB != anchor) { mAnchorB = anchor; mAnchorsDirty = true; }
    return *this;
}
PhysicsConstraint& PhysicsConstraint::setAnchors(const Point& anchorA, const Point& anchorB) {
    getAnchorA();
    for (double value : {double(anchorA.x), double(anchorA.y), double(anchorB.x), double(anchorB.y)})
        constraintFinite(value);
    if (mAnchorA != anchorA || mAnchorB != anchorB) {
        mAnchorA = anchorA; mAnchorB = anchorB; mAnchorsDirty = true;
    }
    return *this;
}
Point PhysicsConstraint::getGrooveStart() const {
    if (mType != constraint_Groove) throw std::logic_error("Groove endpoints require a groove constraint");
    return mAnchorA;
}
Point PhysicsConstraint::getGrooveEnd() const {
    getGrooveStart();
    return mGroove;
}
PhysicsConstraint& PhysicsConstraint::setGroove(const Point& start, const Point& end) {
    getGrooveStart();
    for (double value : {double(start.x), double(start.y), double(end.x), double(end.y)})
        constraintFinite(value);
    if (constraintDistance(start, end) <= 1e-8)
        throw std::invalid_argument("Groove endpoints must differ");
    if (mAnchorA != start || mGroove != end) {
        mAnchorA = start; mGroove = end; mAnchorsDirty = true;
    }
    return *this;
}
PhysicsConstraint &PhysicsConstraint::setMaxForce(double x) {
    if (std::isnan(x) || x < 0)
        throw std::invalid_argument("Maximum constraint force must be nonnegative");
    mMaxForce = x;
    return *this;
}
PhysicsConstraint &PhysicsConstraint::setBreakForce(double x) {
    constraintPositive(x);
    mBreakForce = x;
    return *this;
}
PhysicsConstraint &PhysicsConstraint::setCollideBodies(bool value) {
    mCollideBodies = value;
    return *this;
}
double PhysicsConstraint::getMinAngle() const {
    if (mType != constraint_RotaryLimit) throw std::logic_error("Angle limits require a rotary-limit constraint");
    return mValue1;
}
double PhysicsConstraint::getMaxAngle() const {
    if (mType != constraint_RotaryLimit) throw std::logic_error("Angle limits require a rotary-limit constraint");
    return mValue2;
}
PhysicsConstraint& PhysicsConstraint::setAngleLimits(double minAngle, double maxAngle) {
    getMinAngle(); // Validate the constraint type before changing anything.
    constraintFinite(minAngle); constraintFinite(maxAngle);
    if (minAngle > maxAngle) throw std::invalid_argument("Invalid rotary limits");
    mValue1 = minAngle; mValue2 = maxAngle;
    return *this;
}
void PhysicsConstraint::disconnect() {
    if (!mA)
        return;
    addRef();
    mNative.reset();
    auto *a = mA;
    auto *b = mB;
    mA = mB = nullptr;
    for (auto *body : {a, b}) {
        auto &list = body->mConstraints;
        auto i = std::find(list.begin(), list.end(), this);
        if (i != list.end()) {
            list.erase(i);
            release();
        }
    }
    release();
}
PhysicsBody &PhysicsBody::disconnect(PhysicsBody *other) {
    for (size_t i = 0; i < mConstraints.size();) {
        auto *c = mConstraints[i];
        if (!other || &c->getBodyA() == other || &c->getBodyB() == other)
            c->disconnect();
        else
            ++i;
    }
    return *this;
}
PhysicsConstraint &PhysicsBody::getConstraint(uint32_t i) const {
    if (i >= mConstraints.size())
        throw std::out_of_range("Constraint index");
    return *mConstraints[i];
}
bool PhysicsBody::permitsCollisionWith(const PhysicsBody &other) const {
    for (auto *c : mConstraints)
        if (!c->mCollideBodies && (&c->getBodyA() == &other || &c->getBodyB() == &other))
            return false;
    return true;
}
void PhysicsBody::applyConstraintAngularImpulse(double j) {
    if (mMode != physicsBody_Dynamic)
        return;
    syncState();
    mState.angularVelocity += j / mInertia;
    commitState(false);
}
PhysicsConstraint &PhysicsBody::createConstraint(PhysicsBody &other, int type, const Point &pa,
                                                 const Point &pb, const Point &groove, double a,
                                                 double b, double c) {
    if (!isPresent() || !other.isPresent() || this == &other)
        throw std::invalid_argument("Constraints require two distinct instantiated PhysicsBodies");
    for (double value : {double(pa.x), double(pa.y), double(pb.x), double(pb.y), double(groove.x),
                         double(groove.y), a, b, c})
        constraintFinite(value);
    if (world() != other.world())
        throw std::invalid_argument("Constraint bodies must belong to the same world");
    mConstraints.reserve(mConstraints.size() + 1);
    other.mConstraints.reserve(other.mConstraints.size() + 1);
    auto *constraint = new PhysicsConstraint(*this, other, type, pa, pb, groove, a, b, c);
    constraint->addRef();
    mConstraints.push_back(constraint);
    constraint->addRef();
    other.mConstraints.push_back(constraint);
    return *constraint;
}
PhysicsConstraint &PhysicsBody::createPinJoint(PhysicsBody &other, const Point &a, const Point &b) {
    return createConstraint(other, constraint_Pin, a, b, Point(),
                            constraintDistance(bodyPoint(*this, a), bodyPoint(other, b)), 0, 0);
}
PhysicsConstraint &PhysicsBody::createSlideJoint(PhysicsBody &other, const Point &a, const Point &b,
                                                 double min, double max) {
    constraintPositive(min);
    constraintPositive(max);
    if (max < min)
        throw std::invalid_argument("Invalid slide limits");
    return createConstraint(other, constraint_Slide, a, b, Point(), min, max, 0);
}
PhysicsConstraint &PhysicsBody::createPivotJoint(PhysicsBody &other, const Point &a,
                                                 const Point &b) {
    return createConstraint(other, constraint_Pivot, a, b, Point(), 0, 0, 0);
}
PhysicsConstraint &PhysicsBody::createGrooveJoint(PhysicsBody &other, const Point &start,
                                                  const Point &end, const Point &b) {
    if (constraintDistance(start, end) <= 1e-8)
        throw std::invalid_argument("Groove endpoints must differ");
    return createConstraint(other, constraint_Groove, start, b, end, 0, 0, 0);
}
PhysicsConstraint &PhysicsBody::createSpring(PhysicsBody &other, const Point &a, const Point &b,
                                             double length, double k, double d) {
    constraintPositive(length);
    constraintPositive(k);
    constraintPositive(d);
    return createConstraint(other, constraint_Spring, a, b, Point(), length, k, d);
}
PhysicsConstraint &PhysicsBody::createRotarySpring(PhysicsBody &other, double angle, double k,
                                                   double d) {
    constraintPositive(k);
    constraintPositive(d);
    return createConstraint(other, constraint_RotarySpring, Point(), Point(), Point(), angle, k, d);
}
PhysicsConstraint &PhysicsBody::createRotaryLimit(PhysicsBody &other, double min, double max) {
    if (max < min)
        throw std::invalid_argument("Invalid rotary limits");
    return createConstraint(other, constraint_RotaryLimit, Point(), Point(), Point(), min, max, 0);
}
PhysicsConstraint &PhysicsBody::createRatchet(PhysicsBody &other, double interval, double phase) {
    if (interval == 0)
        throw std::invalid_argument("Ratchet interval must be nonzero");
    const double angle = other.getState().rotation - getState().rotation;
    return createConstraint(other, constraint_Ratchet, Point(), Point(), Point(), interval, phase,
                            angle);
}
PhysicsConstraint &PhysicsBody::createGear(PhysicsBody &other, double ratio, double phase) {
    if (ratio == 0)
        throw std::invalid_argument("Gear ratio must be nonzero");
    return createConstraint(other, constraint_Gear, Point(), Point(), Point(), ratio, phase, 0);
}
PhysicsConstraint &PhysicsBody::createMotor(PhysicsBody &other, double rate, double torque) {
    constraintPositive(torque);
    return createConstraint(other, constraint_Motor, Point(), Point(), Point(), rate, 0, 0)
        .setMaxForce(torque);
}

void PhysicsConstraint::prepareNative() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (!isActive())
        return;
    if (mA->world() != mB->world()) {
        mNative.reset();
        return;
    }
    auto *a = static_cast<cpBody *>(mA->nativeBody());
    auto *b = static_cast<cpBody *>(mB->nativeBody());
    auto *space = a ? cpBodyGetSpace(a) : nullptr;
    if (!a || !b || !space || space != cpBodyGetSpace(b) ||
        (cpBodyGetType(a) != CP_BODY_TYPE_DYNAMIC && cpBodyGetType(b) != CP_BODY_TYPE_DYNAMIC)) {
        mNative.reset();
        return;
    }
    if (mAnchorsDirty) {
        if (cpSpaceIsLocked(space))
            throw std::logic_error("Apply constraint anchor edits outside the physical solve");
        // Rebuild only the solver joint, discarding impulses cached for the old
        // lever arms. Setters may run in contact callbacks; adoption waits here.
        mNative.reset();
        mAnchorsDirty = false;
    }
    if (!mNative) {
        if (cpSpaceIsLocked(space))
            throw std::logic_error("Create constraints outside the physical solve");
        auto next = std::make_unique<Native>();
        next->a = mA;
        next->b = mB;
        next->owner = this;
        const cpVect pa = cpv(mAnchorA.x, mAnchorA.y), pb = cpv(mAnchorB.x, mAnchorB.y);
        switch (mType) {
        case constraint_Pin:
            if (mValue1 <= 1e-8)
                next->joint = cpPivotJointNew2(a, b, pa, pb);
            else {
                next->joint = cpPinJointNew(a, b, pa, pb);
                cpPinJointSetDist(next->joint, mValue1);
            }
            break;
        case constraint_Slide:
            next->joint = cpSlideJointNew(a, b, pa, pb, mValue1, mValue2);
            break;
        case constraint_Pivot:
            next->joint = cpPivotJointNew2(a, b, pa, pb);
            break;
        case constraint_Groove:
            next->joint = cpGrooveJointNew(a, b, pa, cpv(mGroove.x, mGroove.y), pb);
            break;
        case constraint_Spring:
            next->joint = cpDampedSpringNew(a, b, pa, pb, mValue1, mValue2, mValue3);
            break;
        case constraint_RotarySpring:
            next->joint = cpDampedRotarySpringNew(a, b, -mValue1, mValue2, mValue3);
            break;
        case constraint_RotaryLimit:
            next->joint = cpRotaryLimitJointNew(a, b, mValue1, mValue2);
            break;
        case constraint_Ratchet:
            next->joint = cpRatchetJointNew(a, b, mValue2, mValue1);
            cpRatchetJointSetAngle(next->joint, mValue3);
            break;
        case constraint_Gear:
            next->joint = cpGearJointNew(a, b, mValue2, mValue1);
            break;
        case constraint_Motor:
            next->joint = cpSimpleMotorNew(a, b, -mValue1);
            break;
        }
        cpSpaceAddConstraint(space, next->joint);
        mA->addSolverObserver(this, [this] { mNative.reset(); });
        mB->addSolverObserver(this, [this] { mNative.reset(); });
        mNative = std::move(next);
    }
    if (mType == constraint_RotaryLimit) {
        if (cpRotaryLimitJointGetMin(mNative->joint) != mValue1) cpRotaryLimitJointSetMin(mNative->joint, mValue1);
        if (cpRotaryLimitJointGetMax(mNative->joint) != mValue2) cpRotaryLimitJointSetMax(mNative->joint, mValue2);
    }
    cpConstraintSetMaxForce(mNative->joint, mMaxForce);
    cpConstraintSetCollideBodies(mNative->joint, mCollideBodies);
#endif
}
void PhysicsConstraint::solveBasic(double seconds) {
    if (!isActive() || seconds <= 0 || mA->nativeBody() || mB->nativeBody())
        return;
    const auto a = mA->getState(), b = mB->getState();
    const double ia = mA->getMode() == physicsBody_Dynamic ? 1 / mA->getMass() : 0,
                 ib = mB->getMode() == physicsBody_Dynamic ? 1 / mB->getMass() : 0;
    const double ja = mA->getMode() == physicsBody_Dynamic ? 1 / mA->getMomentOfInertia() : 0,
                 jb = mB->getMode() == physicsBody_Dynamic ? 1 / mB->getMomentOfInertia() : 0;
    auto bounded = [&](double j) {
        const double budget = std::max(0.0, mMaxForce * seconds - mImpulse);
        j = std::clamp(j, -budget, budget);
        mImpulse += std::abs(j);
        return j;
    };
    if (mType >= constraint_RotarySpring) {
        double ca = -1, cb = 1, error = 0, target = 0;
        const double angle = b.rotation - a.rotation;
        switch (mType) {
        case constraint_RotarySpring:
            error = angle - mValue1;
            break;
        case constraint_RotaryLimit:
            error = angle - std::clamp(angle, mValue1, mValue2);
            if (error == 0)
                return;
            break;
        case constraint_Ratchet:
            if ((angle - mValue3) * mValue1 > 0) {
                mValue3 = std::floor((angle - mValue2) / mValue1) * mValue1 + mValue2;
                return;
            }
            error = angle - mValue3;
            break;
        case constraint_Gear:
            cb = mValue1;
            error = b.rotation * mValue1 - a.rotation - mValue2;
            break;
        case constraint_Motor:
            target = mValue1;
            break;
        }
        const double inv = ca * ca * ja + cb * cb * jb;
        if (inv == 0)
            return;
        const double speed = ca * a.angularVelocity + cb * b.angularVelocity;
        double impulse = mType == constraint_RotarySpring
                             ? (-mValue2 * error - mValue3 * speed) * seconds
                             : (target - speed - .2 * error / seconds) / inv;
        impulse = bounded(impulse);
        mA->applyConstraintAngularImpulse(ca * impulse);
        mB->applyConstraintAngularImpulse(cb * impulse);
        return;
    }
    Point pa = bodyPoint(*mA, mAnchorA), pb = bodyPoint(*mB, mAnchorB);
    Point grooveNormal;
    bool insideGroove = false;
    if (mType == constraint_Groove) {
        const Point end = bodyPoint(*mA, mGroove);
        const double x = end.x - pa.x, y = end.y - pa.y;
        const double t =
            std::clamp(((pb.x - pa.x) * x + (pb.y - pa.y) * y) / (x * x + y * y), 0.0, 1.0);
        pa = Point(pa.x + x * t, pa.y + y * t);
        insideGroove = t > 0 && t < 1;
        const double length = std::hypot(x, y);
        grooveNormal = Point(-y / length, x / length);
    }
    const double dx = pb.x - pa.x, dy = pb.y - pa.y, dist = std::hypot(dx, dy);
    double error = dist;
    if (mType == constraint_Pin || mType == constraint_Spring)
        error -= mValue1;
    if (mType == constraint_Slide) {
        error = dist - std::clamp(dist, mValue1, mValue2);
        if (error == 0)
            return;
    }
    Point axes[2];
    int count = 1;
    axes[0] = dist > 1e-8 ? Point(dx / dist, dy / dist) : Point(1, 0);
    if (mType == constraint_Pivot || mType == constraint_Groove ||
        (mType == constraint_Pin && mValue1 <= 1e-8)) {
        axes[0] = Point(1, 0);
        axes[1] = Point(0, 1);
        count = 2;
    }
    if (insideGroove) {
        axes[0] = grooveNormal;
        count = 1;
        error = dx * grooveNormal.x + dy * grooveNormal.y;
    }
    for (int i = 0; i < count; ++i) {
        const auto n = axes[i];
        const double ax = pa.x - a.x, ay = pa.y - a.y, bx = pb.x - b.x, by = pb.y - b.y;
        const double ar = ax * n.y - ay * n.x, br = bx * n.y - by * n.x,
                     inv = ia + ib + ar * ar * ja + br * br * jb;
        if (inv == 0)
            continue;
        const double speed =
            (b.velocityX - b.angularVelocity * by - a.velocityX + a.angularVelocity * ay) * n.x +
            (b.velocityY + b.angularVelocity * bx - a.velocityY - a.angularVelocity * ax) * n.y;
        const double e = count == 2 ? dx * n.x + dy * n.y : error;
        double impulse = mType == constraint_Spring ? (-mValue2 * e - mValue3 * speed) * seconds
                                                    : -(speed + .2 * e / seconds) / inv;
        impulse = bounded(impulse);
        mA->applyContactImpulse(Vector(-n.x * impulse, -n.y * impulse), pa);
        mB->applyContactImpulse(Vector(n.x * impulse, n.y * impulse), pb);
    }
}
void PhysicsConstraint::finishStep(double seconds) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mNative) {
        mImpulse = std::abs(cpConstraintGetImpulse(mNative->joint));
        if (mType == constraint_Ratchet) mValue3 = cpRatchetJointGetAngle(mNative->joint);
    }
#endif
    mForce = seconds > 0 ? mImpulse / seconds : 0;
    if (mBreakForce > 0 && mForce > mBreakForce) {
        mBroken = true;
        disconnect();
    }
}
namespace {
std::vector<PhysicsConstraint *> collectConstraints(const std::vector<PhysicsBody *> &bodies) {
    std::set<PhysicsBody *> owners(bodies.begin(), bodies.end());
    std::set<PhysicsConstraint *> seen;
    std::vector<PhysicsConstraint *> result;
    for (auto *body : bodies)
        for (uint32_t i = 0; i < body->getConstraintCount(); ++i) {
            auto *c = &body->getConstraint(i);
            if (owners.count(&c->getBodyA()) && owners.count(&c->getBodyB()) &&
                seen.insert(c).second) {
                c->addRef();
                result.push_back(c);
            }
        }
    return result;
}
} // namespace
void PhysicsBody::prepareConstraints(const std::vector<PhysicsBody *> &bodies) {
    auto all = collectConstraints(bodies);
    try {
        for (auto *c : all)
            c->prepareNative();
    } catch (...) {
        for (auto *c : all)
            c->release();
        throw;
    }
    for (auto *c : all)
        c->release();
}
void PhysicsBody::solveConstraints(const std::vector<PhysicsBody *> &bodies, double seconds) {
    if (!std::isfinite(seconds) || seconds < 0)
        throw std::invalid_argument("Constraint steps require nonnegative finite seconds");
    auto all = collectConstraints(bodies);
    try {
        for (auto *c : all) {
            c->mImpulse = 0;
            c->solveBasic(seconds);
            c->finishStep(seconds);
        }
    } catch (...) {
        for (auto *c : all)
            c->release();
        throw;
    }
    for (auto *c : all)
        c->release();
}
} // namespace pdg
