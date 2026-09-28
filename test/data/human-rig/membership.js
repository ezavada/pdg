// Explicit assembly membership, separate from physical joint connectivity.
'use strict';
const {bones}=require('./human');
const {handLoadKg}=require('./arm-blocker');
const dumbbellMass=10;
function createMembership(pdg,sprite,rig,scale) {
    const P=(x,y)=>new pdg.Point(x,y);
    const upper=sprite.findPart('right_upper_arm'),forearm=sprite.findPart('right_forearm'),hand=sprite.findPart('right_hand');
    const elbow=rig.joints.find(j=>j.name==='right_forearm');
    const state={armDetached:false,holdingWeight:false,weight:null,contacts:0};
    let grip=[];
    const local=(frame,point)=> {
        const c=Math.cos(frame.rotation),s=Math.sin(frame.rotation),x=point.x-frame.x,y=point.y-frame.y;
        return P(c*x+s*y,-s*x+c*y);
    };
    const world=(frame,point)=> {
        const c=Math.cos(frame.rotation),s=Math.sin(frame.rotation);
        return P(frame.x+c*point.x-s*point.y,frame.y+s*point.x+c*point.y);
    };
    const upperFrame=upper.physics.getState(),elbowPoint=sprite.getAnimationBoneTransform('right_forearm',pdg.animationSpace_World);
    const upperAnchor=local(upperFrame,elbowPoint),lowerAnchor=local(forearm.physics.getState(),elbowPoint);
    const rest=[forearm,hand].map(part=> {
        const frame=part.physics.getState();
        return {part,point:local(upperFrame,frame),angle:frame.rotation-upperFrame.rotation};
    });
    const rightNames=['right_upper_arm','right_forearm','right_hand'];
    const settings=rightNames.map(name=>sprite.getAnimationPhysicsDriveSettings(name));
    const gravity=980*scale;
    const loadSettings=rightNames.map((name,i)=> {
        let reach=0,moment=0;
        for(let j=i;j<rightNames.length;j++) {
            const bone=bones.find(b=>b.name===rightNames[j]),body=sprite.findPart(bone.name).physics;
            const pivot=sprite.getAnimationBoneTransform(bone.name,pdg.animationSpace_World),frame=body.getState();
            const lever=Math.hypot(frame.x-pivot.x,frame.y-pivot.y);
            moment+=body.getMass()*(reach+lever);
            reach+=j===rightNames.length-1?lever:bone.length*scale;
        }
        // A bounded angular drive supplies the lifting moment. The pivots
        // carry the linear load, avoiding competing position controllers.
        return {...settings[i],maxForce:0,maxTorque:gravity*(handLoadKg*reach+moment),frequency:8,dampingRatio:3.5};
    });
    const configureArm=loaded=> {
        rightNames.forEach((name,i)=> {
            if(sprite.isAnimationPhysicsPartAttached(sprite.findPart(name)))
                sprite.setAnimationPhysicsDriveSettings((loaded?loadSettings:settings)[i],name);
        });
        sprite.setAnimationPhysicsMode(loaded?pdg.animationPhysics_Driven:pdg.animationPhysics_Kinematic,
            'right_upper_arm',true,0,pdg.rotationDirection_Shortest);
    };
    const placeWeight=()=> {
        const frame=hand.physics.getState();
        state.weight.physics.teleport(P(frame.x,frame.y),frame.rotation-Math.PI/2).setVelocity(0,0).setAngularVelocity(0);
    };
    state.toggleArm=()=> {
        if(rig.mode!=='standing')return false;
        if(!state.armDetached) {
            sprite.detachAnimationPhysicsPart(forearm);
            state.armDetached=true;
            configureArm(false);
        } else {
            // A deliberate demo reset: membership itself never teleports or
            // manufactures constraints. Restore the limb, then rebuild elbow.
            const frame=upper.physics.getState();
            for(const entry of rest)entry.part.physics.teleport(world(frame,entry.point),frame.rotation+entry.angle)
                .setVelocity(0,0).setAngularVelocity(0);
            sprite.attachAnimationPhysicsPart(forearm).attachAnimationPhysicsPart(hand);
            upper.physics.createPivotJoint(forearm.physics,upperAnchor,lowerAnchor);
            elbow.joint=upper.physics.createRotaryLimit(forearm.physics,
                elbow.offset+elbow.min*Math.PI/180,elbow.offset+elbow.max*Math.PI/180);
            if(state.holdingWeight) {
                placeWeight();sprite.attachAnimationPhysicsPart(state.weight,hand);
            }
            state.armDetached=false;configureArm(state.holdingWeight);
        }
        return true;
    };
    state.toggleWeight=()=> {
        if(rig.mode!=='standing' || (state.armDetached && !state.holdingWeight))return false;
        if(state.holdingWeight) {
            sprite.detachAnimationPhysicsPart(state.weight);
            // The limb may already be detached, in which case the grip is
            // internal to that free piece and must be released explicitly.
            for(const joint of grip)if(joint.isActive())joint.disconnect();
            grip=[];state.holdingWeight=false;configureArm(false);
        } else {
            if(!state.weight) {
                const halfWidth=12*scale,halfHeight=5*scale;
                state.weight=sprite.createPart('dumbbell');
                state.weight.setupPhysicsBody(dumbbellMass,dumbbellMass*(halfWidth*halfWidth+halfHeight*halfHeight)/3)
                    .setLinearDamping(.3).setAngularDamping(3);
                // Ordinary Part geometry inherits the Sprite's scale. Keep
                // collider dimensions in centimeters; inertia above and the
                // direct body-space drawing below use layer pixels instead.
                state.weight.setupCollider().setBox(new pdg.Rect(-12,-5,12,5))
                    .setCategory(1).setCollisionMask(8|16).setFriction(.8).setRestitution(0)
                    .setContactHandler(contact=>{if(contact.phase!==pdg.collision_End)state.contacts++;});
            }
            placeWeight();
            sprite.attachAnimationPhysicsPart(state.weight,hand);
            grip=[hand.physics.createPivotJoint(state.weight.physics),hand.physics.createGear(state.weight.physics,1,-Math.PI/2)];
            state.holdingWeight=true;configureArm(true);
        }
        return true;
    };
    state.update=()=> {
        // Whole-body recovery ends Kinematic. Resume load-bearing arm drives.
        if(rig.mode==='standing' && state.holdingWeight && !state.armDetached &&
            sprite.getAnimationPhysicsMode('right_upper_arm')===pdg.animationPhysics_Kinematic)configureArm(true);
    };
    state.draw=port=> {
        if(!state.weight)return;
        const frame=state.weight.physics.getState(),ink=new pdg.Attributes().fillColor('#5a6570');
        const rect=(left,top,right,bottom)=>port.drawQuad(new pdg.Quad(
            world(frame,P(left*scale,top*scale)),world(frame,P(right*scale,top*scale)),
            world(frame,P(right*scale,bottom*scale)),world(frame,P(left*scale,bottom*scale))),ink);
        rect(-9,-1,9,1);rect(-12,-5,-6,5);rect(6,-5,12,5);
        const label=state.weight.physics.getMass().toFixed(0)+' kg',text=new pdg.Attributes().fillColor('#34414c').textSize(12);
        const width=port.getTextWidth(label,text.getTextSize(),text.getTextStyle());
        port.drawRect(new pdg.Rect(frame.x-width/2-4,frame.y+19,frame.x+width/2+4,frame.y+37),
            new pdg.Attributes().fillColor('#f2f8f8').roundedCorners(3));
        port.drawText(label,P(frame.x-width/2,frame.y+32),text);
    };
    state.getState=()=>({armDetached:state.armDetached,holdingWeight:state.holdingWeight,
        mass:sprite.physics.getMass(),weightAttached:!!state.weight && sprite.isAnimationPhysicsPartAttached(state.weight),contacts:state.contacts});
    return state;
}
module.exports={createMembership,dumbbellMass};
