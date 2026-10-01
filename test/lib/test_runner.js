#!/usr/bin/env node
'use strict';
const fs = require('fs');
const path = require('path');
const cp = require('child_process');
const http = require('http');
const optionsAPI = require('./test_options');
const specRunner = require('./spec_runner');
const root = path.resolve(__dirname, '../..');
const testDir = path.join(root, 'test');

function run(command, args, opts) {
    const result = cp.spawnSync(command, args, Object.assign({cwd: root, stdio: 'inherit'}, opts));
    if (result.error) throw result.error;
    return result.status === null ? 1 : result.status;
}
function nativeExecutable() {
    const names = process.platform === 'win32' ? ['test/pdg-run.exe', 'pdg.exe', 'test/pdg.exe'] : ['pdg', 'test/pdg'];
    const executable = process.env.PDG_EXECUTABLE ? path.resolve(process.env.PDG_EXECUTABLE)
        : names.map(n => path.join(root, n)).find(p => fs.existsSync(p));
    if (!executable) throw Error('No current PDG build. Run configure and make pdg, or choose --node, --web, or --ios.');
    return executable;
}
function currentCTest() {
    let dir = process.env.PDG_TEST_BUILD_DIR && path.resolve(process.env.PDG_TEST_BUILD_DIR);
    if (!dir) {
        try { dir = path.dirname(fs.realpathSync(nativeExecutable())); } catch (_) { return null; }
        while (!fs.existsSync(path.join(dir, 'CMakeCache.txt'))) {
            const parent = path.dirname(dir);
            if (parent === dir) return null;
            dir = parent;
        }
    }
    const cache = fs.readFileSync(path.join(dir, 'CMakeCache.txt'), 'utf8');
    if (!/^BUILD_TESTING:BOOL=ON$/m.test(cache)) return null;
    const ctest = (cache.match(/^CMAKE_CTEST_COMMAND:INTERNAL=(.+)$/m) || [null, 'ctest'])[1].trim();
    const result = cp.spawnSync(ctest, ['--test-dir', dir, '--show-only=json-v1'], {encoding: 'utf8'});
    if (result.error || result.status) throw Error('Could not list C++ tests: ' + (result.error || result.stderr));
    return {dir, ctest, names: JSON.parse(result.stdout).tests.map(t => t.name)};
}
function unitSuites(target) {
    if (target === 'web' || target === 'ios') return require('./unit_spec_catalog')[target];
    return fs.readdirSync(path.join(testDir, 'spec')).filter(n => /\.spec\.js$/.test(n)).map(n => n.slice(0, -8)).sort();
}
function envFor(options) {
    process.env.PDG_ROOT = root;
    process.env.PDG_TEST_MODE = options.kind;
    process.env.PDG_TEST_PLATFORM = options.target === 'native' ? process.platform : options.target;
    return specRunner.ensureTestEnvironment(process, fs);
}
function buildWeb(options, configuration = 'test') {
    if (!options['no-build']) {
        const code = run('bash', ['test/lib/build_web.sh', configuration]);
        if (code) throw Error('Web build failed (' + code + ').');
    }
    ['js', 'wasm'].forEach(ext => {
        if (!fs.existsSync(path.join(root, 'build/wasm/wasm32', configuration === 'release' ? 'release' : '', 'libpdg.' + ext))) throw Error('Missing web build; retry without --no-build.');
    });
}
function browserPath() {
    if (process.env.PDG_BROWSER) return process.env.PDG_BROWSER;
    const candidates = process.platform === 'darwin' ? ['/Applications/Google Chrome.app/Contents/MacOS/Google Chrome'] :
        process.platform === 'win32' ? [process.env.PROGRAMFILES, process.env['PROGRAMFILES(X86)'], process.env.LOCALAPPDATA]
            .filter(Boolean).map(p => path.join(p, 'Google/Chrome/Application/chrome.exe')) : [];
    const found = candidates.find(p => fs.existsSync(p));
    if (found) return found;
    for (const name of ['google-chrome', 'chromium', 'chromium-browser']) {
        const result = cp.spawnSync('which', [name], {encoding: 'utf8'});
        if (result.status === 0) return result.stdout.trim();
    }
    throw Error('Chrome/Chromium not found. Set PDG_BROWSER to its executable.');
}
function serve() {
    const types = {'.js':'text/javascript', '.html':'text/html', '.css':'text/css', '.wasm':'application/wasm', '.json':'application/json', '.png':'image/png'};
    const realRoot = fs.realpathSync(root) + path.sep;
    const server = http.createServer((req, res) => {
        try {
            const file = fs.realpathSync(path.join(root, decodeURIComponent(new URL(req.url, 'http://localhost').pathname)));
            if (!file.startsWith(realRoot) || !fs.statSync(file).isFile()) throw Error('Not a file');
            res.setHeader('Content-Type', types[path.extname(file)] || 'application/octet-stream');
            res.setHeader('Cache-Control', 'no-store');
            fs.createReadStream(file).pipe(res);
        } catch (_) { res.writeHead(404); res.end('Not found'); }
    });
    return new Promise((resolve, reject) => {
        server.on('error', reject);
        server.listen(Number(process.env.PDG_TEST_PORT || 0), '127.0.0.1', () => resolve(server));
    });
}
function spawnAsync(command, args, opts) {
    return new Promise((resolve, reject) => {
        const child = cp.spawn(command, args, Object.assign({cwd: root, stdio: 'inherit'}, opts));
        child.on('error', reject);
        child.on('exit', (code) => resolve(code === null ? 1 : code));
    });
}
async function web(options, env, suites, pages) {
    buildWeb(options);
    const server = await serve();
    const base = 'http://127.0.0.1:' + server.address().port + '/test/';
    try {
        if (options.automated) {
            const urls = options.kind === 'unit' ? [base + 'unit.html?specs=' + encodeURIComponent(suites.join(','))]
                : suites.map(id => base + 'ui.html?test=' + encodeURIComponent(id) + '&automated=1');
            let failed = 0;
            for (let i = 0; i < urls.length; ++i) {
                const report = path.join(env.reportDir, (options.kind === 'unit' ? 'unit' : suites[i]) + '.html');
                const entry = options.kind === 'unit' ? null : pages.find(page => page.suite === suites[i]).entry;
                const timeout = Math.max(120000, entry && entry.smokeTimeoutMs ? entry.smokeTimeoutMs + 30000 : 0);
                const code = await spawnAsync(process.execPath, [path.join(testDir, 'emscripten/run_ui_browser.js'),
                    browserPath(), urls[i], report, options.kind === 'unit' ? 'pdg-result-json' : 'pdg-ui-result-json', String(timeout)]);
                console.log((code ? 'FAIL ' : 'PASS ') + (options.kind === 'unit' ? 'browser unit suites' : suites[i]) + '\nReport: ' + report);
                failed = failed || code;
            }
            return failed;
        }
        const query = options.kind === 'unit' ? new URLSearchParams({specs: suites.join(',')}) :
            new URLSearchParams({kind: options.kind, suites: suites.join(','), page: String(optionsAPI.pageIndex(pages, options.page) + 1), interactive: '1'});
        const url = base + (options.kind === 'unit' ? 'unit.html?' : 'ui.html?') + query;
        console.log('Open ' + url + '\n' + (options.kind === 'unit' ? 'Results stay open for inspection. ' :
            'Left/Right: page. Space/background click: pause. ') + 'Ctrl+C stops the server.');
        if (process.platform === 'darwin') run('open', [url]);
        else if (process.platform === 'win32') run('powershell.exe', ['-NoProfile', '-Command', 'Start-Process -FilePath $env:PDG_TEST_URL'],
            {env: Object.assign({}, process.env, {PDG_TEST_URL: url})});
        else run('xdg-open', [url]);
        await new Promise(resolve => { process.once('SIGINT', resolve); process.once('SIGTERM', resolve); });
        return 0;
    } finally { server.close(); }
}

async function main(args) {
    const options = optionsAPI.parse(args[0], args.slice(1));
    if (options.help) {
        console.log('Usage: test/' + options.kind + ' [--web | --ios | --node] [--list] [suite ...]' +
            (options.kind === 'unit' ? '' : ' [--page number|name]') + '\n' +
            'Default: current native build. --web/--ios build incrementally when needed.\n' +
            '--no-build skips the web/iOS build. --verbose prints spec progress.\n' +
            (options.kind === 'unit' ? 'Includes JavaScript specs and configured CTest suites (cpp:name) in the current native build.\n' +
                '--web opens browser results; --automated runs headlessly, saves a report, and exits with the test status.\n' :
                'Left/Right: previous/next page; Space/background click: pause/resume; Escape: quit.\n--automated runs the selected suites as smoke checks instead of interactive pages.\n') +
            '--ios supports --iphone/--ipad or PDG_IOS_DEVICE_ID (requires macOS/Xcode).');
        return 0;
    }
    const cpp = options.kind === 'unit' && options.target === 'native' ? currentCTest() : null;
    const available = options.kind === 'unit' ? unitSuites(options.target).concat(cpp ? cpp.names.map(n => 'cpp:' + n) : []) : [];
    const pages = options.kind === 'unit' ? [] : optionsAPI.visualPages(options);
    if (options.list) {
        if (options.kind === 'unit') available.forEach(name => console.log(name));
        else pages.forEach((p, i) => console.log((i + 1) + '\t' + p.id + '\t' + p.entry.name));
        return 0;
    }
    let suites;
    if (options.kind === 'unit') {
        options.suites.forEach(name => { if (!available.includes(name)) throw Error('Unknown unit suite: ' + name + '. Use --list.'); });
        suites = options.suites.length ? [...new Set(options.suites)] : available;
    } else {
        optionsAPI.pageIndex(pages, options.page); // Validate before building or launching.
        suites = [...new Set(pages.map(p => p.suite))];
    }
    const env = envFor(options);
    if (options.target === 'web') return web(options, env, suites, pages);
    if (options.target === 'ios') {
        if (process.platform !== 'darwin') throw Error('--ios requires macOS with Xcode and an iOS Simulator.');
        if (options.kind !== 'unit' && !options.automated) return require('./ios_visual_runner').run(options, pages, env);
        const iosArgs = options.kind === 'unit' ? ['--unit'].concat(suites) : ['--ui'];
        if (options.kind === 'unit' && options.verbose) iosArgs.push('--verbose');
        if (options.iphone) iosArgs.unshift('--iphone');
        if (options.ipad) iosArgs.unshift('--ipad');
        if (options['no-build']) iosArgs.unshift('--no-build');
        if (options.kind === 'unit') return run(path.join(testDir, 'ios'), iosArgs);
        let failed = 0;
        suites.forEach(id => { failed = run(path.join(testDir, 'ios'), iosArgs.concat(id)) || failed; });
        return failed;
    }
    if (options.kind !== 'unit') {
        let executable = options.target === 'node' ? process.execPath : nativeExecutable();
        if (options.target === 'node') {
            const probe = cp.spawnSync(executable, ['-e', 'const p=require("pdg");process.exit(p.hasGraphics?0:3)'], {cwd: root, encoding:'utf8'});
            if (probe.status !== 0) throw Error('The current Node plugin has no graphics. Use the native GUI build or --web/--ios for visual tests.');
        }
        if (options.automated) return run(process.execPath, [path.join(__dirname, 'ui_runner.js')].concat(suites),
            {env: Object.assign({}, process.env, {PDG_EXECUTABLE: executable})});
        let index = optionsAPI.pageIndex(pages, options.page);
        while (true) {
            const page = pages[index];
            const code = run(executable, [path.join(__dirname, 'visual_entry.js'), page.suite, String(page.localPage),
                (index + 1) + '/' + pages.length + '  ' + page.id, '--wait'], {cwd: page.entry.workingDir === 'repo' ? root : testDir});
            if (code !== 90 && code !== 91) return code;
            index = (index + (code === 90 ? 1 : -1) + pages.length) % pages.length;
        }
    }
    let failed = 0;
    const cppNames = suites.filter(n => n.startsWith('cpp:')).map(n => n.slice(4));
    if (cppNames.length) failed = run(cpp.ctest, ['--test-dir', cpp.dir, '--output-on-failure', '-R',
        '^(' + cppNames.map(n => n.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')).join('|') + ')$']);
    const jsNames = suites.filter(n => !n.startsWith('cpp:'));
    if (jsNames.length) {
        const echo = cp.spawn(process.execPath, [path.join(root, 'tools/echo_tcp.js')], {cwd: root, stdio: 'ignore'});
        echo.on('error', error => console.error('Echo server:', error.message));
        try {
            // Async spawn lets the echo server run while the runtime executes tests.
            failed = (await spawnAsync(options.target === 'node' ? process.execPath : nativeExecutable(),
                [path.join(testDir, 'js', options.target === 'node' ? 'unit_node_test.js' : 'unit_test.js')]
                    .concat(jsNames, options.verbose ? ['--verbose'] : []), {cwd: testDir})) || failed;
        } finally { echo.kill(); }
    }
    return failed;
}
exports.main = main;
exports.nativeExecutable = nativeExecutable;
exports.envFor = envFor;
exports.buildWeb = buildWeb;
exports.serve = serve;
exports.browserPath = browserPath;
if (require.main === module) main(process.argv.slice(2)).then(code => { process.exitCode = code; }, error => {
    console.error('Error: ' + error.message); process.exitCode = 2;
});
