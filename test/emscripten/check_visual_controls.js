'use strict';
const fs = require('fs');
const path = require('path');
const {spawn} = require('child_process');
const runner = require('../lib/test_runner');
(async function() {
    const server = await runner.serve();
    try {
        const dir = path.resolve(__dirname, '../../artifacts/test-results/web/runner');
        fs.mkdirSync(dir, {recursive:true});
        const url = 'http://127.0.0.1:' + server.address().port + '/test/ui.html?interactive=1&kind=ui&suites=shape-fill&page=8';
        process.exitCode = await new Promise((resolve, reject) => {
            const child = spawn(process.execPath, [path.join(__dirname,'run_ui_browser.js'), runner.browserPath(), url,
                path.join(dir,'controls.json'), 'pdg-visual-controls'], {stdio:'inherit'});
            child.on('error',reject); child.on('exit',code => resolve(code === null ? 1 : code));
        });
    } finally { server.close(); }
})().catch(error => { console.error(error); process.exitCode=1; });
