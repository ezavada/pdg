// Practical angular envelopes for this 2D silhouette, in bone-local degrees.
'use strict';
const {bones}=require('./human');
const degrees=Math.PI/180;
const bind=name=>bones.find(b=>b.name===name).local.angle/degrees;
const limits=[
    {name:'torso',min:-25,max:25},
    {name:'neck',min:-20,max:20},
    {name:'head',min:-25,max:25}
];
for(const side of ['left','right']) {
    const left=side==='left';
    limits.push(
        {name:side+'_upper_arm',min:bind(side+'_upper_arm')+(left?-150:-25),max:bind(side+'_upper_arm')+(left?25:150)},
        {name:side+'_forearm',min:left?-150:2,max:left?-2:150},
        {name:side+'_hand',min:-55,max:55},
        {name:side+'_thigh',min:bind(side+'_thigh')-75,max:bind(side+'_thigh')+75},
        {name:side+'_shin',min:left?0:-150,max:left?150:0},
        {name:side+'_foot',min:bind(side+'_foot')-50,max:bind(side+'_foot')+50}
    );
}
function installJointLimits(pdg,sprite,elbows) {
    return limits.map(limit=> {
        const bone=bones.find(b=>b.name===limit.name);
        const parent=sprite.findPart(bone.parent).physics,child=sprite.findPart(bone.name).physics;
        // Keep the native body's angular branch and its capsule-axis offset.
        const offset=child.getState().rotation-parent.getState().rotation-bone.local.angle;
        const min=offset+limit.min*degrees,max=offset+limit.max*degrees;
        let joint;
        if(limit.name.endsWith('_forearm')) {
            joint=elbows[limit.name.startsWith('left')?0:1];joint.setAngleLimits(min,max);
        } else joint=parent.createRotaryLimit(child,min,max);
        return {...limit,joint,offset};
    });
}
function limitPose(view,activeLimits=limits) {
    for(const limit of activeLimits) {
        const bone=bones.find(b=>b.name===limit.name),t=view.getLocalTransform(limit.name);
        const angle=bone.local.angle+Math.atan2(Math.sin(t.rotation-bone.local.angle),Math.cos(t.rotation-bone.local.angle));
        t.rotation+=Math.max(limit.min*degrees,Math.min(limit.max*degrees,angle))-angle;
        view.setLocalTransform(limit.name,t);
    }
}
module.exports={limits,installJointLimits,limitPose};
