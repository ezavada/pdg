describe('Procedural animation',function(){
    function chain(count,layer){const sprite=layer?layer.createSprite():new pdg.Sprite(),parts=[];for(let i=0;i<count;++i){const p=sprite.createPart('p'+i);if(i)p.setParentPart(parts[i-1]).setLocation(10,0);parts.push(p);}return {sprite,parts,root:parts[0]};}
    function world(part){const t=part.getTransform(pdg.partSpace_World);return {x:t.tx,y:t.ty};}
    it('reaches long Part chains, preserves geometry and reports bounded failure',function(){
        const c=chain(9),target=new pdg.Point(35,23),result=c.root.solveFABRIK(c.parts.slice(1),target,{maxIterations:128,tolerance:.001});
        expect(result.reached).toBe(true);expect(Math.hypot(world(c.parts[8]).x-35,world(c.parts[8]).y-23)).toBeLessThan(.001);
        for(let i=1;i<9;++i){const a=world(c.parts[i-1]),b=world(c.parts[i]);expect(Math.hypot(b.x-a.x,b.y-a.y)).toBeCloseTo(10,4);}
        const before=c.root.getRotation();expect(()=>c.root.solveFABRIK([c.parts[2]],target)).toThrow();expect(c.root.getRotation()).toBe(before);
        const far=c.root.solveFABRIK(c.parts.slice(1),new pdg.Point(1000,0));expect(far.reached).toBe(false);expect(far.withinGeometricReach).toBe(false);expect(far.iterations).toBeLessThan(17);
        c.sprite.clearParts();
    });
    it('maintains scheduled FABRIK with live limits and exclusive channels',function(){
        const c=chain(5);c.parts[1].setIKLimits(-.3,.3);c.root.setFABRIKTarget(c.parts.slice(1),new pdg.Point(20,18),{maxIterations:128});c.root.animate(.01);
        expect(c.root.hasIKTarget()).toBe(true);expect(Math.abs(c.parts[1].getRotation())).toBeLessThan(.30001);
        expect(()=>c.root.setJiggle({mode:pdg.jiggleMode_Chain,chain:c.parts.slice(1),length:10})).toThrow();
        c.root.clearIKTarget();expect(c.root.hasIKTarget()).toBe(false);c.sprite.clearParts();
    });
    it('adds spring lag to Part IK targets without replacing the desired target',function(){
        const c=chain(3);c.root.setIKTarget(c.parts[1],c.parts[2],new pdg.Point(20,0));c.root.setJiggle({mode:pdg.jiggleMode_IKTarget});
        c.root.setIKTarget(c.parts[1],c.parts[2],new pdg.Point(10,10));c.root.animate(1/60);
        const r=c.root.getJiggleResult();expect(r.desiredTarget.x).toBe(10);expect(r.effectiveTarget.x).toBeGreaterThan(10);expect(r.effectiveTarget.x).toBeLessThan(20);
        const state=c.root.getJiggleState();c.root.getJiggleResult();expect(c.root.getJiggleState()).toEqual(state);
        c.root.setJiggleEnabled(false);c.root.animate(1/60);expect(c.root.getJiggleState()).toEqual(state);expect(c.root.isIKTargetReached()).toBe(true);
        c.root.setJiggleEnabled(true);c.root.animate(1/60);expect(c.root.getJiggleState().velocityX).toBe(0);
        c.root.clearIKTarget();expect(c.root.hasJiggle()).toBe(false);c.sprite.clearParts();
    });
    it('jiggles each Part joint while preserving the programmed base and state',function(){
        const c=chain(4);c.root.setJiggle({mode:pdg.jiggleMode_Chain,chain:c.parts.slice(1),length:10});c.root.kickJiggle({angularVelocity:2});c.root.animate(1/60);
        expect(c.root.getRotation()).toBeGreaterThan(0);const state=c.root.getJiggleState();expect(()=>c.root.setJiggleState(Object.assign({},state,{chain:[999]}))).toThrow();c.root.setJiggleState(state);expect(c.root.getJiggleState()).toEqual(state);
        expect(()=>c.root.solveIK(c.parts[1],c.parts[2],new pdg.Point(12,3))).toThrow();
        c.root.setJiggleInfluence(0,.05);for(let i=0;i<4;++i)c.root.animate(1/60);expect(c.root.getRotation()).toBeCloseTo(0,5);
        c.root.clearJiggle();expect(c.root.getRotation()).toBeCloseTo(0,5);c.sprite.clearParts();
    });
    it('supports sparse per-joint tuning and rejects invalid overrides atomically',function(){
        const c=chain(3);c.root.setJiggle({mode:pdg.jiggleMode_Chain,chain:c.parts.slice(1),length:10,joints:[{part:c.parts[1],frequency:8,dampingRatio:1},{part:c.root,dampingRatio:.2}]});
        expect(c.root.getJiggleOptions().joints[0].frequency).toBe(8);expect(c.root.getJiggleOptions().joints[1].bone).toBe(c.root.getId());
        c.root.setJiggleSettings({frequency:2});expect(c.root.getJiggleOptions().joints[0].frequency).toBe(8);
        const before=c.root.getJiggleOptions();expect(()=>c.root.setJiggleSettings({joints:[{part:c.parts[1],frequency:-1}]})).toThrow();expect(c.root.getJiggleOptions()).toEqual(before);
        c.root.clearJiggle();c.sprite.clearParts();
    });
    it('restores native Part jiggle and FABRIK controllers in both snapshot modes',function(){
        for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]){
            for(const kind of ['jiggle','fabrik']){const c=chain(4);
                if(kind==='jiggle'){c.root.setJiggle({mode:pdg.jiggleMode_Chain,chain:c.parts.slice(1),length:10});c.root.kickJiggle({angularVelocity:2});c.root.animate(1/60);}
                else{c.root.setFABRIKTarget(c.parts.slice(1),new pdg.Point(15,10));c.root.animate(1/60);}
                const writer=new pdg.Serializer(),reader=new pdg.Deserializer();writer.setResourceMode(mode);writer.serialize_obj(c.sprite);reader.setDataPtr(writer.getDataPtr());const copy=reader.deserialize_obj(),root=copy.findPart('p0');
                if(kind==='jiggle'){expect(root.hasJiggle()).toBe(true);expect(root.getJiggleState()).toEqual(c.root.getJiggleState());for(let frame=0;frame<12;++frame){root.animate(1/60);c.root.animate(1/60);}expect(root.getRotation()).toBeCloseTo(c.root.getRotation(),5);expect(root.getJiggleState()).toEqual(c.root.getJiggleState());}else{expect(root.hasIKTarget()).toBe(true);root.animate(1/60);expect(root.getFABRIKResult().reachError).toBeLessThan(.02);}
                copy.clearParts();c.sprite.clearParts();
            }
        }
    });
    it('filters skeletal IK during paused clip playback and removes dependent decorators',function(){
        const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(false);
        if(typeof layer.createSpriteFromSpriterFile!=='function'){pdg.cleanupLayer(layer);pending('Spriter disabled');return;}
        try{const sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.enableAnimationPose('reference');sprite.pauseAnimation();
            const ik=sprite.addAnimationIK({root:'shoulder',middle:'forearm',tip:'hand',targetX:15,targetY:0});const j=sprite.addAnimationJiggle({mode:pdg.jiggleMode_IKTarget,ik:ik});
            sprite.setAnimationIKTarget(ik,8,8);sprite.getAnimationPose();expect(sprite.getAnimationJiggleState(j).velocityX).toBe(0);
            sprite.removeAnimationModifier(ik);expect(()=>sprite.getAnimationJiggleState(j)).toThrow();
            const f=sprite.addAnimationFABRIK({chain:['shoulder','forearm','hand'],targetX:10,targetY:5,maxIterations:128,tolerance:.001});expect(sprite.getAnimationFABRIKResult(f).reached).toBe(true);
            expect(()=>sprite.addAnimationJiggle({mode:pdg.jiggleMode_Chain,chain:['shoulder','forearm'],length:10})).toThrow();sprite.removeAnimationModifier(f);
            const sway=sprite.addAnimationJiggle({mode:pdg.jiggleMode_Chain,chain:['shoulder','forearm','hand'],length:10});sprite.kickAnimationJiggle(sway,{joint:'hand',angularVelocity:2});const saved=sprite.getAnimationJiggleState(sway);sprite.getAnimationPose();expect(sprite.getAnimationJiggleState(sway)).toEqual(saved);
            expect(()=>sprite.addAnimationIK({root:'shoulder',middle:'forearm',tip:'hand'})).toThrow();
        }finally{pdg.cleanupLayer(layer);}
    });
    it('continues Part jiggle after incremental Layer updates',function(){
        const source=pdg.createSpriteLayer(),copy=pdg.createSpriteLayer();source.setUseChipmunkPhysics(false);copy.setUseChipmunkPhysics(false);
        try{const c=chain(4,source);c.root.setJiggle({mode:pdg.jiggleMode_Chain,chain:c.parts.slice(1),length:10});
            function send(flags){source.setSerializationFlags(flags);const w=new pdg.Serializer(),r=new pdg.Deserializer();source.serialize(w);r.setDataPtr(w.getDataPtr());copy.deserialize(r);}
            send(pdg.ser_Full);c.root.setRotation(.2);c.root.kickJiggle({angularVelocity:3});c.root.setJiggleInfluence(.6,.2);for(let i=0;i<5;++i)c.root.animate(1/60);
            send(pdg.ser_Animations);const root=copy.getNthSprite(0).findPart('p0');expect(root.getJiggleState()).toEqual(c.root.getJiggleState());
            for(let i=0;i<8;++i){root.animate(1/60);c.root.animate(1/60);}expect(root.getRotation()).toBeCloseTo(c.root.getRotation(),5);expect(root.getJiggleOptions().influence).toBeCloseTo(c.root.getJiggleOptions().influence,8);
        }finally{pdg.cleanupLayer(source);pdg.cleanupLayer(copy);}
    });
    it('saves skeletal native procedural modifiers without treating them as callbacks',function(){
        const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(false);
        try{for(const kind of ['target','chain','fabrik'])for(const mode of [pdg.serialization_Complete,pdg.serialization_ExternalReferences]){
            const sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.enableAnimationPose('reference');sprite.pauseAnimation();let id;
            if(kind==='fabrik')id=sprite.addAnimationFABRIK({chain:['shoulder','forearm','hand'],targetX:9,targetY:7,maxIterations:128});
            else if(kind==='target'){const ik=sprite.addAnimationIK({root:'shoulder',middle:'forearm',tip:'hand',targetX:15,targetY:0});id=sprite.addAnimationJiggle({mode:pdg.jiggleMode_IKTarget,ik:ik});sprite.kickAnimationJiggle(id,{velocityX:4});}
            else{id=sprite.addAnimationJiggle({mode:pdg.jiggleMode_Chain,chain:['shoulder','forearm','hand'],length:10});sprite.kickAnimationJiggle(id,{joint:'hand',angularVelocity:2});}
            const w=new pdg.Serializer(),r=new pdg.Deserializer();w.setResourceMode(mode);sprite.serialize(w);r.setDataPtr(w.getDataPtr());const copy=new pdg.Sprite();copy.deserialize(r);
            if(kind==='fabrik')expect(copy.getAnimationFABRIKResult(id).reachError).toBeLessThan(.02);
            else {const saved=sprite.getAnimationJiggleState(id),restored=copy.getAnimationJiggleState(id);expect(restored.rigRevision).toBe(copy.getAnimationPose().rigRevision);expect(Object.assign({},restored,{rigRevision:saved.rigRevision})).toEqual(saved);expect(()=>copy.setAnimationJiggleState(id,saved)).toThrow();}copy.disableAnimationPose();
        }}finally{pdg.cleanupLayer(layer);}
    });
    it('advances skeletal target jiggle on simulation time while the clip is paused',function(done){
        const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(false);
        const sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');sprite.enableAnimationPose('reference');sprite.pauseAnimation();
        const ik=sprite.addAnimationIK({root:'shoulder',middle:'forearm',tip:'hand',targetX:15,targetY:0}),id=sprite.addAnimationJiggle({mode:pdg.jiggleMode_IKTarget,ik:ik});sprite.setAnimationIKTarget(ik,8,8);
        setTimeout(function(){try{const state=sprite.getAnimationJiggleState(id);expect(Math.abs(state.velocityX)+Math.abs(state.velocityY)).toBeGreaterThan(0);expect(sprite.getAnimationJiggleResult(id).simulatedSeconds).toBeGreaterThan(0);sprite.getAnimationPose();expect(sprite.getAnimationJiggleState(id)).toEqual(state);}finally{pdg.cleanupLayer(layer);done();}},100);
    });
    it('filters physical IK drives while preserving their bodies and colliders',function(){
        const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);layer.setGravity(0);
        try{const c=chain(3,layer),a=c.root.setupPhysicsBody(1,20),b=c.parts[1].setupPhysicsBody(1,20),collider=c.parts[1].setupCollider().setCircle(2);
            c.root.setIKDriveTarget(c.parts[1],c.parts[2],new pdg.Point(20,0),3000,3000);c.root.setJiggle({mode:pdg.jiggleMode_IKTarget});
            c.root.setIKDriveTarget(c.parts[1],c.parts[2],new pdg.Point(10,10),3000,3000);c.root.animate(1/60);
            expect(c.root.getJiggleResult().effectiveTarget.x).toBeGreaterThan(10);expect(c.parts[1].physics).toBe(b);expect(c.parts[1].collider).toBe(collider);expect(a.isDriveEnabled()).toBe(true);expect(b.isDriveEnabled()).toBe(true);expect(c.root.getIKError()).toBe('');
            c.root.clearIKTarget();expect(c.root.hasJiggle()).toBe(false);
        }finally{pdg.cleanupLayer(layer);}
    });

});
