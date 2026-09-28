describe('Shared Collider and PhysicsConstraint APIs', function() {
    it('edits copied local anchors atomically without changing body or constraint identity', function() {
        const owner=new pdg.Sprite(),part=owner.createPart('limb');
        const a=owner.setupPhysicsBody(),b=part.setupPhysicsBody(2,3);
        const p=new pdg.Point(1,2),q=new pdg.Point(-3,4);
        const joints=[a.createPinJoint(b),a.createSlideJoint(b,p,q,1,5),a.createPivotJoint(b),a.createSpring(b,p,q,2,10,1)];
        for(const joint of joints) {
            const state=b.getState();
            expect(joint.setAnchors(p,q)).toBe(joint);
            expect(joint.getAnchorA() instanceof pdg.Point).toBe(true);
            expect(joint.getAnchorB() instanceof pdg.Point).toBe(true);
            joint.getAnchorA().x=999;expect(joint.getAnchorA().x).toBe(1);
            expect(joint.getAnchorB().y).toBe(4);
            for(const invalid of [null,{}, {x:0,y:NaN}, {x:Infinity,y:0}, {x:'1',y:0}]) {
                expect(()=>joint.setAnchors(new pdg.Point(7,8),invalid)).toThrow();
                // Native bindings reserve a single null argument for signature introspection.
                if(invalid!==null) {
                    expect(()=>joint.setAnchorA(invalid)).toThrow();expect(()=>joint.setAnchorB(invalid)).toThrow();
                }
                expect(joint.getAnchorA().x).toBe(1);expect(joint.getAnchorB().x).toBe(-3);
            }
            expect(()=>joint.setAnchors(p)).toThrow();expect(()=>joint.setAnchorA()).toThrow();
            const throwsOnRead={get x(){throw new Error('coordinate unavailable');},y:0};
            expect(()=>joint.setAnchors(new pdg.Point(7,8),throwsOnRead)).toThrow();
            expect(joint.getAnchorA().x).toBe(1);expect(joint.getAnchorB().x).toBe(-3);
            expect(joint.setAnchorA(q).setAnchorB(p)).toBe(joint);
            expect(joint.getAnchorA().x).toBe(-3);expect(joint.getAnchorB().x).toBe(1);
            expect(b.getState().x).toBe(state.x);expect(b.getMomentOfInertia()).toBe(3);
            expect(joint.getBodyA()).toBe(a);expect(joint.getBodyB()).toBe(b);
            expect(()=>joint.getGrooveStart()).toThrow();expect(()=>joint.setGroove(p,q)).toThrow();
        }
        p.x=55;expect(joints[0].getAnchorB().x).toBe(1);
        a.disconnect();joints[0].setAnchorA(p);
        expect(joints[0].getAnchorA().x).toBe(55);expect(joints[0].isActive()).toBe(false);
        const angular=[a.createRotarySpring(b,0,2,1),a.createRotaryLimit(b,-1,1),a.createRatchet(b,.5),a.createGear(b,2),a.createMotor(b,1,2)];
        for(const joint of angular) {
            expect(()=>joint.getAnchorA()).toThrow();expect(()=>joint.getAnchorB()).toThrow();
            expect(()=>joint.setAnchorA(p)).toThrow();expect(()=>joint.setAnchorB(p)).toThrow();
            expect(()=>joint.setAnchors(p,q)).toThrow();expect(()=>joint.getGrooveEnd()).toThrow();
        }
        a.disconnect();
    });
    it('edits groove tracks and saves the current anchor geometry in both resource modes', function() {
        for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
            const source=new pdg.Sprite(),part=source.createPart('slider');
            const a=source.setupPhysicsBody(),b=part.setupPhysicsBody();
            const groove=a.createGrooveJoint(b,new pdg.Point(0,0),new pdg.Point(1,0),new pdg.Point(0,0));
            expect(groove.setGroove(new pdg.Point(-2,3),new pdg.Point(4,3)).setAnchorB(new pdg.Point(.5,1))).toBe(groove);
            expect(()=>groove.getAnchorA()).toThrow();expect(()=>groove.setAnchorA(new pdg.Point())).toThrow();
            expect(()=>groove.setGroove(new pdg.Point(9,9),new pdg.Point(9,9))).toThrow();
            expect(()=>groove.setGroove(new pdg.Point(9,9),{x:NaN,y:0})).toThrow();
            expect(groove.getGrooveStart().x).toBe(-2);expect(groove.getGrooveEnd().x).toBe(4);
            const pivot=a.createPivotJoint(b);pivot.setAnchors(new pdg.Point(2,1),new pdg.Point(-1,2));
            const writer=new pdg.Serializer();writer.setResourceMode(mode);source.serialize(writer);
            const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());const copy=new pdg.Sprite();copy.deserialize(reader);
            const restored=copy.physics.getConstraint(0),restoredPivot=copy.physics.getConstraint(1);
            expect(restored.getGrooveStart().x).toBe(-2);expect(restored.getGrooveEnd().y).toBe(3);
            expect(restored.getAnchorB().x).toBe(.5);expect(restored.getAnchorB().y).toBe(1);
            expect(restored).toBe(copy.findPart('slider').physics.getConstraint(0));
            expect(restoredPivot.getAnchorA().x).toBe(2);expect(restoredPivot.getAnchorB().y).toBe(2);
            copy.physics.disconnect();a.disconnect();
        }
    });
    it('follows editable Part artwork and snapshots the source without replacing handles', function() {
        const owner=new pdg.Sprite(),part=owner.createPart('art').setLocation(10,20);
        const collider=part.setupFrameCollider(pdg.frameCollider_Bounds);
        expect(collider).toBe(part.collider);expect(collider.getShapeCount()).toBe(0);
        for(const bad of [-1,.5,256,NaN,Infinity,'128'])
            expect(()=>part.setupFrameCollider(pdg.frameCollider_Bounds,bad)).toThrow();
        expect(()=>part.setupFrameCollider(.5)).toThrow();
        expect(()=>part.setupAnimationCollider()).toThrow();
        if(typeof part.setDrawing!=='function')return;
        const drawing=pdg.createDrawing();
        const rect=drawing.addRect(new pdg.Rect(-2,-3,4,5),new pdg.Attributes());
        part.setDrawing(drawing);const id=collider.getShapeId(0);
        expect(collider.getBounds().left).toBeCloseTo(8,5);
        rect.setAttributes(new pdg.Attributes().translation(new pdg.Offset(3,0)));
        expect(collider.getBounds().left).toBeCloseTo(11,5);expect(collider.getShapeId(0)).toBe(id);
        expect(()=>part.setupFrameCollider()).toThrow();expect(part.collider).toBe(collider);
        for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
            const writer=new pdg.Serializer();writer.setResourceMode(mode);owner.serialize(writer);
            const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());
            const copy=new pdg.Sprite();copy.deserialize(reader);const restored=copy.findPart('art');
            expect(restored.collider.getGeometrySource()).toBe(pdg.colliderSource_Frame);
            expect(restored.collider.getBounds().left).toBeCloseTo(11,5);
            restored.clearContent();expect(restored.collider.getShapeCount()).toBe(0);
        }
    });
    function assign(owner, value) { 'use strict'; owner.collider = value; }
    it('restores shared collider and constraint graphs in both resource modes', function() {
        for (const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
            const source=new pdg.Sprite(),root=source.createPart('root'),child=source.createPart('child');
            child.setParentPart(root).setLocation(8,0);
            const a=root.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic),b=child.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic);
            const joint=a.createRotaryLimit(b,-.4,.7);child.setIKLimits(joint);
            const collider=child.setupCollider().setCircle(2).setPhysicsBody(a).setSensor(true).setGroup(17);
            const shape=collider.getShapeId(0);
            const writer=new pdg.Serializer();writer.setResourceMode(mode);source.serialize(writer);
            const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());const copy=new pdg.Sprite();copy.deserialize(reader);
            const r=copy.findPart('root'),c=copy.findPart('child'),restored=c.collider;
            expect(restored.getShapeId(0)).toBe(shape);expect(restored.getGroup()).toBe(17);expect(restored.isSensor()).toBe(true);
            expect(restored.getPhysicsBody()).toBe(r.physics);
            const link=r.physics.getConstraint(0);expect(link).toBe(c.physics.getConstraint(0));expect(link.getBodyB()).toBe(c.physics);
            expect(c.getIKMaxAngle()).toBeCloseTo(.7,6);link.setAngleLimits(-.2,.5);expect(c.getIKMaxAngle()).toBe(.5);
            c.clearIKLimits();r.physics.disconnect();root.clearIKLimits();child.clearIKLimits();a.disconnect();
        }
    });
    it('creates exact capsules with stable shape IDs and copied local endpoints', function() {
        const sprite=new pdg.Sprite(), c=sprite.setupCollider();
        const start=new pdg.Point(-3,0),end=new pdg.Point(3,0);
        expect(c.setCapsule(start,end,1)).toBe(c);
        const id=c.getShapeId(0);
        expect(c.getShapeType(id)).toBe(pdg.collisionShape_Capsule);
        expect(c.getCapsuleStart(id).x).toBe(-3);expect(c.getCapsuleEnd(id).x).toBe(3);
        expect(c.getCapsuleStart(id) instanceof pdg.Point).toBe(true);
        expect(c.getCapsuleEnd(id) instanceof pdg.Point).toBe(true);
        expect(c.getCapsuleRadius(id)).toBe(1);expect(c.getBounds().right).toBe(4);
        start.x=100;const returned=c.getCapsuleEnd(id);returned.x=100;
        expect(c.getCapsuleStart(id).x).toBe(-3);expect(c.getCapsuleEnd(id).x).toBe(3);
        expect(c.contains(new pdg.Point(3.99,.04))).toBe(true);
        expect(c.contains(new pdg.Point(3.8,.8))).toBe(false);
        const second=c.addCapsule(new pdg.Point(0,-4),new pdg.Point(0,4),.25);
        expect(c.getShapeCount()).toBe(2);expect(c.getShapeId(0)).toBe(id);
        expect(c.removeShape(second)).toBe(true);
        const circle=c.addCircle(1);
        expect(()=>c.getCapsuleRadius(circle)).toThrow();expect(()=>c.getCircleRadius(id)).toThrow();
        for(const value of [0,-1,NaN,Infinity]) expect(()=>c.setCapsule(start,end,value)).toThrow();
        expect(()=>c.addCapsule({x:NaN,y:0},end,1)).toThrow();
        for(const value of [-1,.5,NaN,999]) expect(()=>c.getCapsuleStart(value)).toThrow();
        expect(c.getShapeId(0)).toBe(id);expect(c.getShapeCount()).toBe(2);
        expect(pdg.Collider.NoCollider.addCapsule(start,end,1)).toBe(pdg.collisionShape_None);
        expect(pdg.Collider.NoCollider.setCapsule(start,end,1)).toBe(pdg.Collider.NoCollider);
        c.setCapsule(end,end,1);expect(c.contains(new pdg.Point(4,0))).toBe(true);
        expect(c.getShapeType(c.getShapeId(0))).toBe(pdg.collisionShape_Capsule);
    });
    it('uses capsules on Parts and Particle templates with transformed queries', function() {
        const sprite=new pdg.Sprite().setLocation(10,20),part=sprite.createPart('limb');
        part.setScale(-2,2);
        const c=part.setupCollider().setCapsule(new pdg.Point(-3,0),new pdg.Point(3,0),1);
        expect(c.contains(new pdg.Point(17.5,20))).toBe(true);
        expect(c.contains(new pdg.Point(17.6,21.6))).toBe(false);
        part.setScale(2,1);expect(c.getBounds().right).toBeCloseTo(18,5);
        const particle=new pdg.Particle();particle.setupCollider().setCapsule(new pdg.Point(0,-3),new pdg.Point(0,3),.5);
        const layer=pdg.createSpriteLayer();
        try {
            const emitter=layer.createParticleEmitter().setParticleTemplate(particle);emitter.emit(2);
            const a=layer.getNthParticle(0).collider,b=layer.getNthParticle(1).collider;
            expect(a.overlaps(b)).toBe(true);expect(a===b).toBe(false);
            expect(a.getCapsuleRadius(a.getShapeId(0))).toBe(.5);
        } finally {pdg.cleanupLayer(layer);}
    });
    it('round-trips capsule geometry and IDs in both resource modes', function() {
        for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
            const source=new pdg.Sprite(),part=source.createPart('limb');
            const c=part.setupCollider().setCapsule(new pdg.Point(-2.125,3.5),new pdg.Point(7.75,-4.25),.875);
            const id=c.getShapeId(0);c.addCircle(2);
            const writer=new pdg.Serializer();writer.setResourceMode(mode);source.serialize(writer);
            const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());const copy=new pdg.Sprite();copy.deserialize(reader);
            const restored=copy.findPart('limb').collider;
            expect(restored.getShapeId(0)).toBe(id);expect(restored.getShapeType(id)).toBe(pdg.collisionShape_Capsule);
            expect(restored.getCapsuleStart(id).x).toBe(-2.125);expect(restored.getCapsuleEnd(id).y).toBe(-4.25);
            expect(restored.getCapsuleRadius(id)).toBe(.875);expect(restored.getShapeCount()).toBe(2);
        }
    });
    it('shares read-only absence across Sprite and Part without physics', function() {
        const sprite = new pdg.Sprite(), part = sprite.createPart('sensor');
        expect(sprite.collider).toBe(pdg.Collider.NoCollider);
        expect(part.collider).toBe(sprite.collider);
        expect(sprite.collider.setCircle(3)).toBe(pdg.Collider.NoCollider);
        expect(sprite.collider.getShapeCount()).toBe(0);
        expect(sprite.physics).toBe(pdg.PhysicsBody.NoPhysics);
        expect(()=>new pdg.Collider()).toThrow();
        const collider=part.setupCollider();
        expect(collider).toBe(part.collider);expect(part.setupCollider()).toBe(collider);
        expect(()=>assign(part,collider)).toThrow();
        expect(()=>assign(sprite,pdg.Collider.NoCollider)).toThrow();
        expect(new pdg.Animated().collider).toBeUndefined();
        expect(new pdg.AnimatedAttributes().collider).toBeUndefined();
    });
    it('queries shapes through owner transforms and preserves stable IDs', function() {
        const sprite=new pdg.Sprite(), part=sprite.createPart('offset');
        sprite.setLocation(10,20);part.setLocation(5,0);
        const c=part.setupCollider().setCircle(2), id=c.getShapeId(0);
        expect(c.contains(new pdg.Point(15,20))).toBe(true);
        expect(c.contains(new pdg.Point(19,20))).toBe(false);
        expect(c.getBounds().left).toBeCloseTo(13,4);
        c.addBox(new pdg.Rect(-1,-1,1,1));expect(c.getShapeId(0)).toBe(id);
        expect(()=>c.addPolygon([new pdg.Point(0,0),new pdg.Point(1,1),new pdg.Point(0,1),new pdg.Point(1,0)])).toThrow();
        expect(c.getShapeCount()).toBe(2);
        expect(c.removeShape(id)).toBe(true);expect(c.removeShape(id)).toBe(false);
        c.clearShapes().addPolygon([new pdg.Point(0,0),new pdg.Point(2,0),new pdg.Point(0,2)]);
        expect(c.contains(new pdg.Point(15.25,20.25))).toBe(true);
        part.removeCollider();expect(part.collider).toBe(pdg.Collider.NoCollider);
        expect(c.isAttached()).toBe(false);expect(c.contains(new pdg.Point(15.25,20.25))).toBe(true);
    });
    it('shares body-to-body constraints across owner types and preserves retained handles', function() {
        const sprite=new pdg.Sprite(), part=sprite.createPart('body');
        const a=sprite.setupPhysicsBody(), b=part.setupPhysicsBody();
        const joint=a.createPinJoint(b);
        expect(joint instanceof pdg.PhysicsConstraint).toBe(true);
        expect(()=>new pdg.PhysicsConstraint()).toThrow();
        expect(joint.getBodyA()).toBe(a);expect(joint.getBodyB()).toBe(b);
        expect(a.getConstraint(0)).toBe(joint);expect(b.getConstraint(0)).toBe(joint);
        expect(joint.setMaxForce(10).setBreakForce(8).setCollideBodies(true)).toBe(joint);
        expect(joint.getType()).toBe(pdg.constraint_Pin);expect(joint.getCollideBodies()).toBe(true);
        part.removePhysicsBody();expect(joint.isActive()).toBe(false);
        expect(joint.getBodyA()).toBe(pdg.PhysicsBody.NoPhysics);
        expect(a.getConstraintCount()).toBe(0);joint.disconnect();
        expect(()=>a.createPinJoint(pdg.PhysicsBody.NoPhysics)).toThrow();
        expect(()=>a.createPinJoint(a)).toThrow();
    });
    it('creates every constraint family with the same body endpoints', function() {
        const ownerA=new pdg.Sprite(), ownerB=new pdg.Sprite();
        const a=ownerA.setupPhysicsBody(), b=ownerB.setupPhysicsBody();
        const p=new pdg.Point(0,0), q=new pdg.Point(1,0);
        const joints=[a.createPinJoint(b),a.createPivotJoint(b),a.createSlideJoint(b,p,p,1,2),
            a.createGrooveJoint(b,p,q,p),a.createSpring(b,p,p,1,2,.5),a.createRotarySpring(b,0,2,.5),
            a.createRotaryLimit(b,-1,1),a.createRatchet(b,.5),a.createGear(b,2),a.createMotor(b,1,4)];
        expect(a.getConstraintCount()).toBe(10);
        joints.forEach(joint=>{expect(joint.isActive()).toBe(true);expect(joint.getBodyA()).toBe(a);});
        a.disconnect(b);expect(a.getConstraintCount()).toBe(0);expect(b.getConstraintCount()).toBe(0);
        joints.forEach(joint=>expect(joint.isActive()).toBe(false));
    });
    it('rejects invalid handles and integer filters without corrupting geometry', function() {
        const sprite=new pdg.Sprite(), c=sprite.setupCollider().setCircle(2), body=sprite.setupPhysicsBody();
        for(const value of [-1,.5,4294967296,NaN,Infinity,'1']) {
            expect(()=>c.setCategory(value)).toThrow();expect(()=>c.setCollisionMask(value)).toThrow();
            expect(()=>c.setGroup(value)).toThrow();expect(()=>c.removeShape(value)).toThrow();
            expect(()=>c.getShapeId(value)).toThrow();expect(()=>body.getConstraint(value)).toThrow();
        }
        expect(()=>c.overlaps({})).toThrow();expect(()=>c.overlaps(body)).toThrow();expect(()=>c.setPhysicsBody({})).toThrow();
        expect(()=>body.createPinJoint(null,new pdg.Point(0,0))).toThrow();expect(()=>body.createPinJoint(c)).toThrow();
        expect(()=>c.addPolygon([new pdg.Point(0,0),null,new pdg.Point(1,1)])).toThrow();
        expect(c.getShapeCount()).toBe(1);expect(c.getCategory()).toBe(1);
        for(const bad of [-1,.5,256,NaN,Infinity,'128']) {
            expect(()=>sprite.setupFrameCollider(pdg.frameCollider_Bounds,bad)).toThrow();
        }
        expect(()=>sprite.setupFrameCollider(.5)).toThrow();expect(c.getGeometrySource()).toBe(pdg.colliderSource_Explicit);
    });
    it('reports sensor contacts with shared identities on the owning Sprite', function(done) {
        const layer=pdg.createSpriteLayer();layer.enableCollisions();
        const owner=layer.createSprite(), obstacle=layer.createSprite();
        const part=owner.createPart('sensor');
        const c=part.setupCollider().setCircle(2).setSensor(true).setWantsContactEvents(true);
        const other=obstacle.setupCollider().setCircle(2);
        let events=0;
        const handler=new pdg.IEventHandler(function(event) {
            if(event.phase===pdg.collision_Begin) {
                ++events;expect(event.collider).toBe(c);expect(event.other).toBe(other);
                expect(event.shape).toBe(c.getShapeId(0));expect(event.sensor).toBe(true);
                expect(typeof event.point.x).toBe('number');expect(event.impulse.x).toBe(0);
            }
            return true;
        });
        owner.addHandler(handler,pdg.eventType_ColliderContact);
        setTimeout(function() { try { expect(events).toBe(1);expect(owner.physics).toBe(pdg.PhysicsBody.NoPhysics); }
            finally {pdg.cleanupLayer(layer);done();} },150);
    });
    it('keeps concave polygon gaps and accepts Polygon objects in both winding orders', function() {
        const owner=new pdg.Sprite(),c=owner.setupCollider();
        const points=[[0,0],[6,0],[6,6],[4,6],[4,2],[2,2],[2,6],[0,6]].map(p=>new pdg.Point(p[0],p[1]));
        const polygon=new pdg.Polygon(points);
        expect(c.setPolygon(polygon)).toBe(c);
        expect(c.getShapeCount()).toBe(1);
        expect(c.contains(new pdg.Point(1,4))).toBe(true);
        expect(c.contains(new pdg.Point(3,4))).toBe(false);
        c.setPolygon(points.reverse());
        expect(c.contains(new pdg.Point(5,4))).toBe(true);
        expect(c.contains(new pdg.Point(3,4))).toBe(false);
    });
    it('preserves frame sources under additions, removals and resizing', function() {
        const owner=new pdg.Sprite();owner.setSize(4,6);
        const c=owner.setupFrameCollider(pdg.frameCollider_Bounds),source=c.getShapeId(0);
        expect(c).toBe(owner.collider);
        const added=c.addPolygon([new pdg.Point(10,0),new pdg.Point(12,0),new pdg.Point(10,2)]);
        owner.setSize(8,10);
        expect(c.getGeometrySource()).toBe(pdg.colliderSource_Frame);
        expect(c.getShapeCount()).toBe(2);expect(c.getShapeId(0)).toBe(source);
        expect(c.contains(new pdg.Point(-3,0))).toBe(true);
        expect(()=>c.removeShape(source)).toThrow();expect(c.removeShape(added)).toBe(true);
        c.setPolygon([new pdg.Point(0,0),new pdg.Point(2,0),new pdg.Point(0,2)]);
        expect(c.getGeometrySource()).toBe(pdg.colliderSource_Explicit);
        expect(owner.enableCollisions).toBeUndefined();expect(owner.setCollisionRadius).toBeUndefined();
    });

    [false,true].forEach(function(chipmunk) {
        it('filters contacts and delivers callbacks with '+(chipmunk?'Chipmunk':'basic'), function(done) {
            const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(chipmunk);layer.enableCollisions();
            const a=layer.createSprite(),b=layer.createSprite();a.setupPhysicsBody();b.setupPhysicsBody();
            const c=a.setupCollider().setCircle(2).setSensor(true),other=b.setupCollider().setCircle(2);
            let allow=false,filtered=0,begins=0;
            c.setCollisionFilter(function(self,peer) {
                expect(self).toBe(c);expect(peer).toBe(other);++filtered;return allow;
            });
            c.setContactHandler(function(event) {
                expect(event.collider).toBe(c);expect(event.other).toBe(other);
                expect(event.shape).toBe(c.getShapeId(0));
                if(event.phase===pdg.collision_Begin)++begins;
            });
            for(const bad of [3,{},'callback']) {
                expect(()=>c.setContactHandler(bad)).toThrow();expect(()=>c.setCollisionFilter(bad)).toThrow();
            }
            setTimeout(function() {
                expect(filtered).toBeGreaterThan(0);expect(begins).toBe(0);allow=true;
                setTimeout(function() {
                    try {expect(begins).toBe(1);expect(c.setContactHandler(null)).toBe(c);expect(c.setCollisionFilter(null)).toBe(c);}
                    finally {pdg.cleanupLayer(layer);done();}
                },80);
            },80);
        });
    });

});
