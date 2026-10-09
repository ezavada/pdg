// From test/: ./pdg ui_tests/animation_physics_test.js --wait
// Omit --wait to check clips, IK, physics controls, fast tilt and held posing.
// Browser: test/ui.html?test=animation-physics
const {bones, clips, artwork, artworkAt, pixelsPerCm, artworkUnitsPerCm} = require('../data/human-rig/human');
const {GroundMotion,plantFeet,sweepSeconds,fastSweepSeconds} = require('../data/human-rig/ground');
const {createArmBlocker,totalMass,handLoadKg,armNames} = require('../data/human-rig/arm-blocker');
const {createRagdoll,platformHalfWidth,platformDepth} = require('../data/human-rig/ragdoll');
const {createPushes} = require('../data/human-rig/pushes');
const {createHandControl} = require('../data/human-rig/hand-control');
const {createMembership} = require('../data/human-rig/membership');
const {createCapsuleOverlay} = require('../data/human-rig/capsule-overlay');
const {createPoseControl} = require('../data/human-rig/pose-control');
const interactive = !!pdg.visualTestSession || process.argv.indexOf('--wait') >= 0;
const P = (x,y) => new pdg.Point(x,y);
const R = (l,t,r,b) => new pdg.Rect(l,t,r,b);
const fill = color => new pdg.Attributes().fillColor(color);
const stroke = color => new pdg.Attributes().lineColor(color).lineThickness(1);
const port = pdg.gfx.createWindowPort(new pdg.Rect(1180,800), 'PDG - Human animation rig');
pdg.gfx.setTargetFPS(60);
const layer = pdg.createSpriteLayer(port);
layer.setUseChipmunkPhysics(true);
// Match the reference image's native pixel scale for direct outline comparison.
const scale = pixelsPerCm, origin = P(422,668);
const sprite = layer.createSpriteFromSpriterFile(process.cwd()+'/data/human-rig/human.scml');
let clip = clips[1], paused = false, showBones = false, hover = null, scrubbing = false, finished = false;
let checkStarted = 0, lastCheck = -1, clipIndex = 0;
let handCheckIndex = -1;
let ground, groundPreview=false;
let blocker, blockerCheck=-1, blockedHandY=0;
let ragdoll,ragdollCheck=-1;
let pushes,pushCheck=-1;
let handControl,controlCheck=-1,limpStartAngle=0,limpMaxRotation=0,dragStart=null;
let capsuleOverlay,showCapsules=false,membership;
let poseControl,poseCheck=-1,posePoint;
const groundMotion=new GroundMotion();
const groundChecks=[-10,-5,0,5,10,5,0,-5,-10];
const handChecks = [
    ['wave_hello',.269,'left_hand'],['wave_hello',.270,'left_hand_open'],
    ['wave_hello',5.219,'left_hand_open'],['wave_hello',5.220,'left_hand'],
    ['wave_hello',.270,'left_hand_open'],['wave_hello',.269,'left_hand'],
    ['reference',0,'left_hand'],['wave_hello',2.6,'left_hand_open'],
    ['weight_shift',0,'left_hand']
];
const buttons = [], drawings = [];
const stats = {frames:0, steps:0, bones:0, drawings:0, handArtwork:'left_hand', error:null, maxFootDrift:0, maxHandLift:0, hipTravel:0, groundChecks:0, blockerChecks:0, maxArmJointGap:0,ragdollChecks:0,recoveryEvents:0,pushChecks:0,handChecks:0,fastTiltChecks:0};
// Use the same elapsed time as animation/physics. Background browser tabs and
// delayed frames can advance the wall clock while the engine limits catch-up.
// Recovery deadlines and clip checks must not run ahead of the simulation.
let simulationSeconds = 0;
const simulationClock = layer.createSprite();
simulationClock.addAnimationHelper(new pdg.IAnimationHelper((owner, seconds) => {
    simulationSeconds += seconds;
    return true;
}));
const now = () => simulationSeconds;
function check(ok,message) { if (!ok) throw Error(message); }
function text(message,x,y,size=16,color='#202934') {
    port.drawText(message,P(x,y),fill(color).textSize(size));
}
function selectClip(name) {
    if(!canEditClip())return;
    clip = clips.find(c=>c.name===name);
    sprite.startAnimation(name);
    if (paused) sprite.pauseAnimation();
}
function togglePause() {
    if(!canEditClip())return;
    paused = !paused;
    if (paused) sprite.pauseAnimation(); else sprite.resumeAnimation();
}
function setBones(enabled) {
    showBones = enabled;
    sprite.setAnimationDebugDraw(enabled ? pdg.animationDebug_Bones : pdg.animationDebug_None);
}
function setCapsules(enabled) {showCapsules=!!enabled;}
function seek(seconds) {
    if(!canEditClip())return;
    sprite.seekAnimation(clip.name,Math.max(0,Math.min(clip.seconds-.001,seconds)));
    paused = true;
    sprite.pauseAnimation();
}
function toggleGround(fast=false) {
    if(poseBusy())return;
    const duration=fast?fastSweepSeconds:sweepSeconds;
    const enabled=!groundMotion.tilting || groundMotion.sweepSeconds!==duration;
    groundMotion.setTilting(enabled,now(),ground.angle,duration);
    groundPreview=false;
}
// Hold a slope for deterministic inspection, independently of the clip time.
function setGroundAngle(radians) {
    groundPreview=true;
    ground.setAngle(radians);
}
function toggleBlocker() {
    if(poseBusy())return;
    if(ragdoll && ragdoll.mode!=='standing')return;
    if(!blocker.enabled) {
        handControl.release();
        selectClip('wave_hello');
        paused=false; sprite.resumeAnimation();
    }
    blocker.setEnabled(!blocker.enabled);
}
function dropRig() {
    if(poseBusy())return;
    if(handControl)handControl.release();
    if(pushes)pushes.cancel();
    paused=true;ragdoll.drop();
}
function recoverRig() {
    if(poseBusy())return;
    if(handControl)handControl.release();
    if(pushes)pushes.cancel();
    clip=clips[0];paused=true;ragdoll.recover();
}
function pushShoulder(kind) {
    if(!canPush())return;
    handControl.release();
    if(pushes.push(kind))paused=true;
}
function toggleLimpHand() {
    if(poseBusy())return;
    if(!handControl.canStart() || (pushes && pushes.phase))return;
    if(handControl.mode==='animation' && clip.name!=='wave_hello') {
        selectClip('wave_hello');paused=false;sprite.resumeAnimation();
    }
    handControl.toggleLimp();
}
function button(label,x,y,width,action,active,enabled=()=>true) {
    buttons.push({label,bounds:R(x,y,x+width,y+40),action,active,enabled});
}
function toggleArm() {if(canEditMembership())membership.toggleArm();}
function toggleWeight() {if(canEditMembership())membership.toggleWeight();}
const poseBusy=()=>poseControl && poseControl.mode!=='off';
const canPose=()=>poseControl && ragdoll.mode==='standing' && !pushes.phase && !membership.armDetached && !membership.holdingWeight;
const canEditMembership=()=>!poseBusy() && membership && ragdoll.mode==='standing' && !pushes.phase && handControl.mode==='animation';
const canEditClip=()=>!poseBusy() && !(pushes && pushes.phase) && (!ragdoll || ragdoll.mode!=='recovering');
function togglePose() {
    if(poseControl.mode==='posing') {
        poseControl.finish();clip=clips[1];paused=false;
    } else if(poseControl.mode==='off' && canPose()) {
        handControl.release();blocker.setEnabled(false);blocker.driven=false;
        groundMotion.setTilting(false,now(),ground.angle);groundPreview=true;
        scrubbing=false;poseControl.enter();paused=true;
    }
}
function restart() {
    if(poseControl.mode==='posing'){poseControl.reset();clip=clips[0];paused=true;}
    else selectClip(clip.name);
}
button(()=>poseBusy()?'Return to animation [P]':'Pose me [P]',826,60,302,togglePose,poseBusy,
    ()=>poseControl && poseControl.mode==='posing' || (!poseBusy() && canPose()));
button(()=>showCapsules?'Hide capsules + masses  [C]':'Show capsules + masses  [C]',826,124,302,
    ()=>setCapsules(!showCapsules),()=>showCapsules);
button('Weight shift [1]',826,172,146,()=>selectClip('weight_shift'),()=>clip.name==='weight_shift',canEditClip);
button('Wave hello [2]',982,172,146,()=>selectClip('wave_hello'),()=>clip.name==='wave_hello',canEditClip);
button('Reference [3]',826,220,146,()=>selectClip('reference'),()=>clip.name==='reference',canEditClip);
button(()=>pdg.visualTestSession ? (paused?'Play clip':'Pause clip') : (paused?'Play [Space]':'Pause [Space]'),982,220,146,togglePause,undefined,canEditClip);
button(()=>poseBusy()?'Reset pose [R]':'Restart [R]',826,268,146,restart,undefined,()=>canEditClip() || poseControl.mode==='posing');
button(()=>showBones?'Hide bones [B]':'Show bones [B]',982,268,146,()=>setBones(!showBones),()=>showBones);
button(()=>poseBusy()?'Flip selected elbow [X]':handControl && handControl.mode==='limp'?'Restore waving hand [L]':'Limp waving hand [L]',826,316,302,
    ()=>poseBusy()?poseControl.flipElbow():toggleLimpHand(),()=>!poseBusy() && handControl && handControl.mode==='limp',
    ()=>poseBusy()?poseControl.mode==='posing' && /_hand$/.test(poseControl.selected):handControl && handControl.canStart() && !(pushes && pushes.phase));
const tiltingFast=()=>groundMotion.tilting && groundMotion.sweepSeconds===fastSweepSeconds;
const tiltingSlow=()=>groundMotion.tilting && groundMotion.sweepSeconds===sweepSeconds;
const canRotatePose=()=>poseControl.mode==='posing' && /_(hand|foot)$/.test(poseControl.selected);
button(()=>poseBusy()?'Rotate −  [':tiltingSlow()?'Level [G]':'Slow tilt [G]',826,364,146,
    ()=>poseBusy()?poseControl.rotateSelected(-5):toggleGround(false),()=>!poseBusy() && tiltingSlow(),()=>!poseBusy() || canRotatePose());
button(()=>poseBusy()?'Rotate +  ]':tiltingFast()?'Level [F]':'Fast tilt [F]',982,364,146,
    ()=>poseBusy()?poseControl.rotateSelected(5):toggleGround(true),()=>!poseBusy() && tiltingFast(),()=>!poseBusy() || canRotatePose());
button(()=>blocker.enabled?'Remove arm blocker [O]':'Block waving arm [O]',826,412,302,toggleBlocker,()=>blocker.enabled,()=>!poseBusy() && ragdoll.mode==='standing');
button('Ragdoll [D]',826,460,146,dropRig,()=>ragdoll.mode==='ragdoll',()=>!poseBusy());
button('Recover [U]',982,460,146,recoverRig,()=>ragdoll.mode==='recovering',()=>!poseBusy() && (ragdoll.mode==='ragdoll'||(ragdoll.mode==='standing'&&(blocker.driven||handControl.mode!=='animation'||membership.holdingWeight))));
const canPush=()=>!poseBusy() && ragdoll && ragdoll.mode==='standing' && pushes && !pushes.phase;
button('Soft push [S]',826,508,146,()=>pushShoulder('soft'),()=>pushes && pushes.phase && pushes.kind==='soft',canPush);
button('Hard push [H]',982,508,146,()=>pushShoulder('hard'),()=>pushes && pushes.phase && pushes.kind==='hard',canPush);
button(()=>membership && membership.armDetached?'Restore right elbow [E]':'Detach right elbow [E]',826,556,302,toggleArm,
    ()=>membership && membership.armDetached,canEditMembership);
button(()=>membership && membership.holdingWeight?'Drop 10 kg dumbbell [W]':'Hold 10 kg dumbbell [W]',826,604,302,toggleWeight,
    ()=>membership && membership.holdingWeight,()=>canEditMembership() && (!membership.armDetached || membership.holdingWeight));
const scrub = R(64,730,742,756);
function scrubAt(p) { seek((p.x-scrub.left)/(scrub.right-scrub.left)*clip.seconds); }
function inside(p,r) { return p && p.x>=r.left && p.x<=r.right && p.y>=r.top && p.y<=r.bottom; }
function buttonAt(p) { return buttons.find(b=>b.enabled()&&inside(p,b.bounds)); }
function drawPoseHandles() {
    const state=poseControl.getState();
    for(const h of state.handles) {
        const selected=h.name===state.selected,target=state.targets.find(t=>t.name===h.name);
        const limited=target && target.error>.2,color=limited?'#b97925':selected?'#137fab':'#5396ad';
        const p=P(h.point.x,h.point.y);
        port.drawEllipse(p,10,10,fill('#fbfbfa'));
        port.drawEllipse(p,10,10,stroke(color).lineThickness(selected?3:2));
        port.drawEllipse(p,2,2,fill(color));
        if(limited && target.target) {
            const t=P(origin.x+target.target.x*scale,origin.y+target.target.y*scale);
            // Keep an unreachable pointer target inside the figure panel.
            t.x=Math.max(45,Math.min(755,t.x));t.y=Math.max(120,Math.min(695,t.y));
            port.drawLine(p,t,stroke(color));port.drawEllipse(t,4,4,stroke(color));
        }
        const label=h.label,ink=fill(color).textSize(11),pad=5;
        const width=port.getTextWidth(label,ink.getTextSize(),ink.getTextStyle())+2*pad;
        const x=Math.max(85,Math.min(755-width,p.x+15)),y=Math.max(130,Math.min(690,p.y));
        port.drawRect(R(x,y-11,x+width,y+8),fill('#f2f7f8').roundedCorners(3));
        port.drawText(label,P(x+pad,y+3),ink);
    }
}

layer.onPreAnimateLayer(()=> {
    if(finished || !ground)return false;
    try {
        if(!groundPreview)ground.setAngle(groundMotion.sample(now()));
        if(poseControl)poseControl.update();
        if(pushes)pushes.update();
        if(membership)membership.update();
        if(ragdoll) {
            ragdoll.updateGround();
            if(pushes && pushes.phase==='recovering' && ragdoll.phase!=='blending'){clip=clips[0];paused=true;}
            if(ragdoll.phase==='blending'){clip=clips[1];paused=false;}
        }
    }
    catch(error) { fail(error); }
    return false;
});
layer.onErasePort(()=> {
    port.drawRect(port.getDrawingArea(),fill('#eef0f2'));
    port.drawRect(R(32,108,774,720),fill('#fbfbfa').roundedCorners(10));
    port.drawRect(R(800,108,1152,788),fill('#ffffff').roundedCorners(10));
    if(pushes) {
        const r=pushes.bounds;
        port.drawRect(R(r.left,Math.max(116,r.top),r.right,700),fill('#9aa7ae'));
        for(let y=130;y<690;y+=22)port.drawLine(P(r.left+3,y),P(r.right-3,y+12),stroke('#dfe5e8'));
        text('WALL',r.left-3,108,11,'#67727d');
    }
    if(blocker && blocker.enabled) {
        const r=blocker.bounds,touching=blocker.isTouching();
        port.drawRect(r,fill(touching?'#c66e32':'#8797a0').roundedCorners(3));
        for(let x=r.left+8;x<r.right-8;x+=16)
            port.drawLine(P(x,r.top+3),P(x+9,r.bottom-3),stroke('#ffffff'));
        text('ARM BLOCKER',r.left+8,r.top-10,11,'#67727d');
    }
    const angle=ground ? ground.angle : 0;
    // The physical floor extends beyond the viewport. Show the part inside
    // the figure panel without drawing over the controls or timeline.
    const dx=platformHalfWidth*Math.cos(angle),dy=platformHalfWidth*Math.sin(angle);
    const nx=-Math.sin(angle)*platformDepth/2,ny=Math.cos(angle)*platformDepth/2;
    const floorLine=(x,y,attributes)=> {
        let low=-1,high=1;
        for(const [p,d,min,max] of [[x,dx,40,766],[y,dy,116,700]])if(Math.abs(d)>1e-8) {
            const a=(min-p)/d,b=(max-p)/d;low=Math.max(low,Math.min(a,b));high=Math.min(high,Math.max(a,b));
        }
        if(low<high)port.drawLine(P(x+low*dx,y+low*dy),P(x+high*dx,y+high*dy),attributes);
    };
    floorLine(origin.x+nx,origin.y+ny,stroke('#dce3e7').lineThickness(platformDepth));
    floorLine(origin.x,origin.y,stroke('#526c7d').lineThickness(3));
    port.drawLine(P(origin.x,origin.y+5),P(origin.x,origin.y+18),stroke('#a0abb3'));
    // A quiet height ruler makes the adult proportions easy to inspect.
    for(let cm=0; cm<=160; cm+=20) {
        const y=origin.y-cm*scale;
        port.drawLine(P(70,y),P(80,y),stroke('#c4cbd0'));
        text(String(cm),42,y+4,11,'#8c959d');
    }
    text('cm',46,138,11,'#8c959d');
    return true;
});
layer.onPostDrawLayer(()=> {
    if (finished) return false;
    try {
        stats.frames++;
        membership.draw(port);
        if(showCapsules)capsuleOverlay.draw(port);
        if(showBones && ground.enabled && ragdoll.mode!=='ragdoll')for(const leg of ground.legs) {
            const x=origin.x+leg.target.x*scale,y=origin.y+leg.target.y*scale;
            port.drawLine(P(x-5,y),P(x+5,y),stroke('#db8a26'));
            port.drawLine(P(x,y-5),P(x,y+5),stroke('#db8a26'));
        }
        if(blocker.isTouching() && blocker.point)
            port.drawEllipse(P(blocker.point.x,blocker.point.y),4,4,fill('#efb047'));
        if(interactive && !poseBusy() && ragdoll.mode==='standing') {
            const p=handControl.getPoint(),color=handControl.mode==='limp'?'#cb8b32':'#398ec4';
            port.drawEllipse(P(p.x,p.y),12,12,stroke(color));
            if(handControl.target) {
                const t=handControl.target;
                port.drawLine(P(p.x,p.y),P(t.x,t.y),stroke(color));
                port.drawEllipse(P(t.x,t.y),5,5,stroke(color).lineThickness(2));
            }
        }
        if(poseControl.mode==='posing')drawPoseHandles();
        if(pushes.point && now()-pushes.started<.8) {
            const p=pushes.point,ink=stroke(pushes.kind==='hard'?'#b45d3c':'#398ec4').lineThickness(3);
            port.drawLine(P(p.x-65,p.y),P(p.x-5,p.y),ink);
            port.drawLine(P(p.x-5,p.y),P(p.x-17,p.y-7),ink);
            port.drawLine(P(p.x-5,p.y),P(p.x-17,p.y+7),ink);
            text(pushes.kind==='hard'?'HARD PUSH':'SOFT PUSH',p.x-75,p.y-15,11,'#67727d');
        }
        if(showBones && ragdoll.mode==='recovering') {
            const top=ragdoll.getLiftPoint();
            port.drawEllipse(P(top.x,top.y),5,5,stroke('#398ec4').lineThickness(2));
        }
        text('Human animation rig',34,52,30);
        text(poseBusy()?(poseControl.mode==='posing'?'Pose me · drag a handle, then release to hold':'Returning your pose to weight shifting'):ragdoll.mode==='ragdoll'?'Whole-body physics · '+sprite.physics.getMass().toFixed(2)+' kg on a moving platform':ragdoll.phase==='lifting'?'Lifting from the upper torso · limbs hanging freely':ragdoll.phase==='posing'?'Joint drives restoring the standing pose':ragdoll.phase==='lowering'?'Settling onto the floor before returning to animation':ragdoll.phase==='blending'?'Returning to weight shift · physical pose influence fading':'Weight, balance, and a hello · feet planted with IK',35,80,15,'#67727d');
        text('Ground: '+(ground.angle*180/Math.PI).toFixed(1)+'° · '+groundMotion.sweepSeconds+' s each way',826,681,13,'#67727d');
        text(poseBusy()?'Selected: '+(poseControl.selected||'none').replace(/_/g,' '):handControl.mode==='dragging'?'Hand: following your drag':handControl.mode==='limp'?'Hand: limp · arm follows animation':handControl.mode==='recovering'?'Hand: returning to animation':blocker.isTouching()?'Arm: pushing against blocker':blocker.driven?'Arm: following animation with physics':ragdoll.mode==='standing'?'Arm: following animation':'Arm: whole-body physics',826,698,14);
        text(poseBusy()?'Hands / feet hold their placed targets':ragdoll.phase==='lifting'?'Recovery: lifting torso':ragdoll.phase==='posing'?'Recovery: restoring pose':ragdoll.phase==='lowering'?'Recovery: lowering to the floor':ragdoll.phase==='blending'?'Recovery: blending to weight shift':ragdoll.mode==='ragdoll'?'Body: ragdoll':ragdoll.hasRecovered?'Recovery complete · feet planted':'Body: animation + IK',826,723,14);
        text(sprite.physics.getMass().toFixed(2)+' kg attached · '+handLoadKg+' kg lift target',826,747,13,'#67727d');
        text('ESC  close',826,774,12,'#85909b');
        buttons.forEach(b=> {
            const enabled=b.enabled(),selected=b.active && b.active();
            port.drawRect(b.bounds,fill(selected?'#263a47':!enabled?'#f4f5f6':hover===b?'#e1e7eb':'#edf1f3').roundedCorners(6));
            text(typeof b.label==='function'?b.label():b.label,b.bounds.left+14,b.bounds.top+26,15,selected?'#ffffff':enabled?'#263a47':'#9ca6ae');
        });
        const progress=sprite.getAnimationProgress();
        text(clip.name.replace(/_/g,' '),64,717,14);
        text((progress*clip.seconds).toFixed(2)+' / '+clip.seconds.toFixed(2)+' s',619,717,13,'#67727d');
        port.drawRect(R(scrub.left,740,scrub.right,744),fill('#cfd7dc').roundedCorners(2));
        port.drawRect(R(scrub.left,740,scrub.left+progress*(scrub.right-scrub.left),744),fill('#526c7d'));
        port.drawEllipse(P(scrub.left+progress*(scrub.right-scrub.left),742),6,6,fill('#263a47'));
        text(poseBusy()?'Drag hands / feet to place, pelvis to move, torso / head to tilt. Amber = reach or joint limit.':'Drag the hand on the viewer’s right to pull her arm. Drag the timeline to seek.',64,779,12,'#78848e');
        if (!interactive) advanceChecks();
    } catch(error) { fail(error); }
    return true;
});
pdg.on(pdg.eventType_PortDraw,()=>false);
pdg.onMouseDown(event=> {
    if (!interactive) return false;
    try {
        const b=buttonAt(event.mousePos);
        if (b) { b.action(); return true; }
        if(poseBusy())return poseControl.beginDrag(event.mousePos);
        if (inside(event.mousePos,scrub)) { scrubbing=true; scrubAt(event.mousePos); return true; }
        if (!(pushes && pushes.phase) && handControl.hitTest(event.mousePos))return handControl.beginDrag(event.mousePos);
    } catch(error) { fail(error); }
    return false;
});
pdg.onMouseMove(event=> {
    if (!interactive) return false;
    hover=buttonAt(event.mousePos);
    try {
        if(poseBusy())return poseControl.moveDrag(event.mousePos);
        if(handControl.mode==='dragging')return handControl.moveDrag(event.mousePos);
        if(scrubbing)scrubAt(event.mousePos);
    } catch(error) { fail(error); }
    return false;
});
pdg.onMouseUp(()=> {
    scrubbing=false;
    if(!interactive)return false;
    try {return poseBusy()?poseControl.endDrag():handControl.endDrag();} catch(error){fail(error);return false;}
});
pdg.onKeyPress(event=> {
    if (!interactive) return false;
    const key=String.fromCharCode(event.unicode).toLowerCase();
    try {
        if (event.unicode===pdg.key_Escape) finish();
        else if (key==='p') togglePose();
        else if (key==='r') restart();
        else if (key==='b') setBones(!showBones);
        else if (key==='c') setCapsules(!showCapsules);
        else if(poseBusy()) {
            if(key==='x')poseControl.flipElbow();
            else if(key==='[')poseControl.rotateSelected(-5);
            else if(key===']')poseControl.rotateSelected(5);
        }
        else if (key==='1') selectClip('weight_shift');
        else if (key==='2') selectClip('wave_hello');
        else if (key==='3') selectClip('reference');
        else if (key===' ') togglePause();
        else if (key==='e') toggleArm();
        else if (key==='w') toggleWeight();
        else if (key==='g') toggleGround();
        else if (key==='f') toggleGround(true);
        else if (key==='l') toggleLimpHand();
        else if (key==='o') toggleBlocker();
        else if (key==='d') dropRig();
        else if (key==='u' && ragdoll.mode!=='recovering') recoverRig();
        else if (key==='s') pushShoulder('soft');
        else if (key==='h') pushShoulder('hard');
        else return false;
    } catch(error) { fail(error); }
    return true;
});

function verifyPose() {
    bones.forEach(b=> {
        const t=sprite.getAnimationBoneTransform(b.name,pdg.animationSpace_Rig);
        check(Number.isFinite(t.x+t.y+t.rotation),b.name+' transform is nonfinite');
    });
    drawings.forEach(id=>check(sprite.getAnimationDrawableError(id)==='', 'Silhouette drawing failed'));
    ground.modifierIds.forEach(id=>check(sprite.getAnimationModifierError(id)==='', 'Ground modifier failed'));
    ragdoll.modifierIds.forEach(id=>check(sprite.getAnimationModifierError(id)==='', 'Joint limit modifier failed'));
    if(ragdoll.mode==='standing')for(const leg of ground.legs) {
        const foot=sprite.getAnimationBoneTransform(leg.foot.name,pdg.animationSpace_Rig);
        const drift=Math.hypot(foot.x-leg.target.x,foot.y-leg.target.y);
        stats.maxFootDrift=Math.max(stats.maxFootDrift,drift);
        check(drift<.08,'Planted foot slid more than 0.8 mm: '+drift+' cm');
        const rotation=foot.rotation-leg.foot.reference.angle-ground.angle;
        check(Math.abs(Math.atan2(Math.sin(rotation),Math.cos(rotation)))<.001,'Shoe did not follow the ground angle');
        const ik=sprite.getAnimationIKResult(leg.ik);
        check(ik.reachable && !ik.stretched,'Ground target was unreachable or stretched a leg');
    }
    const pelvis=sprite.getAnimationBoneTransform('root',pdg.animationSpace_Rig);
    stats.hipTravel=Math.max(stats.hipTravel,Math.abs(pelvis.x));
    const hand=sprite.getAnimationBoneTransform('left_hand',pdg.animationSpace_Rig);
    stats.maxHandLift=Math.max(stats.maxHandLift,-hand.y);
}
function advanceChecks() {
    if(poseCheck>=0) {advancePoseChecks();return;}
    if(controlCheck>=0) { advanceControlChecks(); return; }
    if(pushCheck>=0) { advancePushChecks(); return; }
    if(ragdollCheck>=0) { advanceRagdollChecks(); return; }
    if(blockerCheck>=0) { advanceBlockerChecks(); return; }
    if(handCheckIndex>=0) {
        const [name,time,expected]=handChecks[handCheckIndex];
        check(stats.handArtwork===expected,`Wrong hand at ${name} ${time}s: ${stats.handArtwork}`);
        verifyPose(); stats.groundChecks++;
        handCheckIndex++;
        if(handCheckIndex<handChecks.length) {
            selectClip(handChecks[handCheckIndex][0]); seek(handChecks[handCheckIndex][1]);
            setGroundAngle(groundChecks[handCheckIndex]*Math.PI/180);
        } else {
            setGroundAngle(0); selectClip('wave_hello'); seek(1.9); toggleBlocker();
            check(sprite.getAnimationProgress()<1e-6,'Blocker did not rewind the active wave');
            blockerCheck=0; checkStarted=now();
        }
        return;
    }
    verifyPose();
    const elapsed=now()-checkStarted;
    // Exercise both states of the public debug switch during each full cycle.
    const section=Math.floor(elapsed);
    if(section!==lastCheck) { setBones(section%2===1); setCapsules(section%2===0); lastCheck=section; }
    if(elapsed<clip.seconds+.15) return;
    stats.steps++;
    if(clipIndex===0) {
        check(stats.hipTravel>4,'Weight-shift clip did not move the pelvis');
        selectClip('wave_hello'); clipIndex++; checkStarted=now(); lastCheck=-1;
    } else {
        check(stats.maxHandLift>160,'Waving hand did not rise above the shoulder');
        handCheckIndex=0; setBones(false);
        selectClip(handChecks[0][0]); seek(handChecks[0][1]);
        setGroundAngle(groundChecks[0]*Math.PI/180);
    }
}
function verifyArmJoints() {
    for(const name of ['left_forearm','left_hand']) {
        const bone=bones.find(b=>b.name===name),local=bone.local;
        const parent=sprite.getAnimationBoneTransform(bone.parent,pdg.animationSpace_World);
        const joint=sprite.getAnimationBoneTransform(name,pdg.animationSpace_World);
        const c=Math.cos(parent.rotation),s=Math.sin(parent.rotation);
        const gap=Math.hypot(joint.x-(parent.x+c*local.x*parent.scaleX-s*local.y*parent.scaleY),
            joint.y-(parent.y+s*local.x*parent.scaleX+c*local.y*parent.scaleY));
        stats.maxArmJointGap=Math.max(stats.maxArmJointGap,gap);
        check(gap<2,'Arm joint separated at '+name+': '+gap+' pixels');
    }
}
function advanceBlockerChecks() {
    verifyPose();
    verifyArmJoints();
    check(Math.abs(sprite.physics.getMass()-totalMass)<1e-8,'Rig total must be 50 kg');
    check(sprite.getAnimationPhysicsMode('left_upper_arm',true)===pdg.animationPhysics_Driven,'Waving arm must be Driven');
    check(sprite.getAnimationPhysicsMode('right_upper_arm',true)===pdg.animationPhysics_Kinematic,'Other arm must stay Kinematic');
    const elapsed=now()-checkStarted;
    if(blockerCheck===0 && elapsed>=2.6) {
        seek(2.6); blockerCheck=1; checkStarted=now();
    } else if(blockerCheck===1 && elapsed>=1) {
        check(blocker.contacts>0 && blocker.isTouching(),'Arm did not contact the blocker');
        check(stats.handArtwork==='left_hand','Contact did not select the default hand artwork');
        blockedHandY=sprite.getAnimationBoneTransform('left_hand',pdg.animationSpace_World).y;
        check(blockedHandY>blocker.bounds.bottom-15,'Arm passed through the blocker: wrist y='+blockedHandY);
        stats.blockerChecks++; stats.blockerContacts=blocker.contacts;
        toggleBlocker(); blockerCheck=2; checkStarted=now();
    } else if(blockerCheck===2 && elapsed>=2) {
        const handY=sprite.getAnimationBoneTransform('left_hand',pdg.animationSpace_World).y;
        check(handY<blockedHandY-40,'Arm did not rise after removing the blocker');
        check(stats.handArtwork==='left_hand_open','Release did not restore the waving hand artwork');
        const wrist=sprite.findPart('left_hand').physics.getDriveState();
        stats.releasedWristErrorDegrees=Math.abs(wrist.rotationError)*180/Math.PI;
        check(stats.releasedWristErrorDegrees<5,'Released wrist stayed off its animation target: '+stats.releasedWristErrorDegrees+' degrees');
        for(const name of armNames)check(sprite.findPart(name).collider.getContactError()==='','Arm contact handler failed');
        stats.blockerChecks++; stats.releasedHandRise=blockedHandY-handY;
        dropRig();ragdollCheck=0;blockerCheck=-1;checkStarted=now();
    }
}
function advanceRagdollChecks() {
    verifyPose();
    check(Math.abs(sprite.physics.getMass()-totalMass)<1e-8,'Ragdoll control changed total mass');
    const elapsed=now()-checkStarted;
    if(ragdollCheck===0) {
        check(sprite.getAnimationPhysicsMode()===pdg.animationPhysics_Dynamic,'Whole ragdoll must be Dynamic');
        if(elapsed<2.5)return;
        const pelvis=sprite.getAnimationBoneTransform('root',pdg.animationSpace_World);
        check(pelvis.y>origin.y+bones[0].reference.y*scale+100,'Ragdoll did not fall');
        check(ragdoll.contacts>0,'Ragdoll did not contact the physical platform');
        stats.ragdollChecks++;recoverRig();ragdollCheck=1;checkStarted=now();
        check(sprite.getAnimationPhysicsMode()===pdg.animationPhysics_Dynamic && ragdoll.phase==='lifting','Recovery must start with a torso lift and free limbs');
    } else {
        check(elapsed<20,'Whole-body recovery did not complete');
        if(ragdoll.mode!=='standing')return;
        check(ragdoll.completions===1,'Expected one whole-body recovery-completion event');
        check(ragdoll.lastRecoverySeconds>=.45,'Recovery completed before its requested duration');
        check(sprite.getAnimationPhysicsMode()===pdg.animationPhysics_Kinematic,'Recovered rig must return to Kinematic');
        check(sprite.isAnimationPlaying() && clip.name==='weight_shift','Recovery must blend back to the playing weight-shift clip');
        check(ragdoll.recoveryEvents===1,'Expected one physics-recovery event');
        stats.ragdollChecks++;stats.recoveryEvents=ragdoll.recoveryEvents;stats.recoverySeconds=ragdoll.lastRecoverySeconds;
        ragdollCheck=-1;pushCheck=0;pushShoulder('soft');checkStarted=now();
    }
}
function advancePushChecks() {
    verifyPose();
    check(now()-checkStarted<20,'Shoulder push did not recover: '+ragdoll.phase);
    if(pushes.phase || pushes.completed!==pushCheck+1)return;
    const result=pushes.lastResult;
    check(result.shoulderTravelCm>1,'Shoulder did not move after the push');
    check(pushCheck===0?result.wallContacts===0:result.wallContacts>0,'Wrong wall-contact behavior for '+result.kind+' push');
    check(sprite.isAnimationPlaying() && clip.name==='weight_shift','Push did not return to weight shifting');
    check(sprite.getAnimationPhysicsMode()===pdg.animationPhysics_Kinematic,'Recovered push stayed physical');
    stats.pushChecks++;stats[result.kind+'Push']=result;stats.recoveryEvents=ragdoll.recoveryEvents;
    if(pushCheck++===0) {pushShoulder('hard');checkStarted=now();return;}
    pushCheck=-1;controlCheck=0;selectClip('wave_hello');seek(2.6);
    checkStarted=now();
}
function advanceControlChecks() {
    verifyPose();
    const elapsed=now()-checkStarted;
    if(controlCheck===0) {
        // Let the paused seek reach the physical bodies before releasing one.
        if(elapsed<.1)return;
        limpStartAngle=sprite.getAnimationBoneTransform('left_hand',pdg.animationSpace_Local).rotation;
        limpMaxRotation=0;
        toggleLimpHand();controlCheck=1;checkStarted=now();return;
    }
    verifyArmJoints();
    check(elapsed<10,'Hand control did not finish: '+handControl.mode);
    if(controlCheck===1) {
        const angle=sprite.getAnimationBoneTransform('left_hand',pdg.animationSpace_Local).rotation;
        // A freely swinging wrist can return near its starting angle. Measure
        // motion over the interval rather than only its final position.
        limpMaxRotation=Math.max(limpMaxRotation,Math.abs(Math.atan2(Math.sin(angle-limpStartAngle),Math.cos(angle-limpStartAngle))));
        stats.limpMaxRotation=limpMaxRotation;
    }
    if(controlCheck===1 && elapsed>=.8) {
        check(sprite.getAnimationPhysicsMode('left_hand')===pdg.animationPhysics_Dynamic,'Limp hand must be Dynamic');
        for(const name of ['left_upper_arm','left_forearm'])check(sprite.getAnimationPhysicsMode(name)===pdg.animationPhysics_Kinematic,'Limp hand released its parent');
        check(limpMaxRotation>.15,'Limp wrist did not move');
        toggleLimpHand();controlCheck=2;checkStarted=now();
    } else if(controlCheck===2 && handControl.mode==='animation') {
        check(handControl.limpCompletions===1,'Hand recovery did not complete');stats.handChecks++;
        dragStart=handControl.getPoint();handControl.beginDrag(dragStart);
        handControl.moveDrag(P(dragStart.x+90,dragStart.y+80));controlCheck=3;checkStarted=now();
    } else if(controlCheck===3 && elapsed>=1.5) {
        const p=handControl.getPoint(),drive=sprite.findPart('left_hand').physics.getDriveState();
        check(p.x>dragStart.x+30 && p.y>dragStart.y+30,'Dragging did not pull the hand');
        check(drive.enabled && Math.hypot(drive.forceX,drive.forceY)<=drive.maxForce+1e-6,'Manual hand drive exceeded its force cap');
        check(sprite.getAnimationPhysicsMode('left_upper_arm',true)===pdg.animationPhysics_Dynamic,'Manual drag did not release rig tracking');
        handControl.endDrag();controlCheck=4;checkStarted=now();
    } else if(controlCheck===4 && elapsed>=2 && handControl.mode==='animation') {
        check(handControl.dragCompletions===1,'Manual handoff did not complete');stats.handChecks++;
        check(sprite.getAnimationPhysicsMode('left_upper_arm',true)===pdg.animationPhysics_Driven,'Drag release did not restore rig tracking');
        checkStarted=now();groundPreview=false;groundMotion.setTilting(true,checkStarted,ground.angle,fastSweepSeconds);controlCheck=5;
    } else if(controlCheck>=5 && elapsed>=controlCheck-4) {
        const target=controlCheck===6?-10:10;
        check(Math.abs(ground.angle*180/Math.PI-target)<.2,'Fast floor tilt missed its one-second endpoint');
        stats.fastTiltChecks++;
        if(++controlCheck<=7)return;
        setGroundAngle(0);togglePose();poseCheck=0;controlCheck=-1;checkStarted=now();
    }
}
function fail(error) {
    stats.error=error.message;
    console.error(error.stack||error);
    finish(1);
}
function advancePoseChecks() {
    const state=poseControl.getState();
    check(!state.errors.length,'Pose controller error: '+state.errors.join(', '));
    check(sprite.physics.getMass()===totalMass,'Posing changed rig mass');
    const elapsed=now()-checkStarted;
    if(poseCheck===0) {
        check(state.mode==='posing' && !ground.enabled,'Pose mode did not release floor IK');
        const h=state.handles.find(h=>h.name==='left_hand');posePoint=h.point;
        check(poseControl.beginDrag(h.point),'Pose hand could not be selected');
        poseControl.moveDrag(P(h.point.x+60,h.point.y-65));poseControl.endDrag();
        poseCheck=1;checkStarted=now();
    } else if(poseCheck===1 && elapsed>.3) {
        const h=state.handles.find(h=>h.name==='left_hand');
        check(Math.hypot(h.point.x-posePoint.x,h.point.y-posePoint.y)>20,'Posed hand did not move');
        posePoint=h.point;poseCheck=2;checkStarted=now();
    } else if(poseCheck===2 && elapsed>.3) {
        const h=state.handles.find(h=>h.name==='left_hand');
        check(Math.hypot(h.point.x-posePoint.x,h.point.y-posePoint.y)<.1,'Released pose did not hold');
        togglePose();poseCheck=3;checkStarted=now();
    } else if(poseCheck===3 && elapsed>.7) {
        check(state.mode==='off' && ground.enabled && sprite.isAnimationPlaying(),'Pose did not return to animation');
        verifyPose();stats.poseChecks=3;
        console.log('PASS: human rig, physics controls, fast tilt and held IK posing.');
        console.log(JSON.stringify(stats));finish();
    }
}
function finish(exitCode) {
    if (finished) return;
    finished=true;
    setTimeout(()=> {
        pdg.cleanupLayer(layer); pdg.gfx.closeGraphicsPort(port); pdg.quit();
        if(exitCode) process.exit(exitCode);
    },0);
}
global.pdgAnimationPhysicsDemo={stats,selectClip,seek,setBones,setCapsules,togglePause,toggleGround,setGroundAngle,toggleBlocker,dropRig,recoverRig,pushShoulder,toggleLimpHand,finish,
    togglePose,getPose:()=>poseControl.getState(),getPoseControl:()=>poseControl,
    toggleArm,toggleWeight,getMembership:()=>membership.getState(),
    getCapsules:()=>({visible:showCapsules,bodies:capsuleOverlay.read()}),
    getArmTwist:()=>ragdoll.armTwist.getState(),
    getSprite:()=>sprite,getGround:()=>({angle:ground.angle,tilting:groundMotion.tilting,sweepSeconds:groundMotion.sweepSeconds}),
    getBlocker:()=>({enabled:blocker.enabled,contacts:blocker.contacts,touching:blocker.isTouching(),torqueLimitsNm:blocker.torqueLimitsNm}),
    getRagdoll:()=>({mode:ragdoll.mode,phase:ragdoll.phase,physicsWeight:ragdoll.physicsWeight,completions:ragdoll.completions,contacts:ragdoll.contacts,recoverySeconds:ragdoll.lastRecoverySeconds}),
    getPush:()=>({kind:pushes.kind,phase:pushes.phase,contacts:pushes.contacts,completed:pushes.completed,lastResult:pushes.lastResult}),
    getHand:()=>({mode:handControl.mode,point:handControl.getPoint(),target:handControl.target,limpCompletions:handControl.limpCompletions,dragCompletions:handControl.dragCompletions})};
try {
    check(!!sprite,'Could not load human.scml');
    sprite.setLocation(origin); sprite.setScale(scale,scale);
    check(sprite.enableAnimationPose('reference'),'Could not enable human animation pose');
    check(sprite.getAnimationBoneNames().length===bones.length,'Expected all 16 human bones');
    ground=plantFeet(pdg,sprite);
    blocker=createArmBlocker(pdg,layer,sprite,origin,scale,now);
    ragdoll=createRagdoll(pdg,layer,sprite,ground,blocker,origin,scale,now);
    pushes=createPushes(pdg,layer,sprite,ground,ragdoll,origin,scale,now);
    handControl=createHandControl(pdg,sprite,ragdoll,blocker,scale);
    capsuleOverlay=createCapsuleOverlay(pdg,sprite,bones);
    membership=createMembership(pdg,sprite,ragdoll,scale);
    poseControl=createPoseControl(pdg,sprite,ground,ragdoll,now);
    stats.bones=bones.length;
    const artworkDrawings={};
    artwork.forEach(art=> {
        const drawing=pdg.createDrawing();
        art.contours.forEach(contour=> {
            const polygon=new pdg.Polygon();
            // Keep artwork in its native resolution; map it to the centimeter
            // rig with Attributes instead of shrinking the polygon vertices.
            contour.forEach(([x,y])=>polygon.addPoint(P(x*artworkUnitsPerCm,y*artworkUnitsPerCm)));
            check(polygon.getPointCount()===contour.length,art.name+' lost artwork vertices');
            drawing.addPolygon(polygon,fill('#030305').scale(1/artworkUnitsPerCm));
        });
        artworkDrawings[art.name]=drawing;
    });
    bones.forEach(bone=> {
        const drawing=bone.name.endsWith('_hand') ? ()=> {
            const side=bone.name.startsWith('left')?'left':'right';
            const normal=(side==='left' && blocker.isTouching())||ragdoll.mode!=='standing'?bone.name:artworkAt(bone.name,clip.name,sprite.getAnimationProgress()*clip.seconds);
            const name=ragdoll.armTwist.artwork(side,normal);
            if(side==='left')stats.handArtwork=name;
            return artworkDrawings[name];
        } : artworkDrawings[bone.name];
        drawings.push(sprite.addAnimationDrawable(drawing,{bone:bone.name,slot:bone.name+'_art',
            placement:pdg.animationDraw_ReplaceSlot,strokeSpace:pdg.animationStroke_Local}));
    });
    stats.drawings=drawings.length;
    selectClip(interactive ? 'reference' : 'weight_shift'); checkStarted=now();
    if(!interactive)groundMotion.setTilting(true,checkStarted);
} catch(error) { fail(error); }
pdg.run();
