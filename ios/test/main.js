// Dispatch either one interactive UI script or the shared Jasmine client
// entry point. Simulator launch arguments select the mode without rebuilding.
var pdg = require('pdg');

function uiTestIdFromArgs(args) {
    for (var i = 1; i < args.length; ++i) {
        if (args[i] === '--ui-test' && i + 1 < args.length) return args[i + 1];
    }
    return null;
}

function runUiTest(testId) {
    var catalog = require('./lib/ui_test_catalog');
    var testDef = null;
    for (var i = 0; i < catalog.length; ++i) {
        if (catalog[i].id === testId) {
            testDef = catalog[i];
            break;
        }
    }
    if (!testDef) throw new Error('Unknown iOS UI test: ' + testId);

    var reported = false;
    function report(status, details) {
        if (reported) return;
        reported = true;
        console.log('[PDG IOS UI RESULT] ' + JSON.stringify({
            status: status,
            id: testDef.id,
            name: testDef.name,
            details: details || ''
        }));
    }

    var originalQuit = pdg.quit;
    pdg.quit = function() {
        report('passed', 'completed');
        return originalQuit.apply(pdg, arguments);
    };
    process.on('exit', function(code) {
        report(code ? 'failed' : 'passed', 'process.exit(' + code + ')');
    });

    process.argv = [process.execPath, testDef.scriptPath].concat(testDef.args || []);
    console.log('[PDG IOS UI START] ' + JSON.stringify({
        id: testDef.id,
        name: testDef.name
    }));
    require('./' + testDef.scriptPath.replace(/^test\//, ''));
}

var uiTestId = uiTestIdFromArgs(process.argv);
try {
    var visualIndex = process.argv.indexOf('--visual-page');
    if (visualIndex >= 0) {
        require('./lib/visual_entry').launch(process.argv[visualIndex + 1],
            Number(process.argv[visualIndex + 2]), process.argv[visualIndex + 3], function(action) {
                console.log('[PDG VISUAL ACTION] ' + action);
                process.exit(0);
            });
    } else if (uiTestId) {
        runUiTest(uiTestId);
    } else {
        require('./js/client_test.js');
    }
} catch (error) {
    console.error('[PDG IOS BOOTSTRAP FAIL] ' + (error.stack || error));
    if (uiTestId || visualIndex >= 0) {
        process.exit(1);
    } else {
        pdg.quit();
    }
}
