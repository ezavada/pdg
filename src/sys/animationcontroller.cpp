#include "pdg/sys/animationcontroller.h"
#include <numbers>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace pdg {
namespace {
thread_local unsigned callbackDepth = 0;
constexpr double pi = std::numbers::pi;
void require(bool condition, const char *error) {
    if (!condition)
        throw std::invalid_argument(error);
}
void validatePose(const AnimationPose &pose, const AnimationTransform &root) {
    require(root.isValid(), "Invalid animation root transform");
    for (AnimationBoneId id = 0; id < pose.getRig()->getBoneCount(); ++id)
        pose.getWorldTransform(id, root);
    for (AnimationBindingId id = 0; id < pose.getRig()->getBindingCount(); ++id)
        pose.getWorldBindingTransform(id, root);
}
double reflection(const AnimationTransform &transform) {
    return transform.scaleX * transform.scaleY < 0 ? -1 : 1;
}
void nonsingular(const AnimationTransform &transform) {
    require(std::abs(transform.scaleX) > 1e-12 && std::abs(transform.scaleY) > 1e-12,
            "Two-bone IK requires nonsingular effective scales");
}
} // namespace
AnimationPose &AnimationPoseView::pose() const {
    if (!mLease || !mLease->pose)
        throw std::logic_error("Animation pose view has expired; retain copy() instead");
    return *mLease->pose;
}
AnimationPose AnimationPoseView::copy() const {
    return pose().copy();
}
AnimationTransform AnimationPoseView::getLocalTransform(AnimationBoneId id) const {
    return pose().getLocalTransform(id);
}
AnimationTransform AnimationPoseView::getTransform(AnimationBoneId id, int space) const {
    auto &value = pose();
    if (space == animationSpace_Local)
        return value.getLocalTransform(id);
    if (space == animationSpace_Rig)
        return value.getGlobalTransform(id);
    if (space == animationSpace_World)
        return value.getWorldTransform(id, mLease->root);
    throw std::invalid_argument("Invalid animation space");
}
void AnimationPoseView::setLocalTransform(AnimationBoneId id, const AnimationTransform &value) {
    pose().setLocalTransform(id, value);
}
void AnimationPoseView::rotateLocal(AnimationBoneId id, double radians) {
    pose().rotateLocal(id, radians);
}
void AnimationPipeline::change(std::function<void()> action) {
    if (mEvaluating)
        mPending.push_back(std::move(action));
    else {
        action();
        ++mRevision;
    }
}
std::shared_ptr<AnimationPipeline::Entry> AnimationPipeline::find(AnimationModifierId id) const {
    for (const auto &entry : mEntries)
        if (entry->id == id)
            return entry;
    throw std::out_of_range("Unknown animation modifier ID");
}
AnimationModifierId AnimationPipeline::addModifier(Modifier callback, int stage, int order) {
    require(bool(callback), "Animation modifier requires a callback");
    require(stage >= animationStage_PreConstraint && stage <= animationStage_PostConstraint,
            "Invalid animation modifier stage");
    if (!mNextId)
        throw std::overflow_error("Animation modifier IDs exhausted");
    auto entry = std::make_shared<Entry>();
    entry->id = mNextId++;
    entry->stage = stage;
    entry->order = order;
    entry->callback = std::move(callback);
    change([this, entry] { mEntries.push_back(entry); });
    return entry->id;
}
void AnimationPipeline::removeModifier(AnimationModifierId id) {
    change([this, id] {
        std::erase_if(mEntries, [id](const auto &entry) { return entry->id == id; });
    });
}
void AnimationPipeline::setModifierEnabled(AnimationModifierId id, bool enabled) {
    auto entry = find(id);
    require(!enabled || bool(entry->callback),
            "Failed modifiers must be removed and registered again");
    change([entry, enabled] { entry->enabled = enabled; });
}
bool AnimationPipeline::isModifierEnabled(AnimationModifierId id) const {
    return find(id)->enabled;
}
std::string AnimationPipeline::getModifierError(AnimationModifierId id) const {
    return find(id)->error;
}
void AnimationPipeline::clearModifiers() {
    change([this] { mEntries.clear(); });
}
void AnimationPipeline::setSource(int source) {
    require(source >= animationSource_Clip && source <= animationSource_Procedural,
            "Invalid animation source");
    change([this, source] { mSource = source; });
}
AnimationCallbackScope::AnimationCallbackScope() {
    ++callbackDepth;
}
AnimationCallbackScope::~AnimationCallbackScope() {
    --callbackDepth;
}
bool AnimationPipeline::isInsideCallback() {
    return callbackDepth != 0;
}
AnimationPose
AnimationPipeline::evaluate(const AnimationPose &base, const AnimationTransform &root,
                            double deltaSeconds,
                            const std::map<AnimationBoneId, AnimationTransform> &overrides) {
    require(std::isfinite(deltaSeconds) && deltaSeconds >= 0,
            "Animation delta must be finite nonnegative seconds");
    if (mEvaluating)
        throw std::logic_error("Recursive animation evaluation is not allowed");
    validatePose(base, root);
    auto result = mSource == animationSource_Clip ? base.copy() : AnimationPose(base.getRig());
    for (const auto &value : overrides)
        result.setLocalTransform(value.first, value.second);
    validatePose(result, root);
    auto entries = mEntries;
    std::stable_sort(entries.begin(), entries.end(), [](const auto &a, const auto &b) {
        return a->stage != b->stage ? a->stage < b->stage : a->order < b->order;
    });
    mEvaluating = true;
    struct Finish {
        AnimationPipeline &pipeline;
        ~Finish() {
            pipeline.mEvaluating = false;
            auto pending = std::move(pipeline.mPending);
            pipeline.mPending.clear();
            for (auto &action : pending) {
                action();
                ++pipeline.mRevision;
            }
        }
    } finish{*this};
    const AnimationModifierContext context{deltaSeconds, root, mRevision};
    for (const auto &entry : entries) {
        if (!entry->enabled)
            continue;
        auto candidate = result.copy();
        auto lease =
            std::make_shared<AnimationPoseView::Lease>(AnimationPoseView::Lease{&candidate, root});
        struct Expire {
            std::shared_ptr<AnimationPoseView::Lease> lease;
            ~Expire() {
                lease->pose = nullptr;
            }
        } expire{lease};
        try {
            AnimationCallbackScope scope;
            entry->callback(AnimationPoseView(lease), context);
            validatePose(candidate, root);
            result = std::move(candidate);
        } catch (const std::exception &error) {
            entry->error = error.what();
            entry->enabled = false;
            entry->callback = {};
            ++mRevision;
        } catch (...) {
            entry->error = "Unknown animation modifier failure";
            entry->enabled = false;
            entry->callback = {};
            ++mRevision;
        }
    }
    return result;
}
AnimationIKResult solveAnimationTwoBoneIK(AnimationPose &output, const AnimationTwoBoneIK &c,
                                          const AnimationTransform &worldRoot) {
    const auto rig = output.getRig();
    const auto &first = rig->getBone(c.root);
    const auto &second = rig->getBone(c.middle);
    require(second.parent == c.root && rig->getBone(c.tip).parent == c.middle,
            "IK requires a contiguous root/middle/tip chain");
    require(c.space >= animationSpace_Local && c.space <= animationSpace_World,
            "Invalid IK target space");
    require(c.bendDirection == -1 || c.bendDirection == 1, "IK bend direction must be -1 or 1");
    require(c.stretch == animationIK_NoStretch || c.stretch == animationIK_Stretch,
            "Invalid IK stretch policy");
    require(std::isfinite(c.targetX) && std::isfinite(c.targetY) &&
                std::isfinite(c.targetRotation) && std::isfinite(c.influence) && c.influence >= 0 &&
                c.influence <= 1,
            "Invalid IK target or influence");
    require(std::isfinite(c.rootMin) && std::isfinite(c.rootMax) && c.rootMin <= c.rootMax &&
                c.rootMin >= -pi && c.rootMax <= pi && std::isfinite(c.middleMin) &&
                std::isfinite(c.middleMax) && c.middleMin <= c.middleMax && c.middleMin >= -pi &&
                c.middleMax <= pi,
            "IK limits must be ordered radians within [-pi, pi]");
    const auto localMiddle = output.getLocalTransform(c.middle),
               localTip = output.getLocalTransform(c.tip);
    // Imported rigs need not declare lengths. Use this frame's actual joint
    // offsets in that case, including animated offsets; never use display widths.
    const double length1 = c.rootLength != 0 ? c.rootLength
        : first.length != 0 ? first.length : std::hypot(localMiddle.x, localMiddle.y);
    const double length2 = c.middleLength != 0 ? c.middleLength
        : second.length != 0 ? second.length : std::hypot(localTip.x, localTip.y);
    require(std::isfinite(length1) && length1 > 0 && std::isfinite(length2) && length2 > 0,
            "IK requires positive segment lengths or nonzero child offsets");
    auto pose = output.copy();
    const auto parent = first.parent == animation_NoBone
                            ? worldRoot
                            : pose.getWorldTransform(first.parent, worldRoot);
    auto a = pose.getWorldTransform(c.root, worldRoot),
         b = pose.getWorldTransform(c.middle, worldRoot),
         d = pose.getWorldTransform(c.tip, worldRoot);
    // PDG/Spriter compose component transforms without accumulating shear.
    // Rotating a joint changes its world heading but not its effective scales,
    // so world-space segment lengths also support nonuniform scaled chains.
    nonsingular(parent);
    nonsingular(a);
    nonsingular(b);
    require(std::abs(std::hypot(localMiddle.x, localMiddle.y) - length1) <= 1e-8 * length1 &&
                std::abs(std::hypot(localTip.x, localTip.y) - length2) <= 1e-8 * length2,
            "Declared IK lengths must match authored child offsets");
    AnimationTransform target;
    target.x = c.targetX;
    target.y = c.targetY;
    target.rotation = c.targetRotation;
    if (c.space == animationSpace_Local)
        target = AnimationTransform::compose(parent, target);
    else if (c.space == animationSpace_Rig)
        target = AnimationTransform::compose(worldRoot, target);
    double l1 = std::hypot(b.x - a.x, b.y - a.y), l2 = std::hypot(d.x - b.x, d.y - b.y);
    const double distance = std::hypot(target.x - a.x, target.y - a.y);
    require(std::isfinite(distance) && std::isfinite(l1 + l2) && l1 > 1e-12 && l2 > 1e-12,
            "Singular or overflowing IK chain");
    AnimationIKResult result;
    if (c.stretch == animationIK_Stretch && distance > l1 + l2) {
        const double ratio = distance / (l1 + l2);
        auto mid = localMiddle, tip = localTip;
        mid.x *= ratio;
        mid.y *= ratio;
        tip.x *= ratio;
        tip.y *= ratio;
        pose.setLocalTransform(c.middle, mid);
        pose.setLocalTransform(c.tip, tip);
        l1 *= ratio;
        l2 *= ratio;
        result.stretched = true;
    }
    const double reach = std::clamp(distance, std::abs(l1 - l2), l1 + l2);
    result.clamped = std::abs(reach - distance) > 1e-8;
    // At a coincident target retain the current root-to-middle heading for a
    // stable fold; the middle solve still folds the tip toward the root.
    const double heading = distance > 1e-12 ? std::atan2(target.y - a.y, target.x - a.x)
                                            : std::atan2(b.y - a.y, b.x - a.x);
    const double offset =
        reach > 1e-12 ? std::acos(std::clamp((reach * reach + l1 * l1 - l2 * l2) / (2 * reach * l1),
                                             -1.0, 1.0))
                      : pi / 2;
    const double desired = heading + c.bendDirection * offset;
    auto firstLocal = pose.getLocalTransform(c.root);
    firstLocal.rotation = std::remainder(
        firstLocal.rotation + reflection(parent) * (desired - std::atan2(b.y - a.y, b.x - a.x)),
        2 * pi);
    const double firstAngle = std::clamp(firstLocal.rotation, c.rootMin, c.rootMax);
    result.limited = firstAngle != firstLocal.rotation;
    firstLocal.rotation = firstAngle;
    pose.setLocalTransform(c.root, firstLocal);
    a = pose.getWorldTransform(c.root, worldRoot);
    b = pose.getWorldTransform(c.middle, worldRoot);
    d = pose.getWorldTransform(c.tip, worldRoot);
    const double aimX = a.x + reach * std::cos(heading), aimY = a.y + reach * std::sin(heading);
    auto secondLocal = pose.getLocalTransform(c.middle);
    secondLocal.rotation =
        std::remainder(secondLocal.rotation + reflection(a) * (std::atan2(aimY - b.y, aimX - b.x) -
                                                               std::atan2(d.y - b.y, d.x - b.x)),
                       2 * pi);
    const double secondAngle = std::clamp(secondLocal.rotation, c.middleMin, c.middleMax);
    result.limited = result.limited || secondAngle != secondLocal.rotation;
    secondLocal.rotation = secondAngle;
    pose.setLocalTransform(c.middle, secondLocal);
    if (c.matchOrientation) {
        const auto middle = pose.getWorldTransform(c.middle, worldRoot);
        auto tip = pose.getLocalTransform(c.tip);
        tip.rotation = reflection(middle) * (target.rotation - middle.rotation);
        pose.setLocalTransform(c.tip, tip);
    }
    auto blended = AnimationPose::blend(output, pose, c.influence);
    validatePose(blended, worldRoot);
    d = blended.getWorldTransform(c.tip, worldRoot);
    result.reachError = std::hypot(d.x - target.x, d.y - target.y);
    result.reachable = result.reachError <= 1e-7 * std::max(1.0, l1 + l2);
    result.stretched = result.stretched && c.influence > 0;
    output = std::move(blended);
    return result;
}
} // namespace pdg
