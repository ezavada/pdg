import pdg = require('../../types');

const point = new pdg.Point(10, 20);
declare const queryScene: pdg.Scene;
const queryHits: pdg.CollisionQueryHit[] = queryScene.overlapCircle(point, 20, {maxHits: 32});
const nearestHit: pdg.CollisionQueryHit | null = queryScene.nearestPoint(point, 100);
const firstHit: pdg.CollisionQueryHit | null = queryScene.raycast(point, new pdg.Point(30, 20));
const sweepHit: pdg.CollisionQueryHit | null = queryScene.sweepCircle(point, 1, new pdg.Vector(20, 0), {layerMask: 4});
const castHits: pdg.CollisionQueryHit[] = queryScene.raycast(point, new pdg.Point(30, 20), 8, {layerMask: 4});
const queryCollider: pdg.Collider = queryHits[0].collider;
// @ts-expect-error result buffers are internal
new pdg.CollisionQueryBuffer();
// @ts-expect-error query predicates must return boolean
queryScene.overlapPoint(point, {predicate: collider => 1});
point.x = 30;
// @ts-expect-error coordinates are numeric
point.y = '20';

declare const sprite: pdg.Sprite;
const concrete: pdg.Sprite = sprite.moveTo(10, 20, 0.5).repeat(2).pauseIt().resumeIt();
const lifecycleSprite: pdg.Sprite = sprite.moveBy(10, 0, 1).on('finished', event => {
    const name: string = event.scriptName;
    const iteration: number = event.iteration;
}).moveBy(0, 10, 1);
const spriteEventHandler: pdg.IEventHandler = sprite.on(2, event => true);
sprite.moveBy(10, 0, 1).on('finished', event => event.target.moveBy(0, 10, 1));
const helperSprite: pdg.Sprite = sprite.onMark(event => console.log(event.markName))
    .onYoyo(event => console.log(event.reverse))
    .onRepeat(event => console.log(event.iteration))
    .onFinished(event => event.target.moveBy(0, 10, 1))
    .onStarted(event => console.log(event.type))
    .onScriptFinished(event => console.log(event.scriptName))
    .onUntilFired(event => console.log(event.elapsedSeconds))
    .on("customSignal", event => console.log(event.type)).triggerEvent("customSignal");
concrete.findPart('hand');
const part = sprite.findPart('hand');
// @ts-expect-error lookup is nullable
const requiredPart: pdg.Part = part;
if (part) part.getLocation();

declare const client: pdg.NetClient;
if (client.connection !== false) {
    const connection: pdg.NetConnection = client.connection;
}
// @ts-expect-error the disconnected state must be narrowed
const connection: pdg.NetConnection = client.connection;

sprite.addAnimationDrawable(context => {
    const transform: pdg.AnimationTransform = context.getTransform();
    return null;
}, {bone: 'hand'});
// @ts-expect-error drawing callbacks are synchronous
sprite.addAnimationDrawable(async () => null, {bone: 0});
// @ts-expect-error options require a bone
sprite.addAnimationDrawable(() => null, {});
// @ts-expect-error a record is not a native drawing
sprite.addAnimationDrawable({x: 0, y: 0}, {bone: 0});
const evaluator: pdg.AnimationEvaluator = context => context.elapsedSeconds > 1;
sprite.until(evaluator);
// @ts-expect-error evaluators return booleans synchronously
const asyncEvaluator: pdg.AnimationEvaluator = async () => true;
new pdg.Sprite();
// @ts-expect-error unresolved options must not become an any overload
sprite.matchCutTo({});
// @ts-expect-error the nominal marker is not a runtime export
pdg.nativeIdentity;

const nativeSprite = new pdg.Sprite();
const attributes: pdg.Attributes = new pdg.AnimatedAttributes();
const animated: pdg.Animated = nativeSprite;
// @ts-expect-error unrelated native instances are not interchangeable
const notAttributes: pdg.Attributes = new pdg.Animated();
new pdg.Polygon(new pdg.Point(0, 0), new pdg.Point(10, 10));
// @ts-expect-error factory-only native objects cannot be constructed
new pdg.Part();
// @ts-expect-error managers are singletons
new pdg.TimerManager();

pdg.on(pdg.eventType_KeyPress, event => {
    const unicode: number = event.unicode;
    // @ts-expect-error keypress payloads do not have mouse coordinates
    event.mousePos;
    return true;
}).cancel();
pdg.on(pdg.eventType_PortResized, event => {
    event.port.getDrawingArea();
    // @ts-expect-error resize payloads do not have draw-frame numbers
    event.frameNum;
    return false;
});
// @ts-expect-error native event handlers must return boolean
pdg.onKeyPress(event => { event.unicode; });
// @ts-expect-error event handlers are synchronous
pdg.onTimer(async () => true);
pdg.tm.onTimeout(event => { const elapsed: number = event.msElapsed; }, 20).cancel();

const snapshot = sprite.getAnimationPose();
const parent: number | null = snapshot.bindings[0].parent;
const kind: number = snapshot.bindings[0].kind;
sprite.addAnimationModifier((pose, context) => {
    pose.rotateLocal('hand', context.deltaSeconds);
    const saved: pdg.AnimationPose = pose.copy();
});
// @ts-expect-error modifiers cannot return promises
sprite.addAnimationModifier(async () => {});
sprite.addAnimationIK({root: 'upper', middle: 'lower', tip: 'hand'});
sprite.setupAnimationPhysics({bodies: [{bone: 'arm', mass: 1, length: 10, radius: 2}]});
// @ts-expect-error shape dimensions must be explicit
sprite.setupAnimationPhysics({bodies: [{bone: 'arm', mass: 1}]});
const settings = sprite.getAnimationPhysicsDriveSettings('arm');
if (settings) settings.dampingRatio.toFixed(2);

declare const sourceCamera: pdg.Camera, targetCamera: pdg.Camera;
sourceCamera.matchCutTo(targetCamera, {matchSource: sprite, matchTarget: nativeSprite, mode: pdg.matchSource});
// @ts-expect-error match cuts need both source and destination subjects
sourceCamera.matchCutTo(targetCamera, {matchSource: sprite});

const search = pdg.fs.findFirst('*.png');
pdg.fs.findClose(search);
// @ts-expect-error search handles contain native state and cannot be fabricated
pdg.fs.findClose({found: true, nodeName: 'a.png', isDirectory: false});
new pdg.NetClient({noDatagram: true}).connect({host: 'localhost', port: 5000}, connection => {
    connection.onMessage((message, sender, transport) => { const protocol: 'tcp' | 'udp' = transport; });
});
const secureAddress: pdg.NetServerAddress = {
    host: 'localhost', tls: {caFile: 'ca.pem', rejectUnauthorized: true},
    serverCertificateHashes: [
        {algorithm: 'sha-256', value: new Uint8Array(32)},
        {algorithm: 'sha-256', value: new ArrayBuffer(32)}
    ]
};
// @ts-expect-error certificate hashes use SHA-256
const invalidHash: pdg.NetCertificateHash = {algorithm: 'sha-1', value: new Uint8Array(32)};
// @ts-expect-error certificate hashes require binary data
const invalidHashBytes: pdg.NetCertificateHash = {algorithm: 'sha-256', value: 'hex'};
// @ts-expect-error toBuffer was removed; convert the portable snapshot explicitly
new pdg.MemBlock().toBuffer();
// @ts-expect-error use getData() for the Uint8Array snapshot
new pdg.MemBlock().toUint8();
const portableBytes: Uint8Array = new pdg.MemBlock().getData();
portableBytes.subarray(0, 1);
// @ts-expect-error portable byte arrays do not expose Node Buffer methods
portableBytes.readUInt32LE(0);
// @ts-expect-error registration invokes a constructor, so arrows are invalid
pdg.registerSerializableClass(() => new pdg.ISerializable(() => 0, () => {}, () => {}, () => 1));
// @ts-expect-error top-level numeric network messages are rejected by the runtime
connection.send(42);
connection.send(new pdg.MemBlock().getData());
declare const candidate: unknown;
if (candidate instanceof pdg.Part) candidate.getTransform();
const partPrototype: pdg.Part = pdg.Part.prototype;

const bytePayload = new Uint8Array([0, 128, 255]);
new pdg.Serializer().serialize_mem(bytePayload);
new pdg.Serializer().sizeof_mem(bytePayload);
new pdg.Deserializer().setDataPtr(bytePayload);
const blockBytes: Uint8Array = new pdg.MemBlock().getData();
const resourceBytes: Uint8Array | false = pdg.res.getResource('bytes.bin');
// @ts-expect-error binary strings are no longer accepted
new pdg.Serializer().serialize_mem('bytes');
// @ts-expect-error binary strings are no longer accepted
new pdg.Deserializer().setDataPtr('bytes');

// Color alternatives come from METHOD_SIGNATURE, including mixed gradients.
const colored = new pdg.AnimatedAttributes();
for (const color of [new pdg.Color('red')]) colored.changeFillColor(color,1);
colored.changeFillColor('blue',1).changeLineColor(0xff0000ff,1).changeAmbientLight('white',1);
colored.fillColor('red').lineColor(0xff0000ff).ambientLight('white');
colored.fillGradient(point,'red',point,0xff0000ff);
colored.fillRadialGradient(point,0xff0000ff,10,'blue');
colored.changeFillGradient(point,'red',point,0xff0000ff,1);
colored.changeFillRadialGradient(point,0xff0000ff,10,'blue',1);
const colorSerializer = new pdg.Serializer();
colorSerializer.serialize_color('red');
colorSerializer.sizeof_color(0xff0000ff);
declare const colorPort: pdg.Port;
colorPort.clear().clear('blue').clear(0xff0000ff).clear(new pdg.Color('red'));
// @ts-expect-error null is not a color
colored.changeFillColor(null,1);
// @ts-expect-error boolean is not a gradient color
colored.fillGradient(point,'red',point,true);

// Named and collective recorders expose semantic subclass commands with fluent identity.
const appearanceScript: pdg.AnimationScript = pdg.Animated.defineScript('typed-appearance')
    .series().fillColor('red').changeFillOpacity(.25, 1, pdg.linearTween)
    .lineThickness(3).setFrame(0).endSeries().endScript();
const appearanceTroupe: pdg.Troupe = new pdg.Troupe().fillColor(new pdg.Color('blue')).fadeTo(.5, 1);
// @ts-expect-error recorder argument types match the native command contract
appearanceTroupe.changeFillOpacity('opaque', 1);
// @ts-expect-error clip playback is not a recorded semantic command
appearanceScript.startAnimation('walk');

// Ribbon configuration is shared by particles and both semantic recorders.
const trailOptions: pdg.ParticleTrailOptions = {lifetime:.4, width:6, endWidth:0,
    endOpacity:0, color:'orange', maxPoints:32, minDistance:2, sampleInterval:1/60};
const ribbonParticle: pdg.Particle = new pdg.Particle().setTrail(trailOptions).breakTrail();
const ribbonScript: pdg.AnimationScript = pdg.Animated.defineScript('typed-trail')
    .setTrail(trailOptions).clearTrail().endScript();
const ribbonTroupe: pdg.Troupe = new pdg.Troupe().setTrail({color:0xff9900ff});
const ribbonPoints: number = ribbonParticle.getTrailPointCount();
const ribbonEnabled: boolean = ribbonParticle.hasTrail();
// @ts-expect-error color is a Color, CSS string or packed RGBA number
ribbonParticle.setTrail({color:true});
// @ts-expect-error interval is numeric
ribbonScript.setTrail({sampleInterval:'fast'});
