/* This file automatically generated from docs/javascript/pdg-js.i */



namespace pdg
{

    const all_events = 0;
    const eventType_Shutdown = 2;
    const eventType_Timer = 3;
    const eventType_KeyDown = 4;
    const eventType_KeyUp = 5;
    const eventType_KeyPress = 6;
    const eventType_MouseDown = 7;
    const eventType_MouseUp = 8;
    const eventType_MouseMove = 9;
    const eventType_MouseEnter = 22;
    const eventType_MouseLeave = 23;
    const eventType_PortResized = 15;
    const eventType_ScrollWheel = 16;
    const eventType_SpriteTouch = 19;
    const eventType_SpriteAnimate = 17;
    const eventType_SpriteLayer = 18;
    const eventType_SpriteCollide = 20;
    const eventType_SpriteBreak = 21;
    const eventType_SoundEvent = 14;
    const eventType_PortDraw = 24;
    const soundEvent_DonePlaying = 0;
    const soundEvent_Looping = 1;
    const soundEvent_FailedToPlay = 2;
    const key_Break = 1;
    const key_Home = 2;
    const key_End = 3;
    const key_Clear = 4;
    const key_Help = 5;
    const key_Pause = 6;
    const key_Mute = 7;
    const key_Backspace = 8;
    const key_Delete = 127;
    const key_Tab = 9;
    const key_PageUp = 11;
    const key_PageDown = 12;
    const key_Return = 13;
    const key_Enter = 13;
    const key_F1 = 14;
    const key_F2 = 15;
    const key_F3 = 16;
    const key_F4 = 17;
    const key_F5 = 18;
    const key_F6 = 19;
    const key_F7 = 20;
    const key_F8 = 21;
    const key_F9 = 22;
    const key_F10 = 23;
    const key_F11 = 24;
    const key_F12 = 25;
    const key_FirstF = 14;
    const key_LastF = 25;
    const key_Insert = 26;
    const key_Escape = 27;
    const key_LeftArrow = 28;
    const key_RightArrow = 29;
    const key_UpArrow = 30;
    const key_DownArrow = 31;
    const key_FirstPrintable = 32;
    const screenPos_Normal = 0;
    const screenPos_Rotated180 = 1;
    const screenPos_Rotated90Clockwise = 2;
    const screenPos_Rotated90CounterClockwise = 3;
    const screenPos_FaceUp = 4;
    const screenPos_FaceDown = 5;
    const textStyle_Plain = 0;
    const textStyle_Bold = 1;
    const textStyle_Italic = 2;
    const textStyle_Underline = 4;
    const textStyle_Centered = 16;
    const textStyle_LeftJustified = 0;
    const textStyle_RightJustified = 32;
    const fit_None = 0;
    const fit_Height = 1;
    const fit_Width = 2;
    const fit_Inside = 3;
    const fit_Fill = 4;
    const fit_FillKeepProportions = 5;
    const init_CreateUniqueNewFile = 0;
    const init_OverwriteExisting = 1;
    const init_AppendToExisting = 2;
    const init_StdOut = 3;
    const init_StdErr = 4;
    const duration_Constant = -1;
    const duration_Instantaneous = 0;
    const animate_StartToEnd = 0;
    const animate_EndToStart = 1;
    const animate_Unidirectional = 0;
    const animate_Bidirectional = 2;
    const animate_NoLooping = 0;
    const animate_Looping = 4;
    const start_FromFirstFrame = -1;
    const start_FromLastFrame = -2;
    const all_Frames = 0;
    const action_CollideSprite = 0;
    const action_CollideWall = 1;
    const action_Offscreen = 2;
    const action_Onscreen = 3;
    const action_ExitLayer = 4;
    const action_AnimationLoop = 8;
    const action_AnimationEnd = 9;
    const action_FadeComplete = 10;
    const action_FadeInComplete = 11;
    const action_FadeOutComplete = 12;
    const action_JointBreak = 13;
    const touch_MouseEnter = 20;
    const touch_MouseLeave = 21;
    const touch_MouseDown = 22;
    const touch_MouseUp = 23;
    const touch_MouseClick = 24;
    const collide_None = 0;
    const collide_Point = 1;
    const collide_BoundingBox = 2;
    const collide_CollisionRadius = 3;
    const collide_AlphaChannel = 4;
    const collide_Last = 4;
    const action_ErasePort = 40;
    const action_PreDrawLayer = 41;
    const action_PostDrawLayer = 42;
    const action_DrawPortComplete = 43;
    const action_AnimationStart = 44;
    const action_PreAnimateLayer = 45;
    const action_PostAnimateLayer = 46;
    const action_AnimationComplete = 47;
    const action_ZoomComplete = 48;
    const action_LayerFadeInComplete = 49;
    const action_LayerFadeOutComplete = 50;
    const facing_North = 0;
    const facing_East = 64;
    const facing_South = 128;
    const facing_West = 192;
    const facing_Ignore = 256;
    const flipped_None = 0;
    const flipped_Horizontal = 64;
    const flipped_Vertical = 128;
    const flipped_Both = 192;
    const flipped_Ignore = 256;
    const timer_OneShot = true;
    const timer_Repeating = false;
    const timer_Never = -1;
    const linearTween = 0;
    const easeInQuad = 1;
    const easeOutQuad = 2;
    const easeInOutQuad = 3;
    const easeInCubic = 4;
    const easeOutCubic = 5;
    const easeInOutCubic = 6;
    const easeInQuart = 7;
    const easeOutQuart = 8;
    const easeInQuint = 10;
    const easeOutQuint = 11;
    const easeInOutQuint = 12;
    const easeInSine = 13;
    const easeOutSine = 14;
    const easeInOutSine = 15;
    const easeInExpo = 16;
    const easeOutExpo = 17;
    const easeInOutExpo = 18;
    const easeInCirc = 19;
    const easeOutCirc = 20;
    const easeInOutCirc = 21;
    const easeInBounce = 22;
    const easeOutBounce = 23;
    const easeInOutBounce = 24;
    const easeInBack = 25;
    const easeOutBack = 26;
    const easeInOutBack = 27;
    const ser_Positions = 1;
    const ser_ZOrder = 2;
    const ser_Sizes = 4;
    const ser_Animations = 8;
    const ser_Motion = 16;
    const ser_Forces = 32;
    const ser_Physics = 64;
    const ser_LayerDraw = 128;
    const ser_ImageRefs = 256;
    const ser_SCMLRefs = 512;
    const ser_HelperRefs = 1024;
    const ser_HelperObjs = 8192;
    const ser_InitialData = 16384;
    const ser_Micro = 3;
    const ser_Update = 127;
    const ser_Full = 18303;
    boolean running;
    boolean quitting;
    const lftTop = 0;
    const rgtTop = 1;
    const rgtBot = 2;
    const lftBot = 3;
    boolean hasNetwork;
    FileManager fs;
    EventManager evt;
    TimerManager tm;
    ResourceManager res;
    ConfigManager cfg;
    LogManager lm;
    GraphicsManager gfx;
    boolean hasGraphics;
    SoundManager snd;
    boolean hasSound;
    string[] argv;

    number rand ();

    srand (uint seed);

    setSerializationDebugMode (bool debugMode);

    registerEasingFunction (function easingFunc);

    FileManager getFileManager ();

    LogManager getLogManager ();

    ConfigManager getConfigManager ();

    ResourceManager getResourceManager ();

    EventManager getEventManager ();

    TimerManager getTimerManager ();

    registerSerializableClass (function klass);

    GraphicsManager getGraphicsManager ();

    SoundManager getSoundManager ();

    SpriteLayer createSpriteLayer (Port port = null);

    cleanupSpriteLayer (SpriteLayer layer);

    TileLayer createTileLayer (Port port = null);

    quit ();

    run ();

    idle ();

    openDebugger ();

    openConsole ();

    openCommandPort (int port = 5757);

    log (string msg);

    info (string msg);

    warn (string msg);

    fatal (string msg);

    error (string msg);

    debug (string msg);

    trace (string msg);

    captureConsole ();

    IEventHandler on (int eventType, function func);

    IEventHandler onShutdown (function func);

    IEventHandler onTimer (function func);

    IEventHandler onKeyDown (function func);

    IEventHandler onKeyUp (function func);

    IEventHandler onKeyPress (function func);

    IEventHandler onMouseDown (function func);

    IEventHandler onMouseUp (function func);

    IEventHandler onMouseMove (function func);

    startRepl ();

    class MemBlock
    {
        public:

            BinaryString getData ();

            number getDataSize ();

            number getByte (uint i);

            BinaryString getBytes (uint start, uint len);

            Buffer toBuffer ();
    };

    class FileManager
    {
        public:

            object findFirst (string inFindName);

            object findNext (object inFindData);

            findClose (object inFindData);

            string getApplicationDataDirectory ();

            string getApplicationDirectory ();

            string getApplicationResourceDirectory ();

            string[] findFiles (string name);

            string[] findDirs (string name);
    };

    class LogManager
    {
        public:
            const init_CreateUniqueNewFile = 0;
            const init_OverwriteExisting = 1;
            const init_AppendToExisting = 2;
            const init_StdOut = 3;
            const init_StdErr = 4;

            number getLogLevel ();

            LogManager setLogLevel (int inLogLevel);

            initialize (string inLogNameBase, int initMode = LogManager.init_StdOut);

            writeLogEntry (int level, string category, string message);

            string binaryDump (BinaryString inData, int length = 0, int bytesPerLine = 20);

            string binaryDump (MemBlock inData, int length = 0, int bytesPerLine = 20);
    };

    class ConfigManager
    {
        public:

            boolean useConfig (string inConfigName);

            string getConfigString (string inConfigItemName);

            number getConfigLong (string inConfigItemName);

            number getConfigFloat (string inConfigItemName);

            boolean getConfigBool (string inConfigItemName);

            setConfigString (string inConfigItemName, string inValue);

            setConfigLong (string inConfigItemName, int inValue);

            setConfigFloat (string inConfigItemName, number inValue);

            setConfigBool (string inConfigItemName, boolean inValue);
    };

    class ResourceManager
    {
        public:

            string getLanguage ();

            ResourceManager setLanguage (string inLanguage);

            number openResourceFile (string filename);

            closeResourceFile (int refNum);

            Image getImage (string imageName);

            ImageStrip getImageStrip (string imageName);

            string getString (int id, int substring = -1);

            number getResourceSize (string resourceName);

            BinaryString getResource (string resourceName);

            string getResourcePaths ();
    };

    class Serializer
    {
        public:

            serialize_8 (number val);

            serialize_8u (number val);

            serialize_d (number val);

            serialize_f (number val);

            serialize_4 (int val);

            serialize_4u (uint val);

            serialize_3u (uint val);

            serialize_2 (int val);

            serialize_2u (uint val);

            serialize_1 (int val);

            serialize_1u (uint val);

            serialize_bool (boolean val);

            serialize_uint (uint val);

            serialize_color (Color val);

            serialize_offset (Offset val);

            serialize_point (Point val);

            serialize_vector (Vector val);

            serialize_rect (Rect val);

            serialize_rotr (RotatedRect val);

            serialize_quad (Quad val);

            serialize_str (string str);

            serialize_mem (BinaryString mem);

            serialize_mem (MemBlock mem);

            serialize_obj (ISerializable obj);

            number serializedSize (string arg);

            number serializedSize (boolean arg);

            number serializedSize (uint arg);

            number serializedSize (Color arg);

            number serializedSize (Offset arg);

            number serializedSize (Point arg);

            number serializedSize (Vector arg);

            number serializedSize (Rect arg);

            number serializedSize (RotatedRect arg);

            number serializedSize (Quad arg);

            number serializedSize (MemBlock arg);

            number serializedSize (ISerializable arg);

            number getDataSize ();

            MemBlock getDataPtr ();
    };

    class Deserializer
    {
        public:

            number deserialize_8 ();

            number deserialize_8u ();

            number deserialize_d ();

            number deserialize_f ();

            number deserialize_4 ();

            number deserialize_4u ();

            number deserialize_3u ();

            number deserialize_2 ();

            number deserialize_2u ();

            number deserialize_1 ();

            number deserialize_1u ();

            boolean deserialize_bool ();

            number deserialize_uint ();

            Color deserialize_color ();

            Offset deserialize_offset ();

            Point deserialize_point ();

            Vector deserialize_vector ();

            Rect deserialize_rect ();

            RotatedRect deserialize_rotr ();

            Quad deserialize_quad ();

            string deserialize_str ();

            MemBlock deserialize_mem ();

            number deserialize_memGetLen ();

            ISerializable deserialize_obj ();

            setDataPtr (BinaryString data);

            setDataPtr (MemBlock data);
    };

    class ISerializable
    {
        public:
    };

    class IEventHandler
    {
        public:
    };

    class EventEmitter
    {
        public:

            addHandler (IEventHandler inHandler, int inEventType = all_events);

            removeHandler (IEventHandler inHandler, int inEventType = all_events);

            clear ();

            blockEvent (int inEventType);

            unblockEvent (int inEventType);
    };

    class EventManager : public EventEmitter
    {
        public:

            boolean isKeyDown (string unicodeChar);

            boolean isKeyDown (uint utf16CharCode);

            boolean isRawKeyDown (int keyCode);

            boolean isButtonDown (int buttonNumber = 0);

            object getDeviceOrientation (boolean absolute = false);
    };

    class TimerManager : public EventEmitter
    {
        public:

            startTimer (int id, uint delay, boolean oneShot = true);

            cancelTimer (int id);

            cancelAllTimers ();

            delayTimer (int id, uint delay);

            delayTimerUntil (int id, uint msTime);

            pause ();

            unpause ();

            boolean isPaused ();

            pauseTimer (int id);

            unpauseTimer (int id);

            boolean isTimerPaused (int id);

            number getWhenTimerFiresNext (int id);

            number getMilliseconds ();

            IEventHandler onTimeout (function func, int delay);

            IEventHandler onInterval (function func, int interval);
    };

    class IAnimationHelper
    {
        public:
    };

    class Animated
    {
        public:

            Rect getBoundingBox ();

            Rect getRotatedBounds ();

            Point getLocation ();

            Animated setLocation (Point inLocation);

            number getSpeed ();

            Animated setSpeed (number inSpeed);

            Vector getVelocity ();

            Animated setVelocity (Vector deltaPerSec);

            Animated setVelocity (number deltaXPerSec, number deltaYPerSec);

            number getWidth ();

            Animated setWidth (number inWidth);

            number getHeight ();

            Animated setHeight (number inHeight);

            number getRotation ();

            Animated setRotation (number inRotation);

            Offset getCenterOffset ();

            Animated setCenterOffset (Offset inCenterOffset);

            number getSpin ();

            Animated setSpin (number inSpin);

            number getMass ();

            Animated setMass (number inMass);

            number getMoveFriction ();

            Animated setMoveFriction (number inMoveFriction);

            number getSpinFriction ();

            Animated setSpinFriction (number inSpinFriction);

            number getSizeFriction ();

            Animated setSizeFriction (number inSizeFriction);

            move (Offset delta, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            moveTo (Point where, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            Animated setVelocityInRadians (number speed, number direction);

            number getMovementDirectionInRadians ();

            stopMoving ();

            accelerate (number deltaSpeed, int msDuration = duration_Instantaneous, int easing = linearTween);

            accelerateTo (number speed, int msDuration = duration_Instantaneous, int easing = linearTween);

            Animated setSize (number width, number height);

            grow (number factor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            stretch (number widthFactor, number heightFactor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            startGrowing (number amountPerSecond);

            stopGrowing ();

            startStretching (number widthPerSecond, number heightPerSecond);

            stopStretching ();

            resize (number deltaWidth, number deltaHeight, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            resizeTo (number width, number height, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            rotate (number radians, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            rotateTo (number radiansRotation, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            stopSpinning ();

            changeCenter (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            changeCenterTo (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);

            Animated wait (int msDuration);

            Animated setFriction (number frictionCoefficient);

            applyForce (Vector force, int msDuration = duration_Instantaneous);

            applyTorque (number forceSpin, int msDuration = duration_Instantaneous);

            stopAllForces ();

            addAnimationHelper (IAnimationHelper helper);

            removeAnimationHelper (IAnimationHelper helper);

            clearAnimationHelpers ();

            boolean animate (int msElapsed);
    };

    class CpArbiter
    {
        public:

            boolean isFirstContact ();

            number getCount ();

            Vector getNormal (int i);

            Point getPoint (int i);

            number getDepth (int i);
    };

    class CpConstraint
    {
        public:

            string getType ();

            activateBodies ();

            number getImpulse ();

            number getMaxForce ();

            cpConstraint setMaxForce (number inMaxForce);

            number getErrorBias ();

            cpConstraint setErrorBias (number inErrorBias);

            number getMaxBias ();

            cpConstraint setMaxBias (number inMaxBias);

            Sprite getSprite ();

            Sprite getOtherSprite ();

            Offset getAnchor ();

            cpConstraint setAnchor (Offset inAnchor);

            Offset getOtherAnchor ();

            cpConstraint setOtherAnchor (Offset inOtherAnchor);

            number getPinDist ();

            cpConstraint setPinDist (number inPinDist);

            number getSpringStiffness ();

            cpConstraint setSpringStiffness (number inSpringStiffness);

            number getSpringDamping ();

            cpConstraint setSpringDamping (number inSpringDamping);

            number getSlideMinDist ();

            cpConstraint setSlideMinDist (number inSlideMinDist);

            number getSlideMaxDist ();

            cpConstraint setSlideMaxDist (number inSlideMaxDist);

            Offset getGrooveStart ();

            cpConstraint setGrooveStart (Offset inGrooveStart);

            Offset getGrooveEnd ();

            cpConstraint setGrooveEnd (Offset inGrooveEnd);

            number getSpringRestLength ();

            cpConstraint setSpringRestLength (number inSpringRestLength);

            number getRotarySpringRestAngle ();

            cpConstraint setRotarySpringRestAngle (number inRotarySpringRestAngle);

            number getMinAngle ();

            cpConstraint setMinAngle (number inMinAngle);

            number getMaxAngle ();

            cpConstraint setMaxAngle (number inMaxAngle);

            number getRatchetAngle ();

            cpConstraint setRatchetAngle (number inRatchetAngle);

            number getRatchetPhase ();

            cpConstraint setRatchetPhase (number inRatchetPhase);

            number getRatchetInterval ();

            cpConstraint setRatchetInterval (number inRatchetInterval);

            number getGearRatio ();

            cpConstraint setGearRatio (number inGearRatio);

            number getGearInitialAngle ();

            cpConstraint setGearInitialAngle (number inGearInitialAngle);

            number getMotorSpinRate ();

            cpConstraint setMotorSpinRate (number inMotorSpinRate);
    };

    class CpSpace
    {
        public:

            useSpatialHash (number dim, int count);

            reindexStatic ();

            step (number dt);

            number getIdleSpeedThreshold ();

            cpSpace setIdleSpeedThreshold (number inIdleSpeedThreshold);

            number getSleepTimeThreshold ();

            cpSpace setSleepTimeThreshold (number inSleepTimeThreshold);

            number getCollisionSlop ();

            cpSpace setCollisionSlop (number inCollisionSlop);

            number getCollisionBias ();

            cpSpace setCollisionBias (number inCollisionBias);

            number getCollisionPersistence ();

            cpSpace setCollisionPersistence (number inCollisionPersistence);

            boolean getEnableContactGraph ();

            cpSpace setEnableContactGraph (boolean inEnableContactGraph);
    };

    class ISpriteDrawHelper
    {
        public:
    };

    class ISpriteCollideHelper
    {
        public:
    };

    class Sprite : public Animated , public EventEmitter , public ISerializable
    {
        public:

            number getMyClassTag ();

            uint getSerializedSize (Serializer serializer);

            serialize (Serializer serializer);

            deserialize (Deserializer deserializer);

            Rect getFrameRotatedBounds (int frame);

            Sprite setFrame (int frame);

            number getCurrentFrame ();

            number getFrameCount ();

            startFrameAnimation (number fps, int startingFrame = start_FromFirstFrame, int numFrames = all_Frames, int animateFlags = animate_Looping);

            stopFrameAnimation ();

            boolean setWantsAnimLoopEvents (boolean wantsThem = true);

            boolean setWantsAnimEndEvents (boolean wantsThem = true);

            Sprite setWantsCollideWallEvents (boolean wantsThem = true);

            addFramesImage (Image image, int startingFrame = start_FromFirstFrame, int numFrames = all_Frames);

            boolean hasAnimation ( int animationId );

            boolean hasAnimation ( string animationName );

            startAnimation ( int animationId );

            startAnimation ( string animationName );

            Sprite setEntityScale (number xScale, number yScale);

            changeFramesImage (Image oldImage, Image newImage);

            offsetFrameCenters (int offsetX, int offsetY, Image image = null, int startingFrame = start_FromFirstFrame, int numFrames = all_Frames);

            Offset getFrameCenterOffset (Image image = null, int frameNum = 0);

            Sprite setOpacity (number opacity);

            number getOpacity ();

            fadeTo (number targetOpacity, int msDuration, int easing = linearTween);

            fadeIn (int msDuration, int easing = linearTween);

            fadeOut (int msDuration, int easing = linearTween);

            boolean isBehind (Sprite sprite);

            int getZOrder ();

            Sprite moveBehind (Sprite sprite);

            Sprite moveInFrontOf (Sprite sprite);

            Sprite moveToFront ();

            Sprite moveToBack ();

            Sprite enableCollisions (int collisionType = collide_AlphaChannel);

            Sprite disableCollisions ();

            Sprite setCollisionRadius (number pixelRadius);

            number getCollisionRadius ();

            useCollisionMask (Image frameImage, Image maskImage);

            setCollisionHelper (ISpriteCollideHelper helper);

            Sprite setElasticity (number elasticity);

            number getElasticity ();

            SpriteLayer getLayer ();

            setDrawHelper (ISpriteDrawHelper helper);

            setPostDrawHelper (ISpriteDrawHelper helper);

            boolean setWantsMouseOverEvents (boolean wantsThem = true);

            boolean setWantsClickEvents (boolean wantsThem = true);

            number setMouseDetectMode (int collisionType = collide_BoundingBox);

            Sprite setWantsOffscreenEvents (boolean wantsThem = true);

            Sprite makeStatic ();

            number getFriction ();

            Sprite setCollideGroup (int group);

            number getCollideGroup ();

            CpConstraint pinJoint (Offset anchor, Sprite otherSprite, Offset otherAnchor, number breakingForce = 0);

            CpConstraint slideJoint (Offset anchor, Sprite otherSprite, Offset otherAnchor, number minDist, number maxDist, number breakingForce = 0);

            CpConstraint pivotJoint (Sprite otherSprite, Point pivot, number breakingForce = 0);

            CpConstraint grooveJoint (Offset grooveStart, Offset grooveEnd, Sprite otherSprite, Offset otherAnchor, number breakingForce = 0);

            CpConstraint springJoint (Offset anchor, Sprite otherSprite, Offset otherAnchor, number restLength, number stiffness, number damping, number breakingForce = 0);

            CpConstraint rotarySpring (Sprite otherSprite, number restAngle, number stiffness, number damping, number breakingForce = 0);

            CpConstraint rotaryLimit (Sprite otherSprite, number minAngle, number maxAngle, number breakingForce = 0);

            CpConstraint ratchet (Sprite otherSprite, number rachetInterval, number phase, number breakingForce = 0);

            CpConstraint gear (Sprite otherSprite, number gearRatio, number initialAngle = 0, number breakingForce = 0);

            CpConstraint motor (Sprite otherSprite, number spin, number maxTorque = INFINITY);

            removeJoint (CpConstraint joint);

            disconnect (Sprite otherSprite);

            makeJointBreakable (CpConstraint joint, number breakingForce);

            makeJointUnbreakable (CpConstraint joint);

            IEventHandler on (int eventCode, function func);

            IEventHandler onCollideSprite (function func);

            IEventHandler onCollideWall (function func);

            IEventHandler onOffscreen (function func);

            IEventHandler onOnscreen (function func);

            IEventHandler onExitLayer (function func);

            IEventHandler onAnimationLoop (function func);

            IEventHandler onAnimationEnd (function func);

            IEventHandler onFadeComplete (function func);

            IEventHandler onFadeInComplete (function func);

            IEventHandler onFadeOutComplete (function func);

            IEventHandler onMouseEnter (function func);

            IEventHandler onMouseLeave (function func);

            IEventHandler onMouseDown (function func);

            IEventHandler onMouseUp (function func);

            IEventHandler onMouseClick (function func);
    };

    class SpriteLayer : public Animated , public EventEmitter , public ISerializable
    {
        public:

            number getMyClassTag ();

            uint getSerializedSize (Serializer serializer);

            serialize (Serializer serializer);

            deserialize (Deserializer deserializer);

            SpriteLayer setSerializationFlags (uint flags);

            startAnimations ();

            stopAnimations ();

            hide ();

            show ();

            boolean isHidden ();

            fadeIn (int msDuration, int easing = linearTween);

            fadeOut (int msDuration, int easing = linearTween);

            moveBehind (SpriteLayer layer);

            moveInFrontOf (SpriteLayer layer);

            moveToFront ();

            moveToBack ();

            int getZOrder ();

            moveWith (SpriteLayer layer, number moveRatio = 1.0, number zoomRatio = 1.0 );

            Sprite findSprite (int id);

            Sprite getNthSprite (int index);

            int getSpriteZOrder (Sprite sprite);

            boolean isSpriteBehind (Sprite sprite, Sprite otherSprite);

            boolean hasSprite (Sprite sprite);

            addSprite (Sprite newSprite);

            removeSprite (Sprite oldSprite);

            removeAllSprites ();

            enableCollisions ();

            disableCollisions ();

            enableCollisionsWithLayer (SpriteLayer otherLayer);

            disableCollisionsWithLayer (SpriteLayer otherLayer);

            Sprite createSprite ();

            Port getSpritePort ();

            setSpritePort (Port port);

            setOrigin (Point origin);

            Point getOrigin ();

            setAutoCenter (boolean autoCenter = true);

            setFixedMoveAxis (boolean fixedAxis = true);

            setZoom (number zoomLevel);

            number getZoom ();

            zoomTo (number zoomLevel, int msDuration, int easing = easeInOutQuad, Rect keepInRect = Rect(0,0), Point centerOn = Point(0,0) );

            zoom (number deltaZoomLevel, int msDuration, int easing = easeInOutQuad, Rect keepInRect = Rect(0,0), Point centerOn = Point(0,0) );

            Point layerToPortPoint (Point p);

            Offset layerToPortOffset (Offset o);

            Vector layerToPortVector (Vector v);

            Rect layerToPortRect (Rect r);

            Quad layerToPortQuad (Quad q);

            Point portToLayerPoint (Point p);

            Offset portToLayerOffset (Offset o);

            Vector portToLayerVector (Vector v);

            Rect portToLayerRect (Rect r);

            Quad portToLayerQuad (Quad q);

            setGravity (number gravity, boolean keepItDownward = true);

            setUseChipmunkPhysics (boolean useIt = true);

            setStaticLayer (boolean isStatic = true);

            setKeepGravityDownward (boolean keepItDownward = true);

            setDamping (number damping);

            CpSpace getSpace ();

            Sprite createSpriteFromSCML (string inSCML, string inEntityName = null);

            Sprite createSpriteFromSCMLFile (string inFileName, string inEntityName = null);

            Sprite createSpriteFromSCMLEntity (string inEntityName);

            IEventHandler on (int eventCode, function func);

            IEventHandler onCollideSprite (function func);

            IEventHandler onCollideWall (function func);

            IEventHandler onOffscreen (function func);

            IEventHandler onOnscreen (function func);

            IEventHandler onExitLayer (function func);

            IEventHandler onAnimationLoop (function func);

            IEventHandler onAnimationEnd (function func);

            IEventHandler onFadeComplete (function func);

            IEventHandler onFadeInComplete (function func);

            IEventHandler onFadeOutComplete (function func);

            IEventHandler onMouseEnter (function func);

            IEventHandler onMouseLeave (function func);

            IEventHandler onMouseDown (function func);

            IEventHandler onMouseUp (function func);

            IEventHandler onMouseClick (function func);

            IEventHandler onErasePort (function func);

            IEventHandler onPreDrawLayer (function func);

            IEventHandler onPostDrawLayer (function func);

            IEventHandler onDrawPortComplete (function func);

            IEventHandler onAnimationStart (function func);

            IEventHandler onPreAnimateLayer (function func);

            IEventHandler onPostAnimateLayer (function func);

            IEventHandler onAnimationComplete (function func);

            IEventHandler onZoomComplete (function func);

            IEventHandler onLayerFadeInComplete (function func);

            IEventHandler onLayerFadeOutComplete (function func);
    };

    class TileLayer : public SpriteLayer
    {
        public:

            setWorldSize (int width, int height, boolean repeatingX = false, boolean repeatingY = false);

            Rect getWorldSize ();

            Rect getWorldBounds ();

            defineTileSet (int tileWidth, int tileHeight, Image tiles, boolean hasTransparency = true, boolean flipTiles = false);

            loadMapData (BinaryString data, int mapWidth = 0, int mapHeight = 0, int dstX, int dstY);

            loadMapData (MemBlock data, int mapWidth = 0, int mapHeight = 0, int dstX, int dstY);

            MemBlock getMapData (int mapWidth = 0, int mapHeight = 0, int srcX, int srcY);

            Image getTileSetImage ();

            Point getTileSize ();

            number getTileTypeAt (int x, int y);

            object getTileTypeAndFacingAt (int x, int y);

            setTileTypeAt (int x, int y, uint t, uint facing = facing_Ignore);

            number checkCollision (Sprite movingSprite, uint alphaThreshold = 128, boolean shortCircuit = true);
    };

    class Image
    {
        public:

            number getWidth ();

            number getHeight ();

            Rect getImageBounds (Point at);

            Image getSubsection (Quad quad);

            Image getSubsection (Rect quad);

            Image setTransparentColor (object inTransparentColor);

            number getOpacity ();

            setOpacity (number opacity);

            setEdgeClamping (boolean inUseEdgeClamp);

            object getTransparentColor ();

            retainData ();

            retainAlpha ();

            number prepareToRasterize ();

            number getAlphaValue (Point p);

            number getAlphaValue (int x, int y);

            Color getPixel (Point p);

            Color getPixel (int x, int y);
    };

    class ImageStrip : public Image
    {
        public:

            Image getFrame (int frameNum);

            number getFrameWidth ();

            ImageStrip setFrameWidth (int inFrameWidth);

            number getNumFrames ();

            ImageStrip setNumFrames (int inNumFrames);
    };

    class Font
    {
        public:

            string getFontName ();

            number getFontHeight (number size, int style = textStyle_Plain);

            number getFontLeading (number size, int style = textStyle_Plain);

            number getFontAscent (number size, int style = textStyle_Plain);

            number getFontDescent (number size, int style = textStyle_Plain);
    };

    class Port
    {
        public:

            Rect getClipRect ();

            Port setClipRect (Rect inClipRect);

            Image getCursor ();

            setCursor (Image cursorImage, Point hotSpot);

            Rect getDrawingArea ();

            fillRect (Quad quad, Color rgba = "black");

            fillRect (Rect quad, Color rgba = "black");

            frameRect (Quad quad, Color rgba = "black");

            frameRect (Rect quad, Color rgba = "black");

            drawLine (Point from, Point to, Color rgba = "black");

            frameOval (Point centerPt, number xRadius, number yRadius, Color rgba = "black");

            fillOval (Point centerPt, number xRadius, number yRadius, Color rgba = "black");

            frameCircle (Point centerPt, number radius, Color rgba = "black");

            fillCircle (Point centerPt, number radius, Color rgba = "black");

            frameRoundRect (Rect rect, number radius, Color rgba = "black");

            fillRoundRect (Rect rect, number radius, Color rgba = "black");

            fillRectEx (Quad quad, uint pattern, uint patternShift, Color rgba);

            fillRectEx (Rect quad, uint pattern, uint patternShift, Color rgba);

            frameRectEx (Quad quad, uint thickness, uint pattern, uint patternShift, Color rgba);

            frameRectEx (Rect quad, uint thickness, uint pattern, uint patternShift, Color rgba);

            drawLineEx (Point from, Point to, uint thickness, uint pattern, uint patternShift, Color rgba);

            fillRectWithGradient (Quad quad, Color startColor, Color endColor);

            fillRectWithGradient (Rect quad, Color startColor, Color endColor);

            drawText (string text, Point location, int size, uint style = textStyle_Plain, Color rgba = 'black');

            drawText (string text, Quad quad, int size, uint style = textStyle_Plain, Color rgba = 'black');

            drawText (string text, Rect rect, int size, uint style = textStyle_Plain, Color rgba = 'black');

            drawImage (Image img, Point loc);

            drawImage (Image img, Quad quad);

            drawImage (Image img, Rect rect, int fitType = fit_Fill, boolean clipOverflow = false);

            drawTexture (Image img, Rect r);

            drawTexturedSphere (Image img, Point loc, number radius, number rotation = 0, Offset polarOffsetRadians = Offset(0,0), Offset lightOffsetRadians = Offset(0,0));

            drawTexturedSphere (ImageStrip imgStrip, int frameNum, Point loc, number radius, number rotation = 0, Offset polarOffsetRadians = Offset(0,0), Offset lightOffsetRadians = Offset(0,0));

            number getTextWidth (string text, int size, uint style = textStyle_Plain, int len = -1);

            Font getCurrentFont (uint style = textStyle_Plain);

            setFont (Font font = DEFAULT_FONT);

            setFontForStyle (uint style, Font font = DEFAULT_FONT);

            setFontScalingFactor (number scaleBy);

            number startTrackingMouse (Rect rect);

            stopTrackingMouse (int trackingRef);

            resetCursor ();
    };

    class GraphicsManager
    {
        public:

            number getNumScreens ();

            number getFPS ();

            number getTargetFPS ();

            GraphicsManager setTargetFPS (number inTargetFPS);

            Point getMouse (int mouseNumber = 0);

            object getCurrentScreenMode (int screenNum = PRIMARY_SCREEN);

            number getNumSupportedScreenModes (int screen = PRIMARY_SCREEN);

            object getNthSupportedScreenMode (int n, int screenNum = PRIMARY_SCREEN);

            setScreenMode (int width, int height, int screenNum = PRIMARY_SCREEN, int bpp = 0);

            Port createWindowPort (Rect rect, string windName = "", int bpp = 0);

            Port createFullScreenPort (Rect rect, int screenNum = PRIMARY_SCREEN, boolean allowResChange = true, int bpp = 0);

            closeGraphicsPort (Port port = MAIN_PORT);

            Font createFont (string fontName, number scalingFactor = 1.0);

            Port getMainPort ();

            boolean switchToFullScreenMode (boolean allowResChange = false, Port port = MAIN_PORT);

            boolean switchToWindowMode (Port port = MAIN_PORT, string windName = "");

            boolean inFullScreenMode ();
    };

    class Sound : public EventEmitter
    {
        public:

            number getVolume ();

            Sound setVolume (number inVolume);

            play (number vol = 1.0, int offsetX = 0, number pitch = 0, uint fromMs = 0, int lenMs = ENTIRE_LENGTH);

            start ();

            stop ();

            pause ();

            resume ();

            boolean isPaused ();

            Sound setLooping (boolean loopingOn);

            boolean isLooping ();

            Sound setPitch (number pitchOffset);

            changePitch (number targetOffset, int msDuration, int easing = easeInOutQuad);

            Sound setOffsetX (int offsetX);

            changeOffsetX (int targetOffset, int msDuration, int easing = linearTween);

            fadeOut (uint fadeMs, int easing = linearTween);

            fadeIn (uint fadeMs, int easing = linearTween);

            changeVolume (number level, uint fadeMs, int easing = linearTween);

            Sound skip (int skipMilliseconds);

            Sound skipTo (uint timeMs);

            IEventHandler on (int eventCode, function func);

            IEventHandler onDonePlaying (function func);

            IEventHandler onLooping (function func);

            IEventHandler onFailedToPlay (function func);
    };

    class SoundManager
    {
        public:

            setVolume (number level);

            setMute (boolean muted);
    };

    class Point : public Offset
    {
        public:
            number x;
            number y;

            Point ();

            Point (number x, number y);

            Point (number[] xy);

            Point (object xy);

            number distance (Point point);

            Point projection (Point point);
    };

    class Offset
    {
        public:
            number x;
            number y;

            string toString ();

            Offset ();

            Offset (number x, number y);

            Offset (number[] xy);

            Offset (object xy);

            boolean equals (Offset offset);

            boolean notEquals (Offset offset);

            Offset assign (Offset offset);

            Offset add (Offset offset);

            Offset sub (Offset offset);

            Offset mul (Offset offset);

            Offset div (Offset offset);

            Offset plus (Offset offset);

            Offset minus (Offset offset);

            Offset times (Offset offset);

            Offset dividedby (Offset offset);
    };

    class Vector : public Offset
    {
        public:
            number x;
            number y;

            Vector ();

            Vector (number x, number y);

            Vector (number[] xy);

            Vector (object xy);

            number dotProduct (Vector vector);

            number vectorLength ();

            number vectorAngle ();
    };

    class Rect
    {
        public:
            number left;
            number top;
            number right;
            number bottom;

            string toString ();

            Rect "Exception: Cannot read property 'top' of null";

            boolean empty ();

            boolean contains (Rect r);

            boolean contains (Point p);

            boolean overlaps (Rect r);

            Point leftTop ();

            Point rightTop ();

            Point leftBottom ();

            Point rightBottom ();

            Point centerPoint ();

            number x1 ();

            number y1 ();

            number x2 ();

            number y2 ();

            number width ();

            number height ();

            Rect intersection (Rect r);

            Rect unionWith (Rect r);

            moveLeft (number delta);

            moveRight (number delta);

            moveUp (number delta);

            moveDown (number delta);

            moveXTo (number x);

            moveYTo (number y);

            moveTo (number x, number y);

            moveTo (Point p);

            center (Rect r);

            center (Point p);

            setSize (number n);

            setWidth (number w);

            setHeight (number h);

            horzShrink (number delta);

            vertShrink (number delta);

            horzGrow (number delta);

            vertGrow (number delta);

            shrink (number delta);

            grow (number delta);

            horzScale (number f);

            vertScale (number f);

            scale (number f);

            round ();

            Quad toQuad ();

            boolean equals (Rect r2);

            boolean notEquals (Rect r2);

            Rect assign (Rect r2);

            Rect add (Rect r2);

            Rect add (Point p);

            Rect sub (Rect r2);

            Rect sub (Point p);

            Rect mul (Rect r2);

            Rect mul (Point p);

            Rect div (Rect r2);

            Rect div (Point p);

            Rect plus (Rect r2);

            Rect plus (Point p);

            Rect minus (Rect r2);

            Rect minus (Point p);

            Rect times (Rect r2);

            Rect times (Point p);

            Rect dividedby (Rect r2);

            Rect dividedby (Point p);
    };

    class Quad
    {
        public:
            Point[] points;

            string toString ();

            Quad (args...);

            Rect getBounds ();

            Point centerPoint ();

            boolean equals (Quad q2);

            boolean notEquals (Quad q2);

            boolean contains (Point p);

            moveLeft (number delta);

            moveRight (number delta);

            moveUp (number delta);

            moveDown (number delta);

            rotate (number rotationRadians, Offset centerPtOffset = Point(0,0));
    };

    class RotatedRect : public Rect
    {
        public:
            number left;
            number top;
            number right;
            number bottom;
            Point centerOffset;

            RotatedRect (Rect rect = Rect(0,0), number rotationRadians = 0.0, Offset cpOffset = null);

            setCenterOffset (Offset cpOffset);

            setRotation (number rotationRadians, Offset cpOffset = null);

            rotate (number rotateRadians);

            Quad getQuad ();
    };

    class Color
    {
        public:
            number red;
            number green;
            number blue;
            number alpha;

            string toString ();

            Color ();

            Color (number c);

            Color (string colorstr);

            Color (number r, number g, number b, number alpha = 1);

            boolean equals (Color color);

            boolean notEquals (Color color);

            Color assign (Color color);

            convertToGrayscale ();
    };

    class NetConnection
    {
        public:
            string localAddr;
            number localPort;
            string remoteAddr;
            number remotePort;
            boolean hasDgram;

            string toString ();

            NetConnection (object socket);

            close (boolean kill);

            NetConnection onClose (function callback);

            NetConnection onMessage (function callback);

            send (string message);

            send (MemBlock message);

            send (ISerializable message);

            send (object message);

            sendDgram (string message );

            sendDgram (MemBlock message );

            sendDgram (ISerializable message );

            sendDgram (object message );
    };

    class NetClient
    {
        public:
            boolean connection;

            string toString ();

            NetClient (object opts = null);

            NetClient connect (object serverInfo, function callback, string clientKey = '');

            NetClient onError (function callback);
    };

    class NetServer
    {
        public:
            number serverPort;
            string serverAddr;
            number handshakeTimeout;
            boolean reservationRequired;
            boolean allowDatagram;
            boolean listening;
            [] connections;

            string toString ();

            NetServer (object opts = null);

            NetServer listen (function callback);

            number broadcast (object message, function filter = null);

            NetServer expectClient (string clientKey, string clientIpAddr = '*', int reservationTTL = FOREVER, boolean singleUse = false);

            NetServer onError (function callback);

            shutdown (boolean closeExisting = true, boolean kill = false);
    };

}
