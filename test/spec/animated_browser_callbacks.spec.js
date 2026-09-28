// Shared callback ownership regressions, plus browser-specific handle deletion.
require('./SpecHelper');
describe('Animation callback lifetime', function() {
    it('uses the original owner and retires completed callbacks exactly once', function() {
        const a=new pdg.Animated();let calls=0;
        const helper=new pdg.IAnimationHelper(function(owner,seconds) {
            expect(owner).toBe(a);expect(this).toBe(helper);expect(seconds).toBe(.125);++calls;return false;
        });
        a.addAnimationHelper(helper);a.animate(.125);a.animate(.125);expect(calls).toBe(1);
        a.removeAnimationHelper(helper);a.addAnimationHelper(helper);a.animate(.125);expect(calls).toBe(2);
        if (typeof a.delete === 'function') a.delete();
    });
    it('safely defers removals while the native helper list is executing', function() {
        const a=new pdg.Animated();let secondCalls=0,firstCalls=0;
        const second=new pdg.IAnimationHelper(function(){++secondCalls;return true;});
        const first=new pdg.IAnimationHelper(function(){++firstCalls;a.removeAnimationHelper(second);a.removeAnimationHelper(first);return true;});
        a.addAnimationHelper(first);a.addAnimationHelper(second);a.animate(.1);a.animate(.1);
        expect(firstCalls).toBe(1);expect(secondCalls).toBe(0);
        const clear=new pdg.IAnimationHelper(function(){a.clearAnimationHelpers();return true;});
        a.addAnimationHelper(clear);a.addAnimationHelper(second);a.animate(.1);a.animate(.1);expect(secondCalls).toBe(0);
        if (typeof a.delete === 'function') a.delete();
    });
    it('shares a retained helper between owners without duplicate registration', function() {
        const a=new pdg.Animated(), b=new pdg.Animated();let calls=0;
        const helper=new pdg.IAnimationHelper(function(){++calls;return false;});
        a.addAnimationHelper(helper);a.addAnimationHelper(helper);b.addAnimationHelper(helper);
        a.animate(.1);b.animate(.1);expect(calls).toBe(2);
        a.addAnimationHelper(helper);a.animate(.1);expect(calls).toBe(3);
        if (typeof a.delete === 'function') { a.delete(); b.delete(); }
    });
    it('defers additions and keeps re-added helpers when the old callback finishes', function() {
        const a=new pdg.Animated();let calls=0,addedCalls=0;
        const added=new pdg.IAnimationHelper(function(){++addedCalls;return false;});
        const helper=new pdg.IAnimationHelper(function(){
            if (++calls===1) { a.removeAnimationHelper(helper);a.addAnimationHelper(helper);a.addAnimationHelper(added); }
            return false;
        });
        a.addAnimationHelper(helper);a.animate(.1);
        expect(calls).toBe(1);expect(addedCalls).toBe(0);
        a.animate(.1);a.animate(.1);expect(calls).toBe(2);expect(addedCalls).toBe(1);
        if (typeof a.delete === 'function') a.delete();
    });
});

if (typeof pdg.Sprite.prototype.delete === 'function') describe('Browser explicit handle lifetime', function() {
    it('keeps retained Parts and bodies safe after their Sprite wrapper is deleted', function() {
        const sprite=new pdg.Sprite(), part=sprite.createPart('retained'), body=part.setupPhysicsBody();
        sprite.delete();expect(part.getSprite()).toBe(null);expect(part.physics).toBe(pdg.NoPhysics);
        expect(body.isAttached()).toBe(false);body.setVelocity(8,0);body.step(.25);expect(body.getState().x).toBeCloseTo(2,5);
        part.setMovement(4,0);part.animate(.25);expect(part.getLocation().x).toBeCloseTo(1,5);
        part.delete();body.delete();
    });
    it('retains layer-owned Sprites independently of an explicitly deleted handle', function() {
        const layer=pdg.createSpriteLayer();
        try {
            const sprite=layer.createSprite(), part=sprite.createPart('layer-owned');
            sprite.delete();expect(part.isAttached()).toBe(true);
            const fresh=layer.getNthSprite(0);expect(fresh.isDeleted()).toBe(false);
            expect(part.getSprite()).toBe(fresh);expect(fresh.getPartCount()).toBe(1);
            fresh.delete(); // cleanup must tolerate expired entries in its wrapper cache
            part.delete();
        } finally { pdg.cleanupLayer(layer); }
    });

});
