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

