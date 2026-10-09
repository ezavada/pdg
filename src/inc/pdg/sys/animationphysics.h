#ifndef PDG_ANIMATION_PHYSICS_H_INCLUDED
#define PDG_ANIMATION_PHYSICS_H_INCLUDED
#include "pdg_project.h"
#include <numbers>
#include "pdg/sys/animationpose.h"
#include "pdg/sys/physicsbody.h"
#include <functional>
#include <optional>
#ifdef PDG_USE_CHIPMUNK_PHYSICS
#include "chipmunk/chipmunk_private.h"
#endif
namespace pdg {

/** \addtogroup AnimationPhysics
 * Animation physics requires Chipmunk. Basic is intentionally not an animation-rig backend.
 * @{
 */
enum AnimationPhysicsMode : int {
    animationPhysics_Kinematic = 0, animationPhysics_Dynamic = 1,
    animationPhysics_Driven = 2, animationPhysics_Mixed = 3
};
struct AnimationPhysicsDriveSettings {
    double maxForce = 0, maxTorque = 0, frequency = 4, dampingRatio = 1;
    int direction = rotationDirection_Shortest;
};
/// @cond INTERNAL
struct AnimationPhysicsRecovery {
    AnimationBoneId bone = animation_NoBone; // noBone denotes whole selection in event payload only
    bool includeDescendants = false, disabled = false;
    int mode = animationPhysics_Kinematic;
    std::vector<uint32_t> bodies;
};
/// @endcond
enum AnimationPhysicsBodyMode : int { animationBody_Dynamic = 0, animationBody_Kinematic = 1 };
enum AnimationPhysicsRootMode : int { animationRoot_Fixed = 0, animationRoot_Follow = 1 };
// Version 1: rigid capsule shapes. All dimensions are layer units, mass is the
// application's mass unit, angles are radians, velocities are units/second.
struct AnimationPhysicsBody {
    AnimationBoneId bone = animation_NoBone;
    int mode = animationBody_Dynamic;
    double mass = 1, length = 1, radius = 0.5;
    double offsetX = 0, offsetY = 0, offsetRotation = 0;
    double friction = 0.7, elasticity = 0;
    uint32_t categories = 0xffffffffu, mask = 0xffffffffu;
};
struct AnimationPhysicsJoint {
    uint32_t parent = 0, child = 0; // indices into bodies, not bone IDs
    double parentX = 0, parentY = 0, childX = 0, childY = 0;
    double minAngle = -std::numbers::pi, maxAngle = std::numbers::pi;
    double maxForce = 1e6;
    bool collide = false;
};
struct AnimationPhysicsDefinition {
    uint32_t version = 1;
    int rootMode = animationRoot_Fixed;
    uint32_t rootBody = 0;
    bool selfCollisions = false;
    std::vector<AnimationPhysicsBody> bodies;
    std::vector<AnimationPhysicsJoint> joints;
    /// @cond INTERNAL
    bool generated = false; // geometry inference/coordinate convention, independent of ownership
    /// @endcond
};
AnimationPhysicsDefinition decodeAnimationPhysicsDefinition(const std::vector<double> &values);
/// @cond INTERNAL
AnimationBoneId selectAnimationPhysicsRoot(const AnimationRig& rig, AnimationBoneId requested = animation_NoBone);
AnimationPhysicsDefinition generateAnimationPhysicsDefinition(const AnimationPose& current,
    const AnimationTransform& root, double totalMass, AnimationBoneId requestedRoot,
    double unitsPerMeter, std::vector<std::string>& diagnostics);
/// @endcond
#ifdef PDG_USE_CHIPMUNK_PHYSICS
// Caller keeps space alive. Destruction in a locked space schedules removal at
// its post-step boundary. No dependence on Sprite, GUI, scripting or Spriter.
class AnimationPhysicsRig {
  public:
    AnimationPhysicsRig(cpSpace *space, const AnimationPhysicsDefinition &definition,
                        const AnimationPose &pose, const AnimationTransform &root,
                        double velocityX = 0, double velocityY = 0, double angularVelocity = 0);
    ~AnimationPhysicsRig();
    AnimationPhysicsRig(const AnimationPhysicsRig &) = delete;
    AnimationPhysicsRig &operator=(const AnimationPhysicsRig &) = delete;
    void prepare(const AnimationPose &desired, const AnimationTransform &root, double deltaSeconds);
    AnimationPose publish(const AnimationPose &desired, const AnimationTransform &root) const;
    AnimationTransform followingRoot(const AnimationPose &desired,
                                     const AnimationTransform &root) const;
    const AnimationPhysicsDefinition &definition() const {
        return mDefinition;
    }
    /// @cond INTERNAL
    AnimationPhysicsRig(cpSpace *space, const AnimationPhysicsDefinition &definition,
                        const AnimationPose &pose, const AnimationTransform &root,
                        double velocityX, double velocityY, double angularVelocity, bool sharedComponents);
    PhysicsBodyState getBodyState(uint32_t index) const;
    std::unique_ptr<PhysicsBody::Solver> createBodySolver(uint32_t index, std::function<void()> moved);
    cpBody *body(uint32_t index) const;
    static AnimationPhysicsRig *find(cpBody *body);
    uint32_t bodyIndex(cpBody *body) const;
    void setRootBody(uint32_t index);
    void attachBodies(const std::vector<PhysicsBody*>& bodies);
    void releaseControls();
    bool isBodyAttached(uint32_t index) const;
    void validateMembershipChange(const std::vector<bool>& attached) const;
    void setMembership(const std::vector<bool>& attached, uint32_t root);
    void removeDetachedBodies(const std::vector<uint32_t>& indices);
    std::vector<uint32_t> select(std::optional<AnimationBoneId> bone, bool descendants) const;
    int getMode(const std::vector<uint32_t>& selection) const;
    void setMode(int mode, const std::vector<uint32_t>& selection, double seconds, int direction,
        const AnimationPose& desired, const AnimationTransform& root, AnimationPhysicsRecovery request);
    void setDriveSettings(const AnimationPhysicsDriveSettings&, const std::vector<uint32_t>&);
    std::optional<AnimationPhysicsDriveSettings> getDriveSettings(uint32_t index) const;
    std::vector<AnimationPhysicsRecovery> finishStep(const AnimationPose&, const AnimationTransform&);
    void publishedRoot(const AnimationTransform& root);
    void frameChanged(const AnimationTransform& root);
    void reflect(const AnimationTransform& root, bool flipX, bool flipY,
                 const std::vector<PhysicsBody*>& members);
    double bodyReflection(uint32_t index) const;
    bool resizeBone(AnimationBoneId bone,double widthFactor,double heightFactor);
    void moveToSpace(cpSpace* space);
    void adoptMovedSpace(cpSpace* space);
    uint32 snapshotRecord(ISerializer* writer, bool emit) const;
    static std::unique_ptr<AnimationPhysicsRig> restoreSnapshot(IDeserializer* reader,
        const AnimationPose& desired, const AnimationTransform& root, const std::vector<PhysicsBody*>& bodies,
        std::function<void()> moved);
    void *owner = nullptr; // optional engine adapter; never stored in Chipmunk user data
    /// @endcond
  private:
    struct Storage;
    std::unique_ptr<Storage> mStorage;
    AnimationPhysicsDefinition mDefinition;
    std::vector<AnimationPhysicsBody> mGeometryReference;
    struct GeometryJoint { std::shared_ptr<PhysicsConstraint> constraint; Point a,b; };
    std::vector<GeometryJoint> mGeometryJoints;
    std::vector<Offset> mGeometryFactors;
    std::shared_ptr<const AnimationRig> mRig;
    std::vector<AnimationBoneId> mOrder;
    struct Control;
    std::unique_ptr<Control> mControl;
    AnimationTransform targetFrame(uint32_t index, const AnimationPose&, const AnimationTransform&) const;
    void configureMode(uint32_t index, int mode);
    void prepareControls(const AnimationPose&, const AnimationTransform&, double);
    void validatePose(const AnimationPose &pose, const AnimationTransform &root) const;
};
#endif
/** @} */

} // namespace pdg
#endif
