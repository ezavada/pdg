// A physical obstruction for the waving arm; the rest of the rig follows IK.
'use strict';
const {bones}=require('./human');
const totalMass=50, handLoadKg=16;
const armNames=['left_upper_arm','left_forearm','left_hand'];

function createArmBlocker(pdg,layer,sprite,origin,scale,clock) {
    const bounds=new pdg.Rect(origin.x+50,origin.y-463,origin.x+230,origin.y-445);
    const state={enabled:false,driven:false,bounds,contacts:0,lastContact:-Infinity,point:null};
    const gravity=980*scale, unitsPerMeter=100*scale;
    layer.enableCollisions(); layer.setGravity(gravity); layer.setDamping(1);
    // Rig geometry is in centimeters and the owning layer is in pixels.
    sprite.setupPhysicsFromAnimationRig(totalMass,unitsPerMeter);
    // Spriter angles wrap across full turns during the wrist wave. Keep the
    // physical angles continuous, including while the arm is still kinematic,
    // so a later control handoff stays on the joint limits' angular branch.
    sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0,pdg.rotationDirection_Shortest);
    const parts=new Map();
    for(const bone of bones) {
        const part=sprite.findPart(bone.name);
        if(!part || !part.physics.isPresent())continue;
        parts.set(bone.name,part);
        const arm=armNames.includes(bone.name);
        part.collider.setCategory(arm?2:1).setCollisionMask(arm?4:0)
            .setFriction(.4).setRestitution(0);
    }
    const arm=armNames.map(name=> {
        const body=parts.get(name).physics, center=body.getState();
        const pivot=sprite.getAnimationBoneTransform(name,pdg.animationSpace_World);
        return {name,body,length:bones.find(b=>b.name===name).length*scale,
            lever:Math.hypot(center.x-pivot.x,center.y-pivot.y)};
    });
    state.torqueLimitsNm=[];
    arm.forEach((segment,i)=> {
        // Worst-case horizontal reach, with a load at the middle of the hand.
        // Add the moment needed to support the downstream rig bodies themselves.
        let reach=0,ownMoment=0;
        for(let j=i;j<arm.length;j++) {
            ownMoment+=arm[j].body.getMass()*(reach+arm[j].lever);
            reach+=arm[j].length*(j===arm.length-1?.5:1);
        }
        const torque=gravity*(handLoadKg*reach+ownMoment);
        state.torqueLimitsNm.push(torque/(unitsPerMeter*unitsPerMeter));
        // Share one torque budget between the center-position servo and the
        // angular servo. Their combined moment about the joint cannot exceed it.
        // A damping ratio of 3.5 settles contact/release without a springy bounce.
        sprite.setAnimationPhysicsDriveSettings({maxForce:torque*.5/segment.lever,
            maxTorque:torque*.5,frequency:[12,9,6][i],dampingRatio:3.5},segment.name);
    });
    // Bone angles can include full turns; align each limit with the physical
    // bodies' current angular branch. The two elbows bend in opposite directions.
    state.elbowLimits=['left','right'].map(side=> {
        const upper=parts.get(side+'_upper_arm').physics, forearm=parts.get(side+'_forearm').physics;
        const a=sprite.getAnimationBoneTransform(side+'_upper_arm',pdg.animationSpace_World);
        const b=sprite.getAnimationBoneTransform(side+'_forearm',pdg.animationSpace_World);
        const bend=Math.atan2(Math.sin(b.rotation-a.rotation),Math.cos(b.rotation-a.rotation));
        const straight=forearm.getState().rotation-upper.getState().rotation-bend;
        const margin=2*Math.PI/180;
        return upper.createRotaryLimit(forearm,
            straight+(side==='left'?-Math.PI:margin),
            straight+(side==='left'?-margin:Math.PI));
    });
    const obstacle=layer.createSprite();
    obstacle.setupPhysicsBody().setMode(pdg.physicsBody_Static);
    obstacle.setupCollider().setBox(bounds).setCategory(4).setCollisionMask(2)
        .setFriction(.4).setRestitution(0).setEnabled(false).setContactHandler(contact=> {
            if(contact.phase===pdg.collision_End)return;
            state.contacts++; state.lastContact=clock();
            state.point={x:contact.point.x,y:contact.point.y};
        });
    state.setEnabled=enabled=> {
        if(enabled) {
            // Explicitly rewind even if this clip is already playing; starting
            // the same Spriter clip again does not reset its playback time.
            // Lower the arm before enabling the bar, preserving angular turns.
            sprite.seekAnimation('wave_hello',0);
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,'left_upper_arm',true,0,pdg.rotationDirection_Shortest);
            for(const segment of arm)segment.body.setVelocity(0,0).setAngularVelocity(0);
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven,'left_upper_arm',true,0);
            state.driven=true;
        }
        obstacle.collider.setEnabled(enabled);
        state.enabled=enabled;
        state.lastContact=-Infinity; state.point=null;
    };
    state.isTouching=()=>state.enabled && clock()-state.lastContact<.12;
    return state;
}
module.exports={createArmBlocker,totalMass,handLoadKg,armNames};
