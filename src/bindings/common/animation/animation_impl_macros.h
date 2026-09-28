#define HAS_ANIMATED_METHODS(klass) \
    HAS_METHOD(klass, "getBoundingBox", GetBoundingBox) \
    HAS_METHOD(klass, "getRotatedBounds", GetRotatedBounds) \
    HAS_METHOD(klass, "getLocation", GetLocation) \
    HAS_METHOD(klass, "getMovement", GetMovement) \
    HAS_METHOD(klass, "getSize", GetSize) \
    HAS_METHOD(klass, "getWidth", GetWidth) \
    HAS_METHOD(klass, "getHeight", GetHeight) \
    HAS_METHOD(klass, "getScale", GetScale) \
    HAS_METHOD(klass, "getStretching", GetStretching) \
    HAS_METHOD(klass, "getRotation", GetRotation) \
    HAS_METHOD(klass, "getCenterOffset", GetCenterOffset) \
    HAS_METHOD(klass, "getSpin", GetSpin) \
    HAS_METHOD(klass, "setLocation", SetLocation) \
    HAS_METHOD(klass, "moveTo", MoveTo) \
    HAS_METHOD(klass, "moveBy", MoveBy) \
    HAS_METHOD(klass, "setMovement", SetMovement) \
    HAS_METHOD(klass, "changeMovementTo", ChangeMovementTo) \
    HAS_METHOD(klass, "changeMovementBy", ChangeMovementBy) \
    HAS_METHOD(klass, "setSize", SetSize) \
    HAS_METHOD(klass, "changeCenterOffsetTo", ChangeCenterOffsetTo) \
    HAS_METHOD(klass, "changeCenterOffsetBy", ChangeCenterOffsetBy) \
    HAS_METHOD(klass, "setWidth", SetWidth) \
    HAS_METHOD(klass, "setHeight", SetHeight) \
    HAS_METHOD(klass, "setRotation", SetRotation) \
    HAS_METHOD(klass, "setSpin", SetSpin) \
    HAS_METHOD(klass, "setGrowing", SetGrowing) \
    HAS_METHOD(klass, "setStretching", SetStretching) \
    HAS_METHOD(klass, "setScale", SetScale) \
    HAS_METHOD(klass, "changeSpinTo", ChangeSpinTo) \
    HAS_METHOD(klass, "changeSpinBy", ChangeSpinBy) \
    HAS_METHOD(klass, "changeGrowingTo", ChangeGrowingTo) \
    HAS_METHOD(klass, "changeGrowingBy", ChangeGrowingBy) \
    HAS_METHOD(klass, "changeStretchingTo", ChangeStretchingTo) \
    HAS_METHOD(klass, "changeStretchingBy", ChangeStretchingBy) \
    HAS_METHOD(klass, "changeScaleTo", ChangeScaleTo) \
    HAS_METHOD(klass, "changeScaleBy", ChangeScaleBy) \
    HAS_METHOD(klass, "grow", Grow) \
    HAS_METHOD(klass, "stretch", Stretch) \
    HAS_METHOD(klass, "resizeBy", ResizeBy) \
    HAS_METHOD(klass, "resizeTo", ResizeTo) \
    HAS_METHOD(klass, "rotateBy", RotateBy) \
    HAS_METHOD(klass, "rotateTo", RotateTo) \
    HAS_METHOD(klass, "setCenterOffset", SetCenterOffset) \
    HAS_METHOD(klass, "setFlipX", SetFlipX) \
    HAS_METHOD(klass, "setFlipY", SetFlipY) \
    HAS_METHOD(klass, "stopMovement", StopMovement) \
    HAS_METHOD(klass, "stopSpinning", StopSpinning) \
    HAS_METHOD(klass, "stopGrowing", StopGrowing) \
    HAS_METHOD(klass, "stopStretching", StopStretching) \
    HAS_METHOD(klass, "pauseSchedule", PauseSchedule) \
    HAS_METHOD(klass, "resumeSchedule", ResumeSchedule) \
    HAS_METHOD(klass, "cancelSchedule", CancelSchedule) \
    HAS_METHOD(klass, "flipX", FlipX) \
    HAS_METHOD(klass, "flipY", FlipY) \
    HAS_METHOD(klass, "andThen", AndThen) \
    HAS_METHOD(klass, "isFlippedX", IsFlippedX) \
    HAS_METHOD(klass, "isFlippedY", IsFlippedY) \
    HAS_METHOD(klass, "isSchedulePaused", IsSchedulePaused) \
    HAS_METHOD(klass, "hasScheduledAnimations", HasScheduledAnimations) \
    HAS_METHOD(klass, "wait", Wait) \
    HAS_METHOD(klass, "addAnimationHelper", AddAnimationHelper) \
    HAS_METHOD(klass, "removeAnimationHelper", RemoveAnimationHelper) \
    HAS_METHOD(klass, "clearAnimationHelpers", ClearAnimationHelpers)

#define ANIMATED_BASE_CLASS_IMPL(klass) CR \
GETTER_IMPL(klass, BoundingBox, RECT) CR \
GETTER_IMPL(klass, RotatedBounds, ROTATED_RECT) CR \
GETTER_IMPL(klass, Location, POINT) CR \
GETTER_IMPL(klass, Movement, OFFSET) CR \
GETTER_IMPL(klass, Size, OFFSET) CR \
GETTER_IMPL(klass, Width, NUMBER) CR \
GETTER_IMPL(klass, Height, NUMBER) CR \
GETTER_IMPL(klass, Scale, OFFSET) CR \
GETTER_IMPL(klass, Stretching, OFFSET) CR \
GETTER_IMPL(klass, Rotation, NUMBER) CR \
GETTER_IMPL(klass, CenterOffset, OFFSET) CR \
GETTER_IMPL(klass, Spin, NUMBER) CR \
METHOD_IMPL(klass, SetLocation) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 2, ({[object Point] value|number x, number y})); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Point value; CR \
auto isPoint = VALUE_IS_POINT(ARGV[0], value); CR \
if (!isPoint.has_value()) { RETURN_NULL; } CR \
if (*isPoint) { CR \
REQUIRE_ARG_COUNT(1); CR \
self->setLocation(value); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, x); REQUIRE_NUMBER_ARG(2, y); CR \
REQUIRE_ARG_COUNT(2); CR \
self->setLocation(x, y); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, MoveTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, ({[object Point] value|number x, number y}, number durationSeconds = 0, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Point value; CR \
auto isPoint = VALUE_IS_POINT(ARGV[0], value); CR \
if (!isPoint.has_value()) { RETURN_NULL; } CR \
if (*isPoint) { CR \
if (ARGC == 1) { self->moveTo(value); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->moveTo(value, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, x); REQUIRE_NUMBER_ARG(2, y); CR \
if (ARGC == 2) { self->moveTo(x, y); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->moveTo(x, y, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, MoveBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, ({[object Offset] value|number x, number y}, number durationSeconds = 0, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Offset value; CR \
auto converted = VALUE_IS_OFFSET(ARGV[0], value); CR \
if (!converted.has_value()) { RETURN_NULL; } CR \
if (*converted) { CR \
if (ARGC == 1) { self->moveBy(value); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->moveBy(value, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, x); REQUIRE_NUMBER_ARG(2, y); CR \
if (ARGC == 2) { self->moveBy(x, y); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->moveBy(x, y, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetMovement) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 2, ({[object Vector] value|number xPerSecond, number yPerSecond})); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Vector value; CR \
auto converted = VALUE_IS_VECTOR(ARGV[0], value); CR \
if (!converted.has_value()) { RETURN_NULL; } CR \
if (*converted) { CR \
REQUIRE_ARG_COUNT(1); CR \
self->setMovement(value); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, xPerSecond); REQUIRE_NUMBER_ARG(2, yPerSecond); CR \
REQUIRE_ARG_COUNT(2); CR \
self->setMovement(xPerSecond, yPerSecond); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeMovementTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, ({[object Vector] value|number xPerSecond, number yPerSecond}, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Vector value; CR \
auto converted = VALUE_IS_VECTOR(ARGV[0], value); CR \
if (!converted.has_value()) { RETURN_NULL; } CR \
if (*converted) { CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeMovementTo(value, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, xPerSecond); REQUIRE_NUMBER_ARG(2, yPerSecond); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeMovementTo(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeMovementBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, ({[object Vector] value|number xPerSecond, number yPerSecond}, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Vector value; CR \
auto converted = VALUE_IS_VECTOR(ARGV[0], value); CR \
if (!converted.has_value()) { RETURN_NULL; } CR \
if (*converted) { CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeMovementBy(value, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, xPerSecond); REQUIRE_NUMBER_ARG(2, yPerSecond); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeMovementBy(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetSize) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 2, ({[object Offset] value|number width, number height})); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Offset value; CR \
auto converted = VALUE_IS_OFFSET(ARGV[0], value); CR \
if (!converted.has_value()) { RETURN_NULL; } CR \
if (*converted) { CR \
REQUIRE_ARG_COUNT(1); CR \
self->setSize(value); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, width); REQUIRE_NUMBER_ARG(2, height); CR \
REQUIRE_ARG_COUNT(2); CR \
self->setSize(width, height); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeCenterOffsetTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, ({[object Offset] value|number x, number y}, number durationSeconds, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Offset value; CR \
auto converted = VALUE_IS_OFFSET(ARGV[0], value); CR \
if (!converted.has_value()) { RETURN_NULL; } CR \
if (*converted) { CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeCenterOffsetTo(value, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, x); REQUIRE_NUMBER_ARG(2, y); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeCenterOffsetTo(x, y, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeCenterOffsetBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, ({[object Offset] value|number x, number y}, number durationSeconds, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
pdg::Offset value; CR \
auto converted = VALUE_IS_OFFSET(ARGV[0], value); CR \
if (!converted.has_value()) { RETURN_NULL; } CR \
if (*converted) { CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeCenterOffsetBy(value, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} else { CR \
REQUIRE_NUMBER_ARG(1, x); REQUIRE_NUMBER_ARG(2, y); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeCenterOffsetBy(x, y, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetWidth) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (number value)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, value); CR \
REQUIRE_ARG_COUNT(1); CR \
self->setWidth(value); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetHeight) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (number value)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, value); CR \
REQUIRE_ARG_COUNT(1); CR \
self->setHeight(value); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetRotation) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (number value)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, value); CR \
REQUIRE_ARG_COUNT(1); CR \
self->setRotation(value); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetSpin) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (number value)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, value); CR \
REQUIRE_ARG_COUNT(1); CR \
self->setSpin(value); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetGrowing) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (number value)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, value); CR \
REQUIRE_ARG_COUNT(1); CR \
self->setGrowing(value); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetStretching) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 2, (number widthPerSecond, number heightPerSecond)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, widthPerSecond); CR \
REQUIRE_NUMBER_ARG(2, heightPerSecond); CR \
REQUIRE_ARG_COUNT(2); CR \
self->setStretching(widthPerSecond, heightPerSecond); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetScale) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 2, (number x, number y = x)); CR \
REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1, x); OPTIONAL_NUMBER_ARG(2, y, x); CR \
self->setScale(x, y); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeSpinTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 3, (number radiansPerSecond, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, radiansPerSecond); CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeSpinTo(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeSpinBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 3, (number radiansPerSecond, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, radiansPerSecond); CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeSpinBy(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeGrowingTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 3, (number amountPerSecond, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, amountPerSecond); CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeGrowingTo(amountPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeGrowingBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 3, (number amountPerSecond, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, amountPerSecond); CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeGrowingBy(amountPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeStretchingTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number widthPerSecond, number heightPerSecond, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, widthPerSecond); CR \
REQUIRE_NUMBER_ARG(2, heightPerSecond); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeStretchingTo(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeStretchingBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number widthPerSecond, number heightPerSecond, number durationSeconds, [number int] easing = linearTween)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, widthPerSecond); CR \
REQUIRE_NUMBER_ARG(2, heightPerSecond); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::linearTween)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeStretchingBy(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeScaleTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number x, number y, number durationSeconds, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, x); CR \
REQUIRE_NUMBER_ARG(2, y); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeScaleTo(x, y, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ChangeScaleBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number x, number y, number durationSeconds, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, x); CR \
REQUIRE_NUMBER_ARG(2, y); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->changeScaleBy(x, y, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, Grow) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 3, (number factor, number durationSeconds = 0, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, factor); CR \
if (ARGC == 1) { self->grow(factor); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->grow(factor, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, Stretch) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number widthFactor, number heightFactor, number durationSeconds = 0, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, widthFactor); CR \
REQUIRE_NUMBER_ARG(2, heightFactor); CR \
if (ARGC == 2) { self->stretch(widthFactor, heightFactor); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->stretch(widthFactor, heightFactor, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ResizeBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number deltaWidth, number deltaHeight, number durationSeconds = 0, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, deltaWidth); CR \
REQUIRE_NUMBER_ARG(2, deltaHeight); CR \
if (ARGC == 2) { self->resizeBy(deltaWidth, deltaHeight); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->resizeBy(deltaWidth, deltaHeight, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ResizeTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number width, number height, number durationSeconds, [number int] easing = easeInOutQuad)); CR \
REQUIRE_ARG_MIN_COUNT(2); CR \
REQUIRE_NUMBER_ARG(1, width); CR \
REQUIRE_NUMBER_ARG(2, height); CR \
REQUIRE_NUMBER_ARG(3, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(4, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
self->resizeTo(width, height, durationSeconds, gEasingFunctions[easing]); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, RotateBy) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number radians, number durationSeconds = 0, [number int] easing = easeInOutQuad, [number int] direction = rotationDirection_AsSpecified)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, radians); CR \
if (ARGC == 1) { self->rotateBy(radians); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
OPTIONAL_NUMBER_ARG(4, directionValue, static_cast<int>(rotationDirection_AsSpecified)); CR \
if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3) { THROW_RANGE_ERR("Expected an integer rotation direction"); RETURN_NULL; } CR \
const int direction = static_cast<int>(directionValue); CR \
self->rotateBy(radians, durationSeconds, gEasingFunctions[easing], direction); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, RotateTo) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 4, (number radians, number durationSeconds = 0, [number int] easing = easeInOutQuad, [number int] direction = rotationDirection_AsSpecified)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, radians); CR \
if (ARGC == 1) { self->rotateTo(radians); RETURN_THIS; } CR \
REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad)); CR \
if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; } CR \
const int easing = static_cast<int>(easingValue); CR \
if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; } CR \
OPTIONAL_NUMBER_ARG(4, directionValue, static_cast<int>(rotationDirection_AsSpecified)); CR \
if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3) { THROW_RANGE_ERR("Expected an integer rotation direction"); RETURN_NULL; } CR \
const int direction = static_cast<int>(directionValue); CR \
self->rotateTo(radians, durationSeconds, gEasingFunctions[easing], direction); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetCenterOffset) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, ([object Offset] offset)); CR \
REQUIRE_ARG_COUNT(1); REQUIRE_OFFSET_ARG(1, offset); CR \
self->setCenterOffset(offset); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetFlipX) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (boolean flip)); CR \
REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1, flip); CR \
self->setFlipX(flip); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, SetFlipY) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (boolean flip)); CR \
REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1, flip); CR \
self->setFlipY(flip); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, StopMovement) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->stopMovement(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, StopSpinning) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->stopSpinning(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, StopGrowing) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->stopGrowing(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, StopStretching) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->stopStretching(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, PauseSchedule) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->pauseSchedule(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, ResumeSchedule) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->resumeSchedule(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, CancelSchedule) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->cancelSchedule(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, FlipX) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->flipX(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, FlipY) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->flipY(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, AndThen) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
self->andThen(); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, IsFlippedX) CR \
try { CR \
METHOD_SIGNATURE("", boolean, 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
RETURN_BOOL(self->isFlippedX()); CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, IsFlippedY) CR \
try { CR \
METHOD_SIGNATURE("", boolean, 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
RETURN_BOOL(self->isFlippedY()); CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, IsSchedulePaused) CR \
try { CR \
METHOD_SIGNATURE("", boolean, 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
RETURN_BOOL(self->isSchedulePaused()); CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, HasScheduledAnimations) CR \
try { CR \
METHOD_SIGNATURE("", boolean, 0, ()); CR \
REQUIRE_ARG_COUNT(0); CR \
RETURN_BOOL(self->hasScheduledAnimations()); CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, Wait) CR \
try { CR \
METHOD_SIGNATURE("", [object Animated], 1, (number durationSeconds)); CR \
REQUIRE_ARG_MIN_COUNT(1); CR \
REQUIRE_NUMBER_ARG(1, durationSeconds); CR \
REQUIRE_ARG_COUNT(1); CR \
self->wait(durationSeconds); RETURN_THIS; CR \
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
END CR \
METHOD_IMPL(klass, AddAnimationHelper) CR \
    try { CR \
	METHOD_SIGNATURE("", [object Animated], 1, ([object IAnimationHelper] helper)); CR \
	OBJECT_SAVE_WEAK(self->mAnimatedScriptObj, THIS); CR \
    DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], IAnimationHelper); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, helper, IAnimationHelper); CR \
	self->addAnimationHelper(helper); CR \
	RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
	END CR \
METHOD_IMPL(klass, RemoveAnimationHelper) CR \
    try { CR \
	METHOD_SIGNATURE("", [object Animated], 1, ([object IAnimationHelper] helper)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_CPP_OBJECT_ARG(1, helper, IAnimationHelper); CR \
	self->removeAnimationHelper(helper); CR \
	RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
	END CR \
METHOD_IMPL(klass, ClearAnimationHelpers) CR \
    try { CR \
	METHOD_SIGNATURE("", [object Animated], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->clearAnimationHelpers(); CR \
	RETURN_THIS; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
	END CR

#define HAS_SPRITE_LAYER_METHODS(klass) \
    HAS_METHOD(klass, "createParticle", CreateParticle) \
    HAS_METHOD(klass, "addParticle", AddParticle) \
    HAS_METHOD(klass, "removeParticle", RemoveParticle) \
    HAS_METHOD(klass, "removeAllParticles", RemoveAllParticles) \
    HAS_METHOD(klass, "getParticleCount", GetParticleCount) \
    HAS_METHOD(klass, "getNthParticle", GetNthParticle) \
    HAS_METHOD(klass, "setMaxParticles", SetMaxParticles) \
    HAS_METHOD(klass, "getMaxParticles", GetMaxParticles) \
    HAS_METHOD(klass, "createParticleEmitter", CreateParticleEmitter) \
    HAS_METHOD(klass, "removeParticleEmitter", RemoveParticleEmitter) \
    HAS_METHOD(klass, "removeAllParticleEmitters", RemoveAllParticleEmitters) \
	HAS_METHOD(klass, "setSerializationFlags", SetSerializationFlags) \
	HAS_METHOD(klass, "startAnimations", StartAnimations)  \
	HAS_METHOD(klass, "stopAnimations", StopAnimations)  \
	HAS_METHOD(klass, "hide", Hide)  \
	HAS_METHOD(klass, "show", Show)  \
	HAS_METHOD(klass, "isHidden", IsHidden)  \
	HAS_METHOD(klass, "fadeIn", FadeIn)  \
	HAS_METHOD(klass, "fadeOut", FadeOut)  \
	HAS_METHOD(klass, "moveBehind", MoveBehind)  \
	HAS_METHOD(klass, "moveInFrontOf", MoveInFrontOf)  \
	HAS_METHOD(klass, "moveToFront", MoveToFront)  \
	HAS_METHOD(klass, "moveToBack", MoveToBack)  \
	HAS_METHOD(klass, "getZOrder", GetZOrder)  \
	HAS_METHOD(klass, "moveWith", MoveWith)  \
	HAS_METHOD(klass, "findSprite", FindSprite)  \
	HAS_METHOD(klass, "getNthSprite", GetNthSprite)  \
	HAS_METHOD(klass, "getSpriteZOrder", GetSpriteZOrder)  \
	HAS_METHOD(klass, "isSpriteBehind", IsSpriteBehind)  \
	HAS_METHOD(klass, "hasSprite", HasSprite)  \
	HAS_METHOD(klass, "addSprite", AddSprite)  \
	HAS_METHOD(klass, "removeSprite", RemoveSprite)  \
	HAS_METHOD(klass, "removeAllSprites", RemoveAllSprites)  \
	HAS_METHOD(klass, "enableCollisions", EnableCollisions)  \
	HAS_METHOD(klass, "disableCollisions", DisableCollisions)  \
	HAS_METHOD(klass, "enableCollisionsWithLayer", EnableCollisionsWithLayer)  \
	HAS_METHOD(klass, "disableCollisionsWithLayer", DisableCollisionsWithLayer)  \
	HAS_METHOD(klass, "createSprite", CreateSprite)  \

#define HAS_SPRITE_LAYER_GUI_METHODS(klass) \
	HAS_METHOD(klass, "getSpritePort", GetSpritePort)  \
	HAS_METHOD(klass, "setSpritePort", SetSpritePort)  \
	HAS_METHOD(klass, "setOrigin", SetOrigin)  \
	HAS_METHOD(klass, "getOrigin", GetOrigin)  \
	HAS_METHOD(klass, "setAutoCenter", SetAutoCenter)  \
	HAS_METHOD(klass, "setFixedMoveAxis", SetFixedMoveAxis)  \
	HAS_METHOD(klass, "setZoom", SetZoom)  \
	HAS_METHOD(klass, "getZoom", GetZoom)  \
	HAS_METHOD(klass, "zoomTo", ZoomTo)  \
	HAS_METHOD(klass, "zoom", Zoom)  \
	HAS_METHOD(klass, "layerToPortPoint", LayerToPortPoint)  \
	HAS_METHOD(klass, "layerToPortOffset", LayerToPortOffset)  \
	HAS_METHOD(klass, "layerToPortVector", LayerToPortVector)  \
	HAS_METHOD(klass, "layerToPortRect", LayerToPortRect)  \
	HAS_METHOD(klass, "layerToPortQuad", LayerToPortQuad)  \
	HAS_METHOD(klass, "portToLayerPoint", PortToLayerPoint)  \
	HAS_METHOD(klass, "portToLayerOffset", PortToLayerOffset)  \
	HAS_METHOD(klass, "portToLayerVector", PortToLayerVector)  \
	HAS_METHOD(klass, "portToLayerRect", PortToLayerRect)  \
	HAS_METHOD(klass, "portToLayerQuad", PortToLayerQuad)  \

#define HAS_SPRITE_LAYER_CHIPMUNK_METHODS(klass) \
	HAS_METHOD(klass, "setGravity", SetGravity)  \
	HAS_METHOD(klass, "setUseChipmunkPhysics", SetUseChipmunkPhysics)  \
	HAS_METHOD(klass, "setStaticLayer", SetStaticLayer)  \
	HAS_METHOD(klass, "setKeepGravityDownward", SetKeepGravityDownward)  \
	HAS_METHOD(klass, "setDamping", SetDamping)  \
	HAS_METHOD(klass, "getSpace", GetSpace)  \

#define SPRITE_LAYER_BASE_CLASS_GUI_IMPL(klass) CR \
METHOD_IMPL(klass, GetSpritePort) CR \
	METHOD_SIGNATURE("", [object Port], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	Port* port = self->getSpritePort(); CR \
	RETURN_CPP_OBJECT(port, Port); CR \
	END CR \
METHOD_IMPL(klass, SetSpritePort) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object Port] port)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, port, Port); CR \
	self->setSpritePort(port); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, SetOrigin) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object Point] origin)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_POINT_ARG(1, origin); CR \
	self->setOrigin(origin); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, GetOrigin) CR \
	METHOD_SIGNATURE("get the point in the layer that is drawn at 0,0 in the port", [object Point], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    Point p = self->getOrigin(); CR \
	RETURN( POINT2VAL(p) ); CR \
	END CR \
METHOD_IMPL(klass, SetAutoCenter) CR \
	METHOD_SIGNATURE("", undefined, 1, (boolean autoCenter = true)); CR \
    OPTIONAL_BOOL_ARG(1, autoCenter, true); CR \
	self->setAutoCenter(autoCenter); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, SetFixedMoveAxis) CR \
	METHOD_SIGNATURE("", undefined, 1, (boolean fixedAxis = true)); CR \
    OPTIONAL_BOOL_ARG(1, fixedAxis, true); CR \
    self->setFixedMoveAxis(fixedAxis); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, SetZoom) CR \
	METHOD_SIGNATURE("", undefined, 1, (number zoomLevel)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, zoomLevel); CR \
	self->setZoom(zoomLevel); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, GetZoom) CR \
	METHOD_SIGNATURE("get the current zoom factor", number, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    float zoom = self->getZoom(); CR \
	RETURN_NUMBER(zoom); CR \
	END CR \
METHOD_IMPL(klass, ZoomTo) CR \
	METHOD_SIGNATURE("", undefined, 5, (number zoomLevel, number durationSeconds, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) )); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, zoomLevel); CR \
	REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad); CR \
	OPTIONAL_RECT_ARG(4, keepInRect, pdg::Rect(0,0)); CR \
    OPTIONAL_POINT_ARG(5, centerOn, pdg::Point(0,0)); CR \
    pdg::Point* centerOnPtr = (ARGC >= 5) ? &centerOn : 0; CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->zoomTo(zoomLevel, durationSeconds, gEasingFunctions[easing], keepInRect, centerOnPtr); CR \
    } else { CR \
		self->zoomTo(zoomLevel, durationSeconds); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, Zoom) CR \
	METHOD_SIGNATURE("", undefined, 5, (number deltaZoomLevel, number durationSeconds, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) )); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, deltaZoomLevel); CR \
	REQUIRE_NUMBER_ARG(2, durationSeconds); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad); CR \
	OPTIONAL_RECT_ARG(4, keepInRect, pdg::Rect(0,0)); CR \
    OPTIONAL_POINT_ARG(5, centerOn, pdg::Point(0,0)); CR \
    pdg::Point* centerOnPtr = (ARGC >= 5) ? &centerOn : 0; CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->zoom(deltaZoomLevel, durationSeconds, gEasingFunctions[easing], keepInRect, centerOnPtr); CR \
    } else { CR \
		self->zoom(deltaZoomLevel, durationSeconds); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, LayerToPortPoint) CR \
	METHOD_SIGNATURE("", [object Point], 1, ([object Point] p)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_POINT_ARG(1, p); CR \
    Point out = self->layerToPort(p); CR \
	RETURN( POINT2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, LayerToPortOffset) CR \
	METHOD_SIGNATURE("", [object Offset], 1, ([object Offset] o)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_OFFSET_ARG(1, o); CR \
    Offset out = self->layerToPort(o); CR \
	RETURN( OFFSET2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, LayerToPortVector) CR \
	METHOD_SIGNATURE("", [object Vector], 1, ([object Vector] v)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_VECTOR_ARG(1, v); CR \
    Vector out = self->layerToPort(v); CR \
	RETURN( VECTOR2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, LayerToPortRect) CR \
	METHOD_SIGNATURE("", [object RotatedRect], 1, ([object Rect] r)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_ROTATED_RECT_ARG(1, r); CR \
    RotatedRect out = self->layerToPort(r); CR \
	RETURN( RECT2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, LayerToPortQuad) CR \
	METHOD_SIGNATURE("", [object Quad], 1, ([object Quad] q)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_QUAD_ARG(1, q); CR \
    Quad out = self->layerToPort(q); CR \
	RETURN( QUAD2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, PortToLayerPoint) CR \
	METHOD_SIGNATURE("", [object Point], 1, ([object Point] p)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_POINT_ARG(1, p); CR \
    Point out = self->portToLayer(p); CR \
	RETURN( POINT2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, PortToLayerOffset) CR \
	METHOD_SIGNATURE("", [object Offset], 1, ([object Offset] o)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_OFFSET_ARG(1, o); CR \
    Offset out = self->portToLayer(o); CR \
	RETURN( OFFSET2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, PortToLayerVector) CR \
	METHOD_SIGNATURE("", [object Vector], 1, ([object Vector] v)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_VECTOR_ARG(1, v); CR \
    Vector out = self->portToLayer(v); CR \
	RETURN( VECTOR2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, PortToLayerRect) CR \
	METHOD_SIGNATURE("", [object RotatedRect], 1, ([object Rect] r)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_ROTATED_RECT_ARG(1, r); CR \
    RotatedRect out = self->portToLayer(r); CR \
	RETURN( RECT2VAL(out) ); CR \
	END CR \
METHOD_IMPL(klass, PortToLayerQuad) CR \
	METHOD_SIGNATURE("", [object Quad], 1, ([object Quad] q)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_QUAD_ARG(1, q); CR \
    Quad out = self->portToLayer(q); CR \
	RETURN( QUAD2VAL(out) ); CR \
	END

#define SPRITE_LAYER_BASE_CLASS_IMPL(klass) CR \
METHOD_IMPL(klass, CreateParticle) CR \
    METHOD_SIGNATURE("", [object Particle], 0, ()); CR \
    try { REQUIRE_ARG_COUNT(0); auto* result=self->createParticle(); RETURN_CPP_OBJECT(result,Particle); } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, AddParticle) CR \
    METHOD_SIGNATURE("", undefined, 1, ([object Particle] value)); CR \
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,value,Particle); self->addParticle(value); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, RemoveParticle) CR \
    METHOD_SIGNATURE("", undefined, 1, ([object Particle] value)); CR \
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,value,Particle); self->removeParticle(value); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, RemoveAllParticles) CR \
    METHOD_SIGNATURE("", undefined, 0, ()); CR \
    try { REQUIRE_ARG_COUNT(0); self->removeAllParticles(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, GetParticleCount) CR \
    METHOD_SIGNATURE("", [number uint], 0, ()); CR \
    try { REQUIRE_ARG_COUNT(0); RETURN_UINT32(self->getParticleCount()); } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, GetNthParticle) CR \
    METHOD_SIGNATURE("", [object Particle], 1, ([number uint] value)); CR \
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if (!std::isfinite(value) || value < 0 || value > UINT32_MAX || std::floor(value)!=value) throw std::invalid_argument("Expected a particle count or index"); auto* result=self->getNthParticle(static_cast<uint32_t>(value)); RETURN_CPP_OBJECT(result,Particle); } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, SetMaxParticles) CR \
    METHOD_SIGNATURE("", [object SpriteLayer], 1, ([number uint] value)); CR \
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if (!std::isfinite(value) || value < 0 || value > UINT32_MAX || std::floor(value)!=value) throw std::invalid_argument("Expected a particle count or index"); self->setMaxParticles(static_cast<uint32_t>(value)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, GetMaxParticles) CR \
    METHOD_SIGNATURE("", [number uint], 0, ()); CR \
    try { REQUIRE_ARG_COUNT(0); RETURN_UINT32(self->getMaxParticles()); } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, CreateParticleEmitter) CR \
    METHOD_SIGNATURE("", [object ParticleEmitter], 0, ()); CR \
    try { REQUIRE_ARG_COUNT(0); auto* result=self->createParticleEmitter(); RETURN_CPP_OBJECT(result,ParticleEmitter); } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, RemoveParticleEmitter) CR \
    METHOD_SIGNATURE("", undefined, 1, ([object ParticleEmitter] value)); CR \
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,value,ParticleEmitter); self->removeParticleEmitter(value); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, RemoveAllParticleEmitters) CR \
    METHOD_SIGNATURE("", undefined, 0, ()); CR \
    try { REQUIRE_ARG_COUNT(0); self->removeAllParticleEmitters(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); } CR \
    END CR \
METHOD_IMPL(klass, SetSerializationFlags) CR \
	METHOD_SIGNATURE("", [object SpriteLayer], 0, ([number uint] flags)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_UINT32_ARG(1, flags); CR \
	self->setSerializationFlags(flags); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, StartAnimations) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->startAnimations(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, StopAnimations) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->stopAnimations(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, Hide) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    self->hide(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, Show) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->show(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, IsHidden) CR \
	METHOD_SIGNATURE("", boolean, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    bool hidden = self->isHidden(); CR \
	RETURN_BOOL(hidden); CR \
	END CR \
METHOD_IMPL(klass, FadeIn) CR \
	METHOD_SIGNATURE("", undefined, 2, (number durationSeconds, [number int] easing = linearTween)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, durationSeconds); CR \
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween); CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->fadeIn(durationSeconds, gEasingFunctions[easing]); CR \
    } else { CR \
		self->fadeIn(durationSeconds); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, FadeOut) CR \
	METHOD_SIGNATURE("", undefined, 2, (number durationSeconds, [number int] easing = linearTween)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, durationSeconds); CR \
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween); CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->fadeOut(durationSeconds, gEasingFunctions[easing]); CR \
    } else { CR \
		self->fadeOut(durationSeconds); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, MoveBehind) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object SpriteLayer] layer)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); CR \
	self->moveBehind(layer); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, MoveInFrontOf) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object SpriteLayer] layer)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); CR \
	self->moveInFrontOf(layer); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, MoveToFront) CR \
	METHOD_SIGNATURE("move this layer in front of all other layers", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->moveToFront(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, MoveToBack) CR \
	METHOD_SIGNATURE("move this layer behind all other layers", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->moveToBack(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, MoveWith) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object SpriteLayer] layer, number moveRatio = 1.0, number zoomRatio = 1.0 )); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); CR \
	OPTIONAL_NUMBER_ARG(2, moveRatio, 1.0f); CR \
	OPTIONAL_NUMBER_ARG(3, zoomRatio, 1.0f); CR \
	self->moveWith(layer, moveRatio, zoomRatio); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, IsSpriteBehind) CR \
	METHOD_SIGNATURE("", boolean, 2, ([object Sprite] sprite, [object Sprite] otherSprite)); CR \
    REQUIRE_ARG_COUNT(2); CR \
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite); CR \
    REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite); CR \
	bool behind = self->isSpriteBehind(sprite, otherSprite); CR \
	RETURN_BOOL(behind); CR \
	END CR \
METHOD_IMPL(klass, GetZOrder) CR \
	METHOD_SIGNATURE("", [number int], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	int zorder = self->getZOrder(); CR \
	RETURN_INTEGER(zorder); CR \
	END CR \
METHOD_IMPL(klass, GetSpriteZOrder) CR \
	METHOD_SIGNATURE("", [number int], 0, ([object Sprite] sprite)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite); CR \
	int zorder = self->getSpriteZOrder(sprite); CR \
	RETURN_INTEGER(zorder); CR \
	END CR \
METHOD_IMPL(klass, FindSprite) CR \
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] id)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_INT32_ARG(1, id); CR \
	Sprite* sprite = self->findSprite(id); CR \
	RETURN_CPP_OBJECT(sprite, Sprite); CR \
	END CR \
METHOD_IMPL(klass, GetNthSprite) CR \
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] index)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_INT32_ARG(1, index); CR \
	Sprite* sprite = self->getNthSprite(index); CR \
	RETURN_CPP_OBJECT(sprite, Sprite); CR \
	END CR \
METHOD_IMPL(klass, HasSprite) CR \
	METHOD_SIGNATURE("", boolean, 1, ([object Sprite] sprite)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite); CR \
	bool found = self->hasSprite(sprite); CR \
	RETURN_BOOL(found); CR \
	END CR \
METHOD_IMPL(klass, AddSprite) CR \
    try { CR \
	METHOD_SIGNATURE("", undefined, 1, ([object Sprite] newSprite)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, newSprite, Sprite); CR \
	self->addSprite(newSprite); CR \
	NO_RETURN; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
	END CR \
METHOD_IMPL(klass, RemoveSprite) CR \
    try { CR \
	METHOD_SIGNATURE("", undefined, 1, ([object Sprite] oldSprite)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, oldSprite, Sprite); CR \
    self->removeSprite(oldSprite); CR \
	NO_RETURN; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
	END CR \
METHOD_IMPL(klass, RemoveAllSprites) CR \
    try { CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->removeAllSprites(); CR \
	NO_RETURN; CR \
    } catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); } CR \
	END CR \
METHOD_IMPL(klass, EnableCollisions) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->enableCollisions(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, DisableCollisions) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->disableCollisions(); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, EnableCollisionsWithLayer) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object SpriteLayer] otherLayer)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, otherLayer, SpriteLayer); CR \
	self->enableCollisionsWithLayer(otherLayer); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, DisableCollisionsWithLayer) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object SpriteLayer] otherLayer)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, otherLayer, SpriteLayer); CR \
	self->disableCollisionsWithLayer(otherLayer); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, CreateSprite) CR \
	METHOD_SIGNATURE("", [object Sprite], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	Sprite* sprite = self->createSprite(); CR \
	RETURN_CPP_OBJECT(sprite, Sprite); CR \
	END CR \

#define SPRITE_LAYER_CHIPMUNK_IMPL(klass) CR \
METHOD_IMPL(klass, SetKeepGravityDownward) CR \
	METHOD_SIGNATURE("", undefined, 1, (boolean keepItDownward = true)); CR \
    OPTIONAL_BOOL_ARG(1, keepItDownward, true); CR \
    self->setKeepGravityDownward(keepItDownward); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, SetGravity) CR \
	METHOD_SIGNATURE("", undefined, 2, (number gravity, boolean keepItDownward = true)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, gravity); CR \
    OPTIONAL_BOOL_ARG(2, keepItDownward, true); CR \
    self->setGravity(gravity, keepItDownward); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, SetDamping) CR \
	METHOD_SIGNATURE("", undefined, 1, (number damping)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, damping); CR \
	self->setDamping(damping); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, SetStaticLayer) CR \
	METHOD_SIGNATURE("", undefined, 1, (boolean isStatic = true)); CR \
    OPTIONAL_BOOL_ARG(1, isStatic, true); CR \
    self->setStaticLayer(isStatic); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, SetUseChipmunkPhysics) CR \
	METHOD_SIGNATURE("", undefined, 1, (boolean useIt = true)); CR \
    OPTIONAL_BOOL_ARG(1, useIt, true); CR \
    self->setUseChipmunkPhysics(useIt); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, GetSpace) CR \
	METHOD_SIGNATURE("", [object CpSpace], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	cpSpace* space = self->getSpace(); CR \
	RETURN_NEW_CPP_OBJECT(space, cpSpace); CR \
	END CR \

