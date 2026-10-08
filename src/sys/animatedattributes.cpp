#include "pdg/sys/animatedattributes.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace pdg {
AnimatedAttributesBase::AnimatedAttributesBase()
    : mShear(0), mYAxis(1), mMatrixSample(1), mMatrixActive(false), mFillSwitch(0),
      mFrameProgress(0), mFirstFrame(0),
      mLastFrame(0), mFramesActive(false) {
    mWidth = mHeight = 1;
}
AnimatedAttributesBase::AnimatedAttributesBase(const Attributes& attributes) : AnimatedAttributesBase() {
    assignAttributes(attributes);
}
void AnimatedAttributesBase::assignAttributes(const Attributes& attributes) {
    validateUnrecordedOperation("AnimatedAttributes appearance command");
    validateImmediateOperation();
    if (static_cast<const Attributes*>(this) == &attributes) return;
    validateMatrix(attributes.getTransform());
    mAnimations.clear(); mMatrixActive = mFramesActive = false; mFillSwitch = 0;
    finishAnimationRequest(); mAttributeStarts.clear();
    Attributes::assignAttributes(attributes);
    setTransform(attributes.getTransform());
}

void AnimatedAttributesBase::tween(std::initializer_list<Value> values, double seconds, EasingFunc easing, bool replacesFill) {
    validateUnrecordedOperation("AnimatedAttributes appearance command");
    // Validate the complete request before interrupting any existing channels.
    validateAnimationDuration(seconds);
    for (const Value& v : values) Animation(v.field, v.target, easing, mDelaySeconds, seconds);
    for (const Value& v : values) {
        if (isFillField(v.field)) markAppearance(Fill);
        if (v.field == &mLineColor.red || v.field == &mLineColor.green || v.field == &mLineColor.blue || v.field == &mLineColor.alpha) markAppearance(LineColor);
        if (v.field == &mAmbientLight.red || v.field == &mAmbientLight.green || v.field == &mAmbientLight.blue || v.field == &mAmbientLight.alpha) markAppearance(AmbientLight);
        if (v.field == &mSubsection.left || v.field == &mSubsection.top || v.field == &mSubsection.right || v.field == &mSubsection.bottom) markAppearance(Subsection);
        if (v.field == &mPolarOffset.x || v.field == &mPolarOffset.y) markAppearance(PolarOffset);
        if (v.field == &mLightOffset.x || v.field == &mLightOffset.y) markAppearance(LightOffset);
        if (v.field == &mLineThickness) markAppearance(LineThickness);
        if (v.field == &mLineOpacity) markAppearance(LineOpacity);
        if (v.field == &mFillOpacity) markAppearance(FillOpacity);
        if (v.field == &mTextSize) markAppearance(TextSize);
        if (v.field == &mRoundedCornerRadius) markAppearance(RoundedCorners);
    }
    beginAnimationRequest();
    if (replacesFill && !mAppendAnimation) attributeChanging(Fill);
    for (const Value& v : values) scheduleAnimation(v.field, v.target, seconds, easing);
    finishAnimationRequest();
}
void AnimatedAttributesBase::switchFill(GradientType mode, double delay, bool chained) {
    if (!chained) cancelAnimation(&mFillSwitch);
    if (!chained && delay == 0) mGradientType = mode;
    else {
        // The marker switches discrete fill mode before this operation's values sample.
        AttributeStart start(AttributeStart::FillMode); start.first = mode;
        mAttributeStarts.insert_or_assign(mAnimationOperation,start);
        Animation marker(&mFillSwitch,0,linearTween,delay,0);
        marker.operation = mAnimationOperation; marker.chained = chained;
        auto first = std::find_if(mAnimations.begin(),mAnimations.end(),[this](const Animation& a) { return a.operation == mAnimationOperation; });
        mAnimations.insert(first,marker);
    }
    if (mLineStyle == lineStyle_Auto) mLineStyle = lineStyle_None;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeLineColor(const Color& target, double seconds, EasingFunc easing) {
    if(recordOperation("changeLineColor", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mLineColor.red, target.red}, {&mLineColor.green, target.green}, {&mLineColor.blue, target.blue}, {&mLineColor.alpha, target.alpha}}, seconds, easing);
    if (mLineStyle == lineStyle_Auto) mLineStyle = lineStyle_Solid;
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeLineThickness(float target, double seconds, EasingFunc easing) {
    if(recordOperation("changeLineThickness", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mLineThickness, target}}, seconds, easing);
    if (mLineStyle == lineStyle_Auto) mLineStyle = lineStyle_Solid;
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeLineOpacity(float target, double seconds, EasingFunc easing) {
    if(recordOperation("changeLineOpacity", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mLineOpacity, target}}, seconds, easing);
    if (mLineStyle == lineStyle_Auto) mLineStyle = lineStyle_Solid;
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeFillColor(const Color& target, double seconds, EasingFunc easing) {
    if(recordOperation("changeFillColor", captureAnimationArguments(target, seconds, easing))) return *this;
    const double delay = mDelaySeconds; const bool chained = mAppendAnimation;
    tween({{&mFillColor.red, target.red}, {&mFillColor.green, target.green}, {&mFillColor.blue, target.blue}, {&mFillColor.alpha, target.alpha}}, seconds, easing, true);
    switchFill(gradientType_None, delay, chained);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeFillOpacity(float target, double seconds, EasingFunc easing) {
    if(recordOperation("changeFillOpacity", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mFillOpacity, target}}, seconds, easing);
    if (mLineStyle == lineStyle_Auto) mLineStyle = lineStyle_None;
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeRoundedCorners(float target, double seconds, EasingFunc easing) {
    if(recordOperation("changeRoundedCorners", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mRoundedCornerRadius, target}}, seconds, easing);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeTextSize(float target, double seconds, EasingFunc easing) {
    if(recordOperation("changeTextSize", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mTextSize, target}}, seconds, easing);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeSubsection(const Rect& target, double seconds, EasingFunc easing) {
    if(recordOperation("changeSubsection", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mSubsection.left, target.left}, {&mSubsection.top, target.top}, {&mSubsection.right, target.right}, {&mSubsection.bottom, target.bottom}}, seconds, easing);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changePolarOffset(const Offset& target, double seconds, EasingFunc easing) {
    if(recordOperation("changePolarOffset", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mPolarOffset.x, target.x}, {&mPolarOffset.y, target.y}}, seconds, easing);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeLightOffset(const Offset& target, double seconds, EasingFunc easing) {
    if(recordOperation("changeLightOffset", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mLightOffset.x, target.x}, {&mLightOffset.y, target.y}}, seconds, easing);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeAmbientLight(const Color& target, double seconds, EasingFunc easing) {
    if(recordOperation("changeAmbientLight", captureAnimationArguments(target, seconds, easing))) return *this;
    tween({{&mAmbientLight.red, target.red}, {&mAmbientLight.green, target.green}, {&mAmbientLight.blue, target.blue}, {&mAmbientLight.alpha, target.alpha}}, seconds, easing);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeFillGradient(const Point& start, const Color& startColor, const Point& end, const Color& endColor, double seconds, EasingFunc easing) {
    if(recordOperation("changeFillGradient", captureAnimationArguments(start, startColor, end, endColor, seconds, easing))) return *this;
    const double delay = mDelaySeconds; const bool chained = mAppendAnimation;
    tween({{&mGradientStart.x, start.x}, {&mGradientStart.y, start.y}, {&mGradientStartColor.red, startColor.red}, {&mGradientStartColor.green, startColor.green}, {&mGradientStartColor.blue, startColor.blue}, {&mGradientStartColor.alpha, startColor.alpha}, {&mGradientEnd.x, end.x}, {&mGradientEnd.y, end.y}, {&mGradientEndColor.red, endColor.red}, {&mGradientEndColor.green, endColor.green}, {&mGradientEndColor.blue, endColor.blue}, {&mGradientEndColor.alpha, endColor.alpha}}, seconds, easing, true);
    switchFill(gradientType_Linear, delay, chained);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeFillRadialGradient(const Point& center, const Color& centerColor, float radius, const Color& endColor, double seconds, EasingFunc easing) {
    if(recordOperation("changeFillRadialGradient", captureAnimationArguments(center, centerColor, radius, endColor, seconds, easing))) return *this;
    const double delay = mDelaySeconds; const bool chained = mAppendAnimation;
    tween({{&mRadialGradientCenter.x, center.x}, {&mRadialGradientCenter.y, center.y}, {&mRadialGradientCenterColor.red, centerColor.red}, {&mRadialGradientCenterColor.green, centerColor.green}, {&mRadialGradientCenterColor.blue, centerColor.blue}, {&mRadialGradientCenterColor.alpha, centerColor.alpha}, {&mRadialGradientRadius, radius}, {&mRadialGradientEndColor.red, endColor.red}, {&mRadialGradientEndColor.green, endColor.green}, {&mRadialGradientEndColor.blue, endColor.blue}, {&mRadialGradientEndColor.alpha, endColor.alpha}}, seconds, easing, true);
    switchFill(gradientType_Radial, delay, chained);
    return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeSphereRotation(float radians, double seconds, EasingFunc easing, int direction) {
    if(recordOperation("changeSphereRotation", captureAnimationArguments(radians, seconds, easing, direction))) return *this;
    validateUnrecordedOperation("AnimatedAttributes appearance command");
    validateAnimationDuration(seconds);
    rotationTarget(mSphereRotation, radians, direction, false); // validate direction before mutation
    Animation a(&mSphereRotation, radians, easing, mDelaySeconds, seconds);
    markAppearance(SphereRotation);
    a.resolveRotation = true; a.rotationDirection = direction;
    beginAnimationRequest(); a.operation = mAnimationOperation; a.chained = mAppendAnimation;
    prepareAnimation(&mSphereRotation);
    if (!mAppendAnimation && seconds == 0 && mDelaySeconds == 0)
        mSphereRotation = rotationTarget(mSphereRotation, radians, direction, false);
    else mAnimations.push_back(a);
    finishAnimationRequest(); return *this;
}
AnimatedAttributesBase& AnimatedAttributesBase::changeFrames(int first, int last, double seconds, EasingFunc easing) {
    if(recordOperation("changeFrames", captureAnimationArguments(first, last, seconds, easing))) return *this;
    validateUnrecordedOperation("AnimatedAttributes appearance command");
    validateAnimationDuration(seconds);
    Animation a(&mFrameProgress, 1, easing, mDelaySeconds, seconds);
    markAppearance(Frame);
    beginAnimationRequest(); a.operation = mAnimationOperation; a.chained = mAppendAnimation;
    prepareAnimation(&mFrameProgress);
    AttributeStart start(AttributeStart::Frames); start.first = first; start.last = last;
    mAttributeStarts.insert_or_assign(mAnimationOperation,start);
    if (!mAppendAnimation && mDelaySeconds == 0) animationStarting(a);
    if (!mAppendAnimation && seconds == 0 && mDelaySeconds == 0) mFrameProgress = 1;
    else mAnimations.push_back(a);
    finishAnimationRequest(); animationValuesChanged(); return *this;
}

AnimatedAttributesBase& AnimatedAttributesBase::changeSkew(float x, float y, double seconds, EasingFunc easing) {
    if(recordOperation("changeSkew", captureAnimationArguments(x, y, seconds, easing))) return *this;
    glm::mat3 shear(1); shear[0][1] = x; shear[1][0] = y;
    const bool chained = mAppendAnimation;
    changeTransform(getTransform() * shear, seconds, easing);
    if (chained) {
        AttributeStart start(AttributeStart::Skew); start.matrix = shear;
        mAttributeStarts.insert_or_assign(mAnimationOperation,start);
    }
    return *this;
}
void AnimatedAttributesBase::validateMatrix(const glm::mat3& matrix) {
    for (int c=0;c<3;++c) for (int r=0;r<3;++r)
        if (!std::isfinite(matrix[c][r])) throw std::invalid_argument("Transform must be finite");
    if (matrix[0][2]!=0 || matrix[1][2]!=0 || matrix[2][2]!=1)
        throw std::invalid_argument("AnimatedAttributes requires an affine 2D transform");
}
AnimatedAttributesBase& AnimatedAttributesBase::changeTransform(const glm::mat3& target, double seconds, EasingFunc easing) {
    if(recordOperation("changeTransform", captureAnimationArguments(target, seconds, easing))) return *this;
    validateUnrecordedOperation("AnimatedAttributes appearance command");
    validateMatrix(target); validateAnimationDuration(seconds);
    if (!mAppendAnimation) validateTransformSize(target);
    if (!easing) throw std::invalid_argument("Easing is required");
    const glm::mat3 targetCopy = target;
    if (!mAppendAnimation) {
        mMatrixSample = getTransform();
        cancelMatrixAnimation();
        // Plain matrix requests acquire the whole transform immediately.
        cancelProgrammedMotion();
        cancelAnimation(&mDeltaWidthPerMs); cancelAnimation(&mDeltaHeightPerMs);
        mDeltaWidthPerMs = mDeltaHeightPerMs = 0;
        for (float* field : {&mLocation.x,&mLocation.y,&mWidth,&mHeight,&mScaleX,&mScaleY,&mFacing,&mCenterOffset.x,&mCenterOffset.y}) cancelAnimation(field);
        mMatrixActive = true;
    }
    beginAnimationRequest();
    for (int c=0;c<3;++c) for (int r=0;r<2;++r)
        scheduleAnimation(&mMatrixSample[c][r], targetCopy[c][r], seconds, easing);
    if (mAppendAnimation) {
        AttributeStart start(AttributeStart::Matrix); start.matrix = targetCopy;
        mAttributeStarts.emplace(mAnimationOperation,start);
    }
    finishAnimationRequest();
    animationValuesChanged(); return *this;
}

void AnimatedAttributesBase::cancelMatrixAnimation() {
    for (int c=0;c<3;++c) for (int r=0;r<2;++r) cancelAnimation(&mMatrixSample[c][r]);
    mMatrixActive = false;
}
void AnimatedAttributesBase::cancelAnimation(float* value) {
    // All component setters and timed requests acquire their channel here, after
    // validation. A component request interrupts an active whole-matrix tween.
    if (isComponentField(value)) cancelMatrixAnimation();
    AnimatedBase::cancelAnimation(value);
    discardUnusedStarts();
}
bool AnimatedAttributesBase::isMatrixField(const float* value) const {
    for (int c=0;c<3;++c) for (int r=0;r<2;++r) if (value==&mMatrixSample[c][r]) return true;
    return false;
}
bool AnimatedAttributesBase::isComponentField(const float* value) const {
    for (const float* field : {&mLocation.x,&mLocation.y,&mWidth,&mHeight,&mScaleX,&mScaleY,&mFacing,
        &mCenterOffset.x,&mCenterOffset.y,&mDeltaXPerMs,&mDeltaYPerMs,&mDeltaFacingPerMs,&mDeltaWidthPerMs,&mDeltaHeightPerMs})
        if (value == field) return true;
    return false;
}
bool AnimatedAttributesBase::isFillField(const float* value) const {
    for (const float* field : {&mFillSwitch,&mFillColor.red,&mFillColor.green,&mFillColor.blue,&mFillColor.alpha,
        &mGradientStart.x,&mGradientStart.y,&mGradientEnd.x,&mGradientEnd.y,
        &mGradientStartColor.red,&mGradientStartColor.green,&mGradientStartColor.blue,&mGradientStartColor.alpha,
        &mGradientEndColor.red,&mGradientEndColor.green,&mGradientEndColor.blue,&mGradientEndColor.alpha,
        &mRadialGradientCenter.x,&mRadialGradientCenter.y,&mRadialGradientCenterColor.red,&mRadialGradientCenterColor.green,
        &mRadialGradientCenterColor.blue,&mRadialGradientCenterColor.alpha,&mRadialGradientEndColor.red,
        &mRadialGradientEndColor.green,&mRadialGradientEndColor.blue,&mRadialGradientEndColor.alpha,&mRadialGradientRadius})
        if (value == field) return true;
    return false;
}
bool AnimatedAttributesBase::animationChannelsConflict(float* a, float* b) const {
    return a==b || (isMatrixField(a) && isComponentField(b)) || (isComponentField(a) && isMatrixField(b)) ||
        (isFillField(a) && isFillField(b));
}
void AnimatedAttributesBase::discardUnusedStarts() {
    for (auto it=mAttributeStarts.begin();it!=mAttributeStarts.end();) {
        const uint64 operation = it->first;
        if (std::none_of(mAnimations.begin(),mAnimations.end(),[operation](const Animation& a) { return a.operation==operation; }))
            it=mAttributeStarts.erase(it);
        else ++it;
    }
}
void AnimatedAttributesBase::animationStarting(Animation& a) {
    if (isComponentField(a.value)) mMatrixActive = false;
    auto it=mAttributeStarts.find(a.operation);
    if (it==mAttributeStarts.end()) return;
    const AttributeStart start=it->second;
    if (start.kind == AttributeStart::Matrix || start.kind == AttributeStart::Skew) {
        // A queued resize may change the reference dimensions before this starts.
        const glm::mat3 target = start.kind == AttributeStart::Skew ? getTransform()*start.matrix : start.matrix;
        try { validateTransformSize(target); }
        catch (...) { cancelMatrixAnimation(); throw; }
    }
    mAttributeStarts.erase(it);
    if (start.kind == AttributeStart::FillMode) mGradientType=static_cast<GradientType>(start.first);
    else if (start.kind == AttributeStart::Frames) {
        mFirstFrame=start.first; mLastFrame=start.last;
        mFrame=mFirstFrame; mFrameProgress=0; mFramesActive=true;
    } else {
        mMatrixSample=getTransform(); mMatrixActive=true;
        mDeltaXPerMs=mDeltaYPerMs=mDeltaFacingPerMs=mDeltaWidthPerMs=mDeltaHeightPerMs=0;
        if (start.kind == AttributeStart::Skew) {
            const glm::mat3 target=mMatrixSample*start.matrix;
            for (auto& track : mAnimations) if (track.operation==a.operation)
                for (int c=0;c<3;++c) for (int r=0;r<2;++r)
                    if (track.value==&mMatrixSample[c][r]) track.targetVal=target[c][r];
        }
    }
}

void AnimatedAttributesBase::updateTransform() {
    const float c = std::cos(mFacing), s = std::sin(mFacing);
    const float w = mWidth * (mFlipX ? -1 : 1), h = mHeight * (mFlipY ? -1 : 1);
    glm::mat3 matrix(1);
    matrix[0] = glm::vec3(c,s,0) * (w*mScaleX);
    matrix[1] = glm::vec3(c*mShear-s*mYAxis,s*mShear+c*mYAxis,0) * (h*mScaleY);
    matrix[2] = glm::vec3(mLocation.x+mCenterOffset.x,mLocation.y+mCenterOffset.y,1)
        - matrix[0]*mCenterOffset.x - matrix[1]*mCenterOffset.y;
    mTransform = matrix;
}
const glm::mat3& AnimatedAttributesBase::getTransform() const {
    if (mDrawingLayoutSample) {
        mLayoutSample = glm::mat3(1);
        mLayoutSample[0][0] = mWidth; mLayoutSample[1][1] = mHeight;
        mLayoutSample[2] = glm::vec3(mLocation.x, mLocation.y, 1);
        return mLayoutSample;
    }
    const_cast<AnimatedAttributesBase*>(this)->updateTransform(); return mTransform;
}
void AnimatedAttributesBase::validateTransformSize(const glm::mat3& matrix) const {
    // A finite scale cannot expand a zero logical dimension into a nonzero column.
    if ((mWidth == 0 && (matrix[0][0] != 0 || matrix[0][1] != 0)) ||
        (mHeight == 0 && (matrix[1][0] != 0 || matrix[1][1] != 0)))
        throw std::invalid_argument("A nonzero transform column requires a nonzero logical dimension");
}
void AnimatedAttributesBase::adoptTransform(const glm::mat3& matrix) {
    validateTransformSize(matrix);
    const float xLength = std::hypot(matrix[0][0],matrix[0][1]);
    const float yLength = std::hypot(matrix[1][0],matrix[1][1]);
    if (xLength != 0) mFacing = std::atan2(matrix[0][1],matrix[0][0]);
    else if (yLength != 0) mFacing = std::atan2(-matrix[1][0],matrix[1][1]);
    const float c=std::cos(mFacing), s=std::sin(mFacing);
    const float along = c*matrix[1][0]+s*matrix[1][1];
    const float across = -s*matrix[1][0]+c*matrix[1][1];
    const float signedYLength = across < 0 ? -yLength : yLength;
    // Keep reference size and explicit flips. Scaling belongs to AnimatedBase's scale
    // channels. A normalized second-column direction also retains rank-one shear.
    if (mWidth != 0) mScaleX = xLength / (mWidth * (mFlipX ? -1 : 1));
    if (mHeight != 0) mScaleY = signedYLength / (mHeight * (mFlipY ? -1 : 1));
    if (yLength != 0) {
        mShear = along / signedYLength;
        mYAxis = across / signedYLength;
    }
    mLocation = Point(matrix[2][0]-mCenterOffset.x+matrix[0][0]*mCenterOffset.x+matrix[1][0]*mCenterOffset.y,
        matrix[2][1]-mCenterOffset.y+matrix[0][1]*mCenterOffset.x+matrix[1][1]*mCenterOffset.y);
    updateTransform();
}
void AnimatedAttributesBase::cancelTransformAnimation() {
    cancelMatrixAnimation(); stopMovement(); stopSpinning(); stopGrowing(); stopStretching();
    for (float* field : {&mLocation.x,&mLocation.y,&mWidth,&mHeight,&mScaleX,&mScaleY,&mFacing,&mCenterOffset.x,&mCenterOffset.y}) cancelAnimation(field);
}
Attributes& AnimatedAttributesBase::composeTransform(const glm::mat3& matrix, TransformOperation operation) {
    validateImmediateOperation();
    validateMatrix(matrix);
    const glm::mat3 result = getTransform() * matrix;
    validateMatrix(result);
    if (operation == TransformOperation::General) {
        setTransform(result);
        return *this;
    }
    const Point location = mLocation;
    const Offset scale = getScale();
    const Offset nextScale = operation == TransformOperation::Scale
        ? Offset(mScaleX*matrix[0][0],mScaleY*matrix[1][1]) : scale;
    if (!std::isfinite(nextScale.x) || !std::isfinite(nextScale.y))
        throw std::invalid_argument("Scale must be finite");
    cancelTransformAnimation();
    // Translation and axis scaling have exact component updates, even with a
    // collapsed axis. Preserve rotation, signed scale, shear and reference size.
    mScaleX = nextScale.x; mScaleY = nextScale.y;
    mLocation = Point(result[2][0]-mCenterOffset.x+result[0][0]*mCenterOffset.x+result[1][0]*mCenterOffset.y,
        result[2][1]-mCenterOffset.y+result[0][1]*mCenterOffset.x+result[1][1]*mCenterOffset.y);
    updateTransform();
    locationChanged(mLocation-location); scaleChanged(getScale()-scale);
    return *this;
}
void AnimatedAttributesBase::setTransformImpl(const glm::mat3& matrix) {
    validateUnrecordedOperation("AnimatedAttributes appearance command");
    validateImmediateOperation();
    validateMatrix(matrix); validateTransformSize(matrix);
    const glm::mat3 copy = matrix;
    cancelTransformAnimation();
    const Point location = mLocation; const float rotation=mFacing; const Offset scale=getScale();
    adoptTransform(copy);
    locationChanged(mLocation-location); rotationChanged(mFacing-rotation); scaleChanged(getScale()-scale);
}
void AnimatedAttributesBase::locationChanged(const Offset&) { if (!mAnimating) cancelMatrixAnimation(); updateTransform(); }
void AnimatedAttributesBase::sizeChanged(float,float) { if (!mAnimating) cancelMatrixAnimation(); updateTransform(); }
void AnimatedAttributesBase::scaleChanged(const Offset&) { if (!mAnimating) cancelMatrixAnimation(); updateTransform(); }
void AnimatedAttributesBase::rotationChanged(float) { if (!mAnimating) cancelMatrixAnimation(); updateTransform(); }
void AnimatedAttributesBase::centerChanged(const Offset&) { if (!mAnimating) cancelMatrixAnimation(); updateTransform(); }
void AnimatedAttributesBase::flipChanged(bool,bool) { if (!mAnimating) cancelMatrixAnimation(); updateTransform(); }
void AnimatedAttributesBase::animationValuesChanged() {
    if (mMatrixActive) {
        adoptTransform(mMatrixSample);
        mMatrixActive = animationChannelScheduled(&mMatrixSample[0][0]) || std::any_of(mAnimations.begin(),mAnimations.end(),[this](const Animation& a) {
            for(int c=0;c<3;++c) for(int r=0;r<2;++r) if(a.value==&mMatrixSample[c][r] && !a.chained) return true;
            return false;
        });
    }
    if (mFramesActive) {
        const auto frameTrack=std::find_if(mAnimations.begin(),mAnimations.end(),[this](const Animation& a) { return a.value==&mFrameProgress; });
        if (frameTrack==mAnimations.end() || frameTrack->delaySeconds==0 || frameTrack->chained) {
            const double count=std::abs(double(mLastFrame)-mFirstFrame)+1;
            const double index=std::min(count-1,std::floor(std::clamp(double(mFrameProgress),0.0,1.0)*count));
            mFrame = static_cast<int>(mFirstFrame + (mLastFrame>=mFirstFrame?index:-index));
        }
    }
    updateTransform();
    discardUnusedStarts();
}
void AnimatedAttributesBase::cancelScheduleImpl() {
    AnimatedBase::cancelScheduleImpl();
    mAttributeStarts.clear();
    mMatrixActive = mFramesActive = false;
    mFillSwitch = 0;
}
bool AnimatedAttributesBase::animate(double seconds) {
    validateDuration(seconds);
    if (mMatrixActive && (mDeltaWidthPerMs != 0 || mDeltaHeightPerMs != 0)) cancelMatrixAnimation();
    try { return AnimatedBase::animate(seconds); }
    catch (...) { mAnimating = false; throw; }
}
void AnimatedAttributesBase::attributeChanging(AttributeChannel channel) {
    validateUnrecordedOperation("AnimatedAttributes appearance command");
    Attributes::attributeChanging(channel);
    switch (channel) {
    case StrokeStyle: case Texture: case Fit: case Clip: case Blend: case TextStyle: case Typeface: break;
    case LineColor:
        cancelAnimation(&mLineColor.red); cancelAnimation(&mLineColor.green); cancelAnimation(&mLineColor.blue); cancelAnimation(&mLineColor.alpha); break;
    case LineThickness:
        cancelAnimation(&mLineThickness); break;
    case LineOpacity:
        cancelAnimation(&mLineOpacity); break;
    case Fill:
        mFillSwitch = 0;
        cancelAnimation(&mFillColor.red); cancelAnimation(&mFillColor.green); cancelAnimation(&mFillColor.blue); cancelAnimation(&mFillColor.alpha); cancelAnimation(&mGradientStart.x); cancelAnimation(&mGradientStart.y); cancelAnimation(&mGradientEnd.x); cancelAnimation(&mGradientEnd.y); cancelAnimation(&mGradientStartColor.red); cancelAnimation(&mGradientStartColor.green); cancelAnimation(&mGradientStartColor.blue); cancelAnimation(&mGradientStartColor.alpha); cancelAnimation(&mGradientEndColor.red); cancelAnimation(&mGradientEndColor.green); cancelAnimation(&mGradientEndColor.blue); cancelAnimation(&mGradientEndColor.alpha); cancelAnimation(&mRadialGradientCenter.x); cancelAnimation(&mRadialGradientCenter.y); cancelAnimation(&mRadialGradientCenterColor.red); cancelAnimation(&mRadialGradientCenterColor.green); cancelAnimation(&mRadialGradientCenterColor.blue); cancelAnimation(&mRadialGradientCenterColor.alpha); cancelAnimation(&mRadialGradientEndColor.red); cancelAnimation(&mRadialGradientEndColor.green); cancelAnimation(&mRadialGradientEndColor.blue); cancelAnimation(&mRadialGradientEndColor.alpha); cancelAnimation(&mRadialGradientRadius); cancelAnimation(&mFillSwitch); break;
    case FillOpacity:
        cancelAnimation(&mFillOpacity); break;
    case RoundedCorners:
        cancelAnimation(&mRoundedCornerRadius); break;
    case TextSize:
        cancelAnimation(&mTextSize); break;
    case Subsection:
        cancelAnimation(&mSubsection.left); cancelAnimation(&mSubsection.top); cancelAnimation(&mSubsection.right); cancelAnimation(&mSubsection.bottom); break;
    case PolarOffset:
        cancelAnimation(&mPolarOffset.x); cancelAnimation(&mPolarOffset.y); break;
    case LightOffset:
        cancelAnimation(&mLightOffset.x); cancelAnimation(&mLightOffset.y); break;
    case AmbientLight:
        cancelAnimation(&mAmbientLight.red); cancelAnimation(&mAmbientLight.green); cancelAnimation(&mAmbientLight.blue); cancelAnimation(&mAmbientLight.alpha); break;
    case SphereRotation:
        cancelAnimation(&mSphereRotation); break;
    case Frame:
        mFramesActive = false;
        cancelAnimation(&mFrameProgress); break;
    }
}
} // namespace pdg

namespace pdg {
#include "animation-operations-animatedattributesbase.inc"
}

namespace pdg {
std::vector<const float*> AnimatedAttributesBase::tweenFields() const {
    auto fields=AnimatedBase::tweenFields();
    for(auto* field : {&mLineColor.red, &mLineColor.green, &mLineColor.blue, &mLineColor.alpha, &mLineThickness, &mLineOpacity, &mFillColor.red, &mFillColor.green, &mFillColor.blue, &mFillColor.alpha, &mFillOpacity, &mGradientStart.x, &mGradientStart.y, &mGradientEnd.x, &mGradientEnd.y, &mGradientStartColor.red, &mGradientStartColor.green, &mGradientStartColor.blue, &mGradientStartColor.alpha, &mGradientEndColor.red, &mGradientEndColor.green, &mGradientEndColor.blue, &mGradientEndColor.alpha, &mRadialGradientCenter.x, &mRadialGradientCenter.y, &mRadialGradientRadius, &mRadialGradientCenterColor.red, &mRadialGradientCenterColor.green, &mRadialGradientCenterColor.blue, &mRadialGradientCenterColor.alpha, &mRadialGradientEndColor.red, &mRadialGradientEndColor.green, &mRadialGradientEndColor.blue, &mRadialGradientEndColor.alpha, &mRoundedCornerRadius, &mTextSize, &mSubsection.left, &mSubsection.top, &mSubsection.right, &mSubsection.bottom, &mSphereRotation, &mPolarOffset.x, &mPolarOffset.y, &mLightOffset.x, &mLightOffset.y, &mAmbientLight.red, &mAmbientLight.green, &mAmbientLight.blue, &mAmbientLight.alpha, &mFillSwitch, &mFrameProgress, &mShear, &mYAxis}) fields.push_back(field);
    for(int c=0;c<3;++c) for(int r=0;r<2;++r) fields.push_back(&mMatrixSample[c][r]);
    return fields;
}
}
