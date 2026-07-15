#!/usr/bin/env node
// Simple utility to compare Bunnymark results

var fs = require('fs');
var path = require('path');

var baselineFile = 'test/perf/bunnymark/bunnymark_baseline.json';
var currentFile = 'test/perf/bunnymark/bunnymark_results.json';

// Allow custom file paths
if (process.argv.length > 2) {
    baselineFile = process.argv[2];
}
if (process.argv.length > 3) {
    currentFile = process.argv[3];
}

console.log('='.repeat(70));
console.log('BUNNYMARK COMPARISON');
console.log('='.repeat(70));

try {
    var baseline = JSON.parse(fs.readFileSync(baselineFile, 'utf8'));
    var current = JSON.parse(fs.readFileSync(currentFile, 'utf8'));
    
    console.log('\nBaseline: ' + new Date(baseline.timestamp).toLocaleString());
    console.log('Current:  ' + new Date(current.timestamp).toLocaleString());
    
    console.log('\n' + '-'.repeat(70));
    console.log('KEY METRICS');
    console.log('-'.repeat(70));
    
    // Helper to calculate improvement
    function improvement(baseVal, currVal) {
        var diff = currVal - baseVal;
        var pct = (diff / baseVal) * 100;
        var arrow = diff > 0 ? '↑' : diff < 0 ? '↓' : '=';
        var color = diff > 0 ? '+' : '';
        return color + diff.toFixed(0) + ' (' + arrow + pct.toFixed(1) + '%)';
    }
    
    function format(label, baseVal, currVal, unit, inverse) {
        var diff = currVal - baseVal;
        var pct = (diff / baseVal) * 100;
        var arrow = diff > 0 ? '↑' : diff < 0 ? '↓' : '=';
        
        // For metrics where lower is better (frame time, dropped frames)
        if (inverse) {
            arrow = diff < 0 ? '↑' : diff > 0 ? '↓' : '=';
        }
        
        console.log('\n' + label + ':');
        console.log('  Baseline: ' + baseVal.toFixed(2) + ' ' + unit);
        console.log('  Current:  ' + currVal.toFixed(2) + ' ' + unit);
        console.log('  Change:   ' + arrow + ' ' + Math.abs(pct).toFixed(1) + '% (' + 
                    (diff >= 0 ? '+' : '') + diff.toFixed(2) + ' ' + unit + ')');
    }
    
    // Main score
    format('Bunnymark Score (Max Sprites @ 60 FPS)',
           baseline.performance.maxBunniesAt60FPS,
           current.performance.maxBunniesAt60FPS,
           'sprites', false);
    
    // Secondary metrics
    format('Max Sprites @ 30 FPS',
           baseline.performance.maxBunniesAt30FPS,
           current.performance.maxBunniesAt30FPS,
           'sprites', false);
    
    format('Average FPS',
           baseline.performance.averageFPS,
           current.performance.averageFPS,
           'fps', false);
    
    format('Mean Frame Time',
           baseline.frameTime.meanMs,
           current.frameTime.meanMs,
           'ms', true);
    
    format('95th Percentile Frame Time',
           baseline.frameTime.percentile95Ms,
           current.frameTime.percentile95Ms,
           'ms', true);
    
    format('99th Percentile Frame Time',
           baseline.frameTime.percentile99Ms,
           current.frameTime.percentile99Ms,
           'ms', true);
    
    format('Dropped Frame Rate',
           baseline.performance.droppedFramePercent,
           current.performance.droppedFramePercent,
           '%', true);
    
    console.log('\n' + '-'.repeat(70));
    console.log('SUMMARY');
    console.log('-'.repeat(70));
    
    var scoreImprovement = ((current.performance.maxBunniesAt60FPS / baseline.performance.maxBunniesAt60FPS) - 1) * 100;
    var fpsImprovement = ((current.performance.averageFPS / baseline.performance.averageFPS) - 1) * 100;
    var frameTimeImprovement = ((baseline.frameTime.meanMs / current.frameTime.meanMs) - 1) * 100;
    
    console.log('\nOverall Performance:');
    if (scoreImprovement > 0) {
        console.log('  ✓ Bunnymark score improved by ' + scoreImprovement.toFixed(1) + '%');
        console.log('  ✓ Can render ' + scoreImprovement.toFixed(0) + '% more sprites at 60 FPS');
    } else if (scoreImprovement < 0) {
        console.log('  ✗ Bunnymark score DECREASED by ' + Math.abs(scoreImprovement).toFixed(1) + '%');
        console.log('  ✗ Performance REGRESSION detected!');
    } else {
        console.log('  = No change in Bunnymark score');
    }
    
    console.log('\nFrame Time:');
    if (frameTimeImprovement > 0) {
        console.log('  ✓ Frame time improved by ' + frameTimeImprovement.toFixed(1) + '%');
        console.log('  ✓ Rendering is faster and more efficient');
    } else if (frameTimeImprovement < 0) {
        console.log('  ✗ Frame time INCREASED by ' + Math.abs(frameTimeImprovement).toFixed(1) + '%');
    } else {
        console.log('  = No change in frame time');
    }
    
    // Expectation check
    console.log('\n' + '-'.repeat(70));
    console.log('OPTIMIZATION SCENARIO TARGETS');
    console.log('-'.repeat(70));
    console.log('\nScenario 1 (Simple Optimizations):');
    console.log('  Target: 2-3x improvement (200-300%)');
    console.log('  Current: ' + scoreImprovement.toFixed(1) + '%');
    if (scoreImprovement >= 200) {
        console.log('  Status: ✓ Target achieved!');
    } else {
        console.log('  Status: ' + (scoreImprovement / 200 * 100).toFixed(0) + '% of target');
    }
    
    console.log('\nScenario 2 (Modern OpenGL):');
    console.log('  Target: 5-10x improvement (500-1000%)');
    console.log('  Current: ' + scoreImprovement.toFixed(1) + '%');
    if (scoreImprovement >= 500) {
        console.log('  Status: ✓ Target achieved!');
    } else {
        console.log('  Status: ' + (scoreImprovement / 500 * 100).toFixed(0) + '% of target');
    }
    
    console.log('\n' + '='.repeat(70) + '\n');
    
} catch (e) {
    console.log('\nError: ' + e.message);
    console.log('\nUsage: node compare_results.js [baseline.json] [current.json]');
    console.log('\nDefault files:');
    console.log('  Baseline: ' + baselineFile);
    console.log('  Current:  ' + currentFile);
    console.log('\nMake sure to run bunnymark.js first to generate results,');
    console.log('and save a baseline with:');
    console.log('  cp test/perf/bunnymark/bunnymark_results.json test/perf/bunnymark/bunnymark_baseline.json');
    console.log('');
    process.exit(1);
}

