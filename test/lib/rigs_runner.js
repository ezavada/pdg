'use strict';
const fs = require('fs');
const path = require('path');
const cp = require('child_process');
const root = path.resolve(__dirname, '../..');
const testDir = path.join(root, 'test/rig_tests');

function catalog() {
    const tests = [];
    for (const rig of fs.readdirSync(testDir, {withFileTypes:true})) {
        if (!rig.isDirectory()) continue;
        for (const file of fs.readdirSync(path.join(testDir, rig.name))) {
            if (!file.endsWith('.test.js')) continue;
            tests.push({id:rig.name + '/' + file.slice(0, -8), rig:rig.name,
                file:path.join(testDir, rig.name, file)});
        }
    }
    return tests.sort((a, b) => a.id.localeCompare(b.id));
}

function main(args) {
    if (args.includes('--help') || args.includes('-h')) {
        console.log('Usage: test/rigs [--list] [rig | rig/check ...]\n' +
            'Runs all rig checks by default, each in a separate Node process.\n' +
            'Examples: test/rigs human; test/rigs human/ground human/pose\n' +
            'Requires a built PDG Node addon with Chipmunk physics.\n' +
            'Node: PDG_NODE, tools/node, then node on PATH.');
        return 0;
    }
    const tests = catalog();
    const names = args.filter(arg => arg !== '--list');
    for (const name of names) {
        if (!tests.some(test => test.id === name || test.rig === name)) {
            throw Error('Unknown rig or check: ' + name + '. Use --list.');
        }
    }
    const selected = tests.filter(test => !names.length || names.includes(test.id) || names.includes(test.rig));
    if (!selected.length) throw Error('No rig checks found in ' + testDir);
    if (args.includes('--list')) {
        selected.forEach(test => console.log(test.id));
        return 0;
    }
    process.env.PDG_ROOT = root;
    process.env.PDG_TEST_MODE = 'rigs';
    process.env.PDG_TEST_PLATFORM = process.platform;
    const env = require('./spec_runner').ensureTestEnvironment(process, fs);
    const childEnv = {...process.env};
    for (const name of ['PDG_NO_AUTO_EXIT', 'PDG_AUTO_EXIT_TIMEOUT', 'PDG_ORIGINAL_ARGS',
        'PDG_PERF_UNCAPPED', 'NODE_OPTIONS']) delete childEnv[name];
    const results = [];
    for (const test of selected) {
        const logPath = path.join(env.logDir, test.rig, path.basename(test.file, '.test.js') + '.log');
        fs.mkdirSync(path.dirname(logPath), {recursive:true});
        const log = fs.openSync(logPath, 'w');
        const start = Date.now();
        let failure;
        console.log('RUN  ' + test.id);
        try {
            const result = cp.spawnSync(process.execPath, [test.file], {
                cwd:root, env:childEnv, stdio:['ignore', log, log], timeout:180000, killSignal:'SIGKILL'
            });
            if (result.error || result.signal || result.status !== 0) {
                failure = result.error ? result.error.message : result.signal || 'exit ' + result.status;
            }
        } catch (error) {
            failure = error.message;
        } finally {
            fs.closeSync(log);
        }
        const output = fs.readFileSync(logPath, 'utf8');
        if (!failure && !/^PASS:/m.test(output)) failure = 'Exited without a PASS: completion marker';
        if (failure) fs.appendFileSync(logPath, '\n' + failure + '\n');
        if (output) process.stdout.write(output);
        const status = failure ? 'failed' : 'passed';
        results.push({id:test.id, status, durationMs:Date.now() - start, log:logPath,
            ...(failure ? {error:failure} : {})});
        console.log((failure ? 'FAIL ' : 'PASS ') + test.id + (failure ? ': ' + failure : ''));
    }
    const failed = results.filter(result => result.status === 'failed').length;
    const passed = results.length - failed;
    const report = path.join(env.reportDir, 'summary.json');
    fs.writeFileSync(report, JSON.stringify({status:failed ? 'failed' : 'passed',
        platform:process.platform, node:process.version, passed, failed, tests:results}, null, 2) + '\n');
    console.log('\nRigs: ' + passed + ' passed, ' + failed + ' failed.\nReport: ' + report);
    return failed ? 1 : 0;
}

if (require.main === module) {
    try { process.exitCode = main(process.argv.slice(2)); }
    catch (error) { console.error('Error: ' + error.message); process.exitCode = 2; }
}
