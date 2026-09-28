// Run from the repository root: ./test/rigs human/blocker
'use strict';
const assert=require('assert');
const path=require('path');
const pdg=require('pdg');
const {pixelsPerCm:scale}=require('../../data/human-rig/human');
const {plantFeet}=require('../../data/human-rig/ground');
const {createArmBlocker}=require('../../data/human-rig/arm-blocker');
const {createRagdoll}=require('../../data/human-rig/ragdoll');
const layer=pdg.createSpriteLayer();layer.setUseChipmunkPhysics(true);
const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
const origin=new pdg.Point(422,668),now=()=>pdg.tm.getMilliseconds()/1000,degrees=Math.PI/180;
sprite.setLocation(origin);sprite.setScale(scale,scale);sprite.enableAnimationPose('reference');
const ground=plantFeet(pdg,sprite),blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
// Include the wrist limits used by the real demo, not only the elbow limits.
const rig=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now);
const hand=sprite.findPart('left_hand').physics,forearm=sprite.findPart('left_forearm').physics;
const joint=rig.joints.find(j=>j.name==='left_hand').joint;
const wristAngle=()=>hand.getState().rotation-forearm.getState().rotation;
let phase='kinematic',started=now(),finished=false,activations=0,positiveAngle=0;
let minWave=Infinity,maxWave=-Infinity,maxReleasedError=0;
sprite.startAnimation('wave_hello');
function stop(error) {
    if(finished)return;finished=true;
    if(error){console.error(error.stack);process.exitCode=1;}
    else console.log('PASS: mid-wave activation, wrist limits, repeated blocker release and resumed wrist motion.\n'+
        JSON.stringify({activations,wristSwingDegrees:(maxWave-minWave)/degrees,maxReleasedErrorDegrees:maxReleasedError/degrees}));
    setTimeout(()=>{pdg.cleanupLayer(layer);pdg.quit();},0);
}
function activate() {
    sprite.startAnimation('wave_hello');sprite.resumeAnimation();blocker.setEnabled(true);activations++;
    assert(sprite.getAnimationProgress()<1e-6,'Enabling the blocker must rewind an already-playing wave');
    assert(wristAngle()>=joint.getMinAngle() && wristAngle()<=joint.getMaxAngle(),'Handoff changed the wrist angular branch');
    phase='raising';started=now();
}
function hold(time,next) {
    sprite.seekAnimation('wave_hello',time);sprite.pauseAnimation();phase=next;started=now();
}
function checkSettled(tolerance=5) {
    const target=sprite.sampleAnimationPose('wave_hello',sprite.getAnimationProgress()*6).bones
        [sprite.getAnimationBoneNames().indexOf('left_hand')].rotation;
    const actual=sprite.getAnimationBoneTransform('left_hand',pdg.animationSpace_Local).rotation;
    const error=Math.abs(Math.atan2(Math.sin(actual-target),Math.cos(actual-target)));
    maxReleasedError=Math.max(maxReleasedError,error);
    assert(error<tolerance*degrees,'Released wrist did not return to its animation target in '+phase+': '+error/degrees+' degrees');
    assert(Math.abs(hand.getDriveState().rotationError)<tolerance*degrees,'Wrist drive is fighting a full-turn offset');
}
layer.onPreAnimateLayer(()=> {
    if(finished)return false;
    try {
        rig.updateGround();
        const elapsed=now()-started,angle=wristAngle();
        assert(Math.abs(sprite.physics.getMass()-50)<1e-8);
        if(phase==='kinematic') {
            assert(angle>=joint.getMinAngle() && angle<=joint.getMaxAngle(),'Kinematic wave wrapped the wrist outside its physical limits');
            if(elapsed>=1.9)activate(); // Negative wrist angle, authored near 360 degrees.
        } else {
            assert(Math.abs(hand.getDriveState().rotationError)<Math.PI,'Wrist drive acquired an extra full turn');
            if(phase==='raising' && elapsed>=2.6)hold(2.6,'blocked');
            else if(phase==='blocked' && elapsed>=1) {
                assert(blocker.isTouching(),'Arm missed the blocker');
                blocker.setEnabled(false);phase='released';started=now();
            } else if(phase==='released' && elapsed>=2) {
                checkSettled();
                if(activations===1)hold(2.816667,'positive');
                else {sprite.resumeAnimation();phase='loop';started=now();}
            } else if(phase==='positive' && elapsed>=1.5) {
                // Finite spring stiffness allows some gravity deflection;
                // both sides of the wave must still be reached after contact.
                checkSettled(10);assert(angle>0,'Wrist did not wave to the positive side');
                positiveAngle=angle;hold(2.483333,'negative');
            } else if(phase==='negative' && elapsed>=1.5) {
                checkSettled(10);assert(angle<0,'Wrist did not wave to the negative side');
                assert(positiveAngle-angle>10*degrees,'Wrist no longer waves to both sides');
                activate(); // Repeat from a negative wrist target while already Driven.
            } else if(phase==='loop') {
                assert(Math.abs(angle)<45*degrees,'Released wrist is stuck at its joint stop');
                minWave=Math.min(minWave,angle);maxWave=Math.max(maxWave,angle);
                if(elapsed>=6) {
                    assert(maxWave-minWave>10*degrees,'Wrist motion did not resume through a full wave');stop();
                }
            }
        }
    } catch(error){stop(error);}
    return false;
});
pdg.run();
