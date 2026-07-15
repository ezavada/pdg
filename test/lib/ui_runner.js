// -----------------------------------------------
// ui_runner.js
//
// Shared runner for the interactive UI test suite.
// Keeps the test list and artifact handling consistent across platforms.
// -----------------------------------------------

var childProcess = require('child_process');
var fs = require('fs');
var path = require('path');
var specRunner = require('./spec_runner');

var UI_TESTS = [
    {
        id: 'port',
        name: 'Port test',
        scriptPath: path.join('ui_tests', 'port_test.js'),
        workingDir: 'test'
    },
    {
        id: 'font',
        name: 'Font test',
        scriptPath: path.join('ui_tests', 'font_test.js'),
        workingDir: 'test'
    },
    {
        id: 'drawing',
        name: 'Drawing test',
        scriptPath: path.join('ui_tests', 'drawing_test.js'),
        workingDir: 'test'
    },
    {
        id: 'shape-fill',
        name: 'Shape fill test',
        scriptPath: path.join('test', 'ui_tests', 'shape_fill_test.js'),
        workingDir: 'repo'
    },
    {
        id: 'image',
        name: 'Image test',
        scriptPath: path.join('ui_tests', 'image_test.js'),
        workingDir: 'test'
    },
    {
        id: 'animation',
        name: 'Animation test',
        scriptPath: path.join('ui_tests', 'animation_test.js'),
        workingDir: 'test'
    }
];

function sanitizeSegment(value, fallbackValue) {
    var text = String(value || fallbackValue || '');
    text = text.toLowerCase().replace(/[^a-z0-9._-]+/g, '-').replace(/^-+|-+$/g, '');
    return text || fallbackValue || 'unknown';
}

function resolvePdgExecutable(envInfo) {
    var candidates = process.platform === 'win32'
        ? [
            path.join(envInfo.repoRoot, 'pdg.exe'),
            path.join(envInfo.testDir, 'pdg.exe')
        ]
        : [
            path.join(envInfo.repoRoot, 'pdg'),
            path.join(envInfo.testDir, 'pdg')
        ];

    for (var i = 0; i < candidates.length; i++) {
        if (fs.existsSync(candidates[i])) {
            return candidates[i];
        }
    }
    return null;
}

function printHelp() {
    if (process.platform === 'win32') {
        console.log('Usage: test\\ui [--list] [ui-test-args]\n');
    } else {
        console.log('Usage: test/ui [--list] [ui-test-args]\n');
    }
    console.log('Runs the interactive UI regression scripts in sequence.');
}

function writeSummary(reportPath, summary) {
    fs.writeFileSync(reportPath, JSON.stringify(summary, null, 2) + '\n', 'utf8');
}

function runUiTests() {
    if (process.argv.indexOf('--help') >= 0 || process.argv.indexOf('-h') >= 0) {
        printHelp();
        return 0;
    }

    if (process.argv.indexOf('--list') >= 0) {
        UI_TESTS.forEach(function(testDef) {
            console.log(testDef.id + ' - ' + testDef.name);
        });
        return 0;
    }

    process.env.PDG_TEST_MODE = process.env.PDG_TEST_MODE || 'ui';
    var envInfo = specRunner.ensureTestEnvironment(process, fs);
    var pdgExecutable = resolvePdgExecutable(envInfo);
    if (!pdgExecutable) {
        console.error('Error: could not find the PDG runtime executable.');
        return 1;
    }

    var forwardedArgs = process.argv.slice(2).filter(function(arg) {
        return arg !== '--list';
    });
    var summary = {
        suite: 'ui',
        platform: envInfo.platformName,
        executable: pdgExecutable,
        startedAt: new Date().toISOString(),
        results: []
    };

    for (var i = 0; i < UI_TESTS.length; i++) {
        var testDef = UI_TESTS[i];
        var testSlug = sanitizeSegment(testDef.id, 'ui-test');
        var stdoutPath = path.join(envInfo.logDir, testSlug + '.stdout.log');
        var stderrPath = path.join(envInfo.logDir, testSlug + '.stderr.log');
        var workingDir = testDef.workingDir === 'repo' ? envInfo.repoRoot : envInfo.testDir;
        var args = [testDef.scriptPath].concat(forwardedArgs);

        console.log('Running ' + testDef.name + '...');
        var startedAt = new Date().toISOString();
        var execResult = childProcess.spawnSync(pdgExecutable, args, {
            cwd: workingDir,
            encoding: 'utf8',
            stdio: ['ignore', 'pipe', 'pipe']
        });

        var stdoutText = execResult.stdout || '';
        var stderrText = execResult.stderr || '';
        fs.writeFileSync(stdoutPath, stdoutText, 'utf8');
        fs.writeFileSync(stderrPath, stderrText, 'utf8');

        var exitCode = typeof execResult.status === 'number' ? execResult.status : 1;
        var testStatus = exitCode === 0 && !execResult.error ? 'passed' : 'failed';
        summary.results.push({
            id: testDef.id,
            name: testDef.name,
            scriptPath: testDef.scriptPath,
            workingDirectory: workingDir,
            startedAt: startedAt,
            endedAt: new Date().toISOString(),
            status: testStatus,
            exitCode: exitCode,
            stdoutLog: stdoutPath,
            stderrLog: stderrPath,
            error: execResult.error ? String(execResult.error.message || execResult.error) : null
        });

        if (testStatus === 'passed') {
            console.log('PASS: ' + testDef.name);
        } else {
            console.log('FAIL: ' + testDef.name);
            if (stdoutText) {
                process.stdout.write(stdoutText);
            }
            if (stderrText) {
                process.stderr.write(stderrText);
            }
            summary.endedAt = new Date().toISOString();
            writeSummary(path.join(envInfo.reportDir, 'ui-summary.json'), summary);
            return 1;
        }
    }

    summary.endedAt = new Date().toISOString();
    writeSummary(path.join(envInfo.reportDir, 'ui-summary.json'), summary);
    console.log('PASS: all UI tests completed');
    return 0;
}

process.exit(runUiTests());
