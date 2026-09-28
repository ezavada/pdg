'use strict';
const cp = require('child_process');
const fs = require('fs');
const path = require('path');
const optionsAPI = require('./test_options');

exports.run = async function(options, pages, env) {
    const args = ['--prepare'];
    if (options.iphone) args.push('--iphone');
    if (options.ipad) args.push('--ipad');
    if (options['no-build']) args.push('--no-build');
    console.log('Preparing iOS Simulator (incremental build and install)…');
    const prepare = cp.spawnSync(path.join(__dirname, '../ios'), args, {encoding:'utf8', maxBuffer: 16 * 1024 * 1024});
    process.stdout.write(prepare.stdout || '');
    process.stderr.write(prepare.stderr || '');
    if (prepare.error) throw prepare.error;
    if (prepare.status) return prepare.status;
    const match = prepare.stdout.match(/PDG_IOS_PREPARED=([0-9A-F-]+)/);
    if (!match) throw Error('iOS preparation did not report a simulator.');
    const device = match[1];
    cp.spawnSync('open', ['-a', 'Simulator', '--args', '-CurrentDeviceUDID', device]);
    let index = optionsAPI.pageIndex(pages, options.page);
    while (true) {
        const page = pages[index];
        const title = (index + 1) + '/' + pages.length + '  ' + page.id;
        const outcome = await new Promise((resolve, reject) => {
            const log = fs.createWriteStream(path.join(env.logDir, 'ios-visual.log'));
            let tail = '', action = null;
            const app = cp.spawn('xcrun', ['simctl', 'launch', '--terminate-running-process', '--console-pty', device,
                'com.dreamrockstudios.pdg-js-test', '--visual-page', page.suite, String(page.localPage), title, '--wait']);
            function output(data) {
                log.write(data); process.stdout.write(data);
                tail = (tail + data.toString()).slice(-8192);
                const found = tail.match(/\[PDG VISUAL ACTION\] (next|previous|quit)/);
                if (found) action = found[1];
            }
            app.stdout.on('data', output); app.stderr.on('data', output);
            app.on('error', reject);
            app.on('exit', code => { log.end(); resolve({action, code}); });
        });
        if (outcome.action === 'quit') return 0;
        if (!outcome.action) return outcome.code || 1;
        index = (index + (outcome.action === 'next' ? 1 : -1) + pages.length) % pages.length;
    }
};
