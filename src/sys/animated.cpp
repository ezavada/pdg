// -----------------------------------------------
// animated.cpp
// 
// animation functionality
//
// Written by Ed Zavada, 2010-2012
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

 
#include "pdg_project.h"
#include <numbers>
#include "snapshot-codec.h"

#include "pdg/sys/animated.h"
#include "pdg/sys/color.h"
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"

#include <algorithm>
#include <cmath>  // for sin() and cos()



namespace pdg {
void AnimatedBase::cancelProgrammedMotion() {
    for (float* field : {&mLocation.x, &mLocation.y, &mFacing,
         &mDeltaXPerMs, &mDeltaYPerMs, &mDeltaFacingPerMs}) cancelAnimation(field);
    mDeltaXPerMs = mDeltaYPerMs = mDeltaFacingPerMs = 0;
}



uint32 AnimatedBase::getSerializedSize(ISerializer* serializer) const {
    // Base transform/rates only. Subclasses with artwork, physics or appearance
    // state supply their own complete object records.
    SnapshotWriter out(serializer, false);
    out.flag(mSchedulePaused); out.flag(mFlipX); out.flag(mFlipY);
    const auto fields = tweenFields();
    for (size_t i=0;i<fields.size();++i) out.floating(*fields[i], (i==animationChannel_ScaleX || i==animationChannel_ScaleY) ? 1 : 0);
    return 5 + out.size() + tweenSerializedSize(serializer);
}
void AnimatedBase::serialize(ISerializer* serializer) const {
    serializer->serialize_4u(0x414e494d); // ANIM
    serializer->serialize_1u(2);
    SnapshotWriter out(serializer, true);
    out.flag(mSchedulePaused); out.flag(mFlipX); out.flag(mFlipY);
    const auto fields = tweenFields();
    for (size_t i=0;i<fields.size();++i) out.floating(*fields[i], (i==animationChannel_ScaleX || i==animationChannel_ScaleY) ? 1 : 0);
    serializeTweens(serializer);
}
void AnimatedBase::deserialize(IDeserializer* deserializer) {
    validateTransformEdit();
    validateProgrammedTransform();
    if (deserializer->deserialize_4u() != 0x414e494d || deserializer->deserialize_1u() != 2)
        throw std::runtime_error("Unsupported Animated snapshot");
    SnapshotReader in(deserializer);
    const bool paused=in.flag(), reflectedX=in.flag(), reflectedY=in.flag();
    const auto fields = tweenFields();
    std::vector<float> values;
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto value = in.floating((i==animationChannel_ScaleX || i==animationChannel_ScaleY) ? 1 : 0);
        if (!std::isfinite(value)) throw std::runtime_error("Invalid Animated field");
        values.push_back(value);
    }
    deserializeTweens(deserializer); // validates the entire track record before replacing it
    const auto location = mLocation;
    const auto center = mCenterOffset;
    const auto scale = getScale();
    const float width = mWidth, height = mHeight, angle = mFacing;
    const bool flipX = mFlipX, flipY = mFlipY;
    for (size_t i = 0; i < fields.size(); ++i) *const_cast<float*>(fields[i]) = values[i];
    mSchedulePaused = paused; mFlipX = reflectedX; mFlipY = reflectedY;
    animationValuesChanged();
    locationChanged(mLocation-location); centerChanged(mCenterOffset-center);
    sizeChanged(mWidth-width,mHeight-height); scaleChanged(getScale()-scale); rotationChanged(mFacing-angle);
    flipChanged(mFlipX!=flipX,mFlipY!=flipY);
}

std::vector<const float*> AnimatedBase::tweenFields() const {
    std::vector<const float*> fields(animationChannel_BaseCount);
    fields[animationChannel_LocationX] = &mLocation.x;
    fields[animationChannel_LocationY] = &mLocation.y;
    fields[animationChannel_Facing] = &mFacing;
    fields[animationChannel_Width] = &mWidth;
    fields[animationChannel_Height] = &mHeight;
    fields[animationChannel_ScaleX] = &mScaleX;
    fields[animationChannel_ScaleY] = &mScaleY;
    fields[animationChannel_CenterOffsetX] = &mCenterOffset.x;
    fields[animationChannel_CenterOffsetY] = &mCenterOffset.y;
    fields[animationChannel_MovementX] = &mDeltaXPerMs;
    fields[animationChannel_MovementY] = &mDeltaYPerMs;
    fields[animationChannel_Spinning] = &mDeltaFacingPerMs;
    fields[animationChannel_StretchingWidth] = &mDeltaWidthPerMs;
    fields[animationChannel_StretchingHeight] = &mDeltaHeightPerMs;
    return fields;
}

void AnimatedBase::copyAnimationStateFrom(const AnimatedBase& source) {
    const auto from = source.tweenFields(), to = tweenFields();
    if (from.size() != to.size()) throw std::logic_error("Incompatible animation template");
    auto tracks = source.mAnimations;
    for (auto& track : tracks) {
        auto field = std::find(from.begin(), from.end(), track.value);
        if (field == from.end() || !to[field - from.begin()])
            throw std::logic_error("Unknown animation template channel");
        track.value = const_cast<float*>(to[field - from.begin()]);
    }
    for (size_t i = 0; i < from.size(); ++i)
        if (from[i] && to[i]) *const_cast<float*>(to[i]) = *from[i];
    mFlipX = source.mFlipX; mFlipY = source.mFlipY;
    mDelaySeconds = source.mDelaySeconds; mSchedulePaused = source.mSchedulePaused;
    mAppendAnimation = source.mAppendAnimation; mWaitPending = source.mWaitPending;
    mAnimationOperation = source.mAnimationOperation;
    mAnimations = std::move(tracks);
    copyScriptStateFrom(source);
}

uint32 AnimatedBase::tweenSerializedSize(ISerializer* serializer) const {
    const bool hasWait = mWaitPending || mDelaySeconds > 0;
    uint32 flagsSize = serializer->sizeof_bool(hasWait);
    flagsSize += serializer->sizeof_bool(mAppendAnimation);
    SnapshotWriter out(serializer, false);
    for (const auto& a : mAnimations) {
        out.real(a.delaySeconds); out.real(a.durationSeconds); out.real(a.elapsedSeconds);
        out.floating(a.beginVal); out.floating(a.deltaVal); out.floating(a.targetVal);
    }
    for(double credit:mTroupeRateTime) out.real(credit);
    return 1 + flagsSize + (hasWait ? serializer->sizeof_d(mDelaySeconds) : 0)
        + serializer->sizeof_uint(mAnimations.size()) + static_cast<uint32>(mAnimations.size()) * 4 + out.size() + scriptSerializedSize(serializer);
}
void AnimatedBase::serializeTweens(ISerializer* serializer) const {
    const auto fields = tweenFields();
    serializer->serialize_1u(6); // collective integration credits and symbolic scripts follow
    const bool hasWait = mWaitPending || mDelaySeconds > 0;
    serializer->serialize_bool(hasWait);
    serializer->serialize_bool(mAppendAnimation);
    if (hasWait) serializer->serialize_d(mDelaySeconds);
    serializer->serialize_uint(mAnimations.size());
    for (const auto& a : mAnimations) {
        const auto field = std::find(fields.begin(), fields.end(), a.value);
        if (field == fields.end()) throw std::runtime_error("Unknown animation tween channel");
        serializer->serialize_1u(static_cast<uint8>(field-fields.begin()));
        serializer->serialize_1u(easingFuncToId(a.easing));
        serializer->serialize_1u(a.rotationDirection);
        serializer->serialize_1u(animationFlags(a));
        SnapshotWriter out(serializer, true);
        out.real(a.delaySeconds); out.real(a.durationSeconds); out.real(a.elapsedSeconds);
        out.floating(a.beginVal); out.floating(a.deltaVal); out.floating(a.targetVal);
    }
    SnapshotWriter credits(serializer,true);
    for(double credit:mTroupeRateTime) credits.real(credit);
    serializeScripts(serializer);
}
void AnimatedBase::deserializeTweens(IDeserializer* deserializer) {
    const auto revision = deserializer->deserialize_1u();
    if (revision < 1 || revision > 6) throw std::runtime_error("Unsupported animation tween record");
    const bool hasWait = revision == 1 || deserializer->deserialize_bool();
    const bool append = revision >= 3 && deserializer->deserialize_bool();
    const double delay = hasWait ? deserializer->deserialize_d() : 0;
    const auto count = deserializer->deserialize_uint();
    if (!std::isfinite(delay) || delay < 0 || count > 1000000)
        throw std::runtime_error("Invalid animation tween state");
    const auto fields = tweenFields();
    std::vector<Animation> tracks;
    tracks.reserve(count);
    for (uint32 i = 0; i < count; ++i) {
        Animation a;
        const auto field = deserializer->deserialize_1u();
        const auto easing = deserializer->deserialize_1u();
        a.rotationDirection = deserializer->deserialize_1u();
        const auto flags = deserializer->deserialize_1u();
        readAnimationFlags(a, flags, revision >= 3);
        SnapshotReader in(deserializer);
        a.delaySeconds = revision>=4 ? in.real() : deserializer->deserialize_d();
        a.durationSeconds = revision>=4 ? in.real() : deserializer->deserialize_d();
        a.elapsedSeconds = revision>=4 ? in.real() : deserializer->deserialize_d();
        a.beginVal = revision>=4 ? in.floating() : deserializer->deserialize_f();
        a.deltaVal = revision>=4 ? in.floating() : deserializer->deserialize_f();
        a.targetVal = revision>=4 ? in.floating() : deserializer->deserialize_f();
        a.easing = easingIdToFunc(easing);
        if (field >= fields.size() || !a.easing ||
            a.rotationDirection > rotationDirection_CounterClockwise ||
            !std::isfinite(a.delaySeconds) || a.delaySeconds < 0 ||
            !std::isfinite(a.durationSeconds) || a.durationSeconds < 0 ||
            !std::isfinite(a.elapsedSeconds) || a.elapsedSeconds < 0 || a.elapsedSeconds > a.durationSeconds ||
            !std::isfinite(a.beginVal) || !std::isfinite(a.deltaVal) || !std::isfinite(a.targetVal))
            throw std::runtime_error("Invalid animation tween track");
        // This method operates on a mutable AnimatedBase; const pointers share the
        // channel table with the const writer and size query.
        a.value = const_cast<float*>(fields[field]);
        if (a.value) tracks.push_back(a);
    }
    std::array<double,5> credits{};
    if(revision>=6) for(auto& credit:credits) { credit=SnapshotReader(deserializer).real(); if(!std::isfinite(credit) || credit<0) throw std::runtime_error("Invalid collective integration credit"); }
    if (revision >= 5) deserializeScripts(deserializer); else mScripts.reset();
    mTroupeRateTime=credits;
    mDelaySeconds = delay; mAppendAnimation = append; mWaitPending = hasWait && !append; mAnimationOperation = 1;
    mAnimations = std::move(tracks);
}

void AnimatedBase::validateDuration(double seconds) {
    if (!std::isfinite(seconds) || seconds < 0)
        throw std::invalid_argument("Animation duration must be finite nonnegative seconds");
}

void AnimatedBase::validateImmediateOperation() const {
    validateScriptEdit();
    if (mWaitPending || mAppendAnimation)
        throw std::invalid_argument("Only operations with a duration can be part of a timed animation sequence.");
}
void AnimatedBase::validateAnimationDuration(double seconds) const {
    validateScriptEdit();
    validateDuration(seconds);
    if (seconds == 0.0) validateImmediateOperation();
}

AnimatedBase& AnimatedBase::andThen() {
    if (scriptAndThen()) return *this;
    mDelaySeconds = 0;
    for (const auto& a : mAnimations)
        if (a.operation == mAnimationOperation)
            mDelaySeconds = std::max(mDelaySeconds, a.delaySeconds + a.durationSeconds - a.elapsedSeconds);
    mAppendAnimation = true; mWaitPending = false;
    return *this;
}

void AnimatedBase::setRelativeAnimationTargets(uint8 mode) {
    for (auto& a : mAnimations) if (a.operation == mAnimationOperation) a.targetMode = mode;
}

float* AnimatedBase::competingAnimationChannel(float* value) {
    float* pairs[][2] = {{&mLocation.x,&mDeltaXPerMs}, {&mLocation.y,&mDeltaYPerMs},
        {&mFacing,&mDeltaFacingPerMs}, {&mWidth,&mDeltaWidthPerMs}, {&mHeight,&mDeltaHeightPerMs}};
    for (auto& pair : pairs) {
        if (value == pair[0]) { *pair[1] = 0; return pair[1]; }
        if (value == pair[1]) return pair[0];
    }
    return nullptr;
}

uint8 AnimatedBase::animationFlags(const Animation& a) const {
    return (a.relativeRotation ? 1 : 0) | (a.resolveRotation ? 2 : 0) |
        (a.chained ? 4 : 0) | (a.targetMode << 3) | (a.operation == mAnimationOperation ? 32 : 0) | (a.completion << 6);
}
void AnimatedBase::readAnimationFlags(Animation& a, uint8 flags, bool sequencing) {
    if ((!sequencing && flags > 3) || ((flags >> 3) & 3) == 3)
        throw std::runtime_error("Invalid animation route flags");
    a.relativeRotation = (flags & 1) != 0; a.resolveRotation = (flags & 2) != 0;
    a.chained = (flags & 4) != 0; a.targetMode = (flags >> 3) & 3;
    a.operation = (flags & 32) ? 1 : 0; a.completion = flags >> 6;
}

void AnimatedBase::cancelAnimation(float* value) {
    animationChannelAcquired(value);
    cancelScriptChannel(value);
    std::erase_if(mAnimations, [value](const Animation& a) { return a.value == value; });
}

void AnimatedBase::scheduleAnimation(float* value, float target, double seconds, EasingFunc easing) {
    Animation a(value, target, easing, mDelaySeconds, seconds);
    a.chained = mAppendAnimation; a.operation = mAnimationOperation;
    prepareAnimation(value);
    if (!mAppendAnimation && seconds == 0 && mDelaySeconds == 0) *value = target;
    else mAnimations.push_back(a);
}

void AnimatedBase::moveToImpl(const Point& loc, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_LocationX,loc.x},{animationChannel_LocationY,loc.y}}, seconds, easing)) return;
    validateProgrammedTransform();
    validateAnimationDuration(seconds);
    if (!std::isfinite(loc.x) || !std::isfinite(loc.y) || !easing)
        throw std::invalid_argument("Movement target and easing must be valid");
    beginAnimationRequest();
    prepareAnimation(&mDeltaXPerMs); prepareAnimation(&mDeltaYPerMs);
    if (!mAppendAnimation) mDeltaXPerMs = mDeltaYPerMs = 0;
    const Point before = mLocation;
    scheduleAnimation(&mLocation.x, loc.x, seconds, easing);
    scheduleAnimation(&mLocation.y, loc.y, seconds, easing);
    finishAnimationRequest();
    if (before != mLocation) locationChanged(mLocation - before);
}


void AnimatedBase::moveByImpl(const Offset& delta, double seconds, EasingFunc easing) {
    validateProgrammedTransform();
    validateAnimationDuration(seconds);
    if (!std::isfinite(delta.x) || !std::isfinite(delta.y) || !easing)
        throw std::invalid_argument("Movement offset and easing must be valid");
    const bool relative = mAppendAnimation;
    const Point before = mLocation;
    beginAnimationRequest();
    if (delta.x != 0) {
        prepareAnimation(&mDeltaXPerMs);
        if (!relative) mDeltaXPerMs = 0;
        scheduleAnimation(&mLocation.x, relative ? delta.x : before.x + delta.x, seconds, easing);
    }
    if (delta.y != 0) {
        prepareAnimation(&mDeltaYPerMs);
        if (!relative) mDeltaYPerMs = 0;
        scheduleAnimation(&mLocation.y, relative ? delta.y : before.y + delta.y, seconds, easing);
    }
    finishAnimationRequest();
    if (before != mLocation) locationChanged(mLocation - before);
}

AnimatedBase& AnimatedBase::setMovement(const Vector& movement) { return setMovement(movement.x, movement.y); }
AnimatedBase& AnimatedBase::setMovement(float x, float y) { return changeMovementTo(x, y, 0, linearTween); }
AnimatedBase& AnimatedBase::setSpin(float rate) { return changeSpinTo(rate, 0, linearTween); }
AnimatedBase& AnimatedBase::setStretching(float x, float y) { return changeStretchingTo(x, y, 0, linearTween); }
AnimatedBase& AnimatedBase::changeMovementBy(const Vector& delta, double seconds, EasingFunc easing) {
    return changeMovementBy(delta.x, delta.y, seconds, easing);
}
AnimatedBase& AnimatedBase::changeMovementBy(float x, float y, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_MovementX,x/1000.f},{animationChannel_MovementY,y/1000.f}}, seconds, easing, animationMode_Add)) return *this;
    const bool relative = mAppendAnimation;
    const Offset rate = getMovement();
    changeMovementTo(relative ? x : rate.x + x, relative ? y : rate.y + y, seconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Add);
    return *this;
}
AnimatedBase& AnimatedBase::changeSpinBy(float delta, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_Spinning,delta/1000.f}}, seconds, easing, animationMode_Add)) return *this;
    const bool relative = mAppendAnimation;
    changeSpinTo(relative ? delta : getSpin() + delta, seconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Add);
    return *this;
}
AnimatedBase& AnimatedBase::changeStretchingBy(float x, float y, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_StretchingWidth,x/1000.f},{animationChannel_StretchingHeight,y/1000.f}}, seconds, easing, animationMode_Add)) return *this;
    const bool relative = mAppendAnimation;
    const Offset rate = getStretching();
    changeStretchingTo(relative ? x : rate.x + x, relative ? y : rate.y + y, seconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Add);
    return *this;
}
AnimatedBase& AnimatedBase::changeScaleBy(float x, float y, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_ScaleX,x},{animationChannel_ScaleY,y}}, seconds, easing, animationMode_Add)) return *this;
    SampledPreparationGuard sampled(*this);
    const bool relative = mAppendAnimation;
    changeScaleTo(relative ? x : mScaleX + x, relative ? y : mScaleY + y, seconds, easing);
    if (relative) setRelativeAnimationTargets(animationMode_Add);
    return *this;
}

AnimatedBase& AnimatedBase::changeMovementTo(const Vector& movement, double seconds, EasingFunc easing) {
    return changeMovementTo(movement.x, movement.y, seconds, easing);
}
AnimatedBase& AnimatedBase::changeMovementTo(float x, float y, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_MovementX,x/1000.f},{animationChannel_MovementY,y/1000.f}}, seconds, easing)) return *this;
    validateProgrammedTransform();
    validateAnimationDuration(seconds);
    if (!std::isfinite(x) || !std::isfinite(y) || !easing)
        throw std::invalid_argument("Movement rate and easing must be valid");
    beginAnimationRequest();
    prepareAnimation(&mLocation.x); prepareAnimation(&mLocation.y);
    scheduleAnimation(&mDeltaXPerMs, x / 1000.0f, seconds, easing);
    scheduleAnimation(&mDeltaYPerMs, y / 1000.0f, seconds, easing);
    finishAnimationRequest();
    return *this;
}
Offset AnimatedBase::getMovement() const { validateScriptRead();
    return Offset(mDeltaXPerMs * 1000.0f, mDeltaYPerMs * 1000.0f);
}

AnimatedBase& AnimatedBase::changeStretchingTo(float x, float y, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_StretchingWidth,x/1000.f},{animationChannel_StretchingHeight,y/1000.f}}, seconds, easing)) return *this;
    validateTransformEdit();
    validateAnimationDuration(seconds);
    if (!std::isfinite(x) || !std::isfinite(y) || !easing)
        throw std::invalid_argument("Stretch rates and easing must be valid");
    beginAnimationRequest();
    prepareAnimation(&mWidth); prepareAnimation(&mHeight);
    scheduleAnimation(&mDeltaWidthPerMs, x / 1000.0f, seconds, easing);
    scheduleAnimation(&mDeltaHeightPerMs, y / 1000.0f, seconds, easing);
    finishAnimationRequest();
    return *this;
}
Offset AnimatedBase::getStretching() const { validateScriptRead();
    return Offset(mDeltaWidthPerMs * 1000.0f, mDeltaHeightPerMs * 1000.0f);
}
AnimatedBase& AnimatedBase::setScale(float x, float y) {
    if (recordScriptAnimation({{animationChannel_ScaleX,x},{animationChannel_ScaleY,y}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
    if (!std::isfinite(x) || !std::isfinite(y))
        throw std::invalid_argument("Scale must be finite");
    cancelAnimation(&mScaleX); cancelAnimation(&mScaleY);
    const Offset before(mScaleX, mScaleY);
    mScaleX = x; mScaleY = y;
    scaleChanged(Offset(mScaleX,mScaleY) - before);
    return *this;
}
AnimatedBase& AnimatedBase::changeScaleTo(float x, float y, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_ScaleX,x},{animationChannel_ScaleY,y}}, seconds, easing)) return *this;
    validateTransformEdit();
    validateAnimationDuration(seconds);
    if (!std::isfinite(x) || !std::isfinite(y) || !easing)
        throw std::invalid_argument("Scale target and easing must be valid");
    beginAnimationRequest();
    const Offset before(mScaleX, mScaleY);
    scheduleAnimation(&mScaleX, x, seconds, easing);
    scheduleAnimation(&mScaleY, y, seconds, easing);
    finishAnimationRequest();
    if (before != Offset(mScaleX,mScaleY)) scaleChanged(Offset(mScaleX,mScaleY) - before);
    return *this;
}
void AnimatedBase::cancelScheduleImpl() {
    cancelScripts();
    mAnimations.clear();
    finishAnimationRequest();
}

void AnimatedBase::resizeToImpl(float width, float height, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_Width,width},{animationChannel_Height,height}}, seconds, easing)) return;
    validateTransformEdit();
    validateAnimationDuration(seconds);
    if (!std::isfinite(width) || !std::isfinite(height) || !easing)
        throw std::invalid_argument("Size target and easing must be valid");
    beginAnimationRequest();
    prepareAnimation(&mDeltaWidthPerMs); prepareAnimation(&mDeltaHeightPerMs);
    if (!mAppendAnimation) mDeltaWidthPerMs = mDeltaHeightPerMs = 0;
    const float beforeW = mWidth, beforeH = mHeight;
    scheduleAnimation(&mWidth, width, seconds, easing);
    scheduleAnimation(&mHeight, height, seconds, easing);
    finishAnimationRequest();
    if (beforeW != mWidth || beforeH != mHeight) sizeChanged(mWidth - beforeW, mHeight - beforeH);
}

AnimatedBase& AnimatedBase::setRotation(float radians) {
    if (recordScriptAnimation({{animationChannel_Facing,radians}}, 0, linearTween)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
    cancelAnimation(&mFacing);
    const float before = mFacing;
    mFacing = radians;
    rotationChanged(radians - before);
    return *this;
}
AnimatedBase& AnimatedBase::changeSpinTo(float radiansPerSecond, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_Spinning,radiansPerSecond/1000.f}}, seconds, easing)) return *this;
    validateProgrammedTransform();
    validateAnimationDuration(seconds);
    if (!std::isfinite(radiansPerSecond) || !easing)
        throw std::invalid_argument("Spin rate and easing must be valid");
    beginAnimationRequest();
    prepareAnimation(&mFacing);
    scheduleAnimation(&mDeltaFacingPerMs, radiansPerSecond / 1000.0f, seconds, easing);
    finishAnimationRequest();
    return *this;
}
float AnimatedBase::getSpin() const { validateScriptRead(); return mDeltaFacingPerMs * 1000.0f; }

double AnimatedBase::rotationTarget(double begin, double target, int direction, bool relative) {
    const double pi = std::numbers::pi, turn = 2 * pi;
    if (!std::isfinite(target) || direction < rotationDirection_AsSpecified ||
        direction > rotationDirection_CounterClockwise)
        throw std::invalid_argument("Invalid rotation target or integer direction");
    if (relative) {
        if (direction == rotationDirection_Clockwise) target = std::abs(target);
        if (direction == rotationDirection_CounterClockwise) target = -std::abs(target);
        // A relative amount is deliberate angular travel, including full turns.
        return begin + target;
    }
    if (direction == rotationDirection_AsSpecified) return target;
    double delta = std::fmod(target - begin, turn);
    if (direction == rotationDirection_Clockwise && delta < 0) delta += turn;
    if (direction == rotationDirection_CounterClockwise && delta > 0) delta -= turn;
    if (direction == rotationDirection_Shortest) {
        // Targets are floats: both float representations of a half turn tie.
        if (std::abs(std::abs(delta) - pi) <= 2 * std::numeric_limits<float>::epsilon() * pi)
            delta = pi;
        if (delta > pi) delta -= turn;
        if (delta <= -pi) delta += turn;
    }
    return begin + delta;
}

void AnimatedBase::rotateToImpl(float radians, double seconds, EasingFunc easing, int direction) {
    if (recordScriptAnimation({{animationChannel_Facing,radians}}, seconds, easing, animationMode_Assign, direction)) return;
    validateProgrammedTransform();
    validateAnimationDuration(seconds);
    rotationTarget(mFacing, radians, direction, false); // validate before mutation
    beginAnimationRequest();
    Animation a(&mFacing, radians, easing, mDelaySeconds, seconds);
    a.chained = mAppendAnimation; a.operation = mAnimationOperation;
    a.rotationDirection = direction; a.resolveRotation = true;
    prepareAnimation(&mFacing); prepareAnimation(&mDeltaFacingPerMs);
    if (!mAppendAnimation) mDeltaFacingPerMs = 0;
    if (!mAppendAnimation && seconds == 0 && mDelaySeconds == 0) setRotation(radians);
    else mAnimations.push_back(a);
    finishAnimationRequest();
}

AnimatedBase& AnimatedBase::rotateBy(float radians, double seconds, EasingFunc easing, int direction) {
    if (recordScriptAnimation({{animationChannel_Facing,radians}}, seconds, easing, animationMode_Add, direction)) return *this;
    validateProgrammedTransform();
    validateAnimationDuration(seconds);
    const double target = rotationTarget(mFacing, radians, direction, true);
    beginAnimationRequest();
    Animation a(&mFacing, radians, easing, mDelaySeconds, seconds);
    a.chained = mAppendAnimation; a.operation = mAnimationOperation;
    a.rotationDirection = direction; a.relativeRotation = true; a.resolveRotation = true;
    prepareAnimation(&mFacing); prepareAnimation(&mDeltaFacingPerMs);
    if (!mAppendAnimation) mDeltaFacingPerMs = 0;
    if (!mAppendAnimation && seconds == 0 && mDelaySeconds == 0) setRotation(static_cast<float>(target));
    else mAnimations.push_back(a);
    finishAnimationRequest();
    return *this;
}

AnimatedBase& AnimatedBase::changeCenterOffsetTo(const Offset& offset, double seconds, EasingFunc easing) {
    if (recordScriptAnimation({{animationChannel_CenterOffsetX,offset.x},{animationChannel_CenterOffsetY,offset.y}}, seconds, easing)) return *this;
    validateTransformEdit();
    validateAnimationDuration(seconds);
    if (!std::isfinite(offset.x) || !std::isfinite(offset.y) || !easing)
        throw std::invalid_argument("Center target and easing must be valid");
    beginAnimationRequest();
    const Offset before = mCenterOffset;
    scheduleAnimation(&mCenterOffset.x, offset.x, seconds, easing);
    scheduleAnimation(&mCenterOffset.y, offset.y, seconds, easing);
    finishAnimationRequest();
    if (before != mCenterOffset) centerChanged(mCenterOffset - before);
    return *this;
}

// Deterministic antiderivative: fixed subdivisions of normalized clip time,
// 8-point Gauss-Legendre quadrature in each subdivision. Subtracting cumulative
// integrals makes timestep partitioning independent of the caller's tick size.
double AnimatedBase::integrateAnimation(const Animation& a, double endSeconds) {
    if (a.durationSeconds == 0 || endSeconds <= 0) return 0;
    static const double x[] = {.1834346424956498,.5255324099163290,.7966664774136267,.9602898564975363};
    static const double w[] = {.3626837833783620,.3137066458778873,.2223810344533745,.1012285362903763};
    const double end = std::min(endSeconds / a.durationSeconds, 1.0);
    double sum = 0;
    for (int bin = 0; bin < 32 && bin / 32.0 < end; ++bin) {
        const double left = bin / 32.0, right = std::min((bin + 1) / 32.0, end);
        const double mid = (left + right) / 2, half = (right - left) / 2;
        for (int i = 0; i < 4; ++i)
            sum += half * w[i] * (a.easing((mid - half*x[i])*a.durationSeconds,a.beginVal,a.deltaVal,a.durationSeconds) +
                a.easing((mid + half*x[i])*a.durationSeconds,a.beginVal,a.deltaVal,a.durationSeconds));
    }
    return sum * a.durationSeconds;
}


// flipping
AnimatedBase&
AnimatedBase::setFlipX(bool flip) {
    if (recordScriptFlip(animationFlipAxis_X,flip)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
	if (mFlipX == flip) return *this;
	mFlipX = flip;
	try { flipChanged(true, false); }
    catch (...) { mFlipX = !flip; throw; }
	// flip the center offset too
	mCenterOffset.x = -mCenterOffset.x;
	centerChanged(mCenterOffset);
	return *this;
}

AnimatedBase&
AnimatedBase::setFlipY(bool flip) {
    if (recordScriptFlip(animationFlipAxis_Y,flip)) return *this;
    validateImmediateOperation();
    validateTransformEdit();
	if (mFlipY == flip) return *this;
	mFlipY = flip;
	try { flipChanged(false, true); }
    catch (...) { mFlipY = !flip; throw; }
	// flip the center offset too
	mCenterOffset.y = -mCenterOffset.y;
	centerChanged(mCenterOffset);
	return *this;
}

// objects that will be called to help with animation of this object
// the animation helper(s) will be called in order they were added
// after all other animation (from constant motion, change over time with easing,
// and programmed rates) has been calculated
void
AnimatedBase::addAnimationHelperImpl(IAnimationHelper* helper) {
    validateScriptControl();
    validateImmediateOperation();
    if (!helper) throw std::invalid_argument("Animation helper must not be null");
    for (const auto& entry : mHelpers) if (entry->helper == helper) return;
    mHelpers.push_back(std::make_shared<HelperRegistration>(helper));
    return;
}

void
AnimatedBase::removeAnimationHelperImpl(IAnimationHelper* helper) {
    validateScriptControl();
    validateImmediateOperation();
    for (auto it = mHelpers.begin(); it != mHelpers.end(); ++it) {
        if ((*it)->helper == helper) {
            (*it)->active = false;
            mHelpers.erase(it);
            return;
        }
    }
    return;
}

void
AnimatedBase::clearAnimationHelpersImpl() {
    validateScriptControl();
    validateImmediateOperation();
    // In-flight snapshots keep owned helpers alive until the callback returns.
    for (const auto& entry : mHelpers) entry->active = false;
    mHelpers.clear();
    return;
}

// called by subclasses to do the actual work of animating
// returns true if anything changed
bool
AnimatedBase::animate(double deltaSeconds) {
    if (!std::isfinite(deltaSeconds) || deltaSeconds < 0) {
        throw std::invalid_argument("animate requires finite nonnegative seconds");
    }
    if (mAnimating) throw std::logic_error("Animated update cannot be reentered");
    struct AnimationUpdateGuard { bool& flag; ~AnimationUpdateGuard() { flag=false; } } animationUpdateGuard{mAnimating};
    // Stored programmed rates are per millisecond; all public timing is seconds.

	// inside the animate call
	mAnimating = true;	

	// save current info
	PointT<float> savedLocation = mLocation;
	float savedFacing = mFacing;
	float savedHeight = mHeight;
	float savedWidth = mWidth;
    const Offset savedScale(mScaleX,mScaleY);
	PointT<float> savedCenterOffset = mCenterOffset;

    bool changes = false;
    mScriptFrameRates={mDeltaXPerMs,mDeltaYPerMs,mDeltaFacingPerMs,mDeltaWidthPerMs,mDeltaHeightPerMs};
    if (!mSchedulePaused) changes=advanceScripts(0,true);
    mScriptFrameRates={mDeltaXPerMs,mDeltaYPerMs,mDeltaFacingPerMs,mDeltaWidthPerMs,mDeltaHeightPerMs};
    double remaining = deltaSeconds;
    for (;;) {
        if (!mSchedulePaused) changes=advanceScripts(0) || changes;
        std::vector<Animation> completed;
        if (!mSchedulePaused) {
            // Publish instantaneous predecessors before a successor samples them.
            for (size_t i=0; i<mAnimations.size();) {
                if (mAnimations[i].delaySeconds > 0) { ++i; continue; }
                if (mAnimations[i].chained) {
                    float* value = mAnimations[i].value;
                    cancelScriptChannel(value);
                    float* competing = competingAnimationChannel(value);
                    for (size_t j=0; j<i;) {
                        if (mAnimations[j].value == value || mAnimations[j].value == competing ||
                            (mAnimations[j].operation != mAnimations[i].operation && animationChannelsConflict(mAnimations[j].value,value))) {
                            mAnimations.erase(mAnimations.begin()+j); --i;
                        } else ++j;
                    }
                    Animation& a = mAnimations[i];
                    a.chained = false;
                    if (a.targetMode == animationMode_Add) a.targetVal += *a.value;
                    if (a.targetMode == animationMode_Multiply) a.targetVal *= *a.value;
                    a.targetMode = animationMode_Assign;
                }
                Animation& a = mAnimations[i];
                if (a.elapsedSeconds == 0) {
                    animationStarting(a);
                    a.beginVal = *a.value;
                    if (a.resolveRotation) {
                        a.targetVal = static_cast<float>(rotationTarget(a.beginVal,a.targetVal,a.rotationDirection,a.relativeRotation));
                        a.resolveRotation = false;
                    }
                    a.deltaVal = a.targetVal - a.beginVal;
                }
                if (a.durationSeconds == 0) {
                    if (*a.value != a.targetVal) changes = true;
                    *a.value = a.targetVal;
                    completed.push_back(a);
                    mAnimations.erase(mAnimations.begin()+i);
                    animationValuesChanged();
                } else ++i;
            }
        }
        double step = remaining;
        if (!mSchedulePaused) for (const auto& a : mAnimations)
            step = std::min(step, a.delaySeconds > 0 ? a.delaySeconds : a.durationSeconds-a.elapsedSeconds);
        if (!mSchedulePaused) step=std::min(step,scriptNextBoundary());
        mScriptFrameRates={mDeltaXPerMs,mDeltaYPerMs,mDeltaFacingPerMs,mDeltaWidthPerMs,mDeltaHeightPerMs};
        // Troupe rate profiles have already integrated their portion of this
        // owner update. Consume that time once; ordinary rates cover the remainder.
        const auto ordinaryRateTime=[&](unsigned channel) {
            const double covered=std::min(step,mTroupeRateTime[channel]);
            mTroupeRateTime[channel]=std::max(0.0,mTroupeRateTime[channel]-covered);
            return step-covered;
        };
        mLocation.x += mDeltaXPerMs * ordinaryRateTime(0) * 1000;
        mLocation.y += mDeltaYPerMs * ordinaryRateTime(1) * 1000;
        mFacing += mDeltaFacingPerMs * ordinaryRateTime(2) * 1000;
        mWidth += mDeltaWidthPerMs * ordinaryRateTime(3) * 1000;
        mHeight += mDeltaHeightPerMs * ordinaryRateTime(4) * 1000;
        if (!mSchedulePaused) {
            if (mAppendAnimation) mDelaySeconds = std::max(0.0, mDelaySeconds-step);
            for (size_t i=0; i<mAnimations.size();) {
                Animation& a = mAnimations[i];
                if (a.delaySeconds > 0) {
                    a.delaySeconds = std::max(0.0,a.delaySeconds-step);
                    ++i; continue;
                }
                const double before = a.elapsedSeconds;
                a.elapsedSeconds = std::min(a.durationSeconds, before+step);
                float* position = a.value == &mDeltaXPerMs ? &mLocation.x :
                    a.value == &mDeltaYPerMs ? &mLocation.y :
                    a.value == &mDeltaFacingPerMs ? &mFacing :
                    a.value == &mDeltaWidthPerMs ? &mWidth :
                    a.value == &mDeltaHeightPerMs ? &mHeight : nullptr;
                if (position) {
                    const double area = integrateAnimation(a,a.elapsedSeconds) - integrateAnimation(a,before);
                    *position += static_cast<float>((area-step * *a.value)*1000.0);
                }
                const float previous = *a.value;
                const bool complete = a.elapsedSeconds >= a.durationSeconds;
                *a.value = complete ? a.targetVal : a.easing(a.elapsedSeconds,a.beginVal,a.deltaVal,a.durationSeconds);
                changes = changes || *a.value != previous;
                if (complete) { completed.push_back(a); mAnimations.erase(mAnimations.begin()+i); }
                else ++i;
            }
        }
        if (!mSchedulePaused) changes=advanceScripts(step) || changes;
        animationValuesChanged();
        remaining = std::max(0.0,remaining-step);
        for (const auto& a : completed) easingCompleted(a);
        if (remaining == 0) {
            // Sample newly due operations at the exact boundary in this tick too.
            const bool starting = !mSchedulePaused && step > 0 && std::any_of(mAnimations.begin(),mAnimations.end(),
                [](const Animation& a) { return a.delaySeconds == 0 && a.elapsedSeconds == 0; });
            if (!starting && (mSchedulePaused || scriptNextBoundary()!=0)) break;
        }
    }

    // Snapshot registrations, not pointers: removing/re-adding a helper inside
    // a callback creates a new registration that first runs on the next tick.
    const auto helpers = mHelpers;
    for (const auto& entry : helpers) {
        if (!entry->active || entry->running) continue;
        entry->running = true;
        struct ResetRunning { bool& running; ~ResetRunning() { running = false; } } reset{entry->running};
        if (!entry->helper->animate(this, deltaSeconds) && entry->active) {
            entry->active = false;
            std::erase(mHelpers, entry);
        }
    }

	// notify subclasses of changes from inside the animate call
	if (savedLocation != mLocation) {
		locationChanged(mLocation - savedLocation);
		changes = true;
	}
	if (savedFacing != mFacing) {
		rotationChanged(mFacing - savedFacing);
		changes = true;
	}
	if (savedHeight != mHeight || savedWidth != mWidth) {
		sizeChanged(mWidth - savedWidth, mHeight - savedHeight);
		changes = true;
	}
    if (savedScale != Offset(mScaleX,mScaleY)) {
        scaleChanged(Offset(mScaleX,mScaleY) - savedScale);
        changes = true;
    }
	if (savedCenterOffset != mCenterOffset) {
		centerChanged(mCenterOffset - savedCenterOffset);
		changes = true;
	}

	mAnimating = false;
	return changes;
}

void
AnimatedBase::locationChanged(const Offset& delta) {
}
    
void
AnimatedBase::sizeChanged(float deltaW, float deltaH) {
}


void AnimatedBase::scaleChanged(const Offset&) {}

void
AnimatedBase::rotationChanged(float deltaRadians) {
}


void
AnimatedBase::centerChanged(const Offset& delta) {
}


void
AnimatedBase::flipChanged(bool xFlipped, bool yFlipped) {
}


void    
AnimatedBase::easingCompleted(const Animation& a) {
}


AnimatedBase::AnimatedBase() {
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mAnimatedScriptObj);
#endif
	mLocation = Point(0,0);
	mCenterOffset = Point(0,0);
	mHeight = 0;
	mWidth = 0;
	mFacing = 0;
    mScaleX = mScaleY = 1;
    mSchedulePaused = false;
    mFlipX = mFlipY = false;
	mDeltaXPerMs = 0;
	mDeltaYPerMs = 0;
	mDeltaWidthPerMs = 0;
	mDeltaHeightPerMs = 0;
	mDeltaFacingPerMs = 0;
    mDelaySeconds = 0;
    mAnimating = false;
}


std::weak_ptr<AnimatedBase*> AnimatedBase::animationLifetime() const {
    if (!mLifetime || *mLifetime!=this) mLifetime=std::make_shared<AnimatedBase*>(const_cast<AnimatedBase*>(this));
    return mLifetime;
}

AnimatedBase::~AnimatedBase() {
    if (mLifetime && *mLifetime==this) *mLifetime=nullptr;
    mScripts.reset();
    finishAnimationRequest();
	clearAnimationHelpers();
	mAnimations.clear();
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	CleanupAnimatedBaseScriptObject(mAnimatedScriptObj);
#endif
}

/*
C++ Easing Equations based on:

Easing Equations v1.5
May 1, 2003
(c) 2003 Robert Penner, all rights reserved. 
  
TERMS OF USE - EASING EQUATIONS

Open source under the BSD License. 

Copyright © 2001 Robert Penner
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the author nor the names of contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// simple linear tweening - no easing
// t: current time, b: beginning value, c: change in value, d: duration
float linearTween(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	return c*t/d + b;
};


 ///////////// QUADRATIC EASING: t^2 ///////////////////

// quadratic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d are floating-point seconds
float easeInQuad(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	return c*t*t + b;
};

// quadratic easing out - decelerating to zero velocity
float easeOutQuad(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	return -c *t*(t-2) + b;
};

// quadratic easing in/out - acceleration until halfway, then deceleration
float easeInOutQuad(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
    float d = (float)ud;
	float t = (float)ut / (d/2.0f);
    if (t < 1) return c/2.0f*t*t + b;
    t--;
    return -c/2.0f * (t*(t-2.0f) - 1.0f) + b;
};


 ///////////// CUBIC EASING: t^3 ///////////////////////

// cubic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d are floating-point seconds
float easeInCubic(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	return c*t*t*t + b;
};

// cubic easing out - decelerating to zero velocity
float easeOutCubic(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
    float d = (float)ud;
	float t = ((float)ut / d) - 1.0f;
	return c*(t*t*t + 1.0f) + b;
};

// cubic easing in/out - acceleration until halfway, then deceleration
float easeInOutCubic(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / (d/2.0f);
	if (t < 1.0f) return c/2.0f*t*t*t + b;
	t -= 2.0f;
	return c/2.0f* (t*t*t + 2.0f) + b;
};


 ///////////// QUARTIC EASING: t^4 /////////////////////

// quartic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d are floating-point seconds
float easeInQuart(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	return c*t*t*t*t + b;
};

// quartic easing out - decelerating to zero velocity
float easeOutQuart(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = ((float)ut / d) - 1.0f;
	return -c * (t*t*t*t - 1.0f) + b;
};

// quartic easing in/out - acceleration until halfway, then deceleration
float easeInOutQuart(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / (d/2.0f);
	if (t < 1.0f) return c/2.0f*t*t*t*t + b;
	t -= 2.0f;
	return -c/2.0f * (t*t*t*t - 2.0f) + b;
};


 ///////////// QUINTIC EASING: t^5  ////////////////////

// quintic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d are floating-point seconds
float easeInQuint(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	return c*t*t*t*t*t + b;
};

// quintic easing out - decelerating to zero velocity
float easeOutQuint(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = ((float)ut / d) - 1.0f;
	return c*(t*t*t*t*t + 1.0f) + b;
};

// quintic easing in/out - acceleration until halfway, then deceleration
float easeInOutQuint(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / (d/2.0f);
	if (t < 1.0f) return c/2.0f*t*t*t*t*t + b;
	t -= 2.0f;
	return c/2.0f*(t*t*t*t*t + 2.0f) + b;
};



 ///////////// SINUSOIDAL EASING: sin(t) ///////////////

// sinusoidal easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
float easeInSine(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	return -c * cos(t/d * (std::numbers::pi_v<float> / 2)) + c + b;
};

// sinusoidal easing out - decelerating to zero velocity
float easeOutSine(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	return c * sin(t/d * (std::numbers::pi_v<float> / 2)) + b;
};

// sinusoidal easing in/out - accelerating until halfway, then decelerating
float easeInOutSine(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	return -c/2.0f * (cos(std::numbers::pi_v<float>*t/d) - 1) + b;
};


 ///////////// EXPONENTIAL EASING: 2^t /////////////////

// exponential easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
float easeInExpo(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	return (ut==0) ? b : c * pow(2.0f, 10.0f * (t/d - 1.0f)) + b;
};

// exponential easing out - decelerating to zero velocity
float easeOutExpo(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	return (ut==d) ? b+c : c * (-pow(2.0f, -10.0f * t/d) + 1.0f) + b;
};

// exponential easing in/out - accelerating until halfway, then decelerating
float easeInOutExpo(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	if (ut==0) return b;
	if (ut==ud) return b+c;
	t/=(d/2.0f);
	if (t < 1.0f) return c/2.0f * pow(2.0f, 10.0f * (t - 1.0f)) + b;
	return c/2.0f * (-pow(2.0f, -10.0f * --t) + 2.0f) + b;
};


 /////////// CIRCULAR EASING: sqrt(1-t^2) //////////////

// circular easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
float easeInCirc(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	return -c * (sqrt(1.0f - t*t) - 1.0f) + b;
};

// circular easing out - decelerating to zero velocity
float easeOutCirc(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = ((float)ut / d) - 1.0f;
	return c * sqrt(1.0f - t*t) + b;
};

// circular easing in/out - acceleration until halfway, then deceleration
float easeInOutCirc(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / (d/2.0f);
	if (t < 1.0f) return -c/2.0f * (sqrt(1.0f - t*t) - 1.0f) + b;
	t -= 2.0f;
	return c/2.0f * (sqrt(1.0f - t*t) + 1.0f) + b;
};


//  /////////// ELASTIC EASING: exponentially decaying sine wave  //////////////
// 
// // t: current time, b: beginning value, c: change in value, d: duration, a: amplitude (optional), p: period (optional)
// // t and d are floating-point seconds
// 
// float easeInElastic = function (t, b, c, d, a) {
// 	if (t==0) return b;  if ((t/=d)==1) return b+c;  float p=d*.3;
// 	if (a < Math.abs(c)) { a=c; var s=p/4; }
// 	else var s = p/(2 * Math.PI) * Math.asin (c/a);
// 	return -(a*Math.pow(2,10*(t-=1)) * Math.sin( (t*d-s)*(2 * Math.PI)/p )) + b;
// };
// 
// float easeOutElastic = function (t, b, c, d, a) {
// 	if (t==0) return b;  if ((t/=d)==1) return b+c;  float p=d*.3;
// 	if (a < Math.abs(c)) { a=c; var s=p/4; }
// 	else var s = p/(2 * Math.PI) * Math.asin (c/a);
// 	return a*Math.pow(2,-10*t) * Math.sin( (t*d-s)*(2 * Math.PI)/p ) + c + b;
// };
// 
// float easeInOutElastic = function (t, b, c, d, a) {
// 	if (t==0) return b;  if ((t/=d/2)==2) return b+c;  float p=d*(.3*1.5);
// 	if (a < Math.abs(c)) { a=c; var s=p/4; }
// 	else var s = p/(2 * Math.PI) * Math.asin (c/a);
// 	if (t < 1) return -.5*(a*Math.pow(2,10*(t-=1)) * Math.sin( (t*d-s)*(2 * Math.PI)/p )) + b;
// 	return a*Math.pow(2,-10*(t-=1)) * Math.sin( (t*d-s)*(2 * Math.PI)/p )*.5 + c + b;
// };
// 

 /////////// BACK EASING: overshooting cubic easing: (s+1)*t^3 - s*t^2  //////////////

// back easing in - backtracking slightly, then reversing direction and moving to target
// t: current time, b: beginning value, c: change in value, d: duration, s: overshoot amount (optional)
// t and d are floating-point seconds
// s controls the amount of overshoot: higher s means greater overshoot
// s has a default value of 1.70158, which produces an overshoot of 10 percent
// s==0 produces cubic easing with no overshoot
float easeInBack(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	float s = 1.70158f; 
	return c*t*t*((s+1.0f)*t - s) + b;
};

// back easing out - moving towards target, overshooting it slightly, then reversing and coming back to target
float easeOutBack(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = ((float)ut / d) -1.0f;
	float s = 1.70158f;
	return c*(t*t*((s+1.0f)*t + s) + 1.0f) + b;
};

// back easing in/out - backtracking slightly, then reversing direction and moving to target,
// then overshooting target, reversing, and finally coming back to target
float easeInOutBack(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / (d/2.0f);
	float s = 1.70158f * 1.525f; 
	if (t < 1.0f) { 
//		s*=1.525f;
		return c/2.0f*(t*t*((s+1.0f)*t - s)) + b;
	}
	t -= 2.0f;
//	s*=1.525f;
	return c/2.0f*(t*t*((s+1.0f)*t + s) + 2.0f) + b;
};

 /////////// BOUNCE EASING: exponentially decaying parabolic bounce  //////////////

// bounce easing in
// t: current time, b: beginning value, c: change in position, d: duration
float easeInBounce(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	return c - easeOutBounce (d-t, 0.0f, c, d) + b;
};

// bounce easing out
float easeOutBounce(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float d = (float)ud;
	float t = (float)ut / d;
	if (t < (0.36363636f)) {
		return c*(7.5625f*t*t) + b;
	} else if (t < 0.72727272f) {
		t-=0.54545454f;
		return c*(7.5625f*t*t + 0.75f) + b;
	} else if (t < 0.90909090f) {
		t-=0.81818181f;
		return c*(7.5625f*t*t + 0.9375f) + b;
	} else {
		t-=0.95454545f;
		return c*(7.5625f*t*t + 0.984375f) + b;
	}
};

// bounce easing in/out
float easeInOutBounce(double ut, float b, float c, double ud) {
    if (ud <= 0) return b + c;
	float t = (float)ut;
	float d = (float)ud;
	if (t < d/2) return easeInBounce (t*2.0f, 0.0f, c, d) * 0.5f + b;
	return easeOutBounce (t*2.0f-d, 0.0f, c, d) * 0.5f + c*0.5f + b;
};

EasingFunc gEasingFunctions[NUM_EASING_FUNCTIONS] = {
	BUILTIN_EASING_FUNC_LIST,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

int gNumCustomEasings = 0;

uint8 easingFuncToId(EasingFunc func) {
	for (int i = 0; i < (NUM_BUILTIN_EASINGS + gNumCustomEasings); i++) {
		if (gEasingFunctions[i] == func) {
			return i;
		}
	}
	if (gNumCustomEasings < MAX_CUSTOM_EASINGS) {
		gEasingFunctions[NUM_BUILTIN_EASINGS + gNumCustomEasings] = func;
		gNumCustomEasings++;
		return NUM_BUILTIN_EASINGS + gNumCustomEasings - 1;
	}
	return 0; // after too many we just use linear tween
}

EasingFunc easingIdToFunc(uint8 id) {
	if (id >= NUM_EASING_FUNCTIONS) {
		return 0;
	} else {
		return gEasingFunctions[id];
	}
}


} // end namespace pdg

#include "animated-script.inc"
