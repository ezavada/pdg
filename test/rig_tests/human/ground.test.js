// Run from the repository root: ./test/rigs human/ground
'use strict';
const assert=require('assert');
const path=require('path');
const pdg=require('pdg');
const {bones,clips}=require('../../data/human-rig/human');
const {GroundMotion,plantFeet,limit,sweepSeconds,fastSweepSeconds}=require('../../data/human-rig/ground');
const close=(actual,expected,message,tolerance=1e-6)=>assert(Math.abs(actual-expected)<tolerance,message);
const motion=new GroundMotion();
motion.setTilting(true,100);
close(motion.sample(100),0,'Starting tilt jumped');
close(motion.sample(110),limit,'Initial tilt did not reach +10 degrees');
close(motion.sample(115),0,'Sweep midpoint is not level');
close(motion.sample(110+sweepSeconds),-limit,'First sweep did not take ten seconds');
close(motion.sample(120+sweepSeconds),limit,'Return sweep did not take ten seconds');
motion.setTilting(false,120);
close(motion.sample(120),-limit,'Stopping tilt jumped');
close(motion.sample(125),0,'Ground did not return to level');
motion.setTilting(true,122);
close(motion.sample(122),-limit*(1-(1-Math.cos(Math.PI*2/5))/2),'Restarting during return jumped');
const beforeFast=motion.sample(123);
motion.setTilting(true,123,beforeFast,fastSweepSeconds);
close(motion.sample(123),beforeFast,'Switching to fast tilt jumped');
close(motion.sample(124),limit,'Fast initial tilt did not take one second');
close(motion.sample(124.5),0,'Fast sweep midpoint was not level');
close(motion.sample(125),-limit,'Fast sweep did not take one second');
close(motion.sample(126),limit,'Fast return sweep did not take one second');
motion.setTilting(false,126);
close(motion.sample(126),limit,'Stopping fast tilt jumped');
close(motion.sample(126.5),0,'Fast tilt did not return to level');
motion.setTilting(true,127,0,fastSweepSeconds);
const beforeSlow=motion.sample(128.25);
motion.setTilting(true,128.25,beforeSlow,sweepSeconds);
close(motion.sample(128.25),beforeSlow,'Switching back to slow tilt jumped');
close(motion.sample(138.25),limit,'Slow duration was not restored');

const layer=pdg.createSpriteLayer();
try {
    const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
    assert(sprite.enableAnimationPose('reference'));
    sprite.setLocation(new pdg.Point(422,668)); sprite.setScale(3,3);
    sprite.pauseAnimation();
    const reference=bones.map(b=>sprite.getAnimationBoneTransform(b.name,pdg.animationSpace_Rig));
    const ground=plantFeet(pdg,sprite);
    let count=0,maxContactError=0;
    for(const clip of clips)for(let time=0;time<clip.seconds;time+=.25) {
        sprite.seekAnimation(clip.name,time);
        for(const degrees of [-10,-5,0,5,10]) {
            // Updating the targets must also reevaluate a paused/unchanged clip.
            const angle=degrees*Math.PI/180,c=Math.cos(angle),s=Math.sin(angle);
            ground.setAngle(angle);
            for(const leg of ground.legs) {
                const foot=sprite.getAnimationBoneTransform(leg.foot.name,pdg.animationSpace_Rig);
                const ik=sprite.getAnimationIKResult(leg.ik);
                assert(ik.reachable && !ik.stretched && !ik.limited,'Leg failed to reach the ground');
                // Check actual shoe-sole artwork points, not just IK targets.
                const ref=leg.foot.reference,rc=Math.cos(ref.angle),rs=Math.sin(ref.angle);
                for(const [x,y] of leg.foot.contours.flat()) {
                    const px=ref.x+rc*x-rs*y,py=ref.y+rs*x+rc*y;
                    if(Math.abs(py)>1e-6)continue;
                    const actualX=foot.x+Math.cos(foot.rotation)*x-Math.sin(foot.rotation)*y;
                    const actualY=foot.y+Math.sin(foot.rotation)*x+Math.cos(foot.rotation)*y;
                    const error=Math.hypot(actualX-(c*px-s*py),actualY-(s*px+c*py));
                    maxContactError=Math.max(maxContactError,error);
                    assert(error<1e-6,'Shoe contact slipped or rotated away from the ground');
                }
                for(const name of [leg.shin.name,leg.foot.name]) {
                    const t=sprite.getAnimationBoneTransform(name,pdg.animationSpace_Local);
                    const b=bones.find(b=>b.name===name);
                    close(Math.hypot(t.x,t.y),Math.hypot(b.local.x,b.local.y),'Leg segment changed length');
                }
            }
            for(const id of ground.modifierIds)assert.strictEqual(sprite.getAnimationModifierError(id),'');
            count++;
        }
    }
    // Level ground must restore the reference pose, without accumulated edits.
    // Allow one micrometer for SCML rounding near the almost-straight knees.
    ground.setAngle(0); sprite.seekAnimation('reference',0);
    for(const bone of bones) {
        const t=sprite.getAnimationBoneTransform(bone.name,pdg.animationSpace_Rig);
        close(t.x,reference[bone.id].x,bone.name+' reference x changed',1e-4);
        close(t.y,reference[bone.id].y,bone.name+' reference y changed',1e-4);
    }
    ground.remove();
    console.log('PASS: ten/one-second sweeps, continuous speed switches, paused IK, all clips, sole contact and unchanged leg lengths.');
    console.log(JSON.stringify({poses:count,maxContactErrorCm:maxContactError}));
} finally { pdg.cleanupLayer(layer); }
