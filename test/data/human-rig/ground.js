// Demo ground motion and foot planting, using PDG's public pose/IK APIs.
'use strict';
const {bones}=require('./human');
const limit=10*Math.PI/180, sweepSeconds=10, fastSweepSeconds=1;
const ease=t=>(1-Math.cos(Math.PI*Math.max(0,Math.min(1,t))))/2;
const rotate=(p,a)=>({x:Math.cos(a)*p.x-Math.sin(a)*p.y,
    y:Math.sin(a)*p.x+Math.cos(a)*p.y});

class GroundMotion {
    constructor() {
        this.tilting=false;
        this.started=0;
        this.from=0;
        this.returnSeconds=0;
        this.sweepSeconds=sweepSeconds;
    }
    setTilting(enabled,seconds,angle=this.sample(seconds),duration=this.sweepSeconds) {
        if(!Number.isFinite(duration) || duration<=0)throw Error('Tilt duration must be positive seconds');
        this.sweepSeconds=duration;
        this.tilting=enabled;
        this.started=seconds;
        this.from=angle;
        this.returnSeconds=duration*Math.abs(angle)/(2*limit);
    }
    sample(seconds) {
        const elapsed=Math.max(0,seconds-this.started);
        if(!this.tilting)
            return this.returnSeconds ? this.from*(1-ease(elapsed/this.returnSeconds)) : 0;
        // Ease from the current angle to +10 degrees, then use the same duration
        // from each extreme to the other, slowing smoothly at the turnarounds.
        const duration=this.sweepSeconds;
        if(elapsed<duration)return this.from+(limit-this.from)*ease(elapsed/duration);
        return limit*Math.cos(Math.PI*(elapsed-duration)/duration);
    }
}

function plantFeet(pdg,sprite) {
    const legs=['left','right'].map(side=> {
        const thigh=bones.find(b=>b.name===side+'_thigh');
        const shin=bones.find(b=>b.name===side+'_shin');
        const foot=bones.find(b=>b.name===side+'_foot');
        const h=thigh.reference,k=shin.reference,a=foot.reference;
        const cross=(a.x-h.x)*(k.y-h.y)-(a.y-h.y)*(k.x-h.x);
        return {side,thigh,shin,foot,bendDirection:cross>0?1:-1,target:{...a}};
    });
    const ground={angle:0,legs,modifierIds:[],enabled:false};
    const install=()=> {
        ground.modifierIds.push(sprite.addAnimationModifier(view=> {
            // Keep the animated weight shift and upper body upright. Lower the
            // pelvis only as far as necessary for the downhill leg to reach.
            let drop=0;
            for(const leg of legs) {
                const hip=view.getTransform(leg.thigh.name,pdg.animationSpace_Rig);
                const knee=view.getLocalTransform(leg.shin.name);
                const ankle=view.getLocalTransform(leg.foot.name);
                const reach=Math.hypot(knee.x,knee.y)+Math.hypot(ankle.x,ankle.y);
                const dx=leg.target.x-hip.x;
                const height=Math.sqrt(Math.max(0,reach*reach-dx*dx));
                drop=Math.max(drop,leg.target.y-height-hip.y);
            }
            const root=view.getLocalTransform('root');
            root.y+=drop;
            view.setLocalTransform('root',root);
        },pdg.animationStage_PreConstraint));
        for(const leg of legs) {
            leg.ik=sprite.addAnimationIK({root:leg.thigh.name,middle:leg.shin.name,tip:leg.foot.name,
                targetX:leg.target.x,targetY:leg.target.y,space:pdg.animationSpace_Rig,
                bendDirection:leg.bendDirection,stretch:pdg.animationIK_NoStretch});
            ground.modifierIds.push(leg.ik);
        }
        ground.modifierIds.push(sprite.addAnimationModifier(view=> {
            // The target setter updates position only. Align each shoe after the
            // leg solve, preserving its authored ankle-to-sole offset.
            for(const leg of legs) {
                const foot=view.getTransform(leg.foot.name,pdg.animationSpace_Rig);
                view.rotateLocal(leg.foot.name,leg.foot.reference.angle+ground.angle-foot.rotation);
            }
        },pdg.animationStage_PostConstraint));
    };
    ground.setAngle=angle=> {
        ground.angle=angle;
        for(const leg of legs) {
            // Rig (0,0) lies on the soles. Rotating the whole reference ankle
            // offset about it keeps the shoe contact fixed on the platform.
            leg.target=rotate(leg.foot.reference,angle);
            if(ground.enabled)sprite.setAnimationIKTarget(leg.ik,leg.target.x,leg.target.y,pdg.animationSpace_Rig);
        }
    };
    ground.setEnabled=enabled=> {
        if(ground.enabled===enabled)return;
        if(enabled)install();
        else {ground.modifierIds.forEach(id=>sprite.removeAnimationModifier(id));ground.modifierIds=[];}
        ground.enabled=enabled;
    };
    ground.remove=()=>ground.setEnabled(false);
    ground.setEnabled(true);
    return ground;
}

module.exports={GroundMotion,plantFeet,limit,sweepSeconds,fastSweepSeconds};
