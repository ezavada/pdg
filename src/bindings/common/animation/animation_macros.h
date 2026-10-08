#define ANIMATED_METHODS(klass) \
    METHODS_FROM(klass, AnimatedBase, \
    METHOD(klass, PlayScript) CR \
    METHOD(klass, Batch) CR \
    METHOD(klass, EndBatch) CR \
    METHOD(klass, Series) CR \
    METHOD(klass, EndSeries) CR \
    METHOD(klass, AndAlso) CR \
    METHOD(klass, Stagger) CR \
    METHOD(klass, Mark) CR \
    METHOD(klass, JumpToMark) CR \
    METHOD(klass, ScriptOn) CR \
    METHOD(klass, TriggerEvent) CR \
    METHOD(klass, OnStarted) CR \
    METHOD(klass, OnFinished) CR \
    METHOD(klass, OnScriptFinished) CR \
    METHOD(klass, OnMark) CR \
    METHOD(klass, OnYoyo) CR \
    METHOD(klass, OnRepeat) CR \
    METHOD(klass, OnUntilFired) CR \
    METHOD(klass, When) CR \
    METHOD(klass, Otherwise) CR \
    METHOD(klass, EndWhen) CR \
    METHOD(klass, EndOtherwise) CR \
    METHOD(klass, Until) CR \
    METHOD(klass, Yoyo) CR \
    METHOD(klass, Repeat) CR \
    METHOD(klass, Diminish) CR \
    METHOD(klass, Increase) CR \
    METHOD(klass, SlowDown) CR \
    METHOD(klass, SpeedUp) CR \
    METHOD(klass, StopIt) CR \
    METHOD(klass, RestartIt) CR \
    METHOD(klass, PauseIt) CR \
    METHOD(klass, ResumeIt) CR \
    METHOD(klass, GetBoundingBox) CR \
    METHOD(klass, GetRotatedBounds) CR \
    METHOD(klass, GetLocation) CR \
    METHOD(klass, GetMovement) CR \
    METHOD(klass, GetSize) CR \
    METHOD(klass, GetWidth) CR \
    METHOD(klass, GetHeight) CR \
    METHOD(klass, GetScale) CR \
    METHOD(klass, GetStretching) CR \
    METHOD(klass, GetRotation) CR \
    METHOD(klass, GetCenterOffset) CR \
    METHOD(klass, GetSpin) CR \
    METHOD(klass, SetLocation) CR \
    METHOD(klass, MoveTo) CR \
    METHOD(klass, MoveBy) CR \
    METHOD(klass, SetMovement) CR \
    METHOD(klass, ChangeMovementTo) CR \
    METHOD(klass, ChangeMovementBy) CR \
    METHOD(klass, SetSize) CR \
    METHOD(klass, ChangeCenterOffsetTo) CR \
    METHOD(klass, ChangeCenterOffsetBy) CR \
    METHOD(klass, SetWidth) CR \
    METHOD(klass, SetHeight) CR \
    METHOD(klass, SetRotation) CR \
    METHOD(klass, SetSpin) CR \
    METHOD(klass, SetGrowing) CR \
    METHOD(klass, SetStretching) CR \
    METHOD(klass, SetScale) CR \
    METHOD(klass, ChangeSpinTo) CR \
    METHOD(klass, ChangeSpinBy) CR \
    METHOD(klass, ChangeGrowingTo) CR \
    METHOD(klass, ChangeGrowingBy) CR \
    METHOD(klass, ChangeStretchingTo) CR \
    METHOD(klass, ChangeStretchingBy) CR \
    METHOD(klass, ChangeScaleTo) CR \
    METHOD(klass, ChangeScaleBy) CR \
    METHOD(klass, Grow) CR \
    METHOD(klass, Stretch) CR \
    METHOD(klass, ResizeBy) CR \
    METHOD(klass, ResizeTo) CR \
    METHOD(klass, RotateBy) CR \
    METHOD(klass, RotateTo) CR \
    METHOD(klass, SetCenterOffset) CR \
    METHOD(klass, SetFlipX) CR \
    METHOD(klass, SetFlipY) CR \
    METHOD(klass, StopMovement) CR \
    METHOD(klass, StopSpinning) CR \
    METHOD(klass, StopGrowing) CR \
    METHOD(klass, StopStretching) CR \
    METHOD(klass, PauseSchedule) CR \
    METHOD(klass, ResumeSchedule) CR \
    METHOD(klass, CancelSchedule) CR \
    METHOD(klass, FlipX) CR \
    METHOD(klass, FlipY) CR \
    METHOD(klass, AndThen) CR \
    METHOD(klass, IsFlippedX) CR \
    METHOD(klass, IsFlippedY) CR \
    METHOD(klass, IsSchedulePaused) CR \
    METHOD(klass, HasScheduledAnimations) CR \
    METHOD(klass, Wait) CR \
    METHOD(klass, AddAnimationHelper) CR \
    METHOD(klass, RemoveAnimationHelper) CR \
    METHOD(klass, ClearAnimationHelpers) \
    )

#define SPRITE_LAYER_METHODS(klass) \
    METHODS_FROM(klass, SpriteLayer, \
    METHOD(klass, SetQueryBits) CR \
    METHOD(klass, GetQueryBits) CR \
    METHOD(klass, SetCamera) CR \
    METHOD(klass, GetCamera) CR \
    METHOD(klass, GetEffectiveCamera) CR \
    METHOD(klass, SetCameraParallax) CR \
    PROPERTY(klass, WorldBounds) CR \
    METHOD(klass, CreateParticle) CR \
    METHOD(klass, AddParticle) CR \
    METHOD(klass, RemoveParticle) CR \
    METHOD(klass, RemoveAllParticles) CR \
    METHOD(klass, GetParticleTrailCount) CR \
    METHOD(klass, GetParticleCount) CR \
    METHOD(klass, GetNthParticle) CR \
    METHOD(klass, SetMaxParticles) CR \
    METHOD(klass, GetMaxParticles) CR \
    METHOD(klass, CreateParticleEmitter) CR \
    METHOD(klass, RemoveParticleEmitter) CR \
    METHOD(klass, RemoveAllParticleEmitters) CR \
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
	METHOD(klass, CreateSprite) \
    )
//	METHOD(klass, CloneSprite)

%#ifndef PDG_NO_GUI
#define SPRITE_LAYER_GUI_METHODS(klass) \
    METHODS_FROM(klass, SpriteLayer, \
	PROPERTY(klass, SpritePort) CR \
	METHOD(klass, LayerToPortPoint) CR \
	METHOD(klass, LayerToPortOffset) CR \
	METHOD(klass, LayerToPortVector) CR \
	METHOD(klass, LayerToPortRect) CR \
	METHOD(klass, LayerToPortQuad) CR \
	METHOD(klass, PortToLayerPoint) CR \
	METHOD(klass, PortToLayerOffset) CR \
	METHOD(klass, PortToLayerVector) CR \
	METHOD(klass, PortToLayerRect) CR \
	METHOD(klass, PortToLayerQuad) \
    )
%#endif

#define SPRITE_LAYER_CHIPMUNK_METHODS(klass) \
    METHODS_FROM(klass, SpriteLayer, \
	METHOD(klass, SetUseChipmunkPhysics) CR \
	METHOD(klass, SetStaticLayer) CR \
	METHOD(klass, SetGravity) CR \
	METHOD(klass, SetDamping) CR \
	METHOD(klass, GetSpace) \
    )

#define SPRITE_LAYER_EVENT_METHODS(klass) \
    METHODS_FROM(klass, SpriteLayer, \
    METHOD(klass, On) CR \
    METHOD(klass, OnCollideSprite) CR \
    METHOD(klass, OnCollideWall) CR \
    METHOD(klass, OnOffscreen) CR \
    METHOD(klass, OnOnscreen) CR \
    METHOD(klass, OnExitLayer) CR \
    METHOD(klass, OnAnimationLoop) CR \
    METHOD(klass, OnAnimationEnd) CR \
    METHOD(klass, OnFadeComplete) CR \
    METHOD(klass, OnFadeInComplete) CR \
    METHOD(klass, OnFadeOutComplete) CR \
    METHOD(klass, OnMouseEnter) CR \
    METHOD(klass, OnMouseLeave) CR \
    METHOD(klass, OnMouseDown) CR \
    METHOD(klass, OnMouseUp) CR \
    METHOD(klass, OnMouseClick) CR \
    METHOD(klass, OnErasePort) CR \
    METHOD(klass, OnPreDrawLayer) CR \
    METHOD(klass, OnPostDrawLayer) CR \
    METHOD(klass, OnDrawPortComplete) CR \
    METHOD(klass, OnAnimationStart) CR \
    METHOD(klass, OnPreAnimateLayer) CR \
    METHOD(klass, OnPostAnimateLayer) CR \
    METHOD(klass, OnAnimationComplete) CR \
    METHOD(klass, OnLayerFadeInComplete) CR \
    METHOD(klass, OnLayerFadeOutComplete) CR \
    )
