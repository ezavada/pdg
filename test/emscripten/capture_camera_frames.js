// tools/node test/emscripten/capture_camera_frames.js [output-directory]
'use strict';
const fs=require('fs'),path=require('path'),{spawn}=require('child_process');
const runner=require('../lib/test_runner');
(async()=>{
    const dir=path.resolve(process.argv[2] || 'artifacts/test-results/web/ui/camera-frames');
    fs.mkdirSync(dir,{recursive:true});
    const server=await runner.serve();
    try {
        const url='http://127.0.0.1:'+server.address().port+'/test/ui.html?interactive=1&kind=ui&suites=camera&page=6&capture=1';
        process.exitCode=await new Promise((resolve,reject)=>{
            const child=spawn(process.execPath,[path.join(__dirname,'run_ui_browser.js'),runner.browserPath(),url,path.join(dir,'frames.json'),'pdg-camera-frames'],{stdio:'inherit'});
            child.on('error',reject);child.on('exit',code=>resolve(code===null?1:code));
        });
    } finally {server.close();}
})().catch(error=>{console.error(error);process.exitCode=1;});
