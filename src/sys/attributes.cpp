// -----------------------------------------------
//  attributes.cpp
//
// Implementation of the Attributes class for the new PDG graphics API
//
// Written by Ed Zavada, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
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

#include "pdg/sys/attributes.h"

namespace pdg {

    // -----------------------------------------------------------------------------------
    // Attributes implementation
    // -----------------------------------------------------------------------------------

    Attributes::Attributes() 
        :
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
          mAttributesScriptObj()
        ,
#endif
          mLineColor(PDG_BLACK_COLOR)
        , mLineThickness(1.0f)
        , mLineOpacity(1.0f)
        , mLineStyle(lineStyle_Auto) // solid for lines, none for fills
        , mFillColor(PDG_TRANSPARENT_COLOR)
        , mFillOpacity(1.0f)
        , mGradientType(gradientType_None)
        , mGradientStart(Point(0, 0))
        , mGradientEnd(Point(0, 0))
        , mGradientStartColor(PDG_BLACK_COLOR)
        , mGradientEndColor(PDG_BLACK_COLOR)
        , mRadialGradientCenter(Point(0, 0))
        , mRadialGradientRadius(0.0f)
        , mRadialGradientCenterColor(PDG_BLACK_COLOR)
        , mRadialGradientEndColor(PDG_BLACK_COLOR)
        , mRoundedCornerRadius(0.0f)
        , mTransform(glm::mat3(1.0f))  // identity matrix
        , mBlendMode(blendMode_Normal)
        , mTextSize(12.0f)
        , mTextStyle(textStyle_Plain)
        , mFont(nullptr)
        , mFrame(0)
        , mFitType(fit_Fill)
        , mClipOverflow(false)
        , mSubsection(Rect(0, 0, 0, 0))
        , mSphereRotation(0.0f)
        , mPolarOffset(Offset(0, 0))
        , mLightOffset(Offset(0, 0))
        , mAmbientLight(Color(0.5f, 0.5f, 0.5f, 1.0f))
        , mTexture(nullptr)
    {
    }

    Attributes::Attributes(const Attributes& other)
        :
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
          mAttributesScriptObj()  // Do not copy the persistent script object.
        ,
#endif
          mRetainedTexture(other.mRetainedTexture)
        , mRetainedFont(other.mRetainedFont)
        , mAppearanceMask(other.mAppearanceMask)
        , mLineColor(other.mLineColor)
        , mLineThickness(other.mLineThickness)
        , mLineOpacity(other.mLineOpacity)
        , mLineStyle(other.mLineStyle)
        , mFillColor(other.mFillColor)
        , mFillOpacity(other.mFillOpacity)
        , mGradientType(other.mGradientType)
        , mGradientStart(other.mGradientStart)
        , mGradientEnd(other.mGradientEnd)
        , mGradientStartColor(other.mGradientStartColor)
        , mGradientEndColor(other.mGradientEndColor)
        , mRadialGradientCenter(other.mRadialGradientCenter)
        , mRadialGradientRadius(other.mRadialGradientRadius)
        , mRadialGradientCenterColor(other.mRadialGradientCenterColor)
        , mRadialGradientEndColor(other.mRadialGradientEndColor)
        , mRoundedCornerRadius(other.mRoundedCornerRadius)
        , mTransform(other.getTransform())
        , mBlendMode(other.mBlendMode)
        , mTextSize(other.mTextSize)
        , mTextStyle(other.mTextStyle)
        , mFont(other.mFont)
        , mFrame(other.mFrame)
        , mFitType(other.mFitType)
        , mClipOverflow(other.mClipOverflow)
        , mSubsection(other.mSubsection)
        , mSphereRotation(other.mSphereRotation)
        , mPolarOffset(other.mPolarOffset)
        , mLightOffset(other.mLightOffset)
        , mAmbientLight(other.mAmbientLight)
        , mTexture(other.mTexture)
    {
    }

    Attributes::~Attributes() {
        if (auto sample = mLiveSample.lock()) {
            sample->frozen = *this;
            sample->source = nullptr;
        }
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#ifndef PDG_NO_GUI
        CleanupAttributesScriptObject(mAttributesScriptObj);
#endif
#endif
    }

    std::shared_ptr<Attributes::LiveSample> Attributes::liveSample() const {
        auto sample = mLiveSample.lock();
        if (!sample) { sample = std::make_shared<LiveSample>(this); mLiveSample = sample; }
        return sample;
    }

    Attributes& Attributes::operator=(const Attributes& other) {
        assignAttributes(other);
        return *this;
    }

    void Attributes::assignAttributes(const Attributes& other) {
        if (this != &other) {
            mAppearanceMask = other.mAppearanceMask;
            mLineColor = other.mLineColor;
            mLineThickness = other.mLineThickness;
            mLineOpacity = other.mLineOpacity;
            mLineStyle = other.mLineStyle;
            mFillColor = other.mFillColor;
            mFillOpacity = other.mFillOpacity;
            mGradientType = other.mGradientType;
            mGradientStart = other.mGradientStart;
            mGradientEnd = other.mGradientEnd;
            mGradientStartColor = other.mGradientStartColor;
            mGradientEndColor = other.mGradientEndColor;
            mRadialGradientCenter = other.mRadialGradientCenter;
            mRadialGradientRadius = other.mRadialGradientRadius;
            mRadialGradientCenterColor = other.mRadialGradientCenterColor;
            mRadialGradientEndColor = other.mRadialGradientEndColor;
            mRoundedCornerRadius = other.mRoundedCornerRadius;
            mTransform = other.getTransform();
            mBlendMode = other.mBlendMode;
            mTextSize = other.mTextSize;
            mTextStyle = other.mTextStyle;
            mRetainedFont = other.mRetainedFont;
            mFont = other.mFont;
            mFrame = other.mFrame;
            mFitType = other.mFitType;
            mClipOverflow = other.mClipOverflow;
            mSubsection = other.mSubsection;
            mSphereRotation = other.mSphereRotation;
            mPolarOffset = other.mPolarOffset;
            mLightOffset = other.mLightOffset;
            mAmbientLight = other.mAmbientLight;
            mRetainedTexture = other.mRetainedTexture;
            mTexture = other.mTexture;
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
            // V8 handles are non-copyable, so we can't copy them in a copy assignment operator
            // The script object will be recreated when needed
            // mAttributesScriptObj = other.mAttributesScriptObj; // This would fail
#endif
        }
    }

    Attributes Attributes::withAppearance(const Attributes& overrides, bool textOnly) const {
        Attributes result(*this);
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << LineColor))) {
            result.mLineColor = overrides.mLineColor;
            result.markAppearance(LineColor);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << LineThickness))) {
            result.mLineThickness = overrides.mLineThickness;
            result.markAppearance(LineThickness);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << LineOpacity))) {
            result.mLineOpacity = overrides.mLineOpacity;
            result.markAppearance(LineOpacity);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << StrokeStyle))) {
            result.mLineStyle = overrides.mLineStyle;
            result.markAppearance(StrokeStyle);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << Fill))) {
            result.mFillColor = overrides.mFillColor;
            result.mGradientType = overrides.mGradientType;
            result.mGradientStart = overrides.mGradientStart;
            result.mGradientEnd = overrides.mGradientEnd;
            result.mGradientStartColor = overrides.mGradientStartColor;
            result.mGradientEndColor = overrides.mGradientEndColor;
            result.mRadialGradientCenter = overrides.mRadialGradientCenter;
            result.mRadialGradientRadius = overrides.mRadialGradientRadius;
            result.mRadialGradientCenterColor = overrides.mRadialGradientCenterColor;
            result.mRadialGradientEndColor = overrides.mRadialGradientEndColor;
            result.markAppearance(Fill);
        }
        if ((overrides.mAppearanceMask & (uint64(1) << FillOpacity))) {
            result.mFillOpacity = overrides.mFillOpacity;
            result.markAppearance(FillOpacity);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << RoundedCorners))) {
            result.mRoundedCornerRadius = overrides.mRoundedCornerRadius;
            result.markAppearance(RoundedCorners);
        }
        if ((overrides.mAppearanceMask & (uint64(1) << TextSize))) {
            result.mTextSize = overrides.mTextSize;
            result.markAppearance(TextSize);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << Frame))) {
            result.mFrame = overrides.mFrame;
            result.markAppearance(Frame);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << Subsection))) {
            result.mSubsection = overrides.mSubsection;
            result.markAppearance(Subsection);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << SphereRotation))) {
            result.mSphereRotation = overrides.mSphereRotation;
            result.markAppearance(SphereRotation);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << PolarOffset))) {
            result.mPolarOffset = overrides.mPolarOffset;
            result.markAppearance(PolarOffset);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << LightOffset))) {
            result.mLightOffset = overrides.mLightOffset;
            result.markAppearance(LightOffset);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << AmbientLight))) {
            result.mAmbientLight = overrides.mAmbientLight;
            result.markAppearance(AmbientLight);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << Texture))) {
            result.mTexture = overrides.mTexture;
            result.mRetainedTexture = overrides.mRetainedTexture;
            result.markAppearance(Texture);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << Fit))) {
            result.mFitType = overrides.mFitType;
            result.markAppearance(Fit);
        }
        if (!textOnly && (overrides.mAppearanceMask & (uint64(1) << Clip))) {
            result.mClipOverflow = overrides.mClipOverflow;
            result.markAppearance(Clip);
        }
        if ((overrides.mAppearanceMask & (uint64(1) << Blend))) {
            result.mBlendMode = overrides.mBlendMode;
            result.markAppearance(Blend);
        }
        if ((overrides.mAppearanceMask & (uint64(1) << TextStyle))) {
            result.mTextStyle = overrides.mTextStyle;
            result.markAppearance(TextStyle);
        }
        if ((overrides.mAppearanceMask & (uint64(1) << Typeface))) {
            result.mFont = overrides.mFont;
            result.mRetainedFont = overrides.mRetainedFont;
            result.markAppearance(Typeface);
        }
        if (!textOnly && result.mLineStyle == lineStyle_Auto &&
            (overrides.mAppearanceMask & ((uint64(1)<<LineColor) | (uint64(1)<<LineThickness) | (uint64(1)<<LineOpacity))))
            result.mLineStyle = lineStyle_Solid;
        return result;
    }

    // Line attributes
    Attributes& Attributes::lineColor(const Color& color) {
        validateAttributeEdit();
        attributeChanging(LineColor);
        mLineColor = color;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_Solid;
        }
        return *this;
    }

    Attributes& Attributes::lineThickness(float thickness) {
        validateAttributeEdit();
        attributeChanging(LineThickness);
        mLineThickness = thickness;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_Solid;
        }
        return *this;
    }

    Attributes& Attributes::lineOpacity(float opacity) {
        validateAttributeEdit();
        attributeChanging(LineOpacity);
        mLineOpacity = opacity;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_Solid;
        }
        return *this;
    }

    Attributes& Attributes::lineStyle(LineStyle style) {
        validateAttributeEdit();
        attributeChanging(StrokeStyle);
        mLineStyle = style;
        return *this;
    }

    // Fill attributes
    Attributes& Attributes::fillColor(const Color& color) {
        validateAttributeEdit();
        attributeChanging(Fill);
        mFillColor = color;
        mGradientType = gradientType_None;  // Clear gradient when setting solid color
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_None;
        }
        return *this;
    }

    Attributes& Attributes::fillOpacity(float opacity) {
        validateAttributeEdit();
        attributeChanging(FillOpacity);
        mFillOpacity = opacity;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_None;
        }
        return *this;
    }

    Attributes& Attributes::fillGradient(const Point& start, const Color& startColor, const Point& end, const Color& endColor) {
        validateAttributeEdit();
        attributeChanging(Fill);
        mGradientType = gradientType_Linear;
        mGradientStart = start;
        mGradientEnd = end;
        mGradientStartColor = startColor;
        mGradientEndColor = endColor;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_None;
        }
        return *this;
    }

    Attributes& Attributes::fillRadialGradient(const Point& center, const Color& centerColor, float radius, const Color& endColor) {
        validateAttributeEdit();
        attributeChanging(Fill);
        mGradientType = gradientType_Radial;
        mRadialGradientCenter = center;
        mRadialGradientRadius = radius;
        mRadialGradientCenterColor = centerColor;
        mRadialGradientEndColor = endColor;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_None;
        }
        return *this;
    }

    // Shape attributes
    Attributes& Attributes::roundedCorners(float radius) {
        validateAttributeEdit();
        attributeChanging(RoundedCorners);
        mRoundedCornerRadius = radius;
        return *this;
    }

    // Transform attributes
    Attributes& Attributes::translation(const Offset& offset) {
        validateAttributeEdit();
        glm::mat3 translation = glm::mat3(1.0f);
        translation[2] = glm::vec3(offset.x, offset.y, 1.0f);
        return composeTransform(translation, TransformOperation::Translation);
    }

    Attributes& Attributes::rotation(float radians, const Point& center) {
        validateAttributeEdit();
        // Translate to origin
        glm::mat3 toOrigin = glm::mat3(1.0f);
        toOrigin[2] = glm::vec3(-center.x, -center.y, 1.0f);
        
        // Rotate
        glm::mat3 rotation = glm::mat3(1.0f);
        float cos_r = cos(radians);
        float sin_r = sin(radians);
        rotation[0][0] = cos_r;
        rotation[0][1] = sin_r;
        rotation[1][0] = -sin_r;
        rotation[1][1] = cos_r;
        
        // Translate back
        glm::mat3 fromOrigin = glm::mat3(1.0f);
        fromOrigin[2] = glm::vec3(center.x, center.y, 1.0f);
        
        return composeTransform(fromOrigin * rotation * toOrigin, TransformOperation::General);
    }

    Attributes& Attributes::scale(float factor, const Point& center) {
        validateAttributeEdit();
        // Translate to origin
        glm::mat3 toOrigin = glm::mat3(1.0f);
        toOrigin[2] = glm::vec3(-center.x, -center.y, 1.0f);
        
        // Scale
        glm::mat3 scale = glm::mat3(1.0f);
        scale[0][0] = factor;
        scale[1][1] = factor;
        
        // Translate back
        glm::mat3 fromOrigin = glm::mat3(1.0f);
        fromOrigin[2] = glm::vec3(center.x, center.y, 1.0f);
        
        return composeTransform(fromOrigin * scale * toOrigin, TransformOperation::Scale);
    }

    Attributes& Attributes::scale(float xFactor, float yFactor, const Point& center) {
        validateAttributeEdit();
        // Translate to origin
        glm::mat3 toOrigin = glm::mat3(1.0f);
        toOrigin[2] = glm::vec3(-center.x, -center.y, 1.0f);
        
        // Scale
        glm::mat3 scale = glm::mat3(1.0f);
        scale[0][0] = xFactor;
        scale[1][1] = yFactor;
        
        // Translate back
        glm::mat3 fromOrigin = glm::mat3(1.0f);
        fromOrigin[2] = glm::vec3(center.x, center.y, 1.0f);
        
        return composeTransform(fromOrigin * scale * toOrigin, TransformOperation::Scale);
    }

    Attributes& Attributes::skew(float xSkew, float ySkew, const Point& center) {
        validateAttributeEdit();
        // Translate to origin
        glm::mat3 toOrigin = glm::mat3(1.0f);
        toOrigin[2] = glm::vec3(-center.x, -center.y, 1.0f);
        
        // GLM doesn't have a direct skew function, so we'll create a skew matrix manually
        glm::mat3 skewMatrix = glm::mat3(1.0f);
        skewMatrix[0][1] = xSkew;  // skew X
        skewMatrix[1][0] = ySkew;  // skew Y
        
        // Translate back
        glm::mat3 fromOrigin = glm::mat3(1.0f);
        fromOrigin[2] = glm::vec3(center.x, center.y, 1.0f);
        
        return composeTransform(fromOrigin * skewMatrix * toOrigin, TransformOperation::General);
    }

    Attributes& Attributes::transform(const glm::mat3& matrix) {
        validateAttributeEdit();
        return composeTransform(matrix, TransformOperation::General);
    }

    Attributes& Attributes::composeTransform(const glm::mat3& matrix, TransformOperation) {
        return setTransform(getTransform() * matrix);
    }

    Attributes& Attributes::setTransform(const glm::mat3& matrix) {
        setTransformImpl(matrix);
        return *this;
    }

    void Attributes::setTransformImpl(const glm::mat3& matrix) {
        validateAttributeEdit();
        mTransform = matrix;
    }

    // Blend mode
    Attributes& Attributes::blendMode(BlendMode mode) {
        validateAttributeEdit();
        attributeChanging(Blend);
        mBlendMode = mode;
        return *this;
    }

    // Text attributes
    Attributes& Attributes::textSize(float size) {
        validateAttributeEdit();
        attributeChanging(TextSize);
        mTextSize = size;
        return *this;
    }

    Attributes& Attributes::textStyle(uint32 style) {
        validateAttributeEdit();
        attributeChanging(TextStyle);
        mTextStyle = style;
        return *this;
    }

    Attributes& Attributes::font(Font* font) {
        validateAttributeEdit();
        attributeChanging(Typeface);
        if (font) font->addRef();
        mRetainedFont = std::shared_ptr<Font>(font, [](Font* p) { if (p) p->release(); });
        mFont = font;
        return *this;
    }

    // Image attributes
    Attributes& Attributes::frame(int frame) {
        validateAttributeEdit();
        attributeChanging(Frame);
        mFrame = frame;
        return *this;
    }

    Attributes& Attributes::fitType(FitType fit) {
        validateAttributeEdit();
        attributeChanging(Fit);
        mFitType = fit;
        return *this;
    }

    Attributes& Attributes::clipOverflow(bool clip) {
        validateAttributeEdit();
        attributeChanging(Clip);
        mClipOverflow = clip;
        return *this;
    }

    Attributes& Attributes::subsection(const Rect& section) {
        validateAttributeEdit();
        attributeChanging(Subsection);
        mSubsection = section;
        return *this;
    }

    // Sphere attributes
    Attributes& Attributes::sphereRotation(float rotation) {
        validateAttributeEdit();
        attributeChanging(SphereRotation);
        mSphereRotation = rotation;
        return *this;
    }

    Attributes& Attributes::polarOffset(const Offset& offset) {
        validateAttributeEdit();
        attributeChanging(PolarOffset);
        mPolarOffset = offset;
        return *this;
    }

    Attributes& Attributes::lightOffset(const Offset& offset) {
        validateAttributeEdit();
        attributeChanging(LightOffset);
        mLightOffset = offset;
        return *this;
    }

    Attributes& Attributes::ambientLight(const Color& color) {
        validateAttributeEdit();
        attributeChanging(AmbientLight);
        mAmbientLight = color;
        return *this;
    }

    Attributes& Attributes::texture(Image* texture) {
        validateAttributeEdit();
        attributeChanging(Texture);
        if (texture) texture->addRef();
        mRetainedTexture = std::shared_ptr<Image>(texture, [](Image* p) { if (p) p->release(); });
        mTexture = texture;
        return *this;
    }


} // end namespace pdg
