'use strict';

const names = ['asteroids-bitmaps', 'asteroids-vectors', 'asteroids-mixed',
    'asteroids-effects', 'arena', 'plasma', '3d'];

function workload(scene, index) {
    if (index === 3) return scene.playerBullets.length;
    if (index === 5) return scene.plasmasize * scene.plasmasize;
    if (index === 6) return scene.k3d.objects.length;
    return scene.enemies.length;
}

function median(values) {
    const sorted = values.slice().sort((a, b) => a - b);
    const middle = Math.floor(sorted.length / 2);
    return sorted.length % 2 ? sorted[middle] : (sorted[middle - 1] + sorted[middle]) / 2;
}

// Observe the unchanged original ramp. Each interval belongs to the preceding
// draw, whose population is still present before this frame's update/spawn.
// Normalize by that population before taking the median: plasma and bullets
// can grow substantially during even the last ten frames of a ramp.
function collect(Game, handler) {
    const references = [], states = new WeakMap();
    const original = Game.Scene.prototype._onBeforeRenderScene;
    Game.Scene.prototype._onBeforeRenderScene = function() {
        const index = handler.game.scenes.indexOf(this) - 1;
        if (index < 0 || index >= names.length || this.sceneCompletedTime)
            return original.call(this);
        let state = states.get(this);
        if (!state || state.start !== this.sceneStartTime) {
            state = {start: this.sceneStartTime, samples: [], first: true};
            states.set(this, state);
        }
        const load = workload(this, index);
        if (!state.first && load > 0 && handler.frameInterval > 0) {
            state.samples.push({load, milliseconds: handler.frameInterval});
            if (state.samples.length > 10) state.samples.shift();
        }
        state.first = false;
        const count = handler.benchmarkScores.length;
        const result = original.call(this);
        if (handler.benchmarkScores.length > count && state.samples.length >= 2) {
            const millisecondsPerItem = median(state.samples.map(s => s.milliseconds / s.load));
            references[index] = {name: names[index], score: handler.benchmarkScores[count], load,
                referenceFPS: 1000 / (load * millisecondsPerItem), terminalSamples: state.samples.slice()};
        }
        return result;
    };
    return references;
}

function result(sample, reference) {
    const equivalentLoad = sample.fixedLoad * sample.averageFPS / reference.referenceFPS;
    let scale = equivalentLoad / reference.load;
    // Work is quadratic in plasma grid width, while the original score grows
    // with elapsed ramp time (one grid-width increment per 100 ms, starting at 8).
    if (reference.name === 'plasma')
        scale = Math.max(0, Math.sqrt(equivalentLoad) - 8) / (Math.sqrt(reference.load) - 8);
    return Object.assign(sample, {
        score: Math.round(reference.score * scale), referenceFPS: reference.referenceFPS,
        equivalentReferenceLoad: equivalentLoad,
        calibration: 'measured ramp endpoint; median frame cost per workload item',
        scoreModel: reference.name === 'plasma' ? 'linear cell throughput; grid-width ramp score' : 'linear workload throughput'
    });
}

module.exports = {names, workload, collect, result, median};
