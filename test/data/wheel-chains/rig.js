// Centimeter geometry, kilogram masses. The wheel is the only animated body.
'use strict';
const radius=50,linkLength=35,linksPerChain=4,chainCount=3;
const colors=['#eea34a','#55bbc4','#ae91df'];
function createWheelRig(pdg,layer,location,rootMode=pdg.animationRoot_Follow) {
    const sprite=layer.createSpriteFromSpriterFile(process.cwd()+'/data/wheel-chains/wheel.scml');
    if(!sprite || !sprite.enableAnimationPose('reference'))throw Error('Could not load wheel skeleton');
    sprite.pauseAnimation();sprite.setLocation(location);
    const bodies=[{bone:'wheel',mode:pdg.animationBody_Kinematic,mass:12,length:0,radius}],joints=[],links=[];
    for(let chain=0;chain<chainCount;chain++)for(let link=0;link<=linksPerChain;link++) {
        const weight=link===linksPerChain,name=`chain${chain+1}_${weight?'weight':'link'+(link+1)}`;
        const index=bodies.length,parent=link?index-1:0;
        const angle=(-90+chain*120)*Math.PI/180;
        bodies.push({bone:name,mass:weight?2:.5,length:weight?0:linkLength,radius:weight?10:4,
            offsetX:weight?0:linkLength/2,friction:.7,elasticity:0});
        joints.push({parent,child:index,parentX:link?linkLength/2:radius*Math.cos(angle),
            parentY:link?0:radius*Math.sin(angle),childX:weight?0:-linkLength/2,
            minAngle:-1e9,maxAngle:1e9});
        links.push({name,chain,link,weight,parent:link?bodies[parent].bone:'wheel'});
    }
    sprite.setupAnimationPhysics({version:1,rootMode,bodies,joints,selfCollisions:false});
    for(const body of bodies) {
        const part=sprite.findPart(body.bone);
        part.collider.setCategory(1).setCollisionMask(2).setRestitution(0);
        part.physics.setAngularDamping(.15);
        if(body.length===0)part.physics.setMomentOfInertia(body.mass*body.radius*body.radius/2);
    }
    const wheel=sprite.findPart('wheel').physics;
    const members=bodies.map(b=>sprite.findPart(b.bone).physics);
    const pivots=joints.map(j=>{
        const body=members[j.child];
        for(let i=0;i<body.getConstraintCount();i++) {
            const joint=body.getConstraint(i);
            if(joint.getType()===pdg.constraint_Pivot && joint.getBodyA()===members[j.parent])return joint;
        }
        throw Error('Missing chain pivot');
    });
    const point=(x,y)=>new pdg.Point(x,y);
    const toWorld=(body,p)=> {
        const s=body.getState(),c=Math.cos(s.rotation),n=Math.sin(s.rotation);
        return {x:s.x+c*p.x-n*p.y,y:s.y+n*p.x+c*p.y};
    };
    return {sprite,wheel,links,bodies,members,radius,linkLength,
        jointErrors() {
            return joints.map((j,i)=>{
                const a=toWorld(members[j.parent],pivots[i].getAnchorA());
                const b=toWorld(members[j.child],pivots[i].getAnchorB());
                return {bone:bodies[j.child].bone,error:Math.hypot(a.x-b.x,a.y-b.y),a,b};
            });
        },
        jointError() {return Math.max(...this.jointErrors().map(j=>j.error));},
        extension() {
            const center=wheel.getState();
            return links.filter(link=>link.weight).reduce((sum,link)=>{
                const p=sprite.findPart(link.name).physics.getState();
                return sum+Math.hypot(p.x-center.x,p.y-center.y);
            },0)/chainCount;
        },
        addArtwork() {
            const fill=color=>new pdg.Attributes().fillColor(color);
            const stroke=(color,width)=>new pdg.Attributes().lineColor(color).lineThickness(width);
            const wheelArt=pdg.createDrawing();
            wheelArt.addEllipse(point(0,0),radius,radius,fill('#263d50'));
            wheelArt.addEllipse(point(0,0),radius-7,radius-7,stroke('#7694a5',3));
            for(let chain=0;chain<chainCount;chain++) {
                const a=(-90+chain*120)*Math.PI/180,c=Math.cos(a),s=Math.sin(a);
                const spoke=new pdg.Polygon();
                for(const [x,y] of [[0,-2.5],[radius,-2.5],[radius,2.5],[0,2.5]])
                    spoke.addPoint(point(c*x-s*y,s*x+c*y));
                wheelArt.addPolygon(spoke,fill(colors[chain]));
            }
            wheelArt.addEllipse(point(0,0),9,9,fill('#dfe9ef'));
            sprite.addAnimationDrawable(wheelArt,{bone:'wheel'});
            for(const link of links) {
                const drawing=pdg.createDrawing(),color=colors[link.chain];
                if(link.weight)drawing.addEllipse(point(0,0),10,10,fill(color));
                else {
                    // Filled geometry stays legible on WebGL implementations
                    // whose native line width is restricted to one pixel.
                    drawing.addRect(new pdg.Rect(0,-4,linkLength,4),fill(color).roundedCorners(4));
                    drawing.addEllipse(point(0,0),4,4,fill('#263d50'));
                    drawing.addEllipse(point(linkLength,0),4,4,fill('#263d50'));
                }
                sprite.addAnimationDrawable(drawing,{bone:link.name});
            }
        }
    };
}
module.exports={createWheelRig,radius,linkLength,linksPerChain,chainCount};
