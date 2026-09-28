// Single-bone release and explicit handoff between rig and manual hand drives.
'use strict';
function createHandControl(pdg,sprite,rig,blocker,scale) {
    const hand=sprite.findPart('left_hand').physics;
    const names=sprite.getAnimationBoneNames();
    const state={mode:'animation',target:null,limpCompletions:0,dragCompletions:0};
    let returnMode,pending=null,grabOffset,dragAngle;
    const point=()=>{const s=hand.getState();return {x:s.x,y:s.y};};
    state.getPoint=point;
    state.canStart=()=>rig.mode==='standing' && (state.mode==='animation' || state.mode==='limp');
    state.hitTest=p=>state.canStart() && Math.hypot(p.x-point().x,p.y-point().y)<=24;
    state.toggleLimp=()=> {
        if(!state.canStart())return false;
        if(state.mode==='limp') {
            pending={kind:'limp',bone:'left_hand',descendants:false,mode:returnMode};
            state.mode='recovering';
            sprite.setAnimationPhysicsMode(returnMode,'left_hand',false,.5,pdg.rotationDirection_Shortest);
        } else {
            returnMode=sprite.getAnimationPhysicsMode('left_hand');
            sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,'left_hand',false,0);
            state.mode='limp';
        }
        return true;
    };
    state.beginDrag=p=> {
        if(!state.canStart())return false;
        const before=hand.getState();
        // Explicitly release the whole arm's rig tracking before the manual
        // drive claims the hand. All pivots and angular limits remain active.
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,'left_upper_arm',true,0);
        pending=null;state.mode='dragging';
        grabOffset={x:before.x-p.x,y:before.y-p.y};dragAngle=before.rotation;
        state.moveDrag(p);return true;
    };
    state.moveDrag=p=> {
        if(state.mode!=='dragging')return false;
        state.target={x:p.x+grabOffset.x,y:p.y+grabOffset.y};
        rig.armTwist.setTarget('left',state.target);
        // A bounded pull of 60 N moves the hand's center. Leave wrist rotation
        // free, so the grab does not fight the arm's anatomical angle limits.
        hand.setDriveTarget(new pdg.Point(state.target.x,state.target.y),dragAngle,
            60*100*scale,0,3,2.5,pdg.rotationDirection_Shortest);
        return true;
    };
    state.endDrag=()=> {
        if(state.mode!=='dragging')return false;
        hand.clearDrive(); // Manual ownership must be released before rig control.
        rig.armTwist.setTarget('left',null);
        state.target=null;state.mode='recovering';
        pending={kind:'drag',bone:'left_upper_arm',descendants:true,mode:pdg.animationPhysics_Driven};
        // Restore ordinary bounded tracking. It pulls the existing physical
        // pose toward the animation without teleporting or forcing Kinematic.
        sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven,'left_upper_arm',true,0,pdg.rotationDirection_Shortest);
        blocker.driven=true;
        return true;
    };
    // Used before whole-rig pushes/recovery or a new blocker sequence. The
    // caller selects the next mode after this releases any current controller.
    state.release=()=> {
        rig.armTwist.setTarget('left',null);
        if(state.mode==='dragging')hand.clearDrive();
        if(pending)sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,pending.bone,pending.descendants,0);
        state.mode='animation';state.target=null;pending=null;
    };
    sprite.onAnimationPhysicsRecoveryComplete(event=> {
        if(!pending || event.wholeRig || event.disabled || event.bone!==names.indexOf(pending.bone)
            || event.includeDescendants!==pending.descendants || event.mode!==pending.mode)return false;
        state[pending.kind+'Completions']++;pending=null;state.mode='animation';
        return true;
    });
    return state;
}
module.exports={createHandControl};
