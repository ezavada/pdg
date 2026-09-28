'use strict';
const perf = require('../quick');

// These references record actual original-ramp populations and terminal frame
// costs, rather than inferring populations from elapsed scores at an assumed Hz.
const calibration = require('./calibration');
const profile = require('./calibration.json');
const references = profile.references;

module.exports = function createQuick(config, context, done) {
    const {GameHandler, Asteroids, Arena, Vector, RAD} = context;
    const sampler = new perf.Sampler(config), results = {};
    let index = -1, scene, load, finished = false;
    function keep(actor) { actor.expired = function() { return false; }; return actor; }
    function next() {
        if (++index === references.length) {
            finished = true;
            perf.write(config, 'canvasmark', results, {
                calibration: profile.method, calibrationSource: profile.source, calibrationTimestamp: profile.timestamp,
                scores: references.map(ref => results[ref.name].score)
            });
            done(); return false;
        }
        const ref = references[index];
        scene = GameHandler.game.scenes[index + 1]; // skip the welcome scene
        scene._onInitScene(); scene.onInitScene();
        scene.world.scale = GameHandler.width / scene.world.viewsize;
        load = Math.ceil(ref.load * config.factor);
        if (index < 3) {
            scene.enemies.length = 0;
            for (let i = 0; i < load; ++i) scene.enemies.push(keep(index < 2
                ? scene.generateAsteroid(Math.random() + 1, i % 4 + 1)
                : new Asteroids.EnemyShip(scene, i % 2)));
        } else if (index === 3) {
            for (let i = 0; i < load; ++i) {
                const heading = i * 360 / load;
                const bullet = new Asteroids.Bullet(new Vector(Math.random() * GameHandler.width,
                    Math.random() * GameHandler.height), new Vector(0, -7).rotate(heading * RAD), heading);
                // Preserve a mix of fading and opaque bullets without population drift.
                bullet.lifespan = i % 40 + 1;
                scene.playerBullets.push(keep(bullet));
            }
        } else if (index === 4) {
            for (let i = 0; i < load; ++i) scene.enemies.push(keep(new Arena.EnemyShip(scene, i % 6 + 1)));
        } else if (index === 5) {
            scene.plasmasize = Math.ceil(Math.sqrt(load));
            load = scene.plasmasize * scene.plasmasize; // cells, not grid width
        } else {
            while (scene.k3d.objects.length < load) scene.add3DObject(scene.k3d.objects.length);
            scene.k3d.objects.length = load;
        }
        sampler.reset();
        console.log('QuickCanvasMark: ' + ref.name + ', fixed load ' + load);
        return true;
    }
    return function frame() {
        if (finished || !GameHandler.game || !GameHandler.game.scenes[0].imagesLoaded) return;
        if (index < 0 && !next()) return;
        if (sampler.tick()) {
            const ref = references[index];
            // CanvasMark's original cutoff is 30 FPS, unlike the other marks.
            results[ref.name] = calibration.result(sampler.result(load, ref.load, ref.score, 30), ref);
            if (!next()) return;
        }
        GameHandler.frameInterval = sampler.frames.length ? sampler.frames[sampler.frames.length - 1] : 1000 / 60;
        GameHandler.frameMultiplier = GameHandler.frameInterval / GameHandler.FPSMS;
        GameHandler.frameCount++;
        scene.onBeforeRenderScene(false); // update existing actors, never ramp
        scene.onRenderScene(GameHandler.canvas.getContext('2d'));
    };
};
module.exports.references = references;
