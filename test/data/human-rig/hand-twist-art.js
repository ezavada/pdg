// Bone-local silhouette for the supplied semi-open, thumb-out hand reference.
// This is a drawing variant, not a change to the physical wrist or capsule.
'use strict';
const outline=[
    [25,65],[25,59],[19,54],[14,48],[10,41],[7,34],[7,30],[8,28],
    [10,29],[14,35],[12,29],[9,21],[9,18],[11,17],[13,20],[18,31],
    [15,23],[12,17],[12,15],[14,14],[16,17],[22,30],
    [19,22],[17,16],[17,13],[19,12],[21,15],[26,28],[28,36],
    [30,36],[33,31],[35,28],[37,27],[38,29],[36,33],[34,38],
    [34,43],[32,49],[31,54],[33,60],[34,65]
];
function contours(pixelsPerCm,wristInsetCm=0) {
    const angle=Math.atan2(13-60,19-29),c=Math.cos(angle),s=Math.sin(angle);
    const shape=outline.map(([x,y])=>[c*(x-29)+s*(y-60)+wristInsetCm*pixelsPerCm,
        -s*(x-29)+c*(y-60)]);
    if(wristInsetCm>0) {
        // Carry the short forearm section with the hand after raising the
        // wrist pivot. Round its new proximal end to overlap the forearm.
        const low=shape[0][1],high=shape.at(-1)[1],center=(low+high)/2,radius=(high-low)/2;
        shape.push([0,high],[-radius*.707,center+radius*.707],[-radius,center],
            [-radius*.707,center-radius*.707],[0,low]);
    }
    // Smooth the traced edge, retaining at least 1.1 reference pixels between
    // samples so millimeter-space PDG polygons preserve the contour vertices.
    const points=[];
    for(let i=0;i<shape.length;i++) {
        const a=shape[(i+shape.length-1)%shape.length],b=shape[i];
        const c=shape[(i+1)%shape.length],d=shape[(i+2)%shape.length];
        for(let j=0;j<12;j++) {
            const t=j/12;
            const p=b.map((v,k)=>.5*(2*v+(-a[k]+c[k])*t+(2*a[k]-5*v+4*c[k]-d[k])*t*t+(-a[k]+3*v-3*c[k]+d[k])*t*t*t));
            if(!points.length || Math.hypot(p[0]-points.at(-1)[0],p[1]-points.at(-1)[1])>=1.1)points.push(p);
        }
    }
    while(Math.hypot(points.at(-1)[0]-points[0][0],points.at(-1)[1]-points[0][1])<1.1)points.pop();
    return [points.map(([x,y])=>[x/pixelsPerCm,y/pixelsPerCm])];
}
module.exports={contours};
