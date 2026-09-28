// Run from the repository root: ./test/rigs human/pushes
'use strict';
const assert=require('assert');
const path=require('path');
const pdg=require('pdg');
const {bones,pixelsPerCm:scale}=require('../../data/human-rig/human');
const {plantFeet}=require('../../data/human-rig/ground');
const {createArmBlocker}=require('../../data/human-rig/arm-blocker');
const {createRagdoll}=require('../../data/human-rig/ragdoll');
const {createPushes}=require('../../data/human-rig/pushes');
const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
const origin=new pdg.Point(422,668),now=()=>pdg.tm.getMilliseconds()/1000;
sprite.setLocation(origin);sprite.setScale(scale,scale);sprite.enableAnimationPose('reference');sprite.pauseAnimation();
const ground=plantFeet(pdg,sprite),blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
const rig=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now);
const pushes=createPushes(pdg,layer,sprite,ground,rig,origin,scale,now);
const trials=[{kind:'soft',slope:0},{kind:'hard',slope:0},{kind:'soft',slope:10},
    {kind:'hard',slope:10},{kind:'soft',slope:-10},{kind:'hard',slope:-10}];
let trial=0,phase='settle',started=now(),finished=false,blendSeen=false;
const results=[];
function stop(error) {
    if(finished)return;finished=true;
    if(error){console.error(error.stack);process.exitCode=1;}
    else console.log('PASS: soft/hard shoulder pushes, wall contacts, automatic recovery, foot IK on both slopes and cancellation.\n'+JSON.stringify(results));
    setTimeout(()=>{pdg.cleanupLayer(layer);pdg.quit();},0);
}
layer.onPreAnimateLayer(()=> {
    if(finished)return false;
    try {
        pushes.update();rig.updateGround();
        assert(Math.abs(sprite.physics.getMass()-50)<1e-8,'Push changed body mass');
        for(const bone of bones) {
            const s=sprite.findPart(bone.name).physics.getState();
            assert(Number.isFinite(s.x+s.y+s.rotation),'Nonfinite pushed body');
        }
        const elapsed=now()-started;
        if(phase==='settle' && elapsed>.2) {
            const shoulder=sprite.getAnimationBoneTransform('right_upper_arm',pdg.animationSpace_World);
            const before=bones.map(b=>sprite.findPart(b.name).physics.getState());
            assert(pushes.push(trials[trial].kind));
            assert.deepStrictEqual(pushes.point,{x:shoulder.x,y:shoulder.y},'Push must act at the non-waving shoulder');
            for(let i=0;i<bones.length;i++)assert.deepStrictEqual(sprite.findPart(bones[i].name).physics.getState(),before[i],'Starting a push teleported a body');
            assert(!pushes.push('hard'),'An active push should not queue another push');
            phase='push';started=now();
        } else if(phase==='push') {
            assert(elapsed<15,'Push stalled on '+JSON.stringify(trials[trial])+': '+rig.phase);
            if(rig.phase==='blending')blendSeen=true;
            if(pushes.phase)return false;
            const result=pushes.lastResult;
            assert(blendSeen,'Push skipped the blend back to animation');
            assert.strictEqual(pushes.completed,trial+1);
            assert.strictEqual(rig.recoveryEvents,trial+1,'Expected one recovery event per push');
            assert(result.shoulderTravelCm>1,'No visible shoulder deflection');
            assert(result.footTravelCm>1,'Feet did not move during recovery');
            assert(trials[trial].kind==='hard'?result.wallContacts>0:result.wallContacts===0,'Wrong wall response: '+JSON.stringify(result));
            assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Kinematic);
            assert(sprite.isAnimationPlaying(),'Weight shift did not resume');
            for(const leg of ground.legs) {
                const foot=sprite.getAnimationBoneTransform(leg.foot.name,pdg.animationSpace_Rig);
                assert(Math.hypot(foot.x-leg.target.x,foot.y-leg.target.y)<.08,'Foot missed its IK placement');
                const ik=sprite.getAnimationIKResult(leg.ik);assert(ik.reachable && !ik.stretched,'Recovery stretched a leg');
            }
            results.push({...trials[trial],...result});
            if(++trial===trials.length) {
                assert(pushes.push('hard'));pushes.cancel();rig.drop();
                phase='cancelled';started=now();return false;
            }
            ground.setAngle(trials[trial].slope*Math.PI/180);
            sprite.seekAnimation('wave_hello',2.6);sprite.pauseAnimation();
            phase='settle';started=now();blendSeen=false;
        } else if(phase==='cancelled' && elapsed>2) {
            assert.strictEqual(pushes.phase,null);assert.strictEqual(rig.mode,'ragdoll','Cancelled push recovered unexpectedly');
            assert.strictEqual(rig.completions,trials.length);stop();
        }
    } catch(error){stop(error);}
    return false;
});
pdg.run();
