// Held, kinematic posing through the public animation modifier and IK APIs.
'use strict';
const {bones}=require('./human');
const {limitPose}=require('./joint-limits');
const rad=Math.PI/180,wrap=a=>Math.atan2(Math.sin(a),Math.cos(a));
function createPoseControl(pdg,sprite,ground,rig,clock) {
    const state={mode:'off',selected:null,dragging:false,completions:0};
    let held=[],controllers=[],grab=null,blendStarted=0,blendFrom=[];
    const chains=['left','right'].flatMap(side=>[
        {name:side+'_hand',label:(side==='left'?'L':'R')+' hand',root:side+'_upper_arm',middle:side+'_forearm',side,arm:true},
        {name:side+'_foot',label:(side==='left'?'L':'R')+' foot',root:side+'_thigh',middle:side+'_shin',side,arm:false}
    ]);
    const handles=chains.concat([{name:'root',label:'Pelvis',move:true},
        {name:'torso',label:'Torso',rotate:true},{name:'head',label:'Head',rotate:true}]);
    const localSnapshot=()=>bones.map(b=>sprite.getAnimationBoneTransform(b.name,pdg.animationSpace_Local));
    const rigPoint=p=> {
        const origin=sprite.getLocation(),s=sprite.getScale(),a=sprite.getRotation();
        const dx=p.x-origin.x,dy=p.y-origin.y,c=Math.cos(a),n=Math.sin(a);
        return {x:(c*dx+n*dy)/s.x,y:(-n*dx+c*dy)/s.y};
    };
    const handlePoint=h=> {
        const t=sprite.getAnimationBoneTransform(h.name,pdg.animationSpace_World);
        const length=h.rotate?bones.find(b=>b.name===h.name).length*.6:0;
        return {x:t.x+Math.cos(t.rotation)*length*t.scaleX,y:t.y+Math.sin(t.rotation)*length*t.scaleX};
    };
    const refresh=()=> {
        for(const c of chains)if(c.ik)sprite.setAnimationIKTarget(c.ik,c.target.x,c.target.y,pdg.animationSpace_Rig);
    };
    const installIK=c=> {
        if(c.ik)sprite.removeAnimationModifier(c.ik);
        if(c.arm)rig.armTwist.setPoseReversed(c.side,c.reversed);
        // Root envelopes cross +/-pi in this frontal rig; the shared limitPose
        // pass clamps their continuous bind-pose branch after the IK solve.
        const positive=c.arm?(c.reversed?c.side==='left':c.side==='right'):c.side==='left';
        c.ik=sprite.addAnimationIK({root:c.root,middle:c.middle,tip:c.name,
            targetX:c.target.x,targetY:c.target.y,space:pdg.animationSpace_Rig,
            bendDirection:positive?-1:1,middleMin:(positive?(c.arm?2:0):-150)*rad,
            middleMax:(positive?150:(c.arm?-2:0))*rad,stretch:pdg.animationIK_NoStretch,
            matchOrientation:!c.arm,targetRotation:c.angle});
    };
    const removeControllers=()=> {
        for(const c of chains) {
            if(c.ik)sprite.removeAnimationModifier(c.ik);c.ik=0;
            if(c.arm)rig.armTwist.setPoseReversed(c.side,null);
        }
        controllers.forEach(id=>sprite.removeAnimationModifier(id));controllers=[];
    };
    const install=()=> {
        controllers.push(sprite.addAnimationModifier(view=> {
            bones.forEach(b=>view.setLocalTransform(b.name,held[b.id]));
        },pdg.animationStage_PreConstraint,-200));
        for(const c of chains)installIK(c);
        controllers.push(sprite.addAnimationModifier(view=>limitPose(view,rig.joints),pdg.animationStage_PostConstraint,2));
    };
    const captureTargets=(read=(name,space)=>sprite.getAnimationBoneTransform(name,space))=> {
        for(const c of chains) {
            const t=read(c.name,pdg.animationSpace_Rig);
            c.target={x:t.x,y:t.y};c.angle=t.rotation;
            const middle=held[bones.find(b=>b.name===c.middle).id];
            c.reversed=c.arm && (c.side==='left'?1:-1)*wrap(middle.rotation)>8*rad;
        }
    };
    state.enter=()=> {
        if(state.mode!=='off')return false;
        held=localSnapshot();captureTargets();sprite.pauseAnimation();ground.setEnabled(false);
        state.mode='posing';state.selected='left_hand';install();
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic,undefined,false,0,pdg.rotationDirection_Shortest);
        return true;
    };
    state.reset=()=> {
        if(state.mode!=='posing')return false;
        removeControllers();ground.setEnabled(true);
        sprite.seekAnimation('reference',0);sprite.pauseAnimation();
        // Read the new desired reference after ground IK. The published physical
        // pose still contains the previous edit until the next simulation tick.
        const capture=sprite.addAnimationModifier(view=> {
            held=bones.map(b=>view.getLocalTransform(b.name));
            captureTargets((name,space)=>view.getTransform(name,space));
        },pdg.animationStage_PostConstraint,50);
        sprite.getAnimationPose();sprite.removeAnimationModifier(capture);ground.setEnabled(false);
        state.dragging=false;grab=null;install();return true;
    };
    state.finish=()=> {
        if(state.mode!=='posing')return false;
        blendFrom=localSnapshot();removeControllers();state.dragging=false;grab=null;
        state.mode='returning';blendStarted=clock();ground.setEnabled(true);
        controllers.push(sprite.addAnimationModifier(view=> {
            const t=Math.min(1,Math.max(0,(clock()-blendStarted)/.5)),w=t*t*(3-2*t);
            bones.forEach(b=> {
                const from=blendFrom[b.id],to=view.getLocalTransform(b.name);
                for(const key of ['x','y','scaleX','scaleY','alpha'])to[key]=from[key]+(to[key]-from[key])*w;
                to.rotation=from.rotation+wrap(to.rotation-from.rotation)*w;
                view.setLocalTransform(b.name,to);
            });
        },pdg.animationStage_PostConstraint,100));
        sprite.transitionToAnimation('weight_shift',0,.5);sprite.resumeAnimation();return true;
    };
    state.update=()=> {
        if(state.mode==='returning' && clock()-blendStarted>=.5) {
            removeControllers();state.mode='off';state.selected=null;state.completions++;
        }
    };
    state.readHandles=()=>handles.map(h=>({...h,point:handlePoint(h)}));
    state.hitTest=p=> {
        if(state.mode!=='posing')return null;
        return state.readHandles().map(h=>({...h,d:Math.hypot(p.x-h.point.x,p.y-h.point.y)}))
            .filter(h=>h.d<=20).sort((a,b)=>a.d-b.d)[0]||null;
    };
    state.beginDrag=p=> {
        const h=state.hitTest(p);if(!h)return false;
        state.selected=h.name;state.dragging=true;
        const q=rigPoint(p),t=sprite.getAnimationBoneTransform(h.name,pdg.animationSpace_Rig);
        grab={handle:h,offset:{x:t.x-q.x,y:t.y-q.y},point:q,
            local:{...held[bones.find(b=>b.name===h.name).id]},angle:Math.atan2(q.y-t.y,q.x-t.x)};
        return true;
    };
    state.moveDrag=p=> {
        if(!state.dragging)return false;
        const q=rigPoint(p),h=grab.handle,b=bones.find(b=>b.name===h.name);
        if(h.move) {
            held[b.id].x=grab.local.x+q.x-grab.point.x;
            held[b.id].y=grab.local.y+q.y-grab.point.y;
        } else if(h.rotate) {
            const t=sprite.getAnimationBoneTransform(h.name,pdg.animationSpace_Rig);
            const limit=rig.joints.find(j=>j.name===h.name);
            held[b.id].rotation=Math.max(limit.min*rad,Math.min(limit.max*rad,
                wrap(grab.local.rotation)+wrap(Math.atan2(q.y-t.y,q.x-t.x)-grab.angle)));
        } else {
            const chain=chains.find(c=>c.name===h.name);
            chain.target={x:q.x+grab.offset.x,y:q.y+grab.offset.y};
        }
        refresh();return true;
    };
    state.endDrag=()=> {const was=state.dragging;state.dragging=false;grab=null;return was;};
    state.rotateSelected=degrees=> {
        if(state.mode!=='posing')return false;
        const c=chains.find(c=>c.name===state.selected);if(!c)return false;
        if(c.arm) {
            const t=held[bones.find(b=>b.name===c.name).id],limit=rig.joints.find(j=>j.name===c.name);
            t.rotation=Math.max(limit.min*rad,Math.min(limit.max*rad,wrap(t.rotation)+degrees*rad));
        } else {
            const middle=sprite.getAnimationBoneTransform(c.middle,pdg.animationSpace_Rig);
            const bone=bones.find(b=>b.name===c.name),limit=rig.joints.find(j=>j.name===c.name);
            const local=bone.local.angle+wrap(c.angle-middle.rotation-bone.local.angle);
            c.angle=middle.rotation+Math.max(limit.min*rad,Math.min(limit.max*rad,local+degrees*rad));
            installIK(c);
        }
        refresh();return true;
    };
    state.flipElbow=()=> {
        if(state.mode!=='posing')return false;
        const c=chains.find(c=>c.name===state.selected && c.arm);if(!c)return false;
        c.reversed=!c.reversed;installIK(c);refresh();return true;
    };
    state.getState=()=>({mode:state.mode,selected:state.selected,dragging:state.dragging,completions:state.completions,
        handles:state.readHandles().map(h=>({name:h.name,label:h.label,point:h.point})),
        targets:chains.map(c=> {
            const actual=sprite.getAnimationBoneTransform(c.name,pdg.animationSpace_Rig);
            return {name:c.name,target:c.target && {...c.target},reversed:c.reversed,
                error:c.target?Math.hypot(actual.x-c.target.x,actual.y-c.target.y):0,
                result:c.ik?sprite.getAnimationIKResult(c.ik):null};
        }),
        errors:controllers.concat(chains.map(c=>c.ik).filter(Boolean)).map(id=>sprite.getAnimationModifierError(id)).filter(Boolean)});
    return state;
}
module.exports={createPoseControl};
