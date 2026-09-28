// Run: tools/node test/data/human-rig/generate.js
// Builds editable SCML and transparent PNG fallbacks from the same silhouettes
// used by the demo's retained PDG Drawings. No external packages are required.
'use strict';
const fs = require('fs');
const path = require('path');
const zlib = require('zlib');
const {bones, clips, artwork, waveHandKeys, artworkUnitsPerCm} = require('./human');
const TAU = Math.PI * 2;
const radians = degrees => degrees * Math.PI / 180;
const smooth = t => t*t*(3-2*t);
function envelope(t, keys) {
    for (let i = 1; i < keys.length; i++) {
        if (t <= keys[i][0]) {
            const [a,x] = keys[i-1], [b,y] = keys[i];
            return x + (y-x)*smooth((t-a)/(b-a));
        }
    }
    return keys[keys.length-1][1];
}
function point(frame, x, y) {
    const c = Math.cos(frame.angle), s = Math.sin(frame.angle);
    return {x:frame.x+c*x-s*y, y:frame.y+s*x+c*y};
}
const boneByName = Object.fromEntries(bones.map(bone=>[bone.name,bone]));
function pose(clip, t) {
    // The reference comes directly from the image landmarks, with no fitting
    // or procedural posture adjustment between the trace and the bind pose.
    if (clip === 'reference') return bones.map(bone=>({...bone.local}));
    const wave = clip === 'wave_hello';
    const shift = envelope(t, wave
        ? [[0,0],[.8,-2],[4.2,-2],[6,0]]
        : [[0,0],[.7,0],[1.8,-4],[2.7,-4],[3.7,0],[4.3,0],[5.5,4.5],[6.5,4.5],[8,0]]);
    const tilt = -shift*.009;
    const world = {};
    function put(name, x, y, angle) { world[name] = {x,y,angle}; return world[name]; }
    function child(name, angle) {
        const bone=boneByName[name], local=bone.local;
        const p=point(world[bone.parent],local.x,local.y);
        return put(name,p.x,p.y,angle);
    }
    const root=boneByName.root.reference;
    put('root',root.x+shift,root.y+Math.abs(shift)*.13,root.angle+tilt);
    // Lower the pelvis just enough to keep both legs reachable as weight moves.
    // Each side retains its measured length and its original planted ankle.
    for(const side of ['right','left']) {
        const upper=boneByName[side+'_thigh'], lower=boneByName[side+'_shin'];
        const ankle=boneByName[side+'_foot'].reference;
        const hip=point(world.root,upper.local.x,upper.local.y);
        const maxHeight=Math.sqrt((upper.length+lower.length)**2-(ankle.x-hip.x)**2);
        world.root.y+=Math.max(0,ankle.y-maxHeight-hip.y);
    }
    const greeting=wave ? envelope(t,[[0,0],[.65,1],[4.65,1],[5.6,0],[6,0]]) : 0;
    const high=wave ? envelope(t,[[0,0],[1.5,0],[2.4,1],[3,1],[3.8,0],[6,0]]) : 0;
    const wag=wave ? Math.sin((t-.65)*TAU*1.5)*greeting : 0;
    child('torso',boneByName.torso.reference.angle-tilt*.55);
    child('neck',boneByName.neck.reference.angle-tilt*.2);
    // Directions here follow the viewer: lean the head left during the high
    // reach, while her waving shoulder (anatomical left) rises on the right.
    child('head',boneByName.head.reference.angle+tilt*.2-radians(6)*high);
    for(const side of ['right','left']) {
        const upperArm=boneByName[side+'_upper_arm'], forearm=boneByName[side+'_forearm'];
        const hand=boneByName[side+'_hand'];
        const waving=side==='left' ? greeting : 0;
        const arm=upperArm.reference.angle+tilt*.45;
        const upper=arm+waving*(radians(40)-arm)-(side==='left' ? high*radians(80) : 0);
        const lowerRest=forearm.reference.angle+tilt*.15;
        const lower=lowerRest+waving*(radians(-83)-lowerRest)+(side==='left' ? radians(13)*wag : 0);
        const shoulder=child(upperArm.name,upper);
        if(side==='left')shoulder.y-=4*high; // centimeters, inherited by elbow and wrist
        child(forearm.name,lower);
        // During the greeting, straight means aligned with the forearm rather
        // than retaining the resting hand's bend. Use the same phase as the
        // forearm for a +/-10 degree wrist wave, easing back to rest afterward.
        child(hand.name,lower+hand.local.angle*(1-waving)+(side==='left' ? radians(10)*wag : 0));
        const thigh=boneByName[side+'_thigh'], shin=boneByName[side+'_shin'];
        const hip=point(world.root,thigh.local.x,thigh.local.y);
        const ankle=boneByName[side+'_foot'].reference;
        const dx=ankle.x-hip.x,dy=ankle.y-hip.y,distance=Math.hypot(dx,dy);
        const a=thigh.length,b=shin.length;
        if(distance>a+b+1e-6)throw Error('Unreachable planted foot');
        const along=(a*a-b*b+distance*distance)/(2*distance);
        const height=Math.sqrt(Math.max(0,a*a-along*along));
        const h=thigh.reference,k=shin.reference;
        const cross=(ankle.x-h.x)*(k.y-h.y)-(ankle.y-h.y)*(k.x-h.x);
        const bend=cross>0 ? -1 : 1;
        const knee={x:hip.x+along*dx/distance+bend*height*dy/distance,
            y:hip.y+along*dy/distance-bend*height*dx/distance};
        put(thigh.name,hip.x,hip.y,Math.atan2(knee.y-hip.y,knee.x-hip.x));
        put(shin.name,knee.x,knee.y,Math.atan2(ankle.y-knee.y,ankle.x-knee.x));
        put(side+'_foot',ankle.x,ankle.y,ankle.angle);
    }
    return bones.map(bone=> {
        const frame=world[bone.name];
        if(!bone.parent)return {...frame};
        const parent=world[bone.parent],dx=frame.x-parent.x,dy=frame.y-parent.y;
        const c=Math.cos(parent.angle),s=Math.sin(parent.angle);
        return {x:c*dx+s*dy,y:-s*dx+c*dy,angle:frame.angle-parent.angle};
    });
}

// Small deterministic supersampled PNG renderer for the SCML editor assets.
function crc32(bytes) {
    let crc = -1;
    for (const byte of bytes) {
        crc ^= byte;
        for (let bit=0; bit<8; bit++) crc = (crc>>>1) ^ ((crc&1) ? 0xedb88320 : 0);
    }
    return (crc^-1)>>>0;
}
function chunk(type, data) {
    const payload = Buffer.concat([Buffer.from(type),data]);
    const size = Buffer.alloc(4), crc = Buffer.alloc(4);
    size.writeUInt32BE(data.length); crc.writeUInt32BE(crc32(payload));
    return Buffer.concat([size,payload,crc]);
}
function png(bone) {
    const points = bone.contours.flat(), scale = artworkUnitsPerCm;
    const l = Math.floor(Math.min(...points.map(p=>p[0]))-1);
    const r = Math.ceil(Math.max(...points.map(p=>p[0]))+1);
    const top = Math.floor(Math.min(...points.map(p=>p[1]))-1);
    const bottom = Math.ceil(Math.max(...points.map(p=>p[1]))+1);
    const width = (r-l)*scale, height = (bottom-top)*scale;
    const samples = 3, coverage = new Uint8Array(width*height);
    for (let sy=0; sy<height*samples; sy++) {
        const y = top+(sy+.5)/(scale*samples), crossings = [];
        for (const contour of bone.contours) for (let i=0,j=contour.length-1; i<contour.length; j=i++) {
            const a=contour[j], b=contour[i];
            if ((a[1]>y)!==(b[1]>y)) crossings.push(a[0]+(y-a[1])*(b[0]-a[0])/(b[1]-a[1]));
        }
        crossings.sort((a,b)=>a-b);
        for (let i=0; i<crossings.length; i+=2) {
            const start=Math.max(0,Math.ceil((crossings[i]-l)*scale*samples-.5));
            const end=Math.min(width*samples,Math.ceil((crossings[i+1]-l)*scale*samples-.5));
            for (let sx=start; sx<end; sx++) coverage[Math.floor(sy/samples)*width+Math.floor(sx/samples)]++;
        }
    }
    const raw = Buffer.alloc(height*(width*4+1));
    for (let y=0; y<height; y++) for(let x=0; x<width; x++)
        raw[y*(width*4+1)+1+x*4+3] = Math.round(coverage[y*width+x]*255/(samples*samples));
    const header = Buffer.alloc(13);
    header.writeUInt32BE(width); header.writeUInt32BE(height,4); header[8]=8; header[9]=6;
    fs.writeFileSync(path.join(__dirname,'images',bone.name+'.png'),Buffer.concat([
        Buffer.from([137,80,78,71,13,10,26,10]),chunk('IHDR',header),chunk('IDAT',zlib.deflateSync(raw)),chunk('IEND',Buffer.alloc(0))]));
    return {width,height,pivotX:-l/(r-l),pivotY:bottom/(bottom-top)};
}
const number = x => Number(x.toFixed(6));
fs.mkdirSync(path.join(__dirname,'images'),{recursive:true});
const files = artwork.map(png);
const lines = ['<?xml version="1.0" encoding="UTF-8"?>',
    '<spriter_data scml_version="1.0" generator="PDG human-rig/generate.js" generator_version="1">','  <folder id="0">'];
artwork.forEach((art,i) => {
    const f=files[i];
    lines.push(`    <file id="${i}" name="images/${art.name}.png" width="${f.width}" height="${f.height}" pivot_x="${number(f.pivotX)}" pivot_y="${number(f.pivotY)}"/>`);
});
lines.push('  </folder>','  <entity id="0" name="human">');
bones.forEach(bone=>lines.push(`    <obj_info name="${bone.name}" type="bone" w="${bone.length}" h="2"/>`));
clips.forEach((clip,clipId) => {
    const count=clip.name==='reference' ? 1 : clip.seconds*24;
    // Exclude the endpoint: looping interpolates the final sample to the first.
    const times=Array.from({length:count},(_,i)=>Math.round(i*1000/24));
    if(clip.name==='wave_hello')times.push(...waveHandKeys.slice(1).map(key=>key.time*1000));
    const frameTimes=[...new Set(times)].sort((a,b)=>a-b);
    const frames=frameTimes.map(time=>pose(clip.name,time/1000));
    lines.push(`    <animation id="${clipId}" name="${clip.name}" length="${clip.seconds*1000}" looping="true">`,'      <mainline>');
    frames.forEach((frame,key)=> {
        lines.push(`        <key id="${key}" time="${frameTimes[key]}">`);
        bones.forEach(b=>lines.push(`          <bone_ref id="${b.id}" timeline="${b.id}" key="${key}"${b.parent ? ` parent="${bones.find(p=>p.name===b.parent).id}"` : ''}/>`));
        bones.forEach(b=> {
            const artKey=b.name==='left_hand'&&clip.name==='wave_hello'
                ? waveHandKeys.filter(k=>k.time*1000<=frameTimes[key]).length-1 : 0;
            lines.push(`          <object_ref id="${b.id}" timeline="${bones.length+b.id}" key="${artKey}" parent="${b.id}" z_index="${b.z}"/>`);
        });
        lines.push('        </key>');
    });
    lines.push('      </mainline>');
    bones.forEach(bone=> {
        lines.push(`      <timeline id="${bone.id}" name="${bone.name}" object_type="bone">`);
        frames.forEach((frame,key)=> {
            const f=frame[bone.id], next=frames[(key+1)%frames.length][bone.id];
            const delta = Math.atan2(Math.sin(next.angle-f.angle),Math.cos(next.angle-f.angle));
            // Spriter's positive y and angles are opposite PDG's screen axes.
            lines.push(`        <key id="${key}" time="${frameTimes[key]}" spin="${delta>0 ? -1 : 1}"><bone x="${number(f.x)}" y="${number(-f.y)}" angle="${number((-f.angle*180/Math.PI%360+360)%360)}"/></key>`);
        });
        lines.push('      </timeline>');
    });
    bones.forEach(bone=> {
        lines.push(`      <timeline id="${bones.length+bone.id}" name="${bone.name}_art" object_type="sprite">`);
        const keys=bone.name==='left_hand'&&clip.name==='wave_hello' ? waveHandKeys : [{time:0,artwork:bone.name}];
        keys.forEach((key,id)=> {
            const file=artwork.findIndex(art=>art.name===key.artwork);
            lines.push(`        <key id="${id}" time="${key.time*1000}" curve_type="instant"><object folder="0" file="${file}" x="0" y="0" scale_x="${1/artworkUnitsPerCm}" scale_y="${1/artworkUnitsPerCm}"/></key>`);
        });
        lines.push('      </timeline>');
    });
    lines.push('    </animation>');
});
lines.push('  </entity>','</spriter_data>','');
fs.writeFileSync(path.join(__dirname,'human.scml'),lines.join('\n'));
console.log(`Generated human.scml: ${bones.length} bones, ${artwork.length} silhouette assets, reference / weight_shift / wave_hello.`);
