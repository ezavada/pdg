#ifndef PDG_PART_H_INCLUDED
#define PDG_PART_H_INCLUDED

#include "pdg/sys/animated.h"
#include "pdg/sys/physicsbody.h"
#include "pdg/sys/collider.h"
#include "pdg/sys/spatialtransform.h"
#include "pdg/sys/animationcontroller.h"
#include <cstdint>
#include <limits>
#include <memory>
#include <string>

namespace pdg {
class Sprite;
class AnimationRig;
class Drawing;
class Image;
using PartId = uint32_t;
using BoneId = uint32_t;
constexpr PartId partId_None = std::numeric_limits<PartId>::max();
constexpr BoneId boneId_None = std::numeric_limits<BoneId>::max();
enum PartPlacement : int { partPlacement_Snap = 0, partPlacement_PreserveWorld = 1 };
enum PartSpace : int { partSpace_Local = 0, partSpace_Sprite = 1, partSpace_World = 2 };

/** Independently animated subsection owned by a Sprite.
 * @ingroup Animation
 * Construct through Sprite::createPart(). The Sprite retains one reference;
 * native callers retaining a Part across removal must addRef()/release(). Script
 * references retain automatically. Removal detaches rather than invalidating a
 * retained Part; it keeps its local state and stops automatic updates.
 *
 * Inherited setters and getters operate in its local frame. This is the Sprite
 * frame by default, a bound bone's frame, or an explicit parent Part's frame.
 * Rebinding/reparenting preserves local state. Logical dimensions/pivot do not
 * change this frame. World denotes owning-layer coordinates, not screen pixels.
 * Artwork, controllers and physics are separate associations.
 */
class Part : public Animated<Part> {
    friend class Bone;
    friend class PhysicsBodyRef<Part>;
    friend class ColliderRef<Part>;
    void initializePhysicsBody(PhysicsBody& body, bool restoring = false);
    void installPhysicsPublisher(PhysicsBody& body);
    friend class Sprite;
    /// @cond INTERNAL
    friend class PhysicsGraphSnapshot;
    friend class SpriteAnimationSnapshot;
    /// @endcond
    friend class SpriteLayer;
    friend class SpriteManager;
    friend class PartWrap;
public:
    /** Optional body; querying never creates one. Returned references are borrowed.
     * Convert physics to PhysicsBody& and retain with addRef/release to keep
     * that body after removal. Only setupPhysicsBody()/removePhysicsBody()
     * change the association; callers cannot assign this member. Immediate transform
     * setters teleport it; dynamic bodies reject programmed movement/spin.
     */
    PhysicsBodyRef<Part> physics;
    /** Optional collision geometry; reading never creates a collider. */
    ColliderRef<Part> collider;
    Collider& setupCollider();
    /** Follow owned Drawing bounds or Image alpha, or the current image of an
     * explicitly bound animation image. Drawings with vector/multiple elements
     * require Bounds. Empty content contributes no source shapes. */
    Collider& setupFrameCollider(int mode = frameCollider_AlphaMask, int alphaThreshold = 128);
    /** Follow one named authored box in the owner's enabled pose. Captures the
     * current local offset; later local edits move the collider with this Part.
     * An invalidated source rig contributes no source shapes. */
    Collider& setupAnimationCollider(const std::string& boxName);
    void removeCollider();
    /** Set up the associated body, applying mass and inertia on every call.
     * Omitted arguments use 1, including when a body already exists.
     * Retains an existing body's identity, motion, mode and constraints.
     * Read physics to access the body without reconfiguring it.
     */
    PhysicsBody& setupPhysicsBody(double mass = 1, double momentOfInertia = 1);
    void removePhysicsBody();

    PartId getId() const { return mId; }
    const std::string& getName() const { return mName; }
    Sprite* getSprite() const { return mSprite; }
    /// @cond INTERNAL
    ISerializable* snapshotAnimationOwner() const override;
    uint32 snapshotAnimationId() const override { return mId; }
    /// @endcond
    bool isAttached() const { return mSprite != nullptr; }
    BoneId getBoneId() const;
    bool isBoundToBone() const { return getBoneId() != boneId_None; }
    Part& bindToBone(BoneId bone);
    Part& unbindFromBone();
    /** Follow an authored artwork binding or socket; local animation remains an offset.
     * Replacing the rig invalidates this relationship safely. No artwork is duplicated.
     */
    Part& bindToAnimationBinding(const std::string& name);
    Part& bindToAnimationSocket(const std::string& name);
    std::string getAnimationBindingName() const;
    std::string getAnimationSocketName() const;
    /** Retain editable Drawing contents, or an Image represented by a local rectangle.
     * Artwork is drawn after the owner's original artwork in Part creation order.
     * It changes no Part identity, logical size, local transforms or body association.
     */
    Part& setDrawing(const Drawing& drawing);
    Part& setImage(const Image& image, const Rect& localBounds);
    Part& clearContent();
    bool hasContent() const { return bool(mDrawing); }
    Rect getContentBounds(int space = partSpace_Local) const;
    /** Solve an explicit two-segment Part chain, without a skeleton or artwork.
     * middle must be this Part's child; tip must be middle's child. Their local
     * offsets define segment lengths. Target space Local is this Part's parent
     * frame. Root local scale must have equal absolute axes; ancestors may have
     * arbitrary invertible affine transforms. bendDirection is +1 or -1.
     * Returns whether the tip reaches the target after applying influence.
     * Dynamic bodies reject direct IK; run before kinematic/physical publication.
     */
    bool solveIK(Part* middle, Part* tip, const Point& target,
                 int space = partSpace_World, int bendDirection = 1, double influence = 1);
    /** Keep solving this chain after Part animation and before physics each step.
     * The chain owns root/middle rotation channels until cleared. Overlapping
     * controllers are rejected. Dynamic bodies require physical drives instead.
     * Invalidated topology holds the current pose and records an error; solving
     * resumes if the chain becomes valid again. Targets use floating-point positions.
     */
    Part& setIKTarget(Part* middle, Part* tip, const Point& target,
                     int space = partSpace_World, int bendDirection = 1, double influence = 1);
    Part& clearIKTarget();
    bool hasIKTarget() const { return bool(mIKTarget)||bool(mFABRIK); }
    bool isIKTargetReached() const;
    /** Limit this joint's local IK rotation in radians; does not constrain physics itself. */
    Part& setIKLimits(double minAngle, double maxAngle);
    /** Retain live rotary limits between this body and its parent Part/Sprite body.
     * Either endpoint order is accepted. Unsupported frames and inactive links throw.
     * Clearing the IK link does not disconnect the physical constraint.
     */
    Part& setIKLimits(PhysicsConstraint& constraint);
    Part& clearIKLimits();
    bool hasIKLimits() const { return mHasIKLimits; }
    double getIKMinAngle() const;
    double getIKMaxAngle() const;
    /** Drive a desired two-segment pose without writing dynamic transforms.
     * Root and middle require dynamic bodies; tip may have a dynamic body or none.
     * Captures joint offsets on installation; repeated targets on the same chain
     * keep those offsets. Physical constraints remain caller-configured.
     */
    Part& setIKDriveTarget(Part* middle, Part* tip, const Point& target,
        double maxForce, double maxTorque, int space = partSpace_World,
        int bendDirection = 1, double influence = 1, double frequency = 4, double dampingRatio = 1);
    bool isIKDriven() const { return mIKTarget && mIKTarget->physical; }
    const std::string& getIKError() const { return mIKError; }
    /// Solve or schedule a contiguous independent Part chain; chain excludes the receiver. See \ref native_procedural_animation.
    AnimationFABRIKResult solveFABRIK(const std::vector<Part*>& following, const Point& target, const AnimationFABRIK& options = {});
    /// Solve or schedule a contiguous independent Part chain; chain excludes the receiver. See \ref native_procedural_animation.
    Part& setFABRIKTarget(const std::vector<Part*>& following, const Point& target, const AnimationFABRIK& options = {});
    /// Return the latest scheduled FABRIK diagnostics. See \ref native_procedural_animation.
    AnimationFABRIKResult getFABRIKResult() const;
    /// Install chain jiggle or decorate an existing Part IK target. See \ref native_procedural_animation.
    Part& setJiggle(const AnimationJiggle& config, const std::vector<Part*>& following = {});
    /// Remove jiggle and restore the underlying programmed rotations. See \ref native_procedural_animation.
    Part& clearJiggle();
    /// Return whether this Part owns a jiggle controller. See \ref native_procedural_animation.
    bool hasJiggle() const { return bool(mJiggle); }
    /// Return an independent configuration record. See \ref native_procedural_animation.
    AnimationJiggle getJiggleOptions() const;
    /// Replace tuning from a complete configuration without changing topology. See \ref native_procedural_animation.
    Part& setJiggleSettings(const AnimationJiggle& settings);
    /// Enable or freeze jiggle; reenabling reseeds from the current pose. See \ref native_procedural_animation.
    Part& setJiggleEnabled(bool);
    /// Return whether jiggle is enabled. See \ref native_procedural_animation.
    bool isJiggleEnabled() const;
    /// Set or linearly fade influence using simulation seconds. See \ref native_procedural_animation.
    Part& setJiggleInfluence(double influence, double seconds = 0);
    /// Reseed jiggle from the desired pose or target. See \ref native_procedural_animation.
    Part& resetJiggle();
    /// Add angular or target velocity. See \ref native_procedural_animation.
    Part& kickJiggle(double x, double y = 0, int joint = 0);
    /// Return the most recently evaluated jiggle diagnostics. See \ref native_procedural_animation.
    JiggleResult getJiggleResult() const;
    /// Return an independent numerical state snapshot. See \ref native_procedural_animation.
    JiggleState getJiggleState() const;
    /// Restore validated numerical state on the same topology. See \ref native_procedural_animation.
    Part& setJiggleState(const JiggleState&);
    const std::string& getJiggleError() const { return mProceduralError; }
    /// @cond INTERNAL
    /// \internal Numeric binding transport.
    std::vector<double> proceduralControl(int operation, const std::vector<double>& values);
    /// @endcond
    /** Create an animated mounting Part below this Part and retain a child Sprite.
     * The optional childMount is sampled once in the child's frame. Both Sprites
     * must be in the same layer, or both off-layer. The child may have no body or
     * a kinematic body; direct physical motion and other modes reject while mounted.
     * Layer removal preserves the
     * mounted group; adding the host to a layer carries its descendants. Detach a
     * child before removing or transferring it independently. The returned mount owns the follow offset; animate
     * that Part rather than editing the attached child's root. Child playback,
     * opacity and layer draw order remain independent. Sheared root placement is
     * rejected; later invalid placements hold the last pose and expose an error.
     */
    Part* attachSprite(Sprite* child, int placement = partPlacement_Snap, Part* childMount = nullptr);
    Sprite* getAttachedSprite() const { return mAttachedSprite; }
    Part& detachSprite();
    const std::string& getAttachmentError() const { return mAttachmentError; }
    Part* getParentPart() const { return mParent; }
    Part& setParentPart(Part* parent);
    SpatialTransform getTransform(int space = partSpace_Local) const;
    /** Advance local programming and publish its body; owned Parts already step with their Sprite. */
    bool animate(double seconds) override;

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mPartScriptObj;
#endif

protected:
    ~Part() override;
private:
    void adoptMotionSnapshot(const Part&);
    PhysicsConstraint* mIKConstraint = nullptr;
    bool validateIKLimitConstraint(const PhysicsConstraint& constraint) const;
    void validateIKJoint(const Part& child, const Point& offset) const;
    bool mHasIKLimits = false;
    double mIKMinAngle = 0, mIKMaxAngle = 0;
    struct IKTarget {
        ~IKTarget();
        Part* owner = nullptr;
        bool physical = false, ownsDrives = false;
        PhysicsBody* bodies[3] = {nullptr, nullptr, nullptr};
        Point rootOffset, middleOffset, tipOffset;
        float tipAngle = 0;
        double maxForce = 0, maxTorque = 0, frequency = 4, dampingRatio = 1;
        void stopDrives();
        PartId middle, tip;
        Point target;
        int space, bend;
        double influence;
        bool reached = false;
    };
    struct IKSolution {
        float rootAngle, middleAngle;
        Point worldTarget;
        double tolerance;
    };
    std::unique_ptr<IKTarget> mIKTarget;
    struct PartFABRIKState { AnimationFABRIK config; std::vector<PartId> chain; AnimationFABRIKResult result; };
    std::unique_ptr<PartFABRIKState> mFABRIK;
    std::shared_ptr<SpriteJiggleState> mJiggle;
    std::vector<PartId> mJiggleChain;
    Part* mProceduralOwner = nullptr;
    float mProceduralBase = 0;
    bool mApplyingProcedural = false;
    std::string mProceduralError;
    std::vector<Part*> proceduralParts(const std::vector<PartId>&) const;
    AnimationPose proceduralPose(const std::vector<Part*>&, AnimationTransform&) const;
    void applyProceduralPose(const std::vector<Part*>&, const AnimationPose&, size_t count);
    void claimProcedural(const std::vector<Part*>&);
    void releaseProcedural();
    bool stepProcedural(double seconds);
    void restoreProceduralBase();
    std::string mIKError;
    IKSolution calculateIK(Part* middle, Part* tip, const Point& target,
                           int space, int bendDirection, double influence, const IKTarget* drive = nullptr) const;
    void validateIKOverlap(Part* middle, Part* tip, bool physical) const;
    bool applyIKTarget(double seconds = 0);
    void stepPhysics(double seconds);
    Part(Sprite* sprite, PartId id, const std::string& name);
    void validateSnapshot(bool layerGraph) const;
    void detach();
    bool mPublishingPhysics = false;
    bool mAnimationPhysicsBody = false;
    void initializeAnimationPhysicsBody(PhysicsBody& body);
    void validateTransformEdit() const override;
    void validateProgrammedTransform() const override;
    void locationChanged(const Offset&) override;
    void rotationChanged(float) override;
    void scaleChanged(const Offset&) override;
    void flipChanged(bool, bool) override;
    SpatialTransform physicsFrame() const;
    SpatialTransform sourceFrame() const;
    void syncPhysicsTransform();
    void syncPhysicsSolver();
    Sprite* mSprite;
    PartId mId;
    const std::string mName;
    Part* mParent = nullptr;
    size_t mChildCount = 0;
    void setParentLink(Part* parent);
    void refreshDependents();
    BoneId mBone = boneId_None;
    std::shared_ptr<const AnimationRig> mRig;
    uint32_t mBinding = std::numeric_limits<uint32_t>::max();
    uint32_t mSocket = std::numeric_limits<uint32_t>::max();
    bool hasCurrentRig() const;
    std::shared_ptr<Drawing> mDrawing;
    void drawContent();
    Sprite* mAttachedSprite = nullptr;
    SpatialTransform mChildMountInverse;
    std::string mAttachmentError;
    void updateAttachment();
    static void decomposeMount(const SpatialTransform& transform, Point& location, float& angle, Offset& scale);
};
}
#endif
