// Capture rendered luma progress in both directions, including the solid HUD.
module.exports=async function({evaluate,pageCall,delay,report,url}) {
    const fs=require('fs'),path=require('path');
    const dir=path.dirname(report),shots=[];
    for (const reverse of [false,true]) {
        const target=new URL(url);target.searchParams.set('capture',reverse?'reverse':'1');
        await pageCall('Page.navigate',{url:target.toString()});
        const deadline=Date.now()+30000;
        while (!await evaluate('!!window.pdgCameraVisualTest')) {
            if(Date.now()>deadline)throw Error('Camera frame capture did not initialize');
            await delay(100);
        }
        for(const progress of [0,.1,.25,.4,.55,.7,.8,.9,1]) {
            await evaluate('window.pdgCameraVisualTest.setProgress('+progress+')');
            await delay(200);
            const shot=await pageCall('Page.captureScreenshot',{format:'png'});
            const name=(reverse?'night-city':'city-night')+'-'+String(Math.round(progress*100)).padStart(3,'0')+'.png';
            fs.writeFileSync(path.join(dir,name),Buffer.from(shot.data,'base64'));
            shots.push({reverse,progress,file:name,data:shot.data});
        }
    }
    // Assemble the screenshots in the browser, where PNG decoding is available.
    const sheet=await pageCall('Runtime.evaluate',{awaitPromise:true,returnByValue:true,expression:`(async()=>{
        const shots=${JSON.stringify(shots)},canvas=document.createElement('canvas');
        const w=480,h=270;canvas.width=w*3;canvas.height=(h+24)*6;
        const ctx=canvas.getContext('2d');ctx.fillStyle='#20262d';ctx.fillRect(0,0,canvas.width,canvas.height);
        for(let i=0;i<shots.length;++i){
            const s=shots[i],image=new Image();image.src='data:image/png;base64,'+s.data;await image.decode();
            const x=(i%3)*w,y=Math.floor(i/3)*(h+24);
            ctx.fillStyle='#fff';ctx.font='16px sans-serif';ctx.fillText((s.reverse?'Night → City':'City → Night')+' '+Math.round(s.progress*100)+'%',x+8,y+18);
            ctx.drawImage(image,160,36,960,610,x,y+24,w,h);
        }
        return canvas.toDataURL('image/png').split(',')[1];
    })()`});
    if(sheet.exceptionDetails)throw Error(sheet.exceptionDetails.text);
    fs.writeFileSync(path.join(dir,'luma-contact-sheet.png'),Buffer.from(sheet.result.value,'base64'));
    return {status:'passed',frames:shots.map(({data,...frame})=>frame),contactSheet:'luma-contact-sheet.png'};
};
