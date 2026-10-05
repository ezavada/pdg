// Jasmine unit-spec adapter for the standalone JavaScriptCore iOS runtime.
// This intentionally uses only bundled JavaScript and does not depend on Node.

var path = require('path');

var unitSpecs = require('./unit_spec_catalog').ios;

var nonGuiSpecs = [
    'color', 'configmanager', 'eventemitter', 'eventmanager', 'filemanager',
    'log', 'memblock', 'offset', 'point', 'polygon', 'quad', 'rect',
    'resourcemanager', 'rotatedrect', 'serialization', 'serialized_data',
    'serialized_objects', 'spline', 'timermanager', 'vector'
];

function installJasmineGlobals(repoRoot) {
    var api = require(path.join(repoRoot, 'jasmine.js'));
    var names = [
        'spyOn', 'it', 'xit', 'expect', 'runs', 'waits', 'waitsFor',
        'beforeEach', 'afterEach', 'describe', 'xdescribe'
    ];
    global.jasmine = api.jasmine;
    for (var i = 0; i < names.length; ++i) {
        global[names[i]] = api[names[i]];
    }
    require('./jasmine_async')(global);
}

function selectSpecs(runConfig, processObj) {
    if (runConfig.requestedTarget) {
        return {
            name: 'unit',
            specs: (runConfig.requestedTargets || [runConfig.requestedTarget]).map(function(name) { return name.replace(/\.spec\.js$/i, ''); })
        };
    }
    for (var i = 1; i < processObj.argv.length; ++i) {
        if (processObj.argv[i] === '--non-gui') {
            return { name: 'non-gui', specs: nonGuiSpecs.slice() };
        }
    }
    return { name: 'unit', specs: unitSpecs.slice() };
}

function failureText(item, includeStack) {
    if (!item) return 'unknown failure';
    var message = item.message || String(item.trace || item);
    if (includeStack && item.trace && item.trace.stack) message += '\n' + item.trace.stack;
    return message;
}

function display(message) {
    console.log('[PDG IOS DISPLAY] ' + message);
}

var colors = {
    pass: '\x1b[32m',
    fail: '\x1b[31m',
    specTiming: '\x1b[34m',
    suiteTiming: '\x1b[33m',
    ignore: '\x1b[37m',
    neutral: '\x1b[0m'
};

function colored(message, color) {
    return color + message + colors.neutral;
}

function indent(message, depth) {
    var spaces = '';
    for (var i = 0; i < depth; ++i) spaces += '  ';
    return spaces + message;
}

function summarize(suiteOrSpec) {
    var isSuite = suiteOrSpec instanceof jasmine.Suite;
    var summary = {
        id: suiteOrSpec.id,
        name: suiteOrSpec.description,
        type: isSuite ? 'suite' : 'spec',
        children: []
    };
    if (isSuite) {
        var children = suiteOrSpec.children();
        for (var i = 0; i < children.length; ++i) {
            summary.children.push(summarize(children[i]));
        }
    }
    return summary;
}

function displayVerboseResults(summaries, specResults, suiteResults, depth) {
    depth = typeof depth === 'number' ? depth : 0;
    for (var i = 0; i < summaries.length; ++i) {
        var summary = summaries[i];
        if (summary.type === 'suite') {
            display('');
            var suiteLine = indent(summary.name, depth);
            if (suiteResults[summary.id]) {
                suiteLine += colored(' - ' + suiteResults[summary.id].runtime + ' ms', colors.suiteTiming);
            }
            display(suiteLine);
        } else {
            var result = specResults[summary.id];
            var specColor = result.result === 'passed' ? colors.pass : colors.fail;
            display(colored(indent(summary.name, depth), specColor) +
                colored(' - ' + result.runtime + ' ms', colors.specTiming));
        }
        displayVerboseResults(summary.children, specResults, suiteResults, depth + 2);
    }
}

exports.run = function(envInfo, runConfig, processObj) {
    installJasmineGlobals(envInfo.repoRoot);

    require(path.join(envInfo.specDir, 'SpecHelper.js'));
    var selection = selectSpecs(runConfig, processObj);
    var specs = selection.specs;
    var verboseReporter = runConfig.verbose || !!runConfig.requestedTarget &&
        (!runConfig.requestedTargets || runConfig.requestedTargets.length === 1);
    var loadFailures = [];
    for (var i = 0; i < specs.length; ++i) {
        try {
            require(path.join(envInfo.specDir, specs[i] + '.spec.js'));
        } catch (error) {
            loadFailures.push(specs[i] + ': ' + (error.stack || error));
            console.error('[PDG TEST LOAD FAIL] ' + loadFailures[loadFailures.length - 1]);
            display('LOAD FAIL ' + specs[i] + ': ' + error);
        }
    }

    var specFailures = [];
    var failureSummaries = [];
    var suiteSummaries = [];
    var specResults = {};
    var suiteResults = {};
    var specStartTimes = {};
    var suiteStartTimes = {};
    var progress = '';
    var runnerStartedAt = 0;
    var jasmineEnv = jasmine.getEnv();
    jasmineEnv.updateInterval = 10;
    jasmineEnv.addReporter({
        reportRunnerStarting: function(runner) {
            runnerStartedAt = Date.now();
            var topLevelSuites = runner.topLevelSuites();
            for (var i = 0; i < topLevelSuites.length; ++i) {
                suiteSummaries.push(summarize(topLevelSuites[i]));
            }
        },
        reportSpecStarting: function(spec) {
            var now = Date.now();
            specStartTimes[spec.id] = now;
            var suite = spec.suite;
            while (suite) {
                if (!suiteStartTimes[suite.id]) suiteStartTimes[suite.id] = now;
                suite = suite.parentSuite;
            }
        },
        reportSpecResults: function(spec) {
            var results = spec.results();
            var elapsed = Date.now() - specStartTimes[spec.id];
            specResults[spec.id] = {
                result: results.passed() ? 'passed' : 'failed',
                runtime: elapsed
            };
            if (results.passed()) {
                progress += colored('.', colors.pass);
            } else {
                progress += colored('F', colors.fail);
                var items = results.getItems();
                for (var index = 0; index < items.length; ++index) {
                    if (items[index].passed && !items[index].passed()) {
                        var detail = spec.getFullName() + ': ' + failureText(items[index], true);
                        specFailures.push(detail);
                        failureSummaries.push({
                            spec: spec.getFullName(),
                            message: failureText(items[index], false),
                            stack: items[index].trace && items[index].trace.stack
                                ? items[index].trace.stack : ''
                        });
                        console.error('[PDG TEST FAIL] ' + detail);
                    }
                }
            }
        },
        reportSuiteResults: function(suite) {
            if (suiteStartTimes[suite.id]) {
                suiteResults[suite.id] = { runtime: Date.now() - suiteStartTimes[suite.id] };
            }
        },
        reportRunnerResults: function(runner) {
            var results = runner.results();
            var failed = results.failedCount + loadFailures.length;
            var runnerSpecs = runner.specs();
            var testCount = runnerSpecs.length;
            var skippedCount = 0;
            for (var i = 0; i < runnerSpecs.length; ++i) {
                if (runnerSpecs[i].results().skipped) ++skippedCount;
            }

            if (verboseReporter) {
                displayVerboseResults(suiteSummaries, specResults, suiteResults);
            } else {
                display(progress);
            }

            if (failureSummaries.length) {
                display('');
                display('Failures:');
                for (var failureIndex = 0; failureIndex < failureSummaries.length; ++failureIndex) {
                    var failure = failureSummaries[failureIndex];
                    display('');
                    display('  ' + (failureIndex + 1) + ') ' + failure.spec);
                    display('   Message:');
                    display('     ' + colored(failure.message, colors.fail));
                    if (runConfig.verbose && failure.stack) {
                        display('   Stacktrace:');
                        display('     ' + failure.stack);
                    }
                }
            }

            display('');
            display('Finished in ' + ((Date.now() - runnerStartedAt) / 1000) + ' seconds');
            var summaryLine = (testCount - skippedCount) + ' test' +
                (testCount - skippedCount === 1 ? '' : 's') + ', ' +
                results.totalCount + ' assertion' + (results.totalCount === 1 ? '' : 's') + ', ' +
                failed + ' failure' + (failed === 1 ? '' : 's') + ', ' +
                skippedCount + ' skipped';
            display(colored(summaryLine, failed ? colors.fail : colors.pass));
            console.log('[PDG IOS RESULT] ' + JSON.stringify({
                status: failed ? 'failed' : 'passed',
                suite: selection.name,
                tests: testCount,
                specs: results.totalCount,
                jasmineFailures: results.failedCount,
                loadFailures: loadFailures.length,
                failureDetails: specFailures
            }));
            require('pdg').quit();
        }
    });
    jasmineEnv.execute();
};
