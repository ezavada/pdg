#define ATTRIBUTES_IFDEF %#ifdef
#define ATTRIBUTES_IFNDEF %#ifndef
#define ATTRIBUTES_ELSE %#else
#define ATTRIBUTES_ENDIF %#endif
// Shared Attributes surface, instantiated with correctly typed native wrappers.
#define HAS_ATTRIBUTES_METHODS(klass) \
    METHODS_FROM(klass, Attributes, \
        HAS_METHOD(klass, "withAppearance", WithAppearance) CR \
        HAS_METHOD(klass, "lineColor", LineColor) CR \
        HAS_METHOD(klass, "lineThickness", LineThickness) CR \
        HAS_METHOD(klass, "lineOpacity", LineOpacity) CR \
        HAS_METHOD(klass, "lineStyle", SetLineStyle) CR \
        HAS_METHOD(klass, "fillColor", FillColor) CR \
        HAS_METHOD(klass, "fillOpacity", FillOpacity) CR \
        HAS_METHOD(klass, "fillGradient", FillGradient) CR \
        HAS_METHOD(klass, "fillRadialGradient", FillRadialGradient) CR \
        HAS_METHOD(klass, "roundedCorners", RoundedCorners) CR \
        HAS_METHOD(klass, "translation", Translation) CR \
        HAS_METHOD(klass, "rotation", Rotation) CR \
        HAS_METHOD(klass, "scale", Scale) CR \
        HAS_METHOD(klass, "skew", Skew) CR \
        HAS_METHOD(klass, "transform", Transform) CR \
        HAS_METHOD(klass, "setTransform", SetTransform) CR \
        HAS_METHOD(klass, "blendMode", SetBlendMode) CR \
        HAS_METHOD(klass, "textSize", TextSize) CR \
        HAS_METHOD(klass, "textStyle", TextStyle) CR \
ATTRIBUTES_IFNDEF PDG_NO_GUI CR CR \
        HAS_METHOD(klass, "font", SetFont) CR \
ATTRIBUTES_ENDIF CR CR \
        HAS_METHOD(klass, "frame", Frame) CR \
        HAS_METHOD(klass, "fitType", SetFitType) CR \
        HAS_METHOD(klass, "clipOverflow", ClipOverflow) CR \
        HAS_METHOD(klass, "subsection", Subsection) CR \
        HAS_METHOD(klass, "sphereRotation", SphereRotation) CR \
        HAS_METHOD(klass, "polarOffset", PolarOffset) CR \
        HAS_METHOD(klass, "lightOffset", LightOffset) CR \
        HAS_METHOD(klass, "ambientLight", AmbientLight) CR \
        HAS_METHOD(klass, "texture", Texture) CR \
        HAS_METHOD(klass, "getLineColor", GetLineColor) CR \
        HAS_METHOD(klass, "getLineThickness", GetLineThickness) CR \
        HAS_METHOD(klass, "getLineOpacity", GetLineOpacity) CR \
        HAS_METHOD(klass, "getLineStyle", GetLineStyle) CR \
        HAS_METHOD(klass, "getFillColor", GetFillColor) CR \
        HAS_METHOD(klass, "getFillOpacity", GetFillOpacity) CR \
        HAS_METHOD(klass, "getRoundedCornerRadius", GetRoundedCornerRadius) CR \
        HAS_METHOD(klass, "getGradientType", GetGradientType) CR \
        HAS_METHOD(klass, "getGradientStart", GetGradientStart) CR \
        HAS_METHOD(klass, "getGradientEnd", GetGradientEnd) CR \
        HAS_METHOD(klass, "getGradientStartColor", GetGradientStartColor) CR \
        HAS_METHOD(klass, "getGradientEndColor", GetGradientEndColor) CR \
        HAS_METHOD(klass, "getRadialGradientCenter", GetRadialGradientCenter) CR \
        HAS_METHOD(klass, "getRadialGradientRadius", GetRadialGradientRadius) CR \
        HAS_METHOD(klass, "getRadialGradientCenterColor", GetRadialGradientCenterColor) CR \
        HAS_METHOD(klass, "getRadialGradientEndColor", GetRadialGradientEndColor) CR \
        HAS_METHOD(klass, "getTransform", GetTransform) CR \
        HAS_METHOD(klass, "getBlendMode", GetBlendMode) CR \
        HAS_METHOD(klass, "getTextSize", GetTextSize) CR \
        HAS_METHOD(klass, "getTextStyle", GetTextStyle) CR \
ATTRIBUTES_IFNDEF PDG_NO_GUI CR CR \
        HAS_METHOD(klass, "getFont", GetFont) CR \
ATTRIBUTES_ENDIF CR CR \
        HAS_METHOD(klass, "getFrame", GetFrame) CR \
        HAS_METHOD(klass, "getFitType", GetFitType) CR \
        HAS_METHOD(klass, "getClipOverflow", GetClipOverflow) CR \
        HAS_METHOD(klass, "getSubsection", GetSubsection) CR \
        HAS_METHOD(klass, "getSphereRotation", GetSphereRotation) CR \
        HAS_METHOD(klass, "getPolarOffset", GetPolarOffset) CR \
        HAS_METHOD(klass, "getLightOffset", GetLightOffset) CR \
        HAS_METHOD(klass, "getAmbientLight", GetAmbientLight) CR \
        HAS_METHOD(klass, "getTexture", GetTexture) \
    )

#define ATTRIBUTES_METHODS_IMPL(klass, scriptClass) \
METHOD_IMPL(klass, WithAppearance) CR \
    METHOD_SIGNATURE("", [object Attributes], 2, ([object Attributes const&] overrides, boolean textOnly = false)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
    REQUIRE_ATTRIBUTES_ARG(1, overrides); CR \
    OPTIONAL_BOOL_ARG(2, textOnly, false); CR \
    Attributes* result = new Attributes(self->withAppearance(*overrides, textOnly)); CR \
    RETURN_CPP_OBJECT(result, Attributes); CR \
    END CR \
METHOD_IMPL(klass, GetLineColor) CR \
    METHOD_SIGNATURE("", [object Color const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Color color = const_cast<Color&>(self->getLineColor()); CR \
    RETURN_COLOR(color); CR \
    END CR \
METHOD_IMPL(klass, GetLineThickness) CR \
    METHOD_SIGNATURE("", [number float], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float thickness = self->getLineThickness(); CR \
    RETURN_NUMBER(thickness); CR \
    END CR \
METHOD_IMPL(klass, GetLineOpacity) CR \
    METHOD_SIGNATURE("", [number float], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float opacity = self->getLineOpacity(); CR \
    RETURN_NUMBER(opacity); CR \
    END CR \
METHOD_IMPL(klass, GetLineStyle) CR \
    METHOD_SIGNATURE("", [number uint], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    LineStyle style = self->getLineStyle(); CR \
    RETURN_UINT32(style); CR \
    END CR \
METHOD_IMPL(klass, GetFillColor) CR \
    METHOD_SIGNATURE("", [object Color const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Color color = const_cast<Color&>(self->getFillColor()); CR \
    RETURN_COLOR(color); CR \
    END CR \
METHOD_IMPL(klass, GetFillOpacity) CR \
    METHOD_SIGNATURE("", [number float], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float opacity = self->getFillOpacity(); CR \
    RETURN_NUMBER(opacity); CR \
    END CR \
METHOD_IMPL(klass, GetRoundedCornerRadius) CR \
    METHOD_SIGNATURE("", [number float], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float radius = self->getRoundedCornerRadius(); CR \
    RETURN_NUMBER(radius); CR \
    END CR \
METHOD_IMPL(klass, GetGradientType) CR \
    METHOD_SIGNATURE("", [number int], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    GradientType type = self->getGradientType(); CR \
    RETURN_UINT32(type); CR \
    END CR \
METHOD_IMPL(klass, GetGradientStart) CR \
    METHOD_SIGNATURE("", [object Point const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Point start = const_cast<Point&>(self->getGradientStart()); CR \
    RETURN_POINT(start); CR \
    END CR \
METHOD_IMPL(klass, GetGradientEnd) CR \
    METHOD_SIGNATURE("", [object Point const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Point end = const_cast<Point&>(self->getGradientEnd()); CR \
    RETURN_POINT(end); CR \
    END CR \
METHOD_IMPL(klass, GetGradientStartColor) CR \
    METHOD_SIGNATURE("", [object Color const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Color color = const_cast<Color&>(self->getGradientStartColor()); CR \
    RETURN_COLOR(color); CR \
    END CR \
METHOD_IMPL(klass, GetGradientEndColor) CR \
    METHOD_SIGNATURE("", [object Color const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Color color = const_cast<Color&>(self->getGradientEndColor()); CR \
    RETURN_COLOR(color); CR \
    END CR \
METHOD_IMPL(klass, GetRadialGradientCenter) CR \
    METHOD_SIGNATURE("", [object Point const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Point center = const_cast<Point&>(self->getRadialGradientCenter()); CR \
    RETURN_POINT(center); CR \
    END CR \
METHOD_IMPL(klass, GetRadialGradientRadius) CR \
    METHOD_SIGNATURE("", [number float], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float radius = self->getRadialGradientRadius(); CR \
    RETURN_NUMBER(radius); CR \
    END CR \
METHOD_IMPL(klass, GetRadialGradientCenterColor) CR \
    METHOD_SIGNATURE("", [object Color const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Color color = const_cast<Color&>(self->getRadialGradientCenterColor()); CR \
    RETURN_COLOR(color); CR \
    END CR \
METHOD_IMPL(klass, GetRadialGradientEndColor) CR \
    METHOD_SIGNATURE("", [object Color const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Color color = const_cast<Color&>(self->getRadialGradientEndColor()); CR \
    RETURN_COLOR(color); CR \
    END CR \
METHOD_IMPL(klass, GetTransform) CR \
    METHOD_SIGNATURE("", [array number], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    const glm::mat3& matrix = self->getTransform(); CR \
    ATTRIBUTES_IFDEF PDG_USING_JAVASCRIPT_CORE CR \
    JSObjectRef result = JSObjectMakeArray(ctx, 0, nullptr, exception); CR \
    for (int i = 0; i < 3; i++) { CR \
        for (int j = 0; j < 3; j++) { CR \
            int index = i * 3 + j; CR \
            JSObjectSetPropertyAtIndex(ctx, result, (unsigned)index, CR \
                JSValueMakeNumber(ctx, matrix[i][j]), exception); CR \
        } CR \
    } CR \
    RETURN_OBJECT(result); CR \
    ATTRIBUTES_ELSE CR \
    v8::Local<v8::Array> result = v8::Array::New(isolate, 9); CR \
    v8::Local<v8::Context> context = isolate->GetCurrentContext(); CR \
    for (int i = 0; i < 3; i++) { CR \
        for (int j = 0; j < 3; j++) { CR \
            int index = i * 3 + j; CR \
            (void)result->Set(context, index, v8::Number::New(isolate, matrix[i][j])); CR \
        } CR \
    } CR \
    args.GetReturnValue().Set(result); CR \
    ATTRIBUTES_ENDIF CR \
    END CR \
METHOD_IMPL(klass, GetBlendMode) CR \
    METHOD_SIGNATURE("", [number int], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    BlendMode blendMode = self->getBlendMode(); CR \
    RETURN_NUMBER(static_cast<int>(blendMode)); CR \
    END CR \
METHOD_IMPL(klass, LineColor) CR \
    try { CR \
    METHOD_SIGNATURE("sets the line color for strokes and outlines", [this], 1, ({[object Color const&] color|string colorName|number rgba})); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_COLOR_ARG(1, color); CR \
    self->lineColor(color); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, LineThickness) CR \
    try { CR \
    METHOD_SIGNATURE("sets the thickness of line strokes in pixels", [this], 1, ([number float] thickness)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, thickness); CR \
    self->lineThickness(thickness); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, LineOpacity) CR \
    try { CR \
    METHOD_SIGNATURE("sets the opacity for line strokes (0.0 to 1.0)", [this], 1, ([number float] opacity)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, opacity); CR \
    self->lineOpacity(opacity); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, SetLineStyle) CR \
    try { CR \
    METHOD_SIGNATURE("sets the style of line strokes (solid, dashed, etc.)", [this], 1, ([number int] lineStyle)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, lineStyle); CR \
    self->lineStyle(static_cast<LineStyle>(lineStyle)); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, FillColor) CR \
    try { CR \
    METHOD_SIGNATURE("sets the fill color for shapes and drawings", [this], 1, ({[object Color const&] color|string colorName|number rgba})); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_COLOR_ARG(1, color); CR \
    self->fillColor(color); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, FillOpacity) CR \
    try { CR \
    METHOD_SIGNATURE("sets the opacity for fill operations (0.0 to 1.0)", [this], 1, ([number float] opacity)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, opacity); CR \
    self->fillOpacity(opacity); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, FillGradient) CR \
    try { CR \
    METHOD_SIGNATURE("sets a linear gradient fill from start point to end point", [this], 4, ([object Point const&] start, {[object Color const&] startColor|string startColorName|number startRGBA}, [object Point const&] end, {[object Color const&] endColor|string endColorName|number endRGBA})); CR \
    REQUIRE_ARG_COUNT(4); CR \
    REQUIRE_POINT_ARG(1, start); CR \
    REQUIRE_COLOR_ARG(2, startColor); CR \
    REQUIRE_POINT_ARG(3, end); CR \
    REQUIRE_COLOR_ARG(4, endColor); CR \
    self->fillGradient(start, startColor, end, endColor); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, FillRadialGradient) CR \
    try { CR \
    METHOD_SIGNATURE("Create a radial gradient fill from center point to outer radius", [this], 4, ([object Point const&] center, {[object Color const&] centerColor|string centerColorName|number centerRGBA}, [number float] radius, {[object Color const&] endColor|string endColorName|number endRGBA})); CR \
    REQUIRE_ARG_COUNT(4); CR \
    REQUIRE_POINT_ARG(1, center); CR \
    REQUIRE_COLOR_ARG(2, centerColor); CR \
    REQUIRE_NUMBER_ARG(3, radius); CR \
    REQUIRE_COLOR_ARG(4, endColor); CR \
    self->fillRadialGradient(center, centerColor, radius, endColor); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, RoundedCorners) CR \
    try { CR \
    METHOD_SIGNATURE("sets the radius for rounded corners", [this], 1, ([number float] radius)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, radius); CR \
    self->roundedCorners(radius); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, Translation) CR \
    try { CR \
    METHOD_SIGNATURE("sets the translation offset for transformations", [this], 1, ([object Offset const&] offset)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_OFFSET_ARG(1, offset); CR \
    self->translation(offset); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, Rotation) CR \
    try { CR \
    METHOD_SIGNATURE("sets the rotation angle and center point for transformations", [this], 2, ([number float] radians, [object Point const&] center = Point(0,0))); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, radians); CR \
    OPTIONAL_POINT_ARG(2, center, Point(0, 0)); CR \
    self->rotation(radians, center); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, Scale) CR \
    try { CR \
    METHOD_SIGNATURE("sets the scaling factors for x and y axes", [this], 3, ([number float] xFactor, [number float] yFactor = xFactor, [object Point const&] center = Point(0,0))); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, xFactor); CR \
    OPTIONAL_NUMBER_ARG(2, yFactor, xFactor); CR \
    OPTIONAL_POINT_ARG(3, center, Point(0, 0)); CR \
    if (ARGC > 1 && !VALUE_IS_UNDEFINED(ARGV[1])) { CR \
        self->scale(xFactor, yFactor, center); CR \
    } else { CR \
        self->scale(xFactor, center); CR \
    } CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, Skew) CR \
    try { CR \
    METHOD_SIGNATURE("sets the skew transformation for x and y axes", [this], 3, ([number float] xSkew, [number float] ySkew, [object Point const&] center = Point(0,0))); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
    REQUIRE_NUMBER_ARG(1, xSkew); CR \
    REQUIRE_NUMBER_ARG(2, ySkew); CR \
    OPTIONAL_POINT_ARG(3, center, Point(0, 0)); CR \
    self->skew(xSkew, ySkew, center); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, Transform) CR \
    try { CR \
    METHOD_SIGNATURE("sets the transformation matrix directly", [this], 1, ([array number] matrix)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    ATTRIBUTES_IFDEF PDG_USING_JAVASCRIPT_CORE CR \
    if (!JSValueIsArray(ctx, ARGV[0])) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]); CR \
    } CR \
    JSObjectRef matrixArray = JSValueToObject(ctx, ARGV[0], exception); CR \
    JSStringRef lengthName = JSStringCreateWithUTF8CString("length"); CR \
    JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception); CR \
    JSStringRelease(lengthName); CR \
    if (*exception) { RETURN_NULL; } CR \
    double matrixLength = JSValueToNumber(ctx, lengthValue, exception); CR \
    if (*exception) { RETURN_NULL; } CR \
    if (matrixLength != 9) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]); CR \
    } CR \
    glm::mat3 matrix; CR \
    for (int i = 0; i < 3; i++) { CR \
        for (int j = 0; j < 3; j++) { CR \
            JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception); CR \
            if (*exception) { RETURN_NULL; } CR \
            if (!JSValueIsNumber(ctx, element)) { CR \
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]); CR \
            } CR \
            matrix[i][j] = JSValueToNumber(ctx, element, exception); CR \
        } CR \
    } CR \
    ATTRIBUTES_ELSE CR \
    if (!ARGV[0]->IsArray()) { CR \
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers"); CR \
        return; CR \
    } CR \
    v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(ARGV[0]); CR \
    if (matrixArray->Length() != 9) { CR \
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers"); CR \
        return; CR \
    } CR \
    glm::mat3 matrix; CR \
    v8::Local<v8::Context> context = isolate->GetCurrentContext(); CR \
    for (int i = 0; i < 3; i++) { CR \
        for (int j = 0; j < 3; j++) { CR \
            v8::Local<v8::Value> element; CR \
            if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element)) { RETURN_NULL; } CR \
            if (!element->IsNumber()) { CR \
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers"); CR \
                return; CR \
            } CR \
            matrix[i][j] = element.As<v8::Number>()->Value(); CR \
        } CR \
    } CR \
    ATTRIBUTES_ENDIF CR \
    self->transform(matrix); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, SetTransform) CR \
    try { CR \
    METHOD_SIGNATURE("Replace the affine transform immediately.", [this], 1, ([array number] matrix)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    ATTRIBUTES_IFDEF PDG_USING_JAVASCRIPT_CORE CR \
    if (!JSValueIsArray(ctx, ARGV[0])) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]); CR \
    } CR \
    JSObjectRef matrixArray = JSValueToObject(ctx, ARGV[0], exception); CR \
    JSStringRef lengthName = JSStringCreateWithUTF8CString("length"); CR \
    JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception); CR \
    JSStringRelease(lengthName); CR \
    if (*exception) { RETURN_NULL; } CR \
    double matrixLength = JSValueToNumber(ctx, lengthValue, exception); CR \
    if (*exception) { RETURN_NULL; } CR \
    if (matrixLength != 9) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]); CR \
    } CR \
    glm::mat3 matrix; CR \
    for (int i = 0; i < 3; i++) { CR \
        for (int j = 0; j < 3; j++) { CR \
            JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception); CR \
            if (*exception) { RETURN_NULL; } CR \
            if (!JSValueIsNumber(ctx, element)) { CR \
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]); CR \
            } CR \
            matrix[i][j] = JSValueToNumber(ctx, element, exception); CR \
        } CR \
    } CR \
    ATTRIBUTES_ELSE CR \
    if (!ARGV[0]->IsArray()) { CR \
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers"); CR \
        return; CR \
    } CR \
    v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(ARGV[0]); CR \
    if (matrixArray->Length() != 9) { CR \
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers"); CR \
        return; CR \
    } CR \
    glm::mat3 matrix; CR \
    v8::Local<v8::Context> context = isolate->GetCurrentContext(); CR \
    for (int i = 0; i < 3; i++) { CR \
        for (int j = 0; j < 3; j++) { CR \
            v8::Local<v8::Value> element; CR \
            if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element)) { RETURN_NULL; } CR \
            if (!element->IsNumber()) { CR \
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers"); CR \
                return; CR \
            } CR \
            matrix[i][j] = element.As<v8::Number>()->Value(); CR \
        } CR \
    } CR \
    ATTRIBUTES_ENDIF CR \
    self->setTransform(matrix); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, SetBlendMode) CR \
    try { CR \
    METHOD_SIGNATURE("sets the blend mode for rendering operations", [this], 1, ([number int] blendMode)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, blendMode); CR \
    self->blendMode(static_cast<BlendMode>(blendMode)); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, TextSize) CR \
    try { CR \
    METHOD_SIGNATURE("Sets the text size in points for drawing text", [this], 1, ([number float] size)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, size); CR \
    self->textSize(size); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, TextStyle) CR \
    try { CR \
    METHOD_SIGNATURE("Sets text style flags (bold, italic, underline, alignment)", [this], 1, ([number int] style)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, style); CR \
    self->textStyle(static_cast<uint32>(style)); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
ATTRIBUTES_IFNDEF PDG_NO_GUI CR \
METHOD_IMPL(klass, SetFont) CR \
    try { CR \
    METHOD_SIGNATURE("Sets the font to use for drawing text", [this], 1, ([object Font*] font = null)); CR \
    OPTIONAL_CPP_OBJECT_ARG(1, font, Font, 0); CR \
    self->font(font); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
ATTRIBUTES_ENDIF CR \
METHOD_IMPL(klass, Frame) CR \
    try { CR \
    METHOD_SIGNATURE("Sets which frame of an ImageStrip to draw", [this], 1, ([number int] frame)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, frame); CR \
    self->frame(frame); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, SetFitType) CR \
    try { CR \
    METHOD_SIGNATURE("Sets how an image should be fitted into a target rectangle", [this], 1, ([number int] fit)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, fit); CR \
    self->fitType(static_cast<FitType>(fit)); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, ClipOverflow) CR \
    try { CR \
    METHOD_SIGNATURE("Confine drawing overflow to the operation's bounds.", [this], 1, (boolean clip)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_BOOL_ARG(1, clip); CR \
    self->clipOverflow(clip); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, Subsection) CR \
    try { CR \
    METHOD_SIGNATURE("Sets a subsection of an image to draw", [this], 1, ([object Rect const&] section)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_RECT_ARG(1, section); CR \
    self->subsection(section); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, SphereRotation) CR \
    try { CR \
    METHOD_SIGNATURE("Sets the rotation angle in radians for a textured sphere", [this], 1, ([number float] rotation)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_NUMBER_ARG(1, rotation); CR \
    self->sphereRotation(rotation); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, PolarOffset) CR \
    try { CR \
    METHOD_SIGNATURE("Sets the polar offset for rotating a textured sphere", [this], 1, ([object Offset const&] offset)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_OFFSET_ARG(1, offset); CR \
    self->polarOffset(offset); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, LightOffset) CR \
    try { CR \
    METHOD_SIGNATURE("Sets light source with spherical coordinates in radians", [this], 1, ([object Offset const&] offset)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_OFFSET_ARG(1, offset); CR \
    self->lightOffset(offset); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, AmbientLight) CR \
    try { CR \
    METHOD_SIGNATURE("Set the ambient light.", [this], 1, ({[object Color const&] color|string colorName|number rgba})); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_COLOR_ARG(1, color); CR \
    self->ambientLight(color); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, Texture) CR \
    try { CR \
    METHOD_SIGNATURE("Sets the texture image to use for drawing a sphere", [this], 1, ([object Image*] texture)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, texture, Image); CR \
    self->texture(texture); CR \
    RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, GetTextSize) CR \
    METHOD_SIGNATURE("", [number float], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float size = self->getTextSize(); CR \
    RETURN_NUMBER(size); CR \
    END CR \
METHOD_IMPL(klass, GetTextStyle) CR \
    METHOD_SIGNATURE("", [number int], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    uint32 style = self->getTextStyle(); CR \
    RETURN_NUMBER(style); CR \
    END CR \
ATTRIBUTES_IFNDEF PDG_NO_GUI CR \
METHOD_IMPL(klass, GetFont) CR \
    METHOD_SIGNATURE("", [object Font*], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Font* font = self->getFont(); CR \
    RETURN_CPP_OBJECT(font, Font); CR \
    END CR \
ATTRIBUTES_ENDIF CR \
METHOD_IMPL(klass, GetFrame) CR \
    METHOD_SIGNATURE("", [number int], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    int frame = self->getFrame(); CR \
    RETURN_NUMBER(frame); CR \
    END CR \
METHOD_IMPL(klass, GetFitType) CR \
    METHOD_SIGNATURE("", [number int], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    FitType fit = self->getFitType(); CR \
    RETURN_NUMBER(static_cast<int>(fit)); CR \
    END CR \
METHOD_IMPL(klass, GetClipOverflow) CR \
    METHOD_SIGNATURE("", [boolean], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    bool clip = self->getClipOverflow(); CR \
    RETURN_BOOL(clip); CR \
    END CR \
METHOD_IMPL(klass, GetSubsection) CR \
    METHOD_SIGNATURE("", [object Rect const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Rect section = self->getSubsection(); CR \
    RETURN_RECT(section); CR \
    END CR \
METHOD_IMPL(klass, GetSphereRotation) CR \
    METHOD_SIGNATURE("", [number float], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float rotation = self->getSphereRotation(); CR \
    RETURN_NUMBER(rotation); CR \
    END CR \
METHOD_IMPL(klass, GetPolarOffset) CR \
    METHOD_SIGNATURE("", [object Offset const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Offset offset = const_cast<Offset&>(self->getPolarOffset()); CR \
    RETURN_OFFSET(offset); CR \
    END CR \
METHOD_IMPL(klass, GetLightOffset) CR \
    METHOD_SIGNATURE("", [object Offset const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Offset offset = const_cast<Offset&>(self->getLightOffset()); CR \
    RETURN_OFFSET(offset); CR \
    END CR \
METHOD_IMPL(klass, GetAmbientLight) CR \
    METHOD_SIGNATURE("", [object Color const&], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Color color = const_cast<Color&>(self->getAmbientLight()); CR \
    RETURN_COLOR(color); CR \
    END CR \
METHOD_IMPL(klass, GetTexture) CR \
    METHOD_SIGNATURE("", [object Image*], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Image* texture = self->getTexture(); CR \
    RETURN_CPP_OBJECT(texture, Image); CR \
    END
