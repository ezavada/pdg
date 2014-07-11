/* This file automatically generated from docs/pdg-js.i */



namespace pdg
{

    const int all_events = 0;
    const int eventType_Startup = 1;
    const int eventType_Shutdown = 2;
    const int eventType_Timer = 3;
    const int eventType_KeyDown = 4;
    const int eventType_KeyUp = 5;
    const int eventType_KeyPress = 6;
    const int eventType_MouseDown = 7;
    const int eventType_MouseUp = 8;
    const int eventType_MouseMove = 9;
    const int eventType_MouseEnter = 22;
    const int eventType_MouseLeave = 23;
    const int eventType_PortResized = 15;
    const int eventType_ScrollWheel = 16;
    const int eventType_SpriteTouch = 19;
    const int eventType_SpriteAnimate = 17;
    const int eventType_SpriteLayer = 18;
    const int eventType_SpriteCollide = 20;
    const int eventType_SpriteBreak = 21;
    const int eventType_SoundEvent = 14;
    const int eventType_PortDraw = 24;
    const int soundEvent_DonePlaying = 0;
    const int soundEvent_Looping = 1;
    const int soundEvent_FailedToPlay = 2;
    const int key_Break = 1;
    const int key_Home = 2;
    const int key_End = 3;
    const int key_Clear = 4;
    const int key_Help = 5;
    const int key_Pause = 6;
    const int key_Mute = 7;
    const int key_Backspace = 8;
    const int key_Delete = 127;
    const int key_Tab = 9;
    const int key_PageUp = 11;
    const int key_PageDown = 12;
    const int key_Return = 13;
    const int key_Enter = 13;
    const int key_F1 = 14;
    const int key_F2 = 15;
    const int key_F3 = 16;
    const int key_F4 = 17;
    const int key_F5 = 18;
    const int key_F6 = 19;
    const int key_F7 = 20;
    const int key_F8 = 21;
    const int key_F9 = 22;
    const int key_F10 = 23;
    const int key_F11 = 24;
    const int key_F12 = 25;
    const int key_FirstF = 14;
    const int key_LastF = 25;
    const int key_Insert = 26;
    const int key_Escape = 27;
    const int key_LeftArrow = 28;
    const int key_RightArrow = 29;
    const int key_UpArrow = 30;
    const int key_DownArrow = 31;
    const int key_FirstPrintable = 32;
    const int screenPos_Normal = 0;
    const int screenPos_Rotated180 = 1;
    const int screenPos_Rotated90Clockwise = 2;
    const int screenPos_Rotated90CounterClockwise = 3;
    const int screenPos_FaceUp = 4;
    const int screenPos_FaceDown = 5;
    const int textStyle_Plain = 0;
    const int textStyle_Bold = 1;
    const int textStyle_Italic = 2;
    const int textStyle_Underline = 4;
    const int textStyle_Centered = 16;
    const int textStyle_LeftJustified = 0;
    const int textStyle_RightJustified = 32;
    const int fit_None = 0;
    const int fit_Height = 1;
    const int fit_Width = 2;
    const int fit_Inside = 3;
    const int fit_Fill = 4;
    const int fit_FillKeepProportions = 5;
    const int init_CreateUniqueNewFile = 0;
    const int init_OverwriteExisting = 1;
    const int init_AppendToExisting = 2;
    const int init_StdOut = 3;
    const int init_StdErr = 4;
    const int duration_Constant = -1;
    const int duration_Instantaneous = 0;
    const int animate_StartToEnd = 0;
    const int animate_EndToStart = 1;
    const int animate_Unidirectional = 0;
    const int animate_Bidirectional = 2;
    const int animate_NoLooping = 0;
    const int animate_Looping = 4;
    const int start_FromFirstFrame = -1;
    const int start_FromLastFrame = -2;
    const int all_Frames = 0;
    const int action_CollideSprite = 0;
    const int action_CollideWall = 1;
    const int action_Offscreen = 2;
    const int action_AnimationLoop = 8;
    const int action_AnimationEnd = 9;
    const int action_FadeComplete = 10;
    const int action_FadeInComplete = 11;
    const int action_FadeOutComplete = 12;
    const int action_JointBreak = 13;
    const int touch_MouseEnter = 20;
    const int touch_MouseLeave = 21;
    const int touch_MouseDown = 22;
    const int touch_MouseUp = 23;
    const int touch_MouseClick = 24;
    const int collide_None = 0;
    const int collide_Point = 1;
    const int collide_BoundingBox = 2;
    const int collide_CollisionRadius = 3;
    const int collide_AlphaChannel = 4;
    const int collide_Last = 4;
    const int action_ErasePort = 40;
    const int action_PreDrawLayer = 41;
    const int action_PostDrawLayer = 42;
    const int action_DrawPortComplete = 43;
    const int action_AnimationStart = 44;
    const int action_PreAnimateLayer = 45;
    const int action_PostAnimateLayer = 46;
    const int action_AnimationComplete = 47;
    const int action_ZoomComplete = 48;
    const int facing_North = 0;
    const int facing_East = 64;
    const int facing_South = 128;
    const int facing_West = 192;
    const int facing_Ignore = 256;
    const int flipped_None = 0;
    const int flipped_Horizontal = 64;
    const int flipped_Vertical = 128;
    const int flipped_Both = 192;
    const int flipped_Ignore = 256;
    const int timer_OneShot = 1;
    const int timer_Repeating = 0;
    const int timer_Never = -1;
    const int linearTween = 0;
    const int easeInQuad = 1;
    const int easeOutQuad = 2;
    const int easeInOutQuad = 3;
    const int easeInCubic = 4;
    const int easeOutCubic = 5;
    const int easeInOutCubic = 6;
    const int easeInQuart = 7;
    const int easeOutQuart = 8;
    const int easeInQuint = 10;
    const int easeOutQuint = 11;
    const int easeInOutQuint = 12;
    const int easeInSine = 13;
    const int easeOutSine = 14;
    const int easeInOutSine = 15;
    const int easeInExpo = 16;
    const int easeOutExpo = 17;
    const int easeInOutExpo = 18;
    const int easeInCirc = 19;
    const int easeOutCirc = 20;
    const int easeInOutCirc = 21;
    const int easeInBounce = 22;
    const int easeOutBounce = 23;
    const int easeInOutBounce = 24;
    const int easeInBack = 25;
    const int easeOutBack = 26;
    const int easeInOutBack = 27;
    const int lftTop = 0;
    const int rgtTop = 1;
    const int rgtBot = 2;
    const int lftBot = 3;
    FileManager fs;
    EventManager evt;
    TimerManager tm;
    ResourceManager res;
    ConfigManager cfg;
    GraphicsManager gfx;
    SoundManager snd;
    string[] argv;

/**  */
    number rand ();
/**  */
    srand (uint seed);
/**  */
    registerEasingFunction (function easingFunc);
/**  */
    FileManager getFileManager ();
/**  */
    LogManager getLogManager ();
/**  */
    ConfigManager getConfigManager ();
/**  */
    ResourceManager getResourceManager ();
/**  */
    EventManager getEventManager ();
/**  */
    TimerManager getTimerManager ();
/**  */
    registerSerializableClass (object klass);
/**  */
    GraphicsManager getGraphicsManager ();
/**  */
    SoundManager getSoundManager ();
/**  */
    SpriteLayer createSpriteLayer (Port port = null);
/**  */
    cleanupSpriteLayer (SpriteLayer layer);
/**  */
    quit ();
/**  */
    run ();
/**  */
    idle ();
/** start node-inspector and open a debugger window in your browser */
    openDebugger ();
/** open a pdg console window */
    openConsole ();
/**  */
    log (string msg);
/**  */
    info (string msg);
/**  */
    warn (string msg);
/**  */
    error (string msg);
/**  */
    debug (string msg);
/**  */
    trace (string msg);
/**  */
    captureConsole ();
/**  */
    IEventHandler on (int eventType, function func);
/**  */
    IEventHandler onShutdown (function func);
/**  */
    IEventHandler onTimer (function func);
/**  */
    IEventHandler onKeyDown (function func);
/**  */
    IEventHandler onKeyUp (function func);
/**  */
    IEventHandler onKeyPress (function func);
/**  */
    IEventHandler onMouseDown (function func);
/**  */
    IEventHandler onMouseUp (function func);
/**  */
    IEventHandler onMouseMove (function func);
/**  */
    startRepl ();

    class (MemBlock)
    {
        public:
/**  */
            BinaryString getData ();
/**  */
            number getDataSize ();
/**  */
            number getByte (uint i);
/**  */
            BinaryString getBytes (uint start, uint len);
    };

    class (FileManager)
    {
        public:
/**  */
            object findFirst (string inFindName);
/**  */
            object findNext (object inFindData);
/**  */
            findClose (object inFindData);
/**  */
            string getApplicationDataDirectory ();
/**  */
            string getApplicationDirectory ();
/**  */
            string getApplicationResourceDirectory ();
/**  */
            string[] findFiles (string name);
/**  */
            string[] findDirs (string name);
    };

    class (LogManager)
    {
        public:
            const int init_CreateUniqueNewFile = 0;
            const int init_OverwriteExisting = 1;
            const int init_AppendToExisting = 2;
            const int init_StdOut = 3;
            const int init_StdErr = 4;
/**  */
            number getLogLevel ();
/**  */
            setLogLevel (int inLogLevel);
/**  */
            initialize (string inLogNameBase, int initMode = LogManager.init_StdOut);
/**  */
            writeLogEntry (int level, string category, string message);
/**  */
            string binaryDump (BinaryString inData, int length = 0, int bytesPerLine = 20);
/**  */
            string binaryDump (MemBlock inData, int length = 0, int bytesPerLine = 20);
    };

    class (ConfigManager)
    {
        public:
/**  */
            boolean useConfig (string inConfigName);
/**  */
            {string|undefined}
            getConfigString (string inConfigItemName);
/**  */
            {number|undefined}
            getConfigLong (string inConfigItemName);
/**  */
            {number|undefined}
            getConfigFloat (string inConfigItemName);
/**  */
            {boolean|undefined}
            getConfigBool (string inConfigItemName);
/**  */
            setConfigString (string inConfigItemName, string inValue);
/**  */
            setConfigLong (string inConfigItemName, int inValue);
/**  */
            setConfigFloat (string inConfigItemName, number inValue);
/**  */
            setConfigBool (string inConfigItemName, boolean inValue);
    };

    class (ResourceManager)
    {
        public:
/**  */
            number openResourceFile (string filename);
/**  */
            Image getImage (string imageName);
/**  */
            Sound getSound (string soundName);
/**  */
            string getString (int id, int substring = -1);
/**  */
            number getResourceSize (string resourceName);
/**  */
            BinaryString getResource (string resourceName);
/**  */
            string getResourcePaths ();
    };

    class (Serializer)
    {
        public:
/**  */
            serialize_d (number val);
/**  */
            serialize_f (number val);
/**  */
            serialize_4 (int val);
/**  */
            serialize_4u (uint val);
/**  */
            serialize_3u (uint val);
/**  */
            serialize_2 (int val);
/**  */
            serialize_2u (uint val);
/**  */
            serialize_1 (int val);
/**  */
            serialize_1u (uint val);
/**  */
            serialize_uint (uint val);
/**  */
            serialize_str (string str);
/**  */
            serialize_mem (BinaryString mem);
/**  */
            serialize_mem (MemBlock mem);
/**  */
            serialize_obj (ISerializable obj);
/**  */
            number serializedSize (string arg);
/**  */
            number serializedSize (uint arg);
/**  */
            number serializedSize (MemBlock arg);
/**  */
            number serializedSize (ISerializable arg);
/**  */
            number getDataSize ();
/**  */
            MemBlock getDataPtr ();
    };

    class (Deserializer)
    {
        public:
/**  */
            number deserialize_d ();
/**  */
            number deserialize_f ();
/**  */
            number deserialize_4 ();
/**  */
            number deserialize_4u ();
/**  */
            number deserialize_3u ();
/**  */
            number deserialize_2 ();
/**  */
            number deserialize_2u ();
/**  */
            number deserialize_1 ();
/**  */
            number deserialize_1u ();
/**  */
            number deserialize_uint ();
/**  */
            string deserialize_str ();
/**  */
            number deserialize_strGetLen ();
/**  */
            MemBlock deserialize_mem ();
/**  */
            number deserialize_memGetLen ();
/**  */
            ISerializable deserialize_obj ();
/**  */
            setDataPtr (BinaryString data);
/**  */
            setDataPtr (MemBlock data);
    };

    class (ISerializable)
    {
        public:
    };

    class (IEventHandler)
    {
        public:
    };

    class (EventEmitter)
    {
        public:
/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
            addHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
            removeHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove all handlers */
            clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
            blockEvent (int inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
            unblockEvent (int inEventType);
    };

    class (EventManager : public EventEmitter)
    {
        public:
/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
            addHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
            removeHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove all handlers */
            clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
            blockEvent (int inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
            unblockEvent (int inEventType);
/**  */
            boolean isKeyDown (string unicodeChar);
/**  */
            boolean isKeyDown (uint utf16CharCode);
/**  */
            boolean isRawKeyDown (int keyCode);
/**  */
            boolean isButtonDown (int buttonNumber = 0);
/** NOT IMPLEMENTED */
            object getDeviceOrientation ();
    };

    class (TimerManager)
    {
        public:
/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
            addHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
            removeHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove all handlers */
            clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
            blockEvent (int inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
            unblockEvent (int inEventType);
/**  */
            startTimer (int id, uint delay, boolean oneShot = true);
/**  */
            cancelTimer (int id);
/**  */
            cancelAllTimers ();
/**  */
            delayTimer (int id, uint delay);
/**  */
            delayTimerUntil (int id, uint msTime);
/**  */
            pause ();
/**  */
            unpause ();
/**  */
            boolean isPaused ();
/**  */
            pauseTimer (int id);
/**  */
            unpauseTimer (int id);
/**  */
            boolean isTimerPaused (int id);
/**  */
            number getWhenTimerFiresNext (int id);
/**  */
            number getMilliseconds ();
/** setup handler to be called once after delay ms */
            IEventHandler onTimeout (function func, int delay);
/** setup handler to be called regularly at interval ms */
            IEventHandler onInterval (function func, int interval);
    };

    class (IAnimationHelper)
    {
        public:
    };

    class (Animated)
    {
        public:
/**  */
            Rect getBoundingBox ();
/**  */
            Rect getRotatedBounds ();
/**  */
            Point getLocation ();
/**  */
            setLocation (Point inLocation);
/**  */
            number getSpeed ();
/**  */
            setSpeed (number inSpeed);
/**  */
            Vector getVelocity ();
/**  */
            setVelocity (Vector deltaPerSec);
/**  */
            setVelocity (number deltaXPerSec, number deltaYPerSec);
/**  */
            number getWidth ();
/**  */
            setWidth (number inWidth);
/**  */
            number getHeight ();
/**  */
            setHeight (number inHeight);
/**  */
            number getRotation ();
/**  */
            setRotation (number inRotation);
/**  */
            Offset getCenterOffset ();
/**  */
            setCenterOffset (Offset inCenterOffset);
/**  */
            number getSpin ();
/**  */
            setSpin (number inSpin);
/**  */
            number getMass ();
/**  */
            setMass (number inMass);
/**  */
            number getMoveFriction ();
/**  */
            setMoveFriction (number inMoveFriction);
/**  */
            number getSpinFriction ();
/**  */
            setSpinFriction (number inSpinFriction);
/**  */
            number getSizeFriction ();
/**  */
            setSizeFriction (number inSizeFriction);
/**  */
            move (Point delta, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            moveTo (Point where, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            setVelocityInRadians (number speed, number direction);
/**  */
            number getMovementDirectionInRadians ();
/**  */
            stopMoving ();
/**  */
            accelerate (number deltaSpeed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            accelerateTo (number speed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            setSize (number width, number height);
/**  */
            grow (number factor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stretch (number widthFactor, number heightFactor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            startGrowing (number amountPerSecond);
/**  */
            stopGrowing ();
/**  */
            startStretching (number widthPerSecond, number heightPerSecond);
/**  */
            stopStretching ();
/**  */
            resize (number deltaWidth, number deltaHeight, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            resizeTo (number width, number height, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotate (number radians, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotateTo (number radiansRotation, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stopSpinning ();
/**  */
            changeCenter (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            changeCenterTo (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            wait (int msDuration);
/**  */
            setFriction (number frictionCoefficient);
/**  */
            applyForce (Vector force, int msDuration = duration_Instantaneous);
/**  */
            applyTorque (number forceSpin, int msDuration = duration_Instantaneous);
/**  */
            stopAllForces ();
/**  */
            addAnimationHelper (IAnimationHelper helper);
/**  */
            removeAnimationHelper (IAnimationHelper helper);
/**  */
            clearAnimationHelpers ();
/**  */
            boolean animate (int msElapsed);
    };

    class (CpArbiter)
    {
        public:
/** true if this is the first moment of contact between the objects, false if part of an ongoing collison */
            boolean isFirstContact ();
/**  */
            number getCount ();
/**  */
            Vector getNormal ();
/**  */
            Point getPoint ();
/**  */
            number getDepth ();
    };

    class (CpConstraint)
    {
        public:
/**  */
            string getType ();
/**  */
            activateBodies ();
/**  */
            number getImpulse ();
/**  */
            number getMaxForce ();
/**  */
            setMaxForce (number inMaxForce);
/**  */
            number getErrorBias ();
/**  */
            setErrorBias (number inErrorBias);
/**  */
            number getMaxBias ();
/**  */
            setMaxBias (number inMaxBias);
/**  */
            Sprite getSprite ();
/**  */
            Sprite getOtherSprite ();
/**  */
            Offset getAnchor ();
/**  */
            setAnchor (Offset inAnchor);
/**  */
            Offset getOtherAnchor ();
/**  */
            setOtherAnchor (Offset inOtherAnchor);
/**  */
            number getPinDist ();
/**  */
            setPinDist (number inPinDist);
/**  */
            number getSpringStiffness ();
/**  */
            setSpringStiffness (number inSpringStiffness);
/**  */
            number getSpringDamping ();
/**  */
            setSpringDamping (number inSpringDamping);
/**  */
            number getSlideMinDist ();
/**  */
            setSlideMinDist (number inSlideMinDist);
/**  */
            number getSlideMaxDist ();
/**  */
            setSlideMaxDist (number inSlideMaxDist);
/**  */
            Offset getGrooveStart ();
/**  */
            setGrooveStart (Offset inGrooveStart);
/**  */
            Offset getGrooveEnd ();
/**  */
            setGrooveEnd (Offset inGrooveEnd);
/**  */
            number getSpringRestLength ();
/**  */
            setSpringRestLength (number inSpringRestLength);
/**  */
            number getRotarySpringRestAngle ();
/**  */
            setRotarySpringRestAngle (number inRotarySpringRestAngle);
/**  */
            number getMinAngle ();
/**  */
            setMinAngle (number inMinAngle);
/**  */
            number getMaxAngle ();
/**  */
            setMaxAngle (number inMaxAngle);
/**  */
            number getRatchetAngle ();
/**  */
            setRatchetAngle (number inRatchetAngle);
/**  */
            number getRatchetPhase ();
/**  */
            setRatchetPhase (number inRatchetPhase);
/**  */
            number getRatchetInterval ();
/**  */
            setRatchetInterval (number inRatchetInterval);
/**  */
            number getGearRatio ();
/**  */
            setGearRatio (number inGearRatio);
/**  */
            number getGearInitialAngle ();
/**  */
            setGearInitialAngle (number inGearInitialAngle);
/**  */
            number getMotorSpinRate ();
/**  */
            setMotorSpinRate (number inMotorSpinRate);
    };

    class (CpSpace)
    {
        public:
/**  */
            useSpatialHash (number dim, int count);
/**  */
            reindexStatic ();
/**  */
            step (number dt);
/**  */
            number getIdleSpeedThreshold ();
/**  */
            setIdleSpeedThreshold (number inIdleSpeedThreshold);
/**  */
            number getSleepTimeThreshold ();
/**  */
            setSleepTimeThreshold (number inSleepTimeThreshold);
/**  */
            number getCollisionSlop ();
/**  */
            setCollisionSlop (number inCollisionSlop);
/**  */
            number getCollisionBias ();
/**  */
            setCollisionBias (number inCollisionBias);
/**  */
            number getCollisionPersistence ();
/**  */
            setCollisionPersistence (number inCollisionPersistence);
/**  */
            boolean getEnableContactGraph ();
/**  */
            setEnableContactGraph (boolean inEnableContactGraph);
    };

    class (ISpriteDrawHelper)
    {
        public:
    };

    class (Sprite : public Animated,public EventEmitter)
    {
        public:
/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
            addHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
            removeHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove all handlers */
            clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
            blockEvent (int inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
            unblockEvent (int inEventType);
/**  */
            Rect getBoundingBox ();
/**  */
            Rect getRotatedBounds ();
/**  */
            Point getLocation ();
/**  */
            setLocation (Point inLocation);
/**  */
            number getSpeed ();
/**  */
            setSpeed (number inSpeed);
/**  */
            Vector getVelocity ();
/**  */
            setVelocity (Vector deltaPerSec);
/**  */
            setVelocity (number deltaXPerSec, number deltaYPerSec);
/**  */
            number getWidth ();
/**  */
            setWidth (number inWidth);
/**  */
            number getHeight ();
/**  */
            setHeight (number inHeight);
/**  */
            number getRotation ();
/**  */
            setRotation (number inRotation);
/**  */
            Offset getCenterOffset ();
/**  */
            setCenterOffset (Offset inCenterOffset);
/**  */
            number getSpin ();
/**  */
            setSpin (number inSpin);
/**  */
            number getMass ();
/**  */
            setMass (number inMass);
/**  */
            number getMoveFriction ();
/**  */
            setMoveFriction (number inMoveFriction);
/**  */
            number getSpinFriction ();
/**  */
            setSpinFriction (number inSpinFriction);
/**  */
            number getSizeFriction ();
/**  */
            setSizeFriction (number inSizeFriction);
/**  */
            move (Point delta, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            moveTo (Point where, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            setVelocityInRadians (number speed, number direction);
/**  */
            number getMovementDirectionInRadians ();
/**  */
            stopMoving ();
/**  */
            accelerate (number deltaSpeed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            accelerateTo (number speed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            setSize (number width, number height);
/**  */
            grow (number factor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stretch (number widthFactor, number heightFactor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            startGrowing (number amountPerSecond);
/**  */
            stopGrowing ();
/**  */
            startStretching (number widthPerSecond, number heightPerSecond);
/**  */
            stopStretching ();
/**  */
            resize (number deltaWidth, number deltaHeight, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            resizeTo (number width, number height, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotate (number radians, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotateTo (number radiansRotation, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stopSpinning ();
/**  */
            changeCenter (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            changeCenterTo (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            wait (int msDuration);
/**  */
            setFriction (number frictionCoefficient);
/**  */
            applyForce (Vector force, int msDuration = duration_Instantaneous);
/**  */
            applyTorque (number forceSpin, int msDuration = duration_Instantaneous);
/**  */
            stopAllForces ();
/**  */
            addAnimationHelper (IAnimationHelper helper);
/**  */
            removeAnimationHelper (IAnimationHelper helper);
/**  */
            clearAnimationHelpers ();
/**  */
            Rect getFrameRotatedBounds (int frame);
/**  */
            setFrame (int frame);
/** which frame of animation the sprite is currently showing */
            number getCurrentFrame ();
/** total number of frames of animation for this sprite */
            number getFrameCount ();
/**  */
            setFramesPerSecond (number fps, int startingFrame = start_FromFirstFrame, int numFrames = all_Frames, int animateFlags = animate_Looping);
/**  */
            stopFrameAnimation ();
/**  */
            boolean setWantsAnimLoopEvents (boolean wantsThem = true);
/**  */
            boolean setWantsAnimEndEvents (boolean wantsThem = true);
/**  */
            addFramesImage (Image image, int startingFrame = start_FromFirstFrame, int numFrames = all_Frames);
/**  */
            setDrawHelper (ISpriteDrawHelper helper);
/**  */
            setPostDrawHelper (ISpriteDrawHelper helper);
/**  */
            changeFramesImage (Image oldImage, Image newImage);
/**  */
            offsetFrameCenters (int offsetX, int offsetY, Image image = null, int startingFrame = start_FromFirstFrame, int numFrames = all_Frames);
/** NOT IMPLEMENTED */
            getFrameCenterOffset ();
/**  */
            setOpacity (number opacity);
/**  */
            number getOpacity ();
/**  */
            fadeTo (number targetOpacity, int msDuration, int easing = linearTween);
/**  */
            fadeIn (int msDuration, int easing = linearTween);
/**  */
            fadeOut (int msDuration, int easing = linearTween);
/**  */
            moveBehind (Sprite sprite);
/**  */
            moveInFrontOf (Sprite sprite);
/** put this sprite in front of all others in its layer */
            moveToFront ();
/** put this sprite behind all others in its layer */
            moveToBack ();
/**  */
            enableCollisions (int collisionType = collide_AlphaChannel);
/**  */
            disableCollisions ();
/**  */
            setCollisionRadius (number pixelRadius);
/**  */
            number getCollisionRadius ();
/**  */
            useCollisionMask (Image frameImage, Image maskImage);
/**  */
            setElasticity (number elasticity);
/**  */
            number getElasticity ();
/**  */
            boolean setWantsMouseOverEvents (boolean wantsThem = true);
/**  */
            boolean setWantsClickEvents (boolean wantsThem = true);
/**  */
            number setMouseDetectMode (int collisionType = collide_BoundingBox);
/** get the layer that contains this sprite */
            SpriteLayer getLayer ();
/**  */
            Sprite makeStatic ();
/**  */
            number getFriction ();
/**  */
            setCollideGroup (int group);
/**  */
            number getCollideGroup ();
/**  */
            CpConstraint pinJoint (Offset anchor, Sprite otherSprite, Offset otherAnchor, number breakingForce = 0);
/**  */
            CpConstraint slideJoint (Offset anchor, Sprite otherSprite, Offset otherAnchor, number minDist, number maxDist, number breakingForce = 0);
/**  */
            CpConstraint pivotJoint (Sprite otherSprite, Point pivot, number breakingForce = 0);
/**  */
            CpConstraint grooveJoint (Offset grooveStart, Offset grooveEnd, Sprite otherSprite, Offset otherAnchor, number breakingForce = 0);
/**  */
            CpConstraint springJoint (Offset anchor, Sprite otherSprite, Offset otherAnchor, number restLength, number stiffness, number damping, number breakingForce = 0);
/**  */
            CpConstraint rotarySpring (Sprite otherSprite, number restAngle, number stiffness, number damping, number breakingForce = 0);
/**  */
            CpConstraint rotaryLimit (Sprite otherSprite, number minAngle, number maxAngle, number breakingForce = 0);
/**  */
            CpConstraint ratchet (Sprite otherSprite, number rachetInterval, number phase, number breakingForce = 0);
/**  */
            CpConstraint gear (Sprite otherSprite, number gearRatio, number initialAngle = 0, number breakingForce = 0);
/**  */
            CpConstraint motor (Sprite otherSprite, number spin, number maxTorque = INFINITY);
/**  */
            removeJoint (CpConstraint joint);
/**  */
            disconnect (Sprite otherSprite);
/**  */
            makeJointBreakable (CpConstraint joint, number breakingForce);
/**  */
            makeJointUnbreakable (CpConstraint joint);
/**  */
            IEventHandler on (int eventCode, function func);
/**  */
            IEventHandler onCollideSprite (function func);
/**  */
            IEventHandler onCollideWall (function func);
/**  */
            IEventHandler onOffscreen (function func);
/**  */
            IEventHandler onAnimationLoop (function func);
/**  */
            IEventHandler onAnimationEnd (function func);
/**  */
            IEventHandler onFadeComplete (function func);
/**  */
            IEventHandler onFadeInComplete (function func);
/**  */
            IEventHandler onFadeOutComplete (function func);
/**  */
            IEventHandler onMouseEnter (function func);
/**  */
            IEventHandler onMouseLeave (function func);
/**  */
            IEventHandler onMouseDown (function func);
/**  */
            IEventHandler onMouseUp (function func);
/**  */
            IEventHandler onMouseClick (function func);
    };

    class (SpriteLayer : public Animated)
    {
        public:
/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
            addHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
            removeHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove all handlers */
            clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
            blockEvent (int inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
            unblockEvent (int inEventType);
/**  */
            Rect getBoundingBox ();
/**  */
            Rect getRotatedBounds ();
/**  */
            Point getLocation ();
/**  */
            setLocation (Point inLocation);
/**  */
            number getSpeed ();
/**  */
            setSpeed (number inSpeed);
/**  */
            Vector getVelocity ();
/**  */
            setVelocity (Vector deltaPerSec);
/**  */
            setVelocity (number deltaXPerSec, number deltaYPerSec);
/**  */
            number getWidth ();
/**  */
            setWidth (number inWidth);
/**  */
            number getHeight ();
/**  */
            setHeight (number inHeight);
/**  */
            number getRotation ();
/**  */
            setRotation (number inRotation);
/**  */
            Offset getCenterOffset ();
/**  */
            setCenterOffset (Offset inCenterOffset);
/**  */
            number getSpin ();
/**  */
            setSpin (number inSpin);
/**  */
            number getMass ();
/**  */
            setMass (number inMass);
/**  */
            number getMoveFriction ();
/**  */
            setMoveFriction (number inMoveFriction);
/**  */
            number getSpinFriction ();
/**  */
            setSpinFriction (number inSpinFriction);
/**  */
            number getSizeFriction ();
/**  */
            setSizeFriction (number inSizeFriction);
/**  */
            move (Point delta, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            moveTo (Point where, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            setVelocityInRadians (number speed, number direction);
/**  */
            number getMovementDirectionInRadians ();
/**  */
            stopMoving ();
/**  */
            accelerate (number deltaSpeed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            accelerateTo (number speed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            setSize (number width, number height);
/**  */
            grow (number factor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stretch (number widthFactor, number heightFactor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            startGrowing (number amountPerSecond);
/**  */
            stopGrowing ();
/**  */
            startStretching (number widthPerSecond, number heightPerSecond);
/**  */
            stopStretching ();
/**  */
            resize (number deltaWidth, number deltaHeight, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            resizeTo (number width, number height, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotate (number radians, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotateTo (number radiansRotation, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stopSpinning ();
/**  */
            changeCenter (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            changeCenterTo (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            wait (int msDuration);
/**  */
            setFriction (number frictionCoefficient);
/**  */
            applyForce (Vector force, int msDuration = duration_Instantaneous);
/**  */
            applyTorque (number forceSpin, int msDuration = duration_Instantaneous);
/**  */
            stopAllForces ();
/**  */
            addAnimationHelper (IAnimationHelper helper);
/**  */
            removeAnimationHelper (IAnimationHelper helper);
/**  */
            clearAnimationHelpers ();
/**  */
            startAnimations ();
/**  */
            stopAnimations ();
/**  */
            hide ();
/**  */
            show ();
/**  */
            boolean isHidden ();
/**  */
            fadeIn (int msDuration, int easing = linearTween);
/**  */
            fadeOut (int msDuration, int easing = linearTween);
/**  */
            moveBehind (SpriteLayer layer);
/**  */
            moveInFrontOf (SpriteLayer layer);
/** move this layer in front of all other layers */
            moveToFront ();
/** move this layer behind all other layers */
            moveToBack ();
/**  */
            Sprite findSprite (int id);
/**  */
            boolean hasSprite (Sprite sprite);
/**  */
            addSprite (Sprite newSprite);
/**  */
            removeSprite (Sprite oldSprite);
/**  */
            removeAllSprites ();
/**  */
            enableCollisions ();
/**  */
            disableCollisions ();
/**  */
            enableCollisionsWithLayer (SpriteLayer otherLayer);
/**  */
            disableCollisionsWithLayer (SpriteLayer otherLayer);
/**  */
            Sprite createSprite ();
/**  */
            Port getSpritePort ();
/**  */
            setSpritePort (Port port);
/**  */
            setOrigin (Point origin);
/** get the point in the layer that is drawn at 0,0 in the port */
            Point getOrigin ();
/**  */
            setAutoCenter (boolean autoCenter = true);
/**  */
            setFixedMoveAxis (boolean fixedAxis = true);
/**  */
            setZoom (number zoomLevel);
/** get the current zoom factor */
            number getZoom ();
/**  */
            zoomTo (number zoomLevel, int msDuration, int easing = easeInOutQuad, Rect keepInRect = Rect(0,0), Point centerOn = Point(0,0) );
/**  */
            zoom (number deltaZoomLevel, int msDuration, int easing = easeInOutQuad, Rect keepInRect = Rect(0,0), Point centerOn = Point(0,0) );
/**  */
            Point layerToPortPoint (Point p);
/**  */
            Offset layerToPortOffset (Offset o);
/**  */
            Vector layerToPortVector (Vector v);
/**  */
            Rect layerToPortRect (Rect r);
/**  */
            Quad layerToPortQuad (Quad q);
/**  */
            Point portToLayerPoint (Point p);
/**  */
            Offset portToLayerOffset (Offset o);
/**  */
            Vector portToLayerVector (Vector v);
/**  */
            Rect portToLayerRect (Rect r);
/**  */
            Quad portToLayerQuad (Quad q);
/**  */
            setGravity (number gravity, boolean keepItDownward = true);
/**  */
            setKeepGravityDownward (boolean keepItDownward = true);
/**  */
            setDamping (number damping);
/**  */
            CpSpace getSpace ();
/**  */
            IEventHandler on (int eventCode, function func);
/**  */
            IEventHandler onCollideSprite (function func);
/**  */
            IEventHandler onCollideWall (function func);
/**  */
            IEventHandler onOffscreen (function func);
/**  */
            IEventHandler onAnimationLoop (function func);
/**  */
            IEventHandler onAnimationEnd (function func);
/**  */
            IEventHandler onFadeComplete (function func);
/**  */
            IEventHandler onFadeInComplete (function func);
/**  */
            IEventHandler onFadeOutComplete (function func);
/**  */
            IEventHandler onMouseEnter (function func);
/**  */
            IEventHandler onMouseLeave (function func);
/**  */
            IEventHandler onMouseDown (function func);
/**  */
            IEventHandler onMouseUp (function func);
/**  */
            IEventHandler onMouseClick (function func);
/**  */
            IEventHandler onErasePort (function func);
/**  */
            IEventHandler onPreDrawLayer (function func);
/**  */
            IEventHandler onPostDrawLayer (function func);
/**  */
            IEventHandler onDrawPortComplete (function func);
/**  */
            IEventHandler onAnimationStart (function func);
/**  */
            IEventHandler onPreAnimateLayer (function func);
/**  */
            IEventHandler onAnimationComplete (function func);
/**  */
            IEventHandler onZoomComplete (function func);
    };

    class (TileLayer : public SpriteLayer)
    {
        public:
/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
            addHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
            removeHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove all handlers */
            clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
            blockEvent (int inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
            unblockEvent (int inEventType);
/**  */
            Rect getBoundingBox ();
/**  */
            Rect getRotatedBounds ();
/**  */
            Point getLocation ();
/**  */
            setLocation (Point inLocation);
/**  */
            number getSpeed ();
/**  */
            setSpeed (number inSpeed);
/**  */
            Vector getVelocity ();
/**  */
            setVelocity (Vector deltaPerSec);
/**  */
            setVelocity (number deltaXPerSec, number deltaYPerSec);
/**  */
            number getWidth ();
/**  */
            setWidth (number inWidth);
/**  */
            number getHeight ();
/**  */
            setHeight (number inHeight);
/**  */
            number getRotation ();
/**  */
            setRotation (number inRotation);
/**  */
            Offset getCenterOffset ();
/**  */
            setCenterOffset (Offset inCenterOffset);
/**  */
            number getSpin ();
/**  */
            setSpin (number inSpin);
/**  */
            number getMass ();
/**  */
            setMass (number inMass);
/**  */
            number getMoveFriction ();
/**  */
            setMoveFriction (number inMoveFriction);
/**  */
            number getSpinFriction ();
/**  */
            setSpinFriction (number inSpinFriction);
/**  */
            number getSizeFriction ();
/**  */
            setSizeFriction (number inSizeFriction);
/**  */
            move (Point delta, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            moveTo (Point where, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            setVelocityInRadians (number speed, number direction);
/**  */
            number getMovementDirectionInRadians ();
/**  */
            stopMoving ();
/**  */
            accelerate (number deltaSpeed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            accelerateTo (number speed, int msDuration = duration_Instantaneous, int easing = linearTween);
/**  */
            setSize (number width, number height);
/**  */
            grow (number factor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stretch (number widthFactor, number heightFactor, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            startGrowing (number amountPerSecond);
/**  */
            stopGrowing ();
/**  */
            startStretching (number widthPerSecond, number heightPerSecond);
/**  */
            stopStretching ();
/**  */
            resize (number deltaWidth, number deltaHeight, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            resizeTo (number width, number height, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotate (number radians, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            rotateTo (number radiansRotation, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            stopSpinning ();
/**  */
            changeCenter (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            changeCenterTo (Offset offset, int msDuration = duration_Instantaneous, int easing = easeInOutQuad);
/**  */
            wait (int msDuration);
/**  */
            setFriction (number frictionCoefficient);
/**  */
            applyForce (Vector force, int msDuration = duration_Instantaneous);
/**  */
            applyTorque (number forceSpin, int msDuration = duration_Instantaneous);
/**  */
            stopAllForces ();
/**  */
            addAnimationHelper (IAnimationHelper helper);
/**  */
            removeAnimationHelper (IAnimationHelper helper);
/**  */
            clearAnimationHelpers ();
/**  */
            startAnimations ();
/**  */
            stopAnimations ();
/**  */
            hide ();
/**  */
            show ();
/**  */
            boolean isHidden ();
/**  */
            fadeIn (int msDuration, int easing = linearTween);
/**  */
            fadeOut (int msDuration, int easing = linearTween);
/**  */
            moveBehind (SpriteLayer layer);
/**  */
            moveInFrontOf (SpriteLayer layer);
/** move this layer in front of all other layers */
            moveToFront ();
/** move this layer behind all other layers */
            moveToBack ();
/**  */
            Sprite findSprite (int id);
/**  */
            boolean hasSprite (Sprite sprite);
/**  */
            addSprite (Sprite newSprite);
/**  */
            removeSprite (Sprite oldSprite);
/**  */
            removeAllSprites ();
/**  */
            enableCollisions ();
/**  */
            disableCollisions ();
/**  */
            enableCollisionsWithLayer (SpriteLayer otherLayer);
/**  */
            disableCollisionsWithLayer (SpriteLayer otherLayer);
/**  */
            Sprite createSprite ();
/**  */
            Port getSpritePort ();
/**  */
            setSpritePort (Port port);
/**  */
            setOrigin (Point origin);
/** get the point in the layer that is drawn at 0,0 in the port */
            Point getOrigin ();
/**  */
            setAutoCenter (boolean autoCenter = true);
/**  */
            setFixedMoveAxis (boolean fixedAxis = true);
/**  */
            setZoom (number zoomLevel);
/** get the current zoom factor */
            number getZoom ();
/**  */
            zoomTo (number zoomLevel, int msDuration, int easing = easeInOutQuad, Rect keepInRect = Rect(0,0), Point centerOn = Point(0,0) );
/**  */
            zoom (number deltaZoomLevel, int msDuration, int easing = easeInOutQuad, Rect keepInRect = Rect(0,0), Point centerOn = Point(0,0) );
/**  */
            Point layerToPortPoint (Point p);
/**  */
            Offset layerToPortOffset (Offset o);
/**  */
            Vector layerToPortVector (Vector v);
/**  */
            Rect layerToPortRect (Rect r);
/**  */
            Quad layerToPortQuad (Quad q);
/**  */
            Point portToLayerPoint (Point p);
/**  */
            Offset portToLayerOffset (Offset o);
/**  */
            Vector portToLayerVector (Vector v);
/**  */
            Rect portToLayerRect (Rect r);
/**  */
            Quad portToLayerQuad (Quad q);
/**  */
            setGravity (number gravity, boolean keepItDownward = true);
/**  */
            setKeepGravityDownward (boolean keepItDownward = true);
/**  */
            setDamping (number damping);
/**  */
            CpSpace getSpace ();
/**  */
            setWorldSize (int width, int height, boolean repeatingX = false, boolean repeatingY = false);
/**  */
            Rect getWorldSize ();
/**  */
            Rect getWorldBounds ();
/**  */
            defineTileSet (int tileWidth, int tileHeight, Image tilese, boolean hasTransparency = true, boolean flipTiles = false);
/**  */
            loadMapData (BinaryString data, int mapWidth = 0, int mapHeight = 0, int dstX, int dstY);
/**  */
            loadMapData (MemBlock data, int mapWidth = 0, int mapHeight = 0, int dstX, int dstY);
/**  */
            MemBlock getMapData (int mapWidth = 0, int mapHeight = 0, int srcX, int srcY);
/**  */
            Image getTileSetImage ();
/**  */
            Point getTileSize ();
/**  */
            {number|object}
            getTileTypeAt (int x, int y, boolean separateFacing = false);
/**  */
            setTileTypeAt (int x, int y, uint t, uint facing = facing_Ignore);
/**  */
            number checkCollision (Sprite movingSprite, uint alphaThreshold = 128, boolean shortCircuit = true);
    };

    class (Image)
    {
        public:
/**  */
            number getWidth ();
/**  */
            number getHeight ();
/** get image boundary rect, optionally with top left at given point */
            Rect getImageBounds (Point at);
/** get image that is a single frame of this multi-frame image */
            Image getFrame (int frameNum);
/** get image that is an arbitrary subsection of this image */
            Image getSubsection (Quad quad);
/** get image that is an arbitrary subsection of this image */
            Image getSubsection (Rect quad);
/**  */
            number getFrameWidth ();
/**  */
            setFrameWidth (int inFrameWidth);
/** how many frames in this multi-frame image */
            number getNumFrames ();
/** set the number of frames that are in this image */
            setNumFrames (int num);
/**  */
            object getTransparentColor ();
/**  */
            setTransparentColor (object inTransparentColor);
/** get opacity of this image: 0.0 - completely transparent to 1.0 - completely solid */
            number getOpacity ();
/** set opacity of this image as range from either (0-255) or (0.0 to 1.0) */
            setOpacity (number opacity);
/** set whether image uses edge clamping or not */
            setEdgeClamping (boolean inUseEdgeClamp);
/** retain pixel data for use by Image.getPixel() */
            retainData ();
/** retain alpha data for use by Image.getAlphaValue() or per-pixel sprite collisions */
            retainAlpha ();
/** bind the image into an OpenGL texture and free image data from main memory */
            number prepareToRasterize ();
/**  */
            number getAlphaValue (Point p);
/**  */
            number getAlphaValue (int x, int y);
/**  */
            Color getPixel (Point p);
/**  */
            Color getPixel (int x, int y);
    };

    class (Font)
    {
        public:
/**  */
            string getFontName ();
/**  */
            number getFontHeight ();
/**  */
            number getFontLeading ();
/**  */
            number getFontAscent ();
/**  */
            number getFontDescent ();
    };

    class (Port)
    {
        public:
/**  */
            Rect getClipRect ();
/**  */
            setClipRect (Rect inClipRect);
/** NOT IMPLEMENTED: get the Image that is being used as the cursor */
            Image getCursor ();
/** NOT IMPLEMENTED */
            setCursor (Image cursorImage, Point hotSpot);
/**  */
            Rect getDrawingArea ();
/**  */
            fillRect (Quad quad, Color rgba = "black");
/**  */
            fillRect (Rect quad, Color rgba = "black");
/**  */
            frameRect (Quad quad, Color rgba = "black");
/**  */
            frameRect (Rect quad, Color rgba = "black");
/**  */
            drawLine (Point from, Point to, Color rgba = "black");
/**  */
            frameOval (Point centerPt, number xRadius, number yRadius, Color rgba = "black");
/**  */
            fillOval (Point centerPt, number xRadius, number yRadius, Color rgba = "black");
/**  */
            frameCircle (Point centerPt, number radius, Color rgba = "black");
/**  */
            fillCircle (Point centerPt, number radius, Color rgba = "black");
/**  */
            frameRoundRect (Rect rect, number radius, Color rgba = "black");
/**  */
            fillRoundRect (Rect rect, number radius, Color rgba = "black");
/**  */
            fillRectEx (Quad quad, uint pattern, uint patternShift, Color rgba);
/**  */
            fillRectEx (Rect quad, uint pattern, uint patternShift, Color rgba);
/**  */
            frameRectEx (Quad quad, uint thickness, uint pattern, uint patternShift, Color rgba);
/**  */
            frameRectEx (Rect quad, uint thickness, uint pattern, uint patternShift, Color rgba);
/**  */
            drawLineEx (Point from, Point to, uint thickness, uint pattern, uint patternShift, Color rgba);
/**  */
            fillRectWithGradient (Quad quad, Color startColor, Color endColor);
/**  */
            fillRectWithGradient (Rect quad, Color startColor, Color endColor);
/**  */
            drawText (string text, Point location, int size, uint style = textStyle_Plain, Color rgba = 'black');
/**  */
            drawText (string text, Quad quad, int size, uint style = textStyle_Plain, Color rgba = 'black');
/**  */
            drawText (string text, Rect rect, int size, uint style = textStyle_Plain, Color rgba = 'black');
/**  */
            drawImage (Image img, Point loc);
/**  */
            drawImage (Image img, Quad quad);
/**  */
            drawImage (Image img, Rect rect, int fitType = fit_Fill, boolean clipOverflow = false);
/**  */
            drawTexture (Image img, Rect r);
/**  */
            number getTextWidth (string text, int size, uint style = textStyle_Plain, int len = -1);
/**  */
            Font getCurrentFont (uint style = textStyle_Plain);
/**  */
            setFont (Font font = DEFAULT_FONT);
/**  */
            setFontForStyle (uint style, Font font = DEFAULT_FONT);
/**  */
            setFontScalingFactor (number scaleBy);
/** NOT IMPLEMENTED */
            number startTrackingMouse (Rect rect);
/** NOT IMPLEMENTED */
            stopTrackingMouse (int trackingRef);
/** NOT IMPLEMENTED: restore the default system cursor */
            resetCursor ();
    };

    class (GraphicsManager)
    {
        public:
/**  */
            number getNumScreens ();
/**  */
            number getFPS ();
/**  */
            number getTargetFPS ();
/**  */
            setTargetFPS (number inTargetFPS);
/**  */
            Point getMouse ();
/** returns object with width, height, depth and maxWindowRect for specified screen */
            object getCurrentScreenMode (int screenNum);
/** changes specified screen to closest matching mode */
            setScreenMode (int screenNum, int width, int height, int depth);
/** create windowed drawing port with given dimensions, title and depth */
            Port createWindowPort (Rect rect, string windName = "", int bpp = 0);
/** create full screen drawing port with given dimensions on given screen, optionally changing depth */
            Port createFullScreenPort (Rect rect, int screenNum = PRIMARY_SCREEN, int bpp = 0);
/** close given port, along with its window and restore screen mode if changed */
            closeGraphicsPort (Port port);
/** get a font with optional scaling adjust */
            Font createFont (string fontName, number scalingFactor = 1.0);
/** return the primary graphics port */
            Port getMainPort ();
/** change the primary graphics port's fullscreen mode, return new state */
            boolean setMainPortFullScreenMode (boolean fullScreen = true);
/** return whether primary graphics port is fullscreen or not */
            boolean inFullScreenMode ();
    };

    class (Sound : public EventEmitter)
    {
        public:
/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
            addHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
            removeHandler (IEventHandler inHandler, int inEventType = all_events);
/** remove all handlers */
            clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
            blockEvent (int inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
            unblockEvent (int inEventType);
/**  */
            number getVolume ();
/**  */
            setVolume (number inVolume);
/**  */
            play ();
/**  */
            stop ();
/**  */
            pause ();
/**  */
            resume ();
/**  */
            boolean isPaused ();
/**  */
            setLooping (boolean loopingOn);
/**  */
            boolean isLooping ();
/**  */
            fadeOut (uint fadeMs);
/**  */
            fadeIn (uint fadeMs);
/**  */
            fadeTo (number level, uint fadeMs);
/**  */
            skip (int skipMilliseconds);
/**  */
            skipTo (uint timeMs);
/**  */
            IEventHandler on (int eventCode, function func);
/**  */
            IEventHandler onDonePlaying (function func);
/**  */
            IEventHandler onLooping (function func);
/**  */
            IEventHandler onFailedToPlay (function func);
    };

    class (SoundManager)
    {
        public:
/** 0.0 - silent to 1.0 - full volume */
            setVolume (number level);
/**  */
            setMute (boolean muted);
    };

    class (Point : public Offset)
    {
        public:
            number x;
            number y;
/** create and set x & y values */
            Point ();
/** create and set x & y values */
            Point (number x, number y);
/** create and set x & y values */
            Point (number[] xy);
/** create and set x & y values */
            Point (object xy);
/** return string representation  */
            string toString ();
/** get distance from another point */
            number distance (Point point);
/** do a projection of a second point onto this point */
            Point projection (Point point);
/** return true if this point is equal to the other */
            boolean equals (Offset offset);
/** return true if this point is not equal to the other */
            boolean notEquals (Offset offset);
/** set this offset equal to the given offset */
            Offset assign (Offset offset);
/** add an offset to this one */
            Offset add (Offset offset);
/** subtract an offset from this one */
            Offset sub (Offset offset);
/** multiply this offset by the given one */
            Offset mul (Offset offset);
/** divide this offset by the given one */
            Offset div (Offset offset);
/** return new offset that is this offset plus given offset */
            Offset plus (Offset offset);
/** return new offset that is this offset minus given offset */
            Offset minus (Offset offset);
/** return new offset that is this offset multiplied by given offset */
            Offset times (Offset offset);
/** return new offset that is this offset divided by given offset */
            Offset dividedby (Offset offset);
    };

    class (Offset)
    {
        public:
            number x;
            number y;
/** return string representation  */
            string toString ();
/** create and set x & y values */
            Offset ();
/** create and set x & y values */
            Offset (number x, number y);
/** create and set x & y values */
            Offset (number[] xy);
/** create and set x & y values */
            Offset (object xy);
/** return true if this point is equal to the other */
            boolean equals (Offset offset);
/** return true if this point is not equal to the other */
            boolean notEquals (Offset offset);
/** set this offset equal to the given offset */
            Offset assign (Offset offset);
/** add an offset to this one */
            Offset add (Offset offset);
/** subtract an offset from this one */
            Offset sub (Offset offset);
/** multiply this offset by the given one */
            Offset mul (Offset offset);
/** divide this offset by the given one */
            Offset div (Offset offset);
/** return new offset that is this offset plus given offset */
            Offset plus (Offset offset);
/** return new offset that is this offset minus given offset */
            Offset minus (Offset offset);
/** return new offset that is this offset multiplied by given offset */
            Offset times (Offset offset);
/** return new offset that is this offset divided by given offset */
            Offset dividedby (Offset offset);
    };

    class (Vector : public Offset)
    {
        public:
            number x;
            number y;
/** create and set x & y values */
            Vector ();
/** create and set x & y values */
            Vector (number x, number y);
/** create and set x & y values */
            Vector (number[] xy);
/** create and set x & y values */
            Vector (object xy);
/** return string representation  */
            string toString ();
/** get dot product for this vector with a 2nd vector */
            number dotProduct (Vector vector);
/** get length as a vector (distance from origin) */
            number vectorLength ();
/** get angle (in radians) for this vector */
            number vectorAngle ();
/** return true if this point is equal to the other */
            boolean equals (Offset offset);
/** return true if this point is not equal to the other */
            boolean notEquals (Offset offset);
/** set this offset equal to the given offset */
            Offset assign (Offset offset);
/** add an offset to this one */
            Offset add (Offset offset);
/** subtract an offset from this one */
            Offset sub (Offset offset);
/** multiply this offset by the given one */
            Offset mul (Offset offset);
/** divide this offset by the given one */
            Offset div (Offset offset);
/** return new offset that is this offset plus given offset */
            Offset plus (Offset offset);
/** return new offset that is this offset minus given offset */
            Offset minus (Offset offset);
/** return new offset that is this offset multiplied by given offset */
            Offset times (Offset offset);
/** return new offset that is this offset divided by given offset */
            Offset dividedby (Offset offset);
    };

    class (Rect)
    {
        public:
            number left;
            number top;
            number right;
            number bottom;
/** return string representation  */
            string toString ();
/**  */
            Rect "Exception: Cannot read property 'top' of null";
/** return true if this rectangle is empty (no width or no height) */
            boolean empty ();
/** contains(Point p) return true if the point is inside this rectangle; contains(Rect r) return true if the rectangle passed in is entirely inside this rectangle */
            boolean contains (Rect r);
/** contains(Point p) return true if the point is inside this rectangle; contains(Rect r) return true if the rectangle passed in is entirely inside this rectangle */
            boolean contains (Point p);
/** return true if this rectangle overlaps the other rectangle at all (sharing an edge is not overlapping) */
            boolean overlaps (Rect r);
/** get top left corner point of this rectangle */
            Point leftTop ();
/** get top right corner point of this rectangle */
            Point rightTop ();
/** get bottom left corner point of this rectangle */
            Point leftBottom ();
/** get bottom right corner point of this rectangle */
            Point rightBottom ();
/** get center point of this rectangle */
            Point centerPoint ();
/** alias for Rect.left */
            number x1 ();
/** alias for Rect.top */
            number y1 ();
/** alias for Rect.right */
            number x2 ();
/** alias for Rect.bottom */
            number y2 ();
/** get the width of this rectangle */
            number width ();
/** get the height of this rectangle */
            number height ();
/** get a new rectangle that is the overlapping area of the the rectangles */
            Rect intersection (Rect r);
/** get the smallest possible new rectangle that contains both rectangles */
            Rect unionWith (Rect r);
/** move the rectangle to the left by some amount */
            moveLeft (number delta);
/** move the rectangle to the right by some amount */
            moveRight (number delta);
/** move the rectangle up by some amount */
            moveUp (number delta);
/** move the rectangle down by some amount */
            moveDown (number delta);
/** move the rectangle to a particular x location, leaving y unchanged */
            moveXTo (number x);
/** move the rectangle to a particular y location, leaving x unchanged */
            moveYTo (number y);
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo(Point p): move the rectangle to a particular point */
            moveTo (number x, number y);
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo(Point p): move the rectangle to a particular point */
            moveTo (Point p);
/** center(Point p): move the rectangle to be centered over a particular point; center(Rect r): move the rectangle to be centered within/relative to another rectangle */
            center (Rect r);
/** center(Point p): move the rectangle to be centered over a particular point; center(Rect r): move the rectangle to be centered within/relative to another rectangle */
            center (Point p);
/** set the size (width & height) of the rectangle */
            setSize (number n);
/**  */
            setWidth (number w);
/**  */
            setHeight (number h);
/** reduce the width of the rectangle while leaving the center point unchanged */
            horzShrink (number delta);
/** reduce the height of the rectangle while leaving the center point unchanged */
            vertShrink (number delta);
/** increase the width of the rectangle while leaving the center point unchanged */
            horzGrow (number delta);
/** increase the height of the rectangle while leaving the center point unchanged */
            vertGrow (number delta);
/** reduce the height and width of the rectangle while leaving the center point unchanged */
            shrink (number delta);
/** increase the height and width of the rectangle while leaving the center point unchanged */
            grow (number delta);
/** change the x coordinates of the rectangle by a multiplier */
            horzScale (number f);
/** change the y coordinates of the rectangle by a multiplier */
            vertScale (number f);
/** change the coordinates of the rectangle by a multiplier */
            scale (number f);
/** round the coordinates to closest whole number */
            round ();
/** convert rectangle to a Quad */
            Quad toQuad ();
/** return true if this rectangle is equal to the given one */
            boolean equals (Rect r2);
/** return true if this rectangle is not equal to the given one */
            boolean notEquals (Rect r2);
/** set this rectangle equal to the given one */
            Rect assign (Rect r2);
/** add(Point p): offset this rectangle's location by adding x & y coordinates of the point; add(Rect r): add another rectangle to this one by adding corresponding coordinates */
            Rect add (Rect r2);
/** add(Point p): offset this rectangle's location by adding x & y coordinates of the point; add(Rect r): add another rectangle to this one by adding corresponding coordinates */
            Rect add (Point p);
/** sub(Point p): offset this rectangle's location by subtracting x & y coordinates of the point; sub(Rect r): add another rectangle to this one by subtracting corresponding coordinates */
            Rect sub (Rect r2);
/** sub(Point p): offset this rectangle's location by subtracting x & y coordinates of the point; sub(Rect r): add another rectangle to this one by subtracting corresponding coordinates */
            Rect sub (Point p);
/** mul(Point p): change this rectangle's location by multiplying by x & y coordinates of the point; mul(Rect r): change this rect by multiplying by corresponding coordinates of another rectangle */
            Rect mul (Rect r2);
/** mul(Point p): change this rectangle's location by multiplying by x & y coordinates of the point; mul(Rect r): change this rect by multiplying by corresponding coordinates of another rectangle */
            Rect mul (Point p);
/** div(Point p): change this rectangle's location by dividing by x & y coordinates of the point; div(Rect r): change this rect by dividing by corresponding coordinates of another rectangle */
            Rect div (Rect r2);
/** div(Point p): change this rectangle's location by dividing by x & y coordinates of the point; div(Rect r): change this rect by dividing by corresponding coordinates of another rectangle */
            Rect div (Point p);
/**  */
            Rect plus (Rect r2);
/**  */
            Rect plus (Point p);
/**  */
            Rect minus (Rect r2);
/**  */
            Rect minus (Point p);
/**  */
            Rect times (Rect r2);
/**  */
            Rect times (Point p);
/**  */
            Rect dividedby (Rect r2);
/**  */
            Rect dividedby (Point p);
    };

    class (Quad)
    {
        public:
            Point[] points;
/** return string representation  */
            string toString ();
/** new Quad(): create an empty quad at 0,0; new Quad(Quad q): copy from another quad; new Quad(Rect r): create a quad from a rectangle; new Quad(RotatedRect r): create a quad from a rotated rectangle; new Quad(Point p1, Point p2, Point p3, Point p4): create a quad given its corner points; new Quad(Point p4): create a quad given an array of 4 points */
            Quad (args...);
/** return a rectangle that bounds the quad */
            Rect getBounds ();
/** return the calculated centerpoint of the quad */
            Point centerPoint ();
/** return true if this quad is equal to the given one */
            boolean equals (Quad q2);
/** return true if this quad is not equal to the given one */
            boolean notEquals (Quad q2);
/** returns true if the point is contained within this quad */
            boolean contains (Point p);
/** move the quad to the left by some amount */
            moveLeft (number delta);
/** move the quad to the right by some amount */
            moveRight (number delta);
/** move the quad up by some amount */
            moveUp (number delta);
/** move the quad down by some amount */
            moveDown (number delta);
/** rotate(n): rotate the quad by a rotation in radians (around the calculated center point of the quad); rotate(n, Offset o): rotate the quad by a rotation in radians around an offset center point */
            rotate (number rotationRadians, Offset centerPtOffset = Point(0,0));
    };

    class (RotatedRect : public Rect)
    {
        public:
            number left;
            number top;
            number right;
            number bottom;
            Point centerOffset;
/** create a new RotatedRect */
            RotatedRect (Rect rect = Rect(0,0), number rotationRadians = 0.0, Offset cpOffset = null);
/** return string representation  */
            string toString ();
/** set an offset for point around which rotation is applied */
            setCenterOffset (Offset cpOffset);
/** set the rotation of this rectangle to a particular amount in radians */
            setRotation (number rotationRadians, Offset cpOffset = null);
/** change the rotation of this rectangle by some number of radians */
            rotate (number rotateRadians);
/** create a Quad by applying the rectangle's rotation around the center point with offset */
            Quad getQuad ();
/** return true if this rectangle is empty (no width or no height) */
            boolean empty ();
/** contains(Point p) return true if the point is inside this rectangle; contains(Rect r) return true if the rectangle passed in is entirely inside this rectangle */
            boolean contains (Rect r);
/** contains(Point p) return true if the point is inside this rectangle; contains(Rect r) return true if the rectangle passed in is entirely inside this rectangle */
            boolean contains (Point p);
/** return true if this rectangle overlaps the other rectangle at all (sharing an edge is not overlapping) */
            boolean overlaps (Rect r);
/** get top left corner point of this rectangle */
            Point leftTop ();
/** get top right corner point of this rectangle */
            Point rightTop ();
/** get bottom left corner point of this rectangle */
            Point leftBottom ();
/** get bottom right corner point of this rectangle */
            Point rightBottom ();
/** get center point of this rectangle */
            Point centerPoint ();
/** alias for Rect.left */
            number x1 ();
/** alias for Rect.top */
            number y1 ();
/** alias for Rect.right */
            number x2 ();
/** alias for Rect.bottom */
            number y2 ();
/** get the width of this rectangle */
            number width ();
/** get the height of this rectangle */
            number height ();
/** get a new rectangle that is the overlapping area of the the rectangles */
            Rect intersection (Rect r);
/** get the smallest possible new rectangle that contains both rectangles */
            Rect unionWith (Rect r);
/** move the rectangle to the left by some amount */
            moveLeft (number delta);
/** move the rectangle to the right by some amount */
            moveRight (number delta);
/** move the rectangle up by some amount */
            moveUp (number delta);
/** move the rectangle down by some amount */
            moveDown (number delta);
/** move the rectangle to a particular x location, leaving y unchanged */
            moveXTo (number x);
/** move the rectangle to a particular y location, leaving x unchanged */
            moveYTo (number y);
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo(Point p): move the rectangle to a particular point */
            moveTo (number x, number y);
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo(Point p): move the rectangle to a particular point */
            moveTo (Point p);
/** center(Point p): move the rectangle to be centered over a particular point; center(Rect r): move the rectangle to be centered within/relative to another rectangle */
            center (Rect r);
/** center(Point p): move the rectangle to be centered over a particular point; center(Rect r): move the rectangle to be centered within/relative to another rectangle */
            center (Point p);
/** set the size (width & height) of the rectangle */
            setSize (number n);
/**  */
            setWidth (number w);
/**  */
            setHeight (number h);
/** reduce the width of the rectangle while leaving the center point unchanged */
            horzShrink (number delta);
/** reduce the height of the rectangle while leaving the center point unchanged */
            vertShrink (number delta);
/** increase the width of the rectangle while leaving the center point unchanged */
            horzGrow (number delta);
/** increase the height of the rectangle while leaving the center point unchanged */
            vertGrow (number delta);
/** reduce the height and width of the rectangle while leaving the center point unchanged */
            shrink (number delta);
/** increase the height and width of the rectangle while leaving the center point unchanged */
            grow (number delta);
/** change the x coordinates of the rectangle by a multiplier */
            horzScale (number f);
/** change the y coordinates of the rectangle by a multiplier */
            vertScale (number f);
/** change the coordinates of the rectangle by a multiplier */
            scale (number f);
/** round the coordinates to closest whole number */
            round ();
/** convert rectangle to a Quad */
            Quad toQuad ();
/** return true if this rectangle is equal to the given one */
            boolean equals (Rect r2);
/** return true if this rectangle is not equal to the given one */
            boolean notEquals (Rect r2);
/** set this rectangle equal to the given one */
            Rect assign (Rect r2);
/** add(Point p): offset this rectangle's location by adding x & y coordinates of the point; add(Rect r): add another rectangle to this one by adding corresponding coordinates */
            Rect add (Rect r2);
/** add(Point p): offset this rectangle's location by adding x & y coordinates of the point; add(Rect r): add another rectangle to this one by adding corresponding coordinates */
            Rect add (Point p);
/** sub(Point p): offset this rectangle's location by subtracting x & y coordinates of the point; sub(Rect r): add another rectangle to this one by subtracting corresponding coordinates */
            Rect sub (Rect r2);
/** sub(Point p): offset this rectangle's location by subtracting x & y coordinates of the point; sub(Rect r): add another rectangle to this one by subtracting corresponding coordinates */
            Rect sub (Point p);
/** mul(Point p): change this rectangle's location by multiplying by x & y coordinates of the point; mul(Rect r): change this rect by multiplying by corresponding coordinates of another rectangle */
            Rect mul (Rect r2);
/** mul(Point p): change this rectangle's location by multiplying by x & y coordinates of the point; mul(Rect r): change this rect by multiplying by corresponding coordinates of another rectangle */
            Rect mul (Point p);
/** div(Point p): change this rectangle's location by dividing by x & y coordinates of the point; div(Rect r): change this rect by dividing by corresponding coordinates of another rectangle */
            Rect div (Rect r2);
/** div(Point p): change this rectangle's location by dividing by x & y coordinates of the point; div(Rect r): change this rect by dividing by corresponding coordinates of another rectangle */
            Rect div (Point p);
/**  */
            Rect plus (Rect r2);
/**  */
            Rect plus (Point p);
/**  */
            Rect minus (Rect r2);
/**  */
            Rect minus (Point p);
/**  */
            Rect times (Rect r2);
/**  */
            Rect times (Point p);
/**  */
            Rect dividedby (Rect r2);
/**  */
            Rect dividedby (Point p);
    };

    class (Color)
    {
        public:
            number red;
            number green;
            number blue;
            number alpha;
/** return string representation  */
            string toString ();
/** create and color and set rgb values */
            Color ();
/** create and color and set rgb values */
            Color (number c);
/** create and color and set rgb values */
            Color (string colorstr);
/** create and color and set rgb values */
            Color (number r, number g, number b, number alpha = 1);
/** return true if this color is equal to the other (ignoring alpha) */
            boolean equals (Color color);
/** return true if this color is not equal to the other (ignoring alpha) */
            boolean notEquals (Color color);
/** set this color equal to the given color */
            Color assign (Color color);
/** convert this color to a matching shade of grey */
            convertToGrayscale ();
    };

    class (NetConnection)
    {
        public:
            string localAddr;
            number localPort;
            string remoteAddr;
            number remotePort;
/** return string representation  */
            string toString ();
/** create a NetConnection to manage a socket */
            NetConnection (object socket);
/** close the connection */
            close ();
/** setup connection close handler */
            NetClient onClose (function callback);
/** setup incoming message handler */
            NetClient onMessage (function callback);
/** send a message via a reliable transport mechanism */
            send (string message);
/** send a message via a reliable transport mechanism */
            send (MemBlock message);
/** send a message via a reliable transport mechanism */
            send (ISerializable message);
/** send a message via a reliable transport mechanism */
            send (object message);
/** send a message via the fastest transport mechanism */
            sendDgram (string message );
/** send a message via the fastest transport mechanism */
            sendDgram (MemBlock message );
/** send a message via the fastest transport mechanism */
            sendDgram (ISerializable message );
/** send a message via the fastest transport mechanism */
            sendDgram (object message );
    };

    class (NetClient)
    {
        public:
            boolean errorCallback;
/** return string representation  */
            string toString ();
/** create a network client for the named game */
            NetClient (string name, string clientKey);
/** connect to a server for your game */
            NetClient connect (function callback, object serverInfo = null);
/** find servers for your game */
            NetClient findServers (function callback, object options = null);
/** setup error handler */
            NetClient onError (function callback);
    };

    class (NetServer)
    {
        public:
            number serverPort;
            string serverAddr;
            boolean fixedPort;
            boolean allowDatagram;
            boolean listener;
            boolean listening;
            [] connections;
/** return string representation  */
            string toString ();
/** create a network server for the named game */
            NetServer (string name, string serverKey, object serverInfo = null);
/** open the server for incoming connections */
            NetServer listen (function callback);
/** send a message to all connections, with optional filter */
            number broadcast (object message, function filter = null);
/** setup error handler */
            NetServer onError (function callback);
/** close the listener and don't accept new connections */
            shutdown ();
    };
}
