// Raw borrowed handles are held only while their test fixture is alive.
describe('Generated Chipmunk C bindings', function() {
    if (!pdg._ChipmunkTestFixture) return; // Fixture exists only in WASM_BUILD=test.
    function throwsType(fn, type) {
        let error;
        try { fn(); } catch (caught) { error = caught; }
        expect(error instanceof type).toBe(true);
    }
    let fixture;
    beforeEach(function() { fixture = new pdg._ChipmunkTestFixture(); });
    afterEach(function() { fixture.delete(); });
    it('dispatches space functions and fluent scalar properties', function() {
        const space = fixture.space();
        [['IdleSpeedThreshold', 2], ['SleepTimeThreshold', 3], ['CollisionSlop', .2],
            ['CollisionBias', .1], ['CollisionPersistence', 4]].forEach(function(pair) {
            expect(space['set'+pair[0]](pair[1])).toBe(space);
            expect(space['get'+pair[0]]()).toBeCloseTo(pair[1], 7);
        });
        expect(space.useSpatialHash(10, 100)).toBeUndefined();
        expect(space.reindexStatic()).toBeUndefined();
        expect(space.step(1/60)).toBeUndefined();
        expect(()=>space.step('bad')).toThrow();
    });
    const properties = [
        ['PinDist'], ['SlideMinDist', 'SlideMaxDist'], [], ['GrooveStart', 'GrooveEnd'],
        ['SpringStiffness', 'SpringDamping', 'SpringRestLength'],
        ['SpringStiffness', 'SpringDamping', 'RotarySpringRestAngle'],
        ['MinAngle', 'MaxAngle'], ['RatchetAngle', 'RatchetPhase', 'RatchetInterval'],
        ['GearRatio', 'GearInitialAngle'], ['MotorSpinRate']
    ];
    properties.forEach(function(props, index) {
        it('selects properties by native joint type '+index+' without user-data tags', function() {
            const joint = fixture.joint(index);
            expect(joint.activateBodies()).toBeUndefined();
            expect(typeof joint.getImpulse()).toBe('number');
            props.concat(['MaxForce', 'MaxBias', 'ErrorBias']).forEach(function(prop) {
                const vector = prop === 'GrooveStart' || prop === 'GrooveEnd';
                const value = vector ? new pdg.Offset(2, 3) : .5;
                expect(joint['set'+prop](value)).toBe(joint);
                const actual = joint['get'+prop]();
                if (vector) {
                    expect(actual instanceof pdg.Offset).toBe(true);
                    expect(actual.x).toBe(2); expect(actual.y).toBe(3);
                } else expect(actual).toBeCloseTo(value, 7);
            });
            ['Anchor', 'OtherAnchor'].forEach(function(prop) {
                const supported = [0,1,2,4].indexOf(index) !== -1 || (index===3 && prop==='OtherAnchor');
                if (supported) {
                    expect(joint['set'+prop](new pdg.Offset(4, 5))).toBe(joint);
                    const actual = joint['get'+prop]();
                    expect(actual instanceof pdg.Offset).toBe(true);
                    expect(actual.x).toBe(4); expect(actual.y).toBe(5);
                } else {
                    expect(joint['get'+prop]()).toBeUndefined();
                    throwsType(()=>joint['set'+prop](new pdg.Offset(4,5)), TypeError);
                }
            });
            const unsupported = index === 0 ? 'GearRatio' : 'PinDist';
            expect(joint['get'+unsupported]()).toBeUndefined();
            throwsType(()=>joint['set'+unsupported](2), TypeError);
        });
    });
    it('converts contacts to public values and checks indices before native calls', function() {
        let contacts = 0;
        fixture.withContact(function(arbiter) {
            contacts++;
            expect(arbiter.isFirstContact()).toBe(true);
            expect(arbiter.getCount()).toBe(1);
            expect(arbiter.getNormal() instanceof pdg.Vector).toBe(true);
            expect(Math.abs(arbiter.getNormal().x)).toBe(1);
            expect(arbiter.getPointA(0) instanceof pdg.Point).toBe(true);
            expect(arbiter.getPointB(0) instanceof pdg.Point).toBe(true);
            expect(arbiter.getDepth(0)).toBeCloseTo(-1, 7);
            ['getPointA', 'getPointB', 'getDepth'].forEach(function(method) {
                [-1, 1].forEach(function(index) {
                    throwsType(()=>arbiter[method](index), RangeError);
                });
                [1.5, NaN, 4294967296, "0"].forEach(function(index) {
                    throwsType(()=>arbiter[method](index), TypeError);
                });
            });
        });
        fixture.withContact(function(arbiter) { contacts++; expect(arbiter.isFirstContact()).toBe(false); });
        expect(contacts).toBe(2);
    });
});
