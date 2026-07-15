#define HAS_IMAGE_METHODS(klass) \
    HAS_GETTER(klass, Width)                  \
    HAS_GETTER(klass, Height)                 \
    HAS_GETTER(klass, ImageBounds)            \
    HAS_GETTER(klass, Subsection)             \
    HAS_SETTER(klass, TransparentColor)       \
    HAS_PROPERTY(klass, Opacity)              \
    HAS_SETTER(klass, EdgeClamping)           \
    HAS_METHOD(klass, "getTransparentColor", GetTransparentColor)  \
    HAS_METHOD(klass, "retainData", RetainData)                     \
    HAS_METHOD(klass, "retainAlpha", RetainAlpha)                   \
    HAS_METHOD(klass, "prepareToRasterize", PrepareToRasterize)     \
    HAS_GETTER(klass, AlphaValue)             \
    HAS_METHOD(klass, "getPixel", GetPixel)  \

#define IMAGE_BASE_CLASS_IMPL(klass) CR \
  PROPERTY_IMPL(klass, TransparentColor, COLOR) CR \
  GETTER_IMPL(klass, Width, INTEGER) CR \
  GETTER_IMPL(klass, Height, INTEGER) CR \
  METHOD_IMPL(klass, GetImageBounds) CR \
	METHOD_SIGNATURE("get image boundary rect, optionally with top left at given point", CR \
		[object Rect], 1, ([object Point] at)); CR \
    OPTIONAL_POINT_ARG(1, at, pdg::Point(0,0)); CR \
    Rect r = self->getImageBounds(at); CR \
	RETURN(RECT2VAL(r)); CR \
	END CR \
  METHOD_IMPL(klass, GetSubsection) CR \
	METHOD_SIGNATURE("get image that is an arbitrary subsection of this image", CR \
		[object Image], 1, ({[object Quad]|[object Rect]} quad)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_QUAD_ARG(1, quad); CR \
	Image* image = self->getSubsection(quad); CR \
	RETURN_CPP_OBJECT(image, Image); CR \
	END CR \
  METHOD_IMPL(klass, GetOpacity) CR \
	METHOD_SIGNATURE("get opacity of this image: 0.0 - completely transparent to 1.0 - completely solid", CR \
		number, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	uint8 opacity = self->getOpacity(); CR \
	double opacityFloat = (float)opacity / 255.0f; CR \
	RETURN_NUMBER(opacityFloat); CR \
	END CR \
  METHOD_IMPL(klass, SetOpacity) CR \
	METHOD_SIGNATURE("set opacity of this image as range from either (0-255) or (0.0 to 1.0)", CR \
		undefined, 1, (number opacity)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, opacityFloat); CR \
	uint32 opacity; CR \
	if (opacityFloat <= 1.0) { CR \
		opacity = std::floor(255.0f * opacityFloat); CR \
	} else { CR \
		opacity = std::round(opacityFloat); CR \
	} CR \
	if (opacity > 255) opacity = 255; CR \
	self->setOpacity(opacity); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, SetEdgeClamping) CR \
	METHOD_SIGNATURE("set whether image uses edge clamping or not", CR \
		undefined, 1, (boolean inUseEdgeClamp)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_BOOL_ARG(1, inUseEdgeClamp); CR \
	self->setEdgeClamping(inUseEdgeClamp); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, RetainData) CR \
	METHOD_SIGNATURE("retain pixel data for use by Image.getPixel()", CR \
		undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->retainData(); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, RetainAlpha) CR \
	METHOD_SIGNATURE("retain alpha data for use by Image.getAlphaValue() or per-pixel sprite collisions", CR \
		undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->retainAlpha(); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, PrepareToRasterize) CR \
	METHOD_SIGNATURE("bind the image into an OpenGL texture and free image data from main memory", CR \
		number, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->prepareToRasterize(); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, GetAlphaValue) CR \
	METHOD_SIGNATURE("", number, 2, ({[object Point] p|[number int] x, [number int] y}));  CR \
    REQUIRE_ARG_MIN_COUNT(1);  CR \
    uint8 a; CR \
    if (ARGC >= 2) { CR \
    	REQUIRE_INT32_ARG(1, x); CR \
		REQUIRE_INT32_ARG(2, y); CR \
    	a = self->getAlphaValue(x, y); CR \
    } else { CR \
    	REQUIRE_POINT_ARG(1, p); CR \
    	a = self->getAlphaValue(p.x, p.y); CR \
    } CR \
	RETURN_UNSIGNED(a); CR \
	END CR \
  METHOD_IMPL(klass, GetPixel) CR \
	METHOD_SIGNATURE("", [object Color], 2, ({[object Point] p|[number int] x, [number int] y}));  CR \
    REQUIRE_ARG_MIN_COUNT(1);  CR \
    pdg::Color c; CR \
    if (ARGC >= 2) { CR \
    	REQUIRE_INT32_ARG(1, x); CR \
    	REQUIRE_INT32_ARG(2, y); CR \
    	c = self->getPixel(x, y); CR \
    } else { CR \
    	REQUIRE_POINT_ARG(1, p); CR \
    	c = self->getPixel(p.x, p.y); CR \
    } CR \
	RETURN(COLOR2VAL(c)); CR \
	END

