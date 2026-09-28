// Regenerate the fixed skeleton: tools/node test/data/wheel-chains/generate.js
'use strict';
const fs=require('fs'),path=require('path');
const {radius,linkLength,linksPerChain,chainCount}=require('./rig');
const bones=[{name:'wheel',parent:-1,x:0,y:0,angle:0}];
for(let chain=0;chain<chainCount;chain++) {
    const angle=(-90+chain*120)*Math.PI/180;
    let parent=0;
    for(let link=0;link<=linksPerChain;link++) {
        bones.push({name:`chain${chain+1}_${link===linksPerChain?'weight':'link'+(link+1)}`,parent,
            x:link?linkLength:radius*Math.cos(angle),y:link?0:radius*Math.sin(angle),
            angle:link?0:Math.PI/2,chain,link});
        parent=bones.length-1;
    }
}
const infos=bones.map(b=>`    <obj_info name="${b.name}" type="bone" w="${linkLength}" h="8"/>`).join('\n');
const refs=bones.map((b,i)=>`          <bone_ref id="${i}" timeline="${i}" key="0"${b.parent<0?'':` parent="${b.parent}"`}/>`).join('\n');
// SCML uses y-up and clockwise angles are negative; PDG's layer is y-down.
const timelines=bones.map((b,i)=>`      <timeline id="${i}" name="${b.name}" object_type="bone">
        <key id="0" time="0"><bone x="${b.x}" y="${-b.y}" angle="${-b.angle*180/Math.PI}"/></key>
      </timeline>`).join('\n');
fs.writeFileSync(path.join(__dirname,'wheel.scml'),`<?xml version="1.0" encoding="UTF-8"?>
<spriter_data scml_version="1.0" generator="PDG wheel and chains fixture" generator_version="1">
  <entity id="0" name="wheel_chains">
${infos}
    <animation id="0" name="reference" length="1000" looping="true">
      <mainline><key id="0" time="0">
${refs}
      </key></mainline>
${timelines}
    </animation>
  </entity>
</spriter_data>
`);
