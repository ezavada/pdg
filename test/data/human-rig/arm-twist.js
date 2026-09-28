// A 2D pose convention: reverse projected elbow bending with a matching hand
// silhouette. This does not introduce a third rotational axis into the solver.
'use strict';
const rad=Math.PI/180;
function createArmTwist(pdg,sprite,joints) {
    const arms=['left','right'].map(side=> {
        const upper=sprite.findPart(side+'_upper_arm').physics,lower=sprite.findPart(side+'_forearm').physics;
        const u=sprite.getAnimationBoneTransform(side+'_upper_arm',pdg.animationSpace_World);
        const e=sprite.getAnimationBoneTransform(side+'_forearm',pdg.animationSpace_World),s=lower.getState();
        const dx=e.x-s.x,dy=e.y-s.y,c=Math.cos(s.rotation),sin=Math.sin(s.rotation);
        return {side,sign:side==='left'?1:-1,target:null,poseReversed:null,reversed:false,visible:false,transitioning:false,
            upper,lower,upperAxisOffset:u.rotation-upper.getState().rotation,
            elbowOffset:{x:c*dx+sin*dy,y:-sin*dx+c*dy},limit:joints.find(j=>j.name===side+'_forearm')};
    });
    const wrapped=a=>Math.atan2(Math.sin(a),Math.cos(a));
    function update(view,recovering) {
        for(const arm of arms) {
            const {side,sign,limit}=arm,upper=arm.upper.getState(),lower=arm.lower.getState();
            if(!limit.joint.isActive())continue; // An elbow may have been detached.
            const actual=(lower.rotation-upper.rotation-limit.offset)/rad;
            const wasReversed=arm.reversed;
            if(arm.poseReversed!==null)arm.reversed=arm.poseReversed;
            else if(arm.target) {
                const c=Math.cos(lower.rotation),s=Math.sin(lower.rotation),p=arm.elbowOffset;
                const elbow={x:lower.x+c*p.x-s*p.y,y:lower.y+s*p.x+c*p.y};
                const dx=arm.target.x-elbow.x,dy=arm.target.y-elbow.y;
                if(Math.hypot(dx,dy)>8) {
                    const requested=sign*wrapped(Math.atan2(dy,dx)-upper.rotation-arm.upperAxisOffset)/rad;
                    // Hysteresis prevents a near-straight drag from chattering.
                    // Directly behind the upper arm either projection is
                    // ambiguous; retain the current branch around +/-180.
                    if(requested>12 && requested<165)arm.reversed=true;
                    else if(requested<-12 && requested>-165)arm.reversed=false;
                }
            } else if(recovering || sprite.getAnimationPhysicsMode(side+'_forearm')!==pdg.animationPhysics_Dynamic) {
                const requested=sign*wrapped(view.getLocalTransform(side+'_forearm').rotation)/rad;
                arm.reversed=requested>8;
            }
            const positive=arm.reversed?sign===1:sign===-1;
            limit.min=positive?2:-150;limit.max=positive?150:-2;
            // Do not slam a newly reversed stop into an already bent arm.
            // Admit both projections until the body crosses to the requested
            // side, then restore the 2-degree stop short of straight.
            if(arm.reversed!==wasReversed)arm.transitioning=true;
            if(positive?actual>=2:actual<=-2)arm.transitioning=false;
            const min=limit.offset+(arm.transitioning?-150:limit.min)*rad;
            const max=limit.offset+(arm.transitioning?150:limit.max)*rad;
            if(Math.abs(limit.joint.getMinAngle()-min)>1e-8 || Math.abs(limit.joint.getMaxAngle()-max)>1e-8)
                limit.joint.setAngleLimits(min,max);
            arm.visible=arm.reversed || (arm.transitioning && sign*actual>2);
        }
    }
    return {
        update,
        setTarget(side,target) {arms.find(a=>a.side===side).target=target;},
        // Posing chooses a branch explicitly, including at the straight-arm
        // hysteresis boundary. Release with null before resuming animation.
        setPoseReversed(side,reversed) {arms.find(a=>a.side===side).poseReversed=reversed;},
        artwork(side,fallback) {return arms.find(a=>a.side===side).visible?side+'_hand_twisted':fallback;},
        getState:()=>arms.map(({side,reversed,visible,transitioning,limit})=>({side,reversed,visible,transitioning,
            min:limit.min,max:limit.max}))
    };
}
module.exports={createArmTwist};
