// -----------------------------------------------
// node_test.js
//
// Shared entry point for the headless Node-based spec suite.
// -----------------------------------------------

var fs = require('fs');
var specRunner = require('./lib/spec_runner');

if (!process.env.NODE_ENV) {
    process.env.NODE_ENV = 'test';
}

function printNodeHelp(platform) {
    if (platform === 'win32') {
        console.log('Usage: test\\node [--verbose] [testfile]\n');
    } else {
        console.log('Usage: test/node [--verbose] [testfile]\n');
    }
    console.log('Runs the headless Node-based PDG spec suite.\n');
    console.log('Options:');
    console.log('  -h, /?        this help message');
    console.log('  --verbose     log test progress');
    if (platform === 'win32') {
        console.log('  [testfile]    must be spec\\{filename}.spec.js - single test to run');
    } else {
        console.log('  [testfile]    must be spec/{filename}.spec.js - single test to run');
    }
}

var envInfo = specRunner.ensureTestEnvironment(process, fs);
var runConfig = specRunner.parseRunnerArgs(process.argv, envInfo.specDir, fs);

if (process.cwd() !== envInfo.testDir) {
    process.chdir(envInfo.testDir);
}

console.log('PDG_ROOT = ' + envInfo.repoRoot);
console.log('PDG_TEST_ARTIFACTS_DIR = ' + envInfo.artifactsDir);

if (runConfig.help) {
    printNodeHelp(process.platform);
    process.exit(0);
}

try {
    console.log('Running jasmine-node on:', envInfo.specDir);
    if (runConfig.requestedTarget) {
        console.log('Target spec:', runConfig.requestedTarget);
    }
    specRunner.runJasmineSpecs(envInfo, runConfig, process);
} catch (e) {
    console.error('Error running jasmine-node:', e);
    process.exit(1);
}
