// Whole-body release and physical recovery for the human demo.
'use strict';
const {bones,femaleRig}=require('./human');
const {totalMass,armNames}=require('./arm-blocker');
const {installJointLimits,limitPose}=require('./joint-limits');
const {createArmTwist}=require('./arm-twist');
// Extend past both sides of the viewport: a full-height sideways fall must
// still land on the platform, including at either end of its tilt sweep.
const platformHalfWidth=1200,platformDepth=10;
// Centimeters in the standing reference pose; anatomical left is viewer right.
// Width/height include the rounded ends. These offsets move colliders, not bones.
const capsuleTuning={
    head:{width:16,height:26,down:-1},
    neck:{width:5},
    torso:{radiusChange:-3},
    root:{down:5,left:2},
    left_hand:{lengthScale:.7},
    right_hand:{lengthScale:.7}
};

function createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,clock) {
    const state={mode:'standing',hasRecovered:false,completions:0,recoveryEvents:0,contacts:0,
        phase:null,recoveryTime:.5,recoveryStarted:0,lastRecoverySeconds:0,modifierIds:[],physicsWeight:0};
    const parts=bones.map(bone=> {
        const part=sprite.findPart(bone.name),body=part.physics;
        return {bone,part,body,linearDamping:body.getLinearDamping(),angularDamping:body.getAngularDamping()};
    });
    const gravity=980*scale;
    const localPoint=(body,x,y)=> {
        const frame=body.getState(),c=Math.cos(frame.rotation),s=Math.sin(frame.rotation);
        const dx=origin.x+x*scale-frame.x,dy=origin.y+y*scale-frame.y;
        return new pdg.Point(c*dx+s*dy,-s*dx+c*dy);
    };
    for(const {bone,part} of parts) {
        const body=part.physics;
        part.collider.setCollisionMask(part.collider.getCollisionMask()|8).setFriction(.7);
        if(bone.name.endsWith('_foot')) {
            // Put the physical sole on the same surface as the traced artwork.
            // The generated artwork-bounds capsule otherwise extends below it.
            const ref=bone.reference,c=Math.cos(ref.angle),s=Math.sin(ref.angle);
            const sole=bone.contours.flat().map(([x,y])=>({x:ref.x+c*x-s*y,y:ref.y+s*x+c*y}))
                .filter(p=>Math.abs(p.y)<1e-6);
            const left=Math.min(...sole.map(p=>p.x)),right=Math.max(...sole.map(p=>p.x));
            const radius=1;
            part.collider.setCapsule(localPoint(body,left+radius,-radius),
                localPoint(body,right-radius,-radius),radius*scale);
        } else if(['root','torso','head'].includes(bone.name)) {
            // Broad body pieces need more than the narrow default bone capsule
            // when they land sideways. Fit their reference artwork in body space.
            const ref=bone.reference,c=Math.cos(ref.angle),s=Math.sin(ref.angle);
            const points=bone.contours.flat().map(([x,y])=>localPoint(body,ref.x+c*x-s*y,ref.y+s*x+c*y));
            const left=Math.min(...points.map(p=>p.x)),right=Math.max(...points.map(p=>p.x));
            const top=Math.min(...points.map(p=>p.y)),bottom=Math.max(...points.map(p=>p.y));
            const radius=(bottom-top)/2,center=(left+right)/2,y=(top+bottom)/2;
            part.collider.setCapsule(new pdg.Point(Math.min(center,left+radius),y),
                new pdg.Point(Math.max(center,right-radius),y),radius);
        }
    }
    // The female demo profile changes only the torso/pelvis mass distribution.
    if(femaleRig) {
        const pelvis=parts.find(p=>p.bone.name==='root').body;
        const torso=parts.find(p=>p.bone.name==='torso').body;
        const pelvisMass=pelvis.getMass(),torsoMass=torso.getMass();
        pelvis.setMass(torsoMass);torso.setMass(pelvisMass);
    }
    for(const [name,tuning] of Object.entries(capsuleTuning)) {
        const {part,body}=parts.find(p=>p.bone.name===name),collider=part.collider,id=collider.getShapeId(0);
        const previousInertia=body.getMomentOfInertia();
        let a=collider.getCapsuleStart(id),b=collider.getCapsuleEnd(id);
        let radius=collider.getCapsuleRadius(id);
        const frame=body.getState(),c=Math.cos(frame.rotation),s=Math.sin(frame.rotation);
        const localVector=(x,y)=>({x:(c*x+s*y)*scale,y:(-s*x+c*y)*scale});
        if(tuning.width!==undefined)radius=tuning.width*scale/2;
        if(tuning.radiusChange!==undefined)radius+=tuning.radiusChange*scale;
        if(tuning.height!==undefined) {
            const center={x:(a.x+b.x)/2,y:(a.y+b.y)/2};
            const half=localVector(0,(tuning.height-tuning.width)/2);
            a={x:center.x-half.x,y:center.y-half.y};
            b={x:center.x+half.x,y:center.y+half.y};
        }
        if(tuning.lengthScale!==undefined) {
            // Scale the full end-to-end length, retaining width and center.
            const length=Math.hypot(b.x-a.x,b.y-a.y),center={x:(a.x+b.x)/2,y:(a.y+b.y)/2};
            const factor=length>0?Math.max(0,(length+2*radius)*tuning.lengthScale-2*radius)/length:0;
            const dx=(b.x-a.x)*factor/2,dy=(b.y-a.y)*factor/2;
            a={x:center.x-dx,y:center.y-dy};b={x:center.x+dx,y:center.y+dy};
        }
        const shift=localVector(tuning.left||0,tuning.down||0);
        a=new pdg.Point(a.x+shift.x,a.y+shift.y);
        b=new pdg.Point(b.x+shift.x,b.y+shift.y);
        collider.setCapsule(a,b,radius);
        // Match Chipmunk's rounded-segment inertia approximation, including
        // the capsule center's offset from the retained physical body origin.
        const length=Math.hypot(b.x-a.x,b.y-a.y)+2*radius,x=(a.x+b.x)/2,y=(a.y+b.y)/2;
        const inertia=body.getMass()*((length*length+4*radius*radius)/12+x*x+y*y);
        body.setMomentOfInertia(inertia);
        if(armNames.includes(name)) {
            // Preserve angular tracking stiffness (inertia * frequency squared)
            // after reshaping a driven arm segment, with the same torque budget.
            const settings=sprite.getAnimationPhysicsDriveSettings(name);
            settings.frequency*=Math.sqrt(previousInertia/inertia);
            sprite.setAnimationPhysicsDriveSettings(settings,name);
        }
    }
    // Size recovery drives after the mass/geometry edits so their budgets use
    // the final distribution and moments of inertia.
    for(const {bone,body} of parts)if(!armNames.includes(bone.name)) {
        const pivot=sprite.getAnimationBoneTransform(bone.name,pdg.animationSpace_World);
        let supportedMass=0,supportedMoment=0;
        for(const child of parts) {
            let ancestor=child.bone;
            while(ancestor && ancestor.name!==bone.name)ancestor=bones.find(b=>b.name===ancestor.parent);
            if(!ancestor)continue;
            const center=child.body.getState(),mass=child.body.getMass();
            supportedMass+=mass;
            supportedMoment+=mass*Math.hypot(center.x-pivot.x,center.y-pivot.y);
        }
        sprite.setAnimationPhysicsDriveSettings({
            maxForce:supportedMass*gravity*3,
            maxTorque:Math.max(supportedMoment*gravity*3,body.getMomentOfInertia()*2000,
                bone.name.endsWith('_foot')?totalMass*gravity*15*scale*2:
                bone.name.endsWith('_thigh')?totalMass*gravity*100*scale:0),
            frequency:8,dampingRatio:3.5},bone.name);
    }
    const platform=layer.createSprite();
    platform.setLocation(origin);
    const platformBody=platform.setupPhysicsBody();platformBody.setMode(pdg.physicsBody_Kinematic);
    platform.setupCollider().setBox(new pdg.Rect(-platformHalfWidth,0,platformHalfWidth,platformDepth))
        .setCategory(8).setCollisionMask(3).setFriction(.8).setRestitution(0)
        .setContactHandler(contact=>{if(contact.phase!==pdg.collision_End)state.contacts++;});
    const torso=sprite.findPart('torso').physics;
    const neck=bones.find(b=>b.name==='neck').reference;
    const liftPoint=localPoint(torso,neck.x,neck.y);
    const lift=layer.createSprite();
    const liftBody=lift.setupPhysicsBody();liftBody.setMode(pdg.physicsBody_Kinematic);
    let liftJoint=null,liftStart,liftDuration,targetPoint,poseSeconds,poseStarted,blendStarted,blendPose,lowerStarted;
    let clearance=0;
    const liftClearance=5; // cm: let dangling shoes unfold clear of the floor
    let referencePose=[];
    const worldLiftPoint=()=> {
        const t=torso.getState(),c=Math.cos(t.rotation),s=Math.sin(t.rotation);
        return {x:t.x+c*liftPoint.x-s*liftPoint.y,y:t.y+s*liftPoint.x+c*liftPoint.y};
    };
    const releaseLift=()=> {
        if(liftJoint)liftJoint.disconnect();
        liftJoint=null;liftBody.setVelocity(0,0);
    };
    const startPoseRecovery=()=> {
        state.phase='posing';poseStarted=clock();
        // The torso support supplies world-space lift and the pivots retain
        // bone lengths. Restore the pose with joint rotation, without a second
        // set of position servos compressing the legs against the platform.
        for(const p of parts)if(sprite.isAnimationPhysicsPartAttached(p.part)) {
            p.driveSettings=sprite.getAnimationPhysicsDriveSettings(p.bone.name);
            sprite.setAnimationPhysicsDriveSettings({...p.driveSettings,maxForce:0},p.bone.name);
        }
        sprite.getAnimationPose();
        sprite.setLocation(origin);
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,poseSeconds,pdg.rotationDirection_Shortest);
    };
    const restoreSettings=()=> {
        for(const p of parts)if(sprite.isAnimationPhysicsPartAttached(p.part)) {
            p.body.setLinearDamping(p.linearDamping).setAngularDamping(p.angularDamping);
            if(p.driveSettings){sprite.setAnimationPhysicsDriveSettings(p.driveSettings,p.bone.name);p.driveSettings=null;}
            if(p.bone.name.endsWith('_foot'))p.part.collider.setFriction(.7);
        }
    };
    const startLowering=()=> {state.phase='lowering';lowerStarted=clock();};
    const startBlend=()=> {
        if(state.phase==='blending')return;
        blendPose=bones.map(b=>sprite.getAnimationBoneTransform(b.name,pdg.animationSpace_Local));
        const root=sprite.getAnimationBoneTransform('root',pdg.animationSpace_World);
        blendPose[0].x=(root.x-origin.x)/scale;blendPose[0].y=(root.y-origin.y)/scale;
        blendStarted=clock();state.phase='blending';state.physicsWeight=1;
        sprite.setLocation(origin);
        sprite.transitionToAnimation('weight_shift',0,poseSeconds);sprite.resumeAnimation();
        sprite.getAnimationPose(); // Apply the captured physical pose at weight 1.
        sprite.setLocation(origin);
        if(sprite.getAnimationPhysicsMode()!==pdg.animationPhysics_Kinematic)
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0,pdg.rotationDirection_Shortest);
        releaseLift();restoreSettings();
    };
    const nearReference=()=> {
        if(referencePose.length!==bones.length)return false;
        state.poseErrors=bones.map((bone,i)=> {
            const actual=sprite.getAnimationBoneTransform(bone.name,pdg.animationSpace_World),target=referencePose[i];
            return {name:bone.name,cm:Math.hypot(actual.x-target.x,actual.y-target.y)/scale,
                degrees:Math.abs(Math.atan2(Math.sin(actual.rotation-target.rotation),Math.cos(actual.rotation-target.rotation)))*180/Math.PI};
        }).filter(e=>sprite.isAnimationPhysicsPartAttached(sprite.findPart(e.name)));
        return state.poseErrors.every(e=>e.cm<2 && e.degrees<5);
    };
    // Sweep kinematic supports within the actual physics step. A render/timer
    // delta can differ from the solver delta after a delayed browser frame.
    platform.addAnimationHelper(new pdg.IAnimationHelper(()=> {
        platform.setRotation(ground.angle);
        return true;
    }));
    lift.addAnimationHelper(new pdg.IAnimationHelper(()=> {
        if(state.mode==='recovering' && state.phase!=='blending') {
            const t=Math.min(1,(clock()-state.recoveryStarted)/liftDuration),blend=t*t*(3-2*t);
            const next=state.phase==='lifting'?{x:liftStart.x+(targetPoint.x-liftStart.x)*blend,
                y:liftStart.y+(targetPoint.y-liftStart.y)*blend}:targetPoint;
            lift.setLocation(new pdg.Point(next.x,next.y));
        }
        return true;
    }));
    state.updateGround=()=> {
        const time=clock();
        if(state.phase==='lowering') {
            const t=Math.min(1,(time-lowerStarted)/poseSeconds);
            clearance=liftClearance*(1-t*t*(3-2*t));
            ground.setAngle(ground.angle);sprite.getAnimationPose();
        }
        if(state.mode==='recovering' && state.phase!=='blending') {
            const t=Math.min(1,(time-state.recoveryStarted)/liftDuration);
            const actual=worldLiftPoint();
            if(state.phase==='lifting' && t===1 && Math.hypot(actual.x-targetPoint.x,actual.y-targetPoint.y)<scale && torso.getSpeed()<10*scale)
                startPoseRecovery();
            if(state.phase==='posing' && time-poseStarted>=poseSeconds && nearReference())startLowering();
            if(state.phase==='lowering' && clearance===0 && nearReference())startBlend();
        }
    };
    state.joints=installJointLimits(pdg,sprite,blocker.elbowLimits);
    state.armTwist=createArmTwist(pdg,sprite,state.joints);
    state.modifierIds.push(sprite.addAnimationModifier(view=> {
        state.armTwist.update(view,state.mode==='recovering');
    },pdg.animationStage_PostConstraint,0));
    state.modifierIds.push(sprite.addAnimationModifier(view=> {
        if(state.phase!=='blending')return;
        const t=Math.min(1,(clock()-blendStarted)/poseSeconds),blend=t*t*(3-2*t);
        state.physicsWeight=1-blend;
        for(const bone of bones) {
            const from=blendPose[bone.id],to=view.getLocalTransform(bone.name);
            for(const key of ['x','y','scaleX','scaleY','alpha'])to[key]=from[key]+(to[key]-from[key])*blend;
            to.rotation=from.rotation+Math.atan2(Math.sin(to.rotation-from.rotation),Math.cos(to.rotation-from.rotation))*blend;
            view.setLocalTransform(bone.name,to);
        }
    },pdg.animationStage_PreConstraint,-100));
    state.modifierIds.push(sprite.addAnimationModifier(view=> {
        if(state.mode==='standing' && !state.hasRecovered)return;
        // Recovery targets must lie inside the physical limits or completion
        // would be impossible, especially at the almost-straight bind elbows.
        limitPose(view,state.joints);
        if(clearance) {
            const root=view.getLocalTransform('root');root.y-=clearance;view.setLocalTransform('root',root);
        }
        const top=view.getTransform('neck',pdg.animationSpace_Rig);
        targetPoint={x:origin.x+top.x*scale,y:origin.y+top.y*scale};
        referencePose=bones.map(b=> {
            const t=view.getTransform(b.name,pdg.animationSpace_Rig);
            return {x:origin.x+t.x*scale,y:origin.y+t.y*scale,rotation:t.rotation};
        });
    },pdg.animationStage_PostConstraint,1));
    sprite.onAnimationPhysicsRecoveryComplete(event=> {
        if(state.mode!=='recovering' || !event.wholeRig || event.disabled || event.mode!==pdg.animationPhysics_Kinematic)return false;
        state.recoveryEvents++;
        if(state.phase==='posing')startLowering();
        return true;
    });
    sprite.onAnimationBlendComplete(()=> {
        if(state.phase!=='blending')return false;
        state.mode='standing';state.phase=null;state.hasRecovered=true;state.completions++;state.physicsWeight=0;
        state.lastRecoverySeconds=clock()-state.recoveryStarted;
        return true;
    });
    state.drop=()=> {
        releaseLift();
        restoreSettings();
        blocker.setEnabled(false);blocker.driven=false;
        sprite.pauseAnimation();
        state.mode='ragdoll';state.phase=null;state.physicsWeight=1;clearance=0;
        for(const p of parts)if(sprite.isAnimationPhysicsPartAttached(p.part))p.body.setLinearDamping(1).setAngularDamping(6);
        for(const p of parts)if(p.bone.name.endsWith('_foot'))p.part.collider.setFriction(.7);
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic);
    };
    state.recover=(seconds=state.recoveryTime)=> {
        releaseLift();
        restoreSettings();
        blocker.setEnabled(false);blocker.driven=false;
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic);
        state.mode='recovering';state.phase='lifting';state.physicsWeight=1;state.recoveryStarted=clock();poseSeconds=Math.max(.01,seconds);
        clearance=liftClearance;
        for(const p of parts)if(sprite.isAnimationPhysicsPartAttached(p.part))p.body.setLinearDamping(2).setAngularDamping(8);
        for(const p of parts)if(p.bone.name.endsWith('_foot'))p.part.collider.setFriction(.05);
        sprite.startAnimation('reference');sprite.pauseAnimation();
        sprite.getAnimationPose(); // Sample the limited reference and ground IK.
        liftStart=worldLiftPoint();
        liftDuration=Math.max(seconds,Math.hypot(targetPoint.x-liftStart.x,targetPoint.y-liftStart.y)/(60*scale));
        lift.setLocation(new pdg.Point(liftStart.x,liftStart.y));
        liftJoint=liftBody.createPivotJoint(torso,new pdg.Point(0,0),liftPoint).setMaxForce(totalMass*gravity*3);
    };
    state.getPlatform=()=>platform;
    state.getLiftPoint=worldLiftPoint;
    return state;
}
module.exports={createRagdoll,platformHalfWidth,platformDepth};
