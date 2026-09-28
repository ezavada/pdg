'use strict';
const assert = require('assert');
const fs = require('fs');
const os = require('os');
const path = require('path');
const cp = require('child_process');
const perf = require('../perf_tests/quick');
const {parse, validate, catalog} = require('./perf_runner');
const builds = require('./perf_build');
assert.throws(() => builds.assertRelease({configuration:'Debug'}), /require a Release/);
assert.throws(() => builds.assertRelease({}), /require a Release/);
assert.strictEqual(builds.assertRelease({configuration:'Release'}).configuration, 'Release');

// A warm-up spike must not bias the measured 50 FPS or the extrapolation.
assert.throws(() => perf.requireRelease({_buildConfiguration:'Debug'}), /require Release/);
perf.requireRelease({_buildConfiguration:'Release'});
const config = perf.options(['--quick']);
assert.strictEqual(perf.load(config, 950, 'polygon'), 3800);
assert.strictEqual(perf.load(config, 6400, 'bunnies'), 9600);
const previousUncapped = process.env.PDG_PERF_UNCAPPED;
perf.uncap();
assert.strictEqual(process.env.PDG_PERF_UNCAPPED, '1');
if (previousUncapped === undefined) delete process.env.PDG_PERF_UNCAPPED;
else process.env.PDG_PERF_UNCAPPED = previousUncapped;
const sampler = new perf.Sampler(config);
assert(!sampler.tick(0));
assert(!sampler.tick(999));
assert(!sampler.tick(1000));
for (let time = 1020; time <= 4000; time += 20) assert.strictEqual(sampler.tick(time), time === 4000);
const sample = sampler.result(150, 100, 120);
assert.strictEqual(sample.averageFPS, 50);
assert.strictEqual(sample.estimatedCapacity, 125);
assert.strictEqual(sample.score, 150); // weighted PDGMark score
assert.strictEqual(sample.totalFrames, 150);
assert.strictEqual(sample.frameTime.percentile99Ms, 20);
assert.strictEqual(sampler.result(150, 100, 120, 30).score, 300); // CanvasMark cutoff
// Clock quantization must preserve frame counts and aggregate elapsed time.
const quantized = new perf.Sampler({...config, warmup:0, seconds:.002});
[0, 0, 1, 1].forEach(time => assert.strictEqual(quantized.tick(time), false));
assert.strictEqual(quantized.tick(2), true);
const quantizedResult = quantized.result(100, 100, 100);
assert.strictEqual(quantizedResult.totalFrames, 4);
assert.strictEqual(quantizedResult.durationSeconds, .002);
assert.strictEqual(quantizedResult.averageFPS, 2000);
assert.throws(() => quantized.tick(1), /Backwards performance clock/);
assert.throws(() => quantized.tick(NaN), /Invalid performance clock/);
assert.throws(() => quantized.tick(Infinity), /Invalid performance clock/);
sampler.reset();
assert.throws(() => sampler.result(150, 100, 100), /Incomplete/);
global.window = globalThis;
global.document = {hidden:true};
try { assert.throws(() => sampler.tick(0), /tab became hidden/); }
finally { delete global.window; delete global.document; }
assert.throws(() => perf.options(['--sample-seconds','NaN']), /Invalid/);
assert.throws(() => perf.options(['--sample-seconds','0']), /Invalid/);
assert.throws(() => perf.options(['--load-factor']), /requires/);
assert.throws(() => parse(['--web','cpp-pdgmark']), /unavailable/);
assert.throws(() => parse(['--web','--node']), /one target/);
assert.strictEqual(parse([]).entries.length, 8);
assert.strictEqual(parse([]).quick, true);
assert.strictEqual(parse(['--quick']).quick, true);
assert.throws(() => perf.options(['--automated']), /Use --quick/);
assert.strictEqual(parse(['--web']).entries.length, 3);
const entry = catalog.find(e => e.id === 'bunnymark');
const report = {testName:'QuickBunnyMark', benchmarkId:'bunnymark', mode:'quick', synthetic:true, tests:{bunnies:sample}, compositeScore:150};
validate(entry, report);
assert.throws(() => validate(entry, {...report, mode:'automated'}), /Missing/);
assert.throws(() => validate(entry, {...report, tests:{}}), /Incomplete/);
assert.throws(() => validate(entry, {...report, compositeScore:149}), /Composite/);
assert.throws(() => validate(entry, {...report, tests:{bunnies:{...sample, averageFPS:NaN}}}), /Invalid/);

// A successful child exit without a fresh result must not reuse an old PASS.
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'pdg-perf-runner-'));
try {
    const fake = path.join(dir, 'fake.js');
    const probe = `if(process.argv[2]==="-e"){console.log('PDG_PERF_BUILD:{"configuration":"Release","hasGraphics":true}');process.exit(0); }\n`;
    fs.writeFileSync(fake, '#!' + process.execPath + '\n' + probe + 'process.exit(0);\n', {mode:0o755});
    fs.mkdirSync(path.join(dir, 'reports'));
    fs.writeFileSync(path.join(dir, 'reports/bunnymark.json'), JSON.stringify(report));
    if (process.platform !== 'win32') {
        const result = cp.spawnSync(process.execPath, [path.join(__dirname, 'perf_runner.js'), '--no-build','bunnymark'], {
            env:{...process.env, PDG_EXECUTABLE:fake, PDG_TEST_ARTIFACTS_DIR:dir,
                PDG_TEST_LOG_DIR:path.join(dir,'logs'), PDG_TEST_REPORT_DIR:path.join(dir,'reports'), PDG_TEST_TEMP_DIR:path.join(dir,'tmp')}, encoding:'utf8'});
        assert.strictEqual(result.status, 1, result.stderr);
        assert(!fs.existsSync(path.join(dir, 'reports/bunnymark.json')));
        const failed = JSON.parse(fs.readFileSync(path.join(dir, 'reports/summary.json')));
        assert.strictEqual(failed.status, 'failed');
        assert.strictEqual(failed.comparison.benchmarks[0].rows[0].current, null);
        assert.match(result.stdout, /Quick performance summary — native: FAILED/);
        assert.match(result.stdout, /bunnies\s+score\s+--\s+29,405\s+--/);

        // A fresh successful result appears both on the console and in saved comparisons.
        fs.writeFileSync(fake, '#!' + process.execPath + '\n' + probe +
            'require("fs").writeFileSync(process.argv[process.argv.indexOf("--output")+1], ' +
            JSON.stringify(JSON.stringify(report)) + ');\n');
        const passed = cp.spawnSync(process.execPath, [path.join(__dirname, 'perf_runner.js'), '--no-build','bunnymark'], {
            env:{...process.env, PDG_EXECUTABLE:fake, PDG_TEST_ARTIFACTS_DIR:dir,
                PDG_TEST_LOG_DIR:path.join(dir,'logs'), PDG_TEST_REPORT_DIR:path.join(dir,'reports'), PDG_TEST_TEMP_DIR:path.join(dir,'tmp')}, encoding:'utf8'});
        assert.strictEqual(passed.status, 0, passed.stderr);
        const saved = JSON.parse(fs.readFileSync(path.join(dir, 'reports/summary.json')));
        assert.strictEqual(saved.build.configuration, 'Release');
        assert.strictEqual(JSON.parse(fs.readFileSync(path.join(dir, 'reports/bunnymark.json'))).build.configuration, 'Release');
        assert.strictEqual(saved.comparison.benchmarks[0].rows[0].current, 150);
        assert.strictEqual(saved.comparison.benchmarks[0].rows[1].baseline, 29405);
        const closing = fs.readFileSync(saved.comparisonReport, 'utf8');
        assert(passed.stdout.includes(closing));
        assert.match(closing, /Quick performance summary — native: PASSED/);
        assert.match(closing, /bunnies\s+score\s+150\s+29,405\s+-99\.5%/);
        fs.writeFileSync(fake, '#!' + process.execPath + '\n' + probe.replace('Release', 'Debug'));
        const debug = cp.spawnSync(process.execPath, [path.join(__dirname, 'perf_runner.js'), '--no-build','bunnymark'], {
            env:{...process.env, PDG_EXECUTABLE:fake, PDG_TEST_ARTIFACTS_DIR:dir,
                PDG_TEST_LOG_DIR:path.join(dir,'logs'), PDG_TEST_REPORT_DIR:path.join(dir,'reports'), PDG_TEST_TEMP_DIR:path.join(dir,'tmp')}, encoding:'utf8'});
        assert.strictEqual(debug.status, 1);
        assert.match(debug.stderr, /require a Release/);
        assert.strictEqual(JSON.parse(fs.readFileSync(path.join(dir, 'reports/summary.json'))).benchmarks.length, 0);
    } else {
        console.log('SKIP: fake-executable stale/fresh report subprocess checks require POSIX shebang support');
    }
} finally { fs.rmSync(dir, {recursive:true, force:true}); }
console.log('PASS: perf sampling, score scaling, selection, incomplete and stale-result rejection');

// Exercise all CanvasMark transitions without a GPU. A late draw after quit
// must not restart a scene or overwrite the completed report.
const createCanvas = require('../perf_tests/canvasmark2013/quick');
const canvasDir = fs.mkdtempSync(path.join(os.tmpdir(), 'pdg-canvas-sampling-'));
const performanceDescriptor = Object.getOwnPropertyDescriptor(globalThis, 'performance');
try {
    let time = 0, completed = 0;
    Object.defineProperty(globalThis, 'performance', {configurable:true, value:{now:() => time}});
    function Vector(x,y) { this.x=x; this.y=y; this.rotate=() => this; }
    function Actor() {}
    const scenes = [{imagesLoaded:true}];
    for (let i = 0; i < 7; ++i) scenes.push({
        world:{viewsize:640}, _onInitScene() {},
        onInitScene() { this.enemies=[]; this.playerBullets=[]; this.k3d={objects:[]}; },
        generateAsteroid() { return new Actor(); },
        add3DObject() { this.k3d.objects.push({}); },
        onBeforeRenderScene(ramp) { assert.strictEqual(ramp, false); }, onRenderScene() {}
    });
    const context = {GameHandler:{game:{scenes}, width:640, height:640, FPSMS:60, frameCount:0,
        canvas:{getContext:() => ({})}}, Asteroids:{EnemyShip:Actor, Bullet:Actor}, Arena:{EnemyShip:Actor}, Vector, RAD:Math.PI/180};
    const output = path.join(canvasDir, 'result.json');
    const frame = createCanvas({quick:true, factor:1.5, warmup:0, seconds:.01, output}, context, () => { ++completed; });
    for (let i = 0; i < 50; ++i) { time += 10; frame(); }
    assert.strictEqual(completed, 1);
    const result = JSON.parse(fs.readFileSync(output));
    validate(catalog.find(entry => entry.id === 'canvasmark'), result);
    assert.strictEqual(result.tests.plasma.fixedLoad, scenes[6].plasmasize ** 2);
    assert.strictEqual(result.tests['asteroids-bitmaps'].fixedLoad, scenes[1].enemies.length);
    assert.strictEqual(result.tests['asteroids-effects'].fixedLoad, scenes[4].playerBullets.length);
    assert.strictEqual(result.tests['3d'].fixedLoad, scenes[7].k3d.objects.length);
} finally {
    if (performanceDescriptor) Object.defineProperty(globalThis, 'performance', performanceDescriptor);
    else delete globalThis.performance;
    fs.rmSync(canvasDir, {recursive:true, force:true});
}
console.log('PASS: CanvasMark fixed populations, seven-scene completion and late draw handling');

// Calibration observes actual preceding-frame populations, drops title time,
// and uses a median of per-item costs so a single slow frame cannot dominate.
const calibration = require('../perf_tests/canvasmark2013/calibration');
function Scene() { this.enemies = []; this.sceneStartTime = 1; }
const scene = new Scene();
const handler = {game:{scenes:[{},scene]}, benchmarkScores:[], frameInterval:0};
Scene.prototype._onBeforeRenderScene = function() {
    if (this.enemies.length === 120) { handler.benchmarkScores.push(500); this.sceneCompletedTime = 1; }
    return true;
};
const references = calibration.collect({Scene}, handler);
handler.frameInterval = 5000; // Title interval; not a workload sample.
assert(scene._onBeforeRenderScene());
for (let load = 10; load <= 120; load += 10) {
    scene.enemies.length = load;
    handler.frameInterval = load === 100 ? 1000 : load * .25;
    assert(scene._onBeforeRenderScene());
}
assert.strictEqual(references[0].load, 120);
assert.strictEqual(references[0].terminalSamples.length, 10);
assert.strictEqual(references[0].terminalSamples[0].load, 30);
assert.strictEqual(references[0].referenceFPS, 1000 / 30);
const equal = calibration.result({fixedLoad:180, averageFPS:1000 / 45}, references[0]);
assert.strictEqual(equal.score, 500);
assert(Math.abs(equal.equivalentReferenceLoad - 120) < 1e-10);
const plasma = {name:'plasma', load:1600, referenceFPS:20, score:400};
assert.strictEqual(calibration.result({fixedLoad:1600, averageFPS:20}, plasma).score, 400);
assert.strictEqual(calibration.result({fixedLoad:6400, averageFPS:20}, plasma).score, 900);
assert.strictEqual(calibration.result({fixedLoad:16, averageFPS:20}, plasma).score, 0);
console.log('PASS: CanvasMark measured ramp calibration and plasma grid-width scoring');

require('./bunnymark_reuse.test');
require('./pdgmark_reuse.test');
