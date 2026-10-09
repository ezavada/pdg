'use strict';
const fs = require('fs');
const path = require('path');
const cp = require('child_process');
const root = path.resolve(__dirname, '../..');
const catalog = [
    {id:'ios-network-transport', file:'ios_network_transport.test.js'},
    {id:'network-transport', file:'network_transport.test.js'},
    {id:'webtransport', file:'webtransport.test.js'},
    {id:'api-contracts', file:'api_contracts.test.js'},
    {id:'interface-metadata', file:'interface_metadata.test.js'},
    {id:'emscripten-generation', file:'emscripten_generation.test.js'},
    {id:'test-options', file:'test_options.test.js'},
    {id:'unit-output', file:'unit_output.test.js'},
    {id:'node-build', file:'node_build.test.js', posix:true},
    {id:'wasm-release', file:'wasm_release.test.js', posix:true},
    {id:'perf-runner', file:'perf_runner.test.js'},
    {id:'perf-comparison', file:'perf_comparison.test.js'},
    {id:'perf-measurement', file:'perf_measurement.test.cpp', cpp:true}
];

function main(args) {
    if (args.includes('--help') || args.includes('-h')) {
        console.log('Usage: test/tools [--list] [suite ...]\n' +
            'Runs tooling checks without a PDG build. No suites selects all suites.\n' +
            'Node: PDG_NODE, tools/node, then node on PATH.\n' +
            'C++20 compiler: CXX (executable path), otherwise c++ or Windows cl.exe.\n' +
            'node-build and wasm-release require POSIX Bash and are skipped on Windows.\n' +
            'wasm-release also requires make, CMake and Python 3.');
        return 0;
    }
    const names = args.filter(arg => arg !== '--list');
    names.forEach(name => {
        if (!catalog.some(entry => entry.id === name)) throw Error('Unknown tools suite: ' + name + '. Use --list.');
    });
    const selected = names.length ? [...new Set(names)].map(name => catalog.find(entry => entry.id === name)) : catalog;
    if (args.includes('--list')) {
        selected.forEach(entry => console.log(entry.id + (entry.posix ? ' (POSIX only)' : '')));
        return 0;
    }
    process.env.PDG_ROOT = root;
    process.env.PDG_TEST_MODE = 'tools';
    process.env.PDG_TEST_PLATFORM = process.platform;
    const env = require('./spec_runner').ensureTestEnvironment(process, fs);
    const results = [];
    for (const entry of selected) {
        if (entry.posix && process.platform === 'win32') {
            const reason = 'Tests the POSIX Bash build helper; not supported by native Windows.';
            console.log('SKIP ' + entry.id + ': ' + reason);
            results.push({id:entry.id, status:'skipped', reason});
            continue;
        }
        const logPath = path.join(env.logDir, entry.id + '.log');
        const log = fs.openSync(logPath, 'w');
        let temporary;
        let failure;
        function run(command, argv, cwd) {
            const result = cp.spawnSync(command, argv, {
                cwd:cwd || root, stdio:['ignore', log, log], timeout:120000, killSignal:'SIGKILL'
            });
            if (result.error || result.signal || result.status !== 0) {
                throw Error(command + ': ' + (result.error ? result.error.message :
                    result.signal || 'exit ' + result.status));
            }
        }
        console.log('RUN  ' + entry.id);
        try {
            if (entry.cpp) {
                temporary = fs.mkdtempSync(path.join(env.tempDir, 'perf-measurement-'));
                const compiler = process.env.CXX || (process.platform === 'win32' ? 'cl.exe' : 'c++');
                const binary = path.join(temporary, process.platform === 'win32' ? 'measurement.exe' : 'measurement');
                const source = path.join(__dirname, entry.file);
                const msvc = /^(cl|clang-cl)(\.exe)?$/i.test(path.basename(compiler));
                run(compiler, msvc ? ['/nologo', '/std:c++20', '/EHsc', '/UNDEBUG', source, '/Fe:' + binary] :
                    ['-std=c++20', '-UNDEBUG', source, '-o', binary], temporary);
                run(binary, [], temporary);
            } else {
                run(process.execPath, [path.join(__dirname, entry.file)]);
            }
        } catch (error) {
            failure = error.message;
            fs.writeSync(log, '\n' + failure + '\n');
        } finally {
            fs.closeSync(log);
            if (temporary) fs.rmSync(temporary, {recursive:true, force:true});
        }
        const output = fs.readFileSync(logPath, 'utf8');
        if (output) process.stdout.write(output);
        const status = failure ? 'failed' : 'passed';
        results.push({id:entry.id, status, log:logPath, ...(failure ? {error:failure} : {})});
        console.log((failure ? 'FAIL ' : 'PASS ') + entry.id);
    }
    const counts = {passed:0, failed:0, skipped:0};
    results.forEach(result => { ++counts[result.status]; });
    const report = path.join(env.reportDir, 'summary.json');
    fs.writeFileSync(report, JSON.stringify({status:counts.failed ? 'failed' : 'passed',
        platform:process.platform, node:process.version, ...counts, tests:results}, null, 2) + '\n');
    console.log('\nTooling: ' + counts.passed + ' passed, ' + counts.failed + ' failed, ' + counts.skipped + ' skipped.\nReport: ' + report);
    return counts.failed ? 1 : 0;
}

if (require.main === module) {
    try { process.exitCode = main(process.argv.slice(2)); }
    catch (error) { console.error('Error: ' + error.message); process.exitCode = 2; }
}
