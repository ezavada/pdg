#define HAS_ANIMATED_METHODS(klass) \
	HAS_GETTER(klass, BoundingBox)  \
	HAS_GETTER(klass, RotatedBounds)  \
	HAS_PROPERTY(klass, Location)  \
	HAS_PROPERTY(klass, Speed)  \
	HAS_PROPERTY(klass, Velocity)  \
	HAS_PROPERTY(klass, Width)  \
	HAS_PROPERTY(klass, Height)  \
	HAS_PROPERTY(klass, Rotation)  \
	HAS_PROPERTY(klass, CenterOffset)  \
	HAS_PROPERTY(klass, Spin)  \
	HAS_PROPERTY(klass, Mass)  \
	HAS_PROPERTY(klass, MoveFriction)  \
	HAS_PROPERTY(klass, SpinFriction)  \
	HAS_PROPERTY(klass, SizeFriction)  \
	HAS_METHOD(klass, "move", Move)  \
	HAS_METHOD(klass, "moveTo", MoveTo)  \
	HAS_METHOD(klass, "setVelocityInRadians", SetVelocityInRadians)  \
	HAS_METHOD(klass, "getMovementDirectionInRadians", GetMovementDirectionInRadians)  \
	HAS_METHOD(klass, "stopMoving", StopMoving)  \
	HAS_METHOD(klass, "accelerate", Accelerate)  \
	HAS_METHOD(klass, "accelerateTo", AccelerateTo)  \
	HAS_METHOD(klass, "setSize", SetSize)  \
	HAS_METHOD(klass, "grow", Grow)  \
	HAS_METHOD(klass, "stretch", Stretch)  \
	HAS_METHOD(klass, "startGrowing", StartGrowing)  \
	HAS_METHOD(klass, "stopGrowing", StopGrowing)  \
	HAS_METHOD(klass, "startStretching", StartStretching)  \
	HAS_METHOD(klass, "stopStretching", StopStretching)  \
	HAS_METHOD(klass, "resize", Resize)  \
	HAS_METHOD(klass, "resizeTo", ResizeTo)  \
	HAS_METHOD(klass, "setFlipX", SetFlipX)  \
	HAS_METHOD(klass, "setFlipY", SetFlipY)  \
	HAS_METHOD(klass, "flipX", FlipX)  \
	HAS_METHOD(klass, "flipY", FlipY)  \
	HAS_METHOD(klass, "isFlippedX", IsFlippedX)  \
	HAS_METHOD(klass, "isFlippedY", IsFlippedY)  \
	HAS_METHOD(klass, "rotate", Rotate)  \
	HAS_METHOD(klass, "rotateTo", RotateTo)  \
	HAS_METHOD(klass, "stopSpinning", StopSpinning)  \
	HAS_METHOD(klass, "changeCenter", ChangeCenter)  \
	HAS_METHOD(klass, "changeCenterTo", ChangeCenterTo)  \
	HAS_METHOD(klass, "wait", Wait)  \
	HAS_METHOD(klass, "setFriction", SetFriction)  \
	HAS_METHOD(klass, "applyForce", ApplyForce)  \
	HAS_METHOD(klass, "applyTorque", ApplyTorque)  \
	HAS_METHOD(klass, "stopAllForces", StopAllForces)  \
	HAS_METHOD(klass, "addAnimationHelper", AddAnimationHelper)  \
	HAS_METHOD(klass, "removeAnimationHelper", RemoveAnimationHelper)  \
	HAS_METHOD(klass, "clearAnimationHelpers", ClearAnimationHelpers)


#define ANIMATED_BASE_CLASS_IMPL(klass) CR \
PROPERTY_IMPL(klass, Location, POINT) CR \
PROPERTY_IMPL(klass, Speed, NUMBER) CR \
PROPERTY_IMPL(klass, Width, NUMBER) CR \
PROPERTY_IMPL(klass, Height, NUMBER) CR \
SETTER_IMPL(klass, FlipX, BOOL) CR \
SETTER_IMPL(klass, FlipY, BOOL) CR \
PROPERTY_IMPL(klass, Rotation, NUMBER) CR \
PROPERTY_IMPL(klass, CenterOffset, OFFSET) CR \
PROPERTY_IMPL(klass, Spin, NUMBER) CR \
PROPERTY_IMPL(klass, Mass, NUMBER) CR \
PROPERTY_IMPL(klass, MoveFriction, NUMBER) CR \
PROPERTY_IMPL(klass, SpinFriction, NUMBER) CR \
PROPERTY_IMPL(klass, SizeFriction, NUMBER) CR \
METHOD_IMPL(klass, GetBoundingBox) CR \
 	METHOD_SIGNATURE("", [object Rect], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    pdg::Rect r = self->getBoundingBox(); CR \
	RETURN( RECT2VAL(r) ); CR \
	END CR \
METHOD_IMPL(klass, GetRotatedBounds) CR \
 	METHOD_SIGNATURE("", [object RotatedRect], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
    pdg::RotatedRect r = self->getRotatedBounds(); CR \
	RETURN( RECT2VAL(r) ); CR \
	END CR \
METHOD_IMPL(klass, Move) CR \
 	METHOD_SIGNATURE("", undefined, 4, ([object Offset] delta, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	pdg::Offset delta; CR \
	int32 msDuration; CR \
	int easing; CR \
	if (VALUE_IS_OFFSET(ARGV[0])) { CR \
		delta = VAL2OFFSET(ARGV[0]); CR \
		OPTIONAL_INT32_ARG(2, msDuration_2, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(3, easing_3, EasingFuncRef::easeInOutQuad); CR \
		msDuration = msDuration_2; CR \
		easing = easing_3; CR \
    } else { CR \
		REQUIRE_NUMBER_ARG(1, deltaX); CR \
		REQUIRE_NUMBER_ARG(2, deltaY); CR \
		delta.x = deltaX; CR \
		delta.y = deltaY; CR \
		OPTIONAL_INT32_ARG(3, msDuration_3, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(4, easing_4, EasingFuncRef::easeInOutQuad); CR \
		msDuration = msDuration_3; CR \
		easing = easing_4; CR \
    } CR \
    if (msDuration || self->mDelayMs) { CR \
    	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    		self->move(delta, msDuration, gEasingFunctions[easing]); CR \
    	} else { CR \
    		self->move(delta, msDuration); CR \
    	} CR \
    } else { CR \
    	self->move(delta); CR \
    } CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, MoveTo) CR \
 	METHOD_SIGNATURE("", undefined, 4, ([object Point] where, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	pdg::Point where; CR \
	int32 msDuration; CR \
	int easing; CR \
	if (VALUE_IS_POINT(ARGV[0])) {  CR \
		where = VAL2POINT(ARGV[0]); CR \
		OPTIONAL_INT32_ARG(2, msDuration_2, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(3, easing_3, EasingFuncRef::easeInOutQuad); CR \
		easing = easing_3; CR \
		msDuration = msDuration_2; CR \
    } else { CR \
		REQUIRE_NUMBER_ARG(1, x); CR \
		REQUIRE_NUMBER_ARG(2, y); CR \
		where.x = x; CR \
		where.y = y; CR \
		OPTIONAL_INT32_ARG(3, msDuration3, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(4, easing_4, EasingFuncRef::easeInOutQuad); CR \
		easing = easing_4; CR \
		msDuration = msDuration3; CR \
    } CR \
    if (msDuration || self->mDelayMs) { CR \
    	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    		self->moveTo(where, msDuration, gEasingFunctions[easing]); CR \
    	} else { CR \
    		self->moveTo(where, msDuration); CR \
    	} CR \
    } else { CR \
    	self->moveTo(where); CR \
    } CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, SetVelocityInRadians) CR \
 	METHOD_SIGNATURE("", [object Animated], 2, (number speed, number direction)); CR \
    REQUIRE_ARG_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, speed); CR \
	REQUIRE_NUMBER_ARG(2, direction); CR \
	self->setVelocityInRadians(speed, direction); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, GetMovementDirectionInRadians) CR \
 	METHOD_SIGNATURE("", number, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	float dir = self->getMovementDirectionInRadians(); CR \
	RETURN_NUMBER(dir); CR \
	END CR \
METHOD_IMPL(klass, SetVelocity) CR \
 	METHOD_SIGNATURE("", [object Animated], 2, ({[object Vector] deltaPerSec|number deltaXPerSec, number deltaYPerSec})); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	pdg::Vector deltaPerSec; CR \
	if (VALUE_IS_VECTOR(ARGV[0])) { CR \
		deltaPerSec = VAL2VECTOR(ARGV[0]);  CR \
		self->setVelocity(deltaPerSec); CR \
    } else { CR \
		REQUIRE_NUMBER_ARG(1, deltaXPerSec); CR \
		REQUIRE_NUMBER_ARG(2, deltaYPerSec); CR \
		self->setVelocity(Vector(deltaXPerSec, deltaYPerSec)); CR \
    } CR \
	RETURN_THIS; CR \
	END CR \
GETTER_IMPL(klass, Velocity, VECTOR) CR \
METHOD_IMPL(klass, StopMoving) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->stopMoving(); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, Accelerate) CR \
 	METHOD_SIGNATURE("", undefined, 3, (number deltaSpeed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween)); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, deltaSpeed); CR \
	OPTIONAL_INT32_ARG(2, msDuration, duration_Instantaneous); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::linearTween); CR \
	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
		self->accelerate(deltaSpeed, msDuration, gEasingFunctions[easing]); CR \
	} else { CR \
		self->accelerate(deltaSpeed, msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, AccelerateTo) CR \
 	METHOD_SIGNATURE("", undefined, 3, (number speed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween)); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, speed); CR \
	OPTIONAL_INT32_ARG(2, msDuration, duration_Instantaneous); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::linearTween); CR \
	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
		self->accelerateTo(speed, msDuration, gEasingFunctions[easing]); CR \
	} else { CR \
		self->accelerateTo(speed, msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, SetSize) CR \
 	METHOD_SIGNATURE("", [object Animated], 2, (number width, number height)); CR \
    REQUIRE_ARG_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, width); CR \
	REQUIRE_NUMBER_ARG(2, height); CR \
	self->setSize(width, height); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, Grow) CR \
 	METHOD_SIGNATURE("", undefined, 3, (number factor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, factor); CR \
	OPTIONAL_INT32_ARG(2, msDuration, duration_Instantaneous); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad); CR \
	if (msDuration == 0) { CR \
		self->grow(factor); CR \
	} else { CR \
    	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    		self->grow(factor, msDuration, gEasingFunctions[easing]); CR \
    	} else { CR \
			self->grow(factor, msDuration); CR \
		} CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, Stretch) CR \
 	METHOD_SIGNATURE("", undefined, 4, (number widthFactor, number heightFactor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
    REQUIRE_NUMBER_ARG(1, widthFactor); CR \
	REQUIRE_NUMBER_ARG(2, heightFactor); CR \
	OPTIONAL_INT32_ARG(3, msDuration, 0); CR \
	OPTIONAL_INT32_ARG(4, easing, EasingFuncRef::easeInOutQuad); CR \
	if (msDuration == 0) { CR \
		self->stretch(widthFactor, heightFactor); CR \
	} else { CR \
    	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    		self->stretch(widthFactor, heightFactor, msDuration, gEasingFunctions[easing]); CR \
    	} else { CR \
			self->stretch(widthFactor, heightFactor, msDuration); CR \
		} CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, StartGrowing) CR \
	METHOD_SIGNATURE("", undefined, 1, (number amountPerSecond)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, amountPerSecond); CR \
	self->startGrowing(amountPerSecond); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, StopGrowing) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->stopGrowing(); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, StartStretching) CR \
 	METHOD_SIGNATURE("", undefined, 2, (number widthPerSecond, number heightPerSecond)); CR \
    REQUIRE_ARG_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, widthPerSecond); CR \
	REQUIRE_NUMBER_ARG(2, heightPerSecond); CR \
	self->startStretching(widthPerSecond, heightPerSecond); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, StopStretching) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->stopStretching(); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, Resize) CR \
 	METHOD_SIGNATURE("", undefined, 4, (number deltaWidth, number deltaHeight, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(3); CR \
	REQUIRE_NUMBER_ARG(1, deltaWidth); CR \
	REQUIRE_NUMBER_ARG(2, deltaHeight); CR \
	OPTIONAL_INT32_ARG(3, msDuration, duration_Instantaneous); CR \
	OPTIONAL_INT32_ARG(4, easing, EasingFuncRef::easeInOutQuad); CR \
	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
		self->resize(deltaWidth, deltaHeight, msDuration, gEasingFunctions[easing]); CR \
	} else { CR \
		self->resize(deltaWidth, deltaHeight, msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, ResizeTo) CR \
 	METHOD_SIGNATURE("", undefined, 4, (number width, number height, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(3); CR \
	REQUIRE_NUMBER_ARG(1, width); CR \
	REQUIRE_NUMBER_ARG(2, height); CR \
	OPTIONAL_INT32_ARG(3, msDuration, duration_Instantaneous); CR \
	OPTIONAL_INT32_ARG(4, easing, EasingFuncRef::easeInOutQuad); CR \
	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
		self->resizeTo(width, height, msDuration, gEasingFunctions[easing]); CR \
	} else { CR \
		self->resizeTo(width, height, msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, FlipX) CR \
	METHOD_SIGNATURE("flips the object horizontally, center offset is flipped too. Applied before other transformations.", [object Animated], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->flipX(); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, FlipY) CR \
	METHOD_SIGNATURE("flips the object vertically, center offset is flipped too. Applied before other transformations.", [object Animated], 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->flipY(); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, IsFlippedX) CR \
	METHOD_SIGNATURE("returns true if the object is flipped horizontally", boolean, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	C_BOOL theFlipX = self->isFlippedX(); CR \
	RETURN_BOOL(theFlipX); CR \
	END CR \
METHOD_IMPL(klass, IsFlippedY) CR \
	METHOD_SIGNATURE("returns true if the object is flipped vertically", boolean, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	C_BOOL theFlipY = self->isFlippedY(); CR \
	RETURN_BOOL(theFlipY); CR \
	END CR \
METHOD_IMPL(klass, Rotate) CR \
 	METHOD_SIGNATURE("", undefined, 3, (number radians, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, radians); CR \
	OPTIONAL_INT32_ARG(2, msDuration, 0); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad); CR \
	if (msDuration == 0) { CR \
		self->rotate(radians); CR \
	} else { CR \
    	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    		self->rotate(radians, msDuration, gEasingFunctions[easing]); CR \
    	} else { CR \
			self->rotate(radians, msDuration); CR \
		} CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, RotateTo) CR \
 	METHOD_SIGNATURE("", undefined, 4, (number radiansRotation, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, radiansRotation); CR \
	OPTIONAL_INT32_ARG(2, msDuration, duration_Instantaneous); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad); CR \
	if (msDuration == 0) { CR \
		self->rotateTo(radiansRotation); CR \
	} else { CR \
    	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    		self->rotateTo(radiansRotation, msDuration, gEasingFunctions[easing]); CR \
    	} else { CR \
			self->rotateTo(radiansRotation, msDuration); CR \
		} CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, StopSpinning) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->stopSpinning(); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, ChangeCenter) CR \
 	METHOD_SIGNATURE("", undefined, 3, ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	pdg::Offset offset; CR \
	int32 msDuration; CR \
	int easing; CR \
	if (VALUE_IS_OFFSET(ARGV[0])) { CR \
		offset = VAL2OFFSET(ARGV[0]);  CR \
		OPTIONAL_INT32_ARG(2, msDuration_2, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(3, easing_3, EasingFuncRef::easeInOutQuad); CR \
		easing = easing_3; CR \
		msDuration = msDuration_2; CR \
    } else { CR \
		REQUIRE_NUMBER_ARG(1, deltaXOffset); CR \
		REQUIRE_NUMBER_ARG(2, deltaYOffset); CR \
		offset.x = deltaXOffset; CR \
		offset.y = deltaYOffset; CR \
		OPTIONAL_INT32_ARG(3, msDuration_3, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(4, easing_4, EasingFuncRef::easeInOutQuad); CR \
		easing = easing_4; CR \
		msDuration = msDuration_3; CR \
    } CR \
	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
		self->changeCenter(offset, msDuration, gEasingFunctions[easing]); CR \
	} else { CR \
		self->changeCenter(offset, msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, ChangeCenterTo) CR \
 	METHOD_SIGNATURE("", undefined, 3, ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	pdg::Offset offset; CR \
	int32 msDuration; CR \
	int easing; CR \
	if (VALUE_IS_OFFSET(ARGV[0])) { CR \
		offset = VAL2OFFSET(ARGV[0]);  CR \
		OPTIONAL_INT32_ARG(2, msDuration_2, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(3, easing_3, EasingFuncRef::easeInOutQuad); CR \
		easing = easing_3; CR \
		msDuration = msDuration_2; CR \
    } else { CR \
		REQUIRE_NUMBER_ARG(1, deltaXOffset); CR \
		REQUIRE_NUMBER_ARG(2, deltaYOffset); CR \
		offset.x = deltaXOffset; CR \
		offset.y = deltaYOffset; CR \
		OPTIONAL_INT32_ARG(3, msDuration_3, duration_Instantaneous); CR \
		OPTIONAL_INT32_ARG(4, easing_4, EasingFuncRef::easeInOutQuad); CR \
		easing = easing_4; CR \
		msDuration = msDuration_3; CR \
    } CR \
	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
		self->changeCenterTo(offset, msDuration, gEasingFunctions[easing]); CR \
	} else { CR \
		self->changeCenterTo(offset, msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, Wait) CR \
	METHOD_SIGNATURE("", [object Animated], 1, ([number int] msDuration)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_INT32_ARG(1, msDuration); CR \
	self->wait(msDuration); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, SetFriction) CR \
 	METHOD_SIGNATURE("", [object Animated], 1, (number frictionCoefficient)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, frictionCoefficient); CR \
	self->setFriction(frictionCoefficient); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, ApplyForce) CR \
	METHOD_SIGNATURE("", undefined, 2, ([object Vector] force, [number int] msDuration = duration_Instantaneous)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_VECTOR_ARG(1, force); CR \
	OPTIONAL_INT32_ARG(2, msDuration, duration_Instantaneous); CR \
	self->applyForce(force, msDuration); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, ApplyTorque) CR \
	METHOD_SIGNATURE("", undefined, 2, (number forceSpin, [number int] msDuration = duration_Instantaneous)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_NUMBER_ARG(1, forceSpin); CR \
	OPTIONAL_INT32_ARG(2, msDuration, duration_Instantaneous); CR \
	self->applyTorque(forceSpin, msDuration); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, StopAllForces) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->stopAllForces(); CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, AddAnimationHelper) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object IAnimationHelper] helper)); CR \
	OBJECT_SAVE(self->mAnimatedScriptObj, THIS); CR \
    DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], IAnimationHelper); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, helper, IAnimationHelper); CR \
	self->addAnimationHelper(helper); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, RemoveAnimationHelper) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object IAnimationHelper] helper)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_CPP_OBJECT_ARG(1, helper, IAnimationHelper); CR \
	self->removeAnimationHelper(helper); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, ClearAnimationHelpers) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->clearAnimationHelpers(); CR \
	NO_RETURN; CR \
	END CR \


#define HAS_SPRITE_LAYER_METHODS(klass) \
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
	METHOD_SIGNATURE("", undefined, 5, (number zoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) )); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, zoomLevel); CR \
	REQUIRE_INT32_ARG(2, msDuration); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad); CR \
	OPTIONAL_RECT_ARG(4, keepInRect, pdg::Rect(0,0)); CR \
    OPTIONAL_POINT_ARG(5, centerOn, pdg::Point(0,0)); CR \
    pdg::Point* centerOnPtr = (ARGC >= 5) ? &centerOn : 0; CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->zoomTo(zoomLevel, msDuration, gEasingFunctions[easing], keepInRect, centerOnPtr); CR \
    } else { CR \
		self->zoomTo(zoomLevel, msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, Zoom) CR \
	METHOD_SIGNATURE("", undefined, 5, (number deltaZoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) )); CR \
    REQUIRE_ARG_MIN_COUNT(2); CR \
	REQUIRE_NUMBER_ARG(1, deltaZoomLevel); CR \
	REQUIRE_INT32_ARG(2, msDuration); CR \
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::easeInOutQuad); CR \
	OPTIONAL_RECT_ARG(4, keepInRect, pdg::Rect(0,0)); CR \
    OPTIONAL_POINT_ARG(5, centerOn, pdg::Point(0,0)); CR \
    pdg::Point* centerOnPtr = (ARGC >= 5) ? &centerOn : 0; CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->zoom(deltaZoomLevel, msDuration, gEasingFunctions[easing], keepInRect, centerOnPtr); CR \
    } else { CR \
		self->zoom(deltaZoomLevel, msDuration); CR \
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
	METHOD_SIGNATURE("", undefined, 2, ([number int] msDuration, [number int] easing = linearTween)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_INT32_ARG(1, msDuration); CR \
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween); CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->fadeIn(msDuration, gEasingFunctions[easing]); CR \
    } else { CR \
		self->fadeIn(msDuration); CR \
	} CR \
	RETURN_THIS; CR \
	END CR \
METHOD_IMPL(klass, FadeOut) CR \
	METHOD_SIGNATURE("", undefined, 2, ([number int] msDuration, [number int] easing = linearTween)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_INT32_ARG(1, msDuration); CR \
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween); CR \
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) { CR \
    	self->fadeOut(msDuration, gEasingFunctions[easing]); CR \
    } else { CR \
		self->fadeOut(msDuration); CR \
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
	METHOD_SIGNATURE("", undefined, 1, ([object Sprite] newSprite)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, newSprite, Sprite); CR \
	self->addSprite(newSprite); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, RemoveSprite) CR \
	METHOD_SIGNATURE("", undefined, 1, ([object Sprite] oldSprite)); CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, oldSprite, Sprite); CR \
    self->removeSprite(oldSprite); CR \
	NO_RETURN; CR \
	END CR \
METHOD_IMPL(klass, RemoveAllSprites) CR \
	METHOD_SIGNATURE("", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->removeAllSprites(); CR \
	NO_RETURN; CR \
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

