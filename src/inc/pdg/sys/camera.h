#ifndef PDG_CAMERA_H_INCLUDED
#define PDG_CAMERA_H_INCLUDED

#include "pdg/sys/animated.h"
#include "pdg/sys/eventemitter.h"
#include "pdg/sys/spatialtransform.h"
#include <algorithm>
#include <array>

namespace pdg {
class Port;
class SpriteLayer;
class Scene;
class Image;
class Sprite;
/// Reference shot and optional projected-size matching for a camera match cut.
enum CameraMatchMode : int {
    matchSource = 0,       ///< Preserve the source shot; align the incoming camera.
    matchSourceAndSize,    ///< Match the source shot's framing, apparent size and size rate.
    matchTarget,           ///< Approach the target shot by adjusting the outgoing camera.
    matchTargetAndSize     ///< Approach the target shot's framing and apparent size.
};
struct CameraMatchOptions {
    Sprite* matchSource = nullptr;
    Sprite* matchTarget = nullptr;
    CameraMatchMode mode = pdg::matchSource;
    double approachSeconds = .4, settleSeconds = .4;
    double fadeSeconds = .4;
    EasingFunc fadeEasing = linearTween;
    bool settleReturnsCamera = false;
    EasingFunc approachEasing = easeInQuad, settleEasing = easeOutQuad;
};
/// Wipe names specify the direction traveled by the destination reveal boundary.
enum CameraTransition {
    camera_Crossfade = 0,
    camera_WipeLeft,
    camera_WipeRight,
    camera_WipeUp,
    camera_WipeDown,
    camera_LumaFade,
    camera_WhipLeft,
    camera_WhipRight,
    camera_WhipUp,
    camera_WhipDown
};
/** \brief Animated view owned by a Port or shared by layers.
 * \ingroup Animation Graphics
 * Each Port owns its camera. A layer uses its retained explicit camera, otherwise
 * its port's built-in camera. Layer cameras own their destination viewport.
 * Location plus center offset maps to the Port anchor or layer viewport center.
 * Rotation is the view's world orientation; zoom and scale magnify the view.
 * Size is animation metadata and does not resize the destination viewport.
 */
class Camera : public Animated<Camera>, public EventEmitter {
public:
    Camera();
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
    uint32 getMyClassTag() const override { return CLASSTAG_CAMERA; }
    uint32 getSerializedSize(ISerializer*) const override;
    void serialize(ISerializer*) const override;
    void deserialize(IDeserializer*) override;
    static ISerializable* CreateInstance() { return new Camera(); }
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mCameraScriptObj;
#endif
    ~Camera() override;
    bool animate(double seconds) override;
    /// Follow a checked weak Animated target in world coordinates; position ownership
    /// lasts until stopFollowing(). Rotation and zoom remain independently animated.
    Camera& follow(AnimatedBase& target);
    Camera& stopFollowing();
    bool isFollowing() const { return followedTarget()!=nullptr; }
    /// Exponential position smoothing time constant in seconds; zero snaps.
    Camera& setSmoothing(double seconds);
    double getSmoothing() const { return mSmoothing; }
    /// Predict target position from measured velocity, in seconds; initially zero.
    Camera& setLookAhead(double seconds);
    double getLookAhead() const { return mLookAhead; }
    /// World-space target offsets from camera focus that do not move the camera.
    Camera& setDeadzone(const Rect& bounds);
    Rect getDeadzone() const { return mDeadzone; }
    Camera& setFollowOffset(const Offset& offset);
    Offset getFollowOffset() const { return mFollowOffset; }
    /// Constrain each attachment's visible world footprint without altering pose.
    Camera& setViewBounds(const Rect& bounds);
    Camera& clearViewBounds() {
        if(recordOperation("clearViewBounds", captureAnimationArguments())) return *this;
        mHasViewBounds = false;
        return *this;
    }
    bool hasViewBounds() const { return mHasViewBounds; }
    Rect getViewBounds() const { return mViewBounds; }
    /// Conversions for a view centered within a port-coordinate viewport.
    Camera& setViewport(const Rect& viewport);
    Rect getViewport() const;
    Point worldToView(const Point& point) const;
    Point viewToWorld(const Point& point) const;
    /// Magnification independent of Animated's nonuniform scale; initially 1.
    float getZoom() const { return mZoom; }
    /** \brief Set view magnification immediately.
     * \param zoom Finite positive factor; 2 doubles the apparent content size.
     * \return This camera for chaining.
     * Throws for invalid zoom or an immediate operation in a timed sequence.
     */
    Camera& setZoom(float zoom);
    /** \brief Animate view magnification.
     * \param zoom Finite positive target factor.
     * \param seconds Finite nonnegative duration in seconds; zero applies immediately.
     * \param easing Easing function; defaults to easeInOutQuad.
     * \return This camera for chaining.
     * Emits eventType_ZoomComplete on this camera when completed.
     * Cancelled or replaced operations do not emit completion.
     * Participates in wait(), andThen(), cancellation and schedule pause/resume.
     */
    Camera& zoomTo(float zoom, double seconds, EasingFunc easing = easeInOutQuad);
    /** \brief Animate magnification by a positive factor.
     * \param factor Finite positive multiplier; 2 doubles zoom, 0.5 halves it.
     * \param seconds Finite nonnegative duration in seconds.
     * \param easing Easing function; defaults to easeInOutQuad.
     * \return This camera for chaining.
     * Queued factors apply to zoom when the operation starts.
     */
    Camera& zoom(float factor, double seconds, EasingFunc easing = easeInOutQuad);
    /** \brief Round final view translation to pixels without changing camera pose.
     * \param snap Enable snapping; false by default on a new camera.
     * \return This camera for chaining.
     */
    Camera& setPixelSnapping(bool snap = true) {
        if(recordOperation("setPixelSnapping", captureAnimationArguments(snap))) return *this;
        mPixelSnapping = snap;
        return *this;
    }
    bool getPixelSnapping() const { return mPixelSnapping; }
    /** \brief Compose the world-to-port affine view.
     * \param anchor Destination point receiving the camera's location plus pivot.
     * \param movementRatio Multiply camera location for attachment parallax.
     * \param zoomRatio Raise camera zoom to this power for attachment parallax.
     * \param viewport Destination port rectangle used to constrain visible-world bounds; an empty rectangle skips bounds clamping.
     * \return View including inverse rotation, zoom, scale, reflection and translation.
     * Throws for a nonfinite transform or zero scale. Use inverse() for port-to-world.
     * Size does not affect the viewport; rotation uses radians. At unit parallax,
     * location + centerOffset maps to anchor, and positive rotation turns the view
     * opposite to content. Manual animate(seconds) additionally advances state;
     * attached cameras are already advanced once per runtime tick.
     */
    SpatialTransform getViewTransform(const Point& anchor = Point(), float movementRatio = 1, float zoomRatio = 1, const Rect& viewport = Rect()) const;
    /// Runtime advances attached cameras once, regardless of attachment count.
    static void advanceAttached(double seconds);
    /// Internal attachment ownership, shared by Port and SpriteLayer.
    void attach();
    Scene* mSceneOwner = nullptr; // automatic advancement belongs to one scene
    void detach();
    /// Independent transient stage, advanced once by this camera. Cannot be attached.
    Camera& getEffects();
    /// Set white overlay opacity at operation start, then fade to zero.
    Camera& flash(float opacity, double seconds, EasingFunc easing = easeOutQuad);
    float getFlashOpacity() const { return std::clamp(mFlashOpacity+(mEffects?mEffects->mFlashOpacity:0),0.f,1.f); }
    /// Visibility affects composed rendering and picking, never animation or physics.
    Camera& show();
    Camera& hide();
    bool isHidden() const { return mHidden >= .5f; }
    Camera& setOpacity(float opacity);
    float getOpacity() const { return std::clamp(mOpacity,0.f,1.f); }
    Camera& fadeTo(float opacity, double seconds, EasingFunc easing = linearTween);
    Camera& fadeIn(double seconds, EasingFunc easing = linearTween) {
        if(recordOperation("fadeIn", captureAnimationArguments(seconds, easing))) return *this;
        return fadeTo(1,seconds,easing);
    }
    Camera& fadeOut(double seconds, EasingFunc easing = linearTween) {
        if(recordOperation("fadeOut", captureAnimationArguments(seconds, easing))) return *this;
        return fadeTo(0,seconds,easing);
    }
    /// Hide this camera and show the destination atomically when scheduled.
    /// Works with independent viewports/Ports and unattached/headless cameras.
    /// Participates in wait/andThen/pause/cancellation; pending cuts retain destination.
    Camera& cutTo(Camera& destination);
    /// Align Sprite centers and optionally projected bounds before a hard cut.
    /// Matching uses a shared Port/viewport. The source schedule owns both phases.
    /// settleReturnsCamera restores the incoming base/follow view; false retains framing.
    Camera& matchCutTo(Camera& destination, const CameraMatchOptions& options);
    /// Synchronize subjects, crossfade while keeping them aligned, then settle.
    /// fadeSeconds/fadeEasing configure the blend; other matching options are shared.
    Camera& matchFadeTo(Camera& destination, const CameraMatchOptions& options);
    /// Transition between two live scenes with the same Port and nonempty viewport.
    /// The source owns progress; completion hides it and shows the destination.
    /// Cancellation restores visibility. Active/queued transitions are not portable.
    Camera& transitionTo(Camera& destination, double seconds, int style = camera_Crossfade, EasingFunc easing = easeInOutQuad);
    /// Reveal by linear luminance; a null mask freezes the initial source output.
    /// Masks stretch to the viewport. Softness is in [0,1]; bright pixels reveal first.
    Camera& lumaFadeTo(Camera& destination, double seconds, Image* mask = nullptr, float softness = .1f, bool darkFirst = false, EasingFunc easing = easeInOutQuad);
    /// Slide live outputs without changing camera pose. Blur is in [0,1], zero by default.
    /// Style must be one of camera_WhipLeft/Right/Up/Down. Blur is calibrated at
    /// 0.65 seconds, scales inversely with duration, and uses at most eight samples.
    Camera& whipPanTo(Camera& destination, double seconds, int style = camera_WhipLeft, float blur = 0, EasingFunc easing = easeInOutQuad);
    Camera& stopIt();
    Camera& restartIt();
protected:
    void cancelScheduleImpl() override;
    void animationChannelAcquired(float* field) override;
    void animationValuesChanged() override;
    uint32 scriptClassTag() const override { return CLASSTAG_CAMERA; }
    std::vector<const float*> tweenFields() const override;
    void animationStarting(Animation&) override;
    void easingCompleted(const Animation&) override;
private:
    // Compare inputs rather than relying on setter notifications: animation,
    // following, snapshots and match cuts can all change pose between draws.
    struct ViewTransformInputs {
        Point anchor, location;
        Offset centerOffset, matchShift;
        std::array<PDG_BASE_COORD_TYPE, 4> viewport, bounds;
        float movementRatio, zoomRatio, facing, scaleX, scaleY, zoom;
        double matchLogZoom;
        bool flipX, flipY, pixelSnapping, hasViewBounds;
        std::array<double, 6> effect;
        bool operator==(const ViewTransformInputs&) const = default;
    };
    mutable ViewTransformInputs mViewTransformInputs{};
    mutable SpatialTransform mViewTransform;
    mutable bool mViewTransformValid = false;
    friend class Port;
    friend class SpriteLayer;
    friend class PortImpl;
    friend class SpriteManager;
#ifndef PDG_NO_GUI
    void drawEffects(Port& port) const;
    void ensureViewport(Port& port);
    SpatialTransform viewportTransform(float movementRatio = 1, float zoomRatio = 1) const;
#endif
    Port* mOwnerPort = nullptr;
    Rect mViewport;
    bool mHasViewport = false;
    Camera& zoomImpl(float value, double seconds, EasingFunc easing, bool relative);
    void notifyZoomComplete(float zoom);
    float mZoom = 1;
    bool mPixelSnapping = false;
    unsigned mAttachments = 0;
    std::weak_ptr<AnimatedBase*> mFollowTarget;
    AnimatedBase* followedTarget() const;
    bool advanceFollowing(double seconds);
    Camera* mEffects=nullptr;
    float mFlashOpacity=0;
    float mOpacity=1, mHidden=0, mTransitionProgress=-1;
    int mTransitionStyle=camera_Crossfade;
    Image* mTransitionMask=nullptr;
    float mTransitionSoftness=.1f, mTransitionBlur=0;
    double mTransitionSeconds=0;
    bool mTransitionDarkFirst=false, mTransitionIsCut=false;
    std::vector<float> mTransitionLuminance;
    long mTransitionMaskWidth=0, mTransitionMaskHeight=0;
    Camera& transitionToImpl(Camera&, double, int, EasingFunc, Image*, float, bool, float, bool cut = false);
    Camera* mTransitionDestination=nullptr;
    Camera* mTransitionSource=nullptr; // checked backlink; source retains destination
    bool mTransitionActive=false, mSourceWasHidden=false, mDestinationWasHidden=false;
    void finishTransition(bool completed);
    void startTransition();
    void validateTransitionDestination(const Camera&, bool cut = false) const;
    void validateSceneOrder(const Camera* destination = nullptr) const;
    bool canPick() const;
    bool mEffectsOwned=false;
    struct MatchState;
    std::unique_ptr<MatchState> mMatch;
    Offset mMatchShift;
    double mMatchLogZoom = 0;
    void updateMatch();
    void cutMatch();
    void alignMatchDestination();
    Camera& matchToImpl(Camera&, const CameraMatchOptions&, bool fade);
    float transitionBlendProgress() const;
    void clearMatch(bool retain);
    Point mPreviousTarget;
    bool mHasPreviousTarget = false, mHasViewBounds = false;
    double mSmoothing = 0, mLookAhead = 0;
    Rect mDeadzone, mViewBounds;
    Offset mFollowOffset;
};
}
#endif
