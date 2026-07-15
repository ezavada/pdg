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
        : mLineColor(PDG_BLACK_COLOR)
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
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
        , mAttributesScriptObj()  // Initialize the persistent object
#endif
    {
    }

    Attributes::Attributes(const Attributes& other)
        : mLineColor(other.mLineColor)
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
        , mTransform(other.mTransform)
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
        , mTexture(other.mTexture)
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
        , mAttributesScriptObj()  // Initialize the persistent object (don't copy from other)
#endif
    {
    }

    Attributes& Attributes::operator=(const Attributes& other) {
        if (this != &other) {
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
            mTransform = other.mTransform;
            mBlendMode = other.mBlendMode;
            mTextSize = other.mTextSize;
            mTextStyle = other.mTextStyle;
            mFont = other.mFont;
            mFrame = other.mFrame;
            mFitType = other.mFitType;
            mClipOverflow = other.mClipOverflow;
            mSubsection = other.mSubsection;
            mSphereRotation = other.mSphereRotation;
            mPolarOffset = other.mPolarOffset;
            mLightOffset = other.mLightOffset;
            mTexture = other.mTexture;
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
            // V8 handles are non-copyable, so we can't copy them in a copy assignment operator
            // The script object will be recreated when needed
            // mAttributesScriptObj = other.mAttributesScriptObj; // This would fail
#endif
        }
        return *this;
    }

    // Line attributes
    Attributes& Attributes::lineColor(const Color& color) {
        mLineColor = color;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_Solid;
        }
        return *this;
    }

    Attributes& Attributes::lineThickness(float thickness) {
        mLineThickness = thickness;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_Solid;
        }
        return *this;
    }

    Attributes& Attributes::lineOpacity(float opacity) {
        mLineOpacity = opacity;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_Solid;
        }
        return *this;
    }

    Attributes& Attributes::lineStyle(LineStyle style) {
        mLineStyle = style;
        return *this;
    }

    // Fill attributes
    Attributes& Attributes::fillColor(const Color& color) {
        mFillColor = color;
        mGradientType = gradientType_None;  // Clear gradient when setting solid color
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_None;
        }
        return *this;
    }

    Attributes& Attributes::fillOpacity(float opacity) {
        mFillOpacity = opacity;
        if (mLineStyle == lineStyle_Auto) {
            mLineStyle = lineStyle_None;
        }
        return *this;
    }

    Attributes& Attributes::fillGradient(const Point& start, const Color& startColor, const Point& end, const Color& endColor) {
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
        mRoundedCornerRadius = radius;
        return *this;
    }

    // Transform attributes
    Attributes& Attributes::translation(const Offset& offset) {
        glm::mat3 translation = glm::mat3(1.0f);
        translation[2] = glm::vec3(offset.x, offset.y, 1.0f);
        mTransform = mTransform * translation;
        return *this;
    }

    Attributes& Attributes::rotation(float radians, const Point& center) {
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
        
        mTransform = mTransform * fromOrigin * rotation * toOrigin;
        return *this;
    }

    Attributes& Attributes::scale(float factor, const Point& center) {
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
        
        mTransform = mTransform * fromOrigin * scale * toOrigin;
        return *this;
    }

    Attributes& Attributes::scale(float xFactor, float yFactor, const Point& center) {
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
        
        mTransform = mTransform * fromOrigin * scale * toOrigin;
        return *this;
    }

    Attributes& Attributes::skew(float xSkew, float ySkew, const Point& center) {
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
        
        mTransform = mTransform * fromOrigin * skewMatrix * toOrigin;
        return *this;
    }

    Attributes& Attributes::transform(const glm::mat3& matrix) {
        mTransform = mTransform * matrix;
        return *this;
    }

    Attributes& Attributes::setTransform(const glm::mat3& matrix) {
        mTransform = matrix;
        return *this;
    }

    // Blend mode
    Attributes& Attributes::blendMode(BlendMode mode) {
        mBlendMode = mode;
        return *this;
    }

    // Text attributes
    Attributes& Attributes::textSize(float size) {
        mTextSize = size;
        return *this;
    }

    Attributes& Attributes::textStyle(uint32 style) {
        mTextStyle = style;
        return *this;
    }

    Attributes& Attributes::font(Font* font) {
        mFont = font;
        return *this;
    }

    // Image attributes
    Attributes& Attributes::frame(int frame) {
        mFrame = frame;
        return *this;
    }

    Attributes& Attributes::fitType(FitType fit) {
        mFitType = fit;
        return *this;
    }

    Attributes& Attributes::clipOverflow(bool clip) {
        mClipOverflow = clip;
        return *this;
    }

    Attributes& Attributes::subsection(const Rect& section) {
        mSubsection = section;
        return *this;
    }

    // Sphere attributes
    Attributes& Attributes::sphereRotation(float rotation) {
        mSphereRotation = rotation;
        return *this;
    }

    Attributes& Attributes::polarOffset(const Offset& offset) {
        mPolarOffset = offset;
        return *this;
    }

    Attributes& Attributes::lightOffset(const Offset& offset) {
        mLightOffset = offset;
        return *this;
    }

    Attributes& Attributes::ambientLight(const Color& color) {
        mAmbientLight = color;
        return *this;
    }

    Attributes& Attributes::texture(Image* texture) {
        mTexture = texture;
        return *this;
    }


} // end namespace pdg
