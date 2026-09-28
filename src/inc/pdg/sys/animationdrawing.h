#ifndef PDG_ANIMATION_DRAWING_H_INCLUDED
#define PDG_ANIMATION_DRAWING_H_INCLUDED
#include "pdg/sys/animationcontroller.h"
#include <array>
namespace pdg {

/** \addtogroup AnimationDrawing
 * @{
 */
class Drawing;
enum AnimationDrawPlacement : int {
    animationDraw_BeforeAll = 0,
    animationDraw_AfterAll = 1,
    animationDraw_BeforeSlot = 2,
    animationDraw_AfterSlot = 3,
    animationDraw_ReplaceSlot = 4
};
enum AnimationStrokeSpace : int { animationStroke_PortPixels = 0, animationStroke_Local = 1 };
using AnimationDrawableId = uint32_t;
struct AnimationDrawBounds {
    double left = 0, top = 0, right = 0, bottom = 0;
    bool uncullable = true;
};
struct AnimationDrawableOptions {
    AnimationBoneId bone = animation_NoBone;
    int placement = animationDraw_AfterAll, order = 0;
    int strokeSpace = animationStroke_PortPixels;
    std::string slot;
    AnimationDrawBounds bounds;
};
AnimationDrawableOptions decodeAnimationDrawableOptions(const std::vector<double> &values,
                                                        const std::string &slot);
struct AnimationDrawingSubmission {
    AnimationDrawableId drawable = 0;
    int strokeSpace = animationStroke_PortPixels;
    AnimationTransform world;
    std::shared_ptr<Drawing> drawing;
};
class AnimationDrawingContext {
  public:
    AnimationTransform getTransform(int space = animationSpace_World) const;
    AnimationPose copyPose() const;

  private:
    friend class AnimationDrawings;
    struct Lease {
        const AnimationPose *pose;
        AnimationBoneId bone;
        AnimationTransform root;
    };
    explicit AnimationDrawingContext(std::shared_ptr<Lease> lease) : mLease(std::move(lease)) {}
    void check() const;
    std::shared_ptr<Lease> mLease;
};
class AnimationDrawings {
    /// @cond INTERNAL
    friend class Sprite;
    friend class SpriteAnimationSnapshot;
    /// @endcond
  public:
    using Callback = std::function<std::shared_ptr<Drawing>(AnimationDrawingContext)>;
    AnimationDrawableId add(const AnimationDrawableOptions &options, Callback callback,
                            const AnimationRig &rig);
    void remove(AnimationDrawableId id);
    void clear();
    void setEnabled(AnimationDrawableId id, bool enabled);
    bool isEnabled(AnimationDrawableId id) const;
    std::string error(AnimationDrawableId id) const;
    void fail(AnimationDrawableId id, const std::string &error);
    void beginFrame();
    void endFrame();
    bool isDrawing() const {
        return mDrawing;
    }
    bool empty() const {
        return mEntries.empty();
    }
    std::vector<AnimationDrawingSubmission> collect(int placement, const std::string &slot,
                                              const AnimationPose &pose,
                                              const AnimationTransform &root);
    std::vector<AnimationDrawableOptions> options() const;

  private:
    struct Entry {
        AnimationDrawableId id;
        AnimationDrawableOptions options;
        Callback callback;
        std::shared_ptr<Drawing> constantDrawing;
        bool enabled = true;
        std::string error;
    };
    std::shared_ptr<Entry> find(AnimationDrawableId id) const;
    void change(std::function<void()> action);
    std::vector<std::shared_ptr<Entry>> mEntries, mFrame;
    std::vector<std::function<void()>> mPending;
    AnimationDrawableId mNextId = 1;
    bool mDrawing = false;
};
/** @} */

} // namespace pdg
#endif
