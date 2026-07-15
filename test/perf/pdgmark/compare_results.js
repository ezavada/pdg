#!/usr/bin/env node
// Compare PDGMark results before/after optimizations

var fs = require('fs');
var path = require('path');

var baselineFile = 'test/perf/pdgmark/pdgmark_baseline.json';
var currentFile = 'test/perf/pdgmark/pdgmark_results.json';

// Allow custom file paths
if (process.argv.length > 2) {
    baselineFile = process.argv[2];
}
if (process.argv.length > 3) {
    currentFile = process.argv[3];
}

console.log('='.repeat(70));
console.log('PDGMARK COMPARISON');
console.log('='.repeat(70));

try {
    var baseline = JSON.parse(fs.readFileSync(baselineFile, 'utf8'));
    var current = JSON.parse(fs.readFileSync(currentFile, 'utf8'));
    
    console.log('\nBaseline: ' + new Date(baseline.timestamp).toLocaleString());
    console.log('Current:  ' + new Date(current.timestamp).toLocaleString());
    
    // Helper functions
    function improvement(baseVal, currVal) {
        var diff = currVal - baseVal;
        var pct = (diff / baseVal) * 100;
        return pct;
    }
    
    function formatChange(pct) {
        var arrow = pct > 0 ? '↑' : pct < 0 ? '↓' : '=';
        var sign = pct > 0 ? '+' : '';
        return arrow + ' ' + sign + pct.toFixed(1) + '%';
    }
    
    function format(label, baseVal, currVal, unit, inverse) {
        var diff = currVal - baseVal;
        var pct = (diff / baseVal) * 100;
        var arrow = diff > 0 ? '↑' : diff < 0 ? '↓' : '=';
        
        // For metrics where lower is better (frame time)
        if (inverse) {
            arrow = diff < 0 ? '↑' : diff > 0 ? '↓' : '=';
        }
        
        console.log('\n' + label + ':');
        console.log('  Baseline: ' + baseVal.toFixed(1) + ' ' + unit);
        console.log('  Current:  ' + currVal.toFixed(1) + ' ' + unit);
        console.log('  Change:   ' + arrow + ' ' + Math.abs(pct).toFixed(1) + '% (' + 
                    (diff >= 0 ? '+' : '') + diff.toFixed(1) + ' ' + unit + ')');
    }
    
    // ============================================
    // COMPOSITE SCORE
    // ============================================
    
    console.log('\n' + '-'.repeat(70));
    console.log('COMPOSITE SCORE');
    console.log('-'.repeat(70));
    
    format('PDGMark Composite Score',
           baseline.compositeScore,
           current.compositeScore,
           'points', false);
    
    var compositeImprovement = improvement(baseline.compositeScore, current.compositeScore);
    
    // ============================================
    // PER-TEST COMPARISON
    // ============================================
    
    console.log('\n' + '-'.repeat(70));
    console.log('INDIVIDUAL TEST SCORES');
    console.log('-'.repeat(70));
    
    var testNames = ['bitmap', 'drawing', 'alpha', 'polygon', 'text'];
    var testTitles = {
        bitmap: 'Bitmap Rendering',
        drawing: 'Canvas Drawing',
        alpha: 'Alpha Blending',
        polygon: 'Polygon Fills',
        text: 'Text Rendering'
    };
    
    for (var i = 0; i < testNames.length; i++) {
        var testName = testNames[i];
        var baseTest = baseline.tests[testName];
        var currTest = current.tests[testName];
        
        if (!baseTest || !currTest) {
            console.log('\n' + testTitles[testName] + ': Missing data');
            continue;
        }
        
        console.log('\n' + (i+1) + '. ' + testTitles[testName]);
        
        var objImprovement = improvement(baseTest.objectsAt60FPS, currTest.objectsAt60FPS);
        var scoreImprovement = improvement(baseTest.score, currTest.score);
        var fpsImprovement = improvement(baseTest.averageFPS, currTest.averageFPS);
        var frameTimeImprovement = improvement(currTest.frameTime.meanMs, baseTest.frameTime.meanMs); // Inverted
        
        console.log('  Objects @ 6 0 FPS: ' + 
                    baseTest.objectsAt60FPS + ' → ' + currTest.objectsAt60FPS + 
                    ' (' + formatChange(objImprovement) + ')');
        console.log('  Score:            ' + 
                    baseTest.score + ' → ' + currTest.score + 
                    ' (' + formatChange(scoreImprovement) + ')');
        console.log('  Avg FPS:          ' + 
                    baseTest.averageFPS.toFixed(1) + ' → ' + currTest.averageFPS.toFixed(1) + 
                    ' (' + formatChange(fpsImprovement) + ')');
        console.log('  Frame Time:       ' + 
                    baseTest.frameTime.meanMs.toFixed(2) + 'ms → ' + currTest.frameTime.meanMs.toFixed(2) + 'ms' + 
                    ' (' + formatChange(frameTimeImprovement) + ')');
    }
    
    // ============================================
    // SUMMARY
    // ============================================
    
    console.log('\n' + '-'.repeat(70));
    console.log('SUMMARY');
    console.log('-'.repeat(70));
    
    console.log('\nOverall Performance:');
    if (compositeImprovement > 0) {
        console.log('  ✓ Composite score improved by ' + compositeImprovement.toFixed(1) + '%');
        console.log('  ✓ Overall 2D rendering performance increased');
    } else if (compositeImprovement < 0) {
        console.log('  ✗ Composite score DECREASED by ' + Math.abs(compositeImprovement).toFixed(1) + '%');
        console.log('  ✗ Performance REGRESSION detected!');
    } else {
        console.log('  = No change in composite score');
    }
    
    // Find best and worst improvements
    var improvements = [];
    for (var i = 0; i < testNames.length; i++) {
        var testName = testNames[i];
        var baseTest = baseline.tests[testName];
        var currTest = current.tests[testName];
        if (baseTest && currTest) {
            improvements.push({
                name: testTitles[testName],
                pct: improvement(baseTest.score, currTest.score)
            });
        }
    }
    improvements.sort(function(a, b) { return b.pct - a.pct; });
    
    if (improvements.length > 0) {
        console.log('\nBest Improvement:');
        console.log('  ' + improvements[0].name + ': ' + formatChange(improvements[0].pct));
        
        console.log('\nNeeds Work:');
        console.log('  ' + improvements[improvements.length - 1].name + ': ' + 
                    formatChange(improvements[improvements.length - 1].pct));
    }
    
    // ============================================
    // OPTIMIZATION TARGETS
    // ============================================
    
    console.log('\n' + '-'.repeat(70));
    console.log('OPTIMIZATION SCENARIO TARGETS');
    console.log('-'.repeat(70));
    
    console.log('\nScenario 1 (Simple Optimizations):');
    console.log('  Target: 2-3x improvement (200-300%)');
    console.log('  Current: ' + compositeImprovement.toFixed(1) + '%');
    if (compositeImprovement >= 200) {
        console.log('  Status: ✓ Target achieved!');
    } else if (compositeImprovement > 0) {
        console.log('  Status: ' + (compositeImprovement / 200 * 100).toFixed(0) + '% of target');
    } else {
        console.log('  Status: Not yet started');
    }
    
    console.log('\nScenario 2 (Modern OpenGL):');
    console.log('  Target: 5-10x improvement (500-1000%)');
    console.log('  Current: ' + compositeImprovement.toFixed(1) + '%');
    if (compositeImprovement >= 500) {
        console.log('  Status: ✓ Target achieved!');
        if (compositeImprovement >= 1000) {
            console.log('           🌟 Exceeded upper target! Excellent work!');
        }
    } else if (compositeImprovement > 0) {
        console.log('  Status: ' + (compositeImprovement / 500 * 100).toFixed(0) + '% of target');
    } else {
        console.log('  Status: Not yet started');
    }
    
    // ============================================
    // RECOMMENDATIONS
    // ============================================
    
    if (compositeImprovement < 200) {
        console.log('\n' + '-'.repeat(70));
        console.log('OPTIMIZATION RECOMMENDATIONS');
        console.log('-'.repeat(70));
        
        console.log('\nBased on test results, focus on:');
        
        // Sort by worst performance (lowest improvement)
        improvements.sort(function(a, b) { return a.pct - b.pct; });
        
        for (var i = 0; i < Math.min(3, improvements.length); i++) {
            var imp = improvements[i];
            var testName = Object.keys(testTitles).find(function(k) { return testTitles[k] === imp.name; });
            
            console.log('\n' + (i+1) + '. ' + imp.name + ' (' + formatChange(imp.pct) + ')');
            
            switch(testName) {
                case 'bitmap':
                    console.log('   - Implement sprite batching');
                    console.log('   - Reduce texture bind calls');
                    console.log('   - Cache transform matrices');
                    break;
                case 'drawing':
                    console.log('   - Batch line/arc drawing');
                    console.log('   - Cache OpenGL state between primitives');
                    console.log('   - Use vertex buffers for curves');
                    break;
                case 'alpha':
                    console.log('   - Minimize blend mode changes');
                    console.log('   - Sort by blend mode before rendering');
                    console.log('   - Use pre-multiplied alpha where possible');
                    break;
                case 'polygon':
                    console.log('   - Cache tessellated polygons');
                    console.log('   - Optimize gradient fill implementation');
                    console.log('   - Use vertex buffers for complex shapes');
                    break;
                case 'text':
                    console.log('   - Implement text batching');
                    console.log('   - Cache rendered glyphs in texture atlas');
                    console.log('   - Reduce font state changes');
                    break;
            }
        }
    }
    
    console.log('\n' + '='.repeat(70) + '\n');
    
} catch (e) {
    console.log('\nError: ' + e.message);
    console.log('\nUsage: node compare_results.js [baseline.json] [current.json]');
    console.log('\nDefault files:');
    console.log('  Baseline: ' + baselineFile);
    console.log('  Current:  ' + currentFile);
    console.log('\nMake sure to run pdgmark.js first to generate results,');
    console.log('and save a baseline with:');
    console.log('  cp test/perf/pdgmark/pdgmark_results.json \\');
    console.log('     test/perf/pdgmark/pdgmark_baseline.json');
    console.log('');
    process.exit(1);
}

