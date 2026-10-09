#ifndef PDG_ANIMATION_CONTROLLER_H_INCLUDED
#define PDG_ANIMATION_CONTROLLER_H_INCLUDED
#include "pdg/sys/animationpose.h"
#include <numbers>
#include <functional>
#include <map>
#include <optional>

namespace pdg {

/** \addtogroup AnimationModifiers
 * @{
 */
// Shared lifetime barrier for native/script animation and drawing callbacks.
class AnimationCallbackScope {
  public:
    AnimationCallbackScope();
    ~AnimationCallbackScope();
    AnimationCallbackScope(const AnimationCallbackScope &) = delete;
    AnimationCallbackScope &operator=(const AnimationCallbackScope &) = delete;
};
enum AnimationModifierStage : int {
    animationStage_PreConstraint = 0,
    animationStage_Constraint = 1,
    animationStage_PostConstraint = 2
};
enum AnimationSource : int {
    animationSource_Clip = 0,
    animationSource_Reference = 1,
    animationSource_Procedural = 2
};
using AnimationModifierId = uint32_t;

// A copy of this view shares its invocation lease. Every operation fails after
// the callback returns; copy() is the explicit way to retain an owned pose.
class AnimationPoseView {
  public:
    AnimationPose copy() const;
    AnimationTransform getLocalTransform(AnimationBoneId id) const;
    AnimationTransform getTransform(AnimationBoneId id, int space = animationSpace_Local) const;
    void setLocalTransform(AnimationBoneId id, const AnimationTransform &transform);
    void rotateLocal(AnimationBoneId id, double radians);

  private:
    friend class AnimationPipeline;
    struct Lease {
        AnimationPose *pose;
        AnimationTransform root;
    };
    explicit AnimationPoseView(std::shared_ptr<Lease> lease) : mLease(std::move(lease)) {}
    AnimationPose &pose() const;
    std::shared_ptr<Lease> mLease;
};
struct AnimationModifierContext {
    double deltaSeconds = 0;
    AnimationTransform root;
    uint64_t revision = 0;
    double simulationDeltaSeconds = 0;
};

// No clock or GUI/physics dependency. Sprite supplies the freshly sampled base
// and one elapsed-seconds value per update. Zero means explicit reevaluation.
class AnimationPipeline {
    /// @cond INTERNAL
    friend class SpriteAnimationSnapshot;
    /// @endcond
  public:
    using Modifier = std::function<void(AnimationPoseView, const AnimationModifierContext &)>;
    AnimationModifierId addModifier(Modifier callback, int stage = animationStage_PreConstraint,
                                    int order = 0);
    void removeModifier(AnimationModifierId id);
    void setModifierEnabled(AnimationModifierId id, bool enabled);
    bool isModifierEnabled(AnimationModifierId id) const;
    std::string getModifierError(AnimationModifierId id) const;
    void clearModifiers();
    void setSource(int source);
    int getSource() const {
        return mSource;
    }
    uint64_t getRevision() const {
        return mRevision;
    }
    bool isEvaluating() const {
        return mEvaluating;
    }
    static bool isInsideCallback();
    AnimationPose evaluate(const AnimationPose &base, const AnimationTransform &root,
                           double deltaSeconds,
                           const std::map<AnimationBoneId, AnimationTransform> &overrides = {},
                           const std::function<void(AnimationPose&,bool)>& controls = {},
                           double simulationDeltaSeconds = -1);

  private:
    struct Entry {
        AnimationModifierId id;
        int stage, order;
        bool enabled = true;
        Modifier callback;
        std::string error;
    };
    std::shared_ptr<Entry> find(AnimationModifierId id) const;
    void change(std::function<void()> action);
    std::vector<std::shared_ptr<Entry>> mEntries;
    std::vector<std::function<void()>> mPending;
    AnimationModifierId mNextId = 1;
    uint64_t mRevision = 1;
    int mSource = animationSource_Clip;
    bool mEvaluating = false;
};

enum AnimationIKStretch : int { animationIK_NoStretch = 0, animationIK_Stretch = 1 };
struct AnimationTwoBoneIK {
    AnimationBoneId root = animation_NoBone, middle = animation_NoBone, tip = animation_NoBone;
    // Explicit segment lengths in parent-local units; zero uses the rig's
    // declared length, or the current child offset length if none is declared.
    // Explicit/declared lengths must match child offsets. Display widths are
    // never used. Inferred lengths follow animated offsets on each solve.
    double rootLength = 0, middleLength = 0;
    double targetX = 0, targetY = 0, influence = 1;
    int space = animationSpace_Rig, bendDirection = 1, stretch = animationIK_NoStretch;
    bool matchOrientation = false;
    double targetRotation = 0;
    double rootMin = -std::numbers::pi, rootMax = std::numbers::pi;
    double middleMin = -std::numbers::pi, middleMax = std::numbers::pi;
};
struct AnimationIKResult {
    double reachError = 0;
    bool reachable = false, clamped = false, limited = false, stretched = false;
};
// Atomic solve. Requires contiguous chains and nonsingular effective
// scales, including nonuniform scales and reflections. Local targets use root's parent
// frame. World coordinates always belong to the supplied owning-layer root.
AnimationIKResult solveAnimationTwoBoneIK(AnimationPose &pose, const AnimationTwoBoneIK &config,
                                          const AnimationTransform &root = {});

/// A contiguous root-to-endpoint chain. The endpoint's rotation is preserved.
struct AnimationFABRIK {
    std::vector<AnimationBoneId> chain;
    double targetX = 0, targetY = 0, influence = 1, tolerance = 0.01;
    int space = animationSpace_Rig, maxIterations = 16, bendDirection = 1;
    std::vector<double> minimum, maximum;
};
struct AnimationFABRIKResult {
    double solveError = 0, reachError = 0;
    int iterations = 0;
    bool converged = false, reached = false, limited = false, withinGeometricReach = false;
};
AnimationFABRIKResult solveAnimationFABRIK(AnimationPose&, const AnimationFABRIK&, const AnimationTransform& root = {});

enum JiggleMode : int { jiggleMode_Chain = 0, jiggleMode_IKTarget = 1 };
struct AnimationJiggleJoint {
    AnimationBoneId bone = animation_NoBone;
    std::optional<double> length,frequency,dampingRatio,inertia,maxAngle,maxAngularSpeed,gravityX,gravityY;
};
struct AnimationJiggle {
    int mode = jiggleMode_Chain;
    AnimationModifierId ik = 0;
    std::vector<AnimationBoneId> chain;
    std::vector<AnimationJiggleJoint> joints;
    double frequency = 3, dampingRatio = 0.4, influence = 1, inertia = 0.5;
    double maxAngle = std::numbers::pi / 3, length = 0;
    double gravityX = 0, gravityY = 0, maxDistance = 32, maxSpeed = 1000, maxAngularSpeed = 20;
    double maxStepSeconds = 1.0 / 120, teleportDistance = 128, teleportAngle = std::numbers::pi / 2;
    int maxSubsteps = 16;
    bool enabled = true, resetOnSeek = true, resetOnTeleport = true;
};
struct JiggleJointState {
    double angle = 0, velocity = 0, desired = 0, pivotX = 0, pivotY = 0, pivotVelocityX = 0, pivotVelocityY = 0;
};
struct JiggleState {
    std::vector<JiggleJointState> joints;
    double x = 0, y = 0, velocityX = 0, velocityY = 0;
    bool initialized = false;
};
struct JiggleResult {
    double lagDistance = 0, influence = 1, simulatedSeconds = 0;
    double desiredX = 0, desiredY = 0, filteredX = 0, filteredY = 0, effectiveX = 0, effectiveY = 0;
    int substeps = 0;
    bool limited = false, reset = false;
};
struct SpriteJiggleState {
    AnimationJiggle config; JiggleState state; JiggleResult result;
    double fadeStart=1,fadeTarget=1,fadeElapsed=0,fadeDuration=0;
};
void validateAnimationJiggle(const AnimationJiggle&);
JiggleResult solveAnimationJiggle(AnimationPose&, const AnimationJiggle&, JiggleState&, double seconds,
                                const AnimationTransform& root = {}, const std::vector<double>& minimum = {},
                                const std::vector<double>& maximum = {});
JiggleResult stepJiggleTarget(const AnimationJiggle&, JiggleState&, double x, double y, double seconds);
/** @} */

} // namespace pdg
#endif
