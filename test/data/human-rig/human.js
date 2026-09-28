// The stationary reference silhouette is traced in original image coordinates.
// Convert each piece to its bone frame, retaining the original asymmetry and
// clothing contours. Bone-local +x runs from the proximal joint toward the tip.
'use strict';
const trace = require('./reference-trace');
const cm = 1/trace.pixelsPerCm;
// Drawing geometry uses millimeters; PNGs use one pixel per millimeter.
// Convert to rig centimeters with a drawing transform.
const artworkUnitsPerCm = 10;
// Demo mass profile; true swaps torso/pelvis masses, retaining capsule sizes.
const femaleRig = true;
function localContours(part) {
    const [x,y]=part.joint,angle=Math.atan2(part.tip[1]-y,part.tip[0]-x);
    const c=Math.cos(angle),s=Math.sin(angle);
    return part.contours.map(polygon=>polygon.map(([px,py])=>[
        (c*(px-x)+s*(py-y))*cm,(-s*(px-x)+c*(py-y))*cm]));
}
const bones = trace.parts.map((part,id)=> {
    const [x,y]=part.joint;
    const angle=Math.atan2(part.tip[1]-y,part.tip[0]-x);
    return {
        name:part.name, id, parent:part.parent, z:part.z,
        label:part.name==='root'?'pelvis':part.name.replace(/_/g,' '),
        length:Math.hypot(part.tip[0]-x,part.tip[1]-y)*cm,
        reference:{x:(x-trace.origin[0])*cm,y:(y-trace.origin[1])*cm,angle},
        contours:localContours(part)
    };
});
for(const bone of bones) {
    const frame=bone.reference;
    if(!bone.parent) { bone.local={...frame}; continue; }
    const parent=bones.find(b=>b.name===bone.parent).reference;
    const c=Math.cos(parent.angle),s=Math.sin(parent.angle),dx=frame.x-parent.x,dy=frame.y-parent.y;
    bone.local={x:c*dx+s*dy,y:-s*dx+c*dy,angle:frame.angle-parent.angle};
}
const clips=[{name:'reference',seconds:1},{name:'weight_shift',seconds:8},{name:'wave_hello',seconds:6}];
const artwork=bones.map(b=>({name:b.name,bone:b.name,contours:b.contours})).concat(
    trace.variants.map(part=>({name:part.name,bone:part.bone,contours:localContours(part)})));
const twistedHand=require('./hand-twist-art').contours(trace.pixelsPerCm,trace.extraction.wristInsetCm);
for(const side of ['left','right'])artwork.push({name:side+'_hand_twisted',bone:side+'_hand',
    contours:twistedHand.map(contour=>contour.map(([x,y])=>[x,side==='left'?y:-y]))});
// Pull alternate hand artwork toward the wrist along bone-local -x (cm).
const handArtworkInsetCm={left_hand_open:1,left_hand_twisted:2,right_hand_twisted:2};
for(const art of artwork) {
    const inset=handArtworkInsetCm[art.name];
    if(inset)art.contours=art.contours.map(contour=>contour.map(([x,y])=>[x-inset,y]));
}
const waveHandKeys=[{time:0,artwork:'left_hand'},{time:.27,artwork:'left_hand_open'},
    {time:5.22,artwork:'left_hand'}];
function artworkAt(bone,clip,time) {
    if(bone!=='left_hand'||clip!=='wave_hello')return bone;
    // PDG's progress is a float, while authored SCML times are milliseconds.
    const milliseconds=Math.round(time*1000);
    return waveHandKeys.filter(key=>key.time*1000<=milliseconds).slice(-1)[0].artwork;
}
module.exports={bones,clips,artwork,waveHandKeys,artworkAt,pixelsPerCm:trace.pixelsPerCm,artworkUnitsPerCm,femaleRig};
