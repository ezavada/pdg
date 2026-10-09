'use strict';
const assert=require('assert');
const fs=require('fs');

// Exercise actual browser pointer events, including exits without an engine move.
module.exports=async function({evaluate,pageCall,delay,report}) {
    const state=()=>evaluate('window.pdgProceduralDemo?.getState()');
    async function waitFor(predicate,label='ready') {
        const deadline=Date.now()+30000;
        let last;
        while(Date.now()<deadline) {
            const value=await state();
            last=value;
            if(value&&predicate(value))return value;
            await delay(100);
        }
        throw Error('FABRIK pointer check timed out: '+label+' '+JSON.stringify(last&&{
            frames:last.frames,reaching:last.reaching,active:last.tentacles.map(t=>t.active)}));
    }
    await waitFor(s=>s.frames>0);
    // Software rendering can consume the demo's eight seconds during pointer
    // checks. Keep its normal smoke-test exit pending until input checks finish.
    await evaluate('window.pdgProceduralDemo.checkingInput=true');
    const bounds=await evaluate(`(()=>{const c=document.getElementById('pdg-canvas'),r=c.getBoundingClientRect();
        return {x:r.left,y:r.top,sx:r.width/c.width,sy:r.height/c.height};})()`);
    async function move(x,y) {
        await pageCall('Input.dispatchMouseEvent',{type:'mouseMoved',x:bounds.x+x*bounds.sx,y:bounds.y+y*bounds.sy});
    }
    function resting(s) {
        assert.strictEqual(s.reaching,false);
        assert.strictEqual(s.blend,0);
        s.tentacles.forEach(t=>{
            assert.strictEqual(t.active,false);
            const root=t.points[0],tip=t.points[t.points.length-1];
            t.points.forEach(p=>assert(Math.abs(p.x-root.x)<.02,'Resting chain must be vertical'));
            assert(Math.abs(tip.y-root.y-t.length)<.02,'Resting chain must point downward');
        });
    }
    await move(10,100);
    resting(await waitFor(s=>!s.reaching&&s.blend===0));
    const initial=await state();
    assert.strictEqual(initial.showTrails,false);
    for(let i=0;i<15;i+=5) {
        const lengths=initial.tentacles.slice(i,i+5).map(t=>t.length);
        assert.strictEqual(new Set(lengths).size,5);
        assert.strictEqual(Math.max(...lengths),lengths[2]);
        assert(lengths[1]>lengths[0]&&lengths[3]>lengths[4]);
    }
    let reachCount=0;
    async function reach() {
        await move(550,430);
        return waitFor(s=>s.reaching&&s.blend===1&&s.tentacles.every(t=>t.active),'reach '+(++reachCount));
    }
    await move(550,430);
    const entering=await waitFor(s=>s.reaching&&s.blend>0,'fade in');
    assert(entering.blend<1,'Entry must ramp through partial IK');
    const reaching=await reach();
    assert(reaching.tentacles.some(t=>Math.abs(t.points.at(-1).x-t.points[0].x)>30));
    const shot=await pageCall('Page.captureScreenshot',{format:'png'});
    fs.writeFileSync(report.replace(/\.html$/,'.reaching.png'),Buffer.from(shot.data,'base64'));
    await move(10,100); // Inside canvas, outside the scene.
    const leaving=await waitFor(s=>!s.reaching,'fade out');
    assert(leaving.blend>0,'Exit must retain partial IK while settling');
    resting(await waitFor(s=>!s.reaching&&s.blend===0,'scene exit'));
    await reach();
    await pageCall('Input.dispatchMouseEvent',{type:'mouseMoved',x:0,y:0}); // Leave canvas.
    resting(await waitFor(s=>!s.reaching&&s.blend===0,'canvas exit'));
    await reach();
    await evaluate("window.dispatchEvent(new Event('blur'))");
    resting(await waitFor(s=>!s.reaching&&s.blend===0,'blur'));
    const frame=(await state()).frames;
    await move(560,430);
    resting(await waitFor(s=>s.frames>frame,'move while blurred'));
    await evaluate("window.dispatchEvent(new Event('focus'))");
    await reach();
    await move(10,100);
    resting(await waitFor(s=>!s.reaching&&s.blend===0,'final scene exit'));
    const restShot=await pageCall('Page.captureScreenshot',{format:'png'});
    fs.writeFileSync(report.replace(/\.html$/,'.png'),Buffer.from(restShot.data,'base64'));
    const result={status:'passed',checks:['varied lengths','longer inner tentacles','downward rest',
        'trails off by default','smooth entry','smooth exit','pointer reaching','scene exit','canvas exit','window blur','pointer reentry','focus recovery']};
    fs.writeFileSync(report.replace(/\.html$/,'.pointer.json'),JSON.stringify(result,null,2)+'\n');
    await evaluate('window.pdgProceduralDemo.checkingInput=false');
    return result;
};
