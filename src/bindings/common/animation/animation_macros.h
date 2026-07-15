#define ANIMATED_METHODS(klass) \
	PROPERTY(klass, Location) CR \
	PROPERTY(klass, Speed) CR \
	PROPERTY(klass, Velocity) CR \
	PROPERTY(klass, Width) CR \
	PROPERTY(klass, Height) CR \
	PROPERTY(klass, Rotation) CR \
	PROPERTY(klass, CenterOffset) CR \
	PROPERTY(klass, Spin) CR \
	PROPERTY(klass, Mass) CR \
	PROPERTY(klass, MoveFriction) CR \
	PROPERTY(klass, SpinFriction) CR \
	PROPERTY(klass, SizeFriction) CR \
	METHOD(klass, GetBoundingBox) CR \
	METHOD(klass, GetRotatedBounds) CR \
	METHOD(klass, Move) CR \
	METHOD(klass, MoveTo) CR \
	METHOD(klass, SetVelocityInRadians) CR \
	METHOD(klass, GetMovementDirectionInRadians) CR \
	METHOD(klass, StopMoving) CR \
	METHOD(klass, Accelerate) CR \
	METHOD(klass, AccelerateTo) CR \
	METHOD(klass, SetSize) CR \
	METHOD(klass, Grow) CR \
	METHOD(klass, Stretch) CR \
	METHOD(klass, StartGrowing) CR \
	METHOD(klass, StopGrowing) CR \
	METHOD(klass, StartStretching) CR \
	METHOD(klass, StopStretching) CR \
	METHOD(klass, Resize) CR \
	METHOD(klass, ResizeTo) CR \
	METHOD(klass, SetFlipX) CR \
	METHOD(klass, SetFlipY) CR \
	METHOD(klass, FlipX) CR \
	METHOD(klass, FlipY) CR \
	METHOD(klass, IsFlippedX) CR \
	METHOD(klass, IsFlippedY) CR \
	METHOD(klass, Rotate) CR \
	METHOD(klass, RotateTo) CR \
	METHOD(klass, StopSpinning) CR \
	METHOD(klass, ChangeCenter) CR \
	METHOD(klass, ChangeCenterTo) CR \
	METHOD(klass, Wait) CR \
	METHOD(klass, SetFriction) CR \
	METHOD(klass, ApplyForce) CR \
	METHOD(klass, ApplyTorque) CR \
	METHOD(klass, StopAllForces) CR \
	METHOD(klass, AddAnimationHelper) CR \
	METHOD(klass, RemoveAnimationHelper) CR \
	METHOD(klass, ClearAnimationHelpers)

#define SPRITE_LAYER_METHODS(klass) \
	METHOD(klass, SetSerializationFlags) CR \
	METHOD(klass, StartAnimations) CR \
	METHOD(klass, StopAnimations) CR \
	METHOD(klass, Hide) CR \
	METHOD(klass, Show) CR \
	METHOD(klass, IsHidden) CR \
	METHOD(klass, FadeIn) CR \
	METHOD(klass, FadeOut) CR \
	METHOD(klass, MoveBehind) CR \
	METHOD(klass, MoveInFrontOf) CR \
	METHOD(klass, MoveToFront) CR \
	METHOD(klass, MoveToBack) CR \
	METHOD(klass, GetZOrder) CR \
	METHOD(klass, MoveWith) CR \
	METHOD(klass, FindSprite) CR \
	METHOD(klass, GetNthSprite) CR \
	METHOD(klass, GetSpriteZOrder) CR \
	METHOD(klass, IsSpriteBehind) CR \
	METHOD(klass, HasSprite) CR \
	METHOD(klass, AddSprite) CR \
	METHOD(klass, RemoveSprite) CR \
	METHOD(klass, RemoveAllSprites) CR \
	METHOD(klass, EnableCollisions) CR \
	METHOD(klass, DisableCollisions) CR \
	METHOD(klass, EnableCollisionsWithLayer) CR \
	METHOD(klass, DisableCollisionsWithLayer) CR \
	METHOD(klass, CreateSprite)
//	METHOD(klass, CloneSprite)

%#ifndef PDG_NO_GUI
#define SPRITE_LAYER_GUI_METHODS(klass) \
	PROPERTY(klass, SpritePort) CR \
	PROPERTY(klass, Origin) CR \
	PROPERTY(klass, Zoom) CR \
	METHOD(klass, Zoom) CR \
	METHOD(klass, ZoomTo) CR \
	METHOD(klass, SetAutoCenter) CR \
	METHOD(klass, SetFixedMoveAxis) CR \
	METHOD(klass, LayerToPortPoint) CR \
	METHOD(klass, LayerToPortOffset) CR \
	METHOD(klass, LayerToPortVector) CR \
	METHOD(klass, LayerToPortRect) CR \
	METHOD(klass, LayerToPortQuad) CR \
	METHOD(klass, PortToLayerPoint) CR \
	METHOD(klass, PortToLayerOffset) CR \
	METHOD(klass, PortToLayerVector) CR \
	METHOD(klass, PortToLayerRect) CR \
	METHOD(klass, PortToLayerQuad)
%#endif

#define SPRITE_LAYER_CHIPMUNK_METHODS(klass) \
	METHOD(klass, SetUseChipmunkPhysics) CR \
	METHOD(klass, SetStaticLayer) CR \
	METHOD(klass, SetGravity) CR \
	METHOD(klass, SetKeepGravityDownward) CR \
	METHOD(klass, SetDamping) CR \
	METHOD(klass, GetSpace)
