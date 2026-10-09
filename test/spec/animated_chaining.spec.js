require('./SpecHelper');
describe('Animated call chaining', function() {
    it('keeps JavaScript subclass identity and callbacks across appearance and movement chains', function() {
        class StyledObject extends pdg.AnimatedAttributes {
            mark() { this.marked = true; return this; }
        }
        const a = new StyledObject();
        let callbackOwner;
        const helper = new pdg.IAnimationHelper(function(owner) { callbackOwner = owner; return false; });
        try {
            expect(a instanceof pdg.AnimatedAttributes).toBe(true);
            expect(a instanceof pdg.Animated).toBe(true);
            expect(a.fillOpacity(1).setLocation(0, 0).addAnimationHelper(helper)
                .moveTo(10, 20, .5, pdg.linearTween).andThen()
                .changeFillOpacity(0, .5, pdg.linearTween).mark()).toBe(a);
            a.animate(.75);
            expect(callbackOwner).toBe(a);
            expect(a.marked).toBe(true);
            expect(a.getLocation().x).toBeCloseTo(10, 5);
            expect(a.getFillOpacity()).toBeCloseTo(.5, 5);
            expect(pdg.AnimatedBase).toBeUndefined();
            expect(pdg.AnimatedAttributesBase).toBeUndefined();
        } finally {
            if (typeof a.delete === 'function') a.delete();
            if (typeof helper.delete === 'function') helper.delete();
        }
    });
    it('returns its original receiver from every public mutation family', function() {
        const a=new pdg.Animated(), helper=new pdg.IAnimationHelper(function(){return false;});
        const calls=[
            ['setLocation',new pdg.Point(1,2)], ['moveTo',3,4], ['moveTo',3,4,.1],
            ['moveTo',new pdg.Point(3,4),.1], ['moveBy',1,2], ['moveBy',new pdg.Offset(1,2),.1],
            ['changeMovementTo',1,2,.1], ['changeMovementTo',new pdg.Vector(1,2),.1], ['stopMovement'],
            ['setSize',10,20], ['setWidth',12], ['setHeight',24], ['grow',2], ['grow',2,.1],
            ['stretch',2,3], ['stretch',2,3,.1], ['resizeBy',1,2,.1], ['resizeTo',10,20,.1],
            ['changeGrowingTo',1,.1], ['stopGrowing'], ['changeStretchingTo',1,2,.1], ['stopStretching'],
            ['setScale',2], ['changeScaleTo',2,3,.1], ['pauseSchedule'], ['resumeSchedule'], ['cancelSchedule'],
            ['setRotation',1], ['rotateBy',1], ['rotateBy',1,.1], ['rotateTo',1], ['rotateTo',1,.1],
            ['changeSpinTo',1,.1], ['stopSpinning'], ['setCenterOffset',new pdg.Offset(1,2)],
            ['changeCenterOffsetBy',1,2,.1], ['changeCenterOffsetTo',new pdg.Offset(1,2),.1],
            ['setFlipX',true], ['setFlipY',true], ['flipX'], ['flipY'], ['wait',.1], ['andThen'],
            ['addAnimationHelper',helper], ['addAnimationHelper',helper],
            ['removeAnimationHelper',helper], ['removeAnimationHelper',helper], ['clearAnimationHelpers']
        ];
        calls.forEach(function(call) { a.cancelSchedule(); expect(a[call[0]].apply(a,call.slice(1))).toBe(a); });
        if (typeof a.delete === 'function') a.delete();
    });
    it('preserves Sprite, Part, Camera and AnimatedAttributes identity through inherited chains', function() {
        const sprite=new pdg.Sprite(),part=sprite.createPart('chain'),camera=new pdg.Camera();
        const attributes=new pdg.AnimatedAttributes();
        try {
            [sprite,part,camera,attributes].forEach(function(a) {
                expect(a.moveTo(1,2,.1).rotateTo(1,.1).changeScaleTo(2,2,.1).wait(.1)
                    .cancelSchedule().clearAnimationHelpers()).toBe(a);
            });
        } finally {
            if (typeof camera.delete === 'function') camera.delete();
            if (typeof sprite.delete === 'function') { part.delete();sprite.delete();attributes.delete(); }
        }
    });
});


describe('Animated sequencing', function() {
    it('returns a Sprite normally through async functions and Promise chains', function() {
        const sprite=new pdg.Sprite(); let settled=false, result, failure;
        async function schedule() { return sprite.moveTo(10,0,.5).andThen().moveTo(20,0,.5); }
        schedule().then(function(value) { return value; }).then(function(value) {
            result=value; settled=true;
        }, function(error) { failure=error; settled=true; });
        waitsFor(function() { return settled; }, 'async Sprite result', 1000);
        runs(function() {
            expect(failure).toBeUndefined(); expect(result).toBe(sprite);
            expect(sprite.getLocation().x).toBe(0); expect(sprite.hasScheduledAnimations()).toBe(true);
            sprite.cancelSchedule();
            if (typeof sprite.delete === 'function') sprite.delete();
        });
    });
    it('preserves successive moves, relative targets and receiver identity', function() {
        const a=new pdg.Animated();
        expect(a.moveTo(10,0,.5,pdg.linearTween).andThen()).toBe(a);
        a.moveBy(5,0,.5,pdg.linearTween).andThen().changeScaleTo(2,2,.5,pdg.linearTween);
        a.animate(.75);expect(a.getLocation().x).toBeCloseTo(12.5,5);expect(a.getScale().x).toBe(1);
        a.animate(.5);expect(a.getLocation().x).toBe(15);expect(a.getScale().x).toBeCloseTo(1.5,5);
        a.animate(.25);expect(a.getScale().x).toBe(2);expect(a.hasScheduledAnimations()).toBe(false);
        expect(typeof a.then).toBe('undefined');
    });
    it('consumes sequencing once, supports pause, and preserves ordinary replacement', function() {
        const a=new pdg.Animated();
        a.wait(.25).moveTo(10,0,.5,pdg.linearTween).andThen().moveTo(20,0,.5,pdg.linearTween).pauseSchedule();
        a.animate(2);expect(a.getLocation().x).toBe(0);
        a.resumeSchedule().animate(.5);expect(a.getLocation().x).toBe(5);
        a.moveTo(30,0,.5,pdg.linearTween);a.animate(.5);expect(a.getLocation().x).toBe(30);
        expect(a.hasScheduledAnimations()).toBe(false);
    });
    it('sequences inherited Sprite, Part, Camera and appearance mutations', function() {
        const sprite=new pdg.Sprite(),part=sprite.createPart('sequence'),camera=new pdg.Camera();
        const attrs=new pdg.AnimatedAttributes();
        try {
            [sprite,part,camera,attrs].forEach(function(a) {
                a.moveTo(10,0,.5,pdg.linearTween).andThen().moveTo(20,0,.5,pdg.linearTween);
                expect(a.hasScheduledAnimations()).toBe(true);
                // Native Sprites are stepped by SpriteManager; their timing
                // is also exercised deterministically by the C++ owner tests.
                if (typeof a.animate === 'function') {
                    a.animate(.75);expect(a.getLocation().x).toBeCloseTo(15,5);
                }
                a.cancelSchedule();
            });
            attrs.changeFillOpacity(0,.5,pdg.linearTween).andThen().changeFillOpacity(1,.5,pdg.linearTween);
            attrs.animate(.75);expect(attrs.getFillOpacity()).toBeCloseTo(.5,5);
        } finally {if (typeof camera.delete === 'function') camera.delete();}
    });
});


describe('Timed animation duration requirements', function() {
    const message='Only operations with a duration can be part of a timed animation sequence.';
    function rejectsImmediate(a, call) {
        [function(){a.wait(.25);},function(){a.wait(0);},function(){a.andThen();}].forEach(function(pending) {
            a.cancelSchedule();pending();let caught;
            try {call(a);} catch(error) {caught=error;}
            expect(caught && caught.message).toBe(message);
        });
        a.cancelSchedule();
    }
    it('rejects omitted and instantaneous durations and immediate transform setters', function() {
        const a=new pdg.Animated();
        const calls=[
            x=>x.moveTo(10,20),x=>x.moveBy(1,2,0),
            x=>x.rotateTo(1),x=>x.rotateBy(1,0),x=>x.grow(2),x=>x.stretch(2,3,0),
            x=>x.resizeTo(3,4,0),x=>x.changeScaleTo(2,2,0),x=>x.setMovement(2,3),
            x=>x.setSpin(2),x=>x.setGrowing(2),x=>x.setStretching(2,3),
            x=>x.changeCenterOffsetBy(1,2,0),x=>x.changeCenterOffsetTo(1,2,0),
            x=>x.setLocation(new pdg.Point(3,4)),x=>x.setSize(3,4),x=>x.setWidth(3),
            x=>x.setHeight(4),x=>x.setScale(2),x=>x.setRotation(1),
            x=>x.setCenterOffset(new pdg.Offset(1,2)),x=>x.setFlipX(true),x=>x.flipY(),
            x=>x.stopMovement(),x=>x.stopSpinning(),x=>x.stopGrowing(),x=>x.stopStretching()
        ];
        calls.forEach(call=>rejectsImmediate(a,call));
        a.moveTo(5,6).rotateTo(1).setSize(3,4).setMovement(2,3).stopMovement();
        expect(a.getLocation().x).toBe(5);expect(a.getRotation()).toBe(1);expect(a.hasScheduledAnimations()).toBe(false);
        if(typeof a.delete==='function')a.delete();
    });
    it('rejects immediate appearance mutations, including nonanimated attribute properties', function() {
        const a=new pdg.AnimatedAttributes();
        [x=>x.changeFillOpacity(.5,0),x=>x.fillOpacity(.5),
         x=>x.changeFrames(1,4,0),x=>x.changeScaleTo(2,3,0),x=>x.changeSphereRotation(1,0),
         x=>x.lineStyle(pdg.lineStyle_Solid),x=>x.fitType(pdg.fit_Fill),x=>x.clipOverflow(true),
         x=>x.textStyle(0),x=>x.blendMode(pdg.blendMode_Normal),x=>x.frame(2),
         x=>x.setLocation(new pdg.Point(1,2)),x=>x.translation(new pdg.Offset(1,2)),
         x=>x.rotation(.5),x=>x.scale(2)].forEach(call=>rejectsImmediate(a,call));
        expect(a.fillOpacity(.5)).toBe(a);expect(a.getFillOpacity()).toBe(.5);
        expect(a.hasScheduledAnimations()).toBe(false);
        if(typeof a.delete==='function')a.delete();
    });
    it('preserves the prior animation and pending sequence after a rejected immediate call', function() {
        const a=new pdg.Animated();
        a.moveTo(10,0,.5,pdg.linearTween).andThen();let caught;
        try {a.setLocation(new pdg.Point(99,0));}catch(error){caught=error;}
        expect(caught && caught.message).toBe(message);expect(a.getLocation().x).toBe(0);
        a.moveTo(20,0,.5,pdg.linearTween);a.animate(.75);expect(a.getLocation().x).toBe(15);
        if(typeof a.delete==='function')a.delete();
    });
});


describe('Normalized Animated API', function() {
    it('separates constant rates from transitions and resolves relative successors', function() {
        const a=new pdg.Animated();
        a.setLocation(3,4).setSize(new pdg.Offset(10,20)).resizeBy(2,3);
        expect(a.getSize().x).toBe(12);expect(a.getSize().y).toBe(23);
        a.setMovement(2,0).changeMovementTo(6,0,.5,pdg.linearTween).andThen().changeMovementBy(new pdg.Vector(4,0),.5,pdg.linearTween);
        a.setSpin(2).changeSpinTo(4,.5,pdg.linearTween).andThen().changeSpinBy(2,.5,pdg.linearTween);
        a.setGrowing(4).changeGrowingTo(8,.5,pdg.linearTween).andThen().changeGrowingBy(4,.5,pdg.linearTween);
        a.setScale(2,3).changeScaleTo(4,5,.5,pdg.linearTween).andThen().changeScaleBy(1,-2,.5,pdg.linearTween);
        a.animate(1);
        expect(a.getMovement().x).toBeCloseTo(10,5);expect(a.getLocation().x).toBeCloseTo(9,5);
        expect(a.getSpin()).toBeCloseTo(6,5);expect(a.getRotation()).toBeCloseTo(4,5);
        expect(a.getStretching().x).toBeCloseTo(12,5);expect(a.getWidth()).toBeCloseTo(20,5);
        expect(a.getScale().x).toBeCloseTo(5,5);expect(a.getScale().y).toBeCloseTo(3,5);
        a.stopMovement().stopSpinning().stopGrowing();
        a.resizeTo(100,100,1).stopStretching();a.animate(1);expect(a.getWidth()).toBeCloseTo(20,5);
        if(a.delete)a.delete();
    });
    it('requires timing for transitions and rejects timing on constant setters', function() {
        const a=new pdg.Animated();
        [()=>a.changeSpinTo(),()=>a.changeMovementTo(1,2),()=>a.changeMovementBy(new pdg.Vector(1,2)),
         ()=>a.changeSpinTo(1),()=>a.changeSpinBy(1),()=>a.changeGrowingTo(1),()=>a.changeGrowingBy(1),
         ()=>a.changeStretchingTo(1,2),()=>a.changeStretchingBy(1,2),
         ()=>a.changeScaleTo(2,3),()=>a.changeScaleBy(2,3),()=>a.resizeTo(2,3),
         ()=>a.changeCenterOffsetTo(1,2),()=>a.changeCenterOffsetBy(new pdg.Offset(1,2)),
         ()=>a.setMovement(1,2,.5),()=>a.setSpin(1,.5),()=>a.setGrowing(1,.5),()=>a.setStretching(1,2,.5)
        ].forEach(call=>expect(call).toThrow());
        a.wait(.25);
        expect(()=>a.setGrowing(8)).toThrow();expect(()=>a.setStretching(8,9)).toThrow();
        a.changeStretchingBy(4,8,.5,pdg.linearTween);a.animate(.75);
        expect(a.getStretching().x).toBeCloseTo(4,5);expect(a.getStretching().y).toBeCloseTo(8,5);
        ['startGrowing','startStretching','scaleTo','move','rotate','resize','pauseTweens','hasTweens'].forEach(name=>expect(typeof a[name]).toBe('undefined'));
        expect(typeof pdg.duration_Instantaneous).toBe('undefined');expect(typeof pdg.duration_Constant).toBe('undefined');
        if(a.delete)a.delete();
    });
});
