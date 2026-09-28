// Live snapshot + update demonstration. Run from the repository root:
//   ./pdg test/js/layer-serialization-demo.js
// Browser: test/ui.html?test=layer-serialization
// Add --ui-test (browser: &automated=1) for the finite regression check.
if (typeof pdg === 'undefined') global.pdg = require('pdg');

const automated = process.argv.includes('--ui-test');
const width = 1160, height = 900;
const port = pdg.gfx.createWindowPort(new pdg.Rect(width, height), 'PDG — live layer serialization');
pdg.gfx.setTargetFPS(60);
const P = (x, y) => new pdg.Point(x, y);
const R = (l, t, r, b) => new pdg.Rect(l, t, r, b);
const ink = (color) => new pdg.Attributes().fillColor(color);
const colors = { script: '#50d9bd', scheduled: '#ac9cfa', physics: '#ffbc66', ik: '#65b8ff' };
const source = pdg.createSpriteLayer(port), target = pdg.createSpriteLayer(port);
// Both layers use independent basic solver worlds. Target stepping is optional.
source.setUseChipmunkPhysics(false);
target.setUseChipmunkPhysics(false);
const sceneTop = 238;
source.setOrigin(P(24, sceneTop));
source.enableCollisions();
const sprites = [];
function sprite(x, y, drawing, name) {
    const s = source.createSprite();
    s.id = sprites.length + 1;
    s.setLocation(x, y);
    if (drawing) s.createPart(name || 'artwork').setDrawing(drawing);
    sprites.push(s);
    return s;
}
function disc(radius, color) {
    const drawing = pdg.createDrawing();
    drawing.addEllipse(P(0, 0), radius, radius, ink(color));
    drawing.addEllipse(P(-radius * .25, -radius * .3), radius * .2, radius * .2, ink('white'));
    return drawing;
}
function box(w, h, color) {
    const drawing = pdg.createDrawing();
    drawing.addRect(R(-w / 2, -h / 2, w / 2, h / 2), ink(color).roundedCorners(4));
    return drawing;
}
const scripted = sprite(260, 68, disc(15, colors.script));
const scheduled = sprite(100, 203, box(34, 34, colors.scheduled));
function scheduleTrip() {
    scheduled.moveTo(435, 203, 2).andThen().moveTo(100, 203, 2);
    scheduled.rotateBy(Math.PI * 2, 4, pdg.linearTween);
}
scheduleTrip();

const walls = [[264, 295, 458, 8], [264, 397, 458, 8], [35, 346, 8, 110], [493, 346, 8, 110]];
for (const [x, y, w, h] of walls) {
    const wall = sprite(x, y, box(w, h, '#374c66'));
    wall.setupPhysicsBody().setMode(pdg.physicsBody_Static);
    wall.setupCollider().setBox(R(-w / 2, -h / 2, w / 2, h / 2));
}
const ballDrawing = disc(12, colors.physics), balls = [];
for (let i = 0; i < 6; ++i) {
    const ball = sprite(82 + i * 67, 327 + (i % 2) * 35, ballDrawing);
    ball.setupPhysicsBody(1, 72).setVelocity(65 + i * 13, i % 2 ? -42 : 48)
        .setRestitution(1).setFriction(0);
    ball.setupCollider().setCircle(12);
    balls.push(ball);
}

const arm = sprite(172, 520, null);
const root = arm.createPart('shoulder'), middle = arm.createPart('elbow'), tip = arm.createPart('hand');
const link = pdg.createDrawing();
link.addRect(R(0, -7, 92, 7), ink(colors.ik).roundedCorners(6));
link.addEllipse(P(0, 0), 11, 11, ink('#d9efff'));
root.setDrawing(link);
middle.setParentPart(root).setLocation(92, 0).setDrawing(link);
tip.setParentPart(middle).setLocation(92, 0).setDrawing(disc(10, '#d9efff'));
const aim = sprite(305, 494, disc(5, '#ff7a97'));

let simSeconds = 0, lastClock = pdg.tm.getMilliseconds() / 1000;
let rate = 20, connected = true, paused = false, nextSend = 0;
let updateFlags = pdg.ser_Update, targetAnimation = false, targetCollisions = false;
const poseFlags = pdg.ser_Micro | pdg.ser_Sizes | pdg.ser_Animations;
const fields = [
    { label: 'Positions', flag: pdg.ser_Positions, help: 'Sprite position / rotation / frame. Micro packets round positions to whole pixels.' },
    { label: 'Z-order', flag: pdg.ser_ZOrder, help: 'Sprite draw order. Without this field, source and target ordering must already match.' },
    { label: 'Sizes', flag: pdg.ser_Sizes, help: 'Sprite and Layer logical size and transform scale.' },
    { label: 'Animations / Parts', flag: pdg.ser_Animations, help: 'Schedules, playback and sampled Part transforms/rates/schedules, including solved IK.' },
    { label: 'Motion', flag: pdg.ser_Motion, help: 'Programmed movement, spin and growth rates on Sprites and the Layer.' },
    { label: 'Forces', flag: pdg.ser_Forces, help: 'Either Forces or Physics sends the root body record, including pose, velocity, settings and loads.' },
    { label: 'Physics', flag: pdg.ser_Physics, help: 'Either Physics or Forces sends the root body record. Disabling Positions alone does not exclude body poses.' }
];
const buttons = [];
let hoverHelp = '';
function applyTargetProcessing() {
    if (targetAnimation) target.startAnimations(); else target.stopAnimations();
    if (targetCollisions) target.enableCollisions(); else target.disableCollisions();
}
function setProcessing(animation, collisions) {
    targetAnimation = animation; targetCollisions = collisions;
    applyTargetProcessing();
}
function setUpdateFlags(flags) { updateFlags = flags; nextSend = 0; }
function setRate(hz) { rate = hz; nextSend = 0; }
function toggleLink() { connected = !connected; nextSend = 0; }
function toggleSource() {
    paused = !paused;
    if (paused) { source.stopAnimations(); source.disableCollisions(); }
    else { source.startAnimations(); source.enableCollisions(); }
}
function addButton(x, y, w, label, active, action, help) {
    buttons.push({ x, y, w, h: 28, label, active, action, help });
}
addButton(24, 112, 104, () => 'M: Micro', () => updateFlags === pdg.ser_Micro,
    () => setUpdateFlags(pdg.ser_Micro), 'Positions, rotation, frame and Z-order only. Part IK poses are not sent.');
addButton(136, 112, 146, () => 'P: Pose + Parts', () => updateFlags === poseFlags,
    () => setUpdateFlags(poseFlags), 'Positions, Z-order, sizes and animation/Part state; no root body records.');
addButton(290, 112, 118, () => 'U: Standard', () => updateFlags === pdg.ser_Update,
    () => setUpdateFlags(pdg.ser_Update), 'All seven update fields (ser_Update). Artwork and structure remain in the initial snapshot.');
[5, 20, 50].forEach((hz, i) => addButton(432 + i * 60, 112, 52, () => hz + ' Hz', () => rate === hz,
    () => setRate(hz), 'Request ' + hz + ' packets/sec. Actual throughput is measured above.'));
addButton(632, 112, 238, () => 'A: Target animation ' + (targetAnimation ? 'ON' : 'OFF'), () => targetAnimation,
    () => setProcessing(!targetAnimation, targetCollisions), 'Advances received schedules, constant motion and basic physics bodies. No source scripts run here.');
addButton(878, 112, 258, () => 'C: Target collisions ' + (targetCollisions ? 'ON' : 'OFF'), () => targetCollisions,
    () => setProcessing(targetAnimation, !targetCollisions), 'Enables target contact detection/response independently. With animation OFF, existing overlaps can still resolve.');
fields.forEach((field, i) => addButton(24 + i * 160, 148, 152,
    () => (updateFlags & field.flag ? '[x] ' : '[ ] ') + field.label, () => !!(updateFlags & field.flag),
    () => setUpdateFlags(updateFlags ^ field.flag), field.help));
function buttonAt(p) {
    return p && buttons.find(b => p.x >= b.x && p.x < b.x + b.w && p.y >= b.y && p.y < b.y + b.h);
}
let initialBytes = 0, lastUpdateBytes = 0, totalBytes = 0, updateCount = 0;
let lastReceived = lastClock, maxError = 0, draws = 0, finished = false;
let mouse = null;
const deliveries = [];
const moved = { script: false, scheduled: false, physics: false, ik: false };
let receiverParts = [], receiverStates = [], frozen = null, freezePassed = false;
let controlStage = '', stageStarted = 0, stageState = null, controlsPassed = false;
const controlChecks = {};
function check(condition, message) {
    if (!condition) throw new Error('Serialization demo: ' + message);
}
function state(layer) {
    return sprites.map((_, i) => {
        const s = layer.getNthSprite(i), p = s.getLocation();
        const parts = s.getPartNames().map(name => {
            const part = s.findPart(name), loc = part.getLocation();
            return [loc.x, loc.y, part.getRotation()];
        });
        return [p.x, p.y, s.getRotation(), ...parts.flat()];
    });
}
function receive(initial) {
    // A fresh stream has its own object/reference table. Complete mode embeds
    // artwork in the initial packet; update packets contain sampled state only.
    source.setSerializationFlags(initial ? pdg.ser_Full : updateFlags);
    const writer = new pdg.Serializer();
    writer.setResourceMode(pdg.serialization_Complete);
    source.serialize(writer);
    const packet = writer.getDataPtr(), bytes = packet.getDataSize();
    const reader = new pdg.Deserializer();
    reader.setDataPtr(packet);
    target.deserialize(reader);
    target.setOrigin(P(608, sceneTop));
    // Layer records also contain processing flags. Always reapply the user's
    // receiver choices after loading, including after an initial snapshot.
    applyTargetProcessing();
    const now = pdg.tm.getMilliseconds() / 1000;
    totalBytes += bytes;
    deliveries.push({ time: now, bytes, initial });
    lastReceived = now;
    if (initial) {
        initialBytes = bytes;
        receiverParts = sprites.map((_, i) => target.getNthSprite(i).getPartNames()
            .map(name => target.getNthSprite(i).findPart(name)));
    } else {
        lastUpdateBytes = bytes;
        ++updateCount;
        for (let i = 0; i < sprites.length; ++i) {
            const s = target.getNthSprite(i);
            s.getPartNames().forEach((name, n) => {
                if (s.findPart(name) !== receiverParts[i][n]) throw new Error('Update replaced a Part');
            });
        }
    }
    const actual = state(target), expected = state(source);
    if (initial || updateFlags === pdg.ser_Update) {
        actual.forEach((row, i) => row.forEach((v, j) => { maxError = Math.max(maxError, Math.abs(v - expected[i][j])); }));
    }
    receiverStates = actual;
}
receive(true);

source.onPreAnimateLayer(() => {
    const clock = pdg.tm.getMilliseconds() / 1000, dt = Math.max(0, clock - lastClock);
    lastClock = clock;
    if (paused) return false;
    simSeconds += dt;
    scripted.setLocation(264 + 165 * Math.sin(simSeconds * 1.3), 70 + 20 * Math.sin(simSeconds * 2.6));
    scripted.setRotation(simSeconds);
    if (!scheduled.hasScheduledAnimations()) scheduleTrip();
    const destination = mouse || P(280 + 55 * Math.cos(simSeconds * 1.1), 506 + 35 * Math.sin(simSeconds * 1.7));
    aim.setLocation(destination);
    root.solveIK(middle, tip, destination, pdg.partSpace_World);
    moved.script ||= Math.abs(scripted.getLocation().x - 260) > 20;
    moved.scheduled ||= scheduled.getLocation().x > 200;
    moved.physics ||= Math.abs(balls[0].getLocation().x - 82) > 15;
    moved.ik ||= Math.abs(middle.getRotation()) > .1;
    return false;
});
source.onPostAnimateLayer(() => {
    // The finite check drops the link for 0.6 seconds and verifies the target
    // stays exactly at the last received pose while the source keeps running.
    if (automated && !controlStage && simSeconds >= 1.5 && simSeconds < 2.1) {
        if (!frozen) frozen = JSON.stringify(state(target));
        connected = false;
        if (JSON.stringify(state(target)) !== frozen) throw new Error('Disconnected target advanced');
    } else if (automated && !controlStage && frozen) { connected = true; freezePassed = true; }
    if (automated && simSeconds >= 5) exerciseControls();
    // Transmission cadence is independent of whether source simulation is paused.
    const packetClock = pdg.tm.getMilliseconds() / 1000;
    if (connected && packetClock >= nextSend) {
        receive(false);
        nextSend += (Math.floor((packetClock - nextSend) * rate) + 1) / rate;
    }
    return false;
});

function targetBall(index) { return target.getNthSprite(sprites.indexOf(balls[index])); }
function exerciseControls() {
    const now = simSeconds;
    if (!controlStage) {
        connected = false;
        // Exercise every selectable flag combination through real streams.
        // A flag controls future packets; it does not erase previous target state.
        for (let mask = 0; mask < 128; ++mask) { setUpdateFlags(mask); receive(false); }
        controlChecks.flagCombinations = 128;
        setUpdateFlags(pdg.ser_Update); receive(false);
        const fullBytes = lastUpdateBytes;
        const oldAngle = target.getNthSprite(sprites.indexOf(arm)).findPart('elbow').getRotation();
        middle.setRotation(oldAngle + .2);
        setUpdateFlags(pdg.ser_Micro); receive(false);
        check(target.getNthSprite(sprites.indexOf(arm)).findPart('elbow').getRotation() === oldAngle,
            'Micro unexpectedly changed a Part');
        check(lastUpdateBytes < fullBytes, 'Micro did not reduce packet size');
        controlChecks.microBytes = lastUpdateBytes; controlChecks.standardBytes = fullBytes;
        setUpdateFlags(poseFlags); receive(false);
        check(Math.abs(target.getNthSprite(sprites.indexOf(arm)).findPart('elbow').getRotation() - middle.getRotation()) < .001,
            'Pose + Parts did not restore the IK angle');
        controlChecks.partSelection = true;
        setUpdateFlags(pdg.ser_Update);
        setProcessing(true, false); receive(true); receive(false);
        stageState = state(target); controlStage = 'animate'; stageStarted = now;
    } else if (controlStage === 'animate' && now - stageStarted >= .35) {
        const current = state(target), ball = sprites.indexOf(balls[0]);
        check(current[1][0] !== stageState[1][0], 'Target schedule did not advance with animation ON');
        check(current[ball][0] !== stageState[ball][0], 'Target body did not advance with animation ON');
        check(JSON.stringify(current[0]) === JSON.stringify(stageState[0]), 'Target ran the source script');
        controlChecks.animation = true;
        setProcessing(false, false); receive(false);
        stageState = JSON.stringify(state(target)); controlStage = 'stopped'; stageStarted = now;
    } else if (controlStage === 'stopped' && now - stageStarted >= .2) {
        check(JSON.stringify(state(target)) === stageState, 'Target did not stop after animation OFF and another update');
        controlChecks.stopAfterUpdate = true;
        targetBall(0).physics.teleport(P(250, 346), 0);
        targetBall(1).physics.teleport(P(260, 346), 0);
        stageState = JSON.stringify(state(target)); controlStage = 'noContacts'; stageStarted = now;
    } else if (controlStage === 'noContacts' && now - stageStarted >= .1) {
        check(JSON.stringify(state(target)) === stageState, 'Target resolved contact with collisions OFF');
        setProcessing(false, true); controlStage = 'contacts'; stageStarted = now;
    } else if (controlStage === 'contacts' && now - stageStarted >= .15) {
        const a = targetBall(0).getLocation(), b = targetBall(1).getLocation();
        check(Math.hypot(a.x - b.x, a.y - b.y) > 15, 'Target did not resolve contact with collisions ON');
        controlChecks.collisions = true;
        setProcessing(true, true); receive(false);
        controlStage = 'both'; stageStarted = now; stageState = state(target);
    } else if (controlStage === 'both' && now - stageStarted >= .15) {
        check(JSON.stringify(state(target)) !== JSON.stringify(stageState), 'Target processing did not survive an update');
        controlChecks.bothAfterUpdate = true;
        setProcessing(false, false); receive(true);
        connected = true; controlsPassed = true; controlStage = 'done'; stageStarted = now;
    }
}
// Compare world-space origins in layer coordinates, excluding the panels' screen offsets.
// Divergence is expected with omitted fields, lower update rates or local simulation.
function positionGap() {
    let gap = 0;
    for (let i = 0; i < sprites.length; ++i) {
        const a = sprites[i], b = target.getNthSprite(i);
        const pa = a.getLocation(), pb = b.getLocation();
        gap = Math.max(gap, Math.hypot(pa.x - pb.x, pa.y - pb.y));
        a.getPartNames().forEach(name => {
            const ta = a.findPart(name).getTransform(pdg.partSpace_World);
            const tb = b.findPart(name).getTransform(pdg.partSpace_World);
            gap = Math.max(gap, Math.hypot(ta.tx - tb.tx, ta.ty - tb.ty));
        });
    }
    return gap;
}

function text(value, x, y, size = 14, color = '#c5d3e5') {
    port.drawText(value, P(x, y), ink(color).textSize(size));
}
function statistics(now) {
    while (deliveries.length && deliveries[0].time <= now - 1) deliveries.shift();
    return { bytes: deliveries.reduce((n, p) => n + p.bytes, 0),
        updates: deliveries.filter(p => !p.initial).length };
}
source.onErasePort(() => {
    port.drawRect(R(0, 0, width, height), ink('#101b2b'));
    text('Live source. Configurable target.', 24, 37, 27, '#f3f7ff');
    text('Choose update fields and target processing. Source scripts and IK goals run only on the left.', 24, 64);
    for (const x of [24, 608]) {
        port.drawRect(R(x, 200, x + 528, 812), ink('#1a2a40').roundedCorners(12));
        text(x === 24 ? 'SOURCE  /  live simulation' : 'TARGET  /  received + optional local processing', x + 16, 228, 17,
            x === 24 ? colors.script : colors.ik);
        const labels = ['SCRIPTED  /  orbit from JavaScript', 'PROGRAMMED  /  move + rotate, repeat',
            'PHYSICS  /  collisions, basic solver', 'IK  /  two linked Parts'];
        labels.forEach((label, i) => text(label, x + 16, [261, 396, 515, 666][i], 13));
        for (const y of [355, 490, 644]) port.drawLine(P(x + 16, y), P(x + 512, y),
            new pdg.Attributes().lineColor('#31445e'));
    }
    return true;
});
// Keep bodies that leave the bin with collisions OFF inside their own panel.
source.onPreDrawLayer(() => { port.setClipRect(R(24, 238, 552, 812)); return false; });
source.onPostDrawLayer(() => { port.setClipRect(port.getDrawingArea()); return false; });
target.onPreDrawLayer(() => { port.setClipRect(R(608, 238, 1136, 812)); return false; });
target.onPostDrawLayer(() => {
    port.setClipRect(port.getDrawingArea());
    ++draws;
    const now = pdg.tm.getMilliseconds() / 1000, stats = statistics(now);
    text(`${stats.bytes.toLocaleString()} bytes/sec`, 24, 101, 22, '#ffffff');
    text(`${stats.updates} updates/sec  |  requested ${rate} Hz  |  ${connected ? 'LINK ON' : 'LINK OFF'}${paused ? '  |  SOURCE PAUSED' : ''}`,
        312, 99, 16, connected ? colors.script : '#ff7a97');
    buttons.forEach(button => {
        port.drawRect(R(button.x, button.y, button.x + button.w, button.y + button.h),
            ink(button.active() ? '#305c77' : '#26374b').roundedCorners(5));
        text(button.label(), button.x + 8, button.y + 19, 13, button.active() ? '#ffffff' : '#aabdd4');
    });
    text(hoverHelp || 'Fields apply to future updates. Animation steps motion and basic physics; collisions control contact response.',
        24, 193, 12, '#b8cbdf');
    text(`Initial: ${initialBytes.toLocaleString()} B   Last update: ${lastUpdateBytes.toLocaleString()} B   Total: ${totalBytes.toLocaleString()} B`,
        24, 839, 14);
    text(`Received ${updateCount} updates   Age: ${Math.max(0, now - lastReceived).toFixed(2)} s   Position gap now: ${positionGap().toFixed(2)} px`,
        608, 839, 13);
    text('L: link    Space: pause ' + (pdg.visualTestSession ? 'demo' : 'source') +
        '    R: new snapshot    Esc: close    |    Click fields to toggle; hover for details.', 24, 867, 14);
    text('Move the mouse over the source IK arm to aim. Omitted fields keep their last received values.', 24, 888, 12, colors.ik);
    if (automated && controlsPassed && simSeconds - stageStarted >= 1.1 && !finished) {
        finished = true;
        const passed = Object.values(moved).every(Boolean) && freezePassed && updateCount > 40 &&
            maxError < .001 && controlsPassed && lastUpdateBytes < initialBytes && draws > 10 &&
            stats.bytes > 0 && stats.updates > 0 && JSON.stringify(receiverStates) === JSON.stringify(state(target));
        global.pdgLayerSerializationTest = { passed, moved, freezePassed, controlChecks, updateCount, initialBytes,
            lastUpdateBytes, totalBytes, bytesPerSecond: stats.bytes, updatesPerSecond: stats.updates, maxError, draws };
        console.log('LAYER SERIALIZATION ' + (passed ? 'PASS ' : 'FAIL ') + JSON.stringify(global.pdgLayerSerializationTest));
        setTimeout(() => process.exit(passed ? 0 : 1), 0);
    }
    return false;
});
// Also lets the browser UI runner count actual rendered frames.
pdg.on(pdg.eventType_PortDraw, () => false);
pdg.onMouseMove(evt => {
    const p = evt.mousePos;
    const button = buttonAt(p);
    hoverHelp = button ? button.help : '';
    mouse = p && p.x >= 24 && p.x < 552 && p.y > 665 && p.y < 812 ? P(p.x - 24, p.y - sceneTop) : null;
    return false;
});
pdg.onMouseDown(evt => {
    const button = buttonAt(evt.mousePos);
    if (!button) return false;
    button.action();
    return true;
});
pdg.onKeyPress(evt => {
    const key = String.fromCharCode(evt.unicode).toLowerCase();
    if ('123'.includes(key) && key) setRate([5, 20, 50][Number(key) - 1]);
    else if (key === 'm') setUpdateFlags(pdg.ser_Micro);
    else if (key === 'p') setUpdateFlags(poseFlags);
    else if (key === 'u') setUpdateFlags(pdg.ser_Update);
    else if (key === 'a') setProcessing(!targetAnimation, targetCollisions);
    else if (key === 'c') setProcessing(targetAnimation, !targetCollisions);
    else if (key === 'l') toggleLink();
    else if (key === ' ') toggleSource();
    else if (key === 'r') { receive(true); nextSend = 0; }
    else if (evt.unicode === 27) pdg.quit();
    return false;
});
pdg.run();
