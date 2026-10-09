// Original procedural artwork; every appendage is animated by native PDG controllers.
'use strict';
module.exports=function(pdg,mode){
    const session=pdg.visualTestSession,interactive=!!session||process.argv.indexOf('--ui-test')<0;
    const port=pdg.gfx.createWindowPort(new pdg.Rect(1100,760),mode==='jiggle'?'Spring tide — PDG jiggle':'Abyssal reach — PDG FABRIK');
    pdg.gfx.setTargetFPS(60);
    const layer=pdg.createSpriteLayer(port);layer.setUseChipmunkPhysics(false);
    const clock=layer.createSprite(),P=(x,y)=>new pdg.Point(x,y),fill=c=>new pdg.Attributes().fillColor(c);
    const stroke=(c,w)=>new pdg.Attributes().lineColor(c).lineThickness(w);
    const rigs=[],palette=['#63eed3','#f6adca','#a99cff'];
    let age=0,frames=0,paused=false,enabled=true,mouse=null,jointDots=false,showTrails=false,finished=false,checks=0,reachBlend=0;
    let pointerInsideCanvas=true,pointerFocused=true;
    function chain(sprite,name,count,length,x,y,angle){const parts=[];for(let i=0;i<count;++i){const p=sprite.createPart(name+i);if(i)p.setParentPart(parts[i-1]).setLocation(length,0);else p.setLocation(x,y).setRotation(angle);parts.push(p);}return parts;}
    function world(p){const t=p.getTransform(pdg.partSpace_World);return P(t.tx,t.ty);}
    for(let row=0;row<3;++row){const sprite=layer.createSprite(),color=palette[row],arms=[];
        sprite.setLocation(230+row*320,245);
        const count=mode==='jiggle'?8:11,restLengths=[134,199,252,185,143];
        for(let a=0;a<5;++a){const length=restLengths[a]*(1+(row-1)*.035)/(count-1),parts=chain(sprite,'a'+a+'_',count,length,(a-2)*22,25,Math.PI/2);
            const root=parts[0];
            // Strong, restrained roots give way to softer, less damped tips.
            const tuning=parts.map((part,index)=>{const t=index/(count-1);return {part,
                frequency:3.2-2.35*t,dampingRatio:[.16,.5,1][row]*(1-.45*t),
                inertia:.12+.7*t,maxAngle:.3+1.05*t};});
            if(mode==='jiggle')root.setJiggle({mode:pdg.jiggleMode_Chain,chain:parts.slice(1),length:length,gravityY:180,teleportDistance:250,joints:tuning});
            arms.push({parts,root,length,target:P(0,0),goal:null,trail:[],tuning});
        }
        rigs.push({sprite,color,arms,row});
    }
    // A two-link instrument shows target filtering alongside angular chain jiggle.
    const armSprite=layer.createSprite();armSprite.setLocation(85,610);
    const arm=chain(armSprite,'instrument',3,55,0,0,-.6);
    if(mode==='jiggle'){arm[0].setIKTarget(arm[1],arm[2],P(90,-35),pdg.partSpace_Sprite);arm[0].setJiggle({mode:pdg.jiggleMode_IKTarget,frequency:2,dampingRatio:.25,maxDistance:100,teleportDistance:300});}
    const sceneBounds={left:24,top:118,right:1076,bottom:590};
    function restPose(a){a.root.setRotation(Math.PI/2);a.parts.slice(1).forEach(p=>p.setRotation(0));}
    function restTentacle(a){if(a.root.hasIKTarget())a.root.clearIKTarget();restPose(a);a.goal=null;}
    function setPointer(point){
        if(mode!=='fabrik')return;
        mouse=point&&point.x>=sceneBounds.left&&point.x<sceneBounds.right&&point.y>=sceneBounds.top&&point.y<sceneBounds.bottom?P(point.x,point.y):null;
    }
    function reset(){reachBlend=0;rigs.forEach(r=>r.arms.forEach(a=>{if(mode==='jiggle')a.root.resetJiggle();else restTentacle(a);a.trail=[];}));if(mode==='jiggle')arm[0].resetJiggle();}

    function kick(){if(mode==='jiggle'&&enabled)rigs.forEach(r=>r.arms.forEach((a,i)=>a.root.kickJiggle({angularVelocity:(i-2)*2+3,joint:a.parts[2]})));}
    clock.addAnimationHelper(new pdg.IAnimationHelper((owner,dt)=>{
        if(paused)return true;age+=dt;
        // Bound catch-up after stalls; ease a reversible half-second fade.
        const step=Math.min(dt,.05),desiredBlend=mouse?1:0;
        reachBlend+=Math.sign(desiredBlend-reachBlend)*Math.min(Math.abs(desiredBlend-reachBlend),step/.55);
        const influence=reachBlend*reachBlend*(3-2*reachBlend);
        rigs.forEach(r=>{const x=230+r.row*320+(mode==='jiggle'?18*Math.sin(age*1.5+r.row):0),y=245+(mode==='jiggle'?12*Math.cos(age*1.9+r.row):0);
            r.sprite.setLocation(x,y);
            r.arms.forEach((a,i)=>{if(mode==='jiggle')a.root.setRotation(Math.PI/2);
                else if(reachBlend>0){
                    if(mouse){const desired=P(mouse.x-x+(i-2)*18,mouse.y-y),follow=1-Math.exp(-step/.12);
                        if(!a.goal)a.goal=desired;else{a.goal.x+=(desired.x-a.goal.x)*follow;a.goal.y+=(desired.y-a.goal.y)*follow;}}
                    // Always blend from the authored pose, rather than accumulating
                    // partial IK on top of last frame's procedural rotations.
                    restPose(a);a.target=P(x+a.goal.x,y+a.goal.y);
                    a.root.setFABRIKTarget(a.parts.slice(1),a.goal,{space:pdg.partSpace_Sprite,influence,maxIterations:48,tolerance:.08});
                }else restTentacle(a);
            });
        });
        if(mode==='jiggle')arm[0].setIKTarget(arm[1],arm[2],P(68+25*Math.sin(age*2.7),-38+30*Math.cos(age*2.1)),pdg.partSpace_Sprite);
        return true;
    }));
    function text(s,x,y,size=16,c='#bfd4de'){port.drawText(s,P(x,y),fill(c).textSize(size));}
    function poly(points,c){const p=new pdg.Polygon();points.forEach(v=>p.addPoint(P(v[0],v[1])));port.drawPolygon(p,fill(c));}
    function drawChain(a,color){const points=a.parts.map(world),tip=points[points.length-1];
        const previous=a.trail[a.trail.length-1];
        if(!paused&&(!previous||Math.hypot(tip.x-previous.x,tip.y-previous.y)>.35)){a.trail.push(P(tip.x,tip.y));if(a.trail.length>45)a.trail.shift();}
        if(showTrails)for(let i=1;i<a.trail.length;++i){
            const start=a.trail[i-1],end=a.trail[i],length=Math.hypot(end.x-start.x,end.y-start.y);
            if(length<.001)continue;
            const progress=i/(a.trail.length-1),width=.4+progress*.85,nx=-(end.y-start.y)/length*width,ny=(end.x-start.x)/length*width;
            const rgb=[1,3,5].map(at=>parseInt(color.slice(at,at+2),16)),background=[7,21,33],strength=.35+progress*.35;
            const trailColor='#'+rgb.map((value,channel)=>Math.round(background[channel]+(value-background[channel])*strength).toString(16).padStart(2,'0')).join('');
            // Filled ribbons retain their width on renderers with one-pixel GL lines.
            poly([[start.x+nx,start.y+ny],[end.x+nx,end.y+ny],[end.x-nx,end.y-ny],[start.x-nx,start.y-ny]],trailColor);
        }
        for(let i=1;i<points.length;++i){const start=points[i-1],end=points[i],w=Math.max(2,7-i*.48),l=Math.hypot(end.x-start.x,end.y-start.y),nx=-(end.y-start.y)/l,ny=(end.x-start.x)/l;
            function ribbon(width,c){poly([[start.x+nx*width,start.y+ny*width],[end.x+nx*(width*.85),end.y+ny*(width*.85)],[end.x-nx*(width*.85),end.y-ny*(width*.85)],[start.x-nx*width,start.y-ny*width]],c);}
            ribbon(w+3,'#122c3c');ribbon(w,color);port.drawCircle(start,w,fill(color));port.drawLine(start,end,stroke('#e6fff4',1));
        }
        port.drawCircle(tip,4,fill(color));if(jointDots)points.forEach(p=>port.drawCircle(p,3,fill('#ffffff')));
        if(mode==='fabrik'&&mouse){const t=a.target;port.drawCircle(t,7,stroke(color,1));port.drawLine(P(t.x-11,t.y),P(t.x+11,t.y),stroke(color,1));port.drawLine(P(t.x,t.y-11),P(t.x,t.y+11),stroke(color,1));}
        for(let i=1;i<points.length;++i){const l=Math.hypot(points[i].x-points[i-1].x,points[i].y-points[i-1].y);if(Math.abs(l-a.length)>.02)throw Error('Procedural demo changed link length');++checks;}
    }
    pdg.on(pdg.eventType_PortDraw,event=>{if(event.port!==port)return false;
        port.drawRect(port.getDrawingArea(),fill('#071521'));
        // Deterministic plankton and receding current lines create a deep-water stage.
        for(let i=0;i<90;++i){const x=(i*157.3+12*Math.sin(age*.3+i))%1100,y=125+(i*83.7+age*7)%530;port.drawCircle(P(x,y),i%7?1:2,fill(i%7?'#1d384a':'#3c6571'));}
        for(let y=160;y<690;y+=65)port.drawLine(P(24,y),P(1076,y),stroke('#112332',1));return false;
    });
    layer.onDrawPortComplete(()=>{if(finished)return false;++frames;
        rigs.forEach(r=>{r.arms.forEach(a=>drawChain(a,r.color));const center=r.sprite.getLocation(),x=center.x,y=center.y;
            poly([[x-77,y+25],[x-64,y-8],[x-37,y-43],[x,y-55],[x+37,y-43],[x+64,y-8],[x+77,y+25]],'#163846');
            poly([[x-65,y+16],[x-54,y-5],[x-28,y-31],[x,y-40],[x+28,y-31],[x+54,y-5],[x+65,y+16]],r.color);
            for(let i=-2;i<=2;++i)port.drawLine(P(x+i*20,y+18),P(x+i*10,y-30),stroke('#c5fff0',1));
            port.drawCircle(P(x-18,y-2),7,fill('#071521'));port.drawCircle(P(x+18,y-2),7,fill('#071521'));port.drawCircle(P(x-16,y-4),2,fill('#ffffff'));port.drawCircle(P(x+20,y-4),2,fill('#ffffff'));
            text(mode==='jiggle'?['Bouncy / damping 0.16','Fluid / damping 0.50','Settled / damping 1.00'][r.row]:['Longer inner tentacles','Varied resting lengths','Pointer-driven reaching'][r.row],x-110,175,17,r.color);
            if(mode==='fabrik'){if(reachBlend>0){const results=r.arms.map(a=>a.root.getFABRIKResult());text('Error '+Math.max.apply(null,results.map(v=>v.reachError)).toFixed(2)+' px  |  '+Math.max.apply(null,results.map(v=>v.iterations))+' passes',x-110,576,15);}else text('Resting — no IK solve',x-110,576,15);}
        });
        text(mode==='jiggle'?'SPRING TIDE':'ABYSSAL REACH',38,57,32,'#effcf8');
        text(mode==='jiggle'?'Secondary motion: independent angular springs + spring-filtered IK targets':'Fifteen varied chains rest downward and reach toward the pointer',40,89,18);
        if(mode==='jiggle'){const a={parts:arm,length:55,trail:[]};drawChain(a,'#ffce79');const r=arm[0].getJiggleResult();port.drawCircle(P(r.desiredTarget.x,r.desiredTarget.y),7,stroke('#ffce79',1));port.drawCircle(P(r.effectiveTarget.x,r.effectiveTarget.y),4,fill('#ffffff'));text('IK instrument: desired ring / filtered white tip',220,616,17,'#ffce79');text('Target lag '+r.lagDistance.toFixed(1)+' px',220,642,15);}
        else{text(mouse?'Following pointer — move it beyond reach to inspect bounded error':'Move the pointer into the scene to reach; leave to hang straight down',42,616,18,'#ffce79');text('Long inner tentacles and shorter outer ones preserve their individual link lengths.',42,646,16);}
        text('Tip-motion trails: '+(showTrails?'on':'off')+'  |  T: show/hide trails',40,674,15,'#91b8c8');
        text('K: impulse   R: reset   B: joints   E: jiggle on/off   Space: pause   Esc: close',40,706,16);
        if(session)session.draw(port);
        const checkingInput=typeof window!=='undefined'&&window.pdgProceduralDemo&&window.pdgProceduralDemo.checkingInput;
        if(!interactive&&age>8&&!checkingInput){finished=true;console.log(mode+' demo: '+frames+' rendered frames; '+checks+' segment checks passed');setTimeout(()=>{pdg.cleanupLayer(layer);pdg.gfx.closeGraphicsPort(port);pdg.quit();},0);}
        return false;
    });
    pdg.onMouseMove(event=>{if(pointerInsideCanvas&&pointerFocused)setPointer(event.mousePos);return false;});
    // Browser canvas exit can happen without a final in-canvas mouse move.
    if(typeof window!=='undefined'){
        const canvas=document.getElementById('pdg-canvas');
        if(canvas){
            canvas.addEventListener('mouseenter',event=>{
                pointerInsideCanvas=true;
                const r=canvas.getBoundingClientRect();
                if(pointerFocused)setPointer(P((event.clientX-r.left)*canvas.width/r.width,(event.clientY-r.top)*canvas.height/r.height));
            });
            canvas.addEventListener('mouseleave',()=>{pointerInsideCanvas=false;setPointer(null);});
        }
        // Ignore queued native moves after DOM exit/blur until input resumes.
        window.addEventListener('blur',()=>{pointerFocused=false;setPointer(null);});
        window.addEventListener('focus',()=>{pointerFocused=true;});
        window.pdgProceduralDemo={checkingInput:false,getState:()=>({mode,frames,reaching:!!mouse,blend:reachBlend,showTrails,sceneBounds,
            tentacles:rigs.flatMap(r=>r.arms.map(a=>({length:a.length*(a.parts.length-1),active:a.root.hasIKTarget(),points:a.parts.map(world)})))})};
    }

    pdg.onKeyPress(event=>{const key=event.unicode;if(key===107)kick();else if(key===114)reset();else if(key===98)jointDots=!jointDots;else if(key===116)showTrails=!showTrails;else if(key===101&&mode==='jiggle'){enabled=!enabled;rigs.forEach(r=>r.arms.forEach(a=>a.root.setJiggleEnabled(enabled)));arm[0].setJiggleEnabled(enabled);}else if(key===32&&!session){paused=!paused;if(paused)layer.stopAnimations();else layer.startAnimations();}else if(key===pdg.key_Escape){pdg.cleanupLayer(layer);pdg.gfx.closeGraphicsPort(port);pdg.quit();}else return false;return true;});
    pdg.run();
};
