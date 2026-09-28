#include "pdg/sys/animationpose.h"
#include <numbers>

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <set>

namespace pdg {
namespace {
constexpr double pi = std::numbers::pi;
void validate(const AnimationTransform& transform) {
    if (!transform.isValid()) throw std::invalid_argument("Animation transform must be finite with alpha in [0, 1]");
}
void validateInfluence(double influence) {
    if (!std::isfinite(influence) || influence < 0 || influence > 1)
        throw std::invalid_argument("Animation influence must be in [0, 1]");
}
}

bool AnimationTransform::isValid() const {
    return std::isfinite(x) && std::isfinite(y) && std::isfinite(rotation)
        && std::isfinite(scaleX) && std::isfinite(scaleY) && std::isfinite(alpha)
        && alpha >= 0 && alpha <= 1;
}

AnimationTransform AnimationTransform::compose(const AnimationTransform& parent, const AnimationTransform& local) {
    validate(parent);
    validate(local);
    const double c = std::cos(parent.rotation), s = std::sin(parent.rotation);
    const double x = local.x * parent.scaleX, y = local.y * parent.scaleY;
    // Match Spriter TransformProcessor, including odd-axis reflection. Zero
    // scales are permitted for forward evaluation; inverse/IK operations must
    // reject singular transforms separately.
    const bool reflected = parent.scaleX * parent.scaleY < 0;
    AnimationTransform result;
    result.x = parent.x + x * c - y * s;
    result.y = parent.y + x * s + y * c;
    result.rotation = parent.rotation + (reflected ? -local.rotation : local.rotation);
    result.scaleX = parent.scaleX * local.scaleX;
    result.scaleY = parent.scaleY * local.scaleY;
    result.alpha = parent.alpha * local.alpha;
    if (!result.isValid()) throw std::overflow_error("Animation transform composition overflow");
    return result;
}

AnimationTransform AnimationTransform::interpolate(const AnimationTransform& from, const AnimationTransform& to, double influence) {
    validate(from);
    validate(to);
    validateInfluence(influence);
    if (influence == 0) return from;
    if (influence == 1) return to;
    const auto mix = [influence](double a, double b) { return a * (1 - influence) + b * influence; };
    AnimationTransform result;
    result.x = mix(from.x, to.x);
    result.y = mix(from.y, to.y);
    const double delta = std::remainder(std::remainder(to.rotation, 2 * pi)
        - std::remainder(from.rotation, 2 * pi), 2 * pi);
    result.rotation = from.rotation + influence * delta;
    result.scaleX = mix(from.scaleX, to.scaleX);
    result.scaleY = mix(from.scaleY, to.scaleY);
    result.alpha = mix(from.alpha, to.alpha);
    validate(result);
    return result;
}

std::shared_ptr<const AnimationRig> AnimationRig::create(std::vector<AnimationBone> bones,
        std::vector<AnimationSocket> sockets, uint64_t revision, std::vector<AnimationBinding> bindings) {
    return std::shared_ptr<const AnimationRig>(new AnimationRig(std::move(bones), std::move(sockets), revision, std::move(bindings)));
}

AnimationRig::AnimationRig(std::vector<AnimationBone> bones, std::vector<AnimationSocket> sockets, uint64_t revision,
        std::vector<AnimationBinding> bindings)
    : mRevision(revision), mBones(std::move(bones)), mSockets(std::move(sockets)), mBindings(std::move(bindings)) {
    if (revision == 0 || mBones.size() >= animation_NoBone || mSockets.size() >= animation_NoSocket || mBindings.size() >= animation_NoBinding)
        throw std::invalid_argument("Invalid animation rig revision or size");
    std::vector<std::vector<AnimationBoneId>> children(mBones.size());
    mEvaluationOrder.reserve(mBones.size());
    for (AnimationBoneId id = 0; id < mBones.size(); ++id) {
        const auto& bone = mBones[id];
        validate(bone.reference);
        if (bone.name.empty() || !mBoneNames.emplace(bone.name, id).second)
            throw std::invalid_argument("Animation bone names must be nonempty and unique");
        if (!std::isfinite(bone.length) || bone.length < 0)
            throw std::invalid_argument("Animation bone length must be finite and nonnegative");
        if (bone.parent == animation_NoBone) mEvaluationOrder.push_back(id);
        else {
            if (bone.parent >= mBones.size() || bone.parent == id)
                throw std::invalid_argument("Invalid animation bone parent");
            children[bone.parent].push_back(id);
        }
    }
    // Stable breadth-first topological order: input IDs need not be parent-first.
    for (size_t index = 0; index < mEvaluationOrder.size(); ++index) {
        const auto& next = children[mEvaluationOrder[index]];
        mEvaluationOrder.insert(mEvaluationOrder.end(), next.begin(), next.end());
    }
    if (mEvaluationOrder.size() != mBones.size()) throw std::invalid_argument("Animation rig contains a parent cycle");
    for (AnimationBindingId id = 0; id < mBindings.size(); ++id) {
        const auto& binding = mBindings[id];
        validate(binding.reference);
        if (binding.hasImageBounds && (!std::isfinite(binding.imageWidth) || !std::isfinite(binding.imageHeight)
            || binding.imageWidth < 0 || binding.imageHeight < 0 || !std::isfinite(binding.pivotX) || !std::isfinite(binding.pivotY)))
            throw std::invalid_argument("Invalid reference image bounds");
        if (binding.name.empty() || !mBindingNames.emplace(binding.name, id).second)
            throw std::invalid_argument("Animation binding names must be nonempty and unique");
        if (binding.bone != animation_NoBone && binding.bone >= mBones.size())
            throw std::invalid_argument("Invalid animation binding parent");
        if (binding.kind != animationBinding_Image && binding.kind != animationBinding_Point
            && binding.kind != animationBinding_Box) throw std::invalid_argument("Invalid animation binding kind");
    }
    for (AnimationSocketId id = 0; id < mSockets.size(); ++id) {
        const auto& socket = mSockets[id];
        validate(socket.local);
        if (socket.name.empty() || !mSocketNames.emplace(socket.name, id).second)
            throw std::invalid_argument("Animation socket names must be nonempty and unique");
        if (socket.bone != animation_NoBone && socket.bone >= mBones.size())
            throw std::invalid_argument("Invalid animation socket parent");
        if (socket.binding != animation_NoBinding && (socket.binding >= mBindings.size()
            || mBindings[socket.binding].kind != animationBinding_Point
            || mBindings[socket.binding].bone != socket.bone))
            throw std::invalid_argument("Invalid animated socket binding");
    }
}

AnimationBindingId AnimationRig::findBinding(const std::string& name) const {
    const auto found = mBindingNames.find(name);
    return found == mBindingNames.end() ? animation_NoBinding : found->second;
}
const AnimationBinding& AnimationRig::getBinding(AnimationBindingId id) const { return mBindings.at(id); }
AnimationBoneId AnimationRig::findBone(const std::string& name) const {
    const auto found = mBoneNames.find(name);
    return found == mBoneNames.end() ? animation_NoBone : found->second;
}
AnimationSocketId AnimationRig::findSocket(const std::string& name) const {
    const auto found = mSocketNames.find(name);
    return found == mSocketNames.end() ? animation_NoSocket : found->second;
}
const AnimationBone& AnimationRig::getBone(AnimationBoneId id) const { return mBones.at(id); }
const AnimationSocket& AnimationRig::getSocket(AnimationSocketId id) const { return mSockets.at(id); }

AnimationPose::AnimationPose(std::shared_ptr<const AnimationRig> rig) : mRig(std::move(rig)) {
    if (!mRig) throw std::invalid_argument("Animation pose requires a rig");
    mGlobal.resize(mRig->getBoneCount());
    mDirty.resize(mRig->getBoneCount(), true);
    mLocal.reserve(mRig->getBoneCount());
    for (const auto& bone : mRig->mBones) mLocal.push_back(bone.reference);
    for (const auto& binding : mRig->mBindings) mBindingLocal.push_back(binding.reference);
}
AnimationTransform AnimationPose::getLocalTransform(AnimationBoneId id) const { return mLocal.at(id); }
void AnimationPose::markDescendantsDirty(AnimationBoneId id) {
    mDirty.at(id) = true;
    for (const auto bone : mRig->mEvaluationOrder) {
        const auto parent = mRig->mBones[bone].parent;
        if (parent != animation_NoBone && mDirty[parent]) mDirty[bone] = true;
    }
    mHasDirty = true;
}
void AnimationPose::setLocalTransform(AnimationBoneId id, const AnimationTransform& transform) {
    validate(transform);
    mLocal.at(id) = transform;
    markDescendantsDirty(id);
}
void AnimationPose::setLocalTransforms(const std::vector<AnimationTransform>& transforms) {
    if (transforms.size() != mLocal.size()) throw std::invalid_argument("Animation pose bone count mismatch");
    for (const auto& transform : transforms) validate(transform);
    mLocal = transforms;
    std::fill(mDirty.begin(), mDirty.end(), true);
    mHasDirty = true;
}
void AnimationPose::rotateLocal(AnimationBoneId id, double deltaRadians) {
    auto transform = getLocalTransform(id);
    transform.rotation += deltaRadians;
    setLocalTransform(id, transform);
}
void AnimationPose::rebuild() const {
    if (!mHasDirty) return;
    for (const auto id : mRig->mEvaluationOrder) {
        if (!mDirty[id]) continue;
        const auto parent = mRig->mBones[id].parent;
        mGlobal[id] = parent == animation_NoBone ? mLocal[id] : AnimationTransform::compose(mGlobal[parent], mLocal[id]);
        mDirty[id] = false;
    }
    mHasDirty = false;
}
AnimationTransform AnimationPose::getGlobalTransform(AnimationBoneId id) const {
    mRig->getBone(id); // reject an invalid ID before any lazy evaluation
    rebuild();
    return mGlobal[id];
}
AnimationTransform AnimationPose::getWorldTransform(AnimationBoneId id, const AnimationTransform& root) const {
    validate(root);
    mRig->getBone(id);
    // Spriter composition is not associative under nonuniform scale. Include
    // the world root at each parent/child step instead of applying it to an
    // already-composed rig-space transform.
    std::vector<AnimationBoneId> ancestors;
    for (auto bone = id; bone != animation_NoBone; bone = mRig->mBones[bone].parent)
        ancestors.push_back(bone);
    AnimationTransform result = root;
    for (auto it = ancestors.rbegin(); it != ancestors.rend(); ++it)
        result = AnimationTransform::compose(result, mLocal[*it]);
    return result;
}
AnimationTransform AnimationPose::getSocketTransform(AnimationSocketId id) const {
    const auto& socket = mRig->getSocket(id);
    if (socket.binding != animation_NoBinding) return getBindingTransform(socket.binding);
    return socket.bone == animation_NoBone ? socket.local : AnimationTransform::compose(getGlobalTransform(socket.bone), socket.local);
}
AnimationTransform AnimationPose::getWorldSocketTransform(AnimationSocketId id, const AnimationTransform& root) const {
    const auto& socket = mRig->getSocket(id);
    if (socket.binding != animation_NoBinding) return getWorldBindingTransform(socket.binding, root);
    return AnimationTransform::compose(socket.bone == animation_NoBone ? root
        : getWorldTransform(socket.bone, root), socket.local);
}
AnimationTransform AnimationPose::getBindingLocalTransform(AnimationBindingId id) const { return mBindingLocal.at(id); }
void AnimationPose::setBindingLocalTransform(AnimationBindingId id, const AnimationTransform& transform) {
    validate(transform);
    mBindingLocal.at(id) = transform;
}
AnimationTransform AnimationPose::getBindingTransform(AnimationBindingId id) const {
    const auto& binding = mRig->getBinding(id);
    return binding.bone == animation_NoBone ? mBindingLocal[id]
        : AnimationTransform::compose(getGlobalTransform(binding.bone), mBindingLocal[id]);
}
AnimationTransform AnimationPose::getWorldBindingTransform(AnimationBindingId id, const AnimationTransform& root) const {
    const auto& binding = mRig->getBinding(id);
    return AnimationTransform::compose(binding.bone == animation_NoBone ? root
        : getWorldTransform(binding.bone, root), mBindingLocal[id]);
}
void AnimationPose::setMetadata(AnimationMetadata metadata) {
    std::set<std::pair<std::string, std::string>> variables;
    for (const auto& value : metadata.variables) {
        if (value.name.empty() || !variables.emplace(value.object, value.name).second)
            throw std::invalid_argument("Animation variable names must be unique within their object");
        if (const auto* number = std::get_if<double>(&value.value); number && !std::isfinite(*number))
            throw std::invalid_argument("Nonfinite animation variable");
    }
    std::set<std::string> objects;
    for (const auto& group : metadata.tags) {
        if (!objects.insert(group.object).second) throw std::invalid_argument("Duplicate animation tag scope");
        std::set<std::string> names;
        for (const auto& name : group.tags) if (name.empty() || !names.insert(name).second)
            throw std::invalid_argument("Animation tags must be nonempty and unique");
    }
    mMetadata = std::move(metadata);
}
void AnimationPose::resetToReference() {
    mMetadata = {};
    for (size_t id = 0; id < mLocal.size(); ++id) mLocal[id] = mRig->mBones[id].reference;
    for (size_t id = 0; id < mBindingLocal.size(); ++id) mBindingLocal[id] = mRig->mBindings[id].reference;
    std::fill(mDirty.begin(), mDirty.end(), true);
    mHasDirty = true;
}
AnimationPose AnimationPose::blend(const AnimationPose& from, const AnimationPose& to, double influence) {
    if (from.mRig != to.mRig) throw std::invalid_argument("Cannot blend poses from different rigs or revisions");
    validateInfluence(influence);
    AnimationPose result(from.mRig);
    for (size_t id = 0; id < from.mLocal.size(); ++id)
        result.mLocal[id] = AnimationTransform::interpolate(from.mLocal[id], to.mLocal[id], influence);
    // Discrete values and presence switch to the destination at halfway.
    // Matching numeric values interpolate, with integer truncation matching
    // Spriter's authored integer variable interpolation.
    result.mMetadata = influence < 0.5 ? from.mMetadata : to.mMetadata;
    for (auto& value : result.mMetadata.variables) {
        const auto find = [&](const AnimationPose& pose) -> const AnimationVariable* {
            for (const auto& candidate : pose.mMetadata.variables)
                if (candidate.object == value.object && candidate.name == value.name) return &candidate;
            return nullptr;
        };
        const auto* a = find(from); const auto* b = find(to);
        if (!a || !b || a->value.index() != b->value.index()) continue;
        if (const auto* number = std::get_if<double>(&a->value))
            value.value = *number * (1 - influence) + std::get<double>(b->value) * influence;
        else if (const auto* integer = std::get_if<int>(&a->value))
            value.value = static_cast<int>(*integer * (1 - influence) + std::get<int>(b->value) * influence);
    }
    for (size_t id = 0; id < from.mBindingLocal.size(); ++id)
        result.mBindingLocal[id] = AnimationTransform::interpolate(from.mBindingLocal[id], to.mBindingLocal[id], influence);
    return result;
}
}
