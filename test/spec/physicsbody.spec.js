describe('PhysicsBody ownership and units', function() {
    function assignPhysics(owner, body) { 'use strict'; owner.physics = body; }
    it('keeps physical methods off Animated and Layers', function() {
        const animated=new pdg.Animated(),layer=pdg.createSpriteLayer(),camera=new pdg.Camera();
        try {
            ['getMass','applyForce','applyTorque','getVelocity','setVelocity','setFriction','physics']
                .forEach(name=>{expect(animated[name]).toBeUndefined();expect(layer[name]).toBeUndefined();expect(camera[name]).toBeUndefined();});
            expect(layer.setMovement).toBeUndefined();expect(layer.getMovement).toBeUndefined();
            layer.setCamera(camera);camera.setMovement(8,0);
            expect(layer.getCamera().getMovement().x).toBeCloseTo(8,5);
        } finally { pdg.cleanupLayer(layer); }
    });
    it('shares immutable NoPhysics without allocating a body', function() {
        const sprite=new pdg.Sprite(),part=sprite.createPart('hand');
        expect(sprite.physics).toBe(pdg.PhysicsBody.NoPhysics);expect(part.physics).toBe(pdg.PhysicsBody.NoPhysics);
        expect((sprite.physics !== pdg.PhysicsBody.NoPhysics)).toBe(false);
        expect(pdg.PhysicsBody.NoPhysics instanceof pdg.PhysicsBody).toBe(true);
        pdg.PhysicsBody.NoPhysics.applyImpulse(new pdg.Vector(5,2));pdg.PhysicsBody.NoPhysics.applyAngularImpulse(2);
        expect(pdg.PhysicsBody.NoPhysics.applyForce(new pdg.Vector(1,0),.5)).toBe(0);
        expect(pdg.PhysicsBody.NoPhysics.getSpeed()).toBe(0);expect(pdg.PhysicsBody.NoPhysics.getMass()).toBe(0);
        expect(pdg.PhysicsBody.NoPhysics.isPresent()).toBe(false);
        expect(()=>new pdg.PhysicsBody()).toThrow();
        const original=sprite.physics;
        [null,undefined,{},42,part,sprite].forEach(value=>{
            expect(()=>assignPhysics(sprite,value)).toThrow();expect(sprite.physics).toBe(original);
            expect(()=>assignPhysics(part,value)).toThrow();expect(part.physics).toBe(original);
        });
        expect(sprite.hasPhysicsBody).toBeUndefined();expect(sprite.getPhysics).toBeUndefined();
        expect(pdg.NoPhysics).toBe(pdg.PhysicsBody.NoPhysics);
    });
    it('separates impulses, finite forces, torque and programmed motion', function() {
        const sprite=new pdg.Sprite();sprite.setLocation(new pdg.Point(10,20));
        const body=sprite.setupPhysicsBody(2,4);
        expect(body).toBe(sprite.physics);
        body.applyImpulse(new pdg.Vector(4,0));body.applyAngularImpulse(4);
        expect(body.getVelocity().x).toBe(2);expect(body.getAngularVelocity()).toBe(1);
        expect(body.applyForce(new pdg.Vector(999,0),0)).toBe(0);
        expect(body.getVelocity().x).toBe(2);
        body.applyForce(new pdg.Vector(8,0),.25,.25);body.applyTorque(8,.25,.25);
        expect(()=>sprite.setMovement(3,0)).toThrow();expect(()=>sprite.rotateTo(1,.5)).toThrow();
        expect(()=>body.step(.25)).toThrow();
        sprite.removePhysicsBody();expect(body.isAttached()).toBe(false);
        expect(sprite.physics).toBe(pdg.PhysicsBody.NoPhysics);body.step(1);
        expect(body.getState().x).toBeCloseTo(12.625,5);
        expect(body.getState().rotation).toBeCloseTo(1.3125,5);
        expect(body.getVelocity().x).toBeCloseTo(3,5);
        expect(sprite.getLocation().x).toBe(10);
        sprite.setMovement(1,0);expect(sprite.getMovement().x).toBeCloseTo(1,5);
    });
    [false,true].forEach(function(chipmunk) {
        it('reconfigures Sprite and Part bodies using setup arguments and defaults with '+(chipmunk?'Chipmunk':'basic'), function() {
            const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(chipmunk);
            try {
                const sprite=layer.createSprite(), part=sprite.createPart('setup');
                const anchor=layer.createSprite().setupPhysicsBody();
                [sprite,part].forEach(function(owner) {
                    expect(owner.createPhysicsBody).toBeUndefined();expect(owner.createCollider).toBeUndefined();
                    expect(()=>owner.setupPhysicsBody(2,0)).toThrow();
                    expect(owner.physics).toBe(pdg.PhysicsBody.NoPhysics);
                    const body=owner.setupPhysicsBody(2,4), joint=body.createPinJoint(anchor);
                    body.setVelocity(new pdg.Vector(3,4)).setAngularVelocity(2).setFriction(.7);
                    const state=body.getState(), solver=body.getSolver();
                    expect(owner.setupPhysicsBody(5,10)).toBe(body);
                    expect(body.getMass()).toBe(5);expect(body.getMomentOfInertia()).toBe(10);
                    [0,-1,NaN,Infinity].forEach(function(bad) {
                        expect(()=>owner.setupPhysicsBody(8,bad)).toThrow();
                        expect(()=>owner.setupPhysicsBody(bad,8)).toThrow();
                        expect(body.getMass()).toBe(5);expect(body.getMomentOfInertia()).toBe(10);
                    });
                    expect(owner.setupPhysicsBody(7)).toBe(body);
                    expect(body.getMass()).toBe(7);expect(body.getMomentOfInertia()).toBe(1);
                    owner.setupPhysicsBody(2,4);
                    expect(owner.setupPhysicsBody()).toBe(body);
                    expect(body.getMass()).toBe(1);expect(body.getMomentOfInertia()).toBe(1);
                    expect(owner.physics).toBe(body);expect(body.getSolver()).toBe(solver);
                    expect(body.getState().x).toBe(state.x);expect(body.getState().y).toBe(state.y);
                    expect(body.getVelocity().x).toBe(3);expect(body.getAngularVelocity()).toBe(2);
                    expect(body.getFriction()).toBeCloseTo(.7,5);
                    expect(joint.isActive()).toBe(true);expect(body.getConstraint(0)).toBe(joint);
                    body.applyImpulse(new pdg.Vector(2,0));body.applyAngularImpulse(3);
                    expect(body.getVelocity().x).toBeCloseTo(5,5);expect(body.getAngularVelocity()).toBeCloseTo(5,5);
                    body.setMode(pdg.physicsBody_Kinematic);owner.setupPhysicsBody(6,9);
                    expect(body.getMode()).toBe(pdg.physicsBody_Kinematic);
                    expect(body.getMass()).toBe(6);expect(body.getMomentOfInertia()).toBe(9);
                });
            } finally { pdg.cleanupLayer(layer); }
        });
    });
    it('supports an independent physical Part and safe retained bodies', function() {
        const sprite=new pdg.Sprite();sprite.setLocation(new pdg.Point(100,50));
        const part=sprite.createPart('unbound');part.setLocation(new pdg.Point(4,0));
        const body=part.setupPhysicsBody();body.setVelocity(new pdg.Vector(8,0));
        part.animate(.25);
        expect(part.getLocation().x).toBeCloseTo(6,5);
        expect(part.getBoneId()).toBe(pdg.boneId_None);
        expect(part.getTransform(pdg.partSpace_World).tx).toBeCloseTo(106,5);
        sprite.removePart(part.getId());expect(body.isAttached()).toBe(false);
        expect(part.physics).toBe(pdg.PhysicsBody.NoPhysics);body.step(.25);
        expect(part.getLocation().x).toBeCloseTo(6,5);
    });
    it('keeps association read-only while exposing the live body', function() {
        const sprite=new pdg.Sprite(), other=new pdg.Sprite(), part=other.createPart('readonly');
        const body=sprite.setupPhysicsBody(2,4), partBody=part.setupPhysicsBody();
        expect(body.getSolver()).toBe(pdg.physicsSolver_Basic);
        expect(body.getBackend).toBeUndefined();expect(pdg.physicsBackend_Basic).toBeUndefined();
        [sprite,part].forEach(owner=>{
            const original=owner.physics;
            [body,partBody,pdg.PhysicsBody.NoPhysics].forEach(value=>{
                expect(()=>assignPhysics(owner,value)).toThrow();expect(owner.physics).toBe(original);
            });
            const descriptor=Object.getOwnPropertyDescriptor(Object.getPrototypeOf(owner),'physics');
            expect(typeof descriptor.get).toBe('function');expect(descriptor.set).toBeUndefined();
            expect(owner._assignPhysics).toBeUndefined();
        });
        sprite.physics.applyImpulse(new pdg.Vector(4,0));expect(body.getVelocity().x).toBe(2);
        sprite.removePhysicsBody();part.removePhysicsBody();
        expect(body.isAttached()).toBe(false);expect(partBody.isAttached()).toBe(false);
        expect(sprite.physics).toBe(other.physics);expect(part.physics).toBe(pdg.PhysicsBody.NoPhysics);
        expect(sprite.setupPhysicsBody()).not.toBe(body);expect(body.isAttached()).toBe(false);
    });
    it('uses force-limited physical drives with explicit rotation routes', function() {
        const sprite=new pdg.Sprite(), body=sprite.setupPhysicsBody(2,4);
        expect(body.setDriveTarget(new pdg.Point(100,100),10,6,8,4,1,pdg.rotationDirection_AsSpecified)).toBe(body);
        expect(body.getState().x).toBe(0);expect(body.isDriveEnabled()).toBe(true);
        const ser=new pdg.Serializer();sprite.serialize(ser);
        body.clearDrive();const des=new pdg.Deserializer();des.setDataPtr(ser.getDataPtr());sprite.deserialize(des);
        expect(body.getDriveState().rotation).toBe(10);expect(body.isDriveEnabled()).toBe(true);
        sprite.removePhysicsBody();body.step(.25);
        expect(body.getSpeed()).toBeLessThan(.750001);expect(body.getAngularVelocity()).toBeCloseTo(.5,5);
        const drive=body.getDriveState();expect(Math.hypot(drive.forceX,drive.forceY)).toBeCloseTo(6,5);
        expect(drive.torque).toBe(8);drive.x=999;expect(body.getDriveState().x).toBe(100);
        [-1,4,.5,NaN,'clockwise'].forEach(direction=>{
            expect(()=>body.setDriveTarget(new pdg.Point(0,0),0,1,1,4,1,direction)).toThrow();
        });
        expect(()=>body.setDriveTarget(new pdg.Point(0,0),0,-1,1)).toThrow();
        expect(body.getDriveState().x).toBe(100);
        const speed=body.getSpeed();expect(body.clearDrive()).toBe(body);body.step(.1);
        expect(body.getSpeed()).toBeCloseTo(speed,6);expect(body.isDriveEnabled()).toBe(false);
        body.setDriveTarget(new pdg.Point(0,0),0,1,1).setMode(pdg.physicsBody_Kinematic);
        expect(body.isDriveEnabled()).toBe(false);
        expect(()=>body.setDriveTarget(new pdg.Point(0,0),0,1,1)).toThrow();
        expect(pdg.NoPhysics.setDriveTarget(new pdg.Point(1,2),0,1,1)).toBe(pdg.NoPhysics);
        expect(pdg.NoPhysics.getDriveState().enabled).toBe(false);
    });
    it('round-trips physical snapshots and pending finite loads', function() {
        const sprite=new pdg.Sprite();sprite.setLocation(new pdg.Point(3,4));
        const body=sprite.setupPhysicsBody(2,4);body.setVelocity(new pdg.Vector(2,0));
        body.setAngularVelocity(1);body.applyForce(new pdg.Vector(8,0),.25,.25);
        body.applyTorque(8,.25,.25);
        const ser=new pdg.Serializer();const size=sprite.getSerializedSize(ser);sprite.serialize(ser);
        expect(ser.getDataPtr().getDataSize()).toBe(size+3);
        body.stopAllForces().setVelocity(new pdg.Vector(99,0));
        const des=new pdg.Deserializer();des.setDataPtr(ser.getDataPtr());sprite.deserialize(des);
        expect(sprite.physics).toBe(body);expect(body.getVelocity().x).toBe(2);
        sprite.removePhysicsBody();body.step(1);
        expect(body.getState().x).toBeCloseTo(5.625,5);
        expect(body.getAngularVelocity()).toBeCloseTo(1.5,5);
    });
    it('restores current programmed movement without instantiating a body', function() {
        const source = new pdg.Sprite();
        source.setMovement(8, -4);source.setSpin(2);
        const ser = new pdg.Serializer();source.serialize(ser);
        const restored = new pdg.Sprite(), des = new pdg.Deserializer();
        des.setDataPtr(ser.getDataPtr());restored.deserialize(des);
        expect(restored.physics).toBe(pdg.PhysicsBody.NoPhysics);
        expect(restored.getMovement().x).toBeCloseTo(8, 5);
        expect(restored.getMovement().y).toBeCloseTo(-4, 5);
        expect(restored.getSpin()).toBeCloseTo(2, 5);
    });
});

describe('PhysicsBody angular-speed breaks', function() {
    it('reports Part overspeed once per excursion and preserves the latch in snapshots', function() {
        const sprite=new pdg.Sprite(), part=sprite.createPart('shaft'), housing=sprite.setupPhysicsBody();
        const body=part.setupPhysicsBody(), events=[];
        const handler=new pdg.IEventHandler(function(event) { events.push(event);return true; });
        sprite.addHandler(handler,pdg.eventType_SpriteBreak);
        expect(body.setBreakAngularSpeed(10)).toBe(body);
        expect(body.getBreakAngularSpeedReference()).toBeNull();
        body.setAngularVelocity(10);part.animate(.01);expect(events.length).toBe(0);
        body.setAngularVelocity(-12);part.animate(.01);
        expect(events.length).toBe(1);
        const event=events[0];
        expect(event.reason).toBe(pdg.physicsBreak_AngularSpeed);expect(event.action).toBe(pdg.action_BodyBreak);
        expect(event.body).toBe(body);expect(event.part).toBe(part);expect(event.actingSprite).toBe(sprite);
        expect(event.inLayer).toBeNull(); // Unattached sprites still emit body-break events.
        expect(event.referenceBody).toBeNull();expect(event.joint).toBeNull();
        expect(event.angularSpeed).toBe(12);expect(event.breakAngularSpeed).toBe(10);
        body.setBreakAngularSpeed(10);part.animate(.01);expect(events.length).toBe(1);
        [-1,NaN,Infinity].forEach(value=>expect(()=>body.setBreakAngularSpeed(value)).toThrow());
        expect(()=>body.setBreakAngularSpeed(1,body)).toThrow();
        expect(()=>body.setBreakAngularSpeed(1,{})).toThrow();
        part.animate(.01);expect(events.length).toBe(1);
        body.setAngularVelocity(10);part.animate(.01);body.setAngularVelocity(11);part.animate(.01);
        expect(events.length).toBe(2);
        body.setBreakAngularSpeed(3,housing);housing.setAngularVelocity(20);body.setAngularVelocity(20);
        part.animate(.01);expect(events.length).toBe(2);
        body.setAngularVelocity(24);part.animate(.01);expect(events.length).toBe(3);
        expect(events[2].referenceBody).toBe(housing);expect(events[2].angularSpeed).toBe(4);
        const writer=new pdg.Serializer();sprite.serialize(writer);
        const restored=new pdg.Sprite(), reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());restored.deserialize(reader);
        const copiedPart=restored.findPart('shaft'), copiedBody=copiedPart.physics;let restoredEvents=0;
        restored.addHandler(new pdg.IEventHandler(function(){++restoredEvents;return true;}),pdg.eventType_SpriteBreak);
        expect(copiedBody.getBreakAngularSpeed()).toBe(3);
        expect(copiedBody.getBreakAngularSpeedReference()).toBe(restored.physics);
        copiedPart.animate(.01);expect(restoredEvents).toBe(0);
        copiedBody.setAngularVelocity(20);copiedPart.animate(.01);copiedBody.setAngularVelocity(24);copiedPart.animate(.01);
        expect(restoredEvents).toBe(1);
        sprite.removePhysicsBody();expect(body.getBreakAngularSpeed()).toBe(0);
        expect(body.getBreakAngularSpeedReference()).toBeNull();
        expect(body.setBreakAngularSpeed(5,null).getBreakAngularSpeedReference()).toBeNull();
        expect(body.setBreakAngularSpeed(5,undefined).getBreakAngularSpeedReference()).toBeNull();
        sprite.removeHandler(handler,pdg.eventType_SpriteBreak);
        expect(pdg.PhysicsBody.NoPhysics.setBreakAngularSpeed(1)).toBe(pdg.PhysicsBody.NoPhysics);
        expect(pdg.PhysicsBody.NoPhysics.getBreakAngularSpeed()).toBe(0);
    });
    [false,true].forEach(function(native) {
        it('routes world-step root and Part events with '+(native?'Chipmunk':'basic'), function(done) {
            const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(native);layer.setGravity(0);layer.setDamping(1);
            const sprite=layer.createSprite(), part=sprite.createPart('shaft');
            const root=sprite.setupPhysicsBody(),body=part.setupPhysicsBody();
            const joint=root.createPivotJoint(body);const events=[];
            sprite.addHandler(new pdg.IEventHandler(function(event) { events.push(event);return true; }),pdg.eventType_SpriteBreak);
            root.setBreakAngularSpeed(1).setAngularVelocity(2);body.setBreakAngularSpeed(3).setAngularVelocity(-4);
            setTimeout(function() {
                try {
                    expect(events.length).toBe(2);
                    expect(events.some(event=>event.body===root && event.part===null && event.actingSprite===sprite && event.inLayer===layer)).toBe(true);
                    expect(events.some(event=>event.body===body && event.part===part && event.angularSpeed===4)).toBe(true);
                    expect(joint.isActive()).toBe(true);expect(body.getAngularVelocity()).toBe(-4);
                } finally {pdg.cleanupLayer(layer);done();}
            },150);
        });
    });
});

describe('Native-qualified object bindings', function() {
    it('rejects invalid reference arguments before invoking native code', function() {
        const a = new pdg.Sprite(), b = new pdg.Sprite();
        const body = a.setupPhysicsBody(), other = b.setupPhysicsBody();
        const collider = a.setupCollider();
        [null, undefined, {}, 1, new pdg.Point(0, 0)].forEach(function(value) {
            expect(()=>body.createPinJoint(value)).toThrow();
            expect(()=>collider.setPhysicsBody(value)).toThrow();
            expect(()=>collider.overlaps(value)).toThrow();
        });
        expect(body.getConstraintCount()).toBe(0);
        const shapedJoint = body.createPinJoint(other, {x:1,y:2}, {x:3,y:4});
        expect(shapedJoint.getAnchorA().x).toBe(1);
        expect(shapedJoint.getAnchorB().y).toBe(4);
        shapedJoint.disconnect();
        const joint = body.createPinJoint(other);
        expect(joint.getBodyA()).toBe(body);
        expect(joint.getBodyB()).toBe(other);
        expect(collider.setPhysicsBody(other)).toBe(collider);
        expect(collider.getPhysicsBody()).toBe(other);
        body.disconnect();
    });
    it('reacquires retained reference results after deletion of a browser handle', function() {
        const owner = new pdg.Sprite(), otherOwner = new pdg.Sprite();
        const body = owner.setupPhysicsBody(), other = otherOwner.setupPhysicsBody();
        if (!body.delete) return; // Explicit Embind handle deletion is browser-only.
        const joint = body.createPinJoint(other);
        body.delete();
        expect(body.isDeleted()).toBe(true);
        expect(()=>other.createPinJoint(body)).toThrow();
        const replacement = owner.setupPhysicsBody();
        expect(replacement === body).toBe(false);
        expect(replacement).toBe(owner.physics);
        expect(joint.getBodyA()).toBe(replacement);
        expect(replacement.getConstraint(0)).toBe(joint);
        owner.removePhysicsBody();
        expect(owner.physics).toBe(pdg.NoPhysics);
        expect(replacement.isAttached()).toBe(false);
        expect(joint.getBodyA()).toBe(pdg.NoPhysics);
        replacement.step(.01);
    });
});
