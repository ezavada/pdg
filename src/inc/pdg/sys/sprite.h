// -----------------------------------------------
// sprite.h
// 
// sprite functionality
//
// Written by Ed Zavada, 2009-2012
// Copyright (c) 2012, Dream Rock Studios, LLC
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


#ifndef PDG_SPRITE_H_INCLUDED
#define PDG_SPRITE_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/platform.h"

#include "pdg/sys/global_types.h"
#include "pdg/sys/coordinates.h"
#include "pdg/sys/refcounted.h"
#include "pdg/sys/image.h"
#include "pdg/sys/core.h"
#include "pdg/sys/events.h"
#include "pdg/sys/eventemitter.h"
#include "pdg/sys/animated.h"
#include "pdg/sys/physicsbody.h"
#include "pdg/sys/collider.h"
#include "pdg/sys/part.h"
#include "pdg/sys/serializable.h"

#ifndef PDG_NO_GUI
  #include "pdg/sys/ispritedrawhelper.h"
#endif

#include <limits> // for infinity()
#include <map>    // for std::map
#include <string> // for std::string
#include <vector> // for std::vector

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

#ifdef PDG_USE_CHIPMUNK_PHYSICS
#include "chipmunk/chipmunk_private.h"
#define CP_COLLIDE_TYPE_SPRITE 1111
#define CP_COLLIDE_TYPE_WALL   1212
#define CP_COLLIDE_TYPE_SPRITER_BOX 1313
#endif

#ifdef PDG_SPRITER_SUPPORT
#include "pdg/sys/animationpose.h"
#include "pdg/sys/animationcontroller.h"
#include "pdg/sys/animationphysics.h"
#include "pdg/sys/animationdrawing.h"
// Suppress SpriterPlusPlus virtual function warnings (Clang only; MSVC does not use these pragmas)
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverloaded-virtual"
#endif
#include "spriterengine/entity/entity.h"
#include "spriterengine/entity/entityinstance.h"
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#endif

#define MAX_FRAMES_PER_SPRITE 256
#define MAX_BREAKABLE_JOINTS_PER_SPRITE 16

namespace pdg {
class Bone;
class SpriterPoseAdapter;
struct SpriterRigSchema;

class ImageImpl;  // internal implementation class

// -----------------------------------------------------------------------------------
// Sprite
// An animated, moving image that is automatically moved, animated, and blitted onto 
// the screen
// Things that happen to a sprite that might require intervention, such as collisions
// completed animations, going offscreen, etc... will generate events 
// -----------------------------------------------------------------------------------

class Sprite : public EventEmitter, public Animated<Sprite> {
    friend class Bone;
    friend class PhysicsBodyRef<Sprite>;
    friend class ColliderRef<Sprite>;
    void initializePhysicsBody(PhysicsBody& body);
    friend class SpriteLayer;
    friend class TileLayer;
    friend class SpriteManager;
    friend class Part;
    /// @cond INTERNAL
    friend class PhysicsGraphSnapshot;
    friend class SpriteAnimationSnapshot;
    /// @endcond
    std::vector<Part*> mParts;
    PartId mNextPartId = 0;
    void animateParts(double deltaSeconds);
    std::vector<Part*> orderedParts() const;
    void refreshPartPhysics();
    bool mRefreshingPartPhysics = false;
    bool mAnimationPrepared = false;
    void advanceAnimation(double elapsed);
    void publishBodyBreak(Part* part, const PhysicsBodyBreakInfo& info);
    void finishAnimation(ms_delta elapsed, bool layerDoCollisions);
    void updatePartAttachments();
    bool mUpdatingPartAttachments = false;
    Part* mAttachmentPart = nullptr;
    void validateTransformEdit() const override;
    bool attachmentReaches(const Sprite* target) const;
    bool mPublishingPhysics = false;
    void validateProgrammedTransform() const override;
    void centerChanged(const Offset& delta) override;
    SpatialTransform partRootTransform() const;
    void validateInitialSnapshot(bool layerGraph = false) const;
    uint32 partSnapshotSize(ISerializer*) const;
    void serializeParts(ISerializer*) const;
    void deserializeParts(IDeserializer*);
    uint32 partMotionSize(ISerializer*) const;
    void serializePartMotion(ISerializer*) const;
    void deserializePartMotion(IDeserializer*);
public:
    /** Optional physics body; querying never creates one.
     * Convert physics to PhysicsBody& and retain with addRef/release to keep
     * that body after removal. Only setupPhysicsBody()/removePhysicsBody()
     * change the association; callers cannot assign this member. Immediate transform
     * setters teleport it; dynamic bodies reject programmed movement/spin.
     */
    PhysicsBodyRef<Sprite> physics;
    /** Optional collision geometry; reading never creates a collider. */
    ColliderRef<Sprite> collider;
    Collider& setupCollider();
    void removeCollider();
    /** Set up the associated body, applying mass and inertia on every call.
     * Omitted arguments use 1, including when a body already exists.
     * Retains an existing body's identity, motion, mode and constraints.
     * Read physics to access the body without reconfiguring it.
     */
    PhysicsBody& setupPhysicsBody(double mass = 1, double momentOfInertia = 1);
    void removePhysicsBody();

    /** Create an empty independent Part with a unique nonempty name.
     * Returned pointer is borrowed; addRef() to retain it across removal. */
    Part* createPart(const std::string& name);
    /** Move an existing Part into this Sprite, preserving world placement and handles.
     * Both owners must share a layer, or both be off-layer. Includes Part and
     * physical-rig descendants by default. Names must be unique here; moved Parts
     * receive new per-Sprite IDs. Internal joints survive; boundary joints disconnect.
     * Source skeleton bindings and assembly membership are released. Attach to a
     * destination rig explicitly. See the method reference for controller restrictions.
     * Returns the same borrowed Part pointer. */
    Part* transferPart(Part* part, bool includeDescendants = true);
    Part* getPart(PartId id) const;
    /// @cond INTERNAL
    AnimatedBase* snapshotAnimationMember(uint32 id) override;
    /// @endcond
    Part* findPart(const std::string& name) const;
    Part* getAttachmentPart() const { return mAttachmentPart; }
    size_t getPartCount() const { return mParts.size(); }
    std::vector<std::string> getPartNames() const;
    bool removePart(PartId id);
    void clearParts();

    uint32 getMyClassTag() const override { return CLASSTAG_SPRITE; }
    uint32 getSerializedSize(ISerializer* serializer) const override;
    void serialize(ISerializer* serializer) const override;
    void deserialize(IDeserializer* deserializer) override;
	static pdg::ISerializable* CreateInstance() { return new Sprite; }

	enum {
		// animation flags, add starting direction + uni/bi-directional + looping/not
		// starting direction
		animate_StartToEnd =		0,
		animate_EndToStart =		1,

		// one direction or bidirectional
		animate_Unidirectional =	0,
		animate_Bidirectional =		2,
		
		// looping or not
		animate_NoLooping =			0,
		animate_Looping =			4,
		
		// frame markers
		start_FromFirstFrame = -1,
		start_FromLastFrame = -2,
		
		all_Frames = 0,
		
		// sprite actions for SprintInfo
		action_CollideSprite = 0,
		action_CollideWall = 1, // hit the boundary of the sprite layer
		action_Offscreen = 2, // is completely offscreen
		action_Onscreen = 3, // has moved from being offscreen to onscreen
		action_ExitLayer = 4, // has moved completely outside the boundries of the sprite layer
		action_AnimationLoop = 8,
		action_AnimationEnd = 9,
		action_FadeComplete = 10,
		action_FadeInComplete = 11,
		action_FadeOutComplete = 12,
		action_JointBreak = 13, // only available with chipmunk physics
        action_AnimationPhysicsRecoveryComplete = 17, //!< physical recovery reached the requested animation control mode.
        action_BodyBreak = 16, //!< a PhysicsBody exceeded its angular-speed threshold.
        action_AnimationBlendComplete = 15, //!< blendToAnimation() or transitionToAnimation() completed; eventType_SpriteAnimate with SpriteAnimateInfo.

		// touch types for SpritTouchInfo
		touch_MouseEnter = 20, /** NOT IMPLEMENTED **/
		touch_MouseLeave = 21, /** NOT IMPLEMENTED **/
		touch_MouseDown = 22,
		touch_MouseUp = 23,
		touch_MouseClick = 24,

		// collision type
		collide_None = 0,
		collide_Point = 1,
		collide_BoundingBox = 2,
		collide_CollisionRadius = 3,
		collide_AlphaChannel = 4,
		collide_SpriterCollisionBox = 5, // AnimatedBase collision boxes from Spriter
		collide_Last = collide_SpriterCollisionBox
	};

    // get the bounds for a frame including rotation, or current frame if no frameNum given
    RotatedRect	getFrameRotatedBounds(int frameNum = -1);

    // sets current frame of Sprite to a given frame number
    Sprite& setFrame(int frame);
	int		getCurrentFrame();
    
    // report how many frames are in the sprite
    int     getFrameCount();
	
	// set how fast we animate through the frames
	// startingFrame and number of frames can be used to only animate through a subset of the
	// Sprite's frames.
	// when animating frames, you 
	void	startFrameAnimation(float fps, int startingFrame = start_FromFirstFrame, 
                            int numFrames = all_Frames, int animateFlags = animate_Looping);
	
	// stops all frame animation, the current frame becomes the sprite's image
	// does not send action_AnimationEnd sprite events
	void	stopFrameAnimation();
	
	// controls whether the sprite should generate action_AnimationLoop or action_AnimationEnd events, default is no
	bool	getWantsAnimLoopEvents() { return wantsAnimLoop; }
	bool	getWantsAnimEndEvents() { return wantsAnimEnd; }

	Sprite&	setWantsAnimLoopEvents(bool wantsThem = true);
	Sprite&	setWantsAnimEndEvents(bool wantsThem = true);

    // adds an image that is used for one or more frames
    // since an image itself can have multiple frames, all frames of the image are added
    // to the Sprite, unless the numFrames is passed in.
    // the frames are added to the end of the frame list, unless startingFrame is passed in 
    void	addFramesImage(Image* image, int startingFrame = start_FromFirstFrame, int numFrames = all_Frames);
	
  #ifdef PDG_SPRITER_SUPPORT
    // Opt-in fixed-hierarchy pose evaluation. Reference is the explicitly
    // selected clip at time zero; failures leave existing playback available.
    // GUI capability is explicit in headless builds. Debug drawing is opt-in,
    // per instance, and uses the final pose in the current layer/port.
    void seekAnimation(const char* clip, double timeSeconds);
    void transitionToAnimation(const char* clip, double timeSeconds, double durationSeconds);
    bool isAnimationTransitioning() const;
    double getAnimationTransitionProgress() const;
    AnimationModifierId addAnimationIK(const AnimationTwoBoneIK& config, int order = 0);
    void setAnimationIKTarget(AnimationModifierId id, double x, double y, int space = animationSpace_Rig);
    AnimationIKResult getAnimationIKResult(AnimationModifierId id) const;
    /// Register a procedural pose modifier; requires an enabled animation pose. See \ref native_procedural_animation.
    AnimationModifierId addAnimationFABRIK(const AnimationFABRIK& config, int order = 0);
    /// Return the latest FABRIK solve diagnostics. See \ref native_procedural_animation.
    AnimationFABRIKResult getAnimationFABRIKResult(AnimationModifierId id) const;
    /// Register a procedural pose modifier; requires an enabled animation pose. See \ref native_procedural_animation.
    AnimationModifierId addAnimationJiggle(const AnimationJiggle& config, int order = 0);
    /// Return an independent configuration record. See \ref native_procedural_animation.
    AnimationJiggle getAnimationJiggleOptions(AnimationModifierId id) const;
    /// Replace tuning from a complete configuration without changing topology. See \ref native_procedural_animation.
    void setAnimationJiggleSettings(AnimationModifierId id, const AnimationJiggle& settings);
    /// Enable or freeze jiggle; reenabling reseeds from the current pose. See \ref native_procedural_animation.
    void setAnimationJiggleEnabled(AnimationModifierId id, bool enabled);
    /// Return whether jiggle is enabled. See \ref native_procedural_animation.
    bool isAnimationJiggleEnabled(AnimationModifierId id) const;
    /// Set or linearly fade influence using simulation seconds. See \ref native_procedural_animation.
    void setAnimationJiggleInfluence(AnimationModifierId id, double influence, double seconds = 0);
    /// Reseed jiggle from the desired pose or target. See \ref native_procedural_animation.
    void resetAnimationJiggle(AnimationModifierId id);
    /// Add angular or target velocity. See \ref native_procedural_animation.
    void kickAnimationJiggle(AnimationModifierId id, double x, double y, int joint = -1);
    /// Return the most recently evaluated jiggle diagnostics. See \ref native_procedural_animation.
    JiggleResult getAnimationJiggleResult(AnimationModifierId id) const;
    /// Return an independent numerical state snapshot. See \ref native_procedural_animation.
    JiggleState getAnimationJiggleState(AnimationModifierId id) const;
    /// Restore validated numerical state on the same topology. See \ref native_procedural_animation.
    void setAnimationJiggleState(AnimationModifierId id, const JiggleState&);
    /// Remove a jiggle controller. See \ref native_procedural_animation.
    void removeAnimationJiggle(AnimationModifierId id);
    /// @cond INTERNAL
    /// \internal Numeric binding transport.
    std::vector<double> proceduralControl(int operation, const std::vector<double>& values);
    /// @endcond
    AnimationModifierId addAnimationModifier(AnimationPipeline::Modifier callback, int stage = animationStage_PreConstraint, int order = 0);
    void removeAnimationModifier(AnimationModifierId id);
    void clearAnimationModifiers();
    std::string getAnimationModifierError(AnimationModifierId id) const;
    void setAnimationSource(int source);
    int getAnimationSource() const;
    bool isAnimationDrawingSupported() const;
    void setAnimationDebugDraw(int flags);
    int getAnimationDebugDraw() const;
    // Persistent artwork shares editable Drawing contents; callbacks return owned handles.
    AnimationDrawableId addAnimationDrawable(const AnimationDrawableOptions& options, const Drawing& drawing);
    AnimationDrawableId addAnimationDrawable(const AnimationDrawableOptions& options, AnimationDrawings::Callback callback);
    void removeAnimationDrawable(AnimationDrawableId id);
    void clearAnimationDrawables();
    void setAnimationDrawableEnabled(AnimationDrawableId id, bool enabled);
    std::string getAnimationDrawableError(AnimationDrawableId id) const;
    AnimationDrawBounds getAnimationDrawBounds() const;
    static bool supportsAnimationPhysics();
    /** Create constrained bodies on bone-named Parts; access them through findPart(name)->physics.
     * Existing names must match an unparented Part without a body or collider with the same bone/offset.
     * Disable before changing mapped bindings, offsets or removing Parts.
     */
    void setupAnimationPhysics(const AnimationPhysicsDefinition& definition);
    /** Generate a dynamic rig from the enabled reference skeleton. The optional
     * unitsPerMeter converts the designated root's 1 mm zero-length fallback.
     * Parts expose generated capsules and pivot joints through collider/physics.
     */
    Sprite& setupPhysicsFromAnimationRig(double totalMass, double unitsPerMeter = 1);
    /// Register a same-Sprite physical Part in the rig assembly; joints are explicit.
    Sprite& attachAnimationPhysicsPart(Part* part, Part* parent = nullptr);
    /// Release membership/control and disconnect boundary joints, preserving internal joints.
    Sprite& detachAnimationPhysicsPart(Part* part, bool includeDescendants = true);
    bool isAnimationPhysicsPartAttached(const Part* part) const;
    Sprite& setAnimationPhysicsRoot(AnimationBoneId bone);
    Sprite& setAnimationPhysicsRoot(const char* bone);
    AnimationBoneId getAnimationPhysicsRoot() const;
    Sprite& clearAnimationPhysicsRoot();
    std::vector<std::string> getAnimationPhysicsSetupWarnings() const { return mAnimationPhysicsSetupWarnings; }
    Sprite& setAnimationPhysicsMode(int mode, double recoveryTime = 0.5, int direction = rotationDirection_AsSpecified);
    Sprite& setAnimationPhysicsMode(int mode, AnimationBoneId bone, bool includeDescendants = false,
        double recoveryTime = 0.5, int direction = rotationDirection_AsSpecified);
    Sprite& setAnimationPhysicsMode(int mode, const char* bone, bool includeDescendants = false,
        double recoveryTime = 0.5, int direction = rotationDirection_AsSpecified);
    int getAnimationPhysicsMode() const;
    int getAnimationPhysicsMode(AnimationBoneId bone, bool includeDescendants = false) const;
    int getAnimationPhysicsMode(const char* bone, bool includeDescendants = false) const;
    Sprite& setAnimationPhysicsDriveSettings(const AnimationPhysicsDriveSettings& settings);
    Sprite& setAnimationPhysicsDriveSettings(const AnimationPhysicsDriveSettings& settings, AnimationBoneId bone, bool includeDescendants = false);
    Sprite& setAnimationPhysicsDriveSettings(const AnimationPhysicsDriveSettings& settings, const char* bone, bool includeDescendants = false);
    std::optional<AnimationPhysicsDriveSettings> getAnimationPhysicsDriveSettings(AnimationBoneId bone) const;
    std::optional<AnimationPhysicsDriveSettings> getAnimationPhysicsDriveSettings(const char* bone) const;
    void disableAnimationPhysics(double recoveryTime = 0.5, int direction = rotationDirection_AsSpecified);
    bool isAnimationPhysicsEnabled() const;
    bool enableAnimationPose(const char* referenceAnimation);
    void disableAnimationPose();
    bool isAnimationPoseEnabled() const;
    std::string getAnimationRigError() const;
    std::shared_ptr<const AnimationRig> getAnimationRig() const;
    AnimationPose getAnimationPose() const;
    AnimationPose sampleAnimationPose(const char* clip, double timeSeconds) const;
    std::vector<std::string> getAnimationBoneNames() const;
    Bone* getBone(const char* name);
    Bone* getBone(AnimationBoneId id);
    std::vector<std::string> getAnimationBindingNames() const;
    AnimationTransform getAnimationBoneTransform(const char* name, int space = animationSpace_Local) const;
    AnimationTransform getAnimationBindingTransform(const char* name, int space = animationSpace_Local) const;
    // Absolute local overrides survive ticks/clip changes, never accumulate,
    // and are cleared by disable/re-enable or an entity change.
    void setAnimationBoneTransform(const char* name, const AnimationTransform& transform);
    void clearAnimationBoneTransforms();

    bool	isSpriterSprite() const;
  	bool	hasAnimation(const char* animationName);
  	bool	hasAnimation(int animationId);
  	void	startAnimation(const char* animationName);
  	void	startAnimation(int animationId);
  	
  	// Character Maps
  	void applyCharacterMap(const char* mapName);
  	void removeCharacterMap(const char* mapName);
  	void removeAllCharacterMaps();
  	std::vector<std::string> getAppliedCharacterMaps() const;
  	
  	// Event System (basic, triggers only)
  	void enableSpriterEvents(bool enable = true);
  	bool areSpriterEventsEnabled() const;
  	
	// Animation blend durations are floating-point seconds; progress is a normalized [0, 1] fraction.
	// Invalid targets/nonfinite durations are ignored. Stop retains pause semantics.
  	void blendToAnimation(const char* animationName, float blendTime);
  	void blendToAnimation(int animationId, float blendTime);
  	bool isBlending() const;
  	float getBlendProgress() const;
  	void pauseAnimation();
  	void resumeAnimation();
  	void stopAnimation();
  	bool isAnimationPlaying() const;
  	bool isAnimationPaused() const;
  	float getAnimationProgress() const;
  	
  	// Attachment Points
	bool hasAttachPoint(const char* attachPointName) const;
	// Offset from the sprite root, expressed in SpriteLayer axes (not bone-local).
	Offset getAttachPoint(const char* attachPointName) const;
	void attachSprite(Sprite* sprite, const char* attachPointName);
	void detachSprite(Sprite* sprite);
	Sprite* getAttachedSprite(const char* attachPointName) const;
	
	// Sub-Entity Management
	void activateSubEntity(const char* entityName, const char* animationName = "idle");
	
	// Spriter Collision Box Methods
	RotatedRect getSpriterCollisionBox(const char* boxName) const;
	bool isSpriterCollisionActive(const char* boxName) const;
	int getSpriterCollisionBoxCount() const;
	const char* getSpriterCollisionBoxName(int index) const;
  #endif // PDG_SPRITER_SUPPORT

  #ifndef PDG_NO_GUI
	// set a drawing helper that will be called before the sprite is drawn
	// it can do whatever drawing it likes, then return true if it wants to let the
	// sprite draw itself, or false if the sprite should skip it's normal drawing
	// if a post draw helper is set, it will always be called, even if false is returned
	// pass null to remove the current helper
	void    setDrawHelper(ISpriteDrawHelper* helper);
	
	// set a drawing helper that will be called after a sprite is drawn
	// it can do whatever drawing it likes. The return value is ignored since
	// the sprite has already drawn. If set, it is called even if the primary draw 
	// helper tells the Sprite to skip normal drawing.
	// pass null to remove the current helper
	void    setPostDrawHelper(ISpriteDrawHelper* helper);	
  #endif

	// replace an image with another one for all the frames that reference that image
	void	changeFramesImage(Image* oldImage, Image* newImage);

    // set offset of centerpoint of sprite (rotation and location are all relative to centerpoint)
	// this can be set for the whole sprite, if image = 0, or for an individual frame or group of
	// frames by specifying the image or by specifying the range of frames
	// if image is 0, the startingFrame and numFrames parameters are frame numbers for the Sprit
	// if image is specified, the startingFrame and numFrames paramaters are Image frame numbers
	// this offset is relative to the absolute center of the image or frame
    void	offsetFrameCenters(int offsetX, int offsetY, Image* image = 0, 
    						int startingFrame = start_FromFirstFrame, int numFrames = all_Frames);
	// fetch the offsets set above, but only for a single frame
    Offset	getFrameCenterOffset(Image* image = 0, int frameNum = 0);

	// fading, with 1.0 being complete opaque and 0.0 being completely transparent
	Sprite& setOpacity(float opacity);
	float	getOpacity();
	Sprite& fadeTo(float targetOpacity, double durationSeconds,
                            EasingFunc easing = linearTween);  // fadeComplete notification when done
	Sprite& fadeIn(double durationSeconds,
                            EasingFunc easing = linearTween);  // fadeInComplete notification when done
	Sprite& fadeOut(double durationSeconds,
                            EasingFunc easing = linearTween);  // fadeOutComplete notification when done

	// arrange sprites within the layer
	Sprite& moveBehind(Sprite* sprite);
	Sprite& moveInFrontOf(Sprite* sprite);
	Sprite& moveToFront();
	Sprite& moveToBack();
	int		getZOrder();
	bool	isBehind(Sprite* sprite);
	
	// collisions
	bool getWantsCollideWallEvents() { return wantsWallCollide; }
	Sprite& setWantsCollideWallEvents(bool wantsThem = true); // collisions for hitting bounds of sprite layer
    /// Follow the current frame using bounds or opaque pixel geometry; returns .collider.
    Collider& setupFrameCollider(int mode = frameCollider_AlphaMask, int alphaThreshold = 128);
    /// Follow active authored animation boxes; returns .collider.
    Collider& setupAnimationCollider();
    /// Assign an optional mask to all frames using this artwork. Null removes the mask.
    Sprite& setFrameCollisionMask(Image* frameImage, Image* maskImage);

  #ifndef PDG_NO_GUI
	bool    getWantsMouseOverEvents() { return wantsMouseOver; }
	bool    getWantsClickEvents() { return wantsClicks; }
	int     getMouseDetectMode() { return mMouseDetectMode; }
	bool    getWantsOffscreenEvents() { return wantsOffscreen; }
	// controls whether the sprite wants to get mouse events
	Sprite& setWantsMouseOverEvents(bool wantsThem = true);
	Sprite& setWantsClickEvents(bool wantsThem = true);
	Sprite& setMouseDetectMode(int collisionType = collide_BoundingBox); // how we detect when the mouse is over a sprite
	Sprite& setWantsOffscreenEvents(bool wantsThem = true); // events for when sprite moves offscreen
  #endif // ! PDG_NO_GUI

	void setUserData(UserData* userData);
	void freeUserData();
    
    SpriteLayer* getLayer() { return mLayer; }

	long spriteId;
	
	bool wantsMouseOver;
	bool wantsClicks;
	bool wantsAnimLoop;
	bool wantsAnimEnd;
	bool wantsOffscreen;
	bool wantsWallCollide;
	
	UserData* userData; // any data the user may have associated with this sprite

  #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	SCRIPT_OBJECT_REF mSpriteScriptObj;
  #endif

#ifndef PDG_INTERNAL_LIB
protected:
#endif
    /// @cond INTERNAL
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    cpBody* mBody;
    cpShape* mCollideShape;

    // used to mark things that are in the same group and so shouldn't collide with one another
    // mainly used with sprites that are joined together
    Sprite&         setCollideGroup(long group) { mCollideGroup = group; return *this; }
    long            getCollideGroup() { return mCollideGroup; }

    // JOINTS:

    // pin sprites together, at a particular anchor point (offset from center) on each
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it

    cpConstraint*   pinJoint(Offset anchor, Sprite* otherSprite, Offset otherAnchor, float breakingForce = 0.0f);

    // join sprites together via a slider between anchor points that has a min/max distance
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   slideJoint(Offset anchor, Sprite* otherSprite, Offset otherAnchor, float minDist, float maxDist, float breakingForce = 0.0f);

    // join sprites together at a particular location in layer coordinates
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   pivotJoint(Sprite* otherSprite, Point pivot, float breakingForce = 0.0f);

    // join sprites together via a groove on this sprite to an anchor point on another
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   grooveJoint(Offset grooveStart, Offset grooveEnd, Sprite* otherSprite, Offset otherAnchor, float breakingForce = 0.0f);

    // join sprites together via a spring between anchor points
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   springJoint(Offset anchor, Sprite* otherSprite, Offset otherAnchor, float restLength, float stiffness, float damping, float breakingForce = 0.0f);

    // keep sprites at a particular angle relative to one another via a rotary spring
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   rotarySpring(Sprite* otherSprite, float restAngle, float stiffness, float damping, float breakingForce = 0.0f);

    // limit the angle another sprite can have relative to this one
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   rotaryLimit(Sprite* otherSprite, float minAngle, float maxAngle, float breakingForce = 0.0f);

    // like a socket wrench. ratchetInterval is the distance between “clicks”, phase is the initial 
    // angular offset to use when deciding where the ratchet angles are.
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   ratchet(Sprite* otherSprite, float rachetInterval, float phase = 0.0f, float breakingForce = 0.0f);

    // keep another sprite's rotation relative to this one at a particular gear ratio
    // optional breaking force at which the joint (and and any other connections to that sprite) are broken
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   gear(Sprite* otherSprite, float gearRatio, float initialAngle = 0.0f, float breakingForce = 0.0f);

    // keep spin of another sprite at a constant rate compared to this one
    // returns the cpConstraint pointer in case you want to do anything special with it
    
    cpConstraint*   motor(Sprite* otherSprite, float spin, float maxTorque = std::numeric_limits<float>::infinity());
    
    // remove a single joint
    void            removeJoint(cpConstraint* joint);
    
    // remove all connections. Optionally only remove all conncetions to a specific other sprite
    void            disconnect(Sprite* otherSprite = 0);

    void            makeJointBreakable(cpConstraint* joint, float breakingForce, Sound* breakSound = 0);
    void            makeJointUnbreakable(cpConstraint* joint);
  #endif // PDG_USE_CHIPMUNK_PHYSICS
    /// @endcond

#ifndef PDG_INTERNAL_LIB
protected:
#endif
/// @cond INTERNAL
    Sprite();

  #ifdef PDG_SPRITER_SUPPORT
    // for use by SpriteLayer::createSpriteFromSpriter functions
    // Borrowed-model construction is used by native adapters that own the model.
    Sprite(SpriterEngine::EntityInstance* entityInstance, SpriterEngine::SpriterModel* spriterModel);
    Sprite(SpriterEngine::EntityInstance* entityInstance, const std::shared_ptr<SpriterEngine::SpriterModel>& spriterModel);
  #endif

    void animationStarting(Animation& a) override;
    virtual void easingCompleted(const Animation& a) override;

	virtual void locationChanged(const Offset& delta) override;
	virtual void sizeChanged(float deltaW, float deltaH) override;
    virtual void scaleChanged(const Offset& delta) override;
	virtual void rotationChanged(float deltaRadians) override;
	virtual void flipChanged(bool xFlipped, bool yFlipped) override;

  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    cpSpace* getSpace();
    
    void            setupCollideGroup(Sprite* otherSprite);
    
    void			initCpBody();
    void			freeCpBody();

    cpConstraint*   mBreakableJoints[MAX_BREAKABLE_JOINTS_PER_SPRITE];
    int             mNumBreakableJoints;
    long            mCollideGroup;
    bool            mStatic;
  #endif

    virtual ~Sprite();
    std::vector<const float*> tweenFields() const override;

    // Mouse hit testing remains independent of physical collider selection.
	bool hitTest(const Point& p);
	
	void recalcOnscreenAndInBounds();
    
	
	// override the way we post events to go to the sprite layer first rather than directly to
	// the sprite manager
	virtual bool postEvent(long inEventType, void* inEventData, EventEmitter* fromEmitter = 0) override; // returns true if event handled
    
	// functions called from the layer
	virtual void	draw();
	virtual void	doAnimate(double msElapsed, bool layerDoCollisions);
    
 	int mNumFrames;

    typedef struct {
        ImageImpl*	image;
        ImageImpl*  collisionMask;
        Point	center;
        int		imageFrameNum;
        int		centerOffsetX;
        int		centerOffsetY;
    } FrameInfoT;


	// animation data
	FrameInfoT		mFrames[MAX_FRAMES_PER_SPRITE];
	float			mFps;
	float			mCurrFramePrecise;
	int				mCurrFrame;
	int				mFirstFrame;
	int				mLastFrame;
	bool			mLoopAnim;
	bool			mBackToFrontAnim;
	bool			mBidirectionalAnim;
	bool			mSpriteAnimating;
	bool			mSpriteAnimatingBackwardsNow;
	
	int				mMouseDetectMode;

  #ifdef PDG_SPRITER_SUPPORT
    AnimationBoneId mAnimationPhysicsRootOverride = animation_NoBone;
    std::vector<std::string> mAnimationPhysicsSetupWarnings;
	SpriterEngine::EntityInstance*	mEntityInstance;
	SpriterEngine::SpriterModel*	mSpriterModel;
    std::shared_ptr<SpriterEngine::SpriterModel> mSpriterModelOwner;
	float					mEntityScaleX;
	float					mEntityScaleY;
	
	// Character maps
	std::vector<std::string> mAppliedCharacterMaps;
	
	// Event system
	bool mSpriterEventsEnabled;
	
	// Animation state
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    std::unique_ptr<AnimationPhysicsRig> mAnimationPhysics;
    std::vector<Part*> mAnimationPhysicsParts;
    std::map<Part*, Part*> mAnimationPhysicsMembers;
    void updateAnimationPhysicsMembers(std::map<Part*, Part*> members, bool disconnectBoundary = true);
    uint32_t selectAnimationPhysicsMemberRoot(const std::map<Part*, Part*>& members) const;
    std::unique_ptr<AnimationPose> mAnimationDesired;
    cpBodyType mAnimationSavedBodyType = CP_BODY_TYPE_DYNAMIC;
    cpShapeFilter mAnimationSavedFilter = CP_SHAPE_FILTER_ALL;
    double mAnimationSavedMass = 1, mAnimationSavedMoment = 1;
    double mAnimationPhysicsUnitsPerMeter = 1;
    void prepareAnimationPhysics(double elapsed);
    void publishAnimationPhysics();
    void finishAnimationPhysics();
    AnimationPhysicsRig& animationPhysicsControl() const;
#endif
    Sprite& changeAnimationPhysicsMode(int mode, std::optional<AnimationBoneId> bone, bool descendants,
        double seconds, int direction, bool disabling = false);
    AnimationBoneId animationPhysicsBone(const char* name) const;
    void releaseAnimationPhysics();
    void notifyAnimationPhysicsRecovery(const AnimationPhysicsRecovery& recovery);
    void dispatchSpriterTriggers(double deltaSeconds);
    AnimationDrawings mAnimationDrawings;
    void drawAnimationArt();
	mutable std::unique_ptr<SpriterPoseAdapter> mAnimationPoseAdapter;
    mutable std::shared_ptr<AnimationPipeline> mAnimationPipeline;
    mutable std::map<AnimationBoneId,std::shared_ptr<Bone>> mBones;
    void clearBoneControls();
    struct AnimationIKState { AnimationTwoBoneIK config; AnimationIKResult result; std::shared_ptr<struct SpriteJiggleState> jiggle; };
    mutable std::map<AnimationModifierId, std::shared_ptr<AnimationIKState>> mAnimationIK;
    struct FABRIKState { AnimationFABRIK config; AnimationFABRIKResult result; };
    mutable std::map<AnimationModifierId,std::shared_ptr<FABRIKState>> mAnimationFABRIK;
    mutable std::map<AnimationModifierId,std::shared_ptr<struct SpriteJiggleState>> mAnimationJiggle;
	std::shared_ptr<SpriterRigSchema> mAnimationRigSchema;
	mutable std::string mAnimationRigError;
	mutable int mAnimationDebugDraw = animationDebug_None;
	std::string mBlendTargetName;
	bool mIsBlending;
	double mBlendDurationMs;
	double mBlendElapsedMs;
	float mBlendProgress;
	std::vector<std::string> mSpriterAnimationNames;
	bool mIsAnimationPaused;
	bool mIsAnimationFinished;
	
	// AttachPoint tracking
    Sprite* mSpriterAttachmentOwner = nullptr;
	std::map<std::string, Sprite*> mAttachedSprites;
	
	// Collision box cache and bounds optimization
	mutable std::map<std::string, RotatedRect> mSpriterCollisionBoxCache;
	mutable bool mSpriterCollisionBoxCacheValid;
	mutable std::string mFallbackCollisionBoxName;
	mutable Rect mColliderBounds;
	mutable bool mColliderBoundsValid;
	mutable bool mSpriterPoseDirty;

	// Rebuilt only when selecting an entity, never by hasAnimation().
	void cacheSpriterAnimationNames();
	void invalidateSpriterPose() const;
	void refreshSpriterPose() const;
	AnimationTransform spriterRootTransform() const;
	void publishSpriterPose(double deltaSeconds = 0,double boneSeconds = -1) const;
    void selectAnimationTime(const char* clip, double normalizedSeconds);
	void drawAnimationDebug() const;
	void updateAttachedSprites() const;
	void syncSpriterRoot() const;
	void resumeSpriterBlend();
	void clearAttachedSprites();

	// Private helper methods for Spriter collision boxes
	void calcColliderBounds() const;
	std::map<std::string, RotatedRect> getActiveSpriterCollisionBoxes() const;
	std::vector<std::string> getActiveSpriterCollisionBoxNames() const;
	bool checkSpriterCollisionBoxPointCollision(const Point& p);
  #endif // PDG_SPRITER_SUPPORT

  #ifndef PDG_NO_GUI
	// control which port this sprite draws into
    Port*   setPort(Port* newPort) { Port* port = mPort; mPort = newPort; return port; }
	
    Port* mPort;
  #endif

	SpriteLayer* mLayer;
	Sprite* mNextSprite;
	Sprite* mPrevSprite;
    
	float			mOpacity;
	int				mFadeCompleteAction;
	
  #ifndef PDG_NO_GUI
	ISpriteDrawHelper*	mDrawHelper;
	ISpriteDrawHelper*	mPostDrawHelper;
  #endif	



	bool mOnscreen;
	bool mInBounds;
	bool mCompletelyInBounds;
	
	uint32 iid;

/// @endcond
};


inline int	
Sprite::getFrameCount() { 
    return mNumFrames; 
}

inline Sprite& 
Sprite::moveToFront() {
    if(recordOperation("moveToFront", captureAnimationArguments())) return *this;
    moveInFrontOf(0);
    return *this;
}

inline Sprite& 
Sprite::moveToBack() {
    if(recordOperation("moveToBack", captureAnimationArguments())) return *this;
    moveBehind(0); 
    return *this;
}

inline Sprite& 
Sprite::setWantsCollideWallEvents(bool wantsThem) {
    if(recordOperation("setWantsCollideWallEvents", captureAnimationArguments(wantsThem))) return *this;
	wantsWallCollide = wantsThem;
	if (wantsThem) recalcOnscreenAndInBounds();
	return *this;
}

inline Sprite&	
Sprite::setWantsAnimLoopEvents(bool wantsThem) {
    if(recordOperation("setWantsAnimLoopEvents", captureAnimationArguments(wantsThem))) return *this;
	wantsAnimLoop = wantsThem; 
	return *this; 
}

inline Sprite&	
Sprite::setWantsAnimEndEvents(bool wantsThem) {
    if(recordOperation("setWantsAnimEndEvents", captureAnimationArguments(wantsThem))) return *this;
	wantsAnimEnd = wantsThem; 
	return *this; 
}

#ifndef PDG_NO_GUI
inline Sprite&	
Sprite::setWantsOffscreenEvents(bool wantsThem) {
    if(recordOperation("setWantsOffscreenEvents", captureAnimationArguments(wantsThem))) return *this;
	wantsOffscreen = wantsThem; 
	if (wantsThem) recalcOnscreenAndInBounds();
	return *this; 
}
#endif // PDG_NO_GUI

#ifdef PDG_SPRITER_SUPPORT
inline bool	Sprite::isSpriterSprite() const {
	return mEntityInstance != nullptr;
}
#endif // PDG_SPRITER_SUPPORT


} // end namespace pdg


#endif // PDG_SPRITE_H_INCLUDED
