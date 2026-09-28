'use strict';
// Shared fixed-load measurement. Frame-start intervals include presentation and
// scheduling, unlike timing only the draw callback. Initialization is excluded.
const fs = require('fs');
const path = require('path');
function options(argv) {
    if (argv.includes('--automated')) throw Error('Use --quick for short performance tests');
    const result = {quick: argv.includes('--quick'), warmup: 1, seconds: 3, factor: 1.5};
    const names = {'--warmup-seconds':'warmup', '--sample-seconds':'seconds', '--load-factor':'factor', '--output':'output'};
    argv.forEach((arg, i) => {
        if (!names[arg]) return;
        const value = argv[i + 1];
        if (!value || value.startsWith('--')) throw Error(arg + ' requires a value');
        result[names[arg]] = arg === '--output' ? value : Number(value);
    });
    for (const key of ['warmup', 'seconds', 'factor']) {
        if (!Number.isFinite(result[key]) || result[key] < (key === 'warmup' ? 0 : 0.001) || result[key] > (key === 'factor' ? 10 : 60))
            throw Error('Invalid quick ' + key);
    }
    return result;
}
function requireRelease(pdg) {
    if (process.versions && process.versions.node && pdg._buildConfiguration !== 'Release')
        throw Error('Performance tests require Release PDG. Use ./test/perf, or run the interactive benchmark through test/lib/perf_build.js.');
}
// Embind owns native allocations until delete(); V8 wrappers are collected.
// Call only for benchmark-owned temporaries after their last use.
function dispose(object) {
    if (object && typeof object.delete === 'function') object.delete();
}
function now() {
    if (typeof performance !== 'undefined' && performance.now) return performance.now();
    const time = process.hrtime();
    return time[0] * 1000 + time[1] / 1e6;
}
// A process-wide benchmark override, including ports created before the script.
// Do not change the public setTargetFPS() semantics for ordinary applications.
function uncap() { process.env.PDG_PERF_UNCAPPED = '1'; }
function load(config, reference, test) {
    // Convex rendering now handles substantially more polygons. Keep the score
    // reference intact; only increase the measured workload (4× at default 1.5×).
    return Math.ceil(reference * config.factor * (test === 'polygon' ? 8 / 3 : 1));
}
class Sampler {
    constructor(config) { this.config = config; this.reset(); }
    reset() { this.start = null; this.previous = null; this.elapsed = 0; this.frames = []; }
    tick(time = now()) {
        if (!Number.isFinite(time)) throw Error('Invalid performance clock');
        if (typeof window !== 'undefined' && window === globalThis && document.hidden)
            throw Error('Quick benchmark tab became hidden; discard this run and retry with the test tab visible');
        if (this.start === null) this.start = time;
        if (time - this.start < this.config.warmup * 1000) return false;
        if (this.previous !== null) {
            const interval = time - this.previous;
            // Browser clock resolution can give adjacent frames the same time.
            // Count both frames; elapsed time catches up on the next clock tick.
            if (interval < 0) throw Error('Backwards performance clock: ' + this.previous + ' -> ' + time);
            this.frames.push(interval); this.elapsed += interval;
        }
        this.previous = time;
        return this.elapsed >= this.config.seconds * 1000 && this.frames.length >= 2;
    }
    result(load, referenceLoad, referenceScore, targetFPS = 60) {
        if (this.frames.length < 2 || this.elapsed <= 0) throw Error('Incomplete performance sample');
        const fps = this.frames.length * 1000 / this.elapsed;
        const sorted = this.frames.slice().sort((a,b) => a-b);
        const percentile = p => sorted[Math.ceil(sorted.length * p) - 1];
        return {synthetic: true, fixedLoad: load, loadFactor: load / referenceLoad, referenceLoad, referenceScore, targetFPS,
            estimatedCapacity: load * fps / targetFPS,
            score: Math.round(referenceScore * load / referenceLoad * fps / targetFPS),
            averageFPS: fps, totalFrames: this.frames.length, durationSeconds: this.elapsed / 1000,
            warmupSeconds: this.config.warmup, requestedSampleSeconds: this.config.seconds,
            frameTime: {meanMs: this.elapsed / this.frames.length, minMs: sorted[0],
                maxMs: sorted[sorted.length-1], percentile95Ms: percentile(.95), percentile99Ms: percentile(.99)},
            atOrAboveTarget: fps >= targetFPS * .98};
    }
}
function baseline(name) { return JSON.parse(fs.readFileSync(path.join(__dirname, name), 'utf8')); }
function markName(id) {
    return {bunnymark:'QuickBunnyMark', pdgmark:'QuickPDGMark', canvasmark:'QuickCanvasMark',
        'cpp-bunnymark':'QuickBunnyMark', 'cpp-pdgmark':'QuickPDGMark'}[id] || id;
}
function write(config, name, tests, extra) {
    const result = Object.assign({testName: markName(name), benchmarkId: name, language: 'JavaScript', mode: 'quick', synthetic: true,
        timestamp: new Date().toISOString(), measurement: 'frame-start intervals; linear load/FPS extrapolation',
        loadFactor: config.factor, framePacing: 'uncapped', requestedEngineFPS: null, requestedSwapInterval: 0, tests,
        compositeScore: Object.keys(tests).reduce((sum, key) => sum + tests[key].score, 0)}, extra);
    const filename = config.output || path.join(__dirname, name + '_quick_results.json');
    fs.writeFileSync(filename, JSON.stringify(result, null, 2) + '\n');
    console.log(result.testName + ' score: ' + result.compositeScore + '\nResults: ' + filename);
    if (typeof global.pdgPerfReport === 'function') global.pdgPerfReport(result);
    return result;
}
module.exports = {requireRelease, dispose, options, now, uncap, load, Sampler, baseline, markName, write};
