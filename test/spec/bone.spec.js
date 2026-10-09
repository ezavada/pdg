describe('Animated bones',function(){
    var layer,sprite,bone;
    beforeEach(function(){
        layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(false);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');
        expect(sprite.enableAnimationPose('reference')).toBe(true);sprite.pauseAnimation();bone=sprite.getBone('hand');
    });
    afterEach(function(){pdg.cleanupLayer(layer);});
    it('returns stable rig-scoped handles and invalidates replaced rigs',function(){
        expect(typeof bone.scaleTo).toBe('undefined');expect(typeof bone.scaleBy).toBe('undefined');
        expect(bone.getName()).toBe('hand');expect(sprite.getBone(bone.getId())).toBe(bone);expect(bone.getSprite()).toBe(sprite);expect(function(){new pdg.Serializer().serialize_obj(bone);}).toThrow();
        sprite.disableAnimationPose();expect(bone.isAttached()).toBe(false);expect(function(){bone.getName();}).toThrow();expect(function(){bone.moveBy(1,0);}).toThrow();
    });
    it('adds motion to fresh samples without accumulating pose evaluation',function(){
        var original=sprite.getAnimationBoneTransform('hand');bone.moveBy(6,0,.5,pdg.linearTween);bone.animate(.25);
        expect(sprite.getAnimationBoneTransform('hand').x).toBeCloseTo(original.x+3,5);
        expect(sprite.getAnimationBoneTransform('hand').x).toBeCloseTo(original.x+3,5);
        bone.animate(.25);expect(sprite.getAnimationBoneTransform('hand').x).toBeCloseTo(original.x+6,5);
    });
    it('overrides only selected channels and eases influence to authored motion',function(){
        var original=sprite.getAnimationBoneTransform('hand');bone.rotateTo(1,.5,pdg.linearTween);bone.animate(.5);
        expect(sprite.getAnimationBoneTransform('hand').rotation).toBeCloseTo(1,5);
        expect(sprite.getAnimationBoneTransform('hand').x).toBeCloseTo(original.x,5);
        bone.diminish(0,.25);bone.animate(.125);expect(sprite.getAnimationBoneTransform('hand').rotation).toBeCloseTo((1+original.rotation)/2,5);
        bone.animate(.125);expect(sprite.getAnimationBoneTransform('hand').rotation).toBeCloseTo(original.rotation,5);
    });
    it('clamps scripted rotations and permits releasing limits',function(){
        bone.setIKLimits(-.3,.4).rotateTo(2);expect(sprite.getAnimationBoneTransform('hand').rotation).toBeCloseTo(.4,5);
        bone.rotateTo(2*Math.PI+.2);expect(bone.getRotation()).toBeCloseTo(.2,4);
        bone.clearIKLimits();bone.rotateTo(2);expect(sprite.getAnimationBoneTransform('hand').rotation).toBeCloseTo(2,5);
    });
    it('resizes child connection distances without scaling descendants',function(){
        var parent=sprite.getBone('forearm'),local=sprite.getAnimationBoneTransform('hand'),size=parent.getSize();
        parent.resizeTo(size.x,size.y*2,0);var after=sprite.getAnimationBoneTransform('hand');
        expect(Math.hypot(after.x,after.y)).toBeCloseTo(Math.hypot(local.x,local.y)*2,4);
        expect(after.scaleX).toBe(local.scaleX);expect(after.scaleY).toBe(local.scaleY);
    });

    it('keeps offsets tied to the advancing authored animation',function(){
        sprite.startAnimation('reach');sprite.resumeAnimation();
        bone.rotateBy(.5);sprite.seekAnimation('reach',.3);
        var sample=sprite.sampleAnimationPose('reach',.3).bones[bone.getId()];
        expect(bone.getRotation()).toBeCloseTo(sample.rotation+.5,4);
        sprite.seekAnimation('reach',.6);sample=sprite.sampleAnimationPose('reach',.6).bones[bone.getId()];
        expect(bone.getRotation()).toBeCloseTo(sample.rotation+.5,4);
        bone.diminish(0,.25);bone.animate(.25);expect(bone.getRotation()).toBeCloseTo(sample.rotation,4);
    });
    it('preserves relative resize, stretch, scale and attachment semantics',function(){
        var size=bone.getSize(),anchor=bone.getCenterOffset(),scale=bone.getScale();
        bone.resizeBy(2,3,.1,pdg.linearTween).animate(.1);
        expect(bone.getWidth()).toBeCloseTo(size.x+2,4);expect(bone.getHeight()).toBeCloseTo(size.y+3,4);
        bone.diminish(0,0);bone.stretch(2,3,.1,pdg.linearTween).animate(.1);
        expect(bone.getWidth()).toBeCloseTo(size.x*2,4);expect(bone.getHeight()).toBeCloseTo(size.y*3,4);
        bone.diminish(0,0);bone.changeScaleBy(1,2,.1,pdg.linearTween).animate(.1);
        expect(bone.getScale().x).toBeCloseTo(scale.x+1,4);expect(bone.getScale().y).toBeCloseTo(scale.y+2,4);
        bone.changeCenterOffsetBy(new pdg.Offset(2,3),.1,pdg.linearTween).animate(.1);
        expect(bone.getCenterOffset().x).toBeCloseTo(anchor.x+2,4);expect(bone.getCenterOffset().y).toBeCloseTo(anchor.y+3,4);
    });
    it('propagates scale and reflection while restoring flips on release',function(){
        var parent=sprite.getBone('forearm'),before=sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig);
        parent.changeScaleTo(2,2,0);var scaled=sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig);
        expect(scaled.scaleX).toBeCloseTo(before.scaleX*2,4);
        parent.flipX();expect(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).scaleX).toBeLessThan(0);
        parent.diminish(0,0);expect(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).scaleX).toBeCloseTo(before.scaleX,4);
        parent.moveBy(1,0);expect(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig).scaleX).toBeCloseTo(before.scaleX,4);
    });
    it('sequences waits, pause, completion and influence release',function(){
        var base=bone.getRotation(),done=0;
        bone.series().rotateBy(1,.1,pdg.linearTween).wait(.1).diminish(0,.1,pdg.linearTween).endSeries().onFinished(function(event){expect(event.target).toBe(bone);++done;});
        bone.animate(.1);expect(bone.getRotation()).toBeCloseTo(base+1,4);
        bone.pauseSchedule();bone.animate(.1);expect(bone.getRotation()).toBeCloseTo(base+1,4);
        bone.resumeSchedule();bone.animate(.15);expect(bone.getRotation()).toBeCloseTo(base+.5,4);
        bone.animate(.051);expect(bone.getRotation()).toBeCloseTo(base,4);expect(done).toBe(1);
    });
    it('reuses Part IK limits and live physical rotary limits',function(){
        var p=sprite.createPart('forearm'),child=sprite.createPart('hand');p.bindToBone(sprite.getBone('forearm').getId());child.bindToBone(bone.getId());
        child.setIKLimits(-.2,.3);bone.rotateTo(2);expect(bone.getRotation()).toBeCloseTo(.3,4);child.clearIKLimits();
        var a=p.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic),b=child.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic),limit=a.createRotaryLimit(b,-.2,.3);
        bone.setIKLimits(limit);expect(bone.getRotation()).toBeCloseTo(.3,4);
        limit.setAngleLimits(-.1,.1);bone.rotateTo(2);expect(bone.getRotation()).toBeCloseTo(.1,4);
        limit.setAngleLimits(-.2,.4);sprite.flipX();bone.rotateTo(2);expect(bone.getRotation()).toBeCloseTo(.2,4);
        limit.disconnect();bone.rotateTo(2);expect(bone.getRotation()).toBeCloseTo(2,4);
        var reversed=b.createRotaryLimit(a,-.6,-.1);bone.setIKLimits(reversed).rotateTo(2);
        expect(bone.getRotation()).toBeCloseTo(-.1,4);
    });
    it('clamps final modifier output and preserves attachment through repeated flips',function(){
        bone.setIKLimits(-.2,.3);
        sprite.addAnimationModifier(function(view){view.rotateLocal('hand',2);},pdg.animationStage_PostConstraint,0);
        expect(bone.getRotation()).toBeCloseTo(.3,4);
        var anchor=bone.getCenterOffset();bone.flipX().flipX();
        expect(bone.getCenterOffset().x).toBeCloseTo(anchor.x,4);
        expect(bone.getCenterOffset().y).toBeCloseTo(anchor.y,4);
    });
    it('permits negative resize offsets while rejecting negative resulting dimensions',function(){
        var parent=sprite.getBone('forearm'),size=parent.getSize();
        parent.resizeBy(-size.x/2,-size.y/2,.1,pdg.linearTween).animate(.1);
        expect(parent.getSize().x).toBeCloseTo(size.x/2,4);expect(parent.getSize().y).toBeCloseTo(size.y/2,4);
        expect(function(){parent.resizeTo(-1,1,0);}).toThrow();expect(sprite.isAnimationPoseEnabled()).toBe(true);
    });
    it('plays shared scripts with independent channel modes and yoyo',function(){
        var name='bone-spec-relative-absolute';
        pdg.Bone.defineScript(name).series().rotateBy(.5,.1,pdg.linearTween).rotateTo(1,.1,pdg.linearTween).endSeries().endScript();
        try {
            bone.playScript(name).animate(.1);expect(bone.getRotation()).toBeCloseTo(.5,4);
            bone.animate(.05);expect(bone.getRotation()).toBeCloseTo(.75,4);bone.animate(.05);expect(bone.getRotation()).toBeCloseTo(1,4);
            bone.rotateBy(.5,.1,pdg.linearTween).yoyo().animate(.2);expect(bone.getRotation()).toBeCloseTo(1,4);
        } finally {pdg.Bone.deleteScript(name);}
    });
    it('starts absolute moves from resized attachments and clamped rotations',function(){
        var parent=sprite.getBone('forearm'),size=parent.getSize();parent.resizeTo(size.x,size.y*2,0);
        var before=bone.getLocation();bone.moveTo(4,0,.2,pdg.linearTween).animate(.1);
        expect(bone.getLocation().x).toBeCloseTo((before.x+4)/2,4);
        bone.setIKLimits(-.2,.3).rotateTo(2);bone.rotateTo(0,.2,pdg.linearTween).animate(.1);
        expect(bone.getRotation()).toBeCloseTo(.15,4);
    });
    it('supports zero dimensions and restores proportional connections',function(){
        var parent=sprite.getBone('forearm'),size=parent.getSize(),before=sprite.getAnimationBoneTransform('hand');
        parent.resizeTo(0,0,0);expect(sprite.getAnimationBoneTransform('hand').x).toBeCloseTo(0,4);
        parent.resizeTo(size.x,size.y,0);expect(sprite.getAnimationBoneTransform('hand').x).toBeCloseTo(before.x,4);
        expect(parent.getBoundingBox().width()).toBeGreaterThan(0);
    });

    it('resizes physical capsules and joint anchors without resizing child bodies',function(){
        if(!sprite.supportsAnimationPhysics())return;
        pdg.cleanupLayer(layer);layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
        sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.enableAnimationPose('reference');sprite.pauseAnimation();sprite.setupPhysicsBody();
        sprite.setupAnimationPhysics({bodies:[
            {bone:'shoulder',mass:1,length:10,radius:.25,offsetX:5},
            {bone:'forearm',mass:1,length:5,radius:.25,offsetX:2.5},
            {bone:'hand',mass:1,length:2,radius:.25,offsetX:1}
        ],joints:[{parent:0,child:1,parentX:5,childX:-2.5},{parent:1,child:2,parentX:2.5,childX:-1}]});
        expect(function(){sprite.getBone('forearm').changeScaleBy(1,1,0);}).toThrow();
        expect(function(){sprite.getBone('forearm').flipX();}).toThrow();
        expect(sprite.isAnimationPhysicsEnabled()).toBe(true);
        var parent=sprite.getBone('forearm'),part=sprite.findPart('forearm'),child=sprite.findPart('hand'),size=parent.getSize();
        var shape=part.collider.getShapeId(0),childShape=child.collider.getShapeId(0),childEnd=child.collider.getCapsuleEnd(childShape).x;
        var joints=[];for(var i=0;i<part.physics.getConstraintCount();++i){var joint=part.physics.getConstraint(i);if(joint.getType()===pdg.constraint_Pivot)joints.push({joint:joint,a:joint.getAnchorA(),b:joint.getAnchorB(),parentIsA:joint.getBodyA()===part.physics});}
        parent.resizeTo(size.x,size.y*2,0);sprite.getAnimationPose();shape=part.collider.getShapeId(0);
        expect(part.collider.getCapsuleEnd(shape).x).toBeCloseTo(5.25,4);
        expect(parent.getBoundingBox().width()).toBeCloseTo(11,4);
        expect(child.collider.getCapsuleEnd(childShape).x).toBeCloseTo(childEnd,4);
        joints.forEach(function(item){expect((item.parentIsA?item.joint.getAnchorA():item.joint.getAnchorB()).x).toBeCloseTo((item.parentIsA?item.a:item.b).x*2,4);});
        parent.diminish(0,0);sprite.getAnimationPose();shape=part.collider.getShapeId(0);expect(part.collider.getCapsuleEnd(shape).x).toBeCloseTo(2.5,4);
    });
});
