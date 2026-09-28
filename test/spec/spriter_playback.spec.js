// Behavioral acceptance for the floating-point-seconds Spriter playback API.
// Uses authored points, so headless and GUI runs can inspect the actual pose.
var spriterPlaybackLayer = pdg.createSpriteLayer();
var spriterPlaybackSupported = typeof spriterPlaybackLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(spriterPlaybackLayer);

describe('Spriter playback regression', function() {
    if (!spriterPlaybackSupported) {
        it('requires Spriter support', function() { pending('Spriter support disabled'); });
        return;
    }
    var layer, sprite, timers;
    function later(fn, ms) { timers.push(setTimeout(fn, ms)); }
    beforeEach(function() {
        timers = [];
        layer = pdg.createSpriteLayer();
        layer.setUseChipmunkPhysics(false);
        sprite = layer.createSpriteFromSpriterFile(process.cwd() + '/data/spriter-regression/playback.scml');
    });
    afterEach(function() {
        timers.forEach(clearTimeout);
        pdg.cleanupLayer(layer);
        layer = sprite = null;
    });
    it('validates targets without changing paused playback', function() {
        sprite.startAnimation('a');
        sprite.pauseAnimation();
        expect(sprite.hasAnimation('a')).toBe(true);
        expect(sprite.hasAnimation('missing')).toBe(false);
        [-1, 999, 0.5, NaN, Infinity, 4294967296].forEach(function(id) {
            expect(sprite.hasAnimation(id)).toBe(false);
        });
        sprite.startAnimation('missing');
        sprite.blendToAnimation('missing', 0.5);
        sprite.blendToAnimation(1, Infinity);
        sprite.blendToAnimation('b', NaN);
        expect(sprite.isAnimationPaused()).toBe(true);
        expect(sprite.isBlending()).toBe(false);
        sprite.startAnimation(0);
        expect(sprite.isAnimationPlaying()).toBe(true);
        expect(sprite.isAnimationPaused()).toBe(false);
    });
    it('validates entity and clip together before changing live playback', function() {
        sprite.startAnimation('b'); sprite.pauseAnimation();
        sprite.activateSubEntity('alternate', 'missing');
        sprite.activateSubEntity('missing', 'a');
        expect(sprite.isAnimationPaused()).toBe(true);
        expect(sprite.getAttachPoint('socket').x).toBeCloseTo(110, 3);
        expect(sprite.hasAnimation('b')).toBe(true);
        sprite.activateSubEntity('alternate', 'a');
        expect(sprite.isAnimationPlaying()).toBe(true);
        expect(sprite.hasAnimation('b')).toBe(true);
        expect(sprite.getAttachPoint('socket').x).toBeCloseTo(10, 3);
    });
    it('keeps visible blend, normalized progress and completion synchronized', function(done) {
        var completions = 0;
        sprite.onAnimationBlendComplete(function() {
            ++completions;
            expect(sprite.isBlending()).toBe(false);
            expect(sprite.getBlendProgress()).toBe(1);
            expect(sprite.getAttachPoint('socket').x).toBeCloseTo(110, 3);
            later(function() {
                expect(completions).toBe(1);
                done();
            }, 80);
            return true;
        });
        sprite.startAnimation('a');
        sprite.blendToAnimation('b', 0.8);
        later(function() {
            sprite.pauseAnimation();
            var progress = sprite.getBlendProgress();
            var x = sprite.getAttachPoint('socket').x;
            var phase = sprite.getAnimationProgress();
            expect(progress > 0 && progress < 1).toBe(true);
            expect(x).toBeCloseTo(10 + progress * 100, 3);
            later(function() {
                expect(sprite.getBlendProgress()).toBe(progress);
                expect(sprite.getAnimationProgress()).toBe(phase);
                expect(sprite.getAttachPoint('socket').x).toBeCloseTo(x, 3);
                expect(completions).toBe(0);
                sprite.resumeAnimation();
            }, 160);
        }, 100);
    });
    it('continues the destination when the source ends during a longer blend', function(done) {
        sprite.startAnimation('once');
        sprite.blendToAnimation('b', 0.3);
        sprite.onAnimationBlendComplete(function() {
            expect(sprite.isAnimationPlaying()).toBe(true);
            expect(sprite.getAttachPoint('socket').x).toBeCloseTo(110, 3);
            var phase = sprite.getAnimationProgress();
            later(function() {
                expect(sprite.getAnimationProgress()).not.toBe(phase);
                done();
            }, 80);
            return true;
        });
    });
    it('reports natural completion separately from pause and resumes from the start', function(done) {
        sprite.startAnimation('once');
        later(function() {
            expect(sprite.isAnimationPlaying()).toBe(false);
            expect(sprite.isAnimationPaused()).toBe(false);
            sprite.resumeAnimation();
            expect(sprite.isAnimationPlaying()).toBe(true);
            expect(sprite.getAnimationProgress()).toBe(0);
            done();
        }, 180);
    });
    it('uses one root transform for sockets, children and boxes', function(done) {
        var child = layer.createSprite();
        sprite.startAnimation('a');
        sprite.pauseAnimation();
        sprite.setLocation(new pdg.Point(100, 40));
        expect(sprite.getAttachPoint('socket').x).toBeCloseTo(10, 3);
        expect(sprite.getSpriterCollisionBox('hitbox').left).toBeCloseTo(110, 3);
        expect(sprite.isSpriterCollisionActive('socket')).toBe(false);
        sprite.attachSprite(child, 'socket');
        later(function() {
            expect(child.getLocation().x).toBeCloseTo(110, 3);
            expect(child.getLocation().y).toBeCloseTo(40, 3);
            sprite.setScale(-2, 3);
            expect(sprite.getAttachPoint('socket').x).toBeCloseTo(-20, 3);
            var box = sprite.getSpriterCollisionBox('hitbox');
            expect(box.left).toBeCloseTo(40, 3);
            expect(box.right).toBeCloseTo(80, 3);
            expect(box.top).toBeCloseTo(10, 3);
            sprite.startAnimation('empty');
            expect(sprite.isSpriterCollisionActive('hitbox')).toBe(false);
            expect(sprite.getSpriterCollisionBoxCount()).toBe(0);
            expect(isNaN(sprite.getAttachPoint('socket').x)).toBe(true);
            sprite.detachSprite(child);
            expect(sprite.getAttachedSprite('socket')).toBeNull();
            done();
        }, 80);
    });
    it('cancels the completion of an interrupted blend', function(done) {
        var completions = 0;
        sprite.onAnimationBlendComplete(function() { ++completions; return true; });
        sprite.blendToAnimation(1, 0.08);
        sprite.pauseAnimation();
        sprite.startAnimation(0);
        expect(sprite.isAnimationPaused()).toBe(false);
        expect(sprite.isBlending()).toBe(false);
        later(function() {
            expect(completions).toBe(0);
            expect(sprite.getAttachPoint('socket').x).toBeCloseTo(10, 3);
            sprite.blendToAnimation(1, 0);
            later(function() {
                expect(completions).toBe(1);
                expect(sprite.getAttachPoint('socket').x).toBeCloseTo(110, 3);
                done();
            }, 80);
        }, 140);
    });
});
