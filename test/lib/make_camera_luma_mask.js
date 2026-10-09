// Recreate the visual transition mask: tools/node test/lib/make_camera_luma_mask.js
'use strict';
const fs=require('fs'),path=require('path'),zlib=require('zlib');
const width=960,height=640;
function noise(x,y) {
    const ix=Math.floor(x),iy=Math.floor(y),fx=x-ix,fy=y-iy;
    const smooth=t=>t*t*(3-2*t);
    const hash=(a,b)=>{let n=Math.imul(a+19,374761393)^Math.imul(b+37,668265263);n=Math.imul(n^(n>>>13),1274126177);return ((n^(n>>>16))>>>0)/4294967295;};
    const sx=smooth(fx),sy=smooth(fy);
    const top=hash(ix,iy)*(1-sx)+hash(ix+1,iy)*sx;
    const bottom=hash(ix,iy+1)*(1-sx)+hash(ix+1,iy+1)*sx;
    return top*(1-sy)+bottom*sy;
}
const values=new Float32Array(width*height),histogram=new Uint32Array(4096);
for(let y=0;y<height;++y)for(let x=0;x<width;++x){
    const u=x/width,v=y/height;
    const value=.55*noise(u*4,v*3)+.25*noise(u*8,v*6)+.13*noise(u*16,v*12)+.07*noise(u*32,v*24);
    const index=y*width+x;values[index]=value;++histogram[Math.min(4095,Math.floor(value*4096))];
}
// Evenly distribute linear luminance so the reveal uses the whole duration.
const ranks=new Float32Array(4096);let count=0;
for(let i=0;i<4096;++i){ranks[i]=(count+histogram[i]/2)/values.length;count+=histogram[i];}
const pixels=Buffer.alloc((width*4+1)*height);
for(let y=0;y<height;++y)for(let x=0;x<width;++x){
    const luma=ranks[Math.min(4095,Math.floor(values[y*width+x]*4096))];
    const encoded=luma<=.0031308?12.92*luma:1.055*Math.pow(luma,1/2.4)-.055;
    const color=Math.round(encoded*255),offset=y*(width*4+1)+1+x*4;
    pixels[offset]=pixels[offset+1]=pixels[offset+2]=color;pixels[offset+3]=255;
}
function crc32(buffer){let crc=0xffffffff;for(const byte of buffer){crc^=byte;for(let i=0;i<8;++i)crc=(crc>>>1)^((crc&1)?0xedb88320:0);}return (crc^0xffffffff)>>>0;}
function chunk(type,data){const name=Buffer.from(type),length=Buffer.alloc(4),crc=Buffer.alloc(4);length.writeUInt32BE(data.length);crc.writeUInt32BE(crc32(Buffer.concat([name,data])));return Buffer.concat([length,name,data,crc]);}
const header=Buffer.alloc(13);header.writeUInt32BE(width);header.writeUInt32BE(height,4);header[8]=8;header[9]=6;
const output=path.resolve(__dirname,'../data/camera-luma-mask.png');
fs.writeFileSync(output,Buffer.concat([Buffer.from([137,80,78,71,13,10,26,10]),chunk('IHDR',header),chunk('IDAT',zlib.deflateSync(pixels)),chunk('IEND',Buffer.alloc(0))]));
console.log('Generated '+output);
