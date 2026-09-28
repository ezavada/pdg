#!/usr/bin/env node
'use strict';
const fs = require('fs');
const path = require('path');
const os = require('os');
const cp = require('child_process');
const runner = require('./test_runner');
const builds = require('./perf_build');
const comparison = require('./perf_comparison');
const measurement = require('../perf_tests/quick');
const root = path.resolve(__dirname, '../..');
const catalog = [
    {id:'bunnymark', script:'bunnymark/bunnymark.js', tests:['bunnies']},
    {id:'pdgmark', script:'pdgmark/pdgmark.js', tests:['bitmap','drawing','alpha','polygon','text']},
    {id:'canvasmark', script:'canvasmark2013/canvasmark.js', tests:['asteroids-bitmaps','asteroids-vectors','asteroids-mixed','asteroids-effects','arena','plasma','3d']},
    {id:'cpp-bunnymark', binary:'bunnymark', tests:['bunnies']},
    {id:'cpp-pdgmark', binary:'pdgmark', tests:['bitmap','drawing','alpha','polygon','text']},
    {id:'animation-pipeline', script:'animation_pipeline.js', micro:true},
    {id:'cpp-collider', binary:'pdg-collider-perf', micro:true},
    {id:'cpp-rig', binary:'pdg-rig-perf', micro:true}
];
function parse(args) {
    const options = Object.assign({kind:'perf', target:'native', suites:[]}, measurement.options(args));
    for (let i = 0; i < args.length; ++i) {
        const arg = args[i];
        if (['--sample-seconds','--warmup-seconds','--load-factor'].includes(arg)) { ++i; continue; }
        if (['--quick','--no-build','--verbose','--list'].includes(arg)) options[arg.slice(2)] = true;
        else if (['--help','-h','/?'].includes(arg)) options.help = true;
        else if (['--web','--emscripten','--node'].includes(arg)) {
            const target = arg === '--emscripten' ? 'web' : arg.slice(2);
            if (options.target !== 'native' && options.target !== target) throw Error('Choose one target.');
            options.target = target;
        } else if (arg.startsWith('-')) throw Error('Unknown option: ' + arg);
        else options.suites.push(arg);
    }
    options.quick = true; // The top-level command always uses short fixed loads.
    const available = catalog.filter(entry => options.target === 'native' ||
        (!entry.binary && (options.target !== 'web' || !entry.micro)));
    options.suites.forEach(id => {
        if (!available.some(entry => entry.id === id)) throw Error('Unknown/unavailable benchmark: ' + id + '. Use --list.');
    });
    options.entries = available.filter(entry => !options.suites.length || options.suites.includes(entry.id));
    return options;
}
function execute(command, args, log, timeout, verbose) {
    return new Promise((resolve, reject) => {
        const out = fs.openSync(log + '.stdout.log', 'w'), err = fs.openSync(log + '.stderr.log', 'w');
        const child = cp.spawn(command, args, {cwd:root, env:process.env, stdio:['ignore','pipe','pipe']});
        let timedOut = false;
        const timer = setTimeout(() => { timedOut = true; child.kill('SIGKILL'); }, timeout);
        child.stdout.on('data', data => { fs.writeSync(out, data); if (verbose) process.stdout.write(data); });
        child.stderr.on('data', data => { fs.writeSync(err, data); if (verbose) process.stderr.write(data); });
        child.on('error', reject);
        child.on('close', (code, signal) => {
            clearTimeout(timer); fs.closeSync(out); fs.closeSync(err);
            if (timedOut) reject(Error('Timed out after ' + timeout / 1000 + 's'));
            else if (code !== 0) reject(Error('Exited with ' + (signal || code)));
            else resolve();
        });
    });
}
function validate(entry, result) {
    if (entry.id === 'cpp-rig') {
        const rows = String(result.output || '').split('\n').filter(line => /^\d+,/.test(line)).map(line => line.split(',').map(Number));
        if (rows.length !== 4 || rows.some((row, i) => row.length !== 7 || row[0] !== [1,10,50,100][i] ||
            row.some(value => !Number.isFinite(value) || value < 0) || row[3] <= 0)) throw Error('Incomplete rig throughput results');
        return;
    }
    if (entry.micro) {
        const animation = entry.id === 'animation-pipeline';
        if (!Array.isArray(result.results) || result.results.length !== (animation ? 6 : 4) ||
            result.results.some(row => !(row[animation ? 'iterations' : 'steps'] > 0) ||
                !Number.isFinite(row[animation ? 'totalSeconds' : 'meanMs']) || row[animation ? 'totalSeconds' : 'meanMs'] <= 0))
            throw Error('Incomplete throughput results');
        return;
    }
    if (result.mode !== 'quick' || result.testName !== measurement.markName(entry.id) ||
        result.benchmarkId !== entry.id || result.synthetic !== true || !result.tests)
        throw Error('Missing quick benchmark result');
    if (Object.keys(result.tests).length !== entry.tests.length) throw Error('Incomplete subtest results');
    let score = 0;
    entry.tests.forEach(id => {
        const test = result.tests[id];
        if (!test || !Number.isFinite(test.averageFPS) || test.averageFPS <= 0 ||
            !Number.isFinite(test.score) || test.score < 0 || test.totalFrames < 2 ||
            !(test.durationSeconds >= test.requestedSampleSeconds) || !(test.fixedLoad > 0))
            throw Error('Invalid/incomplete sample: ' + id);
        score += test.score;
    });
    if (score !== result.compositeScore) throw Error('Composite score does not match subtests');
}
async function main(args) {
    const started = Date.now();
    const options = parse(args);
    if (options.help) {
        console.log('Usage: ./test/perf [--quick] [--web|--node] [--list] [--no-build] [--verbose] [benchmark ...]\n' +
            '  --load-factor N      fixed load / recorded capacity (default 1.5)\n' +
            '  --warmup-seconds N   warm-up per rendering subtest (default 1)\n' +
            '  --sample-seconds N   sampling per rendering subtest (default 3)\n' +
            'Always uses --quick: QuickBunnyMark, QuickPDGMark and QuickCanvasMark.\n' +
            'Native runs C++ and JavaScript; --web runs the three JS rendering marks.\n' +
            'Builds Release runtimes incrementally; --no-build requires an existing release build.\n' +
            'Every run ends with totals and subtests compared with the pinned Quick baseline.\n' +
            'Fixed-work animation/collider/rig benchmarks retain their own throughput units.'); return 0;
    }
    if (options.list) { options.entries.forEach(e => console.log(e.id + (e.micro ? ' (fixed-work throughput)' : ' (' + measurement.markName(e.id) + ')'))); return 0; }
    const env = runner.envFor(options);
    const summaryFile = path.join(env.reportDir, 'summary.json');
    const comparisonFile = path.join(env.reportDir, 'comparison.txt');
    const summary = {status:'running', mode:'quick', target:options.target, timestamp:new Date().toISOString(),
        runtime:process.version, platform:process.platform, architecture:process.arch,
        cpu:os.cpus()[0]?.model, osRelease:os.release(), benchmarks:[]};
    const reports = Object.create(null);
    const save = () => fs.writeFileSync(summaryFile, JSON.stringify(summary, null, 2) + '\n');
    save();
    let server;
    try {
        let runtime;
        if (options.target === 'native') runtime = builds.native(options, options.entries.filter(e => e.binary).map(e => e.binary));
        else if (options.target === 'node') {
            runtime = builds.node(options);
            if (!runtime.hasGraphics && options.entries.some(entry => !entry.micro))
                throw Error('The release Node plugin has no graphics. Use native GUI or --web for rendering marks, or --node animation-pipeline.');
        } else {
            runner.buildWeb(options, 'release');
            runtime = {configuration:'Release', kind:'emscripten', artifact:'build/wasm/wasm32/release/libpdg.js'};
            server = await runner.serve();
        }
        summary.build = runtime;
        save();
        for (const entry of options.entries) {
            const report = path.join(env.reportDir, entry.id + '.json');
            const log = path.join(env.logDir, entry.id);
            fs.rmSync(report, {force:true});
            const label = measurement.markName(entry.id) + (entry.micro ? '' : entry.binary ? ' (C++)' : ' (JavaScript)');
            const result = {id:entry.id, testName:measurement.markName(entry.id), status:'running', report, log};
            const benchmarkStarted = Date.now();
            summary.benchmarks.push(result);
            save();
            try {
                let command, argv;
                const flags = ['--quick', '--sample-seconds', String(options.seconds), '--warmup-seconds',
                    String(options.warmup), '--load-factor', String(options.factor), '--output', report];
                const timeout = Math.ceil(Math.max(60000, ((entry.tests || []).length * (options.seconds + options.warmup) + 45) * 1000));
                if (server) {
                    const query = new URLSearchParams({test:entry.id, quick:'1', 'sample-seconds':options.seconds,
                        'warmup-seconds':options.warmup, 'load-factor':options.factor});
                    command = process.execPath;
                    argv = [path.join(root, 'test/emscripten/run_ui_browser.js'), runner.browserPath(),
                        'http://127.0.0.1:' + server.address().port + '/test/perf.html?' + query,
                        report + '.html', 'pdg-perf-result-json', String(timeout), '--headed', '--perf-uncapped'];
                } else if (entry.binary) {
                    command = builds.binary(runtime.directory, entry.binary);
                    argv = entry.id === 'cpp-collider' ? ['--quick', '--steps','200','--json',report]
                        : entry.id === 'cpp-rig' ? ['--quick'] : flags;
                } else {
                    command = runtime.executable;
                    argv = [path.join(root, 'test/perf_tests', entry.script), ...flags];
                }
                console.log('RUN ' + label);
                await execute(command, argv, log, timeout + 5000, options.verbose);
                if (server) {
                    const lines = fs.readFileSync(log + '.stdout.log', 'utf8').trim().split('\n');
                    const envelope = JSON.parse(lines[lines.length - 1]);
                    if (envelope.status !== 'passed') throw Error('Browser benchmark failed');
                    fs.writeFileSync(report, JSON.stringify(Object.assign(envelope.results,
                        {engine:envelope.engine, userAgent:envelope.userAgent, wasmHeapBytes:envelope.wasmHeapBytes}), null, 2) + '\n');
                } else if (entry.id === 'cpp-rig') {
                    fs.writeFileSync(report, JSON.stringify({testName:entry.id, format:'csv',
                        output:fs.readFileSync(log + '.stdout.log', 'utf8')}, null, 2));
                }
                const data = JSON.parse(fs.readFileSync(report, 'utf8'));
                validate(entry, data);
                data.build = entry.binary ? {configuration:'Release', kind:'native-cpp',
                    executable:command, resolvedExecutable:fs.realpathSync(command), directory:runtime.directory} : runtime;
                fs.writeFileSync(report, JSON.stringify(data, null, 2) + '\n');
                reports[entry.id] = data;
                result.status = 'passed';
                if (!entry.micro) result.syntheticScore = data.compositeScore;
                console.log('PASS ' + label + (entry.micro ? '' : ' — score ' + data.compositeScore));
                if (!entry.micro) {
                    result.aboveTargetFPS = Object.keys(data.tests).filter(id => data.tests[id].atOrAboveTarget);
                }
            } catch (error) { result.status = 'failed'; result.error = error.message; console.error('FAIL ' + entry.id + ': ' + error.message + '\nLogs: ' + log + '.*.log'); }
            result.durationSeconds = (Date.now() - benchmarkStarted) / 1000;
            save();
        }
        summary.status = summary.benchmarks.every(r => r.status === 'passed') ? 'passed' : 'failed';
    } catch (error) { summary.status = 'failed'; summary.error = error.message; console.error(error.message); }
    finally {
        if (server) await new Promise(resolve => server.close(resolve));
        summary.durationSeconds = (Date.now() - started) / 1000;
        try {
            summary.comparison = comparison.compare(summary, options.entries, comparison.loadBaseline(), reports);
        } catch (error) {
            summary.comparison = comparison.compare(summary, options.entries,
                {id:'unavailable', machine:{}, targets:{}}, reports);
            summary.comparison.notes.unshift('Cannot read pinned Quick baseline: ' + error.message);
        }
        const closingSummary = comparison.format(summary.comparison, summary.error);
        fs.writeFileSync(comparisonFile, closingSummary);
        summary.comparisonReport = comparisonFile;
        save();
        console.log(closingSummary);
    }
    console.log('Report: ' + summaryFile);
    return summary.status === 'passed' ? 0 : 1;
}
module.exports = {main, parse, validate, catalog};
if (require.main === module) main(process.argv.slice(2)).then(code => { process.exitCode = code; })
    .catch(error => { console.error(error.message); process.exitCode = 2; });
