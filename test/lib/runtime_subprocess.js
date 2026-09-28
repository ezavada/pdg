'use strict';

// Run engine regressions which need isolated V8 flags, globals or real windows.
// The current executable preserves the client's native-vs-addon test target.
module.exports = function runRuntimeFixture(name) {
    const path = require('node:path');
    const env = Object.assign({}, process.env);
    ['PDG_NO_AUTO_EXIT', 'PDG_AUTO_EXIT_TIMEOUT', 'PDG_ORIGINAL_ARGS', 'NODE_OPTIONS',
        'PDG_PERF_UNCAPPED'].forEach(key => { delete env[key]; });
    const result = require('node:child_process').spawnSync(process.execPath,
        [path.resolve(__dirname, '../spec/fixtures', name)], {
            cwd:path.resolve(__dirname, '../..'), env, encoding:'utf8',
            timeout:15000, killSignal:'SIGKILL', maxBuffer:1024 * 1024,
            stdio:['ignore', 'pipe', 'pipe']
        });
    if (result.error || result.signal || result.status !== 0) {
        throw new Error(name + ': ' + (result.error || result.signal || result.status) +
            '\nstdout:\n' + result.stdout + '\nstderr:\n' + result.stderr);
    }
    return result.stdout;
};
