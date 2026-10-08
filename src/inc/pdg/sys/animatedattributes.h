#ifndef PDG_ANIMATED_ATTRIBUTES_H_INCLUDED
#define PDG_ANIMATED_ATTRIBUTES_H_INCLUDED

#include "pdg/sys/animated.h"
#include "pdg/sys/attributes.h"
#include <initializer_list>
#include <map>

namespace pdg {

/** AnimatedBase drawing attributes. Durations, waits and animate() steps are seconds.
 * @ingroup Animation Graphics
 * Each object starts with a logical 1 x 1 size: width/height give the reference size,
 * independent of drawing geometry. The matrix is translation * pivot * rotation
 * * shear * size * scale * inverse-pivot. Independent scale defaults to (1,1). Attributes transform operations decompose back
 * into the same AnimatedBase state. Copying to Attributes captures a sample only.
 * Inherited AnimatedBase position, rotation, size and scale methods update this matrix.
 * No physics, geometry morphing or texture crossfades. ElementRef::setLiveAttributes()
 * follows values without automatically advancing this object.
 */
class AnimatedAttributesBase : public AnimatedBase, public Attributes {
public:
    using Attributes::operator=;
    AnimatedAttributesBase();
    explicit AnimatedAttributesBase(const Attributes& attributes);
    AnimatedAttributesBase(const AnimatedAttributesBase&) = delete;
    AnimatedAttributesBase& operator=(const AnimatedAttributesBase&) = delete;
    ~AnimatedAttributesBase() override = default;
    /// @cond INTERNAL
    void setDrawingLayout(bool enabled) { mDrawingLayoutSample = enabled; }
    /// @endcond
    bool animate(double seconds) override;
    AnimatedAttributesBase& changeLineColor(const Color& target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeLineThickness(float target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeLineOpacity(float target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeFillColor(const Color& target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeFillOpacity(float target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeRoundedCorners(float target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeTextSize(float target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeSubsection(const Rect& target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changePolarOffset(const Offset& target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeLightOffset(const Offset& target, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeAmbientLight(const Color& target, double seconds, EasingFunc easing = linearTween);

    AnimatedAttributesBase& changeFillGradient(const Point& start, const Color& startColor,
        const Point& end, const Color& endColor, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeFillRadialGradient(const Point& center, const Color& centerColor,
        float radius, const Color& endColor, double seconds, EasingFunc easing = linearTween);
    AnimatedAttributesBase& changeSphereRotation(float radians, double seconds,
        EasingFunc easing = linearTween, int direction = rotationDirection_AsSpecified);
    /// Inclusive integer sequence, equal time per frame before easing. No looping.
    AnimatedAttributesBase& changeFrames(int first, int last, double seconds, EasingFunc easing = linearTween);
    /// Postmultiply the current matrix by a shear, then interpolate affine coefficients.
    AnimatedAttributesBase& changeSkew(float x, float y, double seconds, EasingFunc easing = linearTween);
    /// Replace the matrix via linear coefficient interpolation (may pass through singular matrices).
    /// Use rotateBy()/rotateTo() for angular paths and direction control.
    AnimatedAttributesBase& changeTransform(const glm::mat3& target, double seconds, EasingFunc easing = linearTween);
    const glm::mat3& getTransform() const override;

protected:
    void assignAttributes(const Attributes& attributes) override;
    void setTransformImpl(const glm::mat3& matrix) override;
    void cancelScheduleImpl() override;
    Attributes& composeTransform(const glm::mat3& matrix, TransformOperation operation) override;
    void validateAttributeEdit() const override { validateImmediateOperation(); }
    void attributeChanging(AttributeChannel channel) override;
    void animationValuesChanged() override;
    std::vector<const float*> tweenFields() const override;
    void cancelAnimation(float* value) override;
    bool animationChannelsConflict(float* a, float* b) const override;
    void animationStarting(Animation& a) override;
    void locationChanged(const Offset&) override;
    void sizeChanged(float, float) override;
    void scaleChanged(const Offset&) override;
    void rotationChanged(float) override;
    void centerChanged(const Offset&) override;
    void flipChanged(bool, bool) override;

private:
    struct Value { float* field; float target; };
    void tween(std::initializer_list<Value> values, double seconds, EasingFunc easing, bool replacesFill = false);
    void switchFill(GradientType mode, double delay, bool chained);
    bool isMatrixField(const float* value) const;
    bool isComponentField(const float* value) const;
    bool isFillField(const float* value) const;
    void discardUnusedStarts();
    struct AttributeStart {
        enum Kind { FillMode, Frames, Matrix, Skew } kind;
        int first = 0, last = 0;
        glm::mat3 matrix = glm::mat3(1);
        explicit AttributeStart(Kind k) : kind(k) {}
    };
    std::map<uint64, AttributeStart> mAttributeStarts;
    void updateTransform();
    void adoptTransform(const glm::mat3& matrix);
    void cancelMatrixAnimation();
    void cancelTransformAnimation();
    void validateTransformSize(const glm::mat3& matrix) const;
    static void validateMatrix(const glm::mat3& matrix);
    // Unit direction of the second matrix column in the rotated coordinate frame.
    bool mDrawingLayoutSample = false;
    mutable glm::mat3 mLayoutSample = glm::mat3(1);
    float mShear, mYAxis;
    glm::mat3 mMatrixSample;
    bool mMatrixActive;
    float mFillSwitch;
    float mFrameProgress;
    int mFirstFrame, mLastFrame;
    bool mFramesActive;
};
/** Typed appearance and transform animation.
 * @ingroup Animation Graphics
 * AnimatedAttributes<> is a standalone style; derive custom owners from
 * AnimatedAttributes<Owner>. All fluent methods preserve the chosen owner type.
 * Copying to Attributes captures the current sample, not a live animation.
 */
template<class T = void>
class AnimatedAttributes : public Animated<std::conditional_t<std::is_void_v<T>, AnimatedAttributes<T>, T>, AnimatedAttributesBase> {
    using Parent = Animated<std::conditional_t<std::is_void_v<T>, AnimatedAttributes<T>, T>, AnimatedAttributesBase>;
public:
    using Self = typename Parent::Self;
    /// @copydoc AnimatedAttributesBase::AnimatedAttributesBase()
    AnimatedAttributes() requires std::is_void_v<T> = default;
    /// @copydoc AnimatedAttributesBase::AnimatedAttributesBase(const Attributes&)
    explicit AnimatedAttributes(const Attributes& attributes) requires std::is_void_v<T> { this->assignAttributes(attributes); }
protected:
    AnimatedAttributes() requires (!std::is_void_v<T>) = default;
    explicit AnimatedAttributes(const Attributes& attributes) requires (!std::is_void_v<T>) { this->assignAttributes(attributes); }
public:
    AnimatedAttributes(const AnimatedAttributes&) = delete;
    AnimatedAttributes& operator=(const AnimatedAttributes&) = delete;
    /** Replace attributes and the matrix with a captured sample, clearing scheduled work.
     * @param attributes The source sample; animation tracks are not copied.
     * @return The selected owner, for chaining.
     */
    Self& operator=(const Attributes& attributes) { this->assignAttributes(attributes); return static_cast<Self&>(*this); }
    /// @copydoc AnimatedAttributesBase::changeLineColor(const Color&, double, EasingFunc)
    Self& changeLineColor(const Color& target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeLineColor(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeLineThickness(float, double, EasingFunc)
    Self& changeLineThickness(float target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeLineThickness(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeLineOpacity(float, double, EasingFunc)
    Self& changeLineOpacity(float target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeLineOpacity(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeFillColor(const Color&, double, EasingFunc)
    Self& changeFillColor(const Color& target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeFillColor(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeFillOpacity(float, double, EasingFunc)
    Self& changeFillOpacity(float target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeFillOpacity(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeRoundedCorners(float, double, EasingFunc)
    Self& changeRoundedCorners(float target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeRoundedCorners(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeTextSize(float, double, EasingFunc)
    Self& changeTextSize(float target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeTextSize(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeSubsection(const Rect&, double, EasingFunc)
    Self& changeSubsection(const Rect& target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeSubsection(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changePolarOffset(const Offset&, double, EasingFunc)
    Self& changePolarOffset(const Offset& target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changePolarOffset(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeLightOffset(const Offset&, double, EasingFunc)
    Self& changeLightOffset(const Offset& target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeLightOffset(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeAmbientLight(const Color&, double, EasingFunc)
    Self& changeAmbientLight(const Color& target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeAmbientLight(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeFillGradient(const Point&, const Color&, const Point&, const Color&, double, EasingFunc)
    Self& changeFillGradient(const Point& start, const Color& startColor, const Point& end, const Color& endColor, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeFillGradient(start, startColor, end, endColor, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeFillRadialGradient(const Point&, const Color&, float, const Color&, double, EasingFunc)
    Self& changeFillRadialGradient(const Point& center, const Color& centerColor, float radius, const Color& endColor, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeFillRadialGradient(center, centerColor, radius, endColor, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeSphereRotation(float, double, EasingFunc, int)
    Self& changeSphereRotation(float radians, double seconds, EasingFunc easing = linearTween, int direction = rotationDirection_AsSpecified) {
        AnimatedAttributesBase::changeSphereRotation(radians, seconds, easing, direction);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeFrames(int, int, double, EasingFunc)
    Self& changeFrames(int first, int last, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeFrames(first, last, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeSkew(float, float, double, EasingFunc)
    Self& changeSkew(float x, float y, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeSkew(x, y, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc AnimatedAttributesBase::changeTransform(const glm::mat3&, double, EasingFunc)
    Self& changeTransform(const glm::mat3& target, double seconds, EasingFunc easing = linearTween) {
        AnimatedAttributesBase::changeTransform(target, seconds, easing);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::lineColor(const Color&)
    Self& lineColor(const Color& color) {
        Attributes::lineColor(color);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::lineThickness(float)
    Self& lineThickness(float thickness) {
        Attributes::lineThickness(thickness);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::lineOpacity(float)
    Self& lineOpacity(float opacity) {
        Attributes::lineOpacity(opacity);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::lineStyle(LineStyle)
    Self& lineStyle(LineStyle style) {
        Attributes::lineStyle(style);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::fillColor(const Color&)
    Self& fillColor(const Color& color) {
        Attributes::fillColor(color);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::fillOpacity(float)
    Self& fillOpacity(float opacity) {
        Attributes::fillOpacity(opacity);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::fillGradient(const Point&, const Color&, const Point&, const Color&)
    Self& fillGradient(const Point& start, const Color& startColor, const Point& end, const Color& endColor) {
        Attributes::fillGradient(start, startColor, end, endColor);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::fillRadialGradient(const Point&, const Color&, float, const Color&)
    Self& fillRadialGradient(const Point& center, const Color& centerColor, float radius, const Color& endColor) {
        Attributes::fillRadialGradient(center, centerColor, radius, endColor);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::texture(Image*)
    Self& texture(Image* texture) {
        Attributes::texture(texture);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::fitType(FitType)
    Self& fitType(FitType fit) {
        Attributes::fitType(fit);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::clipOverflow(bool)
    Self& clipOverflow(bool clip) {
        Attributes::clipOverflow(clip);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::roundedCorners(float)
    Self& roundedCorners(float radius) {
        Attributes::roundedCorners(radius);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::translation(const Offset&)
    Self& translation(const Offset& offset) {
        Attributes::translation(offset);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::rotation(float, const Point&)
    Self& rotation(float radians, const Point& center = Point(0, 0)) {
        Attributes::rotation(radians, center);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::scale(float, const Point&)
    Self& scale(float factor, const Point& center = Point(0, 0)) {
        Attributes::scale(factor, center);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::scale(float, float, const Point&)
    Self& scale(float xFactor, float yFactor, const Point& center = Point(0, 0)) {
        Attributes::scale(xFactor, yFactor, center);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::skew(float, float, const Point&)
    Self& skew(float xSkew, float ySkew, const Point& center = Point(0, 0)) {
        Attributes::skew(xSkew, ySkew, center);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::transform(const glm::mat3&)
    Self& transform(const glm::mat3& matrix) {
        Attributes::transform(matrix);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::setTransform(const glm::mat3&)
    Self& setTransform(const glm::mat3& matrix) {
        Attributes::setTransform(matrix);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::blendMode(BlendMode)
    Self& blendMode(BlendMode mode) {
        Attributes::blendMode(mode);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::textSize(float)
    Self& textSize(float size) {
        Attributes::textSize(size);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::textStyle(uint32)
    Self& textStyle(uint32 style) {
        Attributes::textStyle(style);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::font(Font*)
    Self& font(Font* font) {
        Attributes::font(font);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::frame(int)
    Self& frame(int frame) {
        Attributes::frame(frame);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::subsection(const Rect&)
    Self& subsection(const Rect& section) {
        Attributes::subsection(section);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::sphereRotation(float)
    Self& sphereRotation(float rotation) {
        Attributes::sphereRotation(rotation);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::polarOffset(const Offset&)
    Self& polarOffset(const Offset& offset) {
        Attributes::polarOffset(offset);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::lightOffset(const Offset&)
    Self& lightOffset(const Offset& offset) {
        Attributes::lightOffset(offset);
        return static_cast<Self&>(*this);
    }
    /// @copydoc Attributes::ambientLight(const Color&)
    Self& ambientLight(const Color& color) {
        Attributes::ambientLight(color);
        return static_cast<Self&>(*this);
    }
};
AnimatedAttributes(const Attributes&) -> AnimatedAttributes<>;
} // namespace pdg
#endif
