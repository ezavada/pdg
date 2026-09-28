#include "pdg/sys/animationdrawing.h"
#ifndef PDG_NO_GUI
#include "pdg/sys/drawing.h"
#endif
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace pdg {
namespace {
void require(bool ok, const char *error) {
    if (!ok)
        throw std::invalid_argument(error);
}
} // namespace
AnimationDrawableOptions decodeAnimationDrawableOptions(const std::vector<double> &values,
                                                        const std::string &slot) {
    require(values.size() == 9, "Invalid drawing options");
    for (double value : values)
        require(std::isfinite(value), "Invalid drawing options");
    require(values[0] >= 0 && values[0] < animation_NoBone && values[0] == std::floor(values[0]),
            "Invalid drawing bone");
    require(values[1] >= 0 && values[1] <= 4 && values[1] == std::floor(values[1]),
            "Invalid drawing placement");
    require(values[2] >= -2147483648.0 && values[2] <= 2147483647.0 &&
                values[2] == std::floor(values[2]),
            "Invalid drawing order");
    require(values[3] == 0 || values[3] == 1, "Invalid uncullable flag");
    AnimationDrawableOptions result;
    result.bone = static_cast<uint32_t>(values[0]);
    result.placement = static_cast<int>(values[1]);
    result.order = static_cast<int>(values[2]);
    require(values[8] == 0 || values[8] == 1,
            "Invalid drawing stroke space");
    result.strokeSpace = static_cast<int>(values[8]);
    result.slot = slot;
    result.bounds = {values[4], values[5], values[6], values[7], values[3] != 0};
    return result;
}
void AnimationDrawingContext::check() const {
    if (!mLease || !mLease->pose)
        throw std::logic_error("Animation drawing context has expired");
}
AnimationTransform AnimationDrawingContext::getTransform(int space) const {
    check();
    if (space == animationSpace_Local)
        return mLease->pose->getLocalTransform(mLease->bone);
    if (space == animationSpace_Rig)
        return mLease->pose->getGlobalTransform(mLease->bone);
    if (space == animationSpace_World)
        return mLease->pose->getWorldTransform(mLease->bone, mLease->root);
    throw std::invalid_argument("Invalid drawing coordinate space");
}
AnimationPose AnimationDrawingContext::copyPose() const {
    check();
    return mLease->pose->copy();
}
std::shared_ptr<AnimationDrawings::Entry> AnimationDrawings::find(AnimationDrawableId id) const {
    for (const auto &entry : mEntries)
        if (entry->id == id)
            return entry;
    throw std::out_of_range("Unknown animation drawable ID");
}
void AnimationDrawings::change(std::function<void()> action) {
    if (mDrawing)
        mPending.push_back(std::move(action));
    else
        action();
}
AnimationDrawableId AnimationDrawings::add(const AnimationDrawableOptions &options,
                                           Callback callback, const AnimationRig &rig) {
    require(bool(callback), "Drawing callback is required");
    rig.getBone(options.bone);
    require(options.strokeSpace == animationStroke_PortPixels || options.strokeSpace == animationStroke_Local,
            "Invalid drawing stroke space");
    require(options.placement >= animationDraw_BeforeAll &&
                options.placement <= animationDraw_ReplaceSlot,
            "Invalid drawing placement");
    if (options.placement >= animationDraw_BeforeSlot) {
        const auto id = rig.findBinding(options.slot);
        require(id != animation_NoBinding && rig.getBinding(id).kind == animationBinding_Image,
                "Drawing slot must name an image binding");
    } else
        require(options.slot.empty(), "Whole-sprite drawing placement cannot name a slot");
    const auto &b = options.bounds;
    require(std::isfinite(b.left) && std::isfinite(b.top) && std::isfinite(b.right) &&
                std::isfinite(b.bottom) && b.left <= b.right && b.top <= b.bottom,
            "Invalid local drawing bounds");
    if (!mNextId)
        throw std::overflow_error("Animation drawable IDs exhausted");
    auto entry = std::make_shared<Entry>();
    entry->id = mNextId++;
    entry->options = options;
    entry->callback = std::move(callback);
    change([this, entry] { mEntries.push_back(entry); });
    return entry->id;
}
void AnimationDrawings::remove(AnimationDrawableId id) {
    change([this, id] {
        std::erase_if(mEntries, [id](const auto &e) { return e->id == id; });
    });
}
void AnimationDrawings::clear() {
    change([this] { mEntries.clear(); });
}
void AnimationDrawings::setEnabled(AnimationDrawableId id, bool enabled) {
    auto entry = find(id);
    require(!enabled || bool(entry->callback), "Failed drawable must be registered again");
    change([entry, enabled] { entry->enabled = enabled; });
}
bool AnimationDrawings::isEnabled(AnimationDrawableId id) const {
    return find(id)->enabled;
}
std::string AnimationDrawings::error(AnimationDrawableId id) const {
    return find(id)->error;
}
void AnimationDrawings::fail(AnimationDrawableId id, const std::string &error) {
    auto e = find(id);
    e->error = error;
    e->enabled = false;
    e->callback = {};
}
void AnimationDrawings::beginFrame() {
    if (mDrawing)
        throw std::logic_error("Recursive animation drawing is not allowed");
    mFrame = mEntries;
    std::stable_sort(mFrame.begin(), mFrame.end(), [](const auto &a, const auto &b) {
        return a->options.order < b->options.order;
    });
    mDrawing = true;
}
void AnimationDrawings::endFrame() {
    mDrawing = false;
    mFrame.clear();
    auto pending = std::move(mPending);
    mPending.clear();
    for (auto &action : pending)
        action();
}
std::vector<AnimationDrawingSubmission> AnimationDrawings::collect(int placement, const std::string &slot,
                                                             const AnimationPose &pose,
                                                             const AnimationTransform &root) {
    require(mDrawing, "Drawing collection requires a frame");
    std::vector<AnimationDrawingSubmission> result;
#ifndef PDG_NO_GUI
    for (const auto &e : mFrame) {
        if (!e->enabled || e->options.placement != placement || e->options.slot != slot)
            continue;
        auto lease = std::make_shared<AnimationDrawingContext::Lease>(
            AnimationDrawingContext::Lease{&pose, e->options.bone, root});
        struct Expire {
            std::shared_ptr<AnimationDrawingContext::Lease> lease;
            ~Expire() {
                lease->pose = nullptr;
            }
        } expire{lease};
        try {
            AnimationCallbackScope scope;
            auto drawing = e->callback(AnimationDrawingContext(lease));
            if (drawing)
                result.push_back({e->id, e->options.strokeSpace,
                    pose.getWorldTransform(e->options.bone, root), std::move(drawing)});
        } catch (const std::exception &error) {
            fail(e->id, error.what());
        } catch (...) {
            fail(e->id, "Animation drawable failed");
        }
    }
#endif
    return result;
}
std::vector<AnimationDrawableOptions> AnimationDrawings::options() const {
    std::vector<AnimationDrawableOptions> result;
    for (const auto &e : mEntries)
        if (e->enabled)
            result.push_back(e->options);
    return result;
}
} // namespace pdg
