// Native graphics subprocess fixture, exercised by test/unit node_runtime.
// Check the Quick override independently of rendering cost and display refresh.
'use strict';
const pdg = require('pdg');
const quick = require('../../perf_tests/quick');
function fail(message) { console.error('FAIL: ' + message); process.exit(1); }
const first = pdg.gfx.createWindowPort(new pdg.Rect(160, 120), 'Quick pacing check');
const counts = new Map([[first, 0]]);
pdg.gfx.setTargetFPS(5);
pdg.on(pdg.eventType_PortDraw, event => {
    if (counts.has(event.port)) counts.set(event.port, counts.get(event.port) + 1);
    return false;
});
pdg.tm.onTimeout(() => {
    const cappedFrames = counts.get(first);
    if (cappedFrames < 1 || cappedFrames > 4) return fail('Ordinary 5 FPS limit was not respected: ' + cappedFrames);
    quick.uncap();
    counts.set(first, 0);
    const second = pdg.gfx.createWindowPort(new pdg.Rect(160, 120), 'Quick pacing second window');
    counts.set(second, 0);
    pdg.tm.onTimeout(() => {
        if (pdg.gfx.getTargetFPS() !== 5) return fail('Quick override changed the configured target FPS');
        for (const frames of counts.values())
            if (frames <= 4) return fail('Quick mode still obeyed the 5 FPS limit: ' + frames);
        console.log('PASS: ordinary frame limit, Quick bypass, existing and new windows: ' +
            JSON.stringify({cappedFrames, quickFrames:Array.from(counts.values())}));
        pdg.quit();
    }, 500);
}, 500);
pdg.run();
