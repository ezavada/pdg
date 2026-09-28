describe('Part', function() {
    it('transfers retained Parts, bodies and internal joints between owners', function() {
        const source=new pdg.Sprite(),destination=new pdg.Sprite();
        source.setLocation(new pdg.Point(30,40));destination.setLocation(new pdg.Point(-10,20));destination.setScale(2);
        destination.createPart('existing');destination.createPart('spare');
        const arm=source.createPart('arm'),hand=source.createPart('hand'),stay=source.createPart('stay');
        hand.setParentPart(arm).setLocation(new pdg.Point(4,0));
        arm.setupPhysicsBody(3,5).setVelocity(2,1);hand.setupPhysicsBody(2,3);stay.setupPhysicsBody();
        arm.setupCollider().setCircle(.5);
        let drawing;
        if(typeof arm.setDrawing==='function') {
            drawing=pdg.createDrawing();drawing.addRect(new pdg.Rect(0,0,2,3),new pdg.Attributes());arm.setDrawing(drawing);
        }
        const internal=arm.physics.createPivotJoint(hand.physics),boundary=stay.physics.createPivotJoint(arm.physics);
        const id=arm.getId(),body=arm.physics,collider=arm.collider,world=arm.getTransform(pdg.partSpace_World);
        expect(destination.transferPart(arm)).toBe(arm);
        expect(arm.getSprite()).toBe(destination);expect(hand.getSprite()).toBe(destination);
        expect(source.getPart(id)).toBe(null);expect(destination.getPart(arm.getId())).toBe(arm);expect(arm.getId()).not.toBe(id);
        expect(arm.physics).toBe(body);expect(arm.collider).toBe(collider);
        expect(internal.isActive()).toBe(true);expect(boundary.isActive()).toBe(false);
        expect(arm.getTransform(pdg.partSpace_World).tx).toBeCloseTo(world.tx,5);expect(body.getVelocity().x).toBe(2);
        source.clearParts();expect(body.isAttached()).toBe(true);
        if(drawing) {
            drawing.addRect(new pdg.Rect(0,0,7,8),new pdg.Attributes());
            expect(arm.getContentBounds().right).toBe(7);
        }
        const writer=new pdg.Serializer();destination.serialize(writer);const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());
        const copy=new pdg.Sprite();copy.deserialize(reader);
        expect(copy.findPart('hand').getParentPart()).toBe(copy.findPart('arm'));
        expect(copy.findPart('arm').physics.getConstraintCount()).toBe(1);
        destination.clearParts();copy.clearParts();
    });
    it('validates transfers before changing ownership and supports a single Part', function() {
        const a=new pdg.Sprite(),b=new pdg.Sprite(),arm=a.createPart('arm'),hand=a.createPart('hand');
        arm.setLocation(new pdg.Point(10,20));hand.setParentPart(arm).setLocation(new pdg.Point(3,4));
        b.createPart('arm');expect(()=>b.transferPart(arm)).toThrow();expect(arm.getSprite()).toBe(a);expect(hand.getParentPart()).toBe(arm);
        b.clearParts();expect(()=>b.transferPart(null,false)).toThrow();expect(()=>b.transferPart(arm,'yes')).toThrow();
        expect(b.transferPart(arm,false)).toBe(arm);expect(hand.getSprite()).toBe(a);expect(hand.getParentPart()).toBe(null);
        expect(hand.getTransform(pdg.partSpace_World).tx).toBeCloseTo(13,5);
        expect(b.transferPart(arm)).toBe(arm);a.clearParts();b.clearParts();
    });
    it('is Animated, factory-owned and safe to query without bones', function() {
        const sprite=new pdg.Sprite(), part=sprite.createPart('hand');
        expect(part instanceof pdg.Part).toBe(true);
        expect(part instanceof pdg.Animated).toBe(true);
        expect(part.getSprite()).toBe(sprite);
        expect(sprite.getPart(part.getId())).toBe(part);
        expect(sprite.findPart('hand')).toBe(part);
        expect(sprite.findPart('missing')).toBe(null);
        expect(sprite.getPartCount()).toBe(1);
        expect(()=>sprite.removePart(.5)).toThrow();expect(sprite.getPartCount()).toBe(1);
        expect(sprite.getPartNames()).toEqual(['hand']);
        expect(part.getBoneId()).toBe(pdg.boneId_None);
        expect(part.isBoundToBone()).toBe(false);
        expect(()=>new pdg.Part()).toThrow();
        expect(()=>sprite.createPart('hand')).toThrow();
        expect(()=>sprite.createPart('')).toThrow();
        expect(()=>part.bindToBone(0)).toThrow();
        expect(()=>part.bindToBone(0.5)).toThrow();
        expect(part.bindToBone(pdg.boneId_None)).toBe(part);
        sprite.clearParts();
    });
    it('composes local, Sprite and owning-layer transforms', function() {
        const sprite=new pdg.Sprite(),hand=sprite.createPart('hand'),tip=sprite.createPart('tip');
        sprite.moveTo(100,200);sprite.setRotation(Math.PI/2);
        hand.moveTo(10,0);hand.setMovement(4,0);hand.animate(.25);
        tip.setParentPart(hand);tip.moveTo(2,0);
        expect(hand.getMovement() instanceof pdg.Offset).toBe(true);
        expect(tip.getTransform().tx).toBe(2);
        expect(tip.getTransform(pdg.partSpace_Sprite).tx).toBeCloseTo(13,5);
        const world=tip.getTransform(pdg.partSpace_World);
        expect(world.tx).toBeCloseTo(100,4);expect(world.ty).toBeCloseTo(213,4);
        world.tx=999;expect(tip.getTransform(pdg.partSpace_World).tx).toBeCloseTo(100,4);
        expect(()=>hand.setParentPart(tip)).toThrow();
        expect(hand.getParentPart()).toBe(null);
        const other=new pdg.Sprite(), foreign=other.createPart('foreign');
        expect(()=>hand.setParentPart(foreign)).toThrow();
        ['world',1.5,NaN,Infinity,3].forEach(space=>expect(()=>hand.getTransform(space)).toThrow());
        tip.setParentPart();expect(tip.getTransform(pdg.partSpace_Sprite).tx).toBe(2);
        sprite.clearParts();other.clearParts();
    });
    it('detaches retained references without reusing their identity', function() {
        const sprite=new pdg.Sprite(),old=sprite.createPart('hand'),child=sprite.createPart('child');
        child.setParentPart(old);old.moveTo(12,34);
        const id=old.getId();expect(sprite.removePart(id)).toBe(true);
        expect(sprite.removePart(id)).toBe(false);
        expect(old.getSprite()).toBe(null);expect(old.isAttached()).toBe(false);
        expect(old.getBoneId()).toBe(pdg.boneId_None);
        expect(old.getLocation().x).toBe(12);expect(child.getParentPart()).toBe(null);
        const replacement=sprite.createPart('hand');expect(replacement.getId()).not.toBe(id);
        expect(sprite.getPart(id)).toBe(null);expect(old.getName()).toBe('hand');
        old.setMovement(8,0);old.animate(.25);expect(old.getLocation().x).toBeCloseTo(14,5);
        sprite.clearParts();expect(child.isAttached()).toBe(false);expect(replacement.isAttached()).toBe(false);
    });
    (typeof pdg.Part.prototype.setDrawing === 'function' ? it : xit)('retains editable Drawing contents through removal and replacement', function() {
        const sprite=new pdg.Sprite(),part=sprite.createPart('art'),drawing=pdg.createDrawing();
        const e=drawing.addRect(new pdg.Rect(0,0,10,20),new pdg.Attributes().fillColor(new pdg.Color(1,0,0)));
        const id=part.getId();part.setLocation(new pdg.Point(3,4));part.setScale(2,3);
        expect(part.setDrawing(drawing)).toBe(part);expect(part.hasContent()).toBe(true);
        expect(part.getContentBounds().right).toBeCloseTo(10,5);
        expect(part.getContentBounds(pdg.partSpace_Sprite).right).toBeCloseTo(23,5);
        drawing.addRect(new pdg.Rect(0,0,30,40),new pdg.Attributes());
        expect(part.getContentBounds().right).toBeCloseTo(30,5);
        sprite.removePart(id);expect(part.hasContent()).toBe(true);expect(part.getLocation().x).toBe(3);
        part.clearContent();expect(part.hasContent()).toBe(false);expect(part.getId()).toBe(id);
        expect(()=>part.getContentBounds(4)).toThrow();
    });

    it('uses animated mounting Parts for retained Sprite attachments', function() {
        const layer=pdg.createSpriteLayer();
        try {
            const child=layer.createSprite(),host=layer.createSprite();host.setLocation(new pdg.Point(10,20));host.setScale(2);
            const socket=host.createPart('socket');socket.setLocation(new pdg.Point(4,5));
            const grip=child.createPart('grip');grip.setLocation(new pdg.Point(3,0));
            const mount=socket.attachSprite(child,pdg.partPlacement_Snap,grip);
            expect(child.getAttachmentPart()).toBe(mount);expect(mount.getAttachedSprite()).toBe(child);
            expect(child.getLocation().x).toBeCloseTo(12,5);expect(child.getScale().x).toBeCloseTo(2,5);
            mount.setMovement(4,0);mount.animate(.5);expect(child.getLocation().x).toBeCloseTo(16,5);
            expect(()=>child.moveTo(99,0)).toThrow();expect(child.getLocation().x).toBeCloseTo(16,5);
            expect(()=>grip.attachSprite(host)).toThrow();expect(()=>child.setupPhysicsBody()).toThrow();
            mount.detachSprite();expect(child.getAttachmentPart()).toBe(null);expect(child.getLocation().x).toBeCloseTo(16,5);
            const preserved=socket.attachSprite(child,pdg.partPlacement_PreserveWorld,grip);
            expect(child.getLocation().x).toBeCloseTo(16,5);
            host.removePart(socket.getId());expect(preserved.getAttachedSprite()).toBe(null);expect(child.getAttachmentPart()).toBe(null);
            const singular=host.createPart('singular');singular.setScale(0,1);const count=host.getPartCount();
            expect(()=>singular.attachSprite(child)).toThrow();expect(host.getPartCount()).toBe(count);
        } finally { pdg.cleanupLayer(layer); }
    });

    it('retains nested mounts across removal, transfer and layer destruction', function() {
        const first=pdg.createSpriteLayer(),second=pdg.createSpriteLayer();
        let secondAlive=true;
        try {
            const child=first.createSprite(),host=first.createSprite(),tip=first.createSprite();
            const socket=host.createPart('hand'),mount=socket.attachSprite(child);
            const nested=child.createPart('tip').attachSprite(tip);
            expect(()=>first.removeSprite(child)).toThrow();
            expect(()=>second.addSprite(tip)).toThrow();
            expect(first.hasSprite(child)).toBe(true);expect(second.getNthSprite(0)).toBe(null);
            first.removeSprite(host);
            expect(first.getNthSprite(0)).toBe(null);expect(child.getAttachmentPart()).toBe(mount);
            host.setLocation(new pdg.Point(15,30));expect(tip.getLocation().x).toBe(15);
            second.addSprite(host);
            expect(second.getNthSprite(0)).toBe(host);expect(second.getNthSprite(1)).toBe(child);
            expect(second.getNthSprite(2)).toBe(tip);
            first.addSprite(host);expect(second.getNthSprite(0)).toBe(null);expect(first.hasSprite(tip)).toBe(true);
            first.removeAllSprites();expect(nested.getAttachedSprite()).toBe(tip);
            second.addSprite(host);pdg.cleanupLayer(second);secondAlive=false;
            expect(mount.getAttachedSprite()).toBe(child);expect(nested.getAttachedSprite()).toBe(tip);
            mount.detachSprite();expect(child.getAttachmentPart()).toBe(null);
            nested.detachSprite();
        } finally { pdg.cleanupLayer(first);if(secondAlive)pdg.cleanupLayer(second); }
    });

    it('mounts kinematic bodies with one transform owner and releases that restriction on detach', function() {
        const host=new pdg.Sprite(),child=new pdg.Sprite();
        child.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic);
        child.physics.setVelocity(40,0);const hand=host.createPart('hand');hand.setLocation(new pdg.Point(3,0));
        const mount=hand.attachSprite(child);
        expect(child.physics.getState().x).toBe(3);expect(child.physics.getVelocity().x).toBe(0);
        expect(()=>child.physics.setMode(pdg.physicsBody_Dynamic)).toThrow();
        expect(child.physics.getMode()).toBe(pdg.physicsBody_Kinematic);
        expect(()=>child.physics.teleport(new pdg.Point(100,0),0)).toThrow();
        expect(()=>child.physics.setVelocity(1,0)).toThrow();expect(()=>child.physics.setAngularVelocity(1)).toThrow();
        host.setLocation(new pdg.Point(10,20));mount.setLocation(new pdg.Point(2,0));
        expect(child.getLocation().x).toBe(15);expect(child.physics.getState().x).toBe(15);
        mount.detachSprite();child.physics.setMode(pdg.physicsBody_Dynamic);child.physics.teleport(new pdg.Point(5,6),0);
        expect(child.getLocation().x).toBe(5);host.clearParts();child.removePhysicsBody();
    });

    it('keeps dynamic Parts in world space as programmed ancestors change', function() {
        const sprite=new pdg.Sprite(),child=sprite.createPart('child'),parent=sprite.createPart('parent');
        child.setParentPart(parent);child.setLocation(new pdg.Point(4,5));child.setupPhysicsBody();
        parent.setLocation(new pdg.Point(10,20));sprite.setLocation(new pdg.Point(100,200));
        parent.setRotation(.5);parent.setScale(2,-3);
        expect(child.getTransform(pdg.partSpace_World).tx).toBeCloseTo(4,4);
        expect(child.getTransform(pdg.partSpace_World).ty).toBeCloseTo(5,4);
        child.physics.setMode(pdg.physicsBody_Kinematic);child.moveTo(30,0,1);child.setMovement(4,0);
        child.physics.setMode(pdg.physicsBody_Dynamic);expect(child.hasScheduledAnimations()).toBe(false);expect(child.getMovement().x).toBe(0);
        sprite.clearParts();
    });

    it('solves explicit Part chains without bones and rejects competing dynamic physics', function() {
        const s=new pdg.Sprite();s.setLocation(new pdg.Point(10,20));s.setScale(2,-3);
        const root=s.createPart('root'),mid=s.createPart('middle'),tip=s.createPart('tip');
        mid.setParentPart(root);tip.setParentPart(mid);mid.setLocation(new pdg.Point(10,0));tip.setLocation(new pdg.Point(8,0));
        expect(root.solveIK(mid,tip,new pdg.Point(30,-4))).toBe(true);
        expect(tip.getTransform(pdg.partSpace_World).tx).toBeCloseTo(30,4);
        expect(tip.getTransform(pdg.partSpace_World).ty).toBeCloseTo(-4,4);
        expect(root.getBoneId()).toBe(pdg.boneId_None);
        expect(root.solveIK(mid,tip,new pdg.Point(100,0),pdg.partSpace_Local)).toBe(false);
        const angle=root.getRotation();expect(()=>root.solveIK(tip,mid,new pdg.Point(0,0))).toThrow();expect(root.getRotation()).toBe(angle);
        mid.setupPhysicsBody();expect(()=>root.solveIK(mid,tip,new pdg.Point(0,0))).toThrow();expect(root.getRotation()).toBe(angle);
        mid.physics.setMode(pdg.physicsBody_Kinematic);expect(root.solveIK(mid,tip,new pdg.Point(10,8),pdg.partSpace_Local,-1)).toBe(true);
        s.clearParts();
    });

    it('limits local IK angles and preserves the range in snapshots', function() {
        const sprite=new pdg.Sprite(),root=sprite.createPart('root'),middle=sprite.createPart('middle'),tip=sprite.createPart('tip');
        middle.setParentPart(root).setLocation(10,0);tip.setParentPart(middle).setLocation(8,0);
        expect(root.setIKLimits(0,0)).toBe(root);expect(middle.setIKLimits(0,.2)).toBe(middle);
        expect(root.hasIKLimits()).toBe(true);expect(middle.getIKMaxAngle()).toBe(.2);
        expect(root.solveIK(middle,tip,new pdg.Point(10,8))).toBe(false);
        expect(root.getRotation()).toBe(0);expect(middle.getRotation()).toBeCloseTo(.2,5);
        [[1,-1],[0,7],[NaN,1],[0,Infinity],[null,1],["0",1],[Number.MAX_VALUE,Number.MAX_VALUE]].forEach(range=>expect(()=>root.setIKLimits(...range)).toThrow());
        expect(root.getIKMinAngle()).toBe(0);expect(root.getIKMaxAngle()).toBe(0);
        [pdg.serialization_Complete,pdg.serialization_ExternalReferences].forEach(function(mode) {
            const writer=new pdg.Serializer();writer.setResourceMode(mode);sprite.serialize(writer);
            const copy=new pdg.Sprite(),reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());copy.deserialize(reader);
            expect(copy.findPart('root').hasIKLimits()).toBe(true);
            expect(copy.findPart('middle').getIKMaxAngle()).toBe(.2);
        });
        expect(root.clearIKLimits()).toBe(root);middle.clearIKLimits();
        expect(root.hasIKLimits()).toBe(false);expect(root.solveIK(middle,tip,new pdg.Point(10,8))).toBe(true);
    });
    it('shares live rotary limits with IK and suspends on disconnect', function() {
        const s=new pdg.Sprite(),root=s.createPart('root'),middle=s.createPart('middle'),tip=s.createPart('tip');
        middle.setParentPart(root).setLocation(10,0);tip.setParentPart(middle).setLocation(8,0);
        const a=root.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic),b=middle.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic);
        root.setIKLimits(0,0);
        const limit=a.createRotaryLimit(b,0,.2);
        expect(middle.setIKLimits(limit)).toBe(middle);
        root.solveIK(middle,tip,new pdg.Point(10,8));expect(middle.getRotation()).toBeCloseTo(.2,5);
        expect(limit.setAngleLimits(.4,.4)).toBe(limit);expect(limit.getMinAngle()).toBe(.4);expect(limit.getMaxAngle()).toBe(.4);
        expect(middle.getIKMaxAngle()).toBe(.4);
        root.setIKTarget(middle,tip,new pdg.Point(10,8));root.animate(.01);
        expect(middle.getRotation()).toBeCloseTo(.4,5);
        [{},a,2].forEach(value=>expect(()=>middle.setIKLimits(value)).toThrow());
        [[1,0],[NaN,1],[0,Infinity],[null,1],['0',1]].forEach(values=>expect(()=>limit.setAngleLimits(...values)).toThrow());
        const pivot=a.createPivotJoint(b,new pdg.Point(10,0));
        expect(()=>pivot.getMinAngle()).toThrow();expect(()=>pivot.setAngleLimits(0,1)).toThrow();expect(()=>middle.setIKLimits(pivot)).toThrow();
        expect(()=>root.setIKLimits(limit)).toThrow();expect(middle.getIKMinAngle()).toBe(.4);
        limit.disconnect();root.animate(.01);
        expect(middle.hasIKLimits()).toBe(true);expect(()=>middle.getIKMinAngle()).toThrow();expect(root.getIKError()).not.toBe('');
        const reverse=b.createRotaryLimit(a,-.8,-.1);middle.setIKLimits(reverse);
        expect(middle.getIKMinAngle()).toBe(.1);expect(middle.getIKMaxAngle()).toBe(.8);
        root.animate(.01);expect(root.getIKError()).toBe('');
        middle.clearIKLimits();expect(reverse.isActive()).toBe(true);
        root.clearIKTarget();s.clearParts();
    });
    [false,true].forEach(function(native) {
        it('drives a dynamic Part chain with '+(native?'Chipmunk':'basic')+' without teleporting it', function(done) {
            const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(native);layer.setGravity(0);layer.setDamping(1);
            const sprite=layer.createSprite(),root=sprite.createPart('root'),middle=sprite.createPart('middle'),tip=sprite.createPart('tip');
            middle.setParentPart(root).setLocation(10,0);tip.setParentPart(middle).setLocation(8,0);
            const a=root.setupPhysicsBody(1,20),b=middle.setupPhysicsBody(1,20);
            expect(root.setIKDriveTarget(middle,tip,new pdg.Point(10,8),3000,3000)).toBe(root);
            expect(root.hasIKTarget()).toBe(true);expect(root.isIKDriven()).toBe(true);
            expect(tip.getTransform(pdg.partSpace_World).ty).toBe(0);
            expect(()=>b.clearDrive()).toThrow();expect(()=>b.stopAllForces()).toThrow();
            expect(()=>b.setDriveTarget(new pdg.Point(0,0),0,1,1)).toThrow();
            expect(()=>b.setMode(pdg.physicsBody_Kinematic)).toThrow();
            expect(()=>root.setIKDriveTarget(tip,middle,new pdg.Point(0,0),1,1)).toThrow();
            expect(()=>root.setIKDriveTarget(middle,tip,new pdg.Point(0,0),-1,1)).toThrow();
            expect(()=>root.setIKDriveTarget(middle,tip,new pdg.Point(0,0),1,1,pdg.partSpace_World,1,1,Number.MAX_VALUE)).toThrow();
            for (const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
                const writer=new pdg.Serializer();writer.setResourceMode(mode);sprite.serialize(writer);
                const restored=new pdg.Sprite(),reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());restored.deserialize(reader);
                const r=restored.findPart('root'),m=restored.findPart('middle');
                expect(r.isIKDriven()).toBe(true);expect(()=>m.physics.clearDrive()).toThrow();
                r.clearIKTarget();expect(()=>m.physics.clearDrive()).not.toThrow();
            }
            setTimeout(function() {
                try {
                    expect(root.getIKError()).toBe('');expect(a.isDriveEnabled()).toBe(true);expect(b.isDriveEnabled()).toBe(true);
                    const end=tip.getTransform(pdg.partSpace_World);
                    expect(Math.hypot(end.tx-10,end.ty-8)).toBeLessThan(5);
                    const drive=b.getDriveState();expect(drive.maxForce).toBe(3000);expect(drive.maxTorque).toBe(3000);
                    expect(root.clearIKTarget()).toBe(root);expect(root.isIKDriven()).toBe(false);
                    expect(a.isDriveEnabled()).toBe(false);expect(b.isDriveEnabled()).toBe(false);
                    expect(b.setMode(pdg.physicsBody_Kinematic)).toBe(b);
                } finally {pdg.cleanupLayer(layer);done();}
            },500);
        });
    });
    it('keeps a scheduled IK target across steps and recovers after topology changes', function() {
        const s=new pdg.Sprite(),root=s.createPart('root'),middle=s.createPart('middle'),tip=s.createPart('tip');
        middle.setParentPart(root).setLocation(new pdg.Point(10,0));
        tip.setParentPart(middle).setLocation(new pdg.Point(8,0));
        expect(root.setIKTarget(middle,tip,new pdg.Point(10,8))).toBe(root);
        expect(root.hasIKTarget()).toBe(true);expect(root.isIKTargetReached()).toBe(false);
        root.animate(.1);expect(root.isIKTargetReached()).toBe(true);expect(root.getIKError()).toBe('');
        s.setLocation(new pdg.Point(2,1));root.animate(.1);
        expect(tip.getTransform(pdg.partSpace_World).tx).toBeCloseTo(10,4);
        expect(tip.getTransform(pdg.partSpace_World).ty).toBeCloseTo(8,4);
        expect(()=>root.setIKTarget(tip,middle,new pdg.Point(1,2))).toThrow();expect(root.hasIKTarget()).toBe(true);
        const angle=root.getRotation();tip.setParentPart(root);root.animate(.1);
        expect(root.isIKTargetReached()).toBe(false);expect(root.getIKError().length>0).toBe(true);
        expect(root.getRotation()).toBe(angle);
        tip.setParentPart(middle);root.animate(.1);expect(root.isIKTargetReached()).toBe(true);expect(root.getIKError()).toBe('');
        middle.setupPhysicsBody();root.animate(.1);expect(root.getIKError().length>0).toBe(true);
        middle.physics.setMode(pdg.physicsBody_Kinematic);root.animate(.1);expect(root.getIKError()).toBe('');
        [pdg.serialization_Complete,pdg.serialization_ExternalReferences].forEach(function(mode) {
            const writer=new pdg.Serializer(),reader=new pdg.Deserializer();writer.setResourceMode(mode);
            writer.serialize_obj(s);reader.setDataPtr(writer.getDataPtr());const copy=reader.deserialize_obj();
            const restored=copy.findPart('root');expect(restored.hasIKTarget()).toBe(true);
            expect(restored.isIKTargetReached()).toBe(true);copy.moveBy(1,1);restored.animate(.1);
            expect(restored.isIKTargetReached()).toBe(true);
            expect(copy.findPart('tip').getTransform(pdg.partSpace_World).tx).toBeCloseTo(10,4);
            expect(copy.findPart('tip').getTransform(pdg.partSpace_World).ty).toBeCloseTo(8,4);
            copy.clearParts();
        });
        expect(root.clearIKTarget()).toBe(root);expect(root.hasIKTarget()).toBe(false);
        expect(root.isIKTargetReached()).toBe(false);expect(root.getIKError()).toBe('');
        root.setRotation(.25);root.animate(.1);expect(root.getRotation()).toBeCloseTo(.25,5);
        root.setIKTarget(middle,tip,new pdg.Point(10,8));s.removePart(tip.getId());root.animate(.1);
        expect(root.getIKError().length>0).toBe(true);
        s.removePart(root.getId());expect(root.hasIKTarget()).toBe(false);expect(root.getIKError()).toBe('');
        s.clearParts();
    });

    it('rejects overlapping IK controllers and distinguishes unreachable targets from errors', function() {
        const s=new pdg.Sprite(),a=s.createPart('a'),b=s.createPart('b'),c=s.createPart('c'),d=s.createPart('d');
        b.setParentPart(a).setLocation(new pdg.Point(10,0));c.setParentPart(b).setLocation(new pdg.Point(8,0));
        d.setParentPart(c).setLocation(new pdg.Point(2,0));
        a.setIKTarget(b,c,new pdg.Point(100,0));a.animate(.1);
        expect(a.isIKTargetReached()).toBe(false);expect(a.getIKError()).toBe('');
        expect(()=>b.setIKTarget(c,d,new pdg.Point(1,2))).toThrow();expect(b.hasIKTarget()).toBe(false);
        a.clearIKTarget();expect(b.setIKTarget(c,d,new pdg.Point(16,4))).toBe(b);
        b.animate(.1);expect(b.isIKTargetReached()).toBe(true);
        expect(()=>b.setIKTarget(c,d,new pdg.Point(1,2),pdg.partSpace_World,0)).toThrow();
        s.clearParts();
    });

});
