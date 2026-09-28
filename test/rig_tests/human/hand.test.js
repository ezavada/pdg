// Run from the repository root: ./test/rigs human/hand
'use strict';
const assert=require('assert'),path=require('path'),pdg=require('pdg');
const {bones,pixelsPerCm:scale}=require('../../data/human-rig/human');
const {plantFeet,GroundMotion,fastSweepSeconds}=require('../../data/human-rig/ground');
const {createArmBlocker}=require('../../data/human-rig/arm-blocker');
const {createRagdoll}=require('../../data/human-rig/ragdoll');
const {createHandControl}=require('../../data/human-rig/hand-control');
const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
const origin=new pdg.Point(422,668),now=()=>pdg.tm.getMilliseconds()/1000;
sprite.setLocation(origin);sprite.setScale(scale,scale);sprite.enableAnimationPose('reference');sprite.pauseAnimation();
const ground=plantFeet(pdg,sprite),blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
const rig=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now);
const control=createHandControl(pdg,sprite,rig,blocker,scale),motion=new GroundMotion();
const hand=sprite.findPart('left_hand').physics;
let phase='settle',started=now(),finished=false,angleBefore,dragStart,dragTarget,maxForce=0,maxGap=0;
sprite.seekAnimation('wave_hello',2.6);
function stop(error) {
    if(finished)return;finished=true;
    if(error){console.error(error.stack);process.exitCode=1;}
    else console.log('PASS: isolated limp hand, bounded manual drag, explicit release, rig handoff, interruption and fast floor IK.\n'+
        JSON.stringify({limpCompletions:control.limpCompletions,dragCompletions:control.dragCompletions,maxForce,maxJointGapPixels:maxGap}));
    setTimeout(()=>{pdg.cleanupLayer(layer);pdg.quit();},0);
}
const angle=()=>sprite.getAnimationBoneTransform('left_hand',pdg.animationSpace_Local).rotation;
layer.onPreAnimateLayer(()=> {
    if(finished)return false;
    try {
        ground.setAngle(motion.sample(now()));rig.updateGround();
        const elapsed=now()-started;
        assert(elapsed<8,'Hand control stalled in '+phase+': '+control.mode);
        assert(Math.abs(sprite.physics.getMass()-50)<1e-8);
        if(phase==='settle' && elapsed>.2) {
            angleBefore=angle();assert(control.toggleLimp());phase='limp';started=now();
        } else if(phase==='limp' && elapsed>.8) {
            assert.strictEqual(sprite.getAnimationPhysicsMode('left_hand'),pdg.animationPhysics_Dynamic);
            for(const name of ['left_upper_arm','left_forearm'])assert.strictEqual(sprite.getAnimationPhysicsMode(name),pdg.animationPhysics_Kinematic);
            assert(!hand.isDriveEnabled());assert(Math.abs(Math.atan2(Math.sin(angle()-angleBefore),Math.cos(angle()-angleBefore)))>.15);
            assert(control.toggleLimp());phase='restore';started=now();
        } else if(phase==='restore' && control.mode==='animation') {
            assert.strictEqual(control.limpCompletions,1);assert.strictEqual(sprite.getAnimationPhysicsMode('left_hand'),pdg.animationPhysics_Kinematic);
            const before=hand.getState();dragStart=control.getPoint();assert(control.hitTest(dragStart));
            assert(control.beginDrag(dragStart));assert.deepStrictEqual(hand.getState(),before,'Grabbing teleported the hand');
            assert.throws(()=>sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven,'left_upper_arm',true,0),'Manual drive ownership must be released');
            dragTarget={x:dragStart.x+90,y:dragStart.y+80};control.moveDrag(dragTarget);
            phase='drag';started=now();motion.setTilting(true,now(),0,fastSweepSeconds);
        } else if(phase==='drag') {
            const drive=hand.getDriveState();maxForce=Math.max(maxForce,Math.hypot(drive.forceX,drive.forceY));
            assert(Math.hypot(drive.forceX,drive.forceY)<=60*100*scale+1e-6);assert.strictEqual(drive.maxTorque,0);
            if(elapsed>2) {
                const p=control.getPoint();assert(p.x>dragStart.x+30 && p.y>dragStart.y+30,'Hand did not follow the drag');
                assert.strictEqual(sprite.getAnimationPhysicsMode('left_upper_arm',true),pdg.animationPhysics_Dynamic);
                control.endDrag();phase='return';started=now();
            }
        } else if(phase==='return' && elapsed>2) {
            assert.strictEqual(control.mode,'animation');assert.strictEqual(control.dragCompletions,1);
            assert.strictEqual(sprite.getAnimationPhysicsMode('left_upper_arm',true),pdg.animationPhysics_Driven);
            assert(Math.abs(hand.getDriveState().rotationError)<.15,'Released hand failed to follow the wrist animation');
            // A whole-rig action must release a current manual grab first.
            assert(control.beginDrag(control.getPoint()));control.release();rig.drop();
            assert.strictEqual(control.mode,'animation');assert(!hand.isDriveEnabled());
            assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Dynamic);stop();
        }
    } catch(error){stop(error);}
    return false;
});
layer.onPostAnimateLayer(()=> {
    if(finished)return false;
    try {
        for(const name of ['left_forearm','left_hand']) {
            const bone=bones.find(b=>b.name===name),p=sprite.getAnimationBoneTransform(bone.parent,pdg.animationSpace_World);
            const b=sprite.getAnimationBoneTransform(name,pdg.animationSpace_World),c=Math.cos(p.rotation),s=Math.sin(p.rotation);
            const gap=Math.hypot(b.x-p.x-c*bone.local.x*p.scaleX+s*bone.local.y*p.scaleY,
                b.y-p.y-s*bone.local.x*p.scaleX-c*bone.local.y*p.scaleY);
            maxGap=Math.max(maxGap,gap);assert(gap<2,'Arm joint gap at '+name+' in '+phase+' after '+(now()-started)+' s: '+gap+' px');
        }
        for(const leg of ground.legs) {
            const foot=sprite.getAnimationBoneTransform(leg.foot.name,pdg.animationSpace_Rig);
            assert(Math.hypot(foot.x-leg.target.x,foot.y-leg.target.y)<.08,'Fast floor tilt lost foot IK contact');
        }
    } catch(error){stop(error);}
    return false;
});
pdg.run();
