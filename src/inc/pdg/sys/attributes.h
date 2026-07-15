// -----------------------------------------------
//  attributes.h
//
// New graphics API for PDG framework
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

#ifndef PDG_ATTRIBUTES_H_INCLUDED
#define PDG_ATTRIBUTES_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/coordinates.h"
#include "pdg/sys/global_types.h"
#include "pdg/sys/color.h"
#include "pdg/sys/spline.h"
#include "pdg/sys/polygon.h"
#include "pdg/sys/font.h"
#include "pdg/sys/image.h"

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

namespace pdg {

    // -----------------------------------------------------------------------------------
    // Enums for styling and rendering
    // -----------------------------------------------------------------------------------

    enum LineStyle {
        lineStyle_Auto, // solid for lines, none for fills
        lineStyle_None,
        lineStyle_Solid,
        lineStyle_Dashed,
        lineStyle_Dotted,
        lineStyle_DashDot,
        lineStyle_DashDotDot
    };

    // OpenGL-supported blend modes only
    enum BlendMode {
        blendMode_Normal,        // GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
        blendMode_Additive,      // GL_SRC_ALPHA, GL_ONE
        blendMode_Multiply,      // GL_DST_COLOR, GL_ZERO
        blendMode_Screen,        // GL_ONE, GL_ONE_MINUS_SRC_COLOR
        blendMode_Darken,        // GL_ONE, GL_ONE_MINUS_SRC_ALPHA
        blendMode_Lighten        // GL_SRC_ALPHA, GL_ONE
    };

    enum GradientType {
        gradientType_None,
        gradientType_Linear,
        gradientType_Radial
    };

    // Forward declarations to avoid circular includes
    class Font;
    class Image;

    // -----------------------------------------------------------------------------------
    // Attributes class for styling and transformations
    // -----------------------------------------------------------------------------------

    class Attributes {
    public:
         
        // Constructors
        Attributes();
        Attributes(const Attributes& other);
        Attributes& operator=(const Attributes& other);

        // Line attributes
        Attributes& lineColor(const Color& color);
        Attributes& lineThickness(float thickness);
        Attributes& lineOpacity(float opacity);
        Attributes& lineStyle(LineStyle style);

        // Fill attributes  
        Attributes& fillColor(const Color& color);
        Attributes& fillOpacity(float opacity);
        Attributes& fillGradient(const Point& start, const Color& startColor, const Point& end, const Color& endColor);
        Attributes& fillRadialGradient(const Point& center, const Color& centerColor, float radius, const Color& endColor);

        // Texture attributes
        Attributes& texture(Image* texture);
        Attributes& fitType(FitType fit);
        Attributes& clipOverflow(bool clip);

        // Shape attributes
        Attributes& roundedCorners(float radius);

        // Transform attributes
        Attributes& translation(const Offset& offset);
        Attributes& rotation(float radians, const Point& center = Point(0, 0));
        Attributes& scale(float factor, const Point& center = Point(0, 0));
        Attributes& scale(float xFactor, float yFactor, const Point& center = Point(0, 0));
        Attributes& skew(float xSkew, float ySkew, const Point& center = Point(0, 0));
        Attributes& transform(const glm::mat3& matrix);
        Attributes& setTransform(const glm::mat3& matrix);  // Set transform directly instead of multiplying

        // Blend mode
        Attributes& blendMode(BlendMode mode);

        // Text attributes
        Attributes& textSize(float size);
        Attributes& textStyle(uint32 style);
        Attributes& font(Font* font);

        // Image attributes  
        Attributes& frame(int frame);
        Attributes& subsection(const Rect& section);

        // Sphere attributes
        Attributes& sphereRotation(float rotation);
        Attributes& polarOffset(const Offset& offset);
        Attributes& lightOffset(const Offset& offset);
        Attributes& ambientLight(const Color& color);

        // Getters for internal use
        const Color& getLineColor() const { return mLineColor; }
        float getLineThickness() const { return mLineThickness; }
        float getLineOpacity() const { return mLineOpacity; }
        LineStyle getLineStyle() const { return mLineStyle == lineStyle_Auto ? lineStyle_Solid : mLineStyle; }

        const Color& getFillColor() const { return mFillColor; }
        float getFillOpacity() const { return mFillOpacity; }
        GradientType getGradientType() const { return mGradientType; }
        const Point& getGradientStart() const { return mGradientStart; }
        const Point& getGradientEnd() const { return mGradientEnd; }
        const Color& getGradientStartColor() const { return mGradientStartColor; }
        const Color& getGradientEndColor() const { return mGradientEndColor; }
        const Point& getRadialGradientCenter() const { return mRadialGradientCenter; }
        float getRadialGradientRadius() const { return mRadialGradientRadius; }
        const Color& getRadialGradientCenterColor() const { return mRadialGradientCenterColor; }
        const Color& getRadialGradientEndColor() const { return mRadialGradientEndColor; }

        float getRoundedCornerRadius() const { return mRoundedCornerRadius; }
        
        const glm::mat3& getTransform() const { return mTransform; }
        BlendMode getBlendMode() const { return mBlendMode; }

        // Getters for new attributes
        float getTextSize() const { return mTextSize; }
        uint32 getTextStyle() const { return mTextStyle; }
        Font* getFont() const { return mFont; }
        int getFrame() const { return mFrame; }
        FitType getFitType() const { return mFitType; }
        bool getClipOverflow() const { return mClipOverflow; }
        float getSphereRotation() const { return mSphereRotation; }
        const Offset& getPolarOffset() const { return mPolarOffset; }
        const Offset& getLightOffset() const { return mLightOffset; }
        const Color& getAmbientLight() const { return mAmbientLight; }
        Image* getTexture() const { return mTexture; }
        const Rect& getSubsection() const { return mSubsection; }

        bool hasLine() const { return mLineStyle != lineStyle_None && mLineStyle != lineStyle_Auto && mLineOpacity > 0.0f && mLineColor.alpha > 0.0f && mLineThickness > 0.0f; }
        bool hasFill() const { return mFillOpacity > 0.0f && mFillColor.alpha > 0.0f; }

        // Script object for JavaScript bindings
      #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
        SCRIPT_OBJECT_REF mAttributesScriptObj;
      #endif

        virtual ~Attributes() {
        #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
          #ifndef PDG_NO_GUI
            CleanupAttributesScriptObject(mAttributesScriptObj);
          #endif
        #endif
        }

    private:
        // Line properties
        Color mLineColor;
        float mLineThickness;
        float mLineOpacity;
        LineStyle mLineStyle;
        
        // Fill properties
        Color mFillColor;
        float mFillOpacity;
        
        // Gradient properties
        GradientType mGradientType;
        Point mGradientStart;
        Point mGradientEnd;
        Color mGradientStartColor;
        Color mGradientEndColor;
        
        // Radial gradient properties
        Point mRadialGradientCenter;
        float mRadialGradientRadius;
        Color mRadialGradientCenterColor;
        Color mRadialGradientEndColor;
        
        // Rounded corners properties
        float mRoundedCornerRadius;
        
        // Transform and blend properties
        glm::mat3 mTransform;
        BlendMode mBlendMode;
        
        // Text properties
        float mTextSize;
        uint32 mTextStyle;
        Font* mFont;
        
        // Image properties
        int mFrame;
        FitType mFitType;
        bool mClipOverflow;
        Rect mSubsection;
        
        // Sphere properties
        float mSphereRotation;
        Offset mPolarOffset;
        Offset mLightOffset;
        Color mAmbientLight;
        Image* mTexture;
    };

} // end namespace pdg

#endif // PDG_ATTRIBUTES_H_INCLUDED
