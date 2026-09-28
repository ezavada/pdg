#ifndef PDG_ANIMATION_TARGETS_H_INCLUDED
#define PDG_ANIMATION_TARGETS_H_INCLUDED
#include "pdg/sys/animationpose.h"
namespace pdg {

/** \addtogroup AnimationTargets
 * @{
 */
struct AnimationTargetState {
    double x = 0, y = 0, velocityX = 0, velocityY = 0;
};
// Exact damped spring integration toward a target held constant for this update.
// Recoil is an impulse on this state; body targeting supplies sampled body x/y.
class AnimationSpringTarget {
  public:
    AnimationSpringTarget(double mass = 1, double stiffness = 100, double damping = 20);
    AnimationTargetState getState() const {
        return mState;
    }
    void setState(const AnimationTargetState &state);
    void applyImpulse(double x, double y);
    AnimationTargetState update(double targetX, double targetY, double deltaSeconds);

  private:
    double mMass, mStiffness, mDamping;
    AnimationTargetState mState;
};
// No raw platform pointers. Callers provide a stable support ID and its current
// owning-layer transform; missing/replaced support releases a lock explicitly.
struct AnimationContactState {
    double x = 0, y = 0, influence = 0;
    bool locked = false;
};
class AnimationContactTarget {
  public:
    void lockWorld(double x, double y);
    void lockPlatform(double x, double y, uint64_t support, const AnimationTransform &frame);
    void release(double fadeSeconds = 0);
    AnimationContactState update(double deltaSeconds, bool contactActive, bool withinReach,
                                 uint64_t support = 0, const AnimationTransform &frame = {},
                                 double releaseSeconds = 0);
    AnimationContactState getState() const {
        return mState;
    }

  private:
    AnimationContactState mState;
    uint64_t mSupport = 0;
    double mLocalX = 0, mLocalY = 0, mFadeDuration = 0, mFadeRemaining = 0;
};
bool animationHasTag(const AnimationPose &pose, const std::string &object, const std::string &tag);
/** @} */

} // namespace pdg
#endif
