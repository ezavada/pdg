/* This file automatically generated from docs/pdg-js.i */



pdg =
{

    var all_events = 0;
    var eventType_Startup = 1;
    var eventType_Shutdown = 2;
    var eventType_Timer = 3;
    var eventType_KeyDown = 4;
    var eventType_KeyUp = 5;
    var eventType_KeyPress = 6;
    var eventType_MouseDown = 7;
    var eventType_MouseUp = 8;
    var eventType_MouseMove = 9;
    var eventType_MouseEnter = 22;
    var eventType_MouseLeave = 23;
    var eventType_PortResized = 15;
    var eventType_ScrollWheel = 16;
    var eventType_SpriteTouch = 19;
    var eventType_SpriteAnimate = 17;
    var eventType_SpriteLayer = 18;
    var eventType_SpriteCollide = 20;
    var eventType_SpriteBreak = 21;
    var eventType_SoundEvent = 14;
    var soundEvent_DonePlaying = 0;
    var soundEvent_Looping = 1;
    var soundEvent_FailedToPlay = 2;
    var key_Break = 1;
    var key_Home = 2;
    var key_End = 3;
    var key_Clear = 4;
    var key_Help = 5;
    var key_Pause = 6;
    var key_Mute = 7;
    var key_Backspace = 8;
    var key_Delete = 127;
    var key_Tab = 9;
    var key_PageUp = 11;
    var key_PageDown = 12;
    var key_Return = 13;
    var key_Enter = 13;
    var key_F1 = 14;
    var key_F2 = 15;
    var key_F3 = 16;
    var key_F4 = 17;
    var key_F5 = 18;
    var key_F6 = 19;
    var key_F7 = 20;
    var key_F8 = 21;
    var key_F9 = 22;
    var key_F10 = 23;
    var key_F11 = 24;
    var key_F12 = 25;
    var key_FirstF = 14;
    var key_LastF = 25;
    var key_Insert = 26;
    var key_Escape = 27;
    var key_LeftArrow = 28;
    var key_RightArrow = 29;
    var key_UpArrow = 30;
    var key_DownArrow = 31;
    var key_FirstPrintable = 32;
    var screenPos_Normal = 0;
    var screenPos_Rotated180 = 1;
    var screenPos_Rotated90Clockwise = 2;
    var screenPos_Rotated90CounterClockwise = 3;
    var screenPos_FaceUp = 4;
    var screenPos_FaceDown = 5;
    var textStyle_Plain = 0;
    var textStyle_Bold = 1;
    var textStyle_Italic = 2;
    var textStyle_Underline = 4;
    var textStyle_Centered = 16;
    var textStyle_LeftJustified = 0;
    var textStyle_RightJustified = 32;
    var fit_None = 0;
    var fit_Height = 1;
    var fit_Width = 2;
    var fit_Inside = 3;
    var fit_Fill = 4;
    var fit_FillKeepProportions = 5;
    var init_CreateUniqueNewFile = 0;
    var init_OverwriteExisting = 1;
    var init_AppendToExisting = 2;
    var init_StdOut = 3;
    var init_StdErr = 4;
    var duration_Constant = -1;
    var duration_Instantaneous = 0;
    var animate_StartToEnd = 0;
    var animate_EndToStart = 1;
    var animate_Unidirectional = 0;
    var animate_Bidirectional = 2;
    var animate_NoLooping = 0;
    var animate_Looping = 4;
    var start_FromFirstFrame = -1;
    var start_FromLastFrame = -2;
    var all_Frames = 0;
    var action_CollideSprite = 0;
    var action_CollideWall = 1;
    var action_Offscreen = 2;
    var action_AnimationLoop = 8;
    var action_AnimationEnd = 9;
    var action_FadeComplete = 10;
    var action_FadeInComplete = 11;
    var action_FadeOutComplete = 12;
    var action_JointBreak = 13;
    var touch_MouseEnter = 20;
    var touch_MouseLeave = 21;
    var touch_MouseDown = 22;
    var touch_MouseUp = 23;
    var touch_MouseClick = 24;
    var collide_None = 0;
    var collide_Point = 1;
    var collide_BoundingBox = 2;
    var collide_CollisionRadius = 3;
    var collide_AlphaChannel = 4;
    var collide_Last = 4;
    var action_ErasePort = 40;
    var action_PreDrawLayer = 41;
    var action_PostDrawLayer = 42;
    var action_DrawPortComplete = 43;
    var action_AnimationStart = 44;
    var action_PreAnimateLayer = 45;
    var action_PostAnimateLayer = 46;
    var action_AnimationComplete = 47;
    var action_ZoomComplete = 48;
    var facing_North = 0;
    var facing_East = 64;
    var facing_South = 128;
    var facing_West = 192;
    var facing_Ignore = 256;
    var flipped_None = 0;
    var flipped_Horizontal = 64;
    var flipped_Vertical = 128;
    var flipped_Both = 192;
    var flipped_Ignore = 256;
    var timer_OneShot = 1;
    var timer_Repeating = 0;
    var timer_Never = -1;
    var linearTween = 0;
    var easeInQuad = 1;
    var easeOutQuad = 2;
    var easeInOutQuad = 3;
    var easeInCubic = 4;
    var easeOutCubic = 5;
    var easeInOutCubic = 6;
    var easeInQuart = 7;
    var easeOutQuart = 8;
    var easeInQuint = 10;
    var easeOutQuint = 11;
    var easeInOutQuint = 12;
    var easeInSine = 13;
    var easeOutSine = 14;
    var easeInOutSine = 15;
    var easeInExpo = 16;
    var easeOutExpo = 17;
    var easeInOutExpo = 18;
    var easeInCirc = 19;
    var easeOutCirc = 20;
    var easeInOutCirc = 21;
    var easeInBounce = 22;
    var easeOutBounce = 23;
    var easeInOutBounce = 24;
    var easeInBack = 25;
    var easeOutBack = 26;
    var easeInOutBack = 27;
    var lftTop = 0;
    var rgtTop = 1;
    var rgtBot = 2;
    var lftBot = 3;
    var fs;
    var evt;
    var gfx;
    var tm;
    var res;
    var cfg;
    var snd;
    var argv;

/**  */
    rand ();
/**  */
    gameCriticalRandom ();
/**  */
    srand ([number uint] seed);
/**  */
    registerEasingFunction (function easingFunc);
/**  */
    getFileManager ();
/**  */
    getLogManager ();
/**  */
    getConfigManager ();
/**  */
    getResourceManager ();
/**  */
    getEventManager ();
/**  */
    getTimerManager ();
/**  */
    registerSerializableClass (object klass);
/**  */
    getGraphicsManager ();
/**  */
    getSoundManager ();
/**  */
    createSpriteLayer ([object Port] port = null);
/**  */
    cleanupSpriteLayer ([object SpriteLayer] layer);
/**  */
    quit ();
/**  */
    run ();
/**  */
    idle ();
/** start node-inspector and open a debugger window in your browser */
    openDebugger ();
/**  */
    openConsole "Exception: Cannot call method 'indexOf' of undefined";
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
    on ([number int] eventType, function func);
/**  */
    onShutdown (function func);
/**  */
    onTimer (function func);
/**  */
    onKeyDown (function func);
/**  */
    onKeyUp (function func);
/**  */
    onKeyPress (function func);
/**  */
    onMouseDown (function func);
/**  */
    onMouseUp (function func);
/**  */
    onMouseMove (function func);
/**  */
    startRepl ();

    (MemBlock) =
    {

/**  */
        [string Binary] getData ();
/**  */
        number getDataSize ();
/**  */
        number getByte ([number uint] i);
/**  */
        [string Binary] getBytes ([number uint] start, [number uint] len);
    };

    (FileManager) =
    {

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

    (LogManager) =
    {

        var init_CreateUniqueNewFile = 0;
        var init_OverwriteExisting = 1;
        var init_AppendToExisting = 2;
        var init_StdOut = 3;
        var init_StdErr = 4;
/**  */
        number getLogLevel ();
/**  */
        setLogLevel ([number int] inLogLevel);
/**  */
        initialize (string inLogNameBase, [number int] initMode = LogManager.init_StdOut);
/**  */
        writeLogEntry ([number int] level, string category, string message);
/**  */
        string binaryDump ([string Binary] inData, [number int] length = 0, [number int] bytesPerLine = 20);
/**  */
        string binaryDump ([object MemBlock] inData, [number int] length = 0, [number int] bytesPerLine = 20);
    };

    (ConfigManager) =
    {

/**  */
        boolean useConfig (string inConfigName);
/**  */
        {string|}
        getConfigString (string inConfigItemName);
/**  */
        {number|}
        getConfigLong (string inConfigItemName);
/**  */
        {number|}
        getConfigFloat (string inConfigItemName);
/**  */
        {boolean|}
        getConfigBool (string inConfigItemName);
/**  */
        setConfigString (string inConfigItemName, string inValue);
/**  */
        setConfigLong (string inConfigItemName, [number int] inValue);
/**  */
        setConfigFloat (string inConfigItemName, number inValue);
/**  */
        setConfigBool (string inConfigItemName, boolean inValue);
    };

    (ResourceManager) =
    {

/**  */
        number openResourceFile (string filename);
/**  */
        [object Image] getImage (string imageName);
/**  */
        [object Sound] getSound (string soundName);
/**  */
        string getString ([number int] id, [number int] substring = -1);
/**  */
        number getResourceSize (string resourceName);
/**  */
        [string Binary] getResource (string resourceName);
/**  */
        string getResourcePaths ();
    };

    (Serializer) =
    {

/**  */
        serialize_d (number val);
/**  */
        serialize_f (number val);
/**  */
        serialize_4 ([number int] val);
/**  */
        serialize_4u ([number uint] val);
/**  */
        serialize_3u ([number uint] val);
/**  */
        serialize_2 ([number int] val);
/**  */
        serialize_2u ([number uint] val);
/**  */
        serialize_1 ([number int] val);
/**  */
        serialize_1u ([number uint] val);
/**  */
        serialize_uint ([number uint] val);
/**  */
        serialize_str (string str);
/**  */
        serialize_mem ([string Binary] mem);
/**  */
        serialize_mem ([object MemBlock] mem);
/**  */
        serialize_obj ([object ISerializable] obj);
/**  */
        number serializedSize (string arg);
/**  */
        number serializedSize ([number uint] arg);
/**  */
        number serializedSize ([object MemBlock] arg);
/**  */
        number serializedSize ([object ISerializable] arg);
/**  */
        number getDataSize ();
/**  */
        [object MemBlock] getDataPtr ();
    };

    (Deserializer) =
    {

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
        [object MemBlock] deserialize_mem ();
/**  */
        number deserialize_memGetLen ();
/**  */
        [object ISerializable] deserialize_obj ();
/**  */
        setDataPtr ([string Binary] data);
/**  */
        setDataPtr ([object MemBlock] data);
    };

    (ISerializable) =
    {

    };

    (IEventHandler) =
    {

    };

    (EventEmitter) =
    {

/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
        addHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
        removeHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove all handlers */
        clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
        blockEvent ([number int] inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
        unblockEvent ([number int] inEventType);
    };

    (EventManager : public EventEmitter) =
    {

/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
        addHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
        removeHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove all handlers */
        clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
        blockEvent ([number int] inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
        unblockEvent ([number int] inEventType);
/**  */
        boolean isKeyDown (string unicodeChar);
/**  */
        boolean isKeyDown ([number uint] utf16CharCode);
/**  */
        boolean isRawKeyDown ([number int] keyCode);
/**  */
        boolean isButtonDown ([number int] buttonNumber = 0);
/** NOT IMPLEMENTED */
        object getDeviceOrientation ();
    };

    (TimerManager) =
    {

/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
        addHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
        removeHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove all handlers */
        clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
        blockEvent ([number int] inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
        unblockEvent ([number int] inEventType);
/**  */
        startTimer ([number int] id, [number uint] delay, boolean oneShot = true);
/**  */
        cancelTimer ([number int] id);
/**  */
        cancelAllTimers ();
/**  */
        delayTimer ([number int] id, [number uint] delay);
/**  */
        delayTimerUntil ([number int] id, [number uint] msTime);
/**  */
        pause ();
/**  */
        unpause ();
/**  */
        boolean isPaused ();
/**  */
        pauseTimer ([number int] id);
/**  */
        unpauseTimer ([number int] id);
/**  */
        boolean isTimerPaused ([number int] id);
/**  */
        number getWhenTimerFiresNext ([number int] id);
/**  */
        number getMilliseconds ();
    };

    (IAnimationHelper) =
    {

    };

    (Animated) =
    {

/**  */
        [object Rect] getBoundingBox ();
/**  */
        [object Rect] getRotatedBounds ();
/**  */
        [object Point] getLocation ();
/**  */
        setLocation ([object Point] inLocation);
/**  */
        number getSpeed ();
/**  */
        setSpeed (number inSpeed);
/**  */
        [object Vector] getVelocity ();
/**  */
        setVelocity ([object Vector] deltaPerSec);
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
        [object Offset] getCenterOffset ();
/**  */
        setCenterOffset ([object Offset] inCenterOffset);
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
        move ([object Point] delta, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        moveTo ([object Point] where, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        setVelocityInRadians (number speed, number direction);
/**  */
        number getMovementDirectionInRadians ();
/**  */
        stopMoving ();
/**  */
        accelerate (number deltaSpeed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        accelerateTo (number speed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        setSize (number width, number height);
/**  */
        grow (number factor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stretch (number widthFactor, number heightFactor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        startGrowing (number amountPerSecond);
/**  */
        stopGrowing ();
/**  */
        startStretching (number widthPerSecond, number heightPerSecond);
/**  */
        stopStretching ();
/**  */
        resize (number deltaWidth, number deltaHeight, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        resizeTo (number width, number height, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotate (number radians, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotateTo (number radiansRotation, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stopSpinning ();
/**  */
        changeCenter ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        changeCenterTo ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        wait ([number int] msDuration);
/**  */
        setFriction (number frictionCoefficient);
/**  */
        applyForce ([object Vector] force, [number int] msDuration = duration_Instantaneous);
/**  */
        applyTorque (number forceSpin, [number int] msDuration = duration_Instantaneous);
/**  */
        stopAllForces ();
/**  */
        addAnimationHelper ([object IAnimationHelper] helper);
/**  */
        removeAnimationHelper ([object IAnimationHelper] helper);
/**  */
        clearAnimationHelpers ();
/**  */
        boolean animate ([number int] msElapsed);
    };

    (CpArbiter) =
    {

/** true if this is the first moment of contact between the objects, false if part of an ongoing collison */
        boolean isFirstContact ();
/**  */
        number getCount ();
/**  */
        [object Vector] getNormal ();
/**  */
        [object Point] getPoint ();
/**  */
        number getDepth ();
    };

    (CpConstraint) =
    {

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
        [object Sprite] getSprite ();
/**  */
        [object Sprite] getOtherSprite ();
/**  */
        [object Offset] getAnchor ();
/**  */
        setAnchor ([object Offset] inAnchor);
/**  */
        [object Offset] getOtherAnchor ();
/**  */
        setOtherAnchor ([object Offset] inOtherAnchor);
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
        [object Offset] getGrooveStart ();
/**  */
        setGrooveStart ([object Offset] inGrooveStart);
/**  */
        [object Offset] getGrooveEnd ();
/**  */
        setGrooveEnd ([object Offset] inGrooveEnd);
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

    (CpSpace) =
    {

/**  */
        useSpatialHash (number dim, [number int] count);
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

    (ISpriteDrawHelper) =
    {

    };

    (Sprite : public Animated,public EventEmitter) =
    {

/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
        addHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
        removeHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove all handlers */
        clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
        blockEvent ([number int] inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
        unblockEvent ([number int] inEventType);
/**  */
        [object Rect] getBoundingBox ();
/**  */
        [object Rect] getRotatedBounds ();
/**  */
        [object Point] getLocation ();
/**  */
        setLocation ([object Point] inLocation);
/**  */
        number getSpeed ();
/**  */
        setSpeed (number inSpeed);
/**  */
        [object Vector] getVelocity ();
/**  */
        setVelocity ([object Vector] deltaPerSec);
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
        [object Offset] getCenterOffset ();
/**  */
        setCenterOffset ([object Offset] inCenterOffset);
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
        move ([object Point] delta, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        moveTo ([object Point] where, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        setVelocityInRadians (number speed, number direction);
/**  */
        number getMovementDirectionInRadians ();
/**  */
        stopMoving ();
/**  */
        accelerate (number deltaSpeed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        accelerateTo (number speed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        setSize (number width, number height);
/**  */
        grow (number factor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stretch (number widthFactor, number heightFactor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        startGrowing (number amountPerSecond);
/**  */
        stopGrowing ();
/**  */
        startStretching (number widthPerSecond, number heightPerSecond);
/**  */
        stopStretching ();
/**  */
        resize (number deltaWidth, number deltaHeight, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        resizeTo (number width, number height, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotate (number radians, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotateTo (number radiansRotation, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stopSpinning ();
/**  */
        changeCenter ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        changeCenterTo ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        wait ([number int] msDuration);
/**  */
        setFriction (number frictionCoefficient);
/**  */
        applyForce ([object Vector] force, [number int] msDuration = duration_Instantaneous);
/**  */
        applyTorque (number forceSpin, [number int] msDuration = duration_Instantaneous);
/**  */
        stopAllForces ();
/**  */
        addAnimationHelper ([object IAnimationHelper] helper);
/**  */
        removeAnimationHelper ([object IAnimationHelper] helper);
/**  */
        clearAnimationHelpers ();
/**  */
        [object Rect] getFrameRotatedBounds ([number int] frame);
/**  */
        setFrame ([number int] frame);
/** which frame of animation the sprite is currently showing */
        number getCurrentFrame ();
/** total number of frames of animation for this sprite */
        number getFrameCount ();
/**  */
        setFramesPerSecond (number fps, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames, [number int] animateFlags = animate_Looping);
/**  */
        stopFrameAnimation ();
/**  */
        boolean setWantsAnimLoopEvents (boolean wantsThem = true);
/**  */
        boolean setWantsAnimEndEvents (boolean wantsThem = true);
/**  */
        addFramesImage ([object Image] image, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames);
/**  */
        setDrawHelper ([object ISpriteDrawHelper] helper);
/**  */
        setPostDrawHelper ([object ISpriteDrawHelper] helper);
/**  */
        changeFramesImage ([object Image] oldImage, [object Image] newImage);
/**  */
        offsetFrameCenters ([number int] offsetX, [number int] offsetY, [object Image] image = null, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames);
/** NOT IMPLEMENTED */
        getFrameCenterOffset ();
/**  */
        setOpacity (number opacity);
/**  */
        number getOpacity ();
/**  */
        fadeTo (number targetOpacity, [number int] msDuration, [number int] easing = linearTween);
/**  */
        fadeIn ([number int] msDuration, [number int] easing = linearTween);
/**  */
        fadeOut ([number int] msDuration, [number int] easing = linearTween);
/**  */
        moveBehind ([object Sprite] sprite);
/**  */
        moveInFrontOf ([object Sprite] sprite);
/** put this sprite in front of all others in its layer */
        moveToFront ();
/** put this sprite behind all others in its layer */
        moveToBack ();
/**  */
        enableCollisions ([number int] collisionType = collide_AlphaChannel);
/**  */
        disableCollisions ();
/**  */
        setCollisionRadius (number pixelRadius);
/**  */
        number getCollisionRadius ();
/**  */
        useCollisionMask ([object Image] frameImage, [object Image] maskImage);
/**  */
        setElasticity (number elasticity);
/**  */
        number getElasticity ();
/**  */
        boolean setWantsMouseOverEvents (boolean wantsThem = true);
/**  */
        boolean setWantsClickEvents (boolean wantsThem = true);
/**  */
        number setMouseDetectMode ([number int] collisionType = collide_BoundingBox);
/** get the layer that contains this sprite */
        [object SpriteLayer] getLayer ();
/**  */
        [object Sprite] makeStatic ();
/**  */
        number getFriction ();
/**  */
        setCollideGroup ([number int] group);
/**  */
        number getCollideGroup ();
/**  */
        [object CpConstraint] pinJoint ([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number breakingForce = 0);
/**  */
        [object CpConstraint] slideJoint ([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number minDist, number maxDist, number breakingForce = 0);
/**  */
        [object CpConstraint] pivotJoint ([object Sprite] otherSprite, [object Point] pivot, number breakingForce = 0);
/**  */
        [object CpConstraint] grooveJoint ([object Offset] grooveStart, [object Offset] grooveEnd, [object Sprite] otherSprite, [object Offset] otherAnchor, number breakingForce = 0);
/**  */
        [object CpConstraint] springJoint ([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number restLength, number stiffness, number damping, number breakingForce = 0);
/**  */
        [object CpConstraint] rotarySpring ([object Sprite] otherSprite, number restAngle, number stiffness, number damping, number breakingForce = 0);
/**  */
        [object CpConstraint] rotaryLimit ([object Sprite] otherSprite, number minAngle, number maxAngle, number breakingForce = 0);
/**  */
        [object CpConstraint] ratchet ([object Sprite] otherSprite, number rachetInterval, number phase, number breakingForce = 0);
/**  */
        [object CpConstraint] gear ([object Sprite] otherSprite, number gearRatio, number initialAngle = 0, number breakingForce = 0);
/**  */
        [object CpConstraint] motor ([object Sprite] otherSprite, number spin, number maxTorque = INFINITY);
/**  */
        removeJoint ([object CpConstraint] joint);
/**  */
        disconnect ([object Sprite] otherSprite);
/**  */
        makeJointBreakable ([object CpConstraint] joint, number breakingForce);
/**  */
        makeJointUnbreakable ([object CpConstraint] joint);
/**  */
        [object IEventHandler] on ([number int] eventCode, function func);
/**  */
        [object IEventHandler] onCollideSprite (function func);
/**  */
        [object IEventHandler] onCollideWall (function func);
/**  */
        [object IEventHandler] onOffscreen (function func);
/**  */
        [object IEventHandler] onAnimationLoop (function func);
/**  */
        [object IEventHandler] onAnimationEnd (function func);
/**  */
        [object IEventHandler] onFadeComplete (function func);
/**  */
        [object IEventHandler] onFadeInComplete (function func);
/**  */
        [object IEventHandler] onFadeOutComplete (function func);
/**  */
        [object IEventHandler] onMouseEnter (function func);
/**  */
        [object IEventHandler] onMouseLeave (function func);
/**  */
        [object IEventHandler] onMouseDown (function func);
/**  */
        [object IEventHandler] onMouseUp (function func);
/**  */
        [object IEventHandler] onMouseClick (function func);
    };

    (SpriteLayer : public Animated) =
    {

/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
        addHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
        removeHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove all handlers */
        clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
        blockEvent ([number int] inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
        unblockEvent ([number int] inEventType);
/**  */
        [object Rect] getBoundingBox ();
/**  */
        [object Rect] getRotatedBounds ();
/**  */
        [object Point] getLocation ();
/**  */
        setLocation ([object Point] inLocation);
/**  */
        number getSpeed ();
/**  */
        setSpeed (number inSpeed);
/**  */
        [object Vector] getVelocity ();
/**  */
        setVelocity ([object Vector] deltaPerSec);
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
        [object Offset] getCenterOffset ();
/**  */
        setCenterOffset ([object Offset] inCenterOffset);
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
        move ([object Point] delta, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        moveTo ([object Point] where, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        setVelocityInRadians (number speed, number direction);
/**  */
        number getMovementDirectionInRadians ();
/**  */
        stopMoving ();
/**  */
        accelerate (number deltaSpeed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        accelerateTo (number speed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        setSize (number width, number height);
/**  */
        grow (number factor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stretch (number widthFactor, number heightFactor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        startGrowing (number amountPerSecond);
/**  */
        stopGrowing ();
/**  */
        startStretching (number widthPerSecond, number heightPerSecond);
/**  */
        stopStretching ();
/**  */
        resize (number deltaWidth, number deltaHeight, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        resizeTo (number width, number height, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotate (number radians, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotateTo (number radiansRotation, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stopSpinning ();
/**  */
        changeCenter ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        changeCenterTo ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        wait ([number int] msDuration);
/**  */
        setFriction (number frictionCoefficient);
/**  */
        applyForce ([object Vector] force, [number int] msDuration = duration_Instantaneous);
/**  */
        applyTorque (number forceSpin, [number int] msDuration = duration_Instantaneous);
/**  */
        stopAllForces ();
/**  */
        addAnimationHelper ([object IAnimationHelper] helper);
/**  */
        removeAnimationHelper ([object IAnimationHelper] helper);
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
        fadeIn ([number int] msDuration, [number int] easing = linearTween);
/**  */
        fadeOut ([number int] msDuration, [number int] easing = linearTween);
/**  */
        moveBehind ([object SpriteLayer] layer);
/**  */
        moveInFrontOf ([object SpriteLayer] layer);
/** move this layer in front of all other layers */
        moveToFront ();
/** move this layer behind all other layers */
        moveToBack ();
/**  */
        [object Sprite] findSprite ([number int] id);
/**  */
        boolean hasSprite ([object Sprite] sprite);
/**  */
        addSprite ([object Sprite] newSprite);
/**  */
        removeSprite ([object Sprite] oldSprite);
/**  */
        removeAllSprites ();
/**  */
        enableCollisions ();
/**  */
        disableCollisions ();
/**  */
        enableCollisionsWithLayer ([object SpriteLayer] otherLayer);
/**  */
        disableCollisionsWithLayer ([object SpriteLayer] otherLayer);
/**  */
        [object Sprite] createSprite ();
/**  */
        [object Port] getSpritePort ();
/**  */
        setSpritePort ([object Port] port);
/**  */
        setOrigin ([object Point] origin);
/** get the point in the layer that is drawn at 0,0 in the port */
        [object Point] getOrigin ();
/**  */
        setAutoCenter (boolean autoCenter = true);
/**  */
        setFixedMoveAxis (boolean fixedAxis = true);
/**  */
        setZoom (number zoomLevel);
/** get the current zoom factor */
        number getZoom ();
/**  */
        zoomTo (number zoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) );
/**  */
        zoom (number deltaZoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) );
/**  */
        [object Point] layerToPortPoint ([object Point] p);
/**  */
        [object Offset] layerToPortOffset ([object Offset] o);
/**  */
        [object Vector] layerToPortVector ([object Vector] v);
/**  */
        [object Rect] layerToPortRect ([object Rect] r);
/**  */
        [object Quad] layerToPortQuad ([object Quad] q);
/**  */
        [object Point] portToLayerPoint ([object Point] p);
/**  */
        [object Offset] portToLayerOffset ([object Offset] o);
/**  */
        [object Vector] portToLayerVector ([object Vector] v);
/**  */
        [object Rect] portToLayerRect ([object Rect] r);
/**  */
        [object Quad] portToLayerQuad ([object Quad] q);
/**  */
        setGravity (number gravity, boolean keepItDownward = true);
/**  */
        setKeepGravityDownward (boolean keepItDownward = true);
/**  */
        setDamping (number damping);
/**  */
        [object CpSpace] getSpace ();
/**  */
        [object IEventHandler] on ([number int] eventCode, function func);
/**  */
        [object IEventHandler] onCollideSprite (function func);
/**  */
        [object IEventHandler] onCollideWall (function func);
/**  */
        [object IEventHandler] onOffscreen (function func);
/**  */
        [object IEventHandler] onAnimationLoop (function func);
/**  */
        [object IEventHandler] onAnimationEnd (function func);
/**  */
        [object IEventHandler] onFadeComplete (function func);
/**  */
        [object IEventHandler] onFadeInComplete (function func);
/**  */
        [object IEventHandler] onFadeOutComplete (function func);
/**  */
        [object IEventHandler] onMouseEnter (function func);
/**  */
        [object IEventHandler] onMouseLeave (function func);
/**  */
        [object IEventHandler] onMouseDown (function func);
/**  */
        [object IEventHandler] onMouseUp (function func);
/**  */
        [object IEventHandler] onMouseClick (function func);
/**  */
        [object IEventHandler] onErasePort (function func);
/**  */
        [object IEventHandler] onPreDrawLayer (function func);
/**  */
        [object IEventHandler] onPostDrawLayer (function func);
/**  */
        [object IEventHandler] onDrawPortComplete (function func);
/**  */
        [object IEventHandler] onAnimationStart (function func);
/**  */
        [object IEventHandler] onPreAnimateLayer (function func);
/**  */
        [object IEventHandler] onAnimationComplete (function func);
/**  */
        [object IEventHandler] onZoomComplete (function func);
    };

    (TileLayer : public SpriteLayer) =
    {

/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
        addHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
        removeHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove all handlers */
        clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
        blockEvent ([number int] inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
        unblockEvent ([number int] inEventType);
/**  */
        [object Rect] getBoundingBox ();
/**  */
        [object Rect] getRotatedBounds ();
/**  */
        [object Point] getLocation ();
/**  */
        setLocation ([object Point] inLocation);
/**  */
        number getSpeed ();
/**  */
        setSpeed (number inSpeed);
/**  */
        [object Vector] getVelocity ();
/**  */
        setVelocity ([object Vector] deltaPerSec);
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
        [object Offset] getCenterOffset ();
/**  */
        setCenterOffset ([object Offset] inCenterOffset);
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
        move ([object Point] delta, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        moveTo ([object Point] where, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        setVelocityInRadians (number speed, number direction);
/**  */
        number getMovementDirectionInRadians ();
/**  */
        stopMoving ();
/**  */
        accelerate (number deltaSpeed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        accelerateTo (number speed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween);
/**  */
        setSize (number width, number height);
/**  */
        grow (number factor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stretch (number widthFactor, number heightFactor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        startGrowing (number amountPerSecond);
/**  */
        stopGrowing ();
/**  */
        startStretching (number widthPerSecond, number heightPerSecond);
/**  */
        stopStretching ();
/**  */
        resize (number deltaWidth, number deltaHeight, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        resizeTo (number width, number height, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotate (number radians, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        rotateTo (number radiansRotation, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        stopSpinning ();
/**  */
        changeCenter ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        changeCenterTo ([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad);
/**  */
        wait ([number int] msDuration);
/**  */
        setFriction (number frictionCoefficient);
/**  */
        applyForce ([object Vector] force, [number int] msDuration = duration_Instantaneous);
/**  */
        applyTorque (number forceSpin, [number int] msDuration = duration_Instantaneous);
/**  */
        stopAllForces ();
/**  */
        addAnimationHelper ([object IAnimationHelper] helper);
/**  */
        removeAnimationHelper ([object IAnimationHelper] helper);
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
        fadeIn ([number int] msDuration, [number int] easing = linearTween);
/**  */
        fadeOut ([number int] msDuration, [number int] easing = linearTween);
/**  */
        moveBehind ([object SpriteLayer] layer);
/**  */
        moveInFrontOf ([object SpriteLayer] layer);
/** move this layer in front of all other layers */
        moveToFront ();
/** move this layer behind all other layers */
        moveToBack ();
/**  */
        [object Sprite] findSprite ([number int] id);
/**  */
        boolean hasSprite ([object Sprite] sprite);
/**  */
        addSprite ([object Sprite] newSprite);
/**  */
        removeSprite ([object Sprite] oldSprite);
/**  */
        removeAllSprites ();
/**  */
        enableCollisions ();
/**  */
        disableCollisions ();
/**  */
        enableCollisionsWithLayer ([object SpriteLayer] otherLayer);
/**  */
        disableCollisionsWithLayer ([object SpriteLayer] otherLayer);
/**  */
        [object Sprite] createSprite ();
/**  */
        [object Port] getSpritePort ();
/**  */
        setSpritePort ([object Port] port);
/**  */
        setOrigin ([object Point] origin);
/** get the point in the layer that is drawn at 0,0 in the port */
        [object Point] getOrigin ();
/**  */
        setAutoCenter (boolean autoCenter = true);
/**  */
        setFixedMoveAxis (boolean fixedAxis = true);
/**  */
        setZoom (number zoomLevel);
/** get the current zoom factor */
        number getZoom ();
/**  */
        zoomTo (number zoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) );
/**  */
        zoom (number deltaZoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) );
/**  */
        [object Point] layerToPortPoint ([object Point] p);
/**  */
        [object Offset] layerToPortOffset ([object Offset] o);
/**  */
        [object Vector] layerToPortVector ([object Vector] v);
/**  */
        [object Rect] layerToPortRect ([object Rect] r);
/**  */
        [object Quad] layerToPortQuad ([object Quad] q);
/**  */
        [object Point] portToLayerPoint ([object Point] p);
/**  */
        [object Offset] portToLayerOffset ([object Offset] o);
/**  */
        [object Vector] portToLayerVector ([object Vector] v);
/**  */
        [object Rect] portToLayerRect ([object Rect] r);
/**  */
        [object Quad] portToLayerQuad ([object Quad] q);
/**  */
        setGravity (number gravity, boolean keepItDownward = true);
/**  */
        setKeepGravityDownward (boolean keepItDownward = true);
/**  */
        setDamping (number damping);
/**  */
        [object CpSpace] getSpace ();
/**  */
        setWorldSize ([number int] width, [number int] height, boolean repeatingX = false, boolean repeatingY = false);
/**  */
        [object Rect] getWorldSize ();
/**  */
        [object Rect] getWorldBounds ();
/**  */
        defineTileSet ([number int] tileWidth, [number int] tileHeight, [object Image] tilese, boolean hasTransparency = true, boolean flipTiles = false);
/**  */
        loadMapData ([string Binary] data, [number int] mapWidth = 0, [number int] mapHeight = 0, [number int] dstX, [number int] dstY);
/**  */
        loadMapData ([object MemBlock] data, [number int] mapWidth = 0, [number int] mapHeight = 0, [number int] dstX, [number int] dstY);
/**  */
        [object MemBlock] getMapData ([number int] mapWidth = 0, [number int] mapHeight = 0, [number int] srcX, [number int] srcY);
/**  */
        [object Image] getTileSetImage ();
/**  */
        [object Point] getTileSize ();
/**  */
        {number|object}
        getTileTypeAt ([number int] x, [number int] y, boolean separateFacing = false);
/**  */
        setTileTypeAt ([number int] x, [number int] y, [number uint] t, [number uint] facing = facing_Ignore);
/**  */
        number checkCollision ([object Sprite] movingSprite, [number uint] alphaThreshold = 128, boolean shortCircuit = true);
    };

    (Image) =
    {

/**  */
        number getWidth ();
/**  */
        number getHeight ();
/** get image boundary rect, optionally with top left at given point */
        [object Rect] getImageBounds ([object Point] at);
/** get image that is a single frame of this multi-frame image */
        [object Image] getFrame ([number int] frameNum);
/** get image that is an arbitrary subsection of this image */
        [object Image] getSubsection ([object Quad] quad);
/** get image that is an arbitrary subsection of this image */
        [object Image] getSubsection ([object Rect] quad);
/**  */
        number getFrameWidth ();
/**  */
        setFrameWidth ([number int] inFrameWidth);
/** how many frames in this multi-frame image */
        number getNumFrames ();
/** set the number of frames that are in this image */
        setNumFrames ([number int] num);
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
        number getAlphaValue ([object Point] p);
/**  */
        number getAlphaValue ([number int] x, [number int] y);
/**  */
        [object Color] getPixel ([object Point] p);
/**  */
        [object Color] getPixel ([number int] x, [number int] y);
    };

    (Font) =
    {

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

    (Port) =
    {

/**  */
        [object Rect] getClipRect ();
/**  */
        setClipRect ([object Rect] inClipRect);
/** NOT IMPLEMENTED: get the Image that is being used as the cursor */
        [object Image] getCursor ();
/** NOT IMPLEMENTED */
        setCursor ([object Image] cursorImage, [object Point] hotSpot);
/**  */
        [object Rect] getDrawingArea ();
/**  */
        fillRect ([object Quad] quad, [object Color] rgba = "black");
/**  */
        fillRect ([object Rect] quad, [object Color] rgba = "black");
/**  */
        frameRect ([object Quad] quad, [object Color] rgba = "black");
/**  */
        frameRect ([object Rect] quad, [object Color] rgba = "black");
/**  */
        drawLine ([object Point] from, [object Point] to, [object Color] rgba = "black");
/**  */
        frameOval ([object Point] centerPt, number xRadius, number yRadius, [object Color] rgba = "black");
/**  */
        fillOval ([object Point] centerPt, number xRadius, number yRadius, [object Color] rgba = "black");
/**  */
        frameCircle ([object Point] centerPt, number radius, [object Color] rgba = "black");
/**  */
        fillCircle ([object Point] centerPt, number radius, [object Color] rgba = "black");
/**  */
        frameRoundRect ([object Rect] rect, number radius, [object Color] rgba = "black");
/**  */
        fillRoundRect ([object Rect] rect, number radius, [object Color] rgba = "black");
/**  */
        fillRectEx ([object Quad] quad, [number uint] pattern, [number uint] patternShift, [object Color] rgba);
/**  */
        fillRectEx ([object Rect] quad, [number uint] pattern, [number uint] patternShift, [object Color] rgba);
/**  */
        frameRectEx ([object Quad] quad, [number uint] thickness, [number uint] pattern, [number uint] patternShift, [object Color] rgba);
/**  */
        frameRectEx ([object Rect] quad, [number uint] thickness, [number uint] pattern, [number uint] patternShift, [object Color] rgba);
/**  */
        drawLineEx ([object Point] from, [object Point] to, [number uint] thickness, [number uint] pattern, [number uint] patternShift, [object Color] rgba);
/**  */
        fillRectWithGradient ([object Quad] quad, [object Color] startColor, [object Color] endColor);
/**  */
        fillRectWithGradient ([object Rect] quad, [object Color] startColor, [object Color] endColor);
/**  */
        drawText (string text, [object Point] location, [number int] size, [number uint] style = textStyle_Plain, [object Color] rgba = 'black');
/**  */
        drawText (string text, [object Quad] quad, [number int] size, [number uint] style = textStyle_Plain, [object Color] rgba = 'black');
/**  */
        drawText (string text, [object Rect] rect, [number int] size, [number uint] style = textStyle_Plain, [object Color] rgba = 'black');
/**  */
        drawImage ([object Image] img, [object Point] loc);
/**  */
        drawImage ([object Image] img, [object Quad] quad);
/**  */
        drawImage ([object Image] img, [object Rect] rect, [number int] fitType = fit_Fill, boolean clipOverflow = false);
/**  */
        drawTexture ([object Image] img, [object Rect] r);
/**  */
        number getTextWidth (string text, [number int] size, [number uint] style = textStyle_Plain, [number int] len = -1);
/**  */
        [object Font] getCurrentFont ([number uint] style = textStyle_Plain);
/**  */
        setFont ([object Font] font = DEFAULT_FONT);
/**  */
        setFontForStyle ([number uint] style, [object Font] font = DEFAULT_FONT);
/**  */
        setFontScalingFactor (number scaleBy);
/** NOT IMPLEMENTED */
        number startTrackingMouse ([object Rect] rect);
/** NOT IMPLEMENTED */
        stopTrackingMouse ([number int] trackingRef);
/** NOT IMPLEMENTED: restore the default system cursor */
        resetCursor ();
    };

    (GraphicsManager) =
    {

/**  */
        number getNumScreens ();
/**  */
        number getFPS ();
/**  */
        [object Point] getMouse ();
/** returns object with width, height, depth and maxWindowRect for specified screen */
        object getCurrentScreenMode ([number int] screenNum);
/** changes specified screen to closest matching mode */
        setScreenMode ([number int] screenNum, [number int] width, [number int] height, [number int] depth);
/** create windowed drawing port with given dimensions, title and depth */
        [object Port] createWindowPort ([object Rect] rect, string windName = "", [number int] bpp = 0);
/** create full screen drawing port with given dimensions on given screen, optionally changing depth */
        [object Port] createFullScreenPort ([object Rect] rect, [number int] screenNum = PRIMARY_SCREEN, [number int] bpp = 0);
/** close given port, along with its window and restore screen mode if changed */
        closeGraphicsPort ([object Port] port);
/** get a font with optional scaling adjust */
        [object Font] createFont (string fontName, number scalingFactor = 1.0);
/** return the primary graphics port */
        [object Port] getMainPort ();
/** change the primary graphics port's fullscreen mode, return new state */
        boolean setMainPortFullScreenMode (boolean fullScreen = true);
/** return whether primary graphics port is fullscreen or not */
        boolean inFullScreenMode ();
    };

    (Sound : public EventEmitter) =
    {

/** add a new handler for some event type, or for all events if no type specified.  \param inHandler the object to handle events \param inEventType the type of event to handle */
        addHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove a handler for some event type, or for all events (see note) if no type specified. If the handler is listed multiple times it will only remove it once. <br/><br/> NOTE: inType == all_events doesn't work quite like you might expect. If you have registered a handler for multiple events, but not with all_events, doing removeHandler(handler, all_events) will do nothing. Basically, all_events is a special event type that matches all event types when considering whether to invoke a handler or not. <br/><br/> It is safe to call remove handler from within an event handler's handleEvent() call. \param inHandler the object to handle events \param inEventType the type of event to stop handling (see note) */
        removeHandler ([object IEventHandler] inHandler, [number int] inEventType = all_events);
/** remove all handlers */
        clear ();
/** temporarily ignore all events of a particular type. Events that are blocked are NOT cached for later, they are just dropped. \param inEventType the type of event to block */
        blockEvent ([number int] inEventType);
/** stop ignoring events of a particular type  \param inEventType the type of event to unblock */
        unblockEvent ([number int] inEventType);
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
        fadeOut ([number uint] fadeMs);
/**  */
        fadeIn ([number uint] fadeMs);
/**  */
        fadeTo (number level, [number uint] fadeMs);
/**  */
        skip ([number int] skipMilliseconds);
/**  */
        skipTo ([number uint] timeMs);
/**  */
        [object IEventHandler] on ([number int] eventCode, function func);
/**  */
        [object IEventHandler] onDonePlaying (function func);
/**  */
        [object IEventHandler] onLooping (function func);
/**  */
        [object IEventHandler] onFailedToPlay (function func);
    };

    (SoundManager) =
    {

/** 0.0 - silent to 1.0 - full volume */
        setVolume (number level);
/**  */
        setMute (boolean muted);
    };

    (Point : public Offset) =
    {

        var x;
        var y;
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
        number distance ([object Point] point);
/** do a projection of a second point onto this point */
        [object Point] projection ([object Point] point);
/** return true if this point is equal to the other */
        boolean equals ([object Offset] offset);
/** return true if this point is not equal to the other */
        boolean notEquals ([object Offset] offset);
/** set this offset equal to the given offset */
        [object Offset] assign ([object Offset] offset);
/** add an offset to this one */
        [object Offset] add ([object Offset] offset);
/** subtract an offset from this one */
        [object Offset] sub ([object Offset] offset);
/** multiply this offset by the given one */
        [object Offset] mul ([object Offset] offset);
/** divide this offset by the given one */
        [object Offset] div ([object Offset] offset);
/** return new offset that is this offset plus given offset */
        [object Offset] plus ([object Offset] offset);
/** return new offset that is this offset minus given offset */
        [object Offset] minus ([object Offset] offset);
/** return new offset that is this offset multiplied by given offset */
        [object Offset] times ([object Offset] offset);
/** return new offset that is this offset divided by given offset */
        [object Offset] dividedby ([object Offset] offset);
    };

    (Offset) =
    {

        var x;
        var y;
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
        boolean equals ([object Offset] offset);
/** return true if this point is not equal to the other */
        boolean notEquals ([object Offset] offset);
/** set this offset equal to the given offset */
        [object Offset] assign ([object Offset] offset);
/** add an offset to this one */
        [object Offset] add ([object Offset] offset);
/** subtract an offset from this one */
        [object Offset] sub ([object Offset] offset);
/** multiply this offset by the given one */
        [object Offset] mul ([object Offset] offset);
/** divide this offset by the given one */
        [object Offset] div ([object Offset] offset);
/** return new offset that is this offset plus given offset */
        [object Offset] plus ([object Offset] offset);
/** return new offset that is this offset minus given offset */
        [object Offset] minus ([object Offset] offset);
/** return new offset that is this offset multiplied by given offset */
        [object Offset] times ([object Offset] offset);
/** return new offset that is this offset divided by given offset */
        [object Offset] dividedby ([object Offset] offset);
    };

    (Vector : public Offset) =
    {

        var x;
        var y;
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
        number dotProduct ([object Vector] vector);
/** get length as a vector (distance from origin) */
        number vectorLength ();
/** get angle (in radians) for this vector */
        number vectorAngle ();
/** return true if this point is equal to the other */
        boolean equals ([object Offset] offset);
/** return true if this point is not equal to the other */
        boolean notEquals ([object Offset] offset);
/** set this offset equal to the given offset */
        [object Offset] assign ([object Offset] offset);
/** add an offset to this one */
        [object Offset] add ([object Offset] offset);
/** subtract an offset from this one */
        [object Offset] sub ([object Offset] offset);
/** multiply this offset by the given one */
        [object Offset] mul ([object Offset] offset);
/** divide this offset by the given one */
        [object Offset] div ([object Offset] offset);
/** return new offset that is this offset plus given offset */
        [object Offset] plus ([object Offset] offset);
/** return new offset that is this offset minus given offset */
        [object Offset] minus ([object Offset] offset);
/** return new offset that is this offset multiplied by given offset */
        [object Offset] times ([object Offset] offset);
/** return new offset that is this offset divided by given offset */
        [object Offset] dividedby ([object Offset] offset);
    };

    (Rect) =
    {

        var left;
        var top;
        var right;
        var bottom;
/** return string representation  */
        string toString ();
/**  */
        Rect "Exception: Cannot read property 'top' of null";
/** return true if this rectangle is empty (no width or no height) */
        boolean empty ();
/** contains([Point] p) return true if the point is inside this rectangle; contains([Rect] r) return true if the rectangle passed in is entirely inside this rectangle */
        boolean contains ([object Rect] r);
/** contains([Point] p) return true if the point is inside this rectangle; contains([Rect] r) return true if the rectangle passed in is entirely inside this rectangle */
        boolean contains ([object Point] p);
/** return true if this rectangle overlaps the other rectangle at all (sharing an edge is not overlapping) */
        boolean overlaps ([object Rect] r);
/** get top left corner point of this rectangle */
        [object Point] leftTop ();
/** get top right corner point of this rectangle */
        [object Point] rightTop ();
/** get bottom left corner point of this rectangle */
        [object Point] leftBottom ();
/** get bottom right corner point of this rectangle */
        [object Point] rightBottom ();
/** get center point of this rectangle */
        [object Point] centerPoint ();
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
        [object Rect] intersection ([object Rect] r);
/** get the smallest possible new rectangle that contains both rectangles */
        [object Rect] unionWith ([object Rect] r);
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
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo([Point] p): move the rectangle to a particular point */
        moveTo (number x, number y);
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo([Point] p): move the rectangle to a particular point */
        moveTo ([object Point] p);
/** center([Point] p): move the rectangle to be centered over a particular point; center([Rect] r): move the rectangle to be centered within/relative to another rectangle */
        center ([object Rect] r);
/** center([Point] p): move the rectangle to be centered over a particular point; center([Rect] r): move the rectangle to be centered within/relative to another rectangle */
        center ([object Point] p);
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
        [object Quad] toQuad ();
/** return true if this rectangle is equal to the given one */
        boolean equals ([object Rect] r2);
/** return true if this rectangle is not equal to the given one */
        boolean notEquals ([object Rect] r2);
/** set this rectangle equal to the given one */
        [object Rect] assign ([object Rect] r2);
/** add([Point] p): offset this rectangle's location by adding x & y coordinates of the point; add([Rect] r): add another rectangle to this one by adding corresponding coordinates */
        [object Rect] add ([object Rect] r2);
/** add([Point] p): offset this rectangle's location by adding x & y coordinates of the point; add([Rect] r): add another rectangle to this one by adding corresponding coordinates */
        [object Rect] add ([object Point] p);
/** sub([Point] p): offset this rectangle's location by subtracting x & y coordinates of the point; sub([Rect] r): add another rectangle to this one by subtracting corresponding coordinates */
        [object Rect] sub ([object Rect] r2);
/** sub([Point] p): offset this rectangle's location by subtracting x & y coordinates of the point; sub([Rect] r): add another rectangle to this one by subtracting corresponding coordinates */
        [object Rect] sub ([object Point] p);
/** mul([Point] p): change this rectangle's location by multiplying by x & y coordinates of the point; mul([Rect] r): change this rect by multiplying by corresponding coordinates of another rectangle */
        [object Rect] mul ([object Rect] r2);
/** mul([Point] p): change this rectangle's location by multiplying by x & y coordinates of the point; mul([Rect] r): change this rect by multiplying by corresponding coordinates of another rectangle */
        [object Rect] mul ([object Point] p);
/** div([Point] p): change this rectangle's location by dividing by x & y coordinates of the point; div([Rect] r): change this rect by dividing by corresponding coordinates of another rectangle */
        [object Rect] div ([object Rect] r2);
/** div([Point] p): change this rectangle's location by dividing by x & y coordinates of the point; div([Rect] r): change this rect by dividing by corresponding coordinates of another rectangle */
        [object Rect] div ([object Point] p);
/**  */
        [object Rect] plus ([object Rect] r2);
/**  */
        [object Rect] plus ([object Point] p);
/**  */
        [object Rect] minus ([object Rect] r2);
/**  */
        [object Rect] minus ([object Point] p);
/**  */
        [object Rect] times ([object Rect] r2);
/**  */
        [object Rect] times ([object Point] p);
/**  */
        [object Rect] dividedby ([object Rect] r2);
/**  */
        [object Rect] dividedby ([object Point] p);
    };

    (Quad) =
    {

        var points;
/** return string representation  */
        string toString ();
/** new Quad(): create an empty quad at 0,0; new Quad([Quad] q): copy from another quad; new Quad([Rect] r): create a quad from a rectangle; new Quad([RotatedRect r]): create a quad from a rotated rectangle; new Quad([Point] p1, [Point] p2, [Point] p3, [Point] p4): create a quad given its corner points; new Quad([Point] p[4]): create a quad given an array of 4 points */
        Quad (args...);
/** return a rectangle that bounds the quad */
        [object Rect] getBounds ();
/** return the calculated centerpoint of the quad */
        [object Point] centerPoint ();
/** return true if this quad is equal to the given one */
        boolean equals ([object Quad] q2);
/** return true if this quad is not equal to the given one */
        boolean notEquals ([object Quad] q2);
/** returns true if the point is contained within this quad */
        boolean contains ([object Point] p);
/** move the quad to the left by some amount */
        moveLeft (number delta);
/** move the quad to the right by some amount */
        moveRight (number delta);
/** move the quad up by some amount */
        moveUp (number delta);
/** move the quad down by some amount */
        moveDown (number delta);
/** rotate(n): rotate the quad by a rotation in radians (around the calculated center point of the quad); rotate(n, [Offset] o): rotate the quad by a rotation in radians around an offset center point */
        rotate (number rotationRadians, [object Offset] centerPtOffset = Point(0,0));
    };

    (RotatedRect : public Rect) =
    {

        var left;
        var top;
        var right;
        var bottom;
        var centerOffset;
/** create a new RotatedRect */
        RotatedRect ([object Rect] rect = Rect(0,0), number rotationRadians = 0.0, [object Offset] cpOffset = null);
/** return string representation  */
        string toString ();
/** set an offset for point around which rotation is applied */
        setCenterOffset ([object Offset] cpOffset);
/** set the rotation of this rectangle to a particular amount in radians */
        setRotation (number rotationRadians, [object Offset] cpOffset = null);
/** change the rotation of this rectangle by some number of radians */
        rotate (number rotateRadians);
/** create a Quad by applying the rectangle's rotation around the center point with offset */
        [object Quad] getQuad ();
/** return true if this rectangle is empty (no width or no height) */
        boolean empty ();
/** contains([Point] p) return true if the point is inside this rectangle; contains([Rect] r) return true if the rectangle passed in is entirely inside this rectangle */
        boolean contains ([object Rect] r);
/** contains([Point] p) return true if the point is inside this rectangle; contains([Rect] r) return true if the rectangle passed in is entirely inside this rectangle */
        boolean contains ([object Point] p);
/** return true if this rectangle overlaps the other rectangle at all (sharing an edge is not overlapping) */
        boolean overlaps ([object Rect] r);
/** get top left corner point of this rectangle */
        [object Point] leftTop ();
/** get top right corner point of this rectangle */
        [object Point] rightTop ();
/** get bottom left corner point of this rectangle */
        [object Point] leftBottom ();
/** get bottom right corner point of this rectangle */
        [object Point] rightBottom ();
/** get center point of this rectangle */
        [object Point] centerPoint ();
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
        [object Rect] intersection ([object Rect] r);
/** get the smallest possible new rectangle that contains both rectangles */
        [object Rect] unionWith ([object Rect] r);
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
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo([Point] p): move the rectangle to a particular point */
        moveTo (number x, number y);
/** moveTo(x,y): the rectangle to a particular (x, y) location; moveTo([Point] p): move the rectangle to a particular point */
        moveTo ([object Point] p);
/** center([Point] p): move the rectangle to be centered over a particular point; center([Rect] r): move the rectangle to be centered within/relative to another rectangle */
        center ([object Rect] r);
/** center([Point] p): move the rectangle to be centered over a particular point; center([Rect] r): move the rectangle to be centered within/relative to another rectangle */
        center ([object Point] p);
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
        [object Quad] toQuad ();
/** return true if this rectangle is equal to the given one */
        boolean equals ([object Rect] r2);
/** return true if this rectangle is not equal to the given one */
        boolean notEquals ([object Rect] r2);
/** set this rectangle equal to the given one */
        [object Rect] assign ([object Rect] r2);
/** add([Point] p): offset this rectangle's location by adding x & y coordinates of the point; add([Rect] r): add another rectangle to this one by adding corresponding coordinates */
        [object Rect] add ([object Rect] r2);
/** add([Point] p): offset this rectangle's location by adding x & y coordinates of the point; add([Rect] r): add another rectangle to this one by adding corresponding coordinates */
        [object Rect] add ([object Point] p);
/** sub([Point] p): offset this rectangle's location by subtracting x & y coordinates of the point; sub([Rect] r): add another rectangle to this one by subtracting corresponding coordinates */
        [object Rect] sub ([object Rect] r2);
/** sub([Point] p): offset this rectangle's location by subtracting x & y coordinates of the point; sub([Rect] r): add another rectangle to this one by subtracting corresponding coordinates */
        [object Rect] sub ([object Point] p);
/** mul([Point] p): change this rectangle's location by multiplying by x & y coordinates of the point; mul([Rect] r): change this rect by multiplying by corresponding coordinates of another rectangle */
        [object Rect] mul ([object Rect] r2);
/** mul([Point] p): change this rectangle's location by multiplying by x & y coordinates of the point; mul([Rect] r): change this rect by multiplying by corresponding coordinates of another rectangle */
        [object Rect] mul ([object Point] p);
/** div([Point] p): change this rectangle's location by dividing by x & y coordinates of the point; div([Rect] r): change this rect by dividing by corresponding coordinates of another rectangle */
        [object Rect] div ([object Rect] r2);
/** div([Point] p): change this rectangle's location by dividing by x & y coordinates of the point; div([Rect] r): change this rect by dividing by corresponding coordinates of another rectangle */
        [object Rect] div ([object Point] p);
/**  */
        [object Rect] plus ([object Rect] r2);
/**  */
        [object Rect] plus ([object Point] p);
/**  */
        [object Rect] minus ([object Rect] r2);
/**  */
        [object Rect] minus ([object Point] p);
/**  */
        [object Rect] times ([object Rect] r2);
/**  */
        [object Rect] times ([object Point] p);
/**  */
        [object Rect] dividedby ([object Rect] r2);
/**  */
        [object Rect] dividedby ([object Point] p);
    };

    (Color) =
    {

        var red;
        var green;
        var blue;
        var alpha;
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
        boolean equals ([object Color] color);
/** return true if this color is not equal to the other (ignoring alpha) */
        boolean notEquals ([object Color] color);
/** set this color equal to the given color */
        [object Color] assign ([object Color] color);
/** convert this color to a matching shade of grey */
        convertToGrayscale ();
    };
}
