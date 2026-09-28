// Fixed-hierarchy pose publication through the native and script Sprite facade.
describe('Animation pose', function() {
    var capabilityLayer = pdg.createSpriteLayer();
    var supported = typeof capabilityLayer.createSpriteFromSpriterFile === 'function';
    pdg.cleanupLayer(capabilityLayer);
    if (!supported) {
        it('requires Spriter support', function() { pending('Spriter support disabled'); });
        return;
    }
    var layer, sprite, other;
    beforeEach(function() {
        layer = pdg.createSpriteLayer();
        layer.setUseChipmunkPhysics(false);
        var path = process.cwd() + '/data/spriter-regression/arm.scml';
        sprite = layer.createSpriteFromSpriterFile(path);
        other = layer.createSpriteFromSpriterFile(path);
        sprite.pauseAnimation(); other.pauseAnimation();
    });
    afterEach(function() { if(layer)pdg.cleanupLayer(layer); layer = sprite = other = null; });
    it('retains imported animation and Part bindings after source Layer destruction', function() {
        expect(sprite.enableAnimationPose('reference')).toBe(true);
        var hand = sprite.createPart('hand'), bone = sprite.getAnimationBoneNames().indexOf('hand');
        hand.bindToBone(bone);
        var destination = pdg.createSpriteLayer(); destination.setUseChipmunkPhysics(false);
        try {
            destination.addSprite(sprite); layer.removeSprite(other); pdg.cleanupLayer(layer); layer = null;
            expect(sprite.isAnimationPoseEnabled()).toBe(true);
            expect(hand.getBoneId()).toBe(bone); expect(hand.isBoundToBone()).toBe(true);
            expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_Rig).x).toBeCloseTo(17, 5);
            var sample = sprite.sampleAnimationPose('reach', .25);
            expect(sample.bones[0].rotation).toBeCloseTo(Math.PI / 4, 5);
            expect(other.enableAnimationPose('reference')).toBe(true);
            expect(other.getAnimationBoneTransform('hand', pdg.animationSpace_Rig).x).toBeCloseTo(17, 5);
            destination.removeSprite(sprite);
        } finally { pdg.cleanupLayer(destination); }
        expect(sprite.isAnimationPoseEnabled()).toBe(true);
        expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_Rig).x).toBeCloseTo(17, 5);
    });
    function enable() {
        expect(typeof sprite.enableAnimationPose).toBe('function');
        expect(sprite.enableAnimationPose('reference')).toBe(true);
        expect(sprite.getAnimationRigError()).toBe('');
        expect(pdg.animationSpace_Local).toBe(0);
        expect(pdg.animationSpace_Rig).toBe(1);
        expect(pdg.animationSpace_World).toBe(2);
        expect(pdg.animationBinding_Image).toBe(0);
        expect(pdg.animationBinding_Point).toBe(1);
        expect(pdg.animationBinding_Box).toBe(2);
        expect(pdg.animationVariable_Float).toBe(0);
        expect(pdg.animationVariable_Int).toBe(1);
        expect(pdg.animationVariable_String).toBe(2);
    }

    it('selects named Part boxes, preserves local edits and explicitly bound image frames', function() {
        enable();
        const part=sprite.createPart('hit').bindToAnimationBinding('hitbox').setLocation(2,3);
        const collider=part.setupAnimationCollider('hitbox'),id=collider.getShapeId(0);
        const initial=collider.getBounds();part.moveBy(1,0);
        const moved=collider.getBounds();expect(Math.abs(moved.left-initial.left)).toBeGreaterThan(.1);
        expect(()=>part.setupAnimationCollider('grip')).toThrow();
        expect(collider.getShapeId(0)).toBe(id);
        for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
            const writer=new pdg.Serializer();writer.setResourceMode(mode);sprite.serialize(writer);
            const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());
            const copy=new pdg.Sprite();copy.deserialize(reader);
            expect(copy.findPart('hit').collider.getBounds().left).toBeCloseTo(moved.left,4);
        }
        const imagePart=sprite.createPart('artFrame').bindToAnimationBinding('hand_art');
        if(sprite.isAnimationDrawingSupported()) {
            const frame=imagePart.setupFrameCollider(pdg.frameCollider_Bounds);
            expect(frame.getShapeCount()).toBe(1);
            expect(frame.getBounds().width()).toBeGreaterThan(0);
            imagePart.setupFrameCollider(pdg.frameCollider_AlphaMask);
            expect(frame.getShapeCount()).toBe(1);
        } else expect(()=>imagePart.setupFrameCollider()).toThrow();
        sprite.disableAnimationPose();expect(collider.getShapeCount()).toBe(0);
    });
    it('restores authored bindings, transitions, IK and artwork in both save modes', function() {
        enable();
        sprite.seekAnimation('reference', 0);
        sprite.transitionToAnimation('reach', 0, 1);
        const bone=sprite.createPart('bone').bindToBone(1).setLocation(1,2);
        sprite.createPart('socket').bindToAnimationSocket('grip');
        sprite.createPart('art').bindToAnimationBinding('hand_art');
        bone.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic);
        bone.setupCollider().setCircle(.5);
        sprite.setupAnimationCollider();
        const ik=sprite.addAnimationIK({root:'shoulder',middle:'forearm',tip:'hand',
            rootLength:10,middleLength:5,targetX:10,targetY:10,influence:.3});
        // Authored Drawing snapshots are GUI-only; keep checking the pose,
        // transition, bindings and IK in the headless lane as well.
        let drawable;
        if(sprite.isAnimationDrawingSupported()) {
            const drawing=pdg.createDrawing();
            drawing.addLine(new pdg.Point(0,0),new pdg.Point(8,0),new pdg.Attributes().lineThickness(2));
            drawable=sprite.addAnimationDrawable(drawing,{bone:'hand',strokeSpace:pdg.animationStroke_Local,
                bounds:{left:0,top:-1,right:8,bottom:1,uncullable:false}});
        }
        const expected=sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig);
        for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
            const writer=new pdg.Serializer();writer.setResourceMode(mode);sprite.serialize(writer);
            const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());
            const copy=new pdg.Sprite();copy.deserialize(reader);
            expect(copy.isAnimationPoseEnabled()).toBe(true);
            expect(copy.isAnimationTransitioning()).toBe(true);
            expect(copy.isAnimationPaused()).toBe(true);
            expect(copy.findPart('bone').getBoneId()).toBe(1);
            expect(copy.findPart('socket').getAnimationSocketName()).toBe('grip');
            expect(copy.findPart('art').getAnimationBindingName()).toBe('hand_art');
            expect(copy.findPart('bone').physics.getMode()).toBe(pdg.physicsBody_Kinematic);
            expect(copy.findPart('bone').collider.getShapeCount()).toBe(1);
            expect(copy.collider.getGeometrySource()).toBe(pdg.colliderSource_Animation);
            expect(copy.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).x).toBeCloseTo(expected.x,5);
            expect(copy.getAnimationModifierError(ik)).toBe('');
            if(drawable!==undefined)expect(copy.getAnimationDrawableError(drawable)).toBe('');
            copy.setAnimationIKTarget(ik,12,8);
            if(drawable!==undefined)copy.removeAnimationDrawable(drawable);
            copy.removeAnimationModifier(ik);
        }
    });

    it('routes assembly loads and preserves reflected physics through snapshots', function() {
        if(!sprite.supportsAnimationPhysics()){pending('Chipmunk disabled');return;}
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);layer.setGravity(0);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.pauseAnimation();enable();
        sprite.setupPhysicsFromAnimationRig(30);
        const root=sprite.findPart('shoulder').physics, arm=sprite.findPart('forearm');
        const force=sprite.physics.applyForce(new pdg.Vector(2,3),.5,.2);
        const torque=sprite.physics.addContinuousTorque(15);
        expect(force).toBeGreaterThan(0);expect(torque).toBeGreaterThan(0);
        const body=arm.physics, joint=body.getConstraint(0), before=body.getState();
        body.setVelocity(2,3).setAngularVelocity(4);
        const moment=sprite.physics.getMomentOfInertia(), momentum=sprite.physics.getAngularMomentum();
        expect(moment).toBeGreaterThan(root.getMomentOfInertia());
        sprite.setFlipX(true);
        expect(arm.physics).toBe(body);expect(body.getConstraint(0)).toBe(joint);
        expect(body.getState().x).toBeCloseTo(-before.x,5);
        expect(body.getVelocity().x).toBe(-2);expect(body.getAngularVelocity()).toBe(-4);
        expect(sprite.physics.getMomentOfInertia()).toBeCloseTo(moment,5);
        expect(sprite.physics.getAngularMomentum()).toBeCloseTo(-momentum,5);
        const writer=new pdg.Serializer();sprite.serialize(writer);
        const copy=new pdg.Sprite(), reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());copy.deserialize(reader);
        try {
            expect(copy.isFlippedX()).toBe(true);
            expect(copy.physics.getMomentOfInertia()).toBeCloseTo(moment,5);
            expect(copy.physics.removeForce(force)).toBe(true);
            copy.setAnimationPhysicsRoot('forearm');
            expect(copy.physics.removeForce(torque)).toBe(true);
            expect(copy.physics.removeForce(torque)).toBe(false);
            copy.setFlipX(false);
            expect(copy.findPart('forearm').physics.getState().x).toBeCloseTo(before.x,5);
        } finally {copy.disableAnimationPhysics(0);}
        sprite.physics.stopAllForces();
        expect(sprite.physics.removeForce(force)).toBe(false);
        expect(sprite.physics.removeForce(torque)).toBe(false);
    });

    it('restores active explicit and generated assemblies with edited components and drive ownership', function() {
        if(!sprite.supportsAnimationPhysics()) { pending('Chipmunk disabled');return; }
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.pauseAnimation();enable();
        for(const generated of [false,true]) {
            if(generated)sprite.setupPhysicsFromAnimationRig(30);
            else sprite.setupAnimationPhysics({bodies:[
                {bone:'shoulder',mass:10,length:10,radius:.25,offsetX:5},
                {bone:'forearm',mass:10,length:5,radius:.25,offsetX:2.5},
                {bone:'hand',mass:10,length:2,radius:.25,offsetX:1}
            ],joints:[{parent:0,child:1,parentX:5,childX:-2.5},{parent:1,child:2,parentX:2.5,childX:-1}]});
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0);
            sprite.setAnimationPhysicsDriveSettings({maxForce:80,maxTorque:90},'forearm');
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven,'forearm',false,0);
            const hand=sprite.findPart('hand');sprite.detachAnimationPhysicsPart(hand);
            hand.physics.setVelocity(1,2);
            const state=hand.physics.getState();hand.physics.setDriveTarget(new pdg.Point(state.x+2,state.y),state.rotation,40,50);
            const weight=sprite.createPart('weight');weight.setupPhysicsBody(10,3);weight.setupCollider().setCircle(1);
            sprite.attachAnimationPhysicsPart(weight,sprite.findPart('forearm'));
            sprite.findPart('forearm').physics.createPivotJoint(weight.physics);
            const elbow=sprite.findPart('shoulder').physics.getConstraint(0);
            elbow.setAnchors(new pdg.Point(4.5,.25),new pdg.Point(-2,-.5));
            const total=sprite.physics.getMass();
            for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
                const writer=new pdg.Serializer();writer.setResourceMode(mode);sprite.serialize(writer);
                const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());
                const copy=new pdg.Sprite();copy.deserialize(reader);
                expect(copy.isAnimationPhysicsEnabled()).toBe(true);
                expect(copy.physics.getMass()).toBeCloseTo(total,5);
                expect(copy.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Mixed);
                expect(copy.getAnimationPhysicsDriveSettings('forearm').maxTorque).toBe(90);
                expect(copy.isAnimationPhysicsPartAttached(copy.findPart('hand'))).toBe(false);
                expect(copy.isAnimationPhysicsPartAttached(copy.findPart('weight'))).toBe(true);
                expect(copy.findPart('hand').physics.isDriveEnabled()).toBe(true);
                expect(copy.findPart('hand').physics.getVelocity().x).toBe(1);
                expect(copy.findPart('shoulder').collider.getShapeCount()).toBe(1);
                const copiedElbow=copy.findPart('shoulder').physics.getConstraint(0);
                expect(copiedElbow.getAnchorA().x).toBe(4.5);expect(copiedElbow.getAnchorA().y).toBe(.25);
                expect(copiedElbow.getAnchorB().x).toBe(-2);expect(copiedElbow.getAnchorB().y).toBe(-.5);
                copy.findPart('hand').physics.clearDrive();copy.disableAnimationPhysics(0);
                expect(copy.physics.getMass()).toBeCloseTo(total,5);
            }
            hand.physics.clearDrive();sprite.disableAnimationPhysics(0);sprite.removePart(weight.getId());
            for(const name of ['shoulder','forearm','hand'])sprite.removePart(sprite.findPart(name).getId());
        }
    });

    it('transfers a physical bone subtree without retaining the source rig owner', function() {
        if(!sprite.supportsAnimationPhysics()) { pending('Chipmunk disabled');return; }
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.pauseAnimation();enable();
        sprite.setupPhysicsFromAnimationRig(30);
        const destination=layer.createSprite(),arm=sprite.findPart('forearm'),hand=sprite.findPart('hand');
        const body=arm.physics,collider=arm.collider,mass=body.getMass()+hand.physics.getMass(),before=body.getState();
        expect(destination.transferPart(arm)).toBe(arm);
        expect(arm.getSprite()).toBe(destination);expect(hand.getSprite()).toBe(destination);expect(sprite.findPart('forearm')).toBe(null);
        expect(arm.getBoneId()).toBe(pdg.boneId_None);expect(body).toBe(arm.physics);expect(collider).toBe(arm.collider);
        expect(sprite.physics.getMass()).toBeCloseTo(30-mass,5);expect(body.getState().x).toBeCloseTo(before.x,5);
        expect(body.getConstraintCount()).toBe(1);
        for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]) {
            const writer=new pdg.Serializer();writer.setResourceMode(mode);layer.serialize(writer);
            const reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());const copy=pdg.createSpriteLayer();
            try {copy.deserialize(reader);expect(copy.getNthSprite(0).findPart('forearm')).toBe(null);
                expect(copy.getNthSprite(1).findPart('forearm').physics.getConstraintCount()).toBe(1);
            } finally {pdg.cleanupLayer(copy);}
        }
        sprite.disableAnimationPhysics(0);expect(body.isAttached()).toBe(true);expect(body.getSolver()).toBe(pdg.physicsSolver_Chipmunk);
    });

    it('maps Parts to authored bindings and sockets with independent local offsets', function() {
        enable();
        const art=sprite.createPart('mapped hand').bindToAnimationBinding('hand_art');
        const socket=sprite.createPart('mount').bindToAnimationSocket('grip');
        const child=sprite.createPart('child');child.setParentPart(socket);child.setLocation(new pdg.Point(2,0));
        expect(art.getAnimationBindingName()).toBe('hand_art');expect(socket.getAnimationSocketName()).toBe('grip');
        expect(child.getBoneId()).toBe(pdg.boneId_None);expect(art.getBoneId()).not.toBe(pdg.boneId_None);
        const frame=sprite.getAnimationBindingTransform('hand_art',pdg.animationSpace_Rig);
        expect(art.getTransform(pdg.partSpace_Sprite).tx).toBeCloseTo(frame.x,5);
        const before=socket.getTransform(pdg.partSpace_Sprite);
        const shoulder=sprite.getAnimationBoneTransform('shoulder');shoulder.rotation=Math.PI/2;
        sprite.setAnimationBoneTransform('shoulder',shoulder);
        expect(socket.getTransform(pdg.partSpace_Sprite).ty).not.toBeCloseTo(before.ty,5);
        expect(()=>art.bindToAnimationBinding('missing')).toThrow();expect(art.getAnimationBindingName()).toBe('hand_art');
        sprite.disableAnimationPose();expect(art.getBoneId()).toBe(pdg.boneId_None);
        expect(art.getAnimationBindingName()).toBe('');expect(socket.getAnimationSocketName()).toBe('');
        expect(child.getParentPart()).toBe(socket);
    });
    it('publishes one edited pose to bones, artwork, sockets, children and boxes', function() {
        enable();
        expect(sprite.getAnimationBoneNames()).toEqual(['shoulder', 'forearm', 'hand']);
        expect(sprite.getAnimationBindingNames()).toEqual(['shoulder_art', 'forearm_art', 'hand_art', 'grip', 'hitbox']);
        var snapshot = sprite.getAnimationPose();
        var child = layer.createSprite(); sprite.attachSprite(child, 'grip');
        var shoulder = sprite.getAnimationBoneTransform('shoulder');
        shoulder.rotation = Math.PI / 2;
        sprite.setAnimationBoneTransform('shoulder', shoulder);
        expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_Rig).y).toBeCloseTo(18, 6);
        expect(sprite.getAnimationBindingTransform('hand_art', pdg.animationSpace_Rig).y).toBeCloseTo(18, 6);
        expect(sprite.getAttachPoint('grip').y).toBeCloseTo(21, 6);
        expect(child.getLocation().y).toBeCloseTo(21, 6);
        var box = sprite.getSpriterCollisionBox('hitbox');
        expect(box.radians).toBeCloseTo(Math.PI / 2, 6);
        expect(other.getAttachPoint('grip').x).toBeCloseTo(20, 6);
        expect(snapshot.bones[0].rotation).toBe(0);
        snapshot.bones[0].rotation = 999;
        expect(sprite.getAnimationBoneTransform('shoulder').rotation).toBeCloseTo(Math.PI / 2, 6);
        sprite.setLocation(new pdg.Point(100, 50)); sprite.setScale(-2, 3);
        expect(sprite.getAnimationBindingTransform('hand_art', pdg.animationSpace_World).y).toBeCloseTo(89, 6);
        expect(sprite.getAttachPoint('grip').y).toBeCloseTo(45, 6);
        expect(child.getLocation().y).toBeCloseTo(95, 6);
        sprite.clearAnimationBoneTransforms();
        expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_Rig).x).toBeCloseTo(17, 6);
    });
    it('samples floating-point seconds into independent snapshots without changing playback', function() {
        enable();
        var before = sprite.getAnimationProgress();
        expect(function() { sprite.sampleAnimationPose('reach', '0.25'); }).toThrow();
        var quarter = sprite.sampleAnimationPose('reach', 0.25);
        expect(sprite.sampleAnimationPose('reach_once', -0.5).bones[0].rotation).toBe(0);
        expect(sprite.sampleAnimationPose('reach_once', 1.5).bones[0].rotation).toBeCloseTo(Math.PI / 2, 6);
        expect(quarter.bones[0].rotation).toBeCloseTo(Math.PI / 4, 6);
        expect(quarter.rigRevision).toBe(sprite.getAnimationPose().rigRevision);
        expect(quarter.bindings[4].kind).toBe(pdg.animationBinding_Box);
        expect(quarter.bindings[0].kind).toBe(pdg.animationBinding_Image);
        expect(quarter.bindings[3].kind).toBe(pdg.animationBinding_Point);
        expect(quarter.bindings[4].parent).toBe(2);
        expect(sprite.sampleAnimationPose('reach', 1.25).bones[0].rotation).toBeCloseTo(Math.PI / 4, 6);
        expect(sprite.sampleAnimationPose('reach', -0.75).bones[0].rotation).toBeCloseTo(Math.PI / 4, 6);
        expect(sprite.isAnimationPaused()).toBe(true);
        expect(sprite.getAnimationProgress()).toBe(before);
        expect(sprite.getAnimationBoneTransform('shoulder').rotation).toBe(0);
        quarter.bones[0].x = 100;
        expect(sprite.sampleAnimationPose('reach', 0.25).bones[0].x).toBe(2);
    });
    it('samples typed entity/object variables and tag sets without stale clip values', function() {
        enable();
        function value(pose, name, object) { return pose.variables.filter(function(v) { return v.name === name && v.object === (object || ''); })[0]; }
        function tags(pose, object) { return pose.tags.filter(function(v) { return v.object === (object || ''); })[0].tags; }
        var pose = sprite.sampleAnimationPose('reach', 0.25);
        expect(value(pose, 'speed')).toEqual({object: '', name: 'speed', type: pdg.animationVariable_Float, value: 5});
        expect(value(pose, 'phase').type).toBe(pdg.animationVariable_Int);
        expect(value(pose, 'mode').type).toBe(pdg.animationVariable_String);
        expect(value(pose, 'phase').value).toBe(3);
        expect(value(pose, 'mode').value).toBe('reach_start');
        expect(value(pose, 'unchanged').value).toBe(42);
        expect(value(pose, 'pressure', 'grip').value).toBeCloseTo(0.5, 6);
        expect(value(pose, 'missing')).toBeUndefined();
        expect(tags(pose)).toEqual(['grounded']);
        expect(tags(pose, 'grip')).toEqual(['contact']);
        expect(tags(sprite.sampleAnimationPose('reach', 0.75))).toEqual(['airborne']);
        expect(tags(sprite.sampleAnimationPose('reach', 0.75), 'grip')).toEqual([]);
        expect(tags(sprite.getAnimationPose())).toEqual([]);
        expect(value(sprite.getAnimationPose(), 'speed').value).toBe(1);
        sprite.startAnimation('reach'); sprite.pauseAnimation();
        expect(tags(sprite.getAnimationPose())).toEqual(['grounded']);
        sprite.startAnimation('reference'); sprite.pauseAnimation();
        expect(tags(sprite.getAnimationPose())).toEqual([]);
        expect(value(sprite.getAnimationPose(), 'mode').value).toBe('idle');
    });
    it('rejects invalid and throwing transform properties atomically', function() {
        enable();
        var before = sprite.getAnimationBoneTransform('shoulder');
        [NaN, Infinity, -Infinity].forEach(function(value) {
            var bad = sprite.getAnimationBoneTransform('shoulder'); bad.x = value;
            expect(function() { sprite.setAnimationBoneTransform('shoulder', bad); }).toThrow();
        });
        var incomplete = {x: 300, y: 400};
        expect(function() { sprite.setAnimationBoneTransform('shoulder', incomplete); }).toThrow();
        var throwing = sprite.getAnimationBoneTransform('shoulder'); throwing.x = 300;
        Object.defineProperty(throwing, 'alpha', {get: function() { throw new Error('property failure'); }});
        expect(function() { sprite.setAnimationBoneTransform('shoulder', throwing); }).toThrow();
        expect(sprite.getAnimationBoneTransform('shoulder')).toEqual(before);
        expect(function() { sprite.getAnimationBoneTransform('missing'); }).toThrow();
        ['local', 'rig', 'world', -1, 3, 0.5, NaN, Infinity, 4294967296].forEach(function(space) {
            expect(function() { sprite.getAnimationBoneTransform('hand', space); }).toThrow();
            expect(function() { sprite.getAnimationBindingTransform('grip', space); }).toThrow();
        });
        expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_Local)).toEqual(sprite.getAnimationBoneTransform('hand'));
        expect(sprite.getAnimationBindingTransform('grip', pdg.animationSpace_Local)).toEqual(sprite.getAnimationBindingTransform('grip'));
        expect(function() { sprite.sampleAnimationPose('reach', NaN); }).toThrow();
        expect(function() { sprite.sampleAnimationPose('missing', 0.25); }).toThrow();
        expect(sprite.enableAnimationPose('missing')).toBe(false);
        expect(sprite.isAnimationPoseEnabled()).toBe(true);
        expect(sprite.getAnimationBoneTransform('shoulder')).toEqual(before);
    });
    it('keeps overrides stable across animation ticks and clears them on disable', function(done) {
        enable();
        var shoulder = sprite.getAnimationBoneTransform('shoulder'); shoulder.rotation = Math.PI / 2;
        sprite.setAnimationBoneTransform('shoulder', shoulder);
        sprite.startAnimation('reach');
        setTimeout(function() {
            expect(sprite.getAnimationBoneTransform('shoulder').rotation).toBeCloseTo(Math.PI / 2, 6);
            expect(sprite.getAttachPoint('grip').y).toBeCloseTo(21, 6);
            sprite.pauseAnimation();
            sprite.disableAnimationPose();
            expect(sprite.isAnimationPoseEnabled()).toBe(false);
            expect(sprite.getAnimationBoneNames()).toEqual([]);
            expect(function() { sprite.getAnimationPose(); }).toThrow();
            expect(sprite.enableAnimationPose('reference')).toBe(true);
            expect(sprite.getAnimationBoneTransform('shoulder').rotation).not.toBeCloseTo(Math.PI / 2, 3);
            done();
        }, 120);
    });
    it('uses integer debug flags with explicit GUI capability and per-instance state', function() {
        expect(pdg.animationDebug_None).toBe(0);
        expect(pdg.animationDebug_Bones).toBe(1);
        expect(pdg.animationDebug_Sockets).toBe(2);
        expect(pdg.animationDebug_Boxes).toBe(4);
        expect(pdg.animationDebug_All).toBe(7);
        expect(typeof sprite.isAnimationDrawingSupported()).toBe('boolean');
        expect(sprite.getAnimationDebugDraw()).toBe(0);
        expect(function() { sprite.setAnimationDebugDraw(pdg.animationDebug_All); }).toThrow();
        enable();
        if (sprite.isAnimationDrawingSupported()) {
            sprite.setAnimationDebugDraw(pdg.animationDebug_Bones | pdg.animationDebug_Sockets);
            expect(sprite.getAnimationDebugDraw()).toBe(3);
            expect(other.getAnimationDebugDraw()).toBe(0);
        } else {
            expect(function() { sprite.setAnimationDebugDraw(pdg.animationDebug_Bones); }).toThrow();
            expect(sprite.getAnimationDebugDraw()).toBe(0);
        }
        var before = sprite.getAnimationDebugDraw();
        ['bones', 0.5, NaN, Infinity, -1, 8, 4294967296].forEach(function(flags) {
            expect(function() { sprite.setAnimationDebugDraw(flags); }).toThrow();
            expect(sprite.getAnimationDebugDraw()).toBe(before);
        });
        sprite.setAnimationDebugDraw(pdg.animationDebug_None);
        expect(sprite.getAnimationDebugDraw()).toBe(0);
        sprite.disableAnimationPose();
        expect(sprite.getAnimationDebugDraw()).toBe(0);
    });

    it('evaluates ordered borrowed-pose modifiers and invalidates retained views', function() {
        enable();var order=[],retained,copy;
        sprite.addAnimationModifier(function(view,context){order.push(2);expect(context.deltaSeconds).toBe(0);view.rotateLocal('shoulder',Math.PI/2);retained=view;copy=view.copy();},pdg.animationStage_PreConstraint,2);
        sprite.addAnimationModifier(function(){order.push(1);},pdg.animationStage_PreConstraint,1);
        sprite.addAnimationModifier(function(view){order.push(3);expect(view.getTransform('hand',pdg.animationSpace_Rig).y).toBeCloseTo(18,6);},pdg.animationStage_Constraint,-5);
        sprite.addAnimationModifier(function(){order.push(4);},pdg.animationStage_PostConstraint,-5);
        expect(sprite.getAnimationPose().bones[0].rotation).toBeCloseTo(Math.PI/2,6);
        expect(order).toEqual([1,2,3,4]);expect(sprite.getAttachPoint('grip').y).toBeCloseTo(21,6);
        expect(copy.bones[0].rotation).toBeCloseTo(Math.PI/2,6);
        expect(function(){retained.copy();}).toThrow();expect(function(){retained.rotateLocal(0,1);}).toThrow();
        sprite.setAnimationSource(pdg.animationSource_Reference);
        expect(sprite.getAnimationPose().bones[0].rotation).toBeCloseTo(Math.PI/2,6);
        expect(function(){sprite.setAnimationSource('reference');}).toThrow();
        expect(function(){sprite.addAnimationModifier(function(){},'preConstraint');}).toThrow();
        expect(function(){sprite.addAnimationModifier(function(){},0,0.5);}).toThrow();
    });
    it('rolls back failing callbacks, blocks owner destruction, and rejects async mutation', function() {
        enable();var runs=0;
        var id=sprite.addAnimationModifier(function(view){++runs;view.rotateLocal(0,1);throw new Error('modifier failure');});
        expect(sprite.getAnimationPose().bones[0].rotation).toBe(0);
        expect(sprite.getAnimationModifierError(id)).toContain('modifier failure');
        sprite.setAnimationSource(pdg.animationSource_Reference);sprite.getAnimationPose();expect(runs).toBe(1);
        sprite.clearAnimationModifiers();
        id=sprite.addAnimationModifier(function(){pdg.cleanupLayer(layer);});sprite.getAnimationPose();
        expect(sprite.getAnimationModifierError(id)).toContain('outside an animation modifier');
        expect(sprite.isAnimationPoseEnabled()).toBe(true);
        sprite.clearAnimationModifiers();
        id=sprite.addAnimationModifier(function(view){view.rotateLocal(0,1);return {then:function(){}};});
        expect(sprite.getAnimationPose().bones[0].rotation).toBe(0);
        expect(sprite.getAnimationModifierError(id)).toContain('synchronous');
        sprite.clearAnimationModifiers();
        id=sprite.addAnimationModifier(function(){sprite.getAnimationPose();});sprite.getAnimationPose();
        expect(sprite.getAnimationModifierError(id).length).toBeGreaterThan(0);
    });
    it('defers callback registration changes and clears them with rig replacement', function() {
        enable();var calls=0,first=true,later;
        sprite.addAnimationModifier(function(){if(first){first=false;sprite.removeAnimationModifier(later);sprite.addAnimationModifier(function(){calls+=10;});}});
        later=sprite.addAnimationModifier(function(){++calls;});
        sprite.getAnimationPose();expect(calls).toBe(1);
        sprite.setAnimationSource(pdg.animationSource_Clip);sprite.getAnimationPose();expect(calls).toBe(11);
        expect(sprite.enableAnimationPose('missing')).toBe(false);expect(sprite.isAnimationPoseEnabled()).toBe(true);
        var before=calls;expect(sprite.enableAnimationPose('reference')).toBe(true);
        sprite.getAnimationPose();expect(calls).toBe(before);
    });


    it('solves registered IK into the same pose used by artwork, sockets and boxes', function(){
        enable();sprite.setAnimationSource(pdg.animationSource_Reference);
        var config={root:'shoulder',middle:'forearm',tip:'hand',rootLength:10,middleLength:5,targetX:10,targetY:10};
        var id=sprite.addAnimationIK(config);
        expect(sprite.getAnimationIKResult(id).reachable).toBe(true);
        expect(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).x).toBeCloseTo(10,6);
        expect(sprite.getAnimationBindingTransform('hand_art',pdg.animationSpace_Rig).y).toBeCloseTo(10,6);
        expect(sprite.getAnimationBindingTransform('grip',pdg.animationSpace_World).x).toBeCloseTo(sprite.getAttachPoint('grip').x,6);
        var box=sprite.getSpriterCollisionBox('hitbox');expect(isFinite(box.radians)).toBe(true);
        expect(other.enableAnimationPose('reference')).toBe(true);
        expect(other.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).x).toBe(17);
        var second=sprite.addAnimationIK({root:'shoulder',middle:'forearm',tip:'hand',rootLength:10,middleLength:5,targetX:12,targetY:5},1);
        expect(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).x).toBeCloseTo(12,6);
        expect(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).y).toBeCloseTo(5,6);
        sprite.removeAnimationModifier(second);
        sprite.setAnimationIKTarget(id,100,0,pdg.animationSpace_World);
        var result=sprite.getAnimationIKResult(id);expect(result.clamped).toBe(true);expect(result.reachable).toBe(false);expect(result.reachError).toBeGreaterThan(80);
        expect(function(){sprite.setAnimationIKTarget(id,10,10,'world');}).toThrow();
        expect(function(){sprite.setAnimationIKTarget(id,NaN,10);}).toThrow();
        sprite.removeAnimationModifier(id);expect(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).x).toBe(17);
        expect(function(){sprite.getAnimationIKResult(id);}).toThrow();
        config.rootLength=-1;expect(function(){sprite.addAnimationIK(config);}).toThrow();
        config.rootLength=10;config.space='rig';expect(function(){sprite.addAnimationIK(config);}).toThrow();
        config.space=pdg.animationSpace_Rig;var invalidated=sprite.addAnimationIK(config);sprite.setScale(0,1);
        expect(function(){sprite.getAnimationIKResult(invalidated);}).toThrow();expect(sprite.getAnimationModifierError(invalidated)).toContain('nonsingular');
    });


    it('infers animated IK lengths and supports nonuniform scales through the script API', function() {
        enable(); sprite.setScale(-2, 3);
        var offset = 10;
        sprite.addAnimationModifier(function(view) {
            var joint = view.getLocalTransform('forearm'); joint.x = offset;
            view.setLocalTransform('forearm', joint);
        });
        var id = sprite.addAnimationIK({root:'shoulder', middle:'forearm', tip:'hand',
            targetX:10, targetY:4, matchOrientation:true, targetRotation:0.2});
        [10, 11, 12].forEach(function(value) {
            offset = value;
            sprite.setAnimationIKTarget(id, 10, 4);
            expect(sprite.getAnimationIKResult(id).reachable).toBe(true);
            expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_World).x).toBeCloseTo(-20, 6);
            expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_World).y).toBeCloseTo(12, 6);
            expect(sprite.getAnimationBoneTransform('hand', pdg.animationSpace_World).rotation).toBeCloseTo(-0.2, 6);
            expect(sprite.getAnimationBoneTransform('forearm').x).toBe(value);
        });
        expect(sprite.getAnimationModifierError(id)).toBe('');
        sprite.removeAnimationModifier(id);
    });

    it('seeks silently in seconds and preserves state for invalid selections',function(){
        enable();sprite.seekAnimation('reach',0.25);
        expect(sprite.isAnimationPaused()).toBe(true);
        expect(sprite.getAnimationBoneTransform('shoulder').rotation).toBeCloseTo(Math.PI/4,6);
        sprite.seekAnimation('reach',-0.75);expect(sprite.getAnimationProgress()).toBeCloseTo(0.25,6);
        expect(function(){sprite.seekAnimation('missing',0.5);}).toThrow();
        expect(function(){sprite.seekAnimation('reach','0.5');}).toThrow();
        expect(function(){sprite.transitionToAnimation('reference',0,NaN);}).toThrow();
        expect(sprite.getAnimationProgress()).toBeCloseTo(0.25,6);
        sprite.transitionToAnimation('reference',0,0.25);
        expect(sprite.isAnimationTransitioning()).toBe(true);expect(sprite.getAnimationTransitionProgress()).toBe(0);
        expect(sprite.getAnimationBoneTransform('shoulder').rotation).toBeCloseTo(Math.PI/4,6);
        sprite.seekAnimation('reach_once',2);
        expect(sprite.isAnimationTransitioning()).toBe(false);expect(sprite.getAnimationProgress()).toBe(1);
    });
    it('completes independent transitions once and keeps paused progress frozen',function(done){
        enable();var completions=0;
        sprite.onAnimationBlendComplete(function(){++completions;return true;});
        sprite.seekAnimation('reach',0.25);sprite.transitionToAnimation('reference',0,0.15);
        setTimeout(function(){
            expect(sprite.getAnimationTransitionProgress()).toBe(0);expect(completions).toBe(0);
            sprite.resumeAnimation();
            setTimeout(function(){
                expect(sprite.isAnimationTransitioning()).toBe(false);expect(sprite.getAnimationTransitionProgress()).toBe(1);
                expect(sprite.getAnimationBoneTransform('shoulder').rotation).toBe(0);expect(completions).toBe(1);done();
            },350);
        },80);
    });


    it('generates editable dynamic bodies, aggregates mass and routes root impulses', function(){
        if (!sprite.supportsAnimationPhysics()) return;
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();
        layer.setUseChipmunkPhysics(true);layer.setGravity(0);layer.setDamping(1);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.pauseAnimation();
        expect(sprite.enableAnimationPose('reference')).toBe(true);
        expect(sprite.setupPhysicsFromAnimationRig(34)).toBe(sprite);
        var root=sprite.findPart('shoulder'), limb=sprite.findPart('forearm'), leaf=sprite.findPart('hand');
        expect(sprite.physics.getMass()).toBeCloseTo(34,6);
        expect(root.physics.getMass()).toBeCloseTo(20,6);
        expect(limb.physics.getMass()).toBeCloseTo(10,6);
        expect(leaf.physics.getMass()).toBeCloseTo(4,6);
        expect(leaf.collider.getShapeType(leaf.collider.getShapeId(0))).toBe(pdg.collisionShape_Capsule);
        expect(limb.physics.getConstraintCount()).toBe(2);
        expect(limb.physics.getConstraint(0).getType()).toBe(pdg.constraint_Pivot);
        var body=limb.physics, joint=body.getConstraint(0), inertia=body.getMomentOfInertia();
        body.setMass(20);expect(sprite.physics.getMass()).toBeCloseTo(44,6);
        expect(body.getMomentOfInertia()).toBeCloseTo(inertia*2,6);
        sprite.physics.setMass(88);expect(body.getMass()).toBeCloseTo(40,6);
        expect(body.getMomentOfInertia()).toBeCloseTo(inertia*4,6);
        expect(sprite.setAnimationPhysicsRoot('forearm')).toBe(sprite);
        expect(sprite.getAnimationPhysicsRoot()).toBe(1);
        sprite.physics.applyImpulse(new pdg.Vector(40,0));expect(body.getVelocity().x).toBeCloseTo(1,6);
        expect(sprite.clearAnimationPhysicsRoot()).toBe(sprite);expect(sprite.getAnimationPhysicsRoot()).toBe(0);
        expect(function(){sprite.setAnimationPhysicsRoot('missing');}).toThrow();
        expect(function(){sprite.setAnimationPhysicsRoot(-1);}).toThrow();
        expect(function(){sprite.setAnimationPhysicsRoot(1.5);}).toThrow();
        expect(function(){sprite.setupPhysicsFromAnimationRig(0);}).toThrow();
        expect(function(){sprite.setupPhysicsFromAnimationRig(17,null);}).toThrow();
        expect(function(){sprite.physics.setMode(pdg.physicsBody_Dynamic);}).toThrow();
        sprite.setupPhysicsFromAnimationRig(17);
        expect(body.getMass()).toBeCloseTo(5,6);expect(body.getVelocity().x).toBeCloseTo(1,6);
        expect(limb.physics).toBe(body);expect(body.getConstraint(0)).toBe(joint);
        var warnings=sprite.getAnimationPhysicsSetupWarnings();expect(warnings.length).toBeGreaterThan(0);
        warnings.length=0;expect(sprite.getAnimationPhysicsSetupWarnings().length).toBeGreaterThan(0);
        sprite.disableAnimationPhysics(0);
        expect(sprite.physics.getMass()).toBeCloseTo(17,6);expect(joint.isActive()).toBe(false);
        expect(body.getSolver()).toBe(pdg.physicsSolver_Basic);
        expect(limb.physics).toBe(pdg.PhysicsBody.NoPhysics);expect(leaf.collider).toBe(pdg.Collider.NoCollider);
        body.setMass(100);expect(sprite.physics.getMass()).toBeCloseTo(17,6);
    });
    it('edits generated assembly membership without redistributing mass or losing retained handles',function(){
        if(!sprite.supportsAnimationPhysics())return;
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();
        layer.setUseChipmunkPhysics(true);layer.setGravity(0);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');
        sprite.pauseAnimation();sprite.enableAnimationPose('reference');sprite.setupPhysicsFromAnimationRig(34);
        var root=sprite.findPart('shoulder'),forearm=sprite.findPart('forearm'),hand=sprite.findPart('hand');
        var weight=sprite.createPart('weight'),body=weight.setupPhysicsBody(10,20),h=hand.physics.getState();
        body.teleport(new pdg.Point(h.x,h.y),h.rotation);
        var grip=hand.physics.createPivotJoint(body),elbow=root.physics.getConstraint(0);
        expect(sprite.attachAnimationPhysicsPart(weight,hand)).toBe(sprite);
        expect(sprite.attachAnimationPhysicsPart(weight)).toBe(sprite);
        expect(sprite.isAnimationPhysicsPartAttached(weight)).toBe(true);
        expect(sprite.physics.getMass()).toBeCloseTo(44,6);
        expect(function(){sprite.attachAnimationPhysicsPart('hand');}).toThrow();
        expect(function(){sprite.detachAnimationPhysicsPart(hand,1);}).toThrow();
        expect(function(){sprite.attachAnimationPhysicsPart(weight,root);}).toThrow();
        var before=forearm.physics.getState(),inertia=forearm.physics.getMomentOfInertia();
        expect(sprite.detachAnimationPhysicsPart(forearm)).toBe(sprite);
        expect(sprite.physics.getMass()).toBeCloseTo(20,6);
        expect(sprite.isAnimationPhysicsPartAttached(hand)).toBe(false);
        expect(sprite.isAnimationPhysicsPartAttached(weight)).toBe(false);
        expect(grip.isActive()).toBe(true);expect(elbow.isActive()).toBe(false);
        expect(forearm.physics.getState()).toEqual(before);
        expect(forearm.physics.getMomentOfInertia()).toBe(inertia);
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0);
        expect(hand.physics.getMode()).toBe(pdg.physicsBody_Dynamic);
        sprite.physics.setMass(40);expect(forearm.physics.getMass()).toBe(10);expect(body.getMass()).toBe(10);
        expect(function(){sprite.detachAnimationPhysicsPart(root);}).toThrow();
        expect(function(){sprite.setupPhysicsFromAnimationRig(50);}).toThrow();
        sprite.attachAnimationPhysicsPart(forearm).attachAnimationPhysicsPart(hand).attachAnimationPhysicsPart(weight,hand);
        expect(sprite.physics.getMass()).toBeCloseTo(64,6);
        sprite.detachAnimationPhysicsPart(root,false);
        expect(sprite.getAnimationPhysicsRoot()).toBe(1);
        expect(sprite.isAnimationPhysicsPartAttached(hand)).toBe(true);
        sprite.removePart(weight.getId());expect(sprite.physics.getMass()).toBeCloseTo(14,6);
        expect(body.isAttached()).toBe(false);expect(grip.isActive()).toBe(false);
        body.setMass(100);expect(sprite.physics.getMass()).toBeCloseTo(14,6);
        sprite.disableAnimationPhysics(0);
        expect(sprite.isAnimationPhysicsPartAttached(hand)).toBe(false);
        expect(sprite.physics.getMass()).toBeCloseTo(14,6);
    });
    it('keeps a zero-length designated root using an explicit millimeter conversion',function(){
        if (!sprite.supportsAnimationPhysics()) return;
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();
        layer.setUseChipmunkPhysics(true);
        var physical=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/physics-generation.scml');
        expect(physical.enableAnimationPose('reference')).toBe(true);
        physical.setupPhysicsFromAnimationRig(2,1000);
        var root=physical.findPart('root'), id=root.collider.getShapeId(0);
        expect(root.collider.getCapsuleEnd(id).x-root.collider.getCapsuleStart(id).x).toBeCloseTo(1,6);
        expect(root.physics.getMass()).toBe(2);expect(physical.findPart('helper')).toBe(null);
        expect(function(){physical.setAnimationPhysicsRoot('helper');}).toThrow();
        expect(physical.getAnimationPhysicsRoot()).toBe(0);
        physical.disableAnimationPhysics(0);physical.setAnimationPhysicsRoot('helper');
        physical.setupPhysicsFromAnimationRig(3,1000);
        expect(physical.getAnimationPhysicsRoot()).toBe(1);
        expect(physical.findPart('helper').physics.getMass()).toBe(3);
        expect(physical.findPart('root').physics).toBe(pdg.PhysicsBody.NoPhysics);
    });
    it('selects rig controls atomically and requires explicit manual-drive handoff',function(){
        if(!sprite.supportsAnimationPhysics())return;
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();
        layer.setUseChipmunkPhysics(true);layer.setGravity(0);layer.setDamping(1);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.pauseAnimation();
        expect(sprite.enableAnimationPose('reference')).toBe(true);sprite.setupPhysicsFromAnimationRig(34);
        var body=sprite.findPart('forearm').physics,joint=body.getConstraint(0);
        expect(sprite.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Dynamic);
        expect(sprite.getAnimationPhysicsDriveSettings('forearm')).toBe(null);
        expect(function(){sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven);}).toThrow();
        expect(sprite.setAnimationPhysicsDriveSettings({maxForce:50,maxTorque:20},'forearm',true)).toBe(sprite);
        var settings=sprite.getAnimationPhysicsDriveSettings('hand');
        expect(settings.frequency).toBe(4);expect(settings.dampingRatio).toBe(1);expect(settings.direction).toBe(pdg.rotationDirection_Shortest);
        settings.maxForce=999;expect(sprite.getAnimationPhysicsDriveSettings('hand').maxForce).toBe(50);
        expect(function(){sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven);}).toThrow();
        expect(sprite.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Dynamic);
        expect(sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven,'forearm',true,0)).toBe(sprite);
        expect(sprite.getAnimationPhysicsMode('forearm',true)).toBe(pdg.animationPhysics_Driven);
        expect(sprite.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Mixed);
        expect(function(){body.setDriveTarget(new pdg.Point(0,0),0,1,1);}).toThrow();
        expect(function(){body.clearDrive();}).toThrow();
        body.setMode(pdg.physicsBody_Dynamic);
        expect(sprite.getAnimationPhysicsMode('forearm')).toBe(pdg.animationPhysics_Dynamic);
        body.setDriveTarget(new pdg.Point(10,20),0,1,1);
        body.setDriveTarget(new pdg.Point(30,40),1,2,3);
        expect(body.getDriveState().x).toBe(30);expect(body.getDriveState().maxTorque).toBe(3);
        expect(function(){sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0);}).toThrow();
        expect(sprite.getAnimationPhysicsMode('shoulder')).toBe(pdg.animationPhysics_Dynamic);
        body.clearDrive();sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0);
        expect(sprite.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Kinematic);
        expect(body.getMode()).toBe(pdg.physicsBody_Kinematic);expect(body.getConstraint(0)).toBe(joint);
        expect(function(){body.setMode(pdg.physicsBody_Static);}).toThrow();
        [null,-1,1.5,'missing',true].forEach(function(bone){
            expect(function(){sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,bone);}).toThrow();
        });
        expect(function(){sprite.setAnimationPhysicsMode(pdg.animationPhysics_Mixed);}).toThrow();
        expect(function(){sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,'forearm',1);}).toThrow();
        expect(function(){sprite.setAnimationPhysicsDriveSettings({maxForce:1},'forearm');}).toThrow();
        expect(function(){sprite.setAnimationPhysicsDriveSettings({maxForce:1,maxTorque:2,frequency:0},'forearm');}).toThrow();
        expect(function(){sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,undefined,false,-1);}).toThrow();
        expect(sprite.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Kinematic);
        sprite.disableAnimationPhysics(0);
    });
    it('reports recovery completion and keeps the physical rig until disable recovers',function(done){
        if(!sprite.supportsAnimationPhysics()){done();return;}
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();
        layer.setUseChipmunkPhysics(true);layer.setGravity(0);layer.setDamping(1);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.pauseAnimation();
        expect(sprite.enableAnimationPose('reference')).toBe(true);sprite.setupPhysicsFromAnimationRig(34);
        var completions=[];
        sprite.onAnimationPhysicsRecoveryComplete(function(event){completions.push(event);return true;});
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic);
        expect(sprite.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Driven);
        expect(sprite.findPart('hand').physics.getMode()).toBe(pdg.physicsBody_Dynamic);
        setTimeout(function(){
            expect(completions.length).toBe(0);
            expect(sprite.isAnimationPhysicsEnabled()).toBe(true);
            setTimeout(function(){
                expect(completions.length).toBe(1);
                expect(sprite.getAnimationPhysicsMode()).toBe(pdg.animationPhysics_Kinematic);
                if(completions.length){
                    expect(completions[0].actingSprite).toBe(sprite);expect(completions[0].wholeRig).toBe(true);
                    expect(completions[0].bodyCount).toBe(3);expect(completions[0].disabled).toBe(false);
                    expect(completions[0].mode).toBe(pdg.animationPhysics_Kinematic);
                }
                sprite.disableAnimationPhysics(.1);
                expect(sprite.isAnimationPhysicsEnabled()).toBe(true);
                setTimeout(function(){
                    expect(sprite.isAnimationPhysicsEnabled()).toBe(false);expect(completions.length).toBe(2);
                    if(completions.length>1)expect(completions[1].disabled).toBe(true);
                    expect(sprite.findPart('hand').physics).toBe(pdg.PhysicsBody.NoPhysics);done();
                },250);
            },600);
        },100);
    });

    it('maps partial and passive physics through final poses with explicit units', function(done){
        expect(typeof sprite.supportsAnimationPhysics()).toBe('boolean');
        ['getAnimationPhysicsBodyState','applyAnimationPhysicsImpulse','setElasticity','getElasticity','makeStatic'].forEach(function(name){expect(typeof sprite[name]).toBe('undefined');});
        if(!sprite.supportsAnimationPhysics()){
            enable();expect(function(){sprite.setupAnimationPhysics({bodies:[{bone:'shoulder',mass:1,length:10,radius:.25}]});}).toThrow();done();return;
        }
        var physicalLayer=pdg.createSpriteLayer();physicalLayer.setUseChipmunkPhysics(true);physicalLayer.enableCollisions();physicalLayer.setGravity(40);physicalLayer.setDamping(1);
        var physical=physicalLayer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');
        physical.pauseAnimation();expect(physical.enableAnimationPose('reference')).toBe(true);
        var config={version:1,rootMode:pdg.animationRoot_Follow,bodies:[
            {bone:'shoulder',mode:pdg.animationBody_Dynamic,mass:2,length:10,radius:.25,offsetX:5},
            {bone:'forearm',mass:1,length:5,radius:.25,offsetX:2.5},
            {bone:'hand',mass:1,length:2,radius:.25,offsetX:1}],
            joints:[{parent:0,child:1,parentX:5,childX:-2.5},{parent:1,child:2,parentX:2.5,childX:-1}]};
        expect((physical.physics !== pdg.PhysicsBody.NoPhysics)).toBe(false);
        config.version=2;expect(function(){physical.setupAnimationPhysics(config);}).toThrow();
        expect((physical.physics !== pdg.PhysicsBody.NoPhysics)).toBe(false);config.version=1;
        physical.setupAnimationPhysics(config);expect(physical.isAnimationPhysicsEnabled()).toBe(true);
        var state=physical.findPart("shoulder").physics.getState();physical.findPart("shoulder").physics.applyImpulse(new pdg.Vector(4,0),new pdg.Point(state.x,state.y));
        expect(physical.findPart("shoulder").physics.getState().velocityX).toBeCloseTo(2,6);
        expect(physical.findPart("missing")).toBe(null);
        var shoulderPart=physical.findPart('shoulder'), retainedBody=shoulderPart.physics;
        expect(shoulderPart.getBoneId()).toBe(0);
        expect(retainedBody.getSolver()).toBe(pdg.physicsSolver_Chipmunk);
        expect(function(){shoulderPart.removePhysicsBody();}).toThrow();
        expect(function(){shoulderPart.unbindFromBone();}).toThrow();
        expect(function(){shoulderPart.setLocation(new pdg.Point(1,2));}).toThrow();
        expect(function(){shoulderPart.setRotation(.5);}).toThrow();
        expect(function(){shoulderPart.setFlipX(true);}).toThrow();
        expect(function(){shoulderPart.setCenterOffset(new pdg.Offset(1,0));}).toThrow();
        expect(function(){physical.removePart(shoulderPart.getId());}).toThrow();
        expect(function(){physical.clearParts();}).toThrow();
        expect(function(){retainedBody.setMode(pdg.physicsBody_Static);}).toThrow();
        expect(shoulderPart.physics).toBe(retainedBody);

        var invalidImpulse=new pdg.Vector(0,0);invalidImpulse.x=NaN;
        expect(function(){physical.findPart("shoulder").physics.applyImpulse(invalidImpulse);}).toThrow();
        expect(function(){physical.setupAnimationPhysics(config);}).toThrow();
        expect(physical.isAnimationPhysicsEnabled()).toBe(true);
        setTimeout(function(){
            try{
                var body=physical.findPart("hand").physics.getState(),bone=physical.getAnimationBoneTransform('hand',pdg.animationSpace_World);
                expect(bone.x).toBeCloseTo(body.x-Math.cos(body.rotation),5);
                expect(bone.y).toBeCloseTo(body.y-Math.sin(body.rotation),5);
                expect(physical.getLocation().y).toBeGreaterThan(0);
                physical.disableAnimationPhysics(0);
                expect(physical.isAnimationPhysicsEnabled()).toBe(false);
                expect(physical.findPart("shoulder").physics).toBe(pdg.PhysicsBody.NoPhysics);
                expect(physical.findPart('shoulder')).toBe(shoulderPart);
                expect(retainedBody.getSolver()).toBe(pdg.physicsSolver_Basic);
                var velocity=retainedBody.getVelocity().x;
                retainedBody.applyImpulse(new pdg.Vector(2,0));
                expect(retainedBody.getVelocity().x).toBeCloseTo(velocity+1,5);

                config.version=2;expect(function(){physical.setupAnimationPhysics(config);}).toThrow();config.version=1;
                config.rootMode='follow';expect(function(){physical.setupAnimationPhysics(config);}).toThrow();
            }finally{pdg.cleanupLayer(physicalLayer);done();}
        },100);
    });


    it('delivers shared physical bone contacts without interpreting them as trigger payloads',function(done){
        if(!sprite.supportsAnimationPhysics()){done();return;}
        var physicalLayer=pdg.createSpriteLayer();physicalLayer.setUseChipmunkPhysics(true);physicalLayer.enableCollisions();
        physicalLayer.setGravity(0);physicalLayer.setDamping(1);
        var physical=physicalLayer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');
        physical.pauseAnimation();expect(physical.enableAnimationPose('reference')).toBe(true);
        var wall=physicalLayer.createSprite();wall.setLocation(new pdg.Point(3.9,3));
        wall.setupPhysicsBody().setMode(pdg.physicsBody_Static);
        wall.setupCollider().setCircle(1);
        var events=[];
        var onContact=function(event){events.push(event);return true;};
        var contactHandler=new pdg.IEventHandler(onContact);
        physical.addHandler(contactHandler,pdg.eventType_ColliderContact);
        physical.setupAnimationPhysics({version:1,rootMode:pdg.animationRoot_Follow,
            bodies:[{bone:'shoulder',mass:2,length:0,radius:1,friction:0}]});
        physical.findPart("shoulder").collider.setWantsContactEvents(true);
        var body=physical.findPart("shoulder").physics.getState();
        physical.findPart("shoulder").physics.applyImpulse(new pdg.Vector(4,0),new pdg.Point(body.x,body.y));
        setTimeout(function(){try{
            expect(events.length).toBeGreaterThan(0);
            if(events.length){var event=events[0];
                expect(event.collider).toBe(physical.findPart('shoulder').collider);
                expect(event.other).toBe(wall.collider);
                expect(typeof event.impulse.x).toBe('number');
                expect(event.triggerName).toBeUndefined();expect(event.timeSeconds).toBeUndefined();
            }
        }finally{pdg.cleanupLayer(physicalLayer);done();}},100);
    });

    it('delivers authored trigger payloads in seconds while samples and seeks stay silent', function(done){
        enable();sprite.enableSpriterEvents(true);var events=[];
        var handler=new pdg.IEventHandler(function(event){events.push(event);return false;});
        sprite.addHandler(handler,pdg.eventType_SpriteTriggerEvent);
        sprite.seekAnimation('reach',.24);sprite.sampleAnimationPose('reach',.75);expect(events.length).toBe(0);
        sprite.transitionToAnimation('reach',.24,.1);sprite.resumeAnimation();
        setTimeout(function(){
            sprite.pauseAnimation();expect(events.length).toBe(1);
            if(events.length){expect(events[0].triggerName).toBe('contact');expect(events[0].clipName).toBe('reach');expect(events[0].entityName).toBe('arm');expect(events[0].inLayer).toBe(layer);expect(events[0].timeSeconds).toBeCloseTo(.25,8);expect(events[0].offsetSeconds).toBeGreaterThan(0);}
            sprite.seekAnimation('reach',.8);sprite.sampleAnimationPose('reach',1.25);sprite.getAnimationPose();
            setTimeout(function(){expect(events.length).toBe(1);sprite.removeHandler(handler,pdg.eventType_SpriteTriggerEvent);done();},35);
        },80);
    });

    it('integrates spring and contact targets in seconds across moving supports',function(){
        [0,3,20,40].forEach(function(damping){var whole=new pdg.AnimationSpringTarget(1,100,damping),split=new pdg.AnimationSpringTarget(1,100,damping);whole.applyImpulse(4,2);split.applyImpulse(4,2);var expected=whole.update(10,-3,.25);for(var i=0;i<25;++i)split.update(10,-3,.01);expect(split.getState().x).toBeCloseTo(expected.x,9);expect(split.getState().velocityY).toBeCloseTo(expected.velocityY,9);});
        var spring=new pdg.AnimationSpringTarget(2,0,0);spring.applyImpulse(4,-2);expect(spring.update(0,0,.25).x).toBe(.5);expect(spring.update(999,999,0).x).toBe(.5);expect(function(){spring.update(0,0,-1);}).toThrow();expect(spring.getState().x).toBe(.5);
        var contact=new pdg.AnimationContactTarget(),frame={x:10,y:20,rotation:Math.PI/2,scaleX:1,scaleY:1,alpha:1};contact.lockPlatform(10,22,7,frame);frame.x=30;frame.rotation=0;
        var state=contact.update(.1,true,true,7,frame);expect(state.x).toBeCloseTo(32,8);expect(state.y).toBeCloseTo(20,8);
        state=contact.update(.125,true,true,8,frame,.5);expect(state.locked).toBe(false);expect(state.influence).toBe(.75);expect(contact.update(1,true,true,7,frame,.5).influence).toBe(0);
        contact.lockWorld(1,2);state=contact.update(0,true,false,0,null,.25);expect(state.locked).toBe(false);expect(state.influence).toBe(1);
        enable();var pose=sprite.sampleAnimationPose('reach',.25);expect(pdg.animationHasTag(pose,'','missing')).toBe(false);
    });


    it('drives contact windows from sampled metadata without reacquiring on liftoff',function(){
        enable();
        var contact=new pdg.AnimationContactTarget();
        var frame={x:10,y:20,rotation:0,scaleX:1,scaleY:1,alpha:1};
        contact.lockPlatform(12,20,1,frame);
        var stance=sprite.sampleAnimationPose('reach',.25);
        expect(pdg.animationHasTag(stance,'grip','contact')).toBe(true);
        frame.x=13;
        var state=contact.update(.025,pdg.animationHasTag(stance,'grip','contact'),true,1,frame,.2);
        expect(state.locked).toBe(true);expect(state.x).toBeCloseTo(15,8);
        var flight=sprite.sampleAnimationPose('reach',.75);
        expect(pdg.animationHasTag(flight,'grip','contact')).toBe(false);
        state=contact.update(.05,pdg.animationHasTag(flight,'grip','contact'),true,1,frame,.2);
        expect(state.locked).toBe(false);expect(state.influence).toBeCloseTo(.75,8);
        frame.x=30;state=contact.update(.05,true,true,1,frame,.2);
        expect(state.x).toBeCloseTo(15,8);expect(state.influence).toBeCloseTo(.5,8);
        expect(sprite.isAnimationPlaying()).toBe(false);
    });

    it('owns bone drawing registrations and expires borrowed drawing contexts',function(done){
        var drawingPort,ownedPort=false;
        var canDraw=sprite.isAnimationDrawingSupported() && (pdg.gfx.getMainPort() || pdg.gfx.getNumScreens()>0);
        if(sprite.isAnimationDrawingSupported() && !canDraw)console.log("Animation drawing callbacks: no display in this client session; registration checks only.");
        if(canDraw){
            drawingPort=pdg.gfx.getMainPort();
            if(!drawingPort){drawingPort=pdg.gfx.createWindowPort(new pdg.Rect(0,0,320,240),'Animation drawing acceptance');ownedPort=true;}
            pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer(drawingPort);layer.setUseChipmunkPhysics(false);
            sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.pauseAnimation();
        }
        enable();var calls=0,retained,owned,order=[],added=0,pixelChecks=0,nestedPixels=0,editedPixels=0;
        var artwork=pdg.createDrawing();
        artwork.addLine(new pdg.Point(0,0),new pdg.Point(2,0),new pdg.Attributes().lineColor('red').lineOpacity(.5).lineThickness(2));
        artwork.addRect(new pdg.Rect(0,0,2,1),new pdg.Attributes().lineColor('green'));
        artwork.addRect(new pdg.Rect(100,100,120,120),new pdg.Attributes().fillColor('magenta'));
        var drawingResources=canDraw?pdg.res.openResourceFile(process.cwd()+'/data'):0;
        var drawingImage=canDraw?pdg.res.getImage('earthmap2.png'):null;
        if(canDraw){expect(drawingImage).toBeTruthy();
            artwork.addImage(new pdg.Rect(30,20,40,30),drawingImage,new pdg.Attributes().fillOpacity(.5));
        }
        var nested=pdg.createDrawing(), persistentArtwork=pdg.createDrawing();
        var nestedElement=nested.addRect(new pdg.Rect(0,0,10,10),new pdg.Attributes().fillColor('cyan'));
        persistentArtwork.addDrawing(new pdg.Rect(160,100,180,120),nested,new pdg.Attributes());
        var persistent=sprite.addAnimationDrawable(persistentArtwork,{bone:'hand',placement:pdg.animationDraw_AfterAll,strokeSpace:pdg.animationStroke_Local});
        // Embind permits explicit wrapper deletion. Native owners retain editable contents.
        if(typeof persistentArtwork.delete==='function'){persistentArtwork.delete();nested.delete();}
        var invalid=sprite.addAnimationDrawable(function(){return [];},{bone:'hand'});
        var asynchronous=sprite.addAnimationDrawable(function(){return Promise.resolve(artwork);},{bone:'hand'});
        expect(function(){sprite.addAnimationDrawable(artwork,{bone:'hand',strokeSpace:'local'});}).toThrow();
        var browserPixels=canDraw && typeof window!=='undefined' && window.Module && window.Module.ctx;
        if(browserPixels)layer.onPostDrawLayer(function(){
            var gl=window.Module.ctx,canvas=window.Module.canvas,pixel=new Uint8Array(4);
            gl.readPixels(115,canvas.height-110,1,1,gl.RGBA,gl.UNSIGNED_BYTE,pixel);
            if(pixel[0]>245 && pixel[1]<10 && pixel[2]>245)++pixelChecks;
            gl.readPixels(185,canvas.height-110,1,1,gl.RGBA,gl.UNSIGNED_BYTE,pixel);
            if(pixel[0]<10 && pixel[1]>245 && pixel[2]>245){
                ++nestedPixels;
                nestedElement.setAttributes(new pdg.Attributes().fillColor('yellow'));
            }
            if(pixel[0]>245 && pixel[1]>245 && pixel[2]<10)++editedPixels;
            return false;
        });
        var options={bone:'forearm',placement:pdg.animationDraw_BeforeAll};
        var id=sprite.addAnimationDrawable(function(context){
            ++calls;order.push('before');retained=context;owned=context.copyPose();
            expect(context.getTransform(pdg.animationSpace_Rig).x).toBeCloseTo(12,6);
            if(!added)added=sprite.addAnimationDrawable(function(){order.push('added');return null;},{bone:'hand',placement:pdg.animationDraw_AfterAll});
            return artwork;
        },options);
        var bad=sprite.addAnimationDrawable(function(context){throw new Error('script draw failure');},{bone:'hand',placement:pdg.animationDraw_AfterAll});
        expect(function(){sprite.addAnimationDrawable(function(){},{bone:'missing'});}).toThrow();
        expect(function(){sprite.addAnimationDrawable(function(){},{bone:'hand',placement:'afterAll'});}).toThrow();
        expect(function(){sprite.addAnimationDrawable(function(){},{bone:'hand',placement:pdg.animationDraw_ReplaceSlot,slot:'missing'});}).toThrow();
        expect(function(){sprite.setAnimationDrawableEnabled(id,1);}).toThrow();
        expect(sprite.getAnimationDrawBounds().uncullable).toBe(true);
        if(!canDraw){
            expect(calls).toBe(0);sprite.clearAnimationDrawables();expect(function(){sprite.getAnimationDrawableError(id);}).toThrow();done();return;
        }
        // Observe actual draw completion; a busy/headless browser can render
        // fewer than two frames during an arbitrary 100 ms wall-clock delay.
        var drawDeadline = Date.now() + 2000;
        setTimeout(function waitForDrawing(){
            if ((calls < 2 || order.indexOf('added') < 0 || (browserPixels && editedPixels === 0)) && Date.now() < drawDeadline) {
                setTimeout(waitForDrawing, 16); return;
            }
            expect(calls).toBeGreaterThan(0);
            expect(sprite.getAnimationDrawableError(invalid)).toContain('Drawing or null');
            expect(sprite.getAnimationDrawableError(asynchronous)).toContain('synchronous');
            if(browserPixels){expect(pixelChecks).toBeGreaterThan(0);expect(nestedPixels).toBeGreaterThan(0);expect(editedPixels).toBeGreaterThan(0);}
            if(calls){expect(function(){retained.getTransform();}).toThrow();expect(function(){retained.copyPose();}).toThrow();expect(owned.bones.length).toBe(3);expect(order.indexOf('added')).toBeGreaterThan(0);}
            expect(sprite.getAnimationDrawableError(id)).toBe('');expect(sprite.getAnimationDrawableError(bad)).toContain('script draw failure');
            expect(function(){sprite.setAnimationDrawableEnabled(bad,true);}).toThrow();
            sprite.setAnimationDrawableEnabled(id,false);sprite.removeAnimationDrawable(id);expect(function(){sprite.getAnimationDrawableError(id);}).toThrow();
            sprite.clearAnimationDrawables();pdg.cleanupLayer(layer);layer=null;if(drawingResources)pdg.res.closeResourceFile(drawingResources);if(ownedPort)pdg.gfx.closeGraphicsPort(drawingPort);done();
        },16);
    });

    it('reports unsupported rigs while leaving ordinary playback available', function() {
        var plain = layer.createSprite();
        expect(plain.enableAnimationPose('reference')).toBe(false);
        expect(plain.getAnimationRigError().length > 0).toBe(true);
        var unsupported = layer.createSpriteFromSpriterFile(process.cwd() + '/data/spriter-regression/changing-arm.scml');
        expect(unsupported.enableAnimationPose('reference')).toBe(false);
        expect(unsupported.getAnimationRigError()).toMatch(/hierarchy/);
        expect(unsupported.isAnimationPlaying()).toBe(true);
        expect(unsupported.hasAnimation('reach')).toBe(true);
    });
});
