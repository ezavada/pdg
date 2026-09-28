// Run after rebuilding Node: tools/node test/perf_tests/animation_pipeline.js [iterations]
// Measures API costs on the small fixed-hierarchy fixture, not frame budgets.
'use strict';
var pdg = require('pdg');
var path = require('path');
var quick = require('./quick');
quick.requireRelease(pdg);
var quickOptions = quick.options(process.argv);
var iterations = quickOptions.quick ? 2000 : Number(process.argv[2] || 2000);
if (!Number.isSafeInteger(iterations) || iterations < 1 || iterations > 1000000)
    throw new RangeError('Iterations must be an integer between 1 and 1000000');
var layer = pdg.createSpriteLayer();
layer.setUseChipmunkPhysics(false);
var results = [], sink = 0;
function measure(name, count, operation) {
    for (var i = 0; i < Math.min(count, 100); ++i) operation(i);
    var start = process.hrtime();
    for (var i = 0; i < count; ++i) operation(i);
    var elapsed = process.hrtime(start);
    var seconds = elapsed[0] + elapsed[1] / 1e9;
    results.push({name: name, iterations: count, totalSeconds: seconds,
                  secondsPerOperation: seconds / count});
}
try {
    var sprite = layer.createSpriteFromSpriterFile(
        path.resolve(__dirname, '../data/spriter-regression/arm.scml'));
    sprite.pauseAnimation();
    if (!sprite.enableAnimationPose('reference')) throw new Error(sprite.getAnimationRigError());
    measure('owned final pose snapshot', iterations, function() {
        sink += sprite.getAnimationPose().bones[0].rotation;
    });
    measure('silent authored sample (fresh evaluator)', iterations, function(i) {
        sink += sprite.sampleAnimationPose('reach', (i % 100) / 100).bones[0].rotation;
    });
    measure('atomic seek and publication', iterations, function(i) {
        sprite.seekAnimation('reach', (i % 100) / 100);
    });
    var callbacks = 0;
    sprite.addAnimationModifier(function(view) {
        ++callbacks;
        view.rotateLocal('shoulder', 0.05);
    }, pdg.animationStage_PreConstraint);
    measure('seek and publication with script modifier', iterations, function(i) {
        sprite.seekAnimation('reach', (i % 100) / 100);
    });
    if (callbacks < iterations) throw new Error('Benchmark did not evaluate modifiers');
    sprite.addAnimationIK({root: 'shoulder', middle: 'forearm', tip: 'hand',
        rootLength: 10, middleLength: 5, targetX: 10, targetY: 10});
    measure('seek and publication with modifier and IK', iterations, function(i) {
        sprite.seekAnimation('reach', (i % 100) / 100);
    });
    sprite.clearAnimationModifiers();
    measure('independent transition selection/interruption', iterations, function(i) {
        sprite.transitionToAnimation(i % 2 ? 'reach' : 'reference', 0.25, 0.2);
    });
    if (!Number.isFinite(sink)) throw new Error('Invalid benchmark pose');
} finally {
    pdg.cleanupLayer(layer);
}
var report = {fixture: 'arm.scml (3 bones, 5 bindings)',
    runtime: process.version, platform: process.platform, architecture: process.arch,
    note: 'API microbenchmark including bindings and allocations. No physics throughput, sustained transition stepping, or frame-budget claim.',
    results: results};
if (quickOptions.output) require('fs').writeFileSync(quickOptions.output, JSON.stringify(report, null, 2));
console.log(JSON.stringify(report, null, 2));
process.exit(0);
