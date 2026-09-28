// Real-asset rig acceptance, shared by main.js and its finite playback check.
'use strict';
module.exports=function(pdg,aim,scale,options) {
    const sprite=aim.sprite,P=(x,y)=>new pdg.Point(x,y);
    sprite.setupPhysicsFromAnimationRig(options.mass,100*scale);
    sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0);
    sprite.getPartNames().forEach(name=> {
        const part=sprite.findPart(name),body=part.physics;
        if(body===pdg.PhysicsBody.NoPhysics)return;
        part.collider.setCollisionMask(0); // Keep the existing bouncing-ball scene independent.
        sprite.setAnimationPhysicsDriveSettings({maxForce:body.getMass()*20000,
            maxTorque:body.getMomentOfInertia()*1000,frequency:5,dampingRatio:2},name);
    });
    const hand=sprite.findPart(options.hand),limb=sprite.findPart(options.elbow);
    if(!hand || !limb)throw Error(options.label+': missing physical arm');
    const state={sprite,hand,limb,baseMass:options.mass,accessory:null,holding:false,
        phase:0,elapsed:0,running:false,completed:0,recoveries:0,reflections:0};
    let joint=null;
    sprite.onAnimationPhysicsRecoveryComplete(()=>{state.recoveries++;return true;});
    state.setBones=visible=>sprite.setAnimationDebugDraw(visible?pdg.animationDebug_Bones:pdg.animationDebug_None);
    state.flip=axis=> {
        const before=hand.physics.getState(),body=hand.physics;
        const origin=sprite.getLocation(),angle=sprite.getRotation(),c=Math.cos(angle),s=Math.sin(angle);
        let x=c*(before.x-origin.x)+s*(before.y-origin.y);
        let y=-s*(before.x-origin.x)+c*(before.y-origin.y);
        if(axis==='y')y=-y;else x=-x;
        if(axis==='y')sprite.setFlipY(!sprite.isFlippedY());else sprite.setFlipX(!sprite.isFlippedX());
        const after=hand.physics.getState();
        if(hand.physics!==body || !Number.isFinite(after.x+after.y))throw Error('Reflection lost body');
        if(Math.hypot(after.x-(origin.x+c*x-s*y),after.y-(origin.y+s*x+c*y))>.001)
            throw Error(options.label+': physical hand did not reflect with artwork');
        state.reflections++;
    };
    state.attach=()=> {
        if(state.holding)return;
        if(!state.accessory) {
            const weight=sprite.createPart('acceptance_weight'),art=pdg.createDrawing();
            art.addRect(new pdg.Rect(-6,-8,6,8),new pdg.Attributes().fillColor('gold').lineColor('black'));
            weight.setDrawing(art);weight.setupFrameCollider(pdg.frameCollider_Bounds).setCollisionMask(0);
            weight.setupPhysicsBody(1,100*scale*scale);state.accessory=weight;
        }
        const frame=hand.physics.getState();
        state.accessory.physics.teleport(P(frame.x,frame.y),frame.rotation).setVelocity(0,0).setAngularVelocity(0);
        sprite.attachAnimationPhysicsPart(state.accessory,hand);
        joint=hand.physics.createPivotJoint(state.accessory.physics);state.holding=true;
    };
    state.detach=()=> {
        if(!state.holding)return;
        sprite.detachAnimationPhysicsPart(state.accessory);
        if(joint.isActive())throw Error('Accessory boundary joint survived detach');
        joint=null;state.holding=false;
        state.accessory.physics.setVelocity(0,0).setAngularVelocity(0);
    };
    state.start=()=> {
        if(state.running)return;
        state.running=true;state.phase=0;state.elapsed=0;
        state.saved={paused:sprite.isAnimationPaused()};
        sprite.pauseAnimation();aim.physicsPaused=true;aim.aimWeight=0;
        state.attach();
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,options.elbow,true);
        limb.physics.applyAngularImpulse(limb.physics.getMomentOfInertia()*.5);
    };
    state.update=seconds=> {
        if(!state.running)return;
        state.elapsed+=seconds;
        sprite.getPartNames().forEach(name=> {
            const body=sprite.findPart(name).physics;if(body===pdg.PhysicsBody.NoPhysics)return;
            const s=body.getState();if(!Number.isFinite(s.x+s.y+s.rotation+s.velocityX+s.velocityY+s.angularVelocity))
                throw Error(options.label+': nonfinite body '+name);
        });
        const expected=state.baseMass+(state.holding?1:0);
        if(Math.abs(sprite.physics.getMass()-expected)>1e-6)throw Error(options.label+': membership mass mismatch');
        if(state.phase===0 && state.elapsed>.5) {state.flip('x');state.phase=1;state.elapsed=0;}
        else if(state.phase===1 && state.elapsed>.5) {
            const rest=state.accessory.physics.getState();state.detach();state.flip('y');
            const detached=state.accessory.physics.getState();
            if(Math.hypot(rest.x-detached.x,rest.y-detached.y)>.001)throw Error('Detached accessory reflected with rig');
            state.flip('y');state.flip('x');
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,options.elbow,true,.5);
            state.phase=2;state.elapsed=0;
        } else if(state.phase===2) {
            if(sprite.getAnimationPhysicsMode(options.elbow,true)===pdg.animationPhysics_Kinematic) {
                state.completed++;state.running=false;aim.physicsPaused=false;
                if(!state.saved.paused)sprite.resumeAnimation();
                console.log(options.label+' physics PASS: live reflection, accessory mass/detach and arm recovery');
            } else if(state.elapsed>8)throw Error(options.label+': arm recovery timed out');
        }
    };
    return state;
};
