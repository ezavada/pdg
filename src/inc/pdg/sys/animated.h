// -----------------------------------------------
// animated.h
//
// animation functionality
//
// Written by Ed Zavada, 2004-2012
// Copyright (c) 2012, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------


#ifndef PDG_ANIMATED_H_INCLUDED
#define PDG_ANIMATED_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/platform.h"

#include "pdg/sys/global_types.h"
#include "pdg/sys/coordinates.h"
#include "pdg/sys/ianimationhelper.h"
#include "pdg/sys/easing.h"
#include "pdg/sys/serializable.h"
#include "pdg/sys/animationoperation.h"

#include <vector>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include <functional>
#include <array>
#include <string>
#include <initializer_list>

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

namespace pdg {

// Internal scheduler channel IDs. Values are snapshot IDs and must remain stable.
// Numeric channels follow tweenFields(); Camera appends its channels to the base fields.
enum AnimationChannel : unsigned {
    animationChannel_LocationX = 0,
    animationChannel_LocationY = 1,
    animationChannel_Facing = 2,
    animationChannel_Width = 3,
    animationChannel_Height = 4,
    animationChannel_ScaleX = 5,
    animationChannel_ScaleY = 6,
    animationChannel_CenterOffsetX = 7,
    animationChannel_CenterOffsetY = 8,
    animationChannel_MovementX = 9,
    animationChannel_MovementY = 10,
    animationChannel_Spinning = 11,
    animationChannel_StretchingWidth = 12,
    animationChannel_StretchingHeight = 13,
    animationChannel_CameraZoom = 14,
    animationChannel_CameraFlashOpacity = 15,
    animationChannel_CameraOpacity = 16,
    animationChannel_CameraHidden = 17,
    animationChannel_CameraTransition = 18,
    animationChannel_BaseCount = animationChannel_CameraZoom
};

// Target interpretation shared by numeric tracks and recorded script operations.
enum AnimationTargetMode : uint8 {
    animationMode_Assign = 0,
    animationMode_Add = 1,
    animationMode_Multiply = 2,
    animationMode_Toggle = 3,
};

enum AnimationFlipAxis : unsigned {
    animationFlipAxis_X = 0,
    animationFlipAxis_Y = 1
};

class AnimationScript;
class AnimationScriptState;
struct ScriptExecution;
struct AnimationEvaluationContext;
using AnimationEvaluator = std::function<bool(const AnimationEvaluationContext&)>;
struct AnimationEvent;
using AnimationEventHandler = std::function<void(const AnimationEvent&)>;


// -----------------------------------------------------------------------------------
// AnimatedBase: shared state and runtime interface
// An object that can be automatically moved, spun or resized over time
// Not intended to be used directly, but rather as a base class for items that can
// be animated. Public transform, schedule and helper mutators return *this.
// -----------------------------------------------------------------------------------

/** Shared animation state and polymorphic interface.
 * @ingroup Animation
 * Use Animated<T> for fluent methods that return the concrete owner type.
 */
class AnimatedBase : public ISerializable {
public:

	SERIALIZABLE_TAG( CLASSTAG_ANIMATED );
	SERIALIZABLE_METHODS();
	static pdg::ISerializable* CreateInstance() { return new AnimatedBase(); }

	// bounds
	virtual Rect			getBoundingBox() const;
	virtual RotatedRect		getRotatedBounds() const;

	// current location in container's coordinate system
    virtual Point			getLocation() const;
    AnimatedBase&		setLocation(const Point& loc);
    AnimatedBase&		setLocation(float x, float y);
    AnimatedBase&		moveTo(float x, float y);
    AnimatedBase&		moveTo(const Point& where);
    AnimatedBase&		moveBy(float deltaX, float deltaY); // relative to current location
    AnimatedBase&		moveBy(const Offset& delta); // relative to current location

    // animate moving to new location, scheduled via andThen() and wait()
	AnimatedBase& moveTo(const Point& loc, double durationSeconds, EasingFunc easing = easeInOutQuad) { moveToImpl(loc, durationSeconds, easing); return *this; }
	AnimatedBase&			moveTo(float x, float y, double durationSeconds,
                         EasingFunc easing = easeInOutQuad);
	AnimatedBase&			moveBy(float deltaX, float deltaY, double durationSeconds,
                            EasingFunc easing = easeInOutQuad);
	AnimatedBase&			moveBy(const Offset& delta, double durationSeconds,
                         EasingFunc easing = easeInOutQuad);

    // constant movement, in distance units per second
    Offset    getMovement() const;
    AnimatedBase& setMovement(const Vector& movement);
    AnimatedBase& setMovement(float xPerSecond, float yPerSecond);
    AnimatedBase& stopMovement();

    // animate change in movement over time, scheduled via andThen() and wait()
    AnimatedBase& changeMovementTo(const Vector& movement, double durationSeconds,
                          EasingFunc easing = linearTween);
    AnimatedBase& changeMovementTo(float xPerSecond, float yPerSecond, double durationSeconds,
                          EasingFunc easing = linearTween);
    AnimatedBase& changeMovementBy(const Vector& deltaMovement, double durationSeconds,
                          EasingFunc easing = linearTween);
    AnimatedBase& changeMovementBy(float deltaXPerSecond, float deltaYPerSecond, double durationSeconds,
                          EasingFunc easing = linearTween);

	// size
    virtual Offset    getSize() const;
	virtual float	  getWidth() const;
	virtual float	  getHeight() const;
	AnimatedBase& setSize(float width, float height);
    AnimatedBase& setSize(const Offset& size);
	AnimatedBase& setWidth(float width);
	AnimatedBase& setHeight(float height);
    AnimatedBase& resizeBy(float deltaWidth, float deltaHeight); // change current size by fixed amount

	AnimatedBase& grow(float factor); // from current size
	AnimatedBase& stretch(float widthFactor, float heightFactor); // from current size

	// animate change to specific size over time, scheduled via andThen() and wait()
	AnimatedBase& resizeTo(float width, float height, double durationSeconds, EasingFunc easing = easeInOutQuad) { resizeToImpl(width, height, durationSeconds, easing); return *this; }

	// animate change in size over time, relative to current size, scheduled via andThen() and wait()
	AnimatedBase& resizeBy(float deltaWidth, float deltaHeight, double durationSeconds,
                            EasingFunc easing = easeInOutQuad); // change current size by fixed amount
	AnimatedBase& grow(float factor, double durationSeconds,
                            EasingFunc easing = easeInOutQuad); // from current size
	AnimatedBase& stretch(float widthFactor, float heightFactor, double durationSeconds,
                            EasingFunc easing = easeInOutQuad); // from current size

    // Constant changes in logical size, in distance units per second.
    Offset getStretching() const;
    AnimatedBase& setGrowing(float amountPerSecond);
    AnimatedBase& setStretching(float widthPerSecond, float heightPerSecond);
    AnimatedBase& stopGrowing();
    AnimatedBase& stopStretching();

    // Transition growth rates over explicit seconds; the final rate continues.
    AnimatedBase& changeGrowingTo(float amountPerSecond, double durationSeconds, EasingFunc easing = linearTween);
    AnimatedBase& changeGrowingBy(float deltaPerSecond, double durationSeconds, EasingFunc easing = linearTween);
    AnimatedBase& changeStretchingTo(float widthPerSecond, float heightPerSecond, double durationSeconds, EasingFunc easing = linearTween);
    AnimatedBase& changeStretchingBy(float deltaWidthPerSecond, float deltaHeightPerSecond, double durationSeconds, EasingFunc easing = linearTween);

    // dimensionless transform scale, independent of logical width/height.
    virtual Offset    getScale() const { validateScriptRead(); return Offset(mScaleX, mScaleY); }
    AnimatedBase& setScale(float x, float y);
    AnimatedBase& setScale(float scale) { return setScale(scale, scale); }

    // animate changing scale over time, scheduled via andThen() and wait()
    AnimatedBase& changeScaleTo(float x, float y, double durationSeconds, EasingFunc easing = easeInOutQuad);
    AnimatedBase& changeScaleBy(float deltaX, float deltaY, double durationSeconds, // added to current scale
                            EasingFunc easing = easeInOutQuad);

    // These control scheduled animations only. Constant rates, helpers and physics continue.
    bool isSchedulePaused() const { validateScriptRead(); return mSchedulePaused; }
    bool hasScheduledAnimations() const { validateScriptRead(); return !mAnimations.empty() || hasScriptAnimations(); }
    AnimatedBase& pauseSchedule() { validateScriptControl(); mSchedulePaused = true; return *this; }
    AnimatedBase& resumeSchedule() { validateScriptControl(); mSchedulePaused = false; return *this; }
    AnimatedBase& cancelSchedule() { cancelScheduleImpl(); return *this; }

	// rotation clockwise is positive, counter-clockwise negative, around centerpoint, in radians
	virtual float			getRotation() const;
	virtual Offset          getCenterOffset() const; // relative to real bounds-based center
	AnimatedBase&		setRotation(float radiansRotation);
	AnimatedBase&		setCenterOffset(const Offset& offset); // relative to real bounds-based center
	AnimatedBase&		rotateTo(float radiansRotation);
	AnimatedBase&		rotateBy(float radians);

	// animate changing direction over time, scheduled via andThen() and wait()
	AnimatedBase& rotateTo(float radiansRotation, double durationSeconds, EasingFunc easing = easeInOutQuad, int direction = rotationDirection_AsSpecified) { rotateToImpl(radiansRotation, durationSeconds, easing, direction); return *this; }
	AnimatedBase&			rotateBy(float radians, double durationSeconds,
                                EasingFunc easing = easeInOutQuad,
                                int direction = rotationDirection_AsSpecified);
	AnimatedBase&			changeCenterOffsetTo(float xCenterOffset, float yCenterOffset, double durationSeconds,
                                EasingFunc easing = easeInOutQuad);
	AnimatedBase&			changeCenterOffsetTo(const Offset& centerOffset, double durationSeconds,
                                   EasingFunc easing = easeInOutQuad);
	AnimatedBase&			changeCenterOffsetBy(float deltaXOffset, float deltaYOffset, double durationSeconds,
                                EasingFunc easing = easeInOutQuad);
	AnimatedBase&			changeCenterOffsetBy(const Offset& deltaCenterOffset, double durationSeconds,
                                 EasingFunc easing = easeInOutQuad);

	// constant change in direction
	float			getSpin() const;
	AnimatedBase&		setSpin(float radiansPerSecond);
	AnimatedBase&		stopSpinning();

    // animate changing spin over time, scheduled via andThen() and wait()
    AnimatedBase&		changeSpinTo(float radiansPerSecond, double durationSeconds,
                          EasingFunc easing = linearTween);
    AnimatedBase&		changeSpinBy(float deltaRadiansPerSecond, double durationSeconds,
                          EasingFunc easing = linearTween);
    // flipping
	bool			isFlippedX() const;
	bool			isFlippedY() const;
	AnimatedBase&		setFlipX(bool flip);
	AnimatedBase&		setFlipY(bool flip);
	AnimatedBase&		flipX();
	AnimatedBase&		flipY();

    // scheduling of timed operations. Not allowed for constant motion operations
    // delay before starting next scheduled operation
    AnimatedBase&       wait(double durationSeconds);
    // Sequence the next timed operation after the most recently scheduled one.
    AnimatedBase&       andThen();

    /** Record a reusable native animation definition. The library owns the builder. */
    static AnimationScript& defineScript(const std::string& name);
    /** Remove a definition and release its resources. Running copies continue. */
    static bool deleteScript(const std::string& name);
    /// @cond INTERNAL
    static void clearScriptLibrary();
    static bool hasScriptDefinition(const std::string& name);
    /// @endcond
    AnimatedBase& playScript(const std::string& name);
    AnimatedBase& batch();
    AnimatedBase& endBatch();
    AnimatedBase& series();
    AnimatedBase& endSeries();
    AnimatedBase& andAlso();
    AnimatedBase& stagger(double intervalSeconds);
    AnimatedBase& mark(const std::string& name, bool saveState = true);
    AnimatedBase& jumpToMark(const std::string& name, bool restoreState = true);
    AnimatedBase& on(const std::string& event, AnimationEventHandler handler);
    AnimatedBase& triggerEvent(const std::string& name);
    /// Capture a chainable mutation when constructing a script; live calls return false.
    bool recordOperation(const std::string& name, AnimationArguments arguments);
    bool isRecordingOperation() const;
    AnimatedBase& onStarted(AnimationEventHandler handler) { return on("started", std::move(handler)); }
    AnimatedBase& onFinished(AnimationEventHandler handler) { return on("finished", std::move(handler)); }
    AnimatedBase& onScriptFinished(AnimationEventHandler handler) { return on("scriptFinished", std::move(handler)); }
    AnimatedBase& onMark(AnimationEventHandler handler) { return on("mark", std::move(handler)); }
    AnimatedBase& onYoyo(AnimationEventHandler handler) { return on("yoyo", std::move(handler)); }
    AnimatedBase& onRepeat(AnimationEventHandler handler) { return on("repeat", std::move(handler)); }
    AnimatedBase& onUntilFired(AnimationEventHandler handler) { return on("untilFired", std::move(handler)); }
    AnimatedBase& when(AnimationEvaluator evaluator);
    AnimatedBase& otherwise();
    AnimatedBase& endWhen();
    AnimatedBase& endOtherwise();
    AnimatedBase& until(AnimationEvaluator evaluator);
    AnimatedBase& yoyo();
    AnimatedBase& repeat(int additionalExecutions = -1);
    AnimatedBase& diminish(float factor, double seconds, EasingFunc easing = linearTween);
    AnimatedBase& increase(float factor, double seconds, EasingFunc easing = linearTween);
    AnimatedBase& slowDown(float factor, double seconds, EasingFunc easing = linearTween);
    AnimatedBase& speedUp(float factor, double seconds, EasingFunc easing = linearTween);
    // "It" is the most recently selected operation, group, or named script.
    // These control that element only; schedule-wide controls are separate.
    AnimatedBase& stopIt();
    AnimatedBase& restartIt();
    AnimatedBase& pauseIt();
    AnimatedBase& resumeIt();

	// objects that will be called to help with animation of this object
	// the animation helper(s) will be called in order they were added
	// after all other animation (from constant motion, change over time with easing,
	// and programmed rates) has been calculated
	AnimatedBase& addAnimationHelper(IAnimationHelper* helper) { addAnimationHelperImpl(helper); return *this; }
	AnimatedBase& removeAnimationHelper(IAnimationHelper* helper) { removeAnimationHelperImpl(helper); return *this; }
	AnimatedBase& clearAnimationHelpers() { clearAnimationHelpersImpl(); return *this; }

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	SCRIPT_OBJECT_REF mAnimatedScriptObj;
#endif

#ifndef PDG_INTERNAL_LIB
protected:
#endif
/// @cond INTERNAL
	AnimatedBase();
	virtual ~AnimatedBase();
    /// @cond INTERNAL
    friend AnimationObjectArgument captureAnimationObject(RefCountedObj*);
    std::weak_ptr<AnimatedBase*> animationLifetime() const;
    virtual std::vector<AnimatedBase*> animationTargets() const { return {}; }
    virtual bool isTroupe() const { return false; }
    /// @cond INTERNAL
    virtual ISerializable* snapshotAnimationOwner() const { return nullptr; }
    virtual uint32 snapshotAnimationId() const { return 0; }
    virtual AnimatedBase* snapshotAnimationMember(uint32) { return nullptr; }
    /// @endcond
    /// @endcond


    // Virtual behavior is separate from the typed fluent interface.
    virtual void moveToImpl(const Point& loc, double durationSeconds, EasingFunc easing);
    void moveByImpl(const Offset& delta, double durationSeconds, EasingFunc easing);
    virtual void resizeToImpl(float width, float height, double durationSeconds, EasingFunc easing);
    virtual void cancelScheduleImpl();
    virtual void rotateToImpl(float radiansRotation, double durationSeconds, EasingFunc easing, int direction);
    virtual void addAnimationHelperImpl(IAnimationHelper* helper);
    virtual void removeAnimationHelperImpl(IAnimationHelper* helper);
    virtual void clearAnimationHelpersImpl();

	// called by subclasses to do the actual work of animating
	// returns true if anything changed
	virtual bool	animate(double deltaSeconds);

	// ---------------------------------------
	// subclasses should override these when something needs to
	// be done to maintain the state of the object based on a
	// direct change to one of the basic attributes
    // Cancel only spatial motion, without consuming a pending animation wait.
    void cancelProgrammedMotion();
	// mAnimating will be true when following called from animate()
	// or false if called from setX() calls

	bool mAnimating;

	virtual void validateProgrammedTransform() const {}
    virtual void validateTransformEdit() const {}
    virtual void animationValuesChanged() {}

	virtual void locationChanged(const Offset& delta);
	virtual void sizeChanged(float deltaW, float deltaH);
    virtual void scaleChanged(const Offset& delta);
	virtual void rotationChanged(float deltaRadians);
	virtual void centerChanged(const Offset& delta);
	virtual void flipChanged(bool xFlipped, bool yFlipped);

	// ---------------------------------------
	// basic attributes

	Point           mLocation;
	float			mHeight;
	float			mWidth;
	float			mFacing;
    float           mScaleX, mScaleY;
	Offset          mCenterOffset;
	bool			mFlipX;
	bool			mFlipY;

	// ---------------------------------------
	// programmed transform rates (no physical integration)

	float			mDeltaXPerMs;
	float			mDeltaYPerMs;
	float			mDeltaWidthPerMs;
	float			mDeltaHeightPerMs;
	float			mDeltaFacingPerMs;

	// ---------------------------------------
	// change over duration via easing
	// independent of physical simulation

	struct Animation {
		EasingFunc	easing;
        double      delaySeconds;
        float       targetVal;  // only used with delay
		float*		value;
		double      elapsedSeconds;
		double      durationSeconds;
		float		beginVal;
		float		deltaVal;
        int         rotationDirection = rotationDirection_AsSpecified;
        bool        relativeRotation = false;
        bool        resolveRotation = false;
        bool        spawnRelative = false; // preserve moveBy semantics when emitting a template
        bool        chained = false; // defer channel ownership until this operation starts
        uint8       targetMode = animationMode_Assign; // Stored as a byte for snapshots.
        uint64      operation = 0;
        uint8       completion = 0; // owner-specific completion kind, two wire bits
        Animation(float* valPtr, float val, EasingFunc func, double delay, double duration)
            : easing(func),
            delaySeconds(delay),
            targetVal(val),
            value(valPtr),
            elapsedSeconds(0),
            durationSeconds(duration),
            beginVal(*valPtr),
            deltaVal(val - *valPtr)
            {
                if (!std::isfinite(val) || !std::isfinite(delay) || delay < 0 ||
                    !std::isfinite(duration) || duration < 0 || !func)
                    throw std::invalid_argument("Animation values and seconds must be finite; durations must be nonnegative");
            };
        Animation()
            : easing(0),
            delaySeconds(0),
            targetVal(0),
            value(0),
            elapsedSeconds(0),
            durationSeconds(0),
            beginVal(0),
            deltaVal(0)
            {};
	};

    friend class Troupe;
    friend class AnimationScriptState;
    friend struct ScriptExecution;
    friend class AnimationScript;
    struct ScriptValue { unsigned field; float target; };
    bool recordScriptAnimation(std::initializer_list<ScriptValue> values, double seconds,
        EasingFunc easing, uint8 mode = animationMode_Assign, int direction = rotationDirection_AsSpecified, uint8 completion = 0, uint32 requiredClass = 0);
    bool recordScriptFlip(unsigned axis, bool value, bool toggle = false);
    bool scriptWait(double seconds);
    bool scriptAndThen();
    bool advanceScripts(double seconds, bool beginUpdate = false);
    void cancelScriptChannel(float* value);
    virtual void animationChannelAcquired(float*) {}
    // Owners with sampled sources can choose absolute or relative channels.
    virtual bool prepareSampledAnimation(unsigned, uint8, float) { return false; }
    virtual void validateSampledRequest(std::initializer_list<ScriptValue>,double,EasingFunc,uint8) const {}
    virtual bool diminishSampled(float,double,EasingFunc) { return false; }
    unsigned mSampledPreparationDepth = 0;
    struct SampledPreparationGuard {
        AnimatedBase& owner;
        explicit SampledPreparationGuard(AnimatedBase& value):owner(value){++owner.mSampledPreparationDepth;}
        ~SampledPreparationGuard(){--owner.mSampledPreparationDepth;}
    };
    bool animationChannelScheduled(const float*) const;
    bool animationChannelSelected(const float*) const;
    void stopAnimationChannel(const float*);
    virtual uint32 scriptClassTag() const { return CLASSTAG_ANIMATED; }
    mutable std::shared_ptr<AnimatedBase*> mLifetime;
    std::array<float,5> mScriptFrameRates{};
    ScriptExecution* mScriptAcquiring = nullptr;
    bool hasScriptAnimations() const;
    double scriptNextBoundary() const;
    void validateScriptEdit() const;
    void copyScriptStateFrom(const AnimatedBase& source);
    void rebaseScriptState(const Offset& translation, float rotation);
    uint32 scriptSerializedSize(ISerializer*) const;
    void serializeScripts(ISerializer*) const;
    void deserializeScripts(IDeserializer*);
    void cancelScripts();
    void selectScriptOperand();
    void selectNativeAnimation();
    double scriptDependencyStart(uint32 id) const;
    double scriptOwnerTime() const;
    void enqueueScriptCompletion(unsigned field, float value, EasingFunc easing, double seconds, uint8 completion);
    void validateScriptControl() const;
    virtual void validateScriptRead() const;
    void validateUnrecordedOperation(const char* name) const;
    std::shared_ptr<AnimationScriptState> mScripts;
    std::vector<std::weak_ptr<ScriptExecution*>> mExternalScriptExecutions;
    std::array<double,5> mTroupeRateTime{};
    std::vector<std::shared_ptr<AnimatedBase>> mSnapshotScriptObjects;

    double mDelaySeconds;
    bool   mSchedulePaused;
    bool   mAppendAnimation = false;
    bool   mWaitPending = false;
    uint64 mAnimationOperation = 0;

    std::vector<Animation> mAnimations;
    virtual std::vector<const float*> tweenFields() const;
    // Copy values and remaining scheduled work, rebinding channels to this owner.
    // Event handlers and animation helpers are deliberately not copied.
    void copyAnimationStateFrom(const AnimatedBase& source);
    uint32 tweenSerializedSize(ISerializer*) const;
    void serializeTweens(ISerializer*) const;
    void deserializeTweens(IDeserializer*);
    virtual void cancelAnimation(float* value);
    void scheduleAnimation(float* value, float target, double seconds, EasingFunc easing);
    void beginAnimationRequest() { ++mAnimationOperation; selectNativeAnimation(); }
    void finishAnimationRequest() { mDelaySeconds = 0; mAppendAnimation = false; mWaitPending = false; }
    void prepareAnimation(float* value) { if (!mAppendAnimation) cancelAnimation(value); }
    void setRelativeAnimationTargets(uint8 mode);
    float* competingAnimationChannel(float* value);
    virtual bool animationChannelsConflict(float* a, float* b) const { return a == b; }
    virtual void animationStarting(Animation&) {}
    uint8 animationFlags(const Animation& a) const;
    void readAnimationFlags(Animation& a, uint8 flags, bool sequencing);
    void validateImmediateOperation() const;
    void validateAnimationDuration(double seconds) const;
    static void validateDuration(double seconds);
    static double rotationTarget(double begin, double target, int direction, bool relative);
    static double integrateAnimation(const Animation& animation, double endSeconds);

    // subclasses override to do post-easing operations
    virtual void    easingCompleted(const Animation& a);

	// ---------------------------------------
	// helpers

	struct HelperRegistration {
        IAnimationHelper* helper;
        bool active = true;
        bool running = false;
        bool owned;
        explicit HelperRegistration(IAnimationHelper* value)
            : helper(value), owned(value->ownedByAnimated()) {
            if (owned) helper->retainForAnimation();
        }
        ~HelperRegistration() { if (owned) helper->releaseForAnimation(); }
        HelperRegistration(const HelperRegistration&) = delete;
        HelperRegistration& operator=(const HelperRegistration&) = delete;
    };
    std::vector<std::shared_ptr<HelperRegistration>> mHelpers;
/// @endcond
};

// bounds
inline Rect
AnimatedBase::getBoundingBox() const { validateScriptRead();
	return getRotatedBounds().getBounds();
}

inline RotatedRect
AnimatedBase::getRotatedBounds() const { validateScriptRead();
	Rect r(std::abs(mWidth * mScaleX), std::abs(mHeight * mScaleY));
	r.center(mLocation);
	RotatedRect rr(r, mFacing, mCenterOffset);
	return rr;
}


// current location in container's coordinate system
inline AnimatedBase&
AnimatedBase::setLocation(const Point& loc) {
    if (recordScriptAnimation({{animationChannel_LocationX,loc.x},{animationChannel_LocationY,loc.y}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
	cancelAnimation(&mLocation.x); cancelAnimation(&mLocation.y);
    Point delta = loc - mLocation;
	mLocation.x = loc.x;
	mLocation.y = loc.y;
	locationChanged(Offset(delta.x, delta.y));
	return *this;
}

inline Point
AnimatedBase::getLocation() const { validateScriptRead();
	return mLocation;
}

inline AnimatedBase&
AnimatedBase::moveTo(float x, float y) {
    moveTo(Point(x,y));
    return *this;
}

inline AnimatedBase&
AnimatedBase::moveTo(const Point& where) {
    setLocation(where);
    return *this;
}

inline AnimatedBase&
AnimatedBase::moveBy(float deltaX, float deltaY) {
    moveBy(Offset(deltaX, deltaY));
    return *this;
}

inline AnimatedBase&
AnimatedBase::moveBy(const Offset& delta) {
    if (recordScriptAnimation({{animationChannel_LocationX,delta.x},{animationChannel_LocationY,delta.y}}, 0, linearTween, animationMode_Add)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
    if (delta.x != 0) cancelAnimation(&mLocation.x);
    if (delta.y != 0) cancelAnimation(&mLocation.y);
    mLocation += delta;
    locationChanged(delta);
    return *this;
}


inline AnimatedBase&
AnimatedBase::moveTo(float x, float y, double durationSeconds, EasingFunc easing) {
    moveTo(Point(x, y), durationSeconds, easing);
    return *this;
}

inline AnimatedBase&
AnimatedBase::moveBy(float deltaX, float deltaY, double durationSeconds, EasingFunc easing) {
	moveBy(Offset(deltaX, deltaY), durationSeconds, easing);
    return *this;
}

inline AnimatedBase&
AnimatedBase::moveBy(const Offset& delta, double durationSeconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_LocationX,delta.x},{animationChannel_LocationY,delta.y}}, durationSeconds, easing, animationMode_Add)) return *this;
    const bool relative = mAppendAnimation;
    moveByImpl(delta, durationSeconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Add);
    else for (auto& a : mAnimations) if (a.operation == mAnimationOperation) a.spawnRelative = true;
    return *this;
}

inline AnimatedBase& AnimatedBase::stopMovement() {
    if (recordScriptAnimation({{animationChannel_MovementX,0},{animationChannel_MovementY,0}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    cancelAnimation(&mLocation.x); cancelAnimation(&mLocation.y);
    return setMovement(0, 0);
}

// change in size
inline AnimatedBase&
AnimatedBase::setSize(float width, float height) {
    if (recordScriptAnimation({{animationChannel_Width,width},{animationChannel_Height,height}}, 0, linearTween)) return *this;
	setWidth(width);
	setHeight(height);
	return *this;
}


inline AnimatedBase&
AnimatedBase::setHeight(float height) {
    if (recordScriptAnimation({{animationChannel_Height,height}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
	cancelAnimation(&mHeight);
    float deltaH = height - mHeight;
	mHeight = height;
	sizeChanged(0.0f, deltaH);
	return *this;
}


inline AnimatedBase&
AnimatedBase::setWidth(float width) {
    if (recordScriptAnimation({{animationChannel_Width,width}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
	cancelAnimation(&mWidth);
    float deltaW = width - mWidth;
	mWidth = width;
	sizeChanged(deltaW, 0.0f);
	return *this;
}

inline float
AnimatedBase::getHeight() const { validateScriptRead();
	return mHeight;
}

inline float
AnimatedBase::getWidth() const { validateScriptRead();
	return mWidth;
}

inline AnimatedBase&
AnimatedBase::grow(float factor) {
	stretch(factor, factor);
	return *this;
}


inline AnimatedBase&
AnimatedBase::stretch(float widthFactor, float heightFactor) {
    if (recordScriptAnimation({{animationChannel_Width,widthFactor},{animationChannel_Height,heightFactor}}, 0, linearTween, animationMode_Multiply)) return *this;
	return setSize(mWidth * widthFactor, mHeight * heightFactor);
}


// constant change in size
inline AnimatedBase&
AnimatedBase::setGrowing(float amountPerSecond) {
	setStretching(amountPerSecond, amountPerSecond);
	return *this;
}


inline AnimatedBase&
AnimatedBase::stopGrowing() {
	stopStretching();
	return *this;
}


inline AnimatedBase&
AnimatedBase::stopStretching() {
    if (recordScriptAnimation({{animationChannel_StretchingWidth,0},{animationChannel_StretchingHeight,0}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    cancelAnimation(&mWidth); cancelAnimation(&mHeight);
    cancelAnimation(&mDeltaWidthPerMs); cancelAnimation(&mDeltaHeightPerMs);
	mDeltaWidthPerMs = 0.0f;
	mDeltaHeightPerMs = 0.0f;
	return *this;
}


// animate change in size over time, relative to current size
inline AnimatedBase&
AnimatedBase::resizeBy(float deltaWidth, float deltaHeight, double durationSeconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_Width,deltaWidth},{animationChannel_Height,deltaHeight}}, durationSeconds, easing, animationMode_Add)) return *this;
    SampledPreparationGuard sampled(*this);
    const bool relative = mAppendAnimation;
    resizeTo(relative ? deltaWidth : mWidth + deltaWidth, relative ? deltaHeight : mHeight + deltaHeight, durationSeconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Add);
    return *this;
}


inline AnimatedBase&
AnimatedBase::grow(float factor, double durationSeconds, EasingFunc easing) {
	stretch(factor, factor, durationSeconds, easing);
    return *this;
}

 // from current size
inline AnimatedBase&
AnimatedBase::stretch(float widthFactor, float heightFactor, double durationSeconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_Width,widthFactor},{animationChannel_Height,heightFactor}}, durationSeconds, easing, animationMode_Multiply)) return *this;
    SampledPreparationGuard sampled(*this);
    const bool relative = mAppendAnimation;
    resizeTo(relative ? widthFactor : mWidth * widthFactor, relative ? heightFactor : mHeight * heightFactor, durationSeconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Multiply);
    return *this;
}

// rotation clockwise is postive, counter-clockwise negative, around centerpoint, in radians
inline AnimatedBase&
AnimatedBase::rotateBy(float radians) {
    if (recordScriptAnimation({{animationChannel_Facing,radians}}, 0, linearTween, animationMode_Add)) return *this;
	setRotation(mFacing + radians);
	return *this;
}

inline AnimatedBase&
AnimatedBase::rotateTo(float radiansRotation) {
	setRotation(radiansRotation);
	return *this;
}

inline float
AnimatedBase::getRotation() const { validateScriptRead();
	return mFacing;
}

inline AnimatedBase&
AnimatedBase::flipX() {
    if (recordScriptFlip(animationFlipAxis_X,false,true)) return *this;
	return setFlipX(!mFlipX);
}

inline AnimatedBase&
AnimatedBase::flipY() {
    if (recordScriptFlip(animationFlipAxis_Y,false,true)) return *this;
	return setFlipY(!mFlipY);
}

inline bool
AnimatedBase::isFlippedX() const { validateScriptRead();
	return mFlipX;
}

inline bool
AnimatedBase::isFlippedY() const { validateScriptRead();
	return mFlipY;
}


inline AnimatedBase&
AnimatedBase::setCenterOffset(const Offset& offset) {
    if (recordScriptAnimation({{animationChannel_CenterOffsetX,offset.x},{animationChannel_CenterOffsetY,offset.y}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
    cancelAnimation(&mCenterOffset.x); cancelAnimation(&mCenterOffset.y);
    Offset saved = mCenterOffset;
    mCenterOffset = offset;
    centerChanged(mCenterOffset - saved);
    return *this;
}


inline Offset
AnimatedBase::getCenterOffset() const { validateScriptRead();
	return mCenterOffset;
}

inline AnimatedBase&
AnimatedBase::stopSpinning() {
    if (recordScriptAnimation({{animationChannel_Spinning,0}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    cancelAnimation(&mFacing); cancelAnimation(&mDeltaFacingPerMs);
	mDeltaFacingPerMs = 0.0f;
	return *this;
}

// relative to real center
inline AnimatedBase&
AnimatedBase::changeCenterOffsetTo(float xOffset, float yOffset, double durationSeconds, EasingFunc easing) {
	changeCenterOffsetTo(Offset(xOffset, yOffset), durationSeconds, easing);
    return *this;
}

inline AnimatedBase&
AnimatedBase::changeCenterOffsetBy(float deltaXOffset, float deltaYOffset, double durationSeconds, EasingFunc easing) {
    changeCenterOffsetBy(Offset(deltaXOffset, deltaYOffset), durationSeconds, easing);
    return *this;
}

inline AnimatedBase&
AnimatedBase::changeCenterOffsetBy(const Offset& offset, double durationSeconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_CenterOffsetX,offset.x},{animationChannel_CenterOffsetY,offset.y}}, durationSeconds, easing, animationMode_Add)) return *this;
    SampledPreparationGuard sampled(*this);
    const bool relative = mAppendAnimation;
    changeCenterOffsetTo(relative ? offset : mCenterOffset + offset, durationSeconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Add);
    return *this;
}

inline AnimatedBase&
AnimatedBase::wait(double durationSeconds) {
    if (scriptWait(durationSeconds)) return *this;
    if (!std::isfinite(durationSeconds) || durationSeconds < 0)
        throw std::invalid_argument("wait requires finite nonnegative seconds");
    mDelaySeconds = durationSeconds;
    mAppendAnimation = false; // an explicit wait replaces pending sequencing
    mWaitPending = true;
    return *this;
}


inline AnimatedBase& AnimatedBase::setLocation(float x, float y) { return setLocation(Point(x, y)); }
inline Offset AnimatedBase::getSize() const { validateScriptRead(); return Offset(mWidth, mHeight); }
inline AnimatedBase& AnimatedBase::setSize(const Offset& size) { return setSize(size.x, size.y); }
inline AnimatedBase& AnimatedBase::resizeBy(float width, float height) {
    if (recordScriptAnimation({{animationChannel_Width,width},{animationChannel_Height,height}}, 0, linearTween, animationMode_Add)) return *this;
    SampledPreparationGuard sampled(*this);
    return setSize(mWidth + width, mHeight + height);
}
inline AnimatedBase& AnimatedBase::changeGrowingTo(float rate, double seconds, EasingFunc easing) {
    return changeStretchingTo(rate, rate, seconds, easing);
}
inline AnimatedBase& AnimatedBase::changeGrowingBy(float delta, double seconds, EasingFunc easing) {
    return changeStretchingBy(delta, delta, seconds, easing);
}


/** Typed animation interface with one shared AnimatedBase state.
 * @ingroup Animation
 * Derive an owner from Animated<Owner>. Animated<> is the standalone form.
 * Base selects the shared implementation for extensions such as AnimatedAttributes.
 * Methods return the chosen owner type; further subclasses retain that type.
 */
template<class T = void, class Base = AnimatedBase>
class Animated : public Base {
public:
    using Self = std::conditional_t<std::is_void_v<T>, Animated, T>;
    Animated() requires std::is_void_v<T> = default;
protected:
    Animated() requires (!std::is_void_v<T>) = default;
public:
    ~Animated() override = default;
    Self& playScript(const std::string& name) { Base::playScript(name); return static_cast<Self&>(*this); }
    Self& batch() { Base::batch(); return static_cast<Self&>(*this); }
    Self& endBatch() { Base::endBatch(); return static_cast<Self&>(*this); }
    Self& series() { Base::series(); return static_cast<Self&>(*this); }
    Self& endSeries() { Base::endSeries(); return static_cast<Self&>(*this); }
    Self& andAlso() { Base::andAlso(); return static_cast<Self&>(*this); }
    Self& stagger(double intervalSeconds) { Base::stagger(intervalSeconds); return static_cast<Self&>(*this); }
    Self& mark(const std::string& name, bool saveState = true) { Base::mark(name, saveState); return static_cast<Self&>(*this); }
    Self& jumpToMark(const std::string& name, bool restoreState = true) { Base::jumpToMark(name, restoreState); return static_cast<Self&>(*this); }
    Self& on(const std::string& event, AnimationEventHandler handler) { Base::on(event, std::move(handler)); return static_cast<Self&>(*this); }
    Self& triggerEvent(const std::string& name) { Base::triggerEvent(name); return static_cast<Self&>(*this); }
    Self& onStarted(AnimationEventHandler handler) { Base::onStarted(std::move(handler)); return static_cast<Self&>(*this); }
    Self& onFinished(AnimationEventHandler handler) { Base::onFinished(std::move(handler)); return static_cast<Self&>(*this); }
    Self& onScriptFinished(AnimationEventHandler handler) { Base::onScriptFinished(std::move(handler)); return static_cast<Self&>(*this); }
    Self& onMark(AnimationEventHandler handler) { Base::onMark(std::move(handler)); return static_cast<Self&>(*this); }
    Self& onYoyo(AnimationEventHandler handler) { Base::onYoyo(std::move(handler)); return static_cast<Self&>(*this); }
    Self& onRepeat(AnimationEventHandler handler) { Base::onRepeat(std::move(handler)); return static_cast<Self&>(*this); }
    Self& onUntilFired(AnimationEventHandler handler) { Base::onUntilFired(std::move(handler)); return static_cast<Self&>(*this); }
    Self& when(AnimationEvaluator evaluator) { Base::when(std::move(evaluator)); return static_cast<Self&>(*this); }
    Self& otherwise() { Base::otherwise(); return static_cast<Self&>(*this); }
    Self& endWhen() { Base::endWhen(); return static_cast<Self&>(*this); }
    Self& endOtherwise() { Base::endOtherwise(); return static_cast<Self&>(*this); }
    Self& until(AnimationEvaluator evaluator) { Base::until(std::move(evaluator)); return static_cast<Self&>(*this); }
    Self& yoyo() { Base::yoyo(); return static_cast<Self&>(*this); }
    Self& repeat(int additionalExecutions = -1) { Base::repeat(additionalExecutions); return static_cast<Self&>(*this); }
    Self& diminish(float factor, double seconds, EasingFunc easing = linearTween) { Base::diminish(factor, seconds, easing); return static_cast<Self&>(*this); }
    Self& increase(float factor, double seconds, EasingFunc easing = linearTween) { Base::increase(factor, seconds, easing); return static_cast<Self&>(*this); }
    Self& slowDown(float factor, double seconds, EasingFunc easing = linearTween) { Base::slowDown(factor, seconds, easing); return static_cast<Self&>(*this); }
    Self& speedUp(float factor, double seconds, EasingFunc easing = linearTween) { Base::speedUp(factor, seconds, easing); return static_cast<Self&>(*this); }
    Self& stopIt() { Base::stopIt(); return static_cast<Self&>(*this); }
    Self& restartIt() { Base::restartIt(); return static_cast<Self&>(*this); }
    Self& pauseIt() { Base::pauseIt(); return static_cast<Self&>(*this); }
    Self& resumeIt() { Base::resumeIt(); return static_cast<Self&>(*this); }
    /// @copydoc AnimatedBase::setLocation(const Point&)
    Self& setLocation(const Point& loc) {
        Base::setLocation(loc);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setLocation(float, float)
    Self& setLocation(float x, float y) {
        Base::setLocation(x, y);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveTo(float, float)
    Self& moveTo(float x, float y) {
        Base::moveTo(x, y);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveTo(const Point&)
    Self& moveTo(const Point& where) {
        Base::moveTo(where);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveBy(float, float)
    Self& moveBy(float deltaX, float deltaY) {
        Base::moveBy(deltaX, deltaY);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveBy(const Offset&)
    Self& moveBy(const Offset& delta) {
        Base::moveBy(delta);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveTo(const Point&, double, EasingFunc)
    Self& moveTo(const Point& loc, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::moveTo(loc, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveTo(float, float, double, EasingFunc)
    Self& moveTo(float x, float y, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::moveTo(x, y, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveBy(float, float, double, EasingFunc)
    Self& moveBy(float deltaX, float deltaY, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::moveBy(deltaX, deltaY, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::moveBy(const Offset&, double, EasingFunc)
    Self& moveBy(const Offset& delta, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::moveBy(delta, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setMovement(const Vector&)
    Self& setMovement(const Vector& movement) {
        Base::setMovement(movement);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setMovement(float, float)
    Self& setMovement(float xPerSecond, float yPerSecond) {
        Base::setMovement(xPerSecond, yPerSecond);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::stopMovement()
    Self& stopMovement() {
        Base::stopMovement();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeMovementTo(const Vector&, double, EasingFunc)
    Self& changeMovementTo(const Vector& movement, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeMovementTo(movement, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeMovementTo(float, float, double, EasingFunc)
    Self& changeMovementTo(float xPerSecond, float yPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeMovementTo(xPerSecond, yPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeMovementBy(const Vector&, double, EasingFunc)
    Self& changeMovementBy(const Vector& deltaMovement, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeMovementBy(deltaMovement, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeMovementBy(float, float, double, EasingFunc)
    Self& changeMovementBy(float deltaXPerSecond, float deltaYPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeMovementBy(deltaXPerSecond, deltaYPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setSize(float, float)
    Self& setSize(float width, float height) {
        Base::setSize(width, height);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setSize(const Offset&)
    Self& setSize(const Offset& size) {
        Base::setSize(size);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setWidth(float)
    Self& setWidth(float width) {
        Base::setWidth(width);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setHeight(float)
    Self& setHeight(float height) {
        Base::setHeight(height);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::resizeBy(float, float)
    Self& resizeBy(float deltaWidth, float deltaHeight) {
        Base::resizeBy(deltaWidth, deltaHeight);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::grow(float)
    Self& grow(float factor) {
        Base::grow(factor);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::stretch(float, float)
    Self& stretch(float widthFactor, float heightFactor) {
        Base::stretch(widthFactor, heightFactor);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::resizeTo(float, float, double, EasingFunc)
    Self& resizeTo(float width, float height, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::resizeTo(width, height, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::resizeBy(float, float, double, EasingFunc)
    Self& resizeBy(float deltaWidth, float deltaHeight, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::resizeBy(deltaWidth, deltaHeight, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::grow(float, double, EasingFunc)
    Self& grow(float factor, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::grow(factor, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::stretch(float, float, double, EasingFunc)
    Self& stretch(float widthFactor, float heightFactor, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::stretch(widthFactor, heightFactor, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setGrowing(float)
    Self& setGrowing(float amountPerSecond) {
        Base::setGrowing(amountPerSecond);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setStretching(float, float)
    Self& setStretching(float widthPerSecond, float heightPerSecond) {
        Base::setStretching(widthPerSecond, heightPerSecond);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::stopGrowing()
    Self& stopGrowing() {
        Base::stopGrowing();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::stopStretching()
    Self& stopStretching() {
        Base::stopStretching();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeGrowingTo(float, double, EasingFunc)
    Self& changeGrowingTo(float amountPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeGrowingTo(amountPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeGrowingBy(float, double, EasingFunc)
    Self& changeGrowingBy(float deltaPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeGrowingBy(deltaPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeStretchingTo(float, float, double, EasingFunc)
    Self& changeStretchingTo(float widthPerSecond, float heightPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeStretchingTo(widthPerSecond, heightPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeStretchingBy(float, float, double, EasingFunc)
    Self& changeStretchingBy(float deltaWidthPerSecond, float deltaHeightPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeStretchingBy(deltaWidthPerSecond, deltaHeightPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setScale(float, float)
    Self& setScale(float x, float y) {
        Base::setScale(x, y);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setScale(float)
    Self& setScale(float scale) {
        Base::setScale(scale);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeScaleTo(float, float, double, EasingFunc)
    Self& changeScaleTo(float x, float y, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::changeScaleTo(x, y, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeScaleBy(float, float, double, EasingFunc)
    Self& changeScaleBy(float deltaX, float deltaY, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::changeScaleBy(deltaX, deltaY, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::pauseSchedule()
    Self& pauseSchedule() {
        Base::pauseSchedule();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::resumeSchedule()
    Self& resumeSchedule() {
        Base::resumeSchedule();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::cancelSchedule()
    Self& cancelSchedule() {
        Base::cancelSchedule();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setRotation(float)
    Self& setRotation(float radiansRotation) {
        Base::setRotation(radiansRotation);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setCenterOffset(const Offset&)
    Self& setCenterOffset(const Offset& offset) {
        Base::setCenterOffset(offset);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::rotateTo(float)
    Self& rotateTo(float radiansRotation) {
        Base::rotateTo(radiansRotation);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::rotateBy(float)
    Self& rotateBy(float radians) {
        Base::rotateBy(radians);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::rotateTo(float, double, EasingFunc, int)
    Self& rotateTo(float radiansRotation, double durationSeconds, EasingFunc easing = easeInOutQuad, int direction = rotationDirection_AsSpecified) {
        Base::rotateTo(radiansRotation, durationSeconds, easing, direction);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::rotateBy(float, double, EasingFunc, int)
    Self& rotateBy(float radians, double durationSeconds, EasingFunc easing = easeInOutQuad, int direction = rotationDirection_AsSpecified) {
        Base::rotateBy(radians, durationSeconds, easing, direction);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeCenterOffsetTo(float, float, double, EasingFunc)
    Self& changeCenterOffsetTo(float xCenterOffset, float yCenterOffset, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::changeCenterOffsetTo(xCenterOffset, yCenterOffset, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeCenterOffsetTo(const Offset&, double, EasingFunc)
    Self& changeCenterOffsetTo(const Offset& centerOffset, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::changeCenterOffsetTo(centerOffset, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeCenterOffsetBy(float, float, double, EasingFunc)
    Self& changeCenterOffsetBy(float deltaXOffset, float deltaYOffset, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::changeCenterOffsetBy(deltaXOffset, deltaYOffset, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeCenterOffsetBy(const Offset&, double, EasingFunc)
    Self& changeCenterOffsetBy(const Offset& deltaCenterOffset, double durationSeconds, EasingFunc easing = easeInOutQuad) {
        Base::changeCenterOffsetBy(deltaCenterOffset, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setSpin(float)
    Self& setSpin(float radiansPerSecond) {
        Base::setSpin(radiansPerSecond);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::stopSpinning()
    Self& stopSpinning() {
        Base::stopSpinning();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeSpinTo(float, double, EasingFunc)
    Self& changeSpinTo(float radiansPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeSpinTo(radiansPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::changeSpinBy(float, double, EasingFunc)
    Self& changeSpinBy(float deltaRadiansPerSecond, double durationSeconds, EasingFunc easing = linearTween) {
        Base::changeSpinBy(deltaRadiansPerSecond, durationSeconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setFlipX(bool)
    Self& setFlipX(bool flip) {
        Base::setFlipX(flip);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::setFlipY(bool)
    Self& setFlipY(bool flip) {
        Base::setFlipY(flip);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::flipX()
    Self& flipX() {
        Base::flipX();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::flipY()
    Self& flipY() {
        Base::flipY();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::wait(double)
    Self& wait(double durationSeconds) {
        Base::wait(durationSeconds);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::andThen()
    Self& andThen() {
        Base::andThen();
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::addAnimationHelper(IAnimationHelper*)
    Self& addAnimationHelper(IAnimationHelper* helper) {
        Base::addAnimationHelper(helper);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::removeAnimationHelper(IAnimationHelper*)
    Self& removeAnimationHelper(IAnimationHelper* helper) {
        Base::removeAnimationHelper(helper);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedBase::clearAnimationHelpers()
    Self& clearAnimationHelpers() {
        Base::clearAnimationHelpers();
        return static_cast<Self&>(*this);
    }
};

/** Evaluators receive the borrowed target and the operand's local elapsed seconds. */
struct AnimationEvaluationContext {
    AnimatedBase& target;
    double elapsedSeconds;
};

/** Lifecycle notification. Target is borrowed; handlers run after scheduler publication. */
struct AnimationEvent {
    AnimatedBase& target;
    std::string type, scriptName, markName;
    double elapsedSeconds;
    unsigned iteration;
    bool reverse;
    std::string operationName;
};

/** Animate a collection of targets with one script clock. Members keep their
 * rendering, physics and ordinary update owners. Membership is borrowed and
 * expired members are skipped. Nested collections are flattened in insertion order.
 * Snapshots serialize members as shared objects; restored members are retained.
 */
class Troupe : public Animated<Troupe> {
public:
    Troupe() = default;
    #include "pdg/sys/animation-troupe-methods.inc"
    uint32 getMyClassTag() const override { return CLASSTAG_TROUPE; }
    Troupe& add(AnimatedBase& member);
    Troupe& remove(AnimatedBase& member);
    Troupe& clear();
    bool contains(const AnimatedBase& member) const;
    unsigned getMemberCount() const;
    uint32 getSerializedSize(ISerializer* serializer) const override;
    void serialize(ISerializer* serializer) const override;
    void deserialize(IDeserializer* deserializer) override;
    std::vector<AnimatedBase*> animationTargets() const override;
    bool isTroupe() const override { return true; }
private:
    std::vector<std::weak_ptr<AnimatedBase*>> mMembers;
    std::vector<std::shared_ptr<AnimatedBase>> mRestoredMembers;
};

/** Native command recorder. defineScript() retains builders for the library's lifetime. */
class AnimationScript : public Animated<AnimationScript> {
public:
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mAnimationScriptScriptObj{};
#endif
    #include "pdg/sys/animation-script-methods.inc"
    AnimationScript& endScript();
    const std::string& getName() const { return mName; }
private:
    friend class AnimatedBase;
    explicit AnimationScript(std::string name);
    std::string mName;
};

} // end namespace pdg

#endif // PDG_ANIMATED_H_INCLUDED
