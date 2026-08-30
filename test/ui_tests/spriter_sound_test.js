// Spriter rendering and sound playback integration test.

console.log("=== SPRITER AND SOUND UI TEST ===");

var waitForUser = process.argv.indexOf('--wait') >= 0;
var port = null;
var layer = null;
var sounds = [];
var finished = false;
var signals = {
    spriterFilesLoaded: 0,
    soundObjectsLoaded: 0,
    soundPlayCalls: 0,
    frames: 0
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
    sprite.setEntityScale(scale, scale);
    if (sprite.hasAnimation(animationName)) sprite.startAnimation(animationName);
    return sprite;
}

function loadSound(fileName, volume) {
    console.log("Loading sound: " + fileName);
    var sound = new pdg.Sound(fileName);
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

function finish() {
    if (finished) return;
    finished = true;
    sounds.forEach(function(sound) {
        try { sound.stop(); } catch (error) {}
    });
    if (signals.spriterFilesLoaded < 2 || signals.soundObjectsLoaded < 3 ||
        signals.soundPlayCalls < 3 || signals.frames === 0) {
        fail("Spriter/sound coverage was incomplete: " + JSON.stringify(signals));
        return;
    }
    console.log("PASS: rendered two Spriter examples and played three sounds");
    console.log(JSON.stringify(signals));
    if (layer) pdg.cleanupLayer(layer);
    if (port) pdg.gfx.closeGraphicsPort(port);
    pdg.quit();
}

function setup() {
    port = pdg.gfx.createWindowPort(new pdg.Rect(900, 650), "PDG Spriter + Sound Test");
    if (!port) fail("Could not create the graphics port");

    layer = pdg.createSpriteLayer(port);
    if (!layer) fail("Could not create the sprite layer");

    layer.onErasePort(function(evt) {
        var area = port.getDrawingArea();
        port.drawRect(area, new pdg.Attributes().fillColor(new pdg.Color(0.04, 0.08, 0.12, 1)));
        port.drawText("Spriter + Sound Integration", new pdg.Point(area.width() / 2, 36),
            new pdg.Attributes().textSize(24).textStyle(pdg.textStyle_Centered).fillColor("white"));
        port.drawText("Wonky Skeleton / Grey Guy / music + two effects",
            new pdg.Point(area.width() / 2, 66),
            new pdg.Attributes().textSize(15).textStyle(pdg.textStyle_Centered).fillColor("yellow"));
        return true;
    });

    // Keep a global PortDraw observer as well as the layer callbacks so the
    // cross-platform UI harness can verify that real frames were dispatched.
    pdg.on(pdg.eventType_PortDraw, function(evt) {
        if (evt.port === port) signals.frames++;
        return false;
    });

    loadSpriterSprite("data/spriter-samples/wonkyskeleton/wonkyskeleton.scml",
        new pdg.Point(270, 430), 2.2, "walk");
    loadSpriterSprite("data/spriter-samples/greyguy/player.scml",
        new pdg.Point(620, 440), 2.2, "Idle");

    var music = loadSound("data/Peppy_The-Firing-Squad_YMXB.mp3", 0.18);
    var clink1 = loadSound("data/clink1.mp3", 0.45);
    var clink2 = loadSound("data/clink2.mp3", 0.45);

    playSound(music, "background music");
    setTimeout(function() { playSound(clink1, "clink 1"); }, 1500);
    setTimeout(function() { playSound(clink2, "clink 2"); }, 3000);

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
