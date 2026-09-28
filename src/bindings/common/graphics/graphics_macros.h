#define ATTRIBUTES_IFDEF %#ifdef
#define ATTRIBUTES_IFNDEF %#ifndef
#define ATTRIBUTES_ELSE %#else
#define ATTRIBUTES_ENDIF %#endif
#define IMAGE_METHODS(klass)  \
  PROPERTY(klass, TransparentColor) CR \
  PROPERTY(klass, Opacity)  		 CR \
  METHOD(klass, GetWidth)  		 CR \
  METHOD(klass, GetHeight)  		 CR \
  METHOD(klass, GetImageBounds)  	 CR \
  METHOD(klass, GetSubsection)  	 CR \
  METHOD(klass, SetEdgeClamping)    CR \
  METHOD(klass, RetainData)  		 CR \
  METHOD(klass, RetainAlpha)  		 CR \
  METHOD(klass, PrepareToRasterize) CR \
  METHOD(klass, GetAlphaValue)  	 CR \
  METHOD(klass, GetPixel)


#define ATTRIBUTES_METHODS(klass) \
    METHOD(klass, WithAppearance) CR \
  METHOD(klass, LineColor) CR \
  METHOD(klass, LineThickness) CR \
  METHOD(klass, LineOpacity) CR \
  METHOD(klass, SetLineStyle) CR \
  METHOD(klass, FillColor) CR \
  METHOD(klass, FillOpacity) CR \
  METHOD(klass, FillGradient) CR \
  METHOD(klass, FillRadialGradient) CR \
  METHOD(klass, RoundedCorners) CR \
  METHOD(klass, Translation) CR \
  METHOD(klass, Rotation) CR \
  METHOD(klass, Scale) CR \
  METHOD(klass, Skew) CR \
  METHOD(klass, Transform) CR \
  METHOD(klass, SetTransform) CR \
  METHOD(klass, SetBlendMode) CR \
  METHOD(klass, TextSize) CR \
  METHOD(klass, TextStyle) CR \
ATTRIBUTES_IFNDEF PDG_NO_GUI CR \
  METHOD(klass, SetFont) CR \
ATTRIBUTES_ENDIF CR \
  METHOD(klass, Frame) CR \
  METHOD(klass, SetFitType) CR \
  METHOD(klass, ClipOverflow) CR \
  METHOD(klass, Subsection) CR \
  METHOD(klass, SphereRotation) CR \
  METHOD(klass, PolarOffset) CR \
  METHOD(klass, LightOffset) CR \
  METHOD(klass, AmbientLight) CR \
  METHOD(klass, Texture) CR \
  METHOD(klass, GetLineColor) CR \
  METHOD(klass, GetLineThickness) CR \
  METHOD(klass, GetLineOpacity) CR \
  METHOD(klass, GetLineStyle) CR \
  METHOD(klass, GetFillColor) CR \
  METHOD(klass, GetFillOpacity) CR \
  METHOD(klass, GetRoundedCornerRadius) CR \
  METHOD(klass, GetGradientType) CR \
  METHOD(klass, GetGradientStart) CR \
  METHOD(klass, GetGradientEnd) CR \
  METHOD(klass, GetGradientStartColor) CR \
  METHOD(klass, GetGradientEndColor) CR \
  METHOD(klass, GetRadialGradientCenter) CR \
  METHOD(klass, GetRadialGradientRadius) CR \
  METHOD(klass, GetRadialGradientCenterColor) CR \
  METHOD(klass, GetRadialGradientEndColor) CR \
  METHOD(klass, GetTransform) CR \
  METHOD(klass, GetBlendMode) CR \
  METHOD(klass, GetTextSize) CR \
  METHOD(klass, GetTextStyle) CR \
ATTRIBUTES_IFNDEF PDG_NO_GUI CR \
  METHOD(klass, GetFont) CR \
ATTRIBUTES_ENDIF CR \
  METHOD(klass, GetFrame) CR \
  METHOD(klass, GetFitType) CR \
  METHOD(klass, GetClipOverflow) CR \
  METHOD(klass, GetSubsection) CR \
  METHOD(klass, GetSphereRotation) CR \
  METHOD(klass, GetPolarOffset) CR \
  METHOD(klass, GetLightOffset) CR \
  METHOD(klass, GetAmbientLight) CR \
  METHOD(klass, GetTexture)

#define REQUIRE_ATTRIBUTES_ARG(n, name) CR \
    Attributes* name = ExtractAttributes(ARGV[n-1]); CR \
    if (!name) { THROW_TYPE_ERR("Expected Attributes or AnimatedAttributes"); RETURN_NULL; }
