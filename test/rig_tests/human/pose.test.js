// Run from the repository root: ./test/rigs human/pose
'use strict';
const assert=require('assert'),path=require('path'),pdg=require('pdg');
const {bones,pixelsPerCm:scale}=require('../../data/human-rig/human');
const {plantFeet}=require('../../data/human-rig/ground');
const {createArmBlocker}=require('../../data/human-rig/arm-blocker');
const {createRagdoll}=require('../../data/human-rig/ragdoll');
const {createPoseControl}=require('../../data/human-rig/pose-control');
const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
const origin=new pdg.Point(422,668),now=()=>pdg.tm.getMilliseconds()/1000;
sprite.setLocation(origin);sprite.setScale(scale,scale);sprite.enableAnimationPose('reference');sprite.pauseAnimation();
const ground=plantFeet(pdg,sprite),blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
const rig=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now);
const pose=createPoseControl(pdg,sprite,ground,rig,now),wait=ms=>new Promise(resolve=>setTimeout(resolve,ms));
const point=name=>pose.readHandles().find(h=>h.name===name).point;
const distance=(a,b)=>Math.hypot(a.x-b.x,a.y-b.y);
const locals=()=>bones.map(b=>sprite.getAnimationBoneTransform(b.name,pdg.animationSpace_Local));
function verify() {
    const state=pose.getState();assert.deepStrictEqual(state.errors,[]);
    assert.strictEqual(sprite.physics.getMass(),50);
    assert.strictEqual(sprite.getAnimationPhysicsMode(),pdg.animationPhysics_Kinematic);
    for(const c of state.targets)if(c.result)assert.strictEqual(c.result.stretched,false);
    for(const bone of bones) {
        const t=sprite.getAnimationBoneTransform(bone.name,pdg.animationSpace_Local);
        assert(Number.isFinite(t.x+t.y+t.rotation));
        if(bone.parent)assert(Math.abs(Math.hypot(t.x,t.y)-Math.hypot(bone.local.x,bone.local.y))<1e-5,
            'Posing changed bone length: '+bone.name);
        const limit=rig.joints.find(j=>j.name===bone.name);
        if(limit && pose.mode==='posing') {
            const a=bone.local.angle+Math.atan2(Math.sin(t.rotation-bone.local.angle),Math.cos(t.rotation-bone.local.angle));
            assert(a>=limit.min*Math.PI/180-1e-5 && a<=limit.max*Math.PI/180+1e-5,'Pose exceeds limit: '+bone.name);
        }
    }
}
async function drag(name,dx,dy) {
    const start=point(name);assert(pose.beginDrag(start));
    assert.strictEqual(pose.selected,name);pose.moveDrag({x:start.x+dx,y:start.y+dy});pose.endDrag();
    await wait(80);verify();return distance(start,point(name));
}
async function run() {
    await wait(100);assert(pose.enter());assert(!pose.enter());assert(!ground.enabled);assert(!sprite.isAnimationPlaying());
    await wait(80);verify();
    const reference=pose.readHandles();
    assert(await drag('left_hand',60,-80)>25,'Left hand did not follow IK');
    assert(await drag('right_hand',-60,-80)>25,'Right hand did not follow IK');
    const held=locals();await wait(160);
    locals().forEach((t,i)=>assert(distance(t,held[i])<1e-5 && Math.abs(t.rotation-held[i].rotation)<1e-5,'Released pose drifted'));
    assert(await drag('left_foot',20,-50)>20,'Foot could not be lifted');
    const ankleBefore=sprite.getAnimationBoneTransform('left_foot',pdg.animationSpace_Rig).rotation;
    assert(pose.rotateSelected(5));await wait(80);verify();
    assert(Math.abs(sprite.getAnimationBoneTransform('left_foot',pdg.animationSpace_Rig).rotation-ankleBefore)>.05,'Foot rotation did not change');
    const foot=point('left_foot');await drag('root',5,15);
    assert(distance(foot,point('left_foot'))<1,'Moving pelvis lost a reachable foot target');
    const headBefore=sprite.getAnimationBoneTransform('head',pdg.animationSpace_Local).rotation;
    await drag('head',25,0);
    assert(Math.abs(sprite.getAnimationBoneTransform('head',pdg.animationSpace_Local).rotation-headBefore)>.1,'Head did not tilt');
    await drag('torso',-15,0);
    // Extreme target stays finite, marks a limit, and never stretches a bone.
    await drag('right_hand',-2000,-2000);
    assert(pose.getState().targets.find(c=>c.name==='right_hand').error>100);
    assert(pose.flipElbow());await wait(80);verify();
    assert(rig.armTwist.getState().find(a=>a.side==='right').reversed,'Elbow reversal did not change implied twist');
    assert.strictEqual(rig.armTwist.artwork('right','right_hand'),'right_hand_twisted');
    for(let i=0;i<30;i++)pose.rotateSelected(5);
    await wait(80);verify();
    assert(pose.reset());await wait(80);verify();
    for(const h of reference)assert(distance(point(h.name),h.point)<2,'Reset did not restore '+h.name);
    assert.strictEqual(pose.mode,'posing');
    // Blend begins at the edited pose, with no first-frame reset to the clip.
    await drag('left_hand',70,-95);const before=point('left_hand');
    assert(pose.finish());assert(!pose.beginDrag(before));
    assert(distance(before,point('left_hand'))<2,'Return snapped to animation');
    await wait(650);pose.update();verify();
    assert.strictEqual(pose.mode,'off');assert.strictEqual(pose.completions,1);
    assert(ground.enabled && sprite.isAnimationPlaying());
    assert(rig.armTwist.getState().every(a=>!a.reversed),'Posing retained an elbow override after return');
    for(const leg of ground.legs) {
        const t=sprite.getAnimationBoneTransform(leg.foot.name,pdg.animationSpace_Rig);
        assert(distance(t,leg.target)<.08,'Return did not replant foot');
    }
    // Re-enter on a slope and repeat, to catch stale modifiers or IK handles.
    ground.setAngle(10*Math.PI/180);await wait(80);assert(pose.enter());await wait(80);verify();
    assert(await drag('left_hand',40,-50)>10);
    pose.reset();await wait(80);verify();pose.finish();await wait(650);pose.update();verify();
    assert.strictEqual(pose.completions,2);
    console.log('PASS: held poses, both-arm and foot IK, pelvis/head/torso edits, joint limits, unreachable targets, reset, smooth return and repeated entry on a slope.');
}
run().catch(error=>{console.error(error.stack);process.exitCode=1;}).finally(()=>{pdg.cleanupLayer(layer);pdg.quit();});
pdg.run();
