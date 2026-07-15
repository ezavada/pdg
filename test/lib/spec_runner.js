// -----------------------------------------------
// spec_runner.js
//
// Shared helpers for PDG test runners.
// Keeps path handling and jasmine-node setup consistent across wrappers.
// -----------------------------------------------

var path = require('path');
var Module = require('module');

function sanitizeSegment(value, fallbackValue) {
    var text = String(value || fallbackValue || '');
    text = text.toLowerCase().replace(/[^a-z0-9._-]+/g, '-').replace(/^-+|-+$/g, '');
    return text || fallbackValue || 'unknown';
}

function ensureDir(fs, dirPath) {
    if (!fs || !dirPath) {
        return;
    }
    if (!fs.existsSync(dirPath)) {
        fs.mkdirSync(dirPath, { recursive: true });
    }
}

function detectRepoRoot(processObj) {
    if (processObj && processObj.env && processObj.env.PDG_ROOT) {
        return path.resolve(processObj.env.PDG_ROOT);
    }
    return path.resolve(__dirname, '..', '..');
}

function ensureTestEnvironment(processObj, fs) {
    var repoRoot = detectRepoRoot(processObj);
    var env = processObj.env || {};
    var mode = sanitizeSegment(env.PDG_TEST_MODE, 'client');
    var platformName = sanitizeSegment(env.PDG_TEST_PLATFORM || processObj.platform, 'unknown');
    var artifactsDir = path.resolve(env.PDG_TEST_ARTIFACTS_DIR || path.join(repoRoot, 'artifacts', 'test-results', platformName, mode));
    var logDir = path.resolve(env.PDG_TEST_LOG_DIR || path.join(artifactsDir, 'logs'));
    var reportDir = path.resolve(env.PDG_TEST_REPORT_DIR || path.join(artifactsDir, 'reports'));
    var tempDir = path.resolve(env.PDG_TEST_TEMP_DIR || path.join(artifactsDir, 'tmp'));
    var testDir = processObj.ios ? repoRoot : path.join(repoRoot, 'test');
    var specDir = processObj.ios ? path.join(repoRoot, 'spec') : path.join(testDir, 'spec');

    ensureDir(fs, artifactsDir);
    ensureDir(fs, logDir);
    ensureDir(fs, reportDir);
    ensureDir(fs, tempDir);

    env.PDG_ROOT = repoRoot;
    env.PDG_TEST_MODE = mode;
    env.PDG_TEST_PLATFORM = platformName;
    env.PDG_TEST_ARTIFACTS_DIR = artifactsDir;
    env.PDG_TEST_LOG_DIR = logDir;
    env.PDG_TEST_REPORT_DIR = reportDir;
    env.PDG_TEST_TEMP_DIR = tempDir;

    return {
        repoRoot: repoRoot,
        testDir: testDir,
        specDir: specDir,
        mode: mode,
        platformName: platformName,
        artifactsDir: artifactsDir,
        logDir: logDir,
        reportDir: reportDir,
        tempDir: tempDir
    };
}

function resolveRequestedTarget(specDir, arg, fs) {
    if (!arg) {
        return null;
    }
    if (/^spec/.test(arg)) {
        return arg;
    }
    if (fs && fs.existsSync(path.join(specDir, arg))) {
        return arg;
    }
    if (fs && fs.existsSync(path.join(specDir, arg + '.spec.js'))) {
        return arg + '.spec.js';
    }
    return null;
}

function parseRunnerArgs(argv, specDir, fs) {
    var runConfig = {
        debug: false,
        help: false,
        verbose: false,
        requestedTarget: null
    };

    for (var i = 1; i < argv.length; i++) {
        var arg = argv[i];
        if (arg === '--debug') {
            runConfig.debug = true;
        } else if (arg === '--help' || arg === '-h' || arg === '/?') {
            runConfig.help = true;
        } else if (arg === '--verbose') {
            runConfig.verbose = true;
        } else {
            var requestedTarget = resolveRequestedTarget(specDir, arg, fs);
            if (requestedTarget) {
                runConfig.requestedTarget = requestedTarget;
            }
        }
    }

    return runConfig;
}

function printClientHelp(platform) {
    if (platform === 'win32') {
        console.log('Usage: test\\client [--debug] [--verbose] [testfile]\n');
    } else {
        console.log('Usage: test/client [--debug] [--verbose] [testfile]\n');
    }
    console.log('Runs tests against the PDG client app\n');
    console.log('Options:');
    console.log('  -h, /?        this help message');
    console.log('  --debug       launch the debugger');
    console.log('  --verbose     log test progress');
    if (platform === 'win32') {
        console.log('  [testfile]    must be spec\\{filename}.spec.js - single test to run');
    } else {
        console.log('  [testfile]    must be spec/{filename}.spec.js - single test to run');
    }
}

function loadJasmineNode(repoRoot) {
    return withGrowlReporterFallback(function() {
        try {
            return require('jasmine-node');
        } catch (e) {
            return require(path.join(repoRoot, 'node_modules', 'jasmine-node', 'lib', 'jasmine-node', 'index.js'));
        }
    });
}

function createNoopGrowlReporter() {
    function NoopGrowlReporter() {}
    NoopGrowlReporter.prototype.reportRunnerStarting = function() {};
    NoopGrowlReporter.prototype.reportRunnerResults = function() {};
    NoopGrowlReporter.prototype.reportSuiteResults = function() {};
    NoopGrowlReporter.prototype.reportSpecStarting = function() {};
    NoopGrowlReporter.prototype.reportSpecResults = function() {};
    NoopGrowlReporter.prototype.log = function() {};
    return NoopGrowlReporter;
}

function withGrowlReporterFallback(loader) {
    var originalLoad = Module._load;
    Module._load = function(request, parent, isMain) {
        if (request === 'jasmine-growl-reporter') {
            try {
                return originalLoad.apply(this, arguments);
            } catch (e) {
                if (e && e.code === 'MODULE_NOT_FOUND') {
                    return createNoopGrowlReporter();
                }
                throw e;
            }
        }
        return originalLoad.apply(this, arguments);
    };
    try {
        return loader();
    } finally {
        Module._load = originalLoad;
    }
}

function createJasmineOptions(envInfo, runConfig, processObj) {
    var options = {
        specFolders: [envInfo.specDir],
        isVerbose: runConfig.verbose,
        showColors: true,
        teamcity: false,
        useRequireJs: false,
        regExpSpec: new RegExp('\\.spec\\.js$', 'i'),
        junitreport: {
            report: false,
            savePath: envInfo.reportDir,
            useDotNotation: true,
            consolidate: true
        },
        includeStackTrace: true,
        growl: false,
        onComplete: function(runner) {
            var exitCode = 0;
            if (runner.results().failedCount > 0) {
                exitCode = 1;
            }
            processObj.exit(exitCode);
        }
    };

    if (runConfig.requestedTarget) {
        var baseName = runConfig.requestedTarget.replace(/\.spec\.js$/i, '');
        options.regExpSpec = new RegExp('^' + baseName.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + '\\.spec\\.js$', 'i');
        options.isVerbose = true;
    }

    return options;
}

function runJasmineSpecs(envInfo, runConfig, processObj) {
    var jasmineNode = loadJasmineNode(envInfo.repoRoot);
    var options = createJasmineOptions(envInfo, runConfig, processObj);

    jasmineNode.loadHelpersInFolder(envInfo.specDir, new RegExp('^SpecHelper\\.js$', 'i'));
    jasmineNode.executeSpecsInFolder(options);
}

module.exports = {
    ensureTestEnvironment: ensureTestEnvironment,
    parseRunnerArgs: parseRunnerArgs,
    printClientHelp: printClientHelp,
    runJasmineSpecs: runJasmineSpecs
};
