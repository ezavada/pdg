// Run the interactive gallery acceptance checks and capture its rendered page.
'use strict';
const path=require('path'),{spawn}=require('child_process');
const runner=require('../lib/test_runner');
(async function() {
    const server=await runner.serve();
    try {
        const url='http://127.0.0.1:'+server.address().port+'/test/ui.html';
        process.exitCode=await new Promise((resolve,reject)=>{
            const child=spawn(process.execPath,[path.join(__dirname,'run_ui_browser.js'),runner.browserPath(),url,
                path.resolve(__dirname,'../../artifacts/test-results/web/mvc-gallery.json'),'pdg-mvc-gallery'],{stdio:'inherit'});
            child.on('error',reject);child.on('exit',code=>resolve(code===null ? 1 : code));
        });
    } finally { server.close(); }
})().catch(error=>{console.error(error);process.exitCode=1;});
