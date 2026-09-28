// Inspect the generated rig's actual collider geometry and physical body masses.
'use strict';
function createCapsuleOverlay(pdg,sprite,bones) {
    const parts=bones.map(bone=> {
        const part=sprite.findPart(bone.name);
        return {bone,part,body:part.physics,collider:part.collider};
    });
    const P=(x,y)=>new pdg.Point(x,y);
    const line=new pdg.Attributes().lineColor('#21c4cd').lineThickness(1.5);
    const leader=new pdg.Attributes().lineColor('#7aabad').lineThickness(1);
    const background=new pdg.Attributes().fillColor('#f2f8f8').roundedCorners(3);
    const ink=new pdg.Attributes().fillColor('#245559').textSize(11);
    const read=()=>parts.map(({bone,part,body,collider})=> {
        // Generated Part colliders use unscaled physical body coordinates,
        // independently of the animation bone's display scale or control mode.
        const state=body.getState(),c=Math.cos(state.rotation),s=Math.sin(state.rotation);
        const world=p=>P(state.x+c*p.x-s*p.y,state.y+s*p.x+c*p.y);
        const capsules=[];
        for(let i=0;i<collider.getShapeCount();i++) {
            const id=collider.getShapeId(i);
            if(collider.getShapeType(id)!==pdg.collisionShape_Capsule)continue;
            capsules.push({start:world(collider.getCapsuleStart(id)),end:world(collider.getCapsuleEnd(id)),
                radius:collider.getCapsuleRadius(id)});
        }
        return {name:bone.name,label:bone.label.replace('left ','L ').replace('right ','R '),
            mass:body.getMass(),attached:sprite.isAnimationPhysicsPartAttached(part),center:P(state.x,state.y),capsules};
    });
    const draw=port=> {
        const entries=read();
        // Two columns keep small neighboring bodies (neck/head, wrist/hand)
        // readable. Reflow labels vertically as the physical pose changes.
        for(const right of [false,true]) {
            const rows=entries.filter(e=>(e.name.startsWith('left_') || ['neck','root'].includes(e.name))===right)
                .map(e=>({entry:e,y:e.center.y})).sort((a,b)=>a.y-b.y);
            let previous=142;
            rows.forEach(row=>{row.y=Math.max(row.y,previous+22);previous=row.y;});
            let next=710;
            for(let i=rows.length-1;i>=0;i--){rows[i].y=Math.min(rows[i].y,next-22);next=rows[i].y;}
            const x=right?586:100,padding=6;
            for(const {entry:e,y} of rows) {
                const label=e.label+'  '+e.mass.toFixed(2)+' kg'+(e.attached?'':' (free)');
                const width=port.getTextWidth(label,ink.getTextSize(),ink.getTextStyle())+2*padding;
                port.drawLine(e.center,P(right?x:x+width,y),leader);
                port.drawRect(new pdg.Rect(x,y-10,x+width,y+10),background);
                port.drawText(label,P(x+padding,y+4),ink);
            }
        }
        for(const entry of entries)for(const {start:a,end:b,radius:r} of entry.capsules) {
            if(Math.hypot(b.x-a.x,b.y-a.y)<1e-6) {port.drawEllipse(a,r,r,line);continue;}
            const angle=Math.atan2(b.y-a.y,b.x-a.x),nx=-Math.sin(angle)*r,ny=Math.cos(angle)*r;
            port.drawLine(P(a.x+nx,a.y+ny),P(b.x+nx,b.y+ny),line);
            port.drawLine(P(a.x-nx,a.y-ny),P(b.x-nx,b.y-ny),line);
            // drawArc starts at twelve o'clock and increases clockwise.
            port.drawArc(a,r,r,angle+Math.PI,angle+2*Math.PI,line);
            port.drawArc(b,r,r,angle,angle+Math.PI,line);
        }
        const count=entries.reduce((sum,e)=>sum+e.capsules.length,0);
        port.drawText(count+' capsules · '+sprite.physics.getMass().toFixed(2)+' kg attached',P(100,132),ink);
    };
    return {read,draw};
}
module.exports={createCapsuleOverlay};
