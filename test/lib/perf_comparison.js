'use strict';
const fs = require('fs');
const path = require('path');
const measurement = require('../perf_tests/quick');
const baselineFile = path.resolve(__dirname, '../perf_tests/baselines/quick-baseline.json');

function loadBaseline(file = baselineFile) {
    const baseline = JSON.parse(fs.readFileSync(file, 'utf8'));
    if (baseline.schemaVersion !== 1 || !baseline.id || !baseline.targets || !baseline.machine)
        throw Error('Invalid Quick baseline manifest: ' + file);
    for (const target of Object.values(baseline.targets)) {
        for (const entry of Object.values(target.benchmarks)) {
            entry.data = JSON.parse(fs.readFileSync(path.resolve(path.dirname(file), entry.report), 'utf8'));
        }
    }
    return baseline;
}
function settings(object, keys) {
    return Object.fromEntries(keys.map(key => [key, object[key] === undefined ? null : object[key]]));
}
function metrics(entry, data) {
    if (!entry.micro) {
        return [{id:'total', label:'Total', unit:'score', value:data.compositeScore,
            settings:settings(data, ['mode','framePacing','calibration','calibrationTimestamp'])},
        ...entry.tests.map(id => {
            const sample = data.tests[id];
            return {id, label:id, unit:'score', value:sample.score,
                settings:settings(sample, ['fixedLoad','referenceLoad','referenceScore','targetFPS',
                    'referenceFPS','requestedSampleSeconds','warmupSeconds'])};
        })];
    }
    if (entry.id === 'animation-pipeline') {
        return data.results.map(row => ({id:row.name, label:row.name, unit:'us/op',
            value:row.totalSeconds / row.iterations * 1e6,
            settings:{fixture:data.fixture, iterations:row.iterations}}));
    }
    if (entry.id === 'cpp-collider') {
        return data.results.map(row => ({id:[row.solver,row.scenario,row.owner].join('/'),
            label:row.solver + ' / ' + row.scenario, unit:'ms/step', value:row.meanMs,
            settings:{stepSeconds:data.stepSeconds, ...settings(row, ['owner','bodies','colliders','steps',
                'warmup','broadphase','cellSize','iterations','sleepAfterSeconds','constraints'])}}));
    }
    return data.output.split('\n').filter(line => /^\d+,/.test(line)).map(line => {
        const [rigs,parts,,mean] = line.split(',').map(Number);
        return {id:String(rigs), label:rigs + (rigs === 1 ? ' rig' : ' rigs'), unit:'ms/step',
            value:mean, settings:{parts}};
    });
}
function compare(summary, entries, baseline, reports) {
    const target = baseline.targets[summary.target];
    const result = {baselineId:baseline.id, target:summary.target, status:summary.status,
        machine:baseline.machine, notes:[], benchmarks:[]};
    if (!target) result.notes.push('No pinned baseline for target ' + summary.target + '.');
    for (const key of ['platform','architecture','cpu']) {
        if (summary[key] && baseline.machine[key] && summary[key] !== baseline.machine[key])
            result.notes.push(key + ' differs: current ' + summary[key] + ', baseline ' + baseline.machine[key] + '.');
    }
    if (summary.build) result.notes.push('PDG runtime: ' + summary.build.configuration + ' (' + summary.build.kind + ').');
    if (summary.build && target && !target.build)
        result.notes.push('Pinned baseline has no runtime build metadata.');
    if (target && summary.runtime !== target.runtime)
        result.notes.push('Runner runtime differs: current ' + summary.runtime + ', baseline ' + target.runtime + '.');
    for (const entry of entries) {
        const run = summary.benchmarks.find(item => item.id === entry.id);
        const reference = target && target.benchmarks[entry.id];
        const previous = reference ? metrics(entry, reference.data) : [];
        const current = run && run.status === 'passed' && reports[entry.id] ? metrics(entry, reports[entry.id]) : [];
        const comparison = {id:entry.id,
            label:measurement.markName(entry.id) + (entry.micro ? '' : entry.binary ? ' (C++)' : ' (JavaScript)'),
            status:run ? run.status : 'not run', error:run && run.error, notes:[], rows:[]};
        if (!reference) comparison.notes.push('No pinned baseline for this benchmark/target.');
        const ids = [...new Set([...current.map(row => row.id), ...previous.map(row => row.id)])];
        for (const id of ids) {
            const now = current.find(row => row.id === id), before = previous.find(row => row.id === id);
            const row = {id, label:(now || before).label, unit:(now || before).unit,
                current:now ? now.value : null, baseline:before ? before.value : null, changePercent:null};
            if (now && before && Number.isFinite(now.value) && Number.isFinite(before.value) && before.value > 0)
                row.changePercent = (now.value / before.value - 1) * 100;
            if (now && before && JSON.stringify(now.settings) !== JSON.stringify(before.settings))
                comparison.notes.push(row.label + ': workload, sampling or scoring settings differ from baseline.');
            comparison.rows.push(row);
        }
        result.benchmarks.push(comparison);
    }
    return result;
}
function format(comparison, error) {
    const lines = ['', 'Quick performance summary — ' + comparison.target + ': ' + comparison.status.toUpperCase()];
    lines.push('Baseline: ' + comparison.baselineId + (comparison.machine.cpu ? ' (' + comparison.machine.cpu + ', ' +
        comparison.machine.platform + '/' + comparison.machine.architecture + ')' : ''));
    lines.push('Scores: higher is better. Times: lower is better. Change = 100 × (current / baseline - 1)%.');
    const table = [['Benchmark / subtest','Unit','Current','Baseline','Change']];
    const number = (value, unit) => value === null ? '--' : value.toLocaleString('en-US',
        {minimumFractionDigits:unit === 'score' ? 0 : 3, maximumFractionDigits:unit === 'score' ? 0 : 3});
    const percent = value => value === null ? '--' : Math.abs(value) < 0.05 ? '0.0%'
        : (value > 0 ? '+' : '') + value.toFixed(1) + '%';
    for (const benchmark of comparison.benchmarks) {
        const total = benchmark.rows.find(row => row.id === 'total');
        const values = row => [row.unit, number(row.current,row.unit), number(row.baseline,row.unit), percent(row.changePercent)];
        table.push([benchmark.label + (benchmark.status === 'passed' ? '' : ' [' + benchmark.status.toUpperCase() + ']'),
            ...(total ? values(total) : ['', '', '', ''])]);
        benchmark.rows.filter(row => row.id !== 'total').forEach(row => table.push(['  ' + row.label, ...values(row)]));
    }
    const widths = table[0].map((_, i) => Math.max(...table.map(row => row[i].length)));
    const render = row => row.map((cell,i) => i < 2 ? cell.padEnd(widths[i]) : cell.padStart(widths[i])).join('  ').trimEnd();
    lines.push('', render(table[0]), widths.map(width => '-'.repeat(width)).join('  '), ...table.slice(1).map(render));
    if (error) lines.push('', 'Run error: ' + error);
    const notes = [...comparison.notes];
    for (const benchmark of comparison.benchmarks) {
        if (benchmark.error) notes.push(benchmark.label + ': ' + benchmark.error);
        notes.push(...benchmark.notes.map(note => benchmark.label + ': ' + note));
    }
    if (notes.length) lines.push('', ...notes.map(note => 'Note: ' + note));
    return lines.join('\n') + '\n';
}
module.exports = {loadBaseline, metrics, compare, format};
