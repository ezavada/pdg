// The human rig demo, replayed through independently scheduled Bone controls.
'use strict';
const {bones,clips,artwork,artworkAt,artworkUnitsPerCm}=require('../data/human-rig/human');
module.exports=function(pdg,interactive){
    const session=pdg.visualTestSession;
    const port=pdg.gfx.createWindowPort(new pdg.Rect(1000,760),'Human bone controls');
    pdg.gfx.setTargetFPS(60);
    const layer=pdg.createSpriteLayer(port);layer.setUseChipmunkPhysics(false);
    const P=(x,y)=>new pdg.Point(x,y);
    const fill=color=>new pdg.Attributes().fillColor(color);
    const motions=clips.filter(clip=>clip.name!=='reference');
    const speed=interactive?1:2,scale=2.65;
    let selected=0,age=0,finished=false,frames=0,checks=0,showBones=false;
    let stats,handles;
    const drawings={};
    artwork.forEach(art=>{
        const drawing=pdg.createDrawing();
        art.contours.forEach(contour=>{
            const polygon=new pdg.Polygon();
            contour.forEach(([x,y])=>polygon.addPoint(P(x*artworkUnitsPerCm,y*artworkUnitsPerCm)));
            drawing.addPolygon(polygon,fill('#172638').scale(1/artworkUnitsPerCm));
        });
        drawings[art.name]=drawing;
    });
    function makeHuman(x){
        const sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/human-rig/human.scml');
        if(!sprite.enableAnimationPose('reference'))throw Error(sprite.getAnimationRigError());
        sprite.setLocation(x,650).setScale(scale);
        bones.forEach(bone=>sprite.addAnimationDrawable(()=>drawings[artworkAt(bone.name,motions[selected].name,Math.min(age*speed,motions[selected].seconds))],
            {bone:bone.name,slot:bone.name+'_art',placement:pdg.animationDraw_ReplaceSlot,strokeSpace:pdg.animationStroke_Local}));
        return sprite;
    }
    const reference=makeHuman(260),controlled=makeHuman(740);
    handles=bones.map(bone=>controlled.getBone(bone.name));
    const angleDifference=(a,b)=>Math.atan2(Math.sin(a-b),Math.cos(a-b));
    function start(index){
        selected=(index+motions.length)%motions.length;age=0;
        stats={samples:0,maxPositionError:0,maxAngleError:0,maxFootDrift:0,hipTravel:0,handLift:0};
        handles.forEach(bone=>bone.cancelSchedule().diminish(0,0));
        controlled.startAnimation('reference');controlled.seekAnimation('reference',0);controlled.pauseAnimation();
        const clip=motions[selected];
        // Use the same 24 Hz keys as human.scml, including its hand-art switches.
        // The reference is the authored clip; the other Sprite stays in bind pose.
        // Paired move/rotate tweens reproduce its local motion through Bone alone.
        const times=[0,clip.seconds];
        for(let key=1;key<clip.seconds*24;key++)times.push(Math.round(key*1000/24)/1000);
        if(clip.name==='wave_hello')times.push(.27,5.22);
        times.sort((a,b)=>a-b);
        const poses=times.map(time=>controlled.sampleAnimationPose(clip.name,time).bones);
        handles.forEach((bone,id)=>{
            const initial=poses[0][id];
            bone.moveTo(initial.x,initial.y).rotateTo(initial.rotation).series();
            let angle=initial.rotation;
            for(let key=1;key<times.length;key++){
                const target=poses[key][id],duration=(times[key]-times[key-1])/speed;
                angle+=angleDifference(target.rotation,angle);
                bone.moveTo(target.x,target.y,duration,pdg.linearTween).andAlso().rotateTo(angle,duration,pdg.linearTween);
            }
            bone.diminish(0,.25).endSeries();
        });
        reference.startAnimation(clip.name);reference.pauseAnimation();
    }
    function finish(){
        if(finished)return;finished=true;
        handles.forEach(bone=>bone.cancelSchedule());
        setTimeout(()=>{pdg.cleanupLayer(layer);pdg.gfx.closeGraphicsPort(port);pdg.quit();},0);
    }
    controlled.addAnimationHelper(new pdg.IAnimationHelper((owner,dt)=>{
        age+=dt;
        const clip=motions[selected];
        reference.seekAnimation(age*speed<=clip.seconds?clip.name:'reference',age*speed<=clip.seconds?age*speed:0);
        return true;
    }));
    pdg.on(pdg.eventType_PortDraw,event=>{
        if(event.port!==port)return false;
        port.drawRect(port.getDrawingArea(),fill('#eef2f6'));
        port.drawRect(new pdg.Rect(20,118,490,670),fill('#ffffff'));
        port.drawRect(new pdg.Rect(510,118,980,670),fill('#ffffff'));
        port.drawLine(P(40,650),P(470,650),new pdg.Attributes().lineColor('#9babbc').lineThickness(2));
        port.drawLine(P(530,650),P(960,650),new pdg.Attributes().lineColor('#9babbc').lineThickness(2));
        return false;
    });
    function text(message,x,y,size=17,color='#172638'){port.drawText(message,P(x,y),fill(color).textSize(size));}
    layer.onDrawPortComplete(()=>{
        if(finished)return false;
        ++frames;
        const clip=motions[selected],time=age*speed;
        if(time<=clip.seconds){
            const expected=controlled.sampleAnimationPose(clip.name,time).bones;
            bones.forEach((bone,id)=>{
                const actual=controlled.getAnimationBoneTransform(bone.name),target=expected[id];
                stats.maxPositionError=Math.max(stats.maxPositionError,Math.hypot(actual.x-target.x,actual.y-target.y));
                stats.maxAngleError=Math.max(stats.maxAngleError,Math.abs(angleDifference(actual.rotation,target.rotation)));
                if(bone.name.endsWith('_foot')){
                    const foot=controlled.getAnimationBoneTransform(bone.name,pdg.animationSpace_Rig);
                    stats.maxFootDrift=Math.max(stats.maxFootDrift,Math.hypot(foot.x-bone.reference.x,foot.y-bone.reference.y));
                }
            });
            const hip=controlled.getAnimationBoneTransform('root',pdg.animationSpace_Rig);
            const hand=controlled.getAnimationBoneTransform('left_hand',pdg.animationSpace_Rig);
            stats.hipTravel=Math.max(stats.hipTravel,Math.abs(hip.x-bones.find(b=>b.name==='root').reference.x));
            stats.handLift=Math.max(stats.handLift,bones.find(b=>b.name==='left_hand').reference.y-hand.y);
            ++stats.samples;
        }else{reference.seekAnimation('reference',0);reference.pauseAnimation();}
        text('Human rig — animated bone controls',28,38,27);
        text(clip.name==='weight_shift'?'Weight shift: pelvis travel, body balance and planted feet.':'Wave hello: shoulder lift, elbow swing, wrist wave and open hand.',28,72);
        text('Authored Spriter animation',110,108,20);
        text('Bone.moveTo() + Bone.rotateTo()',565,108,20);
        const progress=Math.min(1,time/clip.seconds);
        port.drawRect(new pdg.Rect(28,683,972,687),fill('#d3dce6'));
        port.drawRect(new pdg.Rect(28,683,28+944*progress,687),fill('#3479b5'));
        text(time>clip.seconds?'diminish(0, 0.25): release to bind pose':clip.name+'   '+Math.min(time,clip.seconds).toFixed(1)+' / '+clip.seconds+' s',28,713,16);
        text('Space: next motion   R: restart   B: bones   Escape: exit',28,742,16);
        if(session)session.draw(port);
        if(age>=clip.seconds/speed+.35){
            if(!stats.samples || stats.maxPositionError>.03 || stats.maxAngleError>.01)throw Error('Human Bone replay diverged: '+JSON.stringify(stats));
            if(stats.maxFootDrift>.15)throw Error('Human Bone replay lost planted feet: '+JSON.stringify(stats));
            if(stats.hipTravel<1 || (selected===1 && stats.handLift<40))throw Error('Human Bone replay did not shift/wave: '+JSON.stringify(stats));
            if(handles.some(bone=>bone.getInfluence()>.001))throw Error('Human Bone controls did not release');
            ++checks;console.log('Human bone controls '+clip.name+': '+JSON.stringify(stats));
            if(!interactive && selected===motions.length-1){console.log('Human bone visual checks: '+checks+' passed; '+frames+' rendered frames');finish();}
            else start(selected+1);
        }
        return false;
    });
    pdg.onKeyPress(event=>{
        if(event.unicode===pdg.key_Escape){finish();return true;}
        if(event.unicode===32){start(selected+1);return true;}
        if(event.unicode===114){start(selected);return true;}
        if(event.unicode===98){showBones=!showBones;[reference,controlled].forEach(sprite=>sprite.setAnimationDebugDraw(showBones?pdg.animationDebug_Bones:pdg.animationDebug_None));return true;}
        return false;
    });
    start(0);pdg.run();
};
