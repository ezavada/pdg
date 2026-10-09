// -----------------------------------------------
// Simple.js
//
// Written by Ed Zavada, 2012
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

var pdg = require('pdg');

var path = require('path');
var createCharacterAimDemo = require('./character-aim-demo.js');
var createCharacterPhysicsDemo = require('./character-physics-demo.js');

// GC Monitoring
const automatedDemo = process.argv.indexOf('--ui-test') >= 0;
const GCMonitor = !pdg.visualTestSession && !automatedDemo && process.versions && process.versions.node && !process.ios
    ? require('./gc-monitor.js') : null;
let gcMonitor = null;

var drawBalls = true;
var drawSpinner = true;
var drawWalkingHero = true;
var drawStandingHero = true;
var drawGlobe = true;
var playMusic = pdg.hasSound;
var playSounds = pdg.hasSound;

var gBackgroundColor = new pdg.Color("teal");  // was teal

var kWindowWidth  = 800;
var kWindowHeight =  600;
var kFullscreen   = (global.process.ios) ? true : false;

var kFinalLayerZoom     = 0.25;
var kRockRiseSeconds    = 2.0;
var kNumSprites         = 20; 
var kMaxSpriteMoveDelta =  300;

// see if we were launched from the pdg/test directory or the pdg directory
// this is mainly necessary because of the multiple locations we can be launched
// from when we are in a C++ debugger verses launching from the command line
var launchedFromTest = process.ios || /[\/\\]test$/.test(global.process.cwd());
var testDir = launchedFromTest ? "" : "test/";
var dataDir = testDir + "data/";

// Use absolute path to avoid canonicalization issues
var samplesDir = path.resolve(dataDir, "spriter-samples") + path.sep;

var gSpriteFilename = dataDir + "yinyang.png";
var gEarthFilename = dataDir + "earthmap2.png";
var gHeroFilename = path.resolve(dataDir, "animation-demo/wonkyskeleton.scml");
var gOriginalHeroFilename = samplesDir + "wonkyskeleton/wonkyskeleton.scml";
var gGreyGuyFilename = samplesDir + "greyguy/player.scml";
var gRockFilename = testDir + "perf_tests/canvasmark2013/images/asteroid1.png";
var gStepFilename = process.cwd() + "/" + dataDir + "step.wav";
var gClink1Filename = process.cwd() + "/" + dataDir + "clink1.mp3";
var gClink2Filename = process.cwd() + "/" + dataDir + "clink2.mp3";
var gHitFilename = process.cwd() + "/" + dataDir + "hit.wav";
var gMusicFilename = process.cwd() + "/" + dataDir + "Peppy_The-Firing-Squad_YMXB.mp3";

var gCollisions = true;


var gPort;
var gSpriteLayer;
var gMasterBallSprite;
var gBallImage;
var gEarthImage;
var gGreyGuyIK = null;
var gWonkyAim = null;
var gGreyGuyAim = null;
var gOriginalWonky = null;
var gCharacterPhysics = [];
var gPhysicsBones = false;
var gCharacterPhysicsTime = null;

var gCollisionCount = 0;

var gStartingMs = 0;

var gMusic = 0;
var gClink1;
var gClink2;

///--------------------------------------------------------------------------------------
// main
///--------------------------------------------------------------------------------------



function main()
{
	console.log("in test/main.js main()");
	console.log("argv[0]: " + global.process.argv[0]);
	console.log("cwd: " + global.process.cwd());
 	var logMgr = pdg.getLogManager();
 	logMgr.setLogLevel(10);
// 	logMgr.initialize("simple", logMgr.init_OverwriteExisting);

    // Start GC monitoring
    if (GCMonitor) {
        gcMonitor = new GCMonitor({
            logToConsole: true,
            trackMemoryUsage: true,
            trackFrameRate: true,
            gcThreshold: 10, // Log GC events longer than 10ms
            pdg: pdg
        });
        gcMonitor.start();
        console.log("GC monitoring started");
    }

    Randomize();
    
    SetUpSpriteWorld();
    
    AddSprites();
    
//    pdg.startRepl();	// go into interactive mode
    
    var demoFrames = 0, demoFinished = false;
    pdg.on(pdg.eventType_PortDraw, function() {
        if (automatedDemo && !demoFinished && ++demoFrames >= 180) {
            if (!gWonkyAim || !gGreyGuyAim) throw new Error('Character demos did not initialize');
            if (Math.abs(gPort.getCamera().getZoom() - kFinalLayerZoom) > 0.00001 ||
                !Number.isFinite(gWonkyAim.cycleStartSeconds) ||
                !gGreyGuyIK || !Number.isFinite(gGreyGuyIK.riseStartSeconds)) {
                throw new Error('Introductory camera zoom did not complete and start the character demos');
            }
            demoFinished = true;
            console.log('PASS: rendered Grey Guy and Wonky Skeleton');
            pdg.quit();
        }
        return false;
    });
    RunAnimation();
    
    pdg.onShutdown( CleanUp );
//	pdg.on(pdg.eventType_Sound, function(evt) { return true; });

}

///--------------------------------------------------------------------------------------
//  Randomize
///--------------------------------------------------------------------------------------

function Randomize() {
	console.log("in Randomize()");
	pdg.srand( pdg.tm.getMilliseconds() >>> 0 );
}

///--------------------------------------------------------------------------------------
//  SetUpSpriteWorld
///--------------------------------------------------------------------------------------

function SetUpSpriteWorld() {
	console.log("in SetupSpriteWorld()");

        // Create the SpriteWorld
    pdg.gfx.setTargetFPS(50.0);
    var r = new pdg.Rect(kWindowWidth, kWindowHeight);
    if (kFullscreen) {
//    	console.log(pdg.gfx.getCurrentScreenMode(0));
//    	pdg.gfx.setScreenMode(0, kWindowWidth, kWindowHeight, 32);
        console.log("  creating full screen port "+r);
		gPort = pdg.gfx.createFullScreenPort(r);
	} else {
        console.log("  creating window port "+r);
		gPort = pdg.gfx.createWindowPort(r, "PDG Simple Sprite Test");
	}

        // Create the Sprite Layers
	console.log("  creating spritelayer");
	gSpriteLayer = pdg.createSpriteLayer(gPort);
	gSpriteLayer.setUseChipmunkPhysics();
    if (gCollisions) gSpriteLayer.enableCollisions();
    // Layers inherit the port camera. Keep direct background/HUD drawing and
    // already projected overlays in port coordinates, as before.
    gPort.setCameraDrawingEnabled(false);
    var camera = gPort.getCamera();
    camera.zoomTo(kFinalLayerZoom, automatedDemo ? 0.25 : 10.0);
    var zoomComplete = false;
    
    	// Set the background color
	console.log("  setup spritelayer erase callback");
    gSpriteLayer.onErasePort( function(evt) {
        var animationMs = pdg.visualTestSession ? pdg.visualTestSession.now() : evt.millisec;
        // Camera completion has no timestamp. Start on the next drawing frame
        // so playback and its updates use the same animation clock.
        if (zoomComplete) {
            zoomComplete = false;
            if (gWonkyAim) gWonkyAim.start(animationMs / 1000);
            if (gOriginalWonky && gOriginalWonky.startSeconds === null) gOriginalWonky.startSeconds = animationMs / 1000;
            if (gGreyGuyIK && gGreyGuyIK.riseStartSeconds === null) {
                gGreyGuyIK.riseStartSeconds = animationMs / 1000;
                console.log("Zoom complete: raising the rock over " + kRockRiseSeconds + " seconds.");
            }
        }
 		var portRect = gPort.getDrawingArea();
		//var backgroundAttrs = new pdg.Attributes().fillColor(gBackgroundColor);
		//gPort.drawRect(portRect, backgroundAttrs);
        var loc = portRect.centerPoint();
        if (!gStartingMs) gStartingMs = animationMs;
        var t = (animationMs - gStartingMs);
        var rotation = t / 5000;
        var scale = t/10;
        if (scale > 400.0) scale = 400;
        if (drawGlobe) {
			var earthAttrs = new pdg.Attributes().sphereRotation(rotation).texture(gEarthImage).lightOffset(new pdg.Offset(1, 0));
			gPort.drawSphere(loc, scale, earthAttrs);
        	//gPort.drawTexturedSphere( gEarthImage, loc, scale, rotation);
    	}
        // PortDraw timestamps are milliseconds; keep the demo's animation
        // clock and duration in floating-point seconds.
        if (!pdg.visualTestSession || !pdg.visualTestSession.paused) {
            UpdateGreyGuyRock(animationMs / 1000);
            UpdateCharacterDemos(animationMs / 1000);
        }
		DrawGreyGuyRock();
		var fps = "FPS: " + pdg.gfx.getFPS() + ".0";
		var where = new pdg.Point(10, kWindowHeight - 20);
		var fpsAttrs = new pdg.Attributes().textSize(14).fillColor("white");
		gPort.drawText(fps.substring(0,9), where, fpsAttrs);
		
		// Track frame rate for GC monitoring
		if (gcMonitor) {
		    gcMonitor.onFrame();
		}
		
		return true; // completely handled
	});

    camera.onZoomComplete(function() {
        zoomComplete = true;
        return false;
    });

    // Draw contact/target markers after the characters.
    gSpriteLayer.onPostDrawLayer(function() {
        DrawGreyGuyIKOverlay();
        DrawCharacterDemoOverlay();
        return false;
    });
    pdg.onKeyPress(function(evt) {
        var key=String.fromCharCode(evt.unicode).toLowerCase();
        if(key==='p'){gCharacterPhysics.forEach(function(demo){demo.start();});return true;}
        if(key==='b'){gPhysicsBones=!gPhysicsBones;gCharacterPhysics.forEach(function(demo){demo.setBones(gPhysicsBones);});return true;}
        if (gGreyGuyIK && (evt.unicode === 73 || evt.unicode === 105)) {
            ToggleGreyGuyIK();
            return true;
        }
        return false;
    });

	console.log("  creating ball image");
	gBallImage = new pdg.Image(gSpriteFilename);
	console.log("  ball image created, size: " + gBallImage.getWidth() + "x" + gBallImage.getHeight());
    console.log("  creating earth image from: " + gEarthFilename);
    gEarthImage = new pdg.Image(gEarthFilename);
    console.log("  earth image created, size: " + gEarthImage.getWidth() + "x" + gEarthImage.getHeight());
}

// a helper object that keeps an animated object within bounds and causes it to 
// bounce if it goes out of bounds
var BoundsHelper = new pdg.IAnimationHelper( function(what, deltaSeconds) {
	var boundsRect = gPort.getDrawingArea();
	boundsRect.scale(1 / kFinalLayerZoom);
	var spriteRect = what.getBoundingBox();
	var body = what.physics;
    var physical = body && body !== pdg.PhysicsBody.NoPhysics;
    var moveVector = physical ? body.getVelocity() : what.getMovement();
    function setMotion() {
        if (physical) body.setVelocity(moveVector);
        else what.setMovement(moveVector.x, moveVector.y);
    }
	if (boundsRect.right < spriteRect.right && moveVector.x > 0) {
		// reverse direction of horizontal movement
		moveVector.x = -moveVector.x;
		setMotion();
	} else if (boundsRect.left > spriteRect.left && moveVector.x < 0) {
		// reverse direction of horizontal movement
		moveVector = physical ? body.getVelocity() : what.getMovement();
		moveVector.x = -moveVector.x;
		setMotion();
	}
	if (boundsRect.bottom < spriteRect.bottom && moveVector.y > 0) {
		// reverse direction of vertical movement
		moveVector = physical ? body.getVelocity() : what.getMovement();
		moveVector.y = -moveVector.y;
		setMotion();
	} else if (boundsRect.top > spriteRect.top && moveVector.y < 0) {
		// reverse direction of vertical movement
		moveVector = physical ? body.getVelocity() : what.getMovement();
		moveVector.y = -moveVector.y;
		setMotion();
	}
	return true; // keep helping
});

function BallCollideFunc(sprite, contact) {
    if (contact.phase !== pdg.collision_Begin) return;
    const xloc = gSpriteLayer.layerToPortPoint(sprite.getLocation()).x;
    const xoffset = xloc - gPort.getDrawingArea().width() / 2;
    ++gCollisionCount;
    // Use impulse strength directly for this demo's sound-volume response.
    const soundVol = Math.min(1, Math.max(0.1, Math.hypot(contact.impulse.x, contact.impulse.y) / 4000));
    if (playSounds) {
        const sound = gCollisionCount % 2 ? gClink1 : gClink2;
        if (sound) sound.play(soundVol, xoffset);
    }
}

function WallCollideFunc(evt) {
	return true;
}

///--------------------------------------------------------------------------------------
//  CreateBallSprite - load the master ball sprite and prepare it for cloning later
///--------------------------------------------------------------------------------------

function CreateBallSprite() {
	var ballSprite = gSpriteLayer.createSprite();
	ballSprite.addFramesImage(gBallImage);
	ballSprite.setSize(gBallImage.getWidth(), gBallImage.getHeight());
	var ballRadius = gBallImage.getWidth()/2;
	ballSprite.setupCollider().setCircle( ballRadius );

    ballSprite.collider.setContactHandler(function(contact) {
        BallCollideFunc(ballSprite, contact);
    });
// 	ballSprite.onCollideWall(WallCollideFunc);

	ballSprite.addAnimationHelper(BoundsHelper);

	return ballSprite;
}


///--------------------------------------------------------------------------------------
//  AddSprites - clone the master sprite, and add the clones to the SpriteWorld
///--------------------------------------------------------------------------------------

function AddSprites() {
	console.log("in AddSprites()");
    var newSprite;
	var greyGuySprite;
	// Sprite locations are layer coordinates. Place the characters near the
	// bottom center of the viewport after the introductory zoom finishes.
	var stageBounds = gPort.getDrawingArea();
	var worldScale = 1 / kFinalLayerZoom;
	var heroBaseline = (stageBounds.bottom - 40) * worldScale;

	if (drawBalls) {
		console.log("Creating " + kNumSprites + " ball sprites...");
		for (spriteNum = 0; spriteNum < kNumSprites; spriteNum++) {
			newSprite = CreateBallSprite();
			newSprite.id = spriteNum;
			var screenCenter = gPort.getDrawingArea().scale(1 / kFinalLayerZoom).centerPoint();
			var max_x = screenCenter.x - gBallImage.getWidth()/2;
			var max_y = screenCenter.y - gBallImage.getHeight()/2;
			var loc = new pdg.Point((pdg.rand() % max_x * 2), pdg.rand() % max_y * 2);
			newSprite.setLocation(loc);
			console.log("Created ball sprite " + spriteNum + " at position " + loc.x + "," + loc.y);

			if (gCollisions) {
				newSprite.collider.setEnabled(true);
			} else {
				newSprite.collider.setEnabled(false);
			}

			do {	// make sure we get movement in both axis
				var v = new pdg.Vector(pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta, pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta);
				newSprite.setupPhysicsBody().setVelocity(v);
			} while (v.x == 0 || v.y == 0);
		}
    }
    
	if (drawSpinner) {
        // This is drawn from its logical bounds, not from the ball's image frame.
        const spinner = gSpriteLayer.createSprite();
        spinner.setSize(gBallImage.getWidth() * 2, gBallImage.getHeight() * 2);
        spinner.setLocation(gPort.getDrawingArea().centerPoint());
        spinner.addAnimationHelper(BoundsHelper);
        spinner.setupFrameCollider(pdg.frameCollider_Bounds).setEnabled(gCollisions);
        spinner.collider.setContactHandler(function(contact) { BallCollideFunc(spinner, contact); });
        const size = spinner.getSize(), mass = 10;
        const inertia = mass * (size.x * size.x + size.y * size.y) / 12;
        spinner.setupPhysicsBody(mass, inertia);
	
        const frame = pdg.createDrawing();
        frame.addRect(new pdg.Rect(-size.x / 2, -size.y / 2, size.x / 2, size.y / 2),
            new pdg.Attributes().lineColor("white").lineThickness(1.0).fillColor("black"));
        spinner.createPart('frame').setDrawing(frame);
		spinner.physics.setVelocity(10, 10);
        spinner.physics.setAngularVelocity(1.5); // radians/second, changed naturally by contacts
	}

	if (drawWalkingHero) {
		console.log("AddSprites: createSpriteFromSpriterFile ["+gHeroFilename+"]");
		newSprite = gSpriteLayer.createSpriteFromSpriterFile(gHeroFilename);
		if (newSprite) {
			newSprite.setLocation(new pdg.Point(
				(stageBounds.left + stageBounds.width() * 0.35) * worldScale, heroBaseline));
			newSprite.setScale(worldScale, worldScale);
            gWonkyAim = createCharacterAimDemo(pdg, newSprite, gSpriteLayer, worldScale, {
                label: 'Wonky', reference: 'Idle', clips: ['Idle', 'Walk'], flipWithCycle: true,
                head: 'bone_002', headParent: 'bone_001', shoulder: 'bone_012',
                elbow: 'bone_013', hand: 'bone_014', grip: {x:16,y:5}, sword: false
            });
		}
	}

    if (drawWalkingHero) {
        // Original playback retains Walk's optional debug tracks, Attack's blur,
        // and the changing bone hierarchy in Crumble. Do not opt this Sprite
        // into the fixed-hierarchy pose controller.
        var original = gSpriteLayer.createSpriteFromSpriterFile(gOriginalHeroFilename);
        if (original) {
            original.setLocation(new pdg.Point(
                (stageBounds.left + stageBounds.width() * 0.14) * worldScale, heroBaseline));
            original.setScale(worldScale, worldScale);
            original.startAnimation('Walk');
            gOriginalWonky = {sprite:original, clip:'Walk', clips:['Walk','Attack','Crumble','Idle'],
                startSeconds:null, intervalSeconds:4.0};
        }
    }

	if (drawStandingHero) {
		console.log("AddSprites: createSpriteFromSpriterFile ["+gGreyGuyFilename+"]");
		greyGuySprite = gSpriteLayer.createSpriteFromSpriterFile(gGreyGuyFilename);
		if (greyGuySprite) {
			greyGuySprite.setLocation(new pdg.Point(
				(stageBounds.left + stageBounds.width() * 0.65) * worldScale, heroBaseline));
			greyGuySprite.setScale(worldScale, worldScale);
			if (greyGuySprite.hasAnimation('idle')) {
				console.log("sprite has Idle animation");
				greyGuySprite.startAnimation('idle');
			}
            SetUpGreyGuyIK(greyGuySprite, worldScale);
            gGreyGuyAim = createCharacterAimDemo(pdg, greyGuySprite, gSpriteLayer, worldScale, {
                label: 'Grey Guy', reference: 'idle',
                head: 'head', headParent: 'chest', shoulder: 'front_arm',
                elbow: 'front_forarm', hand: 'front_hand', handSlot: 'p_hand_idle_0',
                grip: {x:17,y:0}, sword: true
            });
		}
	}
}


function UpdateCharacterDemos(timeSeconds) {
    var mouse = pdg.gfx.getMouse();
    var bounds = gPort.getDrawingArea();
    if (gWonkyAim) gWonkyAim.update(timeSeconds, mouse, bounds);
    if (gGreyGuyAim) gGreyGuyAim.update(timeSeconds, mouse, bounds);
    if(!gCharacterPhysics.length && gWonkyAim && gGreyGuyAim && gGreyGuyIK.riseProgress===1) {
        gCharacterPhysics=[
            createCharacterPhysicsDemo(pdg,gWonkyAim,1/kFinalLayerZoom,
                {label:'Wonky',mass:50,elbow:'bone_013',hand:'bone_014'}),
            createCharacterPhysicsDemo(pdg,gGreyGuyAim,1/kFinalLayerZoom,
                {label:'Grey Guy',mass:70,elbow:'front_forarm',hand:'front_hand'})
        ];
        gCharacterPhysics.forEach(function(demo){demo.setBones(gPhysicsBones);});
        console.log('P: test character reflection, attachment and recovery; B: PDG bone overlay; I: foot IK');
    }
    var dt=gCharacterPhysicsTime===null?0:Math.max(0,Math.min(.1,timeSeconds-gCharacterPhysicsTime));
    gCharacterPhysicsTime=timeSeconds;
    gCharacterPhysics.forEach(function(demo){demo.update(dt);});
    if (gOriginalWonky && gOriginalWonky.startSeconds !== null) {
        var original = gOriginalWonky;
        var clip = original.clips[Math.floor((timeSeconds-original.startSeconds)/original.intervalSeconds) % original.clips.length];
        if (clip !== original.clip) {
            original.sprite.startAnimation(clip);
            // Clip selection retains its clock. Resume rewinds completed
            // nonlooping clips so Attack and Crumble play on every cycle.
            original.sprite.resumeAnimation();
            original.clip = clip;
        }
    }
}

function DrawCharacterDemoOverlay() {
    if (!gWonkyAim && !gGreyGuyAim) return;
    if (gWonkyAim) gWonkyAim.drawOverlay(gPort);
    if (gGreyGuyAim) gGreyGuyAim.drawOverlay(gPort);
}


// Grey Guy calls his screen-left leg "front" in the authored Spriter rig.
// Keep the idle clip as input; the native constraint changes only this leg.
function SetUpGreyGuyIK(sprite, worldScale) {
    if (!sprite.enableAnimationPose('idle')) {
        throw new Error("Grey Guy IK: " + sprite.getAnimationRigError());
    }
    var foot = sprite.getAnimationBoneTransform('front_foot', pdg.animationSpace_World);
    var footArt = sprite.getAnimationBindingTransform('p_foot_idle_0', pdg.animationSpace_World);
    var lift = 32 * worldScale;

    // The idle foot's visible sole is 15 pixels below its image pivot, with its
    // center 4 pixels to the right. The ankle is above that sole: target the
    // ankle with the same lift, rather than putting the ankle on the rock.
    var groundY = footArt.y + 15 * worldScale;
    var contactX = footArt.x + 4 * worldScale;
    // CanvasMark stores 180 square frames vertically. Use only its first frame.
    var sheet = new pdg.Image(gRockFilename);
    var image = sheet.getSubsection(new pdg.Rect(0, 0, 64, 64));
    // Frame 0 has its top at pixel 3 and bottom at 61. Flatten the rock so its
    // visible bottom rests on the ground and its top supports the lifted sole.
    var width = 64 * worldScale;
    var height = lift * 64 / (61 - 3);
    var left = contactX - width / 2;
    var top = groundY - lift - height * 3 / 64;
    // Begin eight display pixels below the sole; wait for the camera's actual
    // zoom-complete event before raising the rock to the support position.
    var riseDistance = lift + 8 * worldScale;
    gGreyGuyIK = {
        sprite: sprite,
        image: image,
        rock: new pdg.Rect(left, top + riseDistance, left + width, top + height + riseDistance),
        restTop: top,
        restLeft: left,
        rockWidth: width,
        rockHeight: height,
        slideAmplitude: 10 * worldScale,
        slidePeriodSeconds: 6.0,
        lastUpdateSeconds: null,
        contact: new pdg.AnimationContactTarget(),
        riseDistance: riseDistance,
        riseStartSeconds: null,
        riseProgress: 0,
        restTargetY: foot.y - lift,
        idleFootY: foot.y,
        enabled: true,
        modifier: null,
        config: {
            root: 'front_thigh', middle: 'front_shin', tip: 'front_foot',
            // Omitted lengths follow this frame's authored joint offsets.
            targetX: foot.x, targetY: foot.y + 8 * worldScale,
            space: pdg.animationSpace_World,
            bendDirection: 1,
            stretch: pdg.animationIK_NoStretch,
            matchOrientation: true, targetRotation: foot.rotation
        }
    };
    gGreyGuyIK.contact.lockPlatform(gGreyGuyIK.config.targetX, gGreyGuyIK.config.targetY,
        1, GreyGuyRockFrame());
    console.log("Grey Guy: the rock rises after the zoom, then gently slides. Press I to compare IK with authored idle.");
}

function GreyGuyRockFrame() {
    return {x:gGreyGuyIK.rock.left,y:gGreyGuyIK.rock.top,rotation:0,scaleX:1,scaleY:1,alpha:1};
}

function UpdateGreyGuyRock(timeSeconds) {
    var demo = gGreyGuyIK;
    if (!demo || demo.riseStartSeconds === null) return;
    var progress = Math.max(0, Math.min(1, (timeSeconds - demo.riseStartSeconds) / kRockRiseSeconds));
    var dt = demo.lastUpdateSeconds === null ? 0 : Math.max(0, timeSeconds - demo.lastUpdateSeconds);
    demo.lastUpdateSeconds = timeSeconds;
    demo.riseProgress = progress;
    var drop = (1 - progress) * demo.riseDistance;
    demo.rock.top = demo.restTop + drop;
    demo.rock.bottom = demo.rock.top + demo.rockHeight;
    var slideSeconds = Math.max(0, timeSeconds - demo.riseStartSeconds - kRockRiseSeconds);
    var slide = demo.slideAmplitude * 0.5 * (1 - Math.cos(2 * Math.PI * slideSeconds / demo.slidePeriodSeconds));
    demo.rock.left = demo.restLeft + slide;
    demo.rock.right = demo.rock.left + demo.rockWidth;
    var contact = demo.contact.update(dt, true, true, 1, GreyGuyRockFrame());
    demo.config.targetX = contact.x;
    demo.config.targetY = contact.y;
    SyncGreyGuyIK();
}

function SyncGreyGuyIK() {
    var demo = gGreyGuyIK;
    // Leave the authored foot alone until the rising surface reaches its sole.
    if (demo.enabled && demo.config.targetY < demo.idleFootY) {
        if (demo.modifier === null) {
            demo.modifier = demo.sprite.addAnimationIK(demo.config);
        } else {
            demo.sprite.setAnimationIKTarget(demo.modifier,
                demo.config.targetX, demo.config.targetY, pdg.animationSpace_World);
        }
    } else if (demo.modifier !== null) {
        demo.sprite.removeAnimationModifier(demo.modifier);
        demo.modifier = null;
    }
}

function ToggleGreyGuyIK() {
    gGreyGuyIK.enabled = !gGreyGuyIK.enabled;
    SyncGreyGuyIK();
    console.log("Grey Guy IK " + (gGreyGuyIK.enabled ? "ON" : "OFF (authored idle)"));
}

function DrawGreyGuyRock() {
    if (!gGreyGuyIK) return;
    var demo = gGreyGuyIK;
    // Both scenery and target use owning-layer coordinates, including during
    // the introductory zoom. This rock is a visual support, not a physics body.
    gPort.drawImage(demo.image, gSpriteLayer.layerToPortRect(demo.rock), new pdg.Attributes());
}

function DrawGreyGuyIKOverlay() {
    if (!gGreyGuyIK) return;
    var demo = gGreyGuyIK;
    var target = gSpriteLayer.layerToPortPoint(new pdg.Point(demo.config.targetX, demo.config.targetY));
    var ink = new pdg.Attributes().lineColor("cyan").lineThickness(1);
    gPort.drawLine(new pdg.Point(target.x - 5, target.y), new pdg.Point(target.x + 5, target.y), ink);
    gPort.drawLine(new pdg.Point(target.x, target.y - 5), new pdg.Point(target.x, target.y + 5), ink);

}


///--------------------------------------------------------------------------------------
//  RunAnimation
///--------------------------------------------------------------------------------------

function RunAnimation() {
	console.log("in RunAnimation()");
	if (playMusic) {
		gMusic = new pdg.Sound(gMusicFilename);
		gMusic.setVolume(0.3);
		gMusic.start();
	}
	if (playSounds) {
		gClink1 = new pdg.Sound(gClink1Filename);
		gClink2 = new pdg.Sound(gClink2Filename);
	}
    if (pdg.visualTestSession) pdg.visualTestSession.onPause.push(function(paused) {
        [gMusic,gClink1,gClink2].forEach(function(sound) {
            if (sound) { if (paused) sound.pause(); else if (sound.isPaused()) sound.resume(); }
        });
    });
	pdg.run();
}


///--------------------------------------------------------------------------------------
//  CleanUp - This function is not really necessary, since the system will dispose
//  everything automatically when the program quits.
///--------------------------------------------------------------------------------------

function CleanUp() {
	
    // Stop GC monitoring and print final report
	try {
		if (gcMonitor) {
			console.log("\n=== Final GC Report ===");
			gcMonitor.stop();
			gcMonitor.printReport();
		}
	} catch (e) {
		console.log("No GC report available");
	}
    
    gGreyGuyIK = null;
    gWonkyAim = gGreyGuyAim = gOriginalWonky = null;
    pdg.cleanupLayer(gSpriteLayer);

    return true;
}

    
main();
