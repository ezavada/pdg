// Run a browser test with real elapsed time. Chrome's --dump-dom virtual clock can
// expire test timers without corresponding engine simulation updates.
'use strict';
const {spawn}=require('child_process');
const fs=require('fs');
const path=require('path');
const os=require('os');
const [browser,url,report,resultId='pdg-ui-result-json',timeoutMs='120000']=process.argv.slice(2);
if(!browser || !url || !report)throw Error('Usage: run_ui_browser.js browser url report.html [resultElementId]');
if (!Number.isFinite(Number(timeoutMs)) || Number(timeoutMs) <= 0) throw Error('Invalid browser test timeout');
fs.mkdirSync(path.dirname(report), {recursive:true});
fs.rmSync(report, {force:true}); // Never leave a previous run's PASS report after a crash.
const profile=fs.mkdtempSync(path.join(os.tmpdir(),'pdg-ui-chrome-'));
const headed = process.argv.includes('--headed');
const uncapped = process.argv.includes('--perf-uncapped');
const chrome=spawn(browser,[...(headed ? [] : ['--headless=new','--enable-unsafe-swiftshader']), '--remote-debugging-pipe',
    ...(uncapped ? ['--disable-frame-rate-limit','--disable-gpu-vsync',
        '--disable-extensions','--disable-component-extensions-with-background-pages'] : []),
    '--user-data-dir='+profile,'--no-first-run','--no-default-browser-check',
    '--disable-background-timer-throttling',
    '--disable-renderer-backgrounding','--disable-backgrounding-occluded-windows','about:blank'],
    {stdio:['ignore','ignore','pipe','pipe','pipe']});
let sequence=0,buffer='',browserError='';
const pending=new Map();
chrome.stderr.on('data',chunk=>{browserError=(browserError+chunk).slice(-4000);});
function rejectPending(error) {
    for(const call of pending.values()){clearTimeout(call.timer);call.reject(error);}
    pending.clear();
}
chrome.on('error',rejectPending);
const exited=new Promise(resolve=>{
    chrome.once('exit',code=>{
        rejectPending(Error('Chrome exited: '+code+' '+browserError));resolve();
    });
    chrome.once('error',resolve);
});
chrome.stdio[3].on('error',rejectPending);
chrome.stdio[4].on('data',chunk=>{
    buffer+=chunk.toString();
    let end;
    while((end=buffer.indexOf('\0'))>=0) {
        const message=JSON.parse(buffer.slice(0,end));buffer=buffer.slice(end+1);
        if(message.method==='Runtime.consoleAPICalled' && message.params.type==='error')
            console.error(message.params.args.map(arg=>arg.description || arg.value).join(' '));
        const call=pending.get(message.id);
        if(!call)continue;
        pending.delete(message.id);clearTimeout(call.timer);
        if(message.error)call.reject(Error(message.error.message));else call.resolve(message.result);
    }
});
function send(method,params={},sessionId) {
    return new Promise((resolve,reject)=>{
        const id=++sequence;
        const timer=setTimeout(()=>{pending.delete(id);reject(Error('Chrome command timed out: '+method));},15000);
        pending.set(id,{resolve,reject,timer});
        chrome.stdio[3].write(JSON.stringify({id,method,params,sessionId})+'\0');
    });
}
const delay=ms=>new Promise(resolve=>setTimeout(resolve,ms));
async function run() {
    // Own an explicit page; an extension's startup/sign-in tab must never be
    // mistaken for the benchmark page when Chrome creates multiple targets.
    const {targetId}=await send('Target.createTarget',{url:'about:blank'});
    const {sessionId}=await send('Target.attachToTarget',{targetId,flatten:true});
    const pageCall=(method,params)=>send(method,params,sessionId);
    const evaluate=async expression=>{
        const result=await pageCall('Runtime.evaluate',{expression,returnByValue:true});
        if(result.exceptionDetails)throw Error(result.exceptionDetails.exception?.description || result.exceptionDetails.text);
        return result.result.value;
    };
    await pageCall('Page.enable');
    await pageCall('Runtime.enable');
    await pageCall('Emulation.setDeviceMetricsOverride',{width:1280,height:960,deviceScaleFactor:1,mobile:false});
    await pageCall('Page.bringToFront');
    await pageCall('Page.navigate',{url});
    let result;
    if (resultId === 'pdg-visual-controls' || resultId === 'pdg-mvc-gallery') {
        result = await require(resultId === 'pdg-mvc-gallery' ? './mvc_gallery_check' : './visual_controls_check')({evaluate, pageCall, delay, url});
        fs.writeFileSync(report, JSON.stringify(result, null, 2));
        console.log(JSON.stringify(result));
        return;
    }
    const deadline=Date.now()+Number(timeoutMs);
    while(Date.now()<deadline) {
        await delay(250);
        const text=await evaluate('document.getElementById('+JSON.stringify(resultId)+')?.textContent');
        if(text){result=JSON.parse(text);break;}
    }
    fs.writeFileSync(report,await evaluate('document.documentElement.outerHTML'));
    if(!result)throw Error('Browser test timed out; report: '+report);
    console.log(JSON.stringify(result));
    if(result.status!=='passed')process.exitCode=1;
}
run().catch(error=>{
    console.error(error.message);process.exitCode=1;
    if (!fs.existsSync(report)) {
        const result={status:'failed',url,message:error.message,browserError};
        const json=JSON.stringify(result,null,2);
        fs.writeFileSync(report, resultId === 'pdg-visual-controls' ? json :
            '<!doctype html><meta charset="utf-8"><title>PDG test failed</title><pre>' +
            json.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;') + '</pre>');
    }
}).finally(async()=>{
    chrome.kill();
    const force=setTimeout(()=>chrome.kill('SIGKILL'),3000);
    await exited;clearTimeout(force);
    // Browser helpers can keep inherited DevTools pipes open after Chrome exits.
    // Waiting for the stdio "close" event left completed benchmarks hanging.
    chrome.stdio[3].destroy();chrome.stdio[4].destroy();chrome.stderr.destroy();
    fs.rmSync(profile,{recursive:true,force:true});
});
