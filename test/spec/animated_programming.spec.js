// Seconds, programmed rates and directed rotation on the public script surface.
describe('Animated programming contract', function() {
    it('preserves fractional seconds across tween, wait, helper and easing calls', function() {
        const a=new pdg.Animated();
        a.moveTo(new pdg.Point(10,0),.00025,pdg.linearTween);
        a.animate(.000125);expect(a.getLocation().x).toBeCloseTo(5,5);
        a.animate(.000125);expect(a.getLocation().x).toBeCloseTo(10,5);
        a.wait(.125).moveTo(new pdg.Point(20,0),.25,pdg.linearTween);
        a.animate(.1875);expect(a.getLocation().x).toBeCloseTo(12.5,5);
        let dt=0;
        const helper=new pdg.IAnimationHelper(function(what,seconds){dt=seconds;return true;});
        a.addAnimationHelper(helper);a.animate(.03125);a.removeAnimationHelper(helper);
        expect(dt).toBeCloseTo(.03125,9);
        const seen=[];
        const easing=pdg.registerEasingFunction(function(t,b,c,d){seen.push([t,d]);return b+c*t/d;});
        seen.length=0;a.moveTo(new pdg.Point(30,0),.5,easing);a.animate(.125);
        expect(seen[0][0]).toBeCloseTo(.125,9);expect(seen[0][1]).toBeCloseTo(.5,9);
    });
    it('returns fresh Offsets and integrates movement and spin rates', function() {
        const a=new pdg.Animated();
        expect(a.setMovement(new pdg.Vector(20,0))).toBe(a);
        expect(a.getMovement() instanceof pdg.Offset).toBe(true);
        const copy=a.getMovement();copy.x=999;expect(a.getMovement().x).toBeCloseTo(20,4);
        a.changeMovementTo(0,0,.5,pdg.linearTween);a.animate(.25);
        expect(a.getMovement().x).toBeCloseTo(10,4);expect(a.getLocation().x).toBeCloseTo(3.75,4);
        a.animate(.5);expect(a.getLocation().x).toBeCloseTo(5,4);
        a.changeSpinTo(4,.5,pdg.linearTween);a.animate(.25);
        expect(a.getSpin()).toBeCloseTo(2,4);expect(a.getRotation()).toBeCloseTo(.25,4);
        a.animate(.5);expect(a.getRotation()).toBeCloseTo(2,4);
    });
    it('keeps motion independent of timestep partitions', function() {
        const a=new pdg.Animated(),b=new pdg.Animated();
        a.changeMovementTo(40,0,.75,pdg.easeInOutQuad);b.changeMovementTo(40,0,.75,pdg.easeInOutQuad);
        a.animate(1);for(let i=0;i<100;++i)b.animate(.01);
        expect(a.getLocation().x).toBeCloseTo(25,4);
        expect(b.getLocation().x).toBeCloseTo(a.getLocation().x,4);
        a.moveTo(new pdg.Point(0,0),.5,pdg.linearTween);a.animate(.25);
        expect(a.getMovement().x).toBe(0);expect(a.getLocation().x).toBeCloseTo(12.5,4);
        a.setMovement(4,0);a.animate(.25);expect(a.getLocation().x).toBeCloseTo(13.5,4);
    });
    it('uses integer rotation routes and retains complete relative turns', function() {
        const a=new pdg.Animated();
        a.setRotation(350*Math.PI/180);
        a.rotateTo(10*Math.PI/180,.5,pdg.linearTween,pdg.rotationDirection_Shortest);a.animate(.25);
        expect(a.getRotation()).toBeCloseTo(2*Math.PI,5);
        a.setRotation(0);a.rotateBy(4*Math.PI,.5,pdg.linearTween);a.animate(.5);
        expect(a.getRotation()).toBeCloseTo(4*Math.PI,5);
        a.setRotation(0);a.rotateTo(Math.PI/2,.5,pdg.linearTween,pdg.rotationDirection_CounterClockwise);a.animate(.25);
        expect(a.getRotation()).toBeCloseTo(-3*Math.PI/4,5);
        [1.5,99,NaN,Infinity,'clockwise'].forEach(direction=>
            expect(()=>a.rotateTo(0,.5,pdg.linearTween,direction)).toThrow());
        expect(()=>a.changeMovementTo(1,2,-.25)).toThrow();
        expect(()=>a.animate(NaN)).toThrow();expect(()=>a.wait(Infinity)).toThrow();
    });
    it('grows and stretches without a physics body', function() {
        const a=new pdg.Animated();a.setSize(10,20);a.setStretching(8,-4);a.animate(.25);
        expect(a.getWidth()).toBeCloseTo(12,5);expect(a.getHeight()).toBeCloseTo(19,5);
        a.stopStretching();a.animate(1);expect(a.getWidth()).toBeCloseTo(12,5);
    });
});
