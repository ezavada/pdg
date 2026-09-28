// Run from the repository root: ./test/rigs human/ragdoll
'use strict';
const assert=require('assert');
const path=require('path');
const pdg=require('pdg');
const {bones,pixelsPerCm:scale}=require('../../data/human-rig/human');
const {plantFeet}=require('../../data/human-rig/ground');
const {createArmBlocker}=require('../../data/human-rig/arm-blocker');
const {createRagdoll,platformHalfWidth}=require('../../data/human-rig/ragdoll');
const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
const origin=new pdg.Point(422,668),now=()=>pdg.tm.getMilliseconds()/1000;
sprite.setLocation(origin);sprite.setScale(scale,scale);sprite.enableAnimationPose('reference');sprite.pauseAnimation();
const ground=plantFeet(pdg,sprite),blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
const rig=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now);
assert.strictEqual(rig.joints.length,bones.length-1,'Every skeletal connection needs an angular limit');
assert(platformHalfWidth>170*scale,'Floor must catch a full-length sideways fall');
let trial=0,phase='settle',started=now(),finished=false,blendSeen=false,posingSeen=false,previousWeight=1;
let maxLimitExcursion=0;
const slopes=[0,10,-10],durations=[];
function stop(error) {
    if(finished)return;finished=true;
    if(error){console.error(error.stack);process.exitCode=1;}
    else console.log('PASS: torso lift, joint drives, fading physical pose, weight shift, tilted floors and interrupted recovery.\n'+JSON.stringify({recoveries:rig.completions,durations,maxLimitExcursionDegrees:maxLimitExcursion*180/Math.PI}));
    setTimeout(()=>{pdg.cleanupLayer(layer);pdg.quit();},0);
}
layer.onPreAnimateLayer(()=> {
    if(finished)return false;
    try {
        rig.updateGround();
        assert(Math.abs(sprite.physics.getMass()-50)<1e-8,'Control transition changed total mass');
        for(const {name,joint} of rig.joints) {
            const angle=joint.getBodyB().getState().rotation-joint.getBodyA().getState().rotation;
            const excess=Math.max(0,joint.getMinAngle()-angle,angle-joint.getMaxAngle());
            maxLimitExcursion=Math.max(maxLimitExcursion,excess);
            // Chipmunk corrects discrete impact overshoot over subsequent
            // steps. Reject escaped joints here; check the settled pose below.
            assert(excess<30*Math.PI/180,name+' escaped its angular limits on slope '+slopes[trial]+' in '+phase+': '+excess*180/Math.PI+' degrees');
        }
        const elapsed=now()-started;
        if(phase==='settle' && elapsed>.15) {
            rig.drop();phase='fall';started=now();
        } else if(phase==='fall' && elapsed>2) {
            assert(rig.contacts>0,'Ragdoll missed the physical floor');
            const before=bones.map(b=>sprite.findPart(b.name).physics.getState());
            rig.recover();
            assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Dynamic,'Lift must leave the limbs free');
            for(let i=0;i<bones.length;i++)assert.deepStrictEqual(sprite.findPart(bones[i].name).physics.getState(),before[i],'Starting a lift teleported a body');
            phase=trial===2?'interrupt':'recover';started=now();
        } else if(phase==='interrupt' && elapsed>.25) {
            rig.drop();
            assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Dynamic);
            assert.strictEqual(rig.completions,trial,'Interrupted lift completed');
            phase='fallAgain';started=now();
        } else if(phase==='fallAgain' && elapsed>1) {
            rig.recover();phase='recover';started=now();
        } else if(phase==='recover') {
            assert(elapsed<18,'Recovery stalled on slope '+slopes[trial]+': '+rig.phase+' '+JSON.stringify(rig.poseErrors));
            if(rig.phase==='lifting') {
                assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Dynamic);
                for(const b of bones)assert(!sprite.findPart(b.name).physics.isDriveEnabled(),'Drive activated before torso lift finished');
            }
            if(rig.phase==='posing')posingSeen=true;
            if(rig.phase==='blending') {
                blendSeen=true;
                assert(rig.physicsWeight<=previousWeight+1e-8,'Physical pose influence increased during handoff');
                previousWeight=rig.physicsWeight;
            }
            if(rig.mode==='standing') {
                assert(posingSeen && blendSeen,'Recovery skipped pose restoration or the blend');
                assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Kinematic);
                assert(sprite.isAnimationPlaying(),'Weight shift did not resume');
                assert.strictEqual(rig.recoveryEvents,trial+1,'Wrong number of recovery events');
                assert.strictEqual(rig.completions,trial+1);
                assert.strictEqual(rig.physicsWeight,0);
                for(const {joint} of rig.joints) {
                    const angle=joint.getBodyB().getState().rotation-joint.getBodyA().getState().rotation;
                    assert(angle>=joint.getMinAngle()-1e-3 && angle<=joint.getMaxAngle()+1e-3,'Recovered joint exceeded its limit');
                }
                for(const leg of ground.legs) {
                    const foot=sprite.getAnimationBoneTransform(leg.foot.name,pdg.animationSpace_Rig);
                    assert(Math.hypot(foot.x-leg.target.x,foot.y-leg.target.y)<.08,'Recovered foot missed its IK target');
                }
                durations.push(rig.lastRecoverySeconds);
                if(++trial===slopes.length){stop();return false;}
                ground.setAngle(slopes[trial]*Math.PI/180);
                sprite.seekAnimation('wave_hello',2.6);sprite.pauseAnimation();
                posingSeen=blendSeen=false;previousWeight=1;phase='settle';started=now();
            }
        }
    } catch(error){stop(error);}
    return false;
});
pdg.run();
