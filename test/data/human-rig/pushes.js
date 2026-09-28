// Shoulder pushes and automatic return through the demo's physical recovery.
'use strict';
const pushSettings={soft:{newtons:80,seconds:.18,reactAfter:.25},hard:{newtons:650,seconds:.22,reactAfter:1.8}};
function createPushes(pdg,layer,sprite,ground,rig,origin,scale,clock) {
    const bounds=new pdg.Rect(origin.x+88*scale,origin.y-182*scale,origin.x+94*scale,origin.y+50*scale);
    const state={bounds,kind:null,phase:null,contacts:0,completed:0,lastResult:null,point:null,started:0};
    const torso=sprite.findPart('torso').physics;
    for(const name of sprite.getAnimationBoneNames()) {
        const part=sprite.findPart(name);
        if(part && part.physics.isPresent())part.collider.setCollisionMask(part.collider.getCollisionMask()|16);
    }
    const wall=layer.createSprite();wall.setupPhysicsBody().setMode(pdg.physicsBody_Static);
    wall.setupCollider().setBox(bounds).setCategory(16).setCollisionMask(3).setFriction(.25).setRestitution(0)
        .setContactHandler(contact=> {
            if(contact.phase===pdg.collision_End)return;
            if(state.phase==='pushing') {
                state.contacts++;
                if(firstContact===null)firstContact=clock();
            }
        });
    let firstContact=null,force=0,completion=0,startShoulder,maxTravel=0,maxFootError=0;
    state.cancel=()=> {
        if(force)torso.removeForce(force);
        force=0;state.phase=null;
    };
    state.push=kind=> {
        if(kind!=='soft' && kind!=='hard')throw Error('Unknown shoulder push');
        if(state.phase || rig.mode!=='standing')return false;
        const settings=pushSettings[kind];
        startShoulder=sprite.getAnimationBoneTransform('right_upper_arm',pdg.animationSpace_World);
        state.cancel();rig.drop();
        state.kind=kind;state.phase='pushing';state.started=clock();state.contacts=0;
        state.point={x:startShoulder.x,y:startShoulder.y};firstContact=null;maxTravel=maxFootError=0;
        completion=rig.completions;
        // Apply a short force to the torso at the shoulder pivot, not the
        // upper-arm center. Newton values convert to the layer's pixel units.
        force=torso.applyForce(new pdg.Vector(settings.newtons*100*scale,0),settings.seconds,0,
            new pdg.Point(startShoulder.x,startShoulder.y));
        return true;
    };
    state.update=()=> {
        if(!state.phase)return;
        const time=clock(),shoulder=sprite.getAnimationBoneTransform('right_upper_arm',pdg.animationSpace_World);
        maxTravel=Math.max(maxTravel,(shoulder.x-startShoulder.x)/scale);
        for(const leg of ground.legs) {
            const foot=sprite.getAnimationBoneTransform(leg.foot.name,pdg.animationSpace_World);
            maxFootError=Math.max(maxFootError,Math.hypot(foot.x-origin.x-leg.target.x*scale,
                foot.y-origin.y-leg.target.y*scale)/scale);
        }
        if(state.phase==='pushing') {
            const react=state.kind==='hard' && firstContact!==null ? firstContact+.35 : state.started+pushSettings[state.kind].reactAfter;
            if(time>=react) {
                if(force)torso.removeForce(force);
                force=0;rig.recover();state.phase='recovering';
            }
        } else if(rig.mode==='standing' && rig.completions>completion) {
            state.lastResult={kind:state.kind,wallContacts:state.contacts,shoulderTravelCm:maxTravel,
                footTravelCm:maxFootError,recoverySeconds:rig.lastRecoverySeconds};
            state.completed++;state.phase=null;
        }
    };
    return state;
}
module.exports={createPushes,pushSettings};
