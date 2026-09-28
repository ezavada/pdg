// Run from the repository root: ./test/rigs human/membership
'use strict';
const assert=require('assert'),path=require('path'),pdg=require('pdg');
const {bones,pixelsPerCm:scale}=require('../../data/human-rig/human');
const {plantFeet}=require('../../data/human-rig/ground');
const {createArmBlocker}=require('../../data/human-rig/arm-blocker');
const {createRagdoll}=require('../../data/human-rig/ragdoll');
const {createMembership}=require('../../data/human-rig/membership');
const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
const origin=new pdg.Point(422,668),now=()=>pdg.tm.getMilliseconds()/1000;
sprite.setLocation(origin);sprite.setScale(scale,scale);sprite.enableAnimationPose('reference');sprite.pauseAnimation();
const ground=plantFeet(pdg,sprite),blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
const rig=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now),membership=createMembership(pdg,sprite,rig,scale);
const forearm=sprite.findPart('right_forearm'),hand=sprite.findPart('right_hand');
const limbMass=forearm.physics.getMass()+hand.physics.getMass();
let phase='settle',started=now(),finished=false,fallStart,maxGripGap=0,maxWristGap=0;
const near=(actual,expected)=>assert(Math.abs(actual-expected)<1e-7,actual+' != '+expected);
function stop(error) {
    if(finished)return;finished=true;
    if(error){console.error(error.stack);process.exitCode=1;}
    else console.log('PASS: membership API, 10 kg load, elbow separation, connected detached wrist, subtree mass, restoration and recovery.\n'+
        JSON.stringify({limbMass,maxGripGap,maxWristGap,contacts:membership.contacts}));
    setTimeout(()=>{pdg.cleanupLayer(layer);pdg.quit();},0);
}
function next(value){phase=value;started=now();}
layer.onPreAnimateLayer(()=> {
    if(finished)return false;
    try {
        rig.updateGround();membership.update();
        const elapsed=now()-started;assert(elapsed<20,'Stalled in '+phase+' / '+rig.phase);
        if(phase==='settle' && elapsed>.2) {
            assert.throws(()=>sprite.attachAnimationPhysicsPart('right_hand'),/Part/);
            assert.throws(()=>sprite.detachAnimationPhysicsPart(hand,'yes'),/boolean/);
            assert(membership.toggleWeight());near(sprite.physics.getMass(),60);
            assert(sprite.isAnimationPhysicsPartAttached(membership.weight));
            assert.strictEqual(sprite.getAnimationPhysicsMode('right_upper_arm',true),pdg.animationPhysics_Driven);
            next('loaded');
        } else if(phase==='loaded' && elapsed>1.5) {
            const before=forearm.physics.getState();
            assert(membership.toggleArm());near(sprite.physics.getMass(),50-limbMass);
            assert.deepStrictEqual(forearm.physics.getState(),before,'Detachment changed the body state');
            assert(!sprite.isAnimationPhysicsPartAttached(hand));assert(!sprite.isAnimationPhysicsPartAttached(membership.weight));
            fallStart=hand.physics.getState().y;next('detached');
        } else if(phase==='detached' && elapsed>1) {
            assert(hand.physics.getState().y>fallStart+20,'Detached limb did not fall');
            assert.strictEqual(hand.physics.getMode(),pdg.physicsBody_Dynamic);
            assert(membership.toggleArm());near(sprite.physics.getMass(),60);
            assert(sprite.isAnimationPhysicsPartAttached(hand));next('restored');
        } else if(phase==='restored' && elapsed>1.5) {
            rig.drop();next('loaded-ragdoll');
        } else if(phase==='loaded-ragdoll' && elapsed>1.5) {
            rig.recover();next('loaded-recovery');
        } else if(phase==='loaded-recovery' && rig.mode==='standing') {
            near(sprite.physics.getMass(),60);
            assert.strictEqual(sprite.getAnimationPhysicsMode('right_upper_arm',true),pdg.animationPhysics_Driven);
            assert(membership.toggleWeight());near(sprite.physics.getMass(),50);
            assert(!sprite.isAnimationPhysicsPartAttached(membership.weight));next('dropped');
        } else if(phase==='dropped' && elapsed>2) {
            assert(membership.contacts>0,'Dropped weight did not collide with floor');
            const frame=membership.weight.physics.getState();
            const visibleBottom=frame.y+scale*(12*Math.abs(Math.sin(frame.rotation))+5*Math.abs(Math.cos(frame.rotation)));
            assert(Math.abs(visibleBottom-origin.y)<1,'Dropped weight drawing did not settle on the visible floor: '+visibleBottom);
            assert(membership.toggleWeight());near(sprite.physics.getMass(),60);
            assert(membership.toggleWeight());near(sprite.physics.getMass(),50);
            assert(membership.toggleArm());near(sprite.physics.getMass(),50-limbMass);
            rig.drop();next('ragdoll');
        } else if(phase==='ragdoll' && elapsed>1.5) {
            rig.recover();next('recovering');
        } else if(phase==='recovering' && rig.mode==='standing') {
            near(sprite.physics.getMass(),50-limbMass);
            assert.strictEqual(hand.physics.getMode(),pdg.physicsBody_Dynamic,'Recovery reclaimed detached limb');
            assert(membership.toggleArm());near(sprite.physics.getMass(),50);stop();
        }
    } catch(error){stop(error);}
    return false;
});
layer.onPostAnimateLayer(()=> {
    if(finished)return false;
    try {
        if(membership.weight) {
            const frame=membership.weight.physics.getState(),bounds=membership.weight.collider.getBounds();
            const c=Math.abs(Math.cos(frame.rotation)),s=Math.abs(Math.sin(frame.rotation));
            // The accessory is an ordinary Part and inherits Sprite scale;
            // generated bone colliders instead use a rigid physical frame.
            assert(Math.abs(bounds.right-bounds.left-2*scale*(12*c+5*s))<.01,'Weight collision width differs from artwork');
            assert(Math.abs(bounds.bottom-bounds.top-2*scale*(12*s+5*c))<.01,'Weight collision height differs from artwork');
        }
        const bone=bones.find(b=>b.name==='right_hand'),p=sprite.getAnimationBoneTransform('right_forearm',pdg.animationSpace_World);
        const b=sprite.getAnimationBoneTransform('right_hand',pdg.animationSpace_World),c=Math.cos(p.rotation),s=Math.sin(p.rotation);
        const gap=Math.hypot(b.x-p.x-c*bone.local.x*p.scaleX+s*bone.local.y*p.scaleY,
            b.y-p.y-s*bone.local.x*p.scaleX-c*bone.local.y*p.scaleY);
        maxWristGap=Math.max(maxWristGap,gap);assert(gap<3,'Wrist tore in '+phase+': '+gap);
        if(membership.holdingWeight) {
            const h=hand.physics.getState(),w=membership.weight.physics.getState(),gripGap=Math.hypot(h.x-w.x,h.y-w.y);
            maxGripGap=Math.max(maxGripGap,gripGap);assert(gripGap<3,'Grip tore in '+phase+': '+gripGap);
        }
    } catch(error){stop(error);}
    return false;
});
pdg.run();
