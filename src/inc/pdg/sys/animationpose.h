#ifndef PDG_ANIMATION_POSE_H_INCLUDED
#define PDG_ANIMATION_POSE_H_INCLUDED

#include <cstdint>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>

namespace pdg {

/** \addtogroup AnimationPoses
 * @{
 */

using AnimationBoneId = uint32_t;
using AnimationSocketId = uint32_t;
using AnimationBindingId = uint32_t;
constexpr AnimationBoneId animation_NoBone = std::numeric_limits<AnimationBoneId>::max();
constexpr AnimationSocketId animation_NoSocket = std::numeric_limits<AnimationSocketId>::max();
constexpr AnimationBindingId animation_NoBinding = std::numeric_limits<AnimationBindingId>::max();

// Rigid-part transform, using radians and Spriter's reflected-angle rule.
// This is not a general affine transform: composition does not introduce shear.
// Animation clocks are separate from poses; all public animation time is seconds.
struct AnimationTransform {
    double x = 0.0, y = 0.0;
    double rotation = 0.0;
    double scaleX = 1.0, scaleY = 1.0;
    double alpha = 1.0;

    bool isValid() const;
    static AnimationTransform compose(const AnimationTransform& parent, const AnimationTransform& local);
    static AnimationTransform interpolate(const AnimationTransform& from, const AnimationTransform& to, double influence);
};

// Sampled values retain their authored type. An empty object name denotes
// entity metadata. Missing values have no entry; missing tag tracks are empty.
using AnimationVariableValue = std::variant<int, double, std::string>;
struct AnimationVariable {
    std::string object, name;
    AnimationVariableValue value;
};
struct AnimationTagSet {
    std::string object;
    std::vector<std::string> tags;
};
struct AnimationMetadata {
    std::vector<AnimationVariable> variables;
    std::vector<AnimationTagSet> tags;
};

struct AnimationBone {
    std::string name;
    AnimationBoneId parent = animation_NoBone;
    AnimationTransform reference;
    double length = 0.0; // Explicit authored length; zero means unspecified.
};

enum AnimationSpace : int { animationSpace_Local = 0, animationSpace_Rig = 1, animationSpace_World = 2 };
enum AnimationDebugDraw : int {
    animationDebug_None = 0, animationDebug_Bones = 1,
    animationDebug_Sockets = 2, animationDebug_Boxes = 4, animationDebug_All = 7
};
enum AnimationBindingKind : int { animationBinding_Image = 0, animationBinding_Point = 1, animationBinding_Box = 2 };
enum AnimationVariableType : int { animationVariable_Float = 0, animationVariable_Int = 1, animationVariable_String = 2 };
struct AnimationBinding {
    std::string name;
    AnimationBoneId bone = animation_NoBone;
    AnimationBindingKind kind = animationBinding_Image;
    AnimationTransform reference;
    // Reference image bounds from authored file metadata, independent of GUI
    // texture loading. Used for physical geometry, never inferred IK lengths.
    bool hasImageBounds = false;
    double imageWidth = 0, imageHeight = 0, pivotX = 0, pivotY = 0;
};

struct AnimationSocket {
    std::string name;
    AnimationBoneId bone = animation_NoBone; // No bone means relative to the rig root.
    AnimationTransform local;
    AnimationBindingId binding = animation_NoBinding; // Optional animated point binding.
};

// IDs are vector indices, scoped to this immutable rig and its source revision.
// Construction validates all input before publishing the shared instance.
class AnimationRig {
public:
    static std::shared_ptr<const AnimationRig> create(std::vector<AnimationBone> bones,
        std::vector<AnimationSocket> sockets = {}, uint64_t revision = 1,
        std::vector<AnimationBinding> bindings = {});
    uint64_t getRevision() const { return mRevision; }
    size_t getBoneCount() const { return mBones.size(); }
    size_t getSocketCount() const { return mSockets.size(); }
    size_t getBindingCount() const { return mBindings.size(); }
    AnimationBindingId findBinding(const std::string& name) const;
    const AnimationBinding& getBinding(AnimationBindingId id) const;
    AnimationBoneId findBone(const std::string& name) const;
    AnimationSocketId findSocket(const std::string& name) const;
    const AnimationBone& getBone(AnimationBoneId id) const;
    const AnimationSocket& getSocket(AnimationSocketId id) const;

private:
    friend class AnimationPose;
    AnimationRig(std::vector<AnimationBone> bones, std::vector<AnimationSocket> sockets, uint64_t revision,
        std::vector<AnimationBinding> bindings);
    uint64_t mRevision;
    std::vector<AnimationBone> mBones;
    std::vector<AnimationSocket> mSockets;
    std::vector<AnimationBinding> mBindings;
    std::unordered_map<std::string, AnimationBindingId> mBindingNames;
    std::unordered_map<std::string, AnimationBoneId> mBoneNames;
    std::unordered_map<std::string, AnimationSocketId> mSocketNames;
    std::vector<AnimationBoneId> mEvaluationOrder;
};

// Owned pose snapshot. Copying shares immutable rig data, never mutable transforms.
// Local is parent-relative; global is rig-relative. World queries take an explicit
// sprite-root transform in the owning layer's coordinates. No port or physics dependency.
class AnimationPose {
public:
    explicit AnimationPose(std::shared_ptr<const AnimationRig> rig);
    const std::shared_ptr<const AnimationRig>& getRig() const { return mRig; }
    AnimationTransform getLocalTransform(AnimationBoneId id) const;
    void setLocalTransform(AnimationBoneId id, const AnimationTransform& transform);
    void setLocalTransforms(const std::vector<AnimationTransform>& transforms);
    void rotateLocal(AnimationBoneId id, double deltaRadians);
    AnimationTransform getGlobalTransform(AnimationBoneId id) const;
    AnimationTransform getWorldTransform(AnimationBoneId id, const AnimationTransform& root) const;
    AnimationTransform getSocketTransform(AnimationSocketId id) const;
    AnimationTransform getWorldSocketTransform(AnimationSocketId id, const AnimationTransform& root) const;
    AnimationTransform getBindingLocalTransform(AnimationBindingId id) const;
    void setBindingLocalTransform(AnimationBindingId id, const AnimationTransform& transform);
    AnimationTransform getBindingTransform(AnimationBindingId id) const;
    AnimationTransform getWorldBindingTransform(AnimationBindingId id, const AnimationTransform& root) const;
    const AnimationMetadata& getMetadata() const { return mMetadata; }
    void setMetadata(AnimationMetadata metadata);
    AnimationPose copy() const { return *this; }
    void resetToReference();
    // Poses must share the same rig instance/revision. Input poses are unchanged.
    static AnimationPose blend(const AnimationPose& from, const AnimationPose& to, double influence);

private:
    void markDescendantsDirty(AnimationBoneId id);
    void rebuild() const;
    AnimationMetadata mMetadata;
    std::shared_ptr<const AnimationRig> mRig;
    std::vector<AnimationTransform> mLocal;
    std::vector<AnimationTransform> mBindingLocal;
    mutable std::vector<AnimationTransform> mGlobal;
    mutable std::vector<bool> mDirty;
    mutable bool mHasDirty = true;
};
/** @} */

}
#endif
