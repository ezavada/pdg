// From test/: ./pdg ui_tests/wheel_chains_test.js --wait
// Browser: test/ui.html?test=wheel-chains (automated=1 runs the finite check).
'use strict';
const {createWheelRig}=require('../data/wheel-chains/rig');
const interactive=process.argv.includes('--wait');
const P=(x,y)=>new pdg.Point(x,y),R=(l,t,r,b)=>new pdg.Rect(l,t,r,b);
const fill=color=>new pdg.Attributes().fillColor(color);
const stroke=(color,width=1)=>new pdg.Attributes().lineColor(color).lineThickness(width);
const port=pdg.gfx.createWindowPort(new pdg.Rect(1100,800),'PDG - Wheel and chains');
pdg.gfx.setTargetFPS(60);
const layer=pdg.createSpriteLayer(port);
layer.setUseChipmunkPhysics(true);layer.setGravity(981);layer.setDamping(1);layer.enableCollisions();
const floor=layer.createSprite();floor.setupPhysicsBody().setMode(pdg.physicsBody_Static);
floor.setupCollider().setBox(R(-2000,740,3000,780)).setCategory(2).setCollisionMask(1).setRestitution(0).setFriction(.8);
const state={time:0,target:P(400,330),position:P(400,330),
    velocity:P(0,0),shake:false,shakeWeight:0,shakeOffset:0,free:false,debug:false,follow:true,drag:false,frames:0,maxJointError:0,error:null};
let rig,axle,brake,torqueHandle=0,finished=false,phase=0,phaseStarted=0,restExtension=0,spinExtension=0,spinSamples=0,spinPeak=0,extendedSamples=0;
const buttons=[];
const torqueStep=10,torqueLimit=120; // N m; internal distance units are centimeters.
function check(ok,message){if(!ok)throw Error(message);}
function reset() {
    if(rig)layer.removeSprite(rig.sprite);
    if(axle)layer.removeSprite(axle);
    torqueHandle=0;
    Object.assign(state,{time:0,target:P(400,330),position:P(400,330),velocity:P(0,0),shake:false,shakeWeight:0,shakeOffset:0,free:false,drag:false,torque:0,braking:false});
    rig=createWheelRig(pdg,layer,state.position,state.follow?pdg.animationRoot_Follow:pdg.animationRoot_Fixed);
    rig.addArtwork();setDebug(state.debug);
    rig.sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic,'wheel',false,0);
    axle=layer.createSprite();axle.setLocation(state.position);
    axle.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic);
    holdAxle();
    // Run on each solver substep, so the wheel carries a continuous trajectory
    // even when display frames are delayed. Dynamic links receive no targets.
    rig.sprite.addAnimationHelper(new pdg.IAnimationHelper((owner,seconds)=>{
        state.time+=seconds;
        if(state.free)return true;
        for(const axis of ['x','y']) {
            const velocity=Math.max(-200,Math.min(200,4*(state.target[axis]-state.position[axis])));
            state.velocity[axis]+=Math.max(-600,Math.min(600,8*(velocity-state.velocity[axis])))*seconds;
            state.position[axis]+=state.velocity[axis]*seconds;
        }
        state.shakeWeight+=((state.shake?1:0)-state.shakeWeight)*(1-Math.exp(-5*seconds));
        state.shakeOffset=12*state.shakeWeight*Math.sin(state.time*2*Math.PI*1.5);
        axle.setLocation(P(state.position.x+state.shakeOffset,state.position.y));
        return true;
    }));
}
function setDebug(enabled) {
    state.debug=enabled;
    rig.sprite.setAnimationDebugDraw(enabled?pdg.animationDebug_Bones:pdg.animationDebug_None);
}
function setTorque(value) {
    if(state.free && value!==0)return;
    value=Math.max(-torqueLimit,Math.min(torqueLimit,value));
    if(torqueHandle)rig.sprite.physics.removeForce(torqueHandle);
    state.torque=value;state.braking=false;brake.setMaxForce(0);
    torqueHandle=value?rig.sprite.physics.addContinuousTorque(value*10000):0;
}
function coast(){setTorque(0);}
function stop() {if(state.free)return;coast();state.braking=true;brake.setMaxForce(120*10000);}
function holdAxle() {
    axle.physics.createPivotJoint(rig.wheel);
    brake=axle.physics.createMotor(rig.wheel,0,0);
}
function release() {
    if(state.free)return;
    coast();state.free=true;state.drag=false;state.shake=false;
    axle.physics.disconnect();
}
function regrip() {
    if(!state.free)return;
    const actual=rig.wheel.getState();
    state.position=P(actual.x,actual.y);state.target=P(actual.x,actual.y);
    state.velocity=P(0,0);state.shakeWeight=state.shakeOffset=0;
    axle.setLocation(state.position);holdAxle();state.free=false;
}
function flip(axis) {
    // A brake is an angular boundary constraint. Release it explicitly before
    // reflection, then restore its setting against the stationary support.
    const wasBraking=state.braking;
    axle.physics.disconnect();
    if(axis==='x')rig.sprite.setFlipX(!rig.sprite.isFlippedX());
    else rig.sprite.setFlipY(!rig.sprite.isFlippedY());
    const actual=rig.wheel.getState();
    state.position=P(actual.x,actual.y);state.target=P(actual.x,actual.y);
    state.velocity=P(0,0);state.shakeWeight=state.shakeOffset=0;
    axle.setLocation(state.position);holdAxle();
    brake.setMaxForce(wasBraking?120*10000:0);
    if(state.free)axle.physics.disconnect();
}
function button(label,y,action,active=()=>false) {buttons.push({label,bounds:R(825,y,1070,y+38),action,active});}
button('Add torque: +10 N m [+]',170,()=>setTorque(state.torque+torqueStep));
button('Subtract torque: -10 N m [-]',212,()=>setTorque(state.torque-torqueStep));
button('Coast: no motor torque [C]',254,coast,()=>state.torque===0&&!state.braking);
button(pdg.visualTestSession ? 'Brake [K]' : 'Brake [Space]',296,stop,()=>state.braking);
button('Shake axle [S]',338,()=>{if(!state.free)state.shake=!state.shake;},()=>state.shake);
button('Release / hold axle [D]',380,()=>state.free?regrip():release(),()=>state.free);
button('Show bones [B]',422,()=>setDebug(!state.debug),()=>state.debug);
button('Flip horizontally [X]',464,()=>flip('x'),()=>rig.sprite.isFlippedX());
button('Flip vertically [Y]',506,()=>flip('y'),()=>rig.sprite.isFlippedY());
button('Follow / fixed frame [F]',548,()=>{state.follow=!state.follow;reset();},()=>state.follow);
button('Reset [R]',590,reset);
function text(message,x,y,size=15,color='#d5e0e8'){port.drawText(message,P(x,y),fill(color).textSize(size));}
layer.onErasePort(()=>{
    port.drawRect(port.getDrawingArea(),fill('#101d29'));
    port.drawRect(R(24,106,800,766),fill('#182b39').roundedCorners(10));
    for(let x=40;x<800;x+=40)port.drawLine(P(x,110),P(x,738),stroke('#203542'));
    for(let y=140;y<740;y+=40)port.drawLine(P(28,y),P(796,y),stroke('#203542'));
    port.drawRect(R(26,740,798,765),fill('#496071'));
    port.drawLine(P(26,740),P(798,740),stroke('#a6bcc9',2));
    return true;
});
function advanceChecks() {
    const elapsed=state.time-phaseStarted;
    const wheel=rig.wheel.getState();
    for(const body of rig.members) {
        const s=body.getState();check(Number.isFinite(s.x+s.y+s.rotation+s.velocityX+s.velocityY+s.angularVelocity),'Nonfinite chain body');
    }
    const error=rig.jointError();state.maxJointError=Math.max(error,state.maxJointError);
    check(error<4,'Chain pivot separated by '+error+' cm');
    check(Math.abs(rig.sprite.physics.getMass()-24)<1e-6,'Assembly mass changed');
    if(!state.free)check(Math.hypot(wheel.x-state.position.x-state.shakeOffset,wheel.y-state.position.y)<1,
        'Wheel left its physical axle');
    if(phase===0 && elapsed>2) {
        restExtension=rig.extension();state.target=P(460,290);state.shake=true;phase++;phaseStarted=state.time;
    } else if(phase===1 && elapsed>2) {
        check(Math.abs(wheel.x-400)>20,'Shaking/moving did not move the wheel');
        state.shake=false;setTorque(80);phase++;phaseStarted=state.time;
    } else if(phase===2) {
        if(elapsed>3) {
            const extension=rig.extension();spinExtension+=extension;spinSamples++;
            spinPeak=Math.max(spinPeak,extension);
            if(extension>restExtension+25)extendedSamples++;
        }
        if(elapsed>10) {
            // Flexible chains continue oscillating. Require repeated outward
            // extension at full speed, independent of the final oscillation phase.
            check(extendedSamples>=3,'Spin did not extend the chains outward');
            const old=wheel.angularVelocity;
            flip('x');check(Math.abs(rig.wheel.getAngularVelocity()+old)<1e-6,'Flip did not reverse physical spin');
            stop();phase++;phaseStarted=state.time;
        }
    } else if(phase===3 && elapsed>4) {
        check(Math.abs(wheel.angularVelocity)<.3,'Bounded brake did not slow the wheel');
        release();phase++;phaseStarted=state.time;
    } else if(phase===4 && elapsed>2) {
        check(wheel.y>400,'Released wheel did not fall');
        const frame=rig.sprite.getLocation();
        check(Math.hypot(frame.x-wheel.x,frame.y-wheel.y)<.01,'Following Sprite lost its physical root');
        regrip();phase++;phaseStarted=state.time;
    } else if(phase===5 && elapsed>.5) {
        check(rig.sprite.getAnimationPhysicsMode('wheel')===pdg.animationPhysics_Dynamic,'Wheel lost dynamic control');
        console.log('PASS: torque, axle movement, outward extension, live reflection, braking, release and regrip.');
        console.log(JSON.stringify({frames:state.frames,maxJointError:state.maxJointError,restExtension,spinExtension:spinExtension/spinSamples,spinPeak}));
        finish();
    }
}
layer.onPostDrawLayer(()=>{
    if(finished)return false;
    try {
        state.frames++;
        text('WHEEL + CHAINS',30,42,26,'#f2f6f9');
        text('Apply torque. Coast and brake. Flip a moving assembly.',32,74,16,'#8fa8ba');
        text('AXLE CONTROL',825,140,14,'#91afc3');
        for(const b of buttons) {
            port.drawRect(b.bounds,fill(b.active()?'#335d73':'#21394b').roundedCorners(6));
            text(b.label,b.bounds.left+12,b.bounds.top+25,14);
        }
        const actual=rig.wheel.getState(),frame=rig.sprite.getLocation();
        port.drawLine(P(frame.x-9,frame.y),P(frame.x+9,frame.y),stroke('#fff',2));
        port.drawLine(P(frame.x,frame.y-9),P(frame.x,frame.y+9),stroke('#fff',2));
        text((state.free?'Free':'Held')+' / '+(actual.angularVelocity*60/(2*Math.PI)).toFixed(1)+' RPM',825,653,14);
        text('Motor: '+state.torque.toFixed(0)+' N m'+(state.braking?'  BRAKING':''),825,677,14);
        text('Inertia: '+(rig.sprite.physics.getMomentOfInertia()/10000).toFixed(2)+' kg m²',825,701,13);
        text('Momentum: '+(rig.sprite.physics.getAngularMomentum()/10000).toFixed(2)+' kg m²/s',825,725,13);
        text('24 kg / '+(state.follow?'Follow frame':'Fixed frame'),825,749,12,'#91afc3');
        text('Drag the wheel to move it. F changes frame policy and resets. Esc closes.',32,787,13,'#91afc3');
        if(!interactive)advanceChecks();
    } catch(error){fail(error);}
    return true;
});
pdg.on(pdg.eventType_PortDraw,()=>false);
pdg.onMouseDown(event=>{
    if(!interactive)return false;
    try {
        const p=event.mousePos,b=buttons.find(b=>p.x>=b.bounds.left&&p.x<=b.bounds.right&&p.y>=b.bounds.top&&p.y<=b.bounds.bottom);
        if(b){b.action();return true;}
        const wheel=rig.wheel.getState();
        if(!state.free && Math.hypot(p.x-wheel.x,p.y-wheel.y)<=rig.radius){state.drag=true;return true;}
    }catch(error){fail(error);}
    return false;
});
pdg.onMouseMove(event=>{
    if(!state.drag)return false;
    state.target=P(Math.max(100,Math.min(700,event.mousePos.x)),Math.max(175,Math.min(560,event.mousePos.y)));
    return true;
});
pdg.onMouseUp(()=>{state.drag=false;return false;});
pdg.onKeyPress(event=>{
    if(!interactive)return false;
    try {
        const key=String.fromCharCode(event.unicode).toLowerCase();
        if(event.unicode===pdg.key_Escape)finish();
        else if(key==='+'||key==='=')setTorque(state.torque+torqueStep);else if(key==='-')setTorque(state.torque-torqueStep);
        else if(key===' ' || (pdg.visualTestSession && key==='k'))stop();else if(key==='c')coast();else if(key==='x'||key==='y')flip(key);else if(key==='s'&&!state.free)state.shake=!state.shake;
        else if(key==='d')state.free?regrip():release();else if(key==='b')setDebug(!state.debug);
        else if(key==='f'){state.follow=!state.follow;reset();}else if(key==='r')reset();else return false;
    }catch(error){fail(error);}
    return true;
});
function fail(error){state.error=error.message;console.error(error.stack||error);console.error(JSON.stringify({phase,state,joints:rig&&rig.jointErrors(),wheel:rig&&rig.wheel.getState()}));finish(1);}
function finish(code=0){if(finished)return;finished=true;setTimeout(()=>code?process.exit(code):pdg.quit(),0);}
global.pdgWheelChainsDemo={state,getRig:()=>rig,setTorque,coast,stop,flip,release,regrip,reset,finish};
try{reset();}catch(error){fail(error);}
pdg.run();
