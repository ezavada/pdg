// Spriter rendering and sound playback integration test.

console.log("=== SPRITER AND SOUND UI TEST ===");

var waitForUser = !!pdg.visualTestSession || process.argv.indexOf('--wait') >= 0;
var port = null;
var layer = null;
var sounds = [];
var balls = [];
var camera = null;
var sceneBounds = null;
var soundUnavailable = pdg.hasSound === false;
var finished = false;
var signals = {
    spriterFilesLoaded: 0,
    soundObjectsLoaded: 0,
    soundPlayCalls: 0,
    ballSpritesCreated: 0,
    colliderSizesChecked: 0,
    ballCollisions: 0,
    wallCollisions: 0,
    collisionSoundPlayCalls: 0,
    clink1PlayCalls: 0,
    clink2PlayCalls: 0,
    frames: 0,
    layerFitsViewport: false
};
global.pdgSpriterSoundTest = signals;

function fail(message) {
    console.error("ERROR: " + message);
    process.exit(1);
}

function loadSpriterSprite(fileName, location, scale, animationName) {
    console.log("Loading Spriter example: " + fileName);
    var sprite = layer.createSpriteFromSpriterFile(fileName);
    if (!sprite) fail("Could not load Spriter example " + fileName);
    signals.spriterFilesLoaded++;
    sprite.setLocation(location);
    sprite.setScale(scale, scale);
    sprite.startAnimation(animationName);
    return sprite;
}

function loadSound(fileName, volume) {
    if (soundUnavailable) return null;
    console.log("Loading sound: " + fileName);
    var sound;
    try {
        sound = new pdg.Sound(fileName);
    } catch (error) {
        if (process.platform === 'win32' && require('fs').existsSync(fileName) &&
            /could not create Sound from file/.test(String(error))) {
            soundUnavailable = true;
            console.log("SKIP: Windows DirectShow could not load bundled audio: " + error.message);
            return null;
        }
        throw error;
    }
    if (!sound) fail("Could not load sound " + fileName);
    sound.setVolume(volume);
    sounds.push(sound);
    signals.soundObjectsLoaded++;
    return sound;
}

function playSound(sound, label) {
    console.log("Playing sound: " + label);
    sound.start();
    signals.soundPlayCalls++;
}

function createBouncingSymbols(clinks) {
    var image = new pdg.Image("data/yinyang.png");
    var radius = image.getWidth() / 2;
    var scale = 160 / image.getWidth();
    var thickness = 40;
    var bounds = layer.getWorldBounds();
    [
        new pdg.Rect(bounds.left - thickness, bounds.top - thickness, bounds.left, bounds.bottom + thickness),
        new pdg.Rect(bounds.right, bounds.top - thickness, bounds.right + thickness, bounds.bottom + thickness),
        new pdg.Rect(bounds.left, bounds.top - thickness, bounds.right, bounds.top),
        new pdg.Rect(bounds.left, bounds.bottom, bounds.right, bounds.bottom + thickness)
    ].forEach(function(rect) {
        var wall = layer.createSprite();
        wall.setupPhysicsBody().setMode(pdg.physicsBody_Static);
        wall.setupCollider().setBox(rect).setCategory(2).setRestitution(1).setFriction(0);
    });

    function onContact(contact) {
        if (contact.phase !== pdg.collision_Begin) return;
        var ballContact = contact.other.getCategory() === 1;
        // Both balls receive a contact. Play once for each colliding pair.
        if (ballContact && contact.collider.getId() > contact.other.getId()) return;
        if (ballContact) signals.ballCollisions++; else signals.wallCollisions++;
        if (soundUnavailable) return;
        var count = signals.ballCollisions + signals.wallCollisions;
        var index = (count - 1) % clinks.length;
        var point = layer.layerToPortPoint(contact.point);
        clinks[index].play(0.45, point.x - port.getDrawingArea().width() / 2);
        signals.soundPlayCalls++;
        signals.collisionSoundPlayCalls++;
        if (index === 0) signals.clink1PlayCalls++; else signals.clink2PlayCalls++;
    }

    // Opposing pairs ensure real collisions during the finite smoke run.
    for (var row = 0; row < 4; ++row) {
        for (var side = 0; side < 2; ++side) {
            var sprite = layer.createSprite();
            sprite.addFramesImage(image);
            // Frame artwork and explicit colliders share the Sprite scale.
            // setSize alone changes logical bounds, not image-frame drawing.
            sprite.setSize(image.getWidth(), image.getHeight());
            sprite.setScale(scale, scale);
            sprite.setLocation(side ? 920 : 80, -600 + row * 300);
            sprite.setupCollider().setCircle(radius).setCategory(1).setRestitution(1)
                .setFriction(0).setContactHandler(onContact);
            var frame = sprite.getFrameRotatedBounds();
            var center = frame.centerPoint();
            var visibleRadius = frame.width() / 2;
            [[1, 0], [-1, 0], [0, 1], [0, -1]].forEach(function(direction) {
                var inside = new pdg.Point(center.x + direction[0] * (visibleRadius - 0.5),
                    center.y + direction[1] * (visibleRadius - 0.5));
                var outside = new pdg.Point(center.x + direction[0] * (visibleRadius + 0.5),
                    center.y + direction[1] * (visibleRadius + 0.5));
                if (!sprite.collider.contains(inside) || sprite.collider.contains(outside))
                    fail("Yin/yang collider does not match its image-frame bounds");
            });
            signals.colliderSizesChecked++;
            sprite.setupPhysicsBody().setRestitution(1).setFriction(0)
                .setVelocity((side ? -1 : 1) * (180 + row * 30), row % 2 ? 35 : -35)
                .setAngularVelocity(side ? -0.8 : 0.8);
            balls.push(sprite);
            signals.ballSpritesCreated++;
        }
    }
}

function finish() {
    if (finished) return;
    finished = true;
    sounds.forEach(function(sound) {
        try { sound.stop(); } catch (error) {}
    });
    if (signals.spriterFilesLoaded < 2 || signals.frames === 0 ||
        signals.ballSpritesCreated !== 8 || signals.colliderSizesChecked !== 8 || signals.ballCollisions < 2 ||
        (!soundUnavailable && (signals.soundObjectsLoaded < 3 ||
            signals.collisionSoundPlayCalls < 2 || signals.clink1PlayCalls === 0 || signals.clink2PlayCalls === 0))) {
        fail("Spriter/sound coverage was incomplete: " + JSON.stringify(signals));
        return;
    }
    var visibleBounds = layer.layerToPortQuad(new pdg.Quad(layer.getWorldBounds())).getBounds();
    var viewport = camera.getViewport();
    signals.layerFitsViewport = visibleBounds.left >= viewport.left - 0.5 &&
        visibleBounds.top >= viewport.top - 0.5 && visibleBounds.right <= viewport.right + 0.5 &&
        visibleBounds.bottom <= viewport.bottom + 0.5;
    if (!signals.layerFitsViewport) {
        fail("Sprite layer exceeds the visible scene: " + JSON.stringify(visibleBounds));
        return;
    }
    console.log(soundUnavailable ? "PASS: rendered two Spriter examples and colliding yin/yang symbols (audio unavailable)" :
        "PASS: rendered Spriter examples and bouncing yin/yang symbols with collision sounds");
    console.log(JSON.stringify(signals));
    if (layer) pdg.cleanupLayer(layer);
    if (port) pdg.gfx.closeGraphicsPort(port);
    pdg.quit();
}

function setup() {
    if (soundUnavailable) console.log("SKIP: sound is not available in this build");
    port = pdg.gfx.createWindowPort(new pdg.Rect(900, 650), "PDG Spriter + Sound Test");
    if (!port) fail("Could not create the graphics port");

    layer = pdg.createSpriteLayer(port);
    if (!layer) fail("Could not create the sprite layer");
    if (typeof layer.setUseChipmunkPhysics === 'function') layer.setUseChipmunkPhysics(true);
    if (typeof layer.setGravity === 'function') layer.setGravity(0);
    if (typeof layer.setDamping === 'function') layer.setDamping(1);
    layer.enableCollisions();

    camera = new pdg.Camera();
    layer.setCamera(camera);
    // Both samples are drawn at 2.2x around foot-level origins. The authored
    // scene includes the artwork above those origins and room for moving limbs.
    // Original Wonky playback has optional tracks and a changing hierarchy, so
    // keep it on the classic player rather than enabling the pose controller.
    sceneBounds = new pdg.Rect(-100, -800, 1100, 650);
    layer.setWorldBounds(sceneBounds);

    layer.onErasePort(function(evt) {
        var area = port.getDrawingArea();
        sceneBounds = layer.getWorldBounds();
        var viewport = new pdg.Rect(area.left + 24, area.top + 90,
            area.right - 24, area.bottom - 48);
        camera.setViewport(viewport).setLocation(sceneBounds.centerPoint());
        camera.setZoom(Math.min(1, viewport.width() / sceneBounds.width(),
            viewport.height() / sceneBounds.height()));
        port.drawRect(area, new pdg.Attributes().fillColor(new pdg.Color(0.04, 0.08, 0.12, 1)));
        port.drawText("Spriter + Sound Integration", new pdg.Point(area.width() / 2, 36),
            new pdg.Attributes().textSize(24).textStyle(pdg.textStyle_Centered).fillColor("white"));
        port.drawText("Wonky / Grey Guy / bouncing yin/yang collisions trigger clinks",
            new pdg.Point(area.width() / 2, 66),
            new pdg.Attributes().textSize(15).textStyle(pdg.textStyle_Centered).fillColor("yellow"));
        port.drawQuad(layer.layerToPortQuad(new pdg.Quad(sceneBounds)),
            new pdg.Attributes().lineColor("slategray").lineThickness(1));
        return true;
    });

    // Keep a global PortDraw observer as well as the layer callbacks so the
    // cross-platform UI harness can verify that real frames were dispatched.
    pdg.on(pdg.eventType_PortDraw, function(evt) {
        if (evt.port === port) signals.frames++;
        return false;
    });

    loadSpriterSprite("data/spriter-samples/wonkyskeleton/wonkyskeleton.scml",
        new pdg.Point(270, 430), 2.2, "Walk");
    loadSpriterSprite("data/spriter-samples/greyguy/player.scml",
        new pdg.Point(620, 440), 2.2, "idle");

    var music = loadSound("data/Peppy_The-Firing-Squad_YMXB.mp3", 0.18);
    var clink1 = loadSound("data/clink1.mp3", 0.45);
    var clink2 = loadSound("data/clink2.mp3", 0.45);

    createBouncingSymbols([clink1, clink2]);

    if (!soundUnavailable) {
        if (pdg.visualTestSession) {
            pdg.visualTestSession.onPause.push(function(paused) {
                [music, clink1, clink2].forEach(function(sound) {
                    if (paused) sound.pause(); else if (sound.isPaused()) sound.resume();
                });
            });
        }
        playSound(music, "background music");
    }

    if (!waitForUser) {
        setTimeout(finish, 7000);
    } else {
        console.log("Manual mode: press SPACE to finish after the sounds play, or ESC to quit.");
    }

    pdg.on(pdg.eventType_KeyPress, function(evt) {
        if (evt.unicode === pdg.key_Escape) {
            finish();
            return true;
        }
        if (waitForUser && evt.unicode === 32) {
            finish();
            return true;
        }
        return false;
    });
}

setup();
pdg.run();
