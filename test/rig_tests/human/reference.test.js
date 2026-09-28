// Verify the SCML reference silhouette and joint coverage in articulated poses.
// Run from the repository root: ./test/rigs human/reference
'use strict';
const assert=require('assert');
const path=require('path');
const pdg=require('pdg');
const trace=require('../../data/human-rig/reference-trace');
const {bones,artwork,artworkAt,artworkUnitsPerCm}=require('../../data/human-rig/human');
const layer=pdg.createSpriteLayer();
try {
    const sprite=layer.createSpriteFromSpriterFile(path.resolve(__dirname,'../../data/human-rig/human.scml'));
    assert(sprite.enableAnimationPose('reference'));
    sprite.seekAnimation('reference',0); sprite.pauseAnimation();
    const expected=new Set(),actual=new Set(),width=trace.sourceSize[0];
    for(const [y,...runs] of trace.maskRuns)
        for(let i=0;i<runs.length;i+=2)for(let x=runs[i];x<runs[i+1];x++)expected.add(y*width+x);
    function rasterize(clip,time) {
        sprite.seekAnimation(clip,time);
        const actual=new Set();
        for(const bone of bones) {
            const art=artwork.find(a=>a.name===artworkAt(bone.name,clip,time));
            const artworkContours=art.contours.map(contour=> {
                const polygon=new pdg.Polygon();
                contour.forEach(([x,y])=>polygon.addPoint(new pdg.Point(x*artworkUnitsPerCm,y*artworkUnitsPerCm)));
                assert.strictEqual(polygon.getPointCount(),contour.length,bone.name+' lost traced contour vertices');
                return contour.map((_,i)=> {
                    const p=polygon.getPoint(i);
                    return [p.x/artworkUnitsPerCm,p.y/artworkUnitsPerCm];
                });
            });
            const frame=sprite.getAnimationBoneTransform(bone.name,pdg.animationSpace_Rig);
            const c=Math.cos(frame.rotation),s=Math.sin(frame.rotation),scale=trace.pixelsPerCm;
            const contours=artworkContours.map(poly=>poly.map(([x,y])=>[
                trace.origin[0]+scale*(frame.x+c*x-s*y),trace.origin[1]+scale*(frame.y+s*x+c*y)]));
            const points=contours.flat();
            const top=Math.floor(Math.min(...points.map(p=>p[1]))),bottom=Math.ceil(Math.max(...points.map(p=>p[1])));
            for(let y=top;y<bottom;y++) {
                const crossings=[];
                for(const poly of contours)for(let i=0,j=poly.length-1;i<poly.length;j=i++) {
                    const a=poly[j],b=poly[i],sample=y+.5;
                    if((a[1]>sample)!==(b[1]>sample))crossings.push(a[0]+(sample-a[1])*(b[0]-a[0])/(b[1]-a[1]));
                }
                crossings.sort((a,b)=>a-b);
                for(let i=0;i<crossings.length;i+=2)
                    for(let x=Math.ceil(crossings[i]-.5);x<Math.ceil(crossings[i+1]-.5);x++)actual.add(y*width+x);
            }
        }
        return actual;
    }
    for(const pixel of rasterize('reference',0))actual.add(pixel);
    let missed=0,extra=0;
    for(const p of expected)if(!actual.has(p))missed++;
    for(const p of actual)if(!expected.has(p))extra++;
    const iou=(expected.size-missed)/(expected.size+extra);
    console.log(JSON.stringify({sourcePixels:expected.size,missed,extra,silhouetteIoU:iou}));
    assert(iou>.995,'Reference silhouette differs from the extracted source mask by more than 0.5%');
    const poses=[['weight_shift',1.8],['weight_shift',2.7],['weight_shift',5.5],['weight_shift',6.5],
        ['wave_hello',.269],['wave_hello',.27],['wave_hello',1.1],['wave_hello',2.6],
        ['wave_hello',5.219],['wave_hello',5.22],['wave_hello',2.6,true]];
    for(const [clip,time,bothArms] of poses) {
        const modifier=bothArms ? sprite.addAnimationModifier(view=> {
            for(const part of ['upper_arm','forearm','hand']) {
                const left=view.getLocalTransform('left_'+part),right=view.getLocalTransform('right_'+part);
                right.rotation=-left.rotation;
                view.setLocalTransform('right_'+part,right);
            }
        }) : null;
        const pixels=rasterize(clip,time),label=clip+' at '+time+'s'+(bothArms?' with both arms raised':'');
        const contains=(x,y)=>pixels.has(Math.floor(y)*width+Math.floor(x));
        const scale=trace.pixelsPerCm;
        // Every joint needs a solid interior where the adjoining cutouts meet.
        for(const name of ['root','neck','head','left_upper_arm','right_upper_arm',
            'left_forearm','right_forearm','left_hand','right_hand',
            'left_shin','right_shin','left_foot','right_foot']) {
            const frame=sprite.getAnimationBoneTransform(name,pdg.animationSpace_Rig);
            const x=trace.origin[0]+frame.x*scale,y=trace.origin[1]+frame.y*scale;
            // The traced wrists are narrower than the other joint cutouts.
            const radius=name.endsWith('_hand')?2:3;
            for(let dy=-radius;dy<=radius;dy++)for(let dx=-radius;dx<=radius;dx++)
                if(dx*dx+dy*dy<=radius*radius)assert(contains(x+dx,y+dy),label+': gap at '+name);
        }
        // Keep the crotch filled below the pelvis as the thighs separate.
        const root=sprite.getAnimationBoneTransform('root',pdg.animationSpace_Rig);
        const c=Math.cos(root.rotation),s=Math.sin(root.rotation);
        for(let down=2;down<=7;down++)for(let across=-2;across<=2;across++)
            assert(contains(trace.origin[0]+root.x*scale-c*down-s*across,
                trace.origin[1]+root.y*scale-s*down+c*across),label+': tear above the crotch');
        // No body part or open-hand finger may become a detached island.
        const unseen=new Set(pixels),queue=[unseen.values().next().value];
        unseen.delete(queue[0]);
        const neighbors=[-width-1,-width,-width+1,-1,1,width-1,width,width+1];
        for(let i=0;i<queue.length;i++)for(const delta of neighbors) {
            const p=queue[i]+delta;
            if(unseen.delete(p))queue.push(p);
        }
        assert.strictEqual(unseen.size,0,label+': disconnected artwork');
        if(modifier!==null)sprite.removeAnimationModifier(modifier);
    }
    console.log('PASS: reference silhouette, joint coverage, crotch coverage, and connected cutouts in eleven articulated poses.');
} finally { pdg.cleanupLayer(layer); }
