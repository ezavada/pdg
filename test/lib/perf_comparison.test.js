'use strict';
const assert = require('assert');
const {catalog, validate} = require('./perf_runner');
const {loadBaseline, compare, format} = require('./perf_comparison');

const baseline = loadBaseline();
const entries = ids => catalog.filter(entry => ids.includes(entry.id));
const reports = target => Object.fromEntries(Object.entries(baseline.targets[target].benchmarks)
    .map(([id, entry]) => [id, structuredClone(entry.data)]));
const summary = (target, ids) => ({target, status:'passed', runtime:baseline.targets[target]?.runtime || process.version, ...baseline.machine,
    benchmarks:ids.map(id => ({id, status:'passed'}))});
const row = (comparison, id, subtest = 'total') => comparison.benchmarks.find(b => b.id === id).rows.find(r => r.id === subtest);

// Pinned artifacts must remain complete, valid reports for every supported reference target.
assert.deepStrictEqual(Object.keys(baseline.targets.native.benchmarks).sort(), catalog.map(e => e.id).sort());
assert.deepStrictEqual(Object.keys(baseline.targets.web.benchmarks).sort(), ['bunnymark','canvasmark','pdgmark']);
for (const target of Object.values(baseline.targets)) {
    for (const entry of catalog) if (target.benchmarks[entry.id]) validate(entry, target.benchmarks[entry.id].data);
}
const native = reports('native');
const all = compare(summary('native', catalog.map(e => e.id)), catalog, baseline, native);
assert.strictEqual(all.benchmarks.length, 8);
assert.deepStrictEqual(all.benchmarks.slice(0,5).map(b => b.rows[0].baseline), [29405,77870,85173,47219,143839]);
assert(all.benchmarks.every(b => b.rows.every(r => r.changePercent === 0)));
assert.deepStrictEqual(all.notes, []);
assert(all.benchmarks.every(b => !b.notes.length));
assert.strictEqual(row(all, 'cpp-pdgmark', 'polygon').baseline, 23135);
assert.strictEqual(row(all, 'cpp-pdgmark', 'alpha').baseline, 43807);
assert.strictEqual(all.benchmarks.find(b => b.id === 'canvasmark').rows.length, 8);

// Use the matching target, including the latest browser CanvasMark ship-fix measurement.
const web = compare(summary('web', ['bunnymark','pdgmark','canvasmark']), entries(['bunnymark','pdgmark','canvasmark']), baseline, reports('web'));
assert.deepStrictEqual(web.benchmarks.map(b => b.rows[0].baseline), [4037,8362,26542]);
assert.strictEqual(row(web, 'pdgmark', 'polygon').baseline, 1265);

// A selected benchmark compares every subtest, retaining signs and percentage precision.
native.pdgmark.tests.polygon.score *= 2;
native.pdgmark.tests.alpha.score /= 2;
const selected = compare(summary('native', ['pdgmark']), entries(['pdgmark']), baseline, native);
assert.strictEqual(selected.benchmarks.length, 1);
assert.strictEqual(row(selected, 'pdgmark', 'polygon').changePercent, 100);
assert.strictEqual(row(selected, 'pdgmark', 'alpha').changePercent, -50);
assert.match(format(selected), /polygon\s+score\s+34,172\s+17,086\s+\+100\.0%/);
assert.match(format(selected), /alpha\s+score\s+9,754\s+19,508\s+-50\.0%/);

// Fixed-work benchmarks preserve timing units and expose every scenario/rig count.
const animation = all.benchmarks.find(b => b.id === 'animation-pipeline');
assert.strictEqual(animation.rows.length, 6);
assert.strictEqual(animation.rows[0].unit, 'us/op');
assert(Math.abs(animation.rows[0].baseline - 10.4806665) < 1e-6);
assert.strictEqual(row(all, 'cpp-collider', 'basic/contacts/sprite').baseline, 1.012782085);
assert.strictEqual(row(all, 'cpp-rig', '100').baseline, 22.285);
native['cpp-rig'].output = native['cpp-rig'].output.replace('22.285', '11.1425');
const faster = compare(summary('native', ['cpp-rig']), entries(['cpp-rig']), baseline, native);
assert.strictEqual(row(faster, 'cpp-rig', '100').changePercent, -50);
assert.match(format(faster), /Times: lower is better/);

// Comparing different conditions is allowed but is made visible in the report.
native.pdgmark.tests.polygon.fixedLoad++;
native.pdgmark.tests.bitmap.requestedSampleSeconds++;
const changed = compare({...summary('native', ['pdgmark']), cpu:'Different CPU', architecture:'x64',
    platform:'linux', runtime:'v26.0.0'}, entries(['pdgmark']), baseline, native);
assert.strictEqual(changed.notes.length, 4);
assert.strictEqual(changed.benchmarks[0].notes.length, 2);
assert.match(format(changed), /polygon: workload, sampling or scoring settings differ/);

// No fabricated native-to-Node comparison and no division by zero.
const node = compare(summary('node', ['animation-pipeline']), entries(['animation-pipeline']), baseline, native);
assert(node.benchmarks[0].rows.every(r => r.current > 0 && r.baseline === null && r.changePercent === null));
assert.match(format(node), /No pinned baseline for target node/);
const zero = structuredClone(baseline);
zero.targets.native.benchmarks.bunnymark.data.compositeScore = 0;
assert.strictEqual(row(compare(summary('native', ['bunnymark']), entries(['bunnymark']), zero, native), 'bunnymark').changePercent, null);

// Failed and unstarted benchmarks still show baseline subsections, never stale current scores.
const failed = compare({target:'native', status:'failed', benchmarks:[{id:'pdgmark', status:'failed', error:'Missing result'}]},
    entries(['pdgmark','cpp-pdgmark']), baseline, native);
assert(failed.benchmarks.every(b => b.rows.every(r => r.current === null && r.baseline > 0 && r.changePercent === null)));
const failureText = format(failed, 'Build failed');
assert.match(failureText, /QuickPDGMark \(JavaScript\) \[FAILED\]/);
assert.match(failureText, /QuickPDGMark \(C\+\+\) \[NOT RUN\]/);
assert.match(failureText, /polygon\s+score\s+--\s+23,135\s+--/);
assert.match(failureText, /Run error: Build failed/);
assert.match(failureText, /Missing result/);

console.log('PASS: pinned Quick baselines, totals/subtests, target selection, timing units and comparison failures');
