#ifndef PDG_BONE_H_INCLUDED
#define PDG_BONE_H_INCLUDED
#include "pdg/sys/animated.h"
#include "pdg/sys/animationpose.h"
#include "pdg/sys/physicsconstraint.h"
#include <array>
#include <optional>
namespace pdg {
class Sprite;
#ifdef PDG_SPRITER_SUPPORT
/** Animated controls over one bone in a Sprite's current rig.
 * Absolute operations override individual channels; relative operations modify
 * fresh authored samples. Handles become invalid when their rig is replaced.
 * @ingroup Animation
 *
 * Obtain a borrowed handle with Sprite::getBone(). Native callers retaining a
 * handle beyond its Sprite/rig lifetime must addRef()/release() it. isAttached()
 * remains safe after invalidation; other reads and edits throw.
 *
 * Position, rotation (radians), scale and attachment coordinates are local to
 * the authored parent. Absolute operations acquire only selected channels.
 * Relative movement/rotation and changeScaleBy add to each fresh clip sample. Completed controls persist until changed or released with diminish().
 *
 * Height is longitudinal bone length; width is its transverse dimension.
 * Resize moves children proportionally without scaling their artwork. Scale
 * and flip affect the full descendant hierarchy. Imported bone axes are preserved.
 * Initial dimensions use child connections (or unit length for a terminal bone);
 * physical bones use the dimensions of their capsule.
 * centerOffset is the attachment to the parent, relative to the reference pose.
 *
 * Sprite advances controls once per update, even while its authored clip is
 * paused. Schedule pause/cancel operations affect only these controls. Pose
 * queries never advance clocks. Controls run before modifiers/IK; final local
 * rotations are clamped afterwards. Physical bodies receive animation targets;
 * dynamic bodies remain under solver control. Disable animation physics before
 * scaling or reflecting a single bone; resize supports live capsule geometry.
 */
class Bone : public Animated<Bone> {
    friend class Sprite;
public:
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mBoneScriptObj;
#endif
    uint32 getSerializedSize(ISerializer*) const override;
    void serialize(ISerializer*) const override;
    void deserialize(IDeserializer*) override;
    AnimationBoneId getId() const { validateScriptRead(); return mId; }
    const std::string& getName() const { validateScriptRead(); return mRig->getBone(mId).name; }
    Sprite* getSprite() const { validateScriptRead(); return mOwner; }
    bool isAttached() const { return mOwner!=nullptr; }
    /// Ease scripted influence toward [0,1]; zero releases channels to the running clip.
    Bone& diminish(float influence,double seconds,EasingFunc easing=linearTween);
    float getInfluence() const { validateScriptRead(); return mInfluence; }
    Offset getCenterOffset() const override;
    Rect getBoundingBox() const override;
    RotatedRect getRotatedBounds() const override;
    Point getLocation() const override;
    float getRotation() const override;
    Offset getScale() const override;
    Offset getSize() const override;
    float getWidth() const override { return getSize().x; }
    float getHeight() const override { return getSize().y; }
    /// Set finite ordered local angle limits in radians, spanning at most one turn.
    Bone& setIKLimits(double minimum,double maximum);
    /// Reuse an active rotary limit joining this bone's physical Part and its parent.
    Bone& setIKLimits(PhysicsConstraint& constraint);
    Bone& clearIKLimits();
    bool hasIKLimits() const;
    double getIKMinAngle() const;
    double getIKMaxAngle() const;
    // Internal pose evaluation: clocks are advanced by Sprite, never by getters.
    void apply(AnimationPose& pose,bool constraintsOnly=false);
    void sample(const AnimationPose& pose);
    void invalidate();
    std::optional<std::pair<double,double>> rotationLimits(const AnimationPose&) const;
protected:
    Bone(Sprite*,std::shared_ptr<const AnimationRig>,AnimationBoneId);
    ~Bone() override;
    void validateScriptRead() const override;
    void validateTransformEdit() const override;
    void validateProgrammedTransform() const override { validateTransformEdit(); }
    bool prepareSampledAnimation(unsigned,uint8,float) override;
    void validateSampledRequest(std::initializer_list<ScriptValue>,double,EasingFunc,uint8) const override;
    bool diminishSampled(float factor,double seconds,EasingFunc easing) override { diminish(factor,seconds,easing);return true; }
    std::vector<const float*> tweenFields() const override;
    void animationValuesChanged() override;
    uint32 scriptClassTag() const override { return CLASSTAG_BONE; }
    void locationChanged(const Offset&) override { animationValuesChanged(); }
    void sizeChanged(float,float) override { animationValuesChanged(); }
    void rotationChanged(float) override { animationValuesChanged(); }
    void scaleChanged(const Offset&) override { animationValuesChanged(); }
    void centerChanged(const Offset&) override { animationValuesChanged(); }
    void flipChanged(bool,bool) override;
private:
    Sprite* mOwner;
    std::shared_ptr<const AnimationRig> mRig;
    AnimationBoneId mId;
    AnimationTransform mSample;
    std::array<int,15> mModes;
    double mReferenceWidth=1,mReferenceHeight=1;
    float mInfluence=1;
    PhysicsConstraint* mLimit=nullptr;
    bool mHasLimits=false;
    double mMinimum=0,mMaximum=0;
    const void* mGeometryRig=nullptr;
};
#endif // PDG_SPRITER_SUPPORT
}
#endif
