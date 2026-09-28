'use strict';
// Performance entry points share an isolated, optimized runtime. Never infer
// release mode from an executable filename or --config on a single-config build.
const fs = require('fs');
const path = require('path');
const cp = require('child_process');
const root = path.resolve(__dirname, '../..');
const platform = process.platform === 'win32' ? 'win32' : process.platform;
const arch = process.arch === 'x64' ? 'x86_64' : process.arch;
function run(command, args, env = process.env) {
    const result = cp.spawnSync(command, args, {cwd:root, env, stdio:'inherit'});
    if (result.error || result.status !== 0) throw Error('Release build failed: ' + (result.error || command + ' exited ' + result.status));
}
function directory() {
    return path.resolve(process.env.PDG_PERF_BUILD_DIR || path.join(root, 'build', platform, arch, 'pdg-perf-release'));
}
function binary(dir, name) {
    const names = process.platform === 'darwin' ? [name + '.app/Contents/MacOS/' + name, name]
        : process.platform === 'win32' ? ['Release/' + name + '.exe', name + '.exe'] : [name];
    const found = names.map(name => path.join(dir, 'src', name)).find(file => fs.existsSync(file));
    if (!found) throw Error('Missing release ' + name + '; retry without --no-build.');
    return found;
}
function assertRelease(info) {
    if (!info || info.configuration !== 'Release')
        throw Error('Performance tests require a Release PDG runtime; retry without --no-build or select a release PDG_EXECUTABLE.');
    return info;
}
function probe(executable, addon = false) {
    const source = 'const p=require("pdg");console.log("PDG_PERF_BUILD:"+JSON.stringify({' +
        'configuration:p._buildConfiguration,node:process.versions.node,hasGraphics:p.hasGraphics,' +
        'module:typeof require.resolve==="function"?require.resolve("pdg"):"pdg:embedded"}));p.quit();';
    const result = cp.spawnSync(executable, ['-e', source], {cwd:root, encoding:'utf8', timeout:20000});
    const match = (result.stdout || '').match(/^PDG_PERF_BUILD:(.+)$/m);
    if (result.error || result.status !== 0 || !match)
        throw Error('Cannot verify release PDG runtime: ' + (result.error || result.stderr || result.stdout));
    return {...assertRelease(JSON.parse(match[1])), executable, resolvedExecutable:fs.realpathSync(executable), kind:addon ? 'node-addon' : 'embedded'};
}
function native(options, targets = []) {
    const dir = directory();
    const override = process.env.PDG_EXECUTABLE && path.resolve(process.env.PDG_EXECUTABLE);
    const buildTargets = [...new Set([...targets, ...(!override ? ['pdg'] : [])])];
    if (!options['no-build'] && buildTargets.length) {
        const cacheFile = path.join(dir, 'CMakeCache.txt');
        const cache = fs.existsSync(cacheFile) ? fs.readFileSync(cacheFile, 'utf8') : '';
        const settings = {CMAKE_BUILD_TYPE:'Release', BUILD_TESTING:'ON',
            CAN_BUILD_INTERFACES:'ON', CAN_BUILD_JSC_INTERFACES:'OFF'};
        // CMake's build command detects changed project inputs itself. Avoid
        // needlessly regenerating all bindings on every benchmark invocation.
        if (!Object.entries({...settings, CMAKE_HOME_DIRECTORY:root}).every(([key, value]) =>
            cache.split(/\r?\n/).some(line => {
                if (!line.startsWith(key + ':')) return false;
                const cached = line.slice(line.indexOf('=') + 1);
                return (key === 'CMAKE_HOME_DIRECTORY' ? path.resolve(cached) : cached) === value;
            })))
            run('cmake', ['-S', root, '-B', dir, ...Object.entries(settings).map(([key, value]) => '-D' + key + '=' + value)]);
        run('cmake', ['--build', dir, '--config', 'Release', '--target', ...buildTargets,
            '--parallel', process.env.PDG_BUILD_JOBS || '8']);
    }
    let executable = override || binary(dir, 'pdg');
    // The macOS app launcher treats a bundle path as a Finder launch and changes
    // the resource directory. A command-line symlink preserves the caller's cwd.
    if (!override && process.platform === 'darwin') {
        const launcher = path.join(dir, 'pdg');
        const target = path.relative(dir, executable);
        if (!fs.existsSync(launcher)) fs.symlinkSync(target, launcher);
        else if (!fs.lstatSync(launcher).isSymbolicLink() || fs.readlinkSync(launcher) !== target)
            throw Error('Unexpected performance launcher at ' + launcher);
        executable = launcher;
    }
    return {...probe(executable), directory:dir};
}
function node(options) {
    if (!options['no-build']) {
        const env = {...process.env, PDG_NODE_BUILD_CONFIG:'Release'};
        // node-gyp treats even the string "false" as a truthy debug override.
        for (const key of Object.keys(env)) {
            if (key.toLowerCase() === 'npm_config_debug') delete env[key];
        }
        if (process.platform === 'win32') run('powershell', ['-NoProfile', '-ExecutionPolicy', 'Bypass',
            '-File', path.join(root, 'tools/make-node-module.ps1'), '-Config', 'Release'], env);
        else run('make', ['pdg-node'], env);
    }
    return probe(process.execPath, true);
}
// Direct/interactive benchmark wrappers use the same release selection as test/perf.
if (require.main === module) {
    try {
        const args = process.argv.slice(2);
        const noBuild = args.includes('--no-build');
        const runtime = native({'no-build':noBuild});
        const result = cp.spawnSync(runtime.executable, args.filter(arg => arg !== '--no-build'), {cwd:root, stdio:'inherit'});
        if (result.error) throw result.error;
        process.exitCode = result.status === null ? 1 : result.status;
    } catch (error) { console.error(error.message); process.exitCode = 1; }
}
module.exports = {directory, binary, assertRelease, probe, native, node};
