// Run from the repository root: ./test/rigs human/twist
'use strict';
const assert=require('assert'),path=require('path'),pdg=require('pdg');
const {bones,pixelsPerCm:scale}=require('../../data/human-rig/human');
const {plantFeet}=require('../../data/human-rig/ground');
const {createArmBlocker}=require('../../data/human-rig/arm-blocker');
const {createRagdoll}=require('../../data/human-rig/ragdoll');
const now=()=>pdg.tm.getMilliseconds()/1000,rad=Math.PI/180;
const cases=['left','right'].map(side=> {
    const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
    const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
    const origin=new pdg.Point(422,668);sprite.setLocation(origin);sprite.setScale(scale,scale);
    sprite.enableAnimationPose('reference');sprite.pauseAnimation();
    const ground=plantFeet(pdg,sprite),blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
    const rig=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now);
    return {side,layer,sprite,rig,hand:sprite.findPart(side+'_hand').physics,phase:'settle',started:now(),
        maxGap:0,peakBend:0,bridgeSeen:false,twistedSeen:false};
});
let finished=false;
function finish(error) {
    if(finished)return;finished=true;
    if(error){console.error(error.stack);process.exitCode=1;}
    else console.log('PASS: mirrored inward elbow bends, matching hand art, bounded transition, explicit release and whole-body recovery.\n'+
        JSON.stringify(cases.map(({side,maxGap,peakBend})=>({side,maxGap,peakBend}))));
    setTimeout(()=>{cases.forEach(c=>pdg.cleanupLayer(c.layer));pdg.quit();},0);
}
for(const c of cases)c.layer.onPreAnimateLayer(()=> {
    if(finished || c.phase==='done')return false;
    try {
        const {side,sprite,rig,hand}=c,sign=side==='left'?1:-1;
        rig.updateGround();const elapsed=now()-c.started;
        const twist=rig.armTwist.getState().find(a=>a.side===side);
        assert(elapsed<16,'Twist stalled in '+c.phase+' on '+side);
        if(c.phase==='settle' && elapsed>.2) {
            const before=hand.getState();
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,side+'_upper_arm',true,0);
            const target={x:422-sign*37,y:310};rig.armTwist.setTarget(side,target);
            hand.setDriveTarget(new pdg.Point(target.x,target.y),before.rotation,60*100*scale,0,3,2.5,pdg.rotationDirection_Shortest);
            assert.deepStrictEqual(hand.getState(),before,'Twist request teleported a body');
            c.phase='drag';c.started=now();
        } else if(c.phase==='drag') {
            const t=sprite.getAnimationBoneTransform(side+'_forearm',pdg.animationSpace_Local);
            const bend=sign*Math.atan2(Math.sin(t.rotation),Math.cos(t.rotation))/rad;
            c.peakBend=Math.max(c.peakBend,bend);c.bridgeSeen ||= twist.transitioning;c.twistedSeen ||= twist.visible;
            if(elapsed>2.5) {
                assert(twist.reversed && !twist.transitioning && bend>65 && bend<150,'Elbow did not fold across the body');
                assert(c.bridgeSeen && c.twistedSeen,'Missing twist transition');
                assert.strictEqual(rig.armTwist.artwork(side,side+'_hand'),side+'_hand_twisted');
                hand.clearDrive();rig.armTwist.setTarget(side,null);
                sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven,side+'_upper_arm',true,0,pdg.rotationDirection_Shortest);
                c.phase='release';c.started=now();
            }
        } else if(c.phase==='release' && elapsed>2) {
            assert(!twist.reversed && !twist.visible && !twist.transitioning,'Normal elbow branch was not restored');
            assert.strictEqual(rig.armTwist.artwork(side,side+'_hand'),side+'_hand');
            // Interrupt another inward grab with a ragdoll and recover it.
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,side+'_upper_arm',true,0);
            const target={x:422-sign*37,y:310};rig.armTwist.setTarget(side,target);
            hand.setDriveTarget(new pdg.Point(target.x,target.y),hand.getState().rotation,60*100*scale,0,3,2.5);
            c.phase='again';c.started=now();
        } else if(c.phase==='again' && elapsed>2) {
            assert(twist.reversed,'Second grab did not twist');
            hand.clearDrive();rig.armTwist.setTarget(side,null);rig.drop();
            c.phase='fall';c.started=now();
        } else if(c.phase==='fall' && elapsed>1) {
            rig.recover();c.phase='recover';c.started=now();
        } else if(c.phase==='recover' && rig.mode==='standing') {
            assert(!twist.reversed && !twist.visible,'Recovery kept the reversed hand');
            assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Kinematic);
            c.phase='done';if(cases.every(c=>c.phase==='done'))finish();
        }
    } catch(error){finish(error);}return false;
});
for(const c of cases)c.layer.onPostAnimateLayer(()=> {
    if(finished || !['drag','release','again'].includes(c.phase))return false;
    try {
        for(const name of [c.side+'_forearm',c.side+'_hand']) {
            const bone=bones.find(b=>b.name===name),p=c.sprite.getAnimationBoneTransform(bone.parent,pdg.animationSpace_World);
            const b=c.sprite.getAnimationBoneTransform(name,pdg.animationSpace_World),co=Math.cos(p.rotation),s=Math.sin(p.rotation);
            const gap=Math.hypot(b.x-p.x-co*bone.local.x*p.scaleX+s*bone.local.y*p.scaleY,
                b.y-p.y-s*bone.local.x*p.scaleX-co*bone.local.y*p.scaleY);
            c.maxGap=Math.max(c.maxGap,gap);assert(gap<2,'Twisting separated '+name+': '+gap+' px');
        }
    } catch(error){finish(error);}return false;
});
pdg.run();
