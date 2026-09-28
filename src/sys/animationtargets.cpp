#include "pdg/sys/animationtargets.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace pdg {
namespace {
void require(bool ok, const char *error) {
    if (!ok)
        throw std::invalid_argument(error);
}
bool finite(double x) {
    return std::isfinite(x);
}
void stepSpring(double &position, double &velocity, double target, double mass, double stiffness,
                double damping, double dt) {
    const double a = damping / (2 * mass), w2 = stiffness / mass, disc = a * a - w2,
                 y = position - target, v = velocity;
    double nextY, nextV;
    if (stiffness == 0) {
        if (damping == 0) {
            nextY = y + v * dt;
            nextV = v;
        } else {
            const double factor = std::exp(-damping / mass * dt);
            nextY = y + v * (-std::expm1(-damping / mass * dt)) / (damping / mass);
            nextV = v * factor;
        }
    } else if (std::abs(disc) <= 1e-12 * std::max(1.0, w2)) {
        const double b = v + a * y, e = std::exp(-a * dt);
        nextY = e * (y + b * dt);
        nextV = e * (v - a * b * dt);
    } else if (disc < 0) {
        const double w = std::sqrt(-disc), c = std::cos(w * dt), s = std::sin(w * dt),
                     e = std::exp(-a * dt);
        nextY = e * (y * c + (v + a * y) * s / w);
        nextV = e * (v * c - (a * v + w2 * y) * s / w);
    } else {
        const double d = std::sqrt(disc), r1 = -w2 / (a + d), r2 = -a - d;
        const double c1 = (v - r2 * y) / (r1 - r2), c2 = y - c1, e1 = std::exp(r1 * dt),
                     e2 = std::exp(r2 * dt);
        nextY = c1 * e1 + c2 * e2;
        nextV = r1 * c1 * e1 + r2 * c2 * e2;
    }
    position = target + nextY;
    velocity = nextV;
}
} // namespace
AnimationSpringTarget::AnimationSpringTarget(double mass, double stiffness, double damping)
    : mMass(mass), mStiffness(stiffness), mDamping(damping) {
    require(finite(mass) && mass > 0 && finite(stiffness) && stiffness >= 0 && finite(damping) &&
                damping >= 0,
            "Invalid spring mass, stiffness or damping");
    require(finite(stiffness / mass) && finite(damping / mass) &&
                finite(std::pow(damping / (2 * mass), 2)),
            "Spring coefficients overflow");
}
void AnimationSpringTarget::setState(const AnimationTargetState &s) {
    require(finite(s.x) && finite(s.y) && finite(s.velocityX) && finite(s.velocityY),
            "Invalid spring state");
    mState = s;
}
void AnimationSpringTarget::applyImpulse(double x, double y) {
    require(finite(x) && finite(y), "Invalid spring impulse");
    auto next = mState;
    next.velocityX += x / mMass;
    next.velocityY += y / mMass;
    setState(next);
}
AnimationTargetState AnimationSpringTarget::update(double x, double y, double seconds) {
    require(finite(x) && finite(y) && finite(seconds) && seconds >= 0,
            "Spring target and seconds must be finite");
    if (seconds == 0)
        return mState;
    auto next = mState;
    stepSpring(next.x, next.velocityX, x, mMass, mStiffness, mDamping, seconds);
    stepSpring(next.y, next.velocityY, y, mMass, mStiffness, mDamping, seconds);
    setState(next);
    return mState;
}
void AnimationContactTarget::lockWorld(double x, double y) {
    require(finite(x) && finite(y), "Invalid contact target");
    mState = {x, y, 1, true};
    mSupport = 0;
    mFadeDuration = mFadeRemaining = 0;
}
void AnimationContactTarget::lockPlatform(double x, double y, uint64_t support,
                                          const AnimationTransform &frame) {
    require(support != 0 && frame.isValid() && frame.scaleX != 0 && frame.scaleY != 0 &&
                finite(x) && finite(y),
            "Invalid platform contact frame");
    const double dx = x - frame.x, dy = y - frame.y, c = std::cos(frame.rotation),
                 s = std::sin(frame.rotation);
    const double lx = (c * dx + s * dy) / frame.scaleX, ly = (-s * dx + c * dy) / frame.scaleY;
    require(finite(lx) && finite(ly), "Platform contact transform overflow");
    lockWorld(x, y);
    mSupport = support;
    mLocalX = lx;
    mLocalY = ly;
}
void AnimationContactTarget::release(double seconds) {
    require(finite(seconds) && seconds >= 0, "Contact fade must be nonnegative finite seconds");
    if (!mState.locked)
        return;
    mState.locked = false;
    mSupport = 0;
    mFadeDuration = seconds;
    mFadeRemaining = seconds;
    if (seconds == 0)
        mState.influence = 0;
}
AnimationContactState AnimationContactTarget::update(double seconds, bool active, bool reachable,
                                                     uint64_t support,
                                                     const AnimationTransform &frame, double fade) {
    require(finite(seconds) && seconds >= 0 && finite(fade) && fade >= 0,
            "Contact update requires nonnegative finite seconds");
    if (mState.locked && (!active || !reachable || (mSupport && support != mSupport)))
        release(fade);
    if (mState.locked && mSupport) {
        require(frame.isValid() && frame.scaleX != 0 && frame.scaleY != 0,
                "Invalid moving-platform transform");
        AnimationTransform local;
        local.x = mLocalX;
        local.y = mLocalY;
        auto point = AnimationTransform::compose(frame, local);
        mState.x = point.x;
        mState.y = point.y;
    }
    if (!mState.locked && mFadeDuration > 0) {
        mFadeRemaining = std::max(0.0, mFadeRemaining - seconds);
        mState.influence = mFadeRemaining / mFadeDuration;
    }
    return mState;
}
bool animationHasTag(const AnimationPose &pose, const std::string &object, const std::string &tag) {
    for (const auto &group : pose.getMetadata().tags)
        if (group.object == object)
            return std::find(group.tags.begin(), group.tags.end(), tag) != group.tags.end();
    return false;
}
} // namespace pdg
