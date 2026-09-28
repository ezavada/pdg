'use strict';
// Exercise real build configuration and packaging with a disposable compiler stub.
const assert = require('assert');
const fs = require('fs');
const os = require('os');
const path = require('path');
const crypto = require('crypto');
const {spawnSync} = require('child_process');
const repo = path.resolve(__dirname, '../..');
const fixture = fs.mkdtempSync(path.join(os.tmpdir(), 'pdg-wasm-release-'));
function run(command, args, options = {}) {
    return spawnSync(command, args, {cwd:fixture, encoding:'utf8', ...options});
}
function pass(result) { assert.strictEqual(result.status, 0, result.stdout + result.stderr); }
function write(name, value, mode) {
    const file = path.join(fixture, name);
    fs.mkdirSync(path.dirname(file), {recursive:true});
    fs.writeFileSync(file, value, {mode:mode || 0o644});
}
try {
    write('inspect.mk', 'inspect:\n\t@printf "%s\\n" "FLAGS=$(BUILD_FLAGS)" "OUT=$(WASM_OUT_DIR)" "LIBS=$(LIBS)" "ASSETS=$(ADDITIONAL_JS_FILES)"\n');
    const configurations = {};
    for (const name of ['test', 'debug', 'release']) {
        const result = run('make', ['-s', '-f', repo+'/tools/pdg-js.mak', '-f', fixture+'/inspect.mk',
            'inspect', 'PDG_ROOT='+repo, 'WASM_BUILD='+name]);
        pass(result);
        configurations[name] = result.stdout;
    }
    assert.match(configurations.release, /FLAGS=-O3 -flto -g0/);
    assert.match(configurations.release, /OUT=.*\/release\n/);
    assert.match(configurations.debug, /FLAGS=-O0 -gsource-map=inline/);
    assert.match(configurations.debug, /OUT=.*\/debug\n/);
    assert.match(configurations.debug, /ASSERTIONS=2/);
    assert.match(configurations.debug, /STACK_OVERFLOW_CHECK=2/);
    assert.match(configurations.test, /FLAGS=-O0 -gsource-map\n/);
    assert.match(configurations.test, /--embed-file .*\/test\/spec@\/spec/);
    for (const name of ['debug', 'release']) assert(!configurations[name].includes('/test/spec@/spec'));

    for (const name of ['tools/release-emscripten.sh', 'cmake/ValidateReleaseVersion.cmake',
        'CMakeLists.txt', 'VERSION', 'README.md', 'LICENSE']) write(name, fs.readFileSync(path.join(repo, name)));
    fs.symlinkSync(path.join(repo, 'deps'), path.join(fixture, 'deps'), 'dir');
    for (const name of ['unit', 'ui', 'demo']) write('test/'+name,
        '#!/bin/sh\necho "'+name+' $*" >> "$PDG_WASM_TEST_LOG"\n', 0o755);
    // The fake test runners never open a server, so port discovery needs no socket.
    write('bin/python3', '#!/bin/sh\nprintf "31337\\n"\n', 0o755);
    write('bin/emmake', `#!${process.execPath}
const fs=require('fs'),path=require('path');
const args=process.argv.slice(2);
const mode=args.find(x=>x.startsWith('WASM_BUILD=')).split('=')[1];
const output=path.join(process.env.PDG_ROOT,'build/wasm',process.env.WASM_ARCH,mode==='test'?'':mode);
fs.appendFileSync(process.env.PDG_WASM_BUILD_LOG,mode+(args.includes('clean')?' clean':' build')+'\\n');
if(args.includes('clean')) { fs.rmSync(output+'/pdg',{recursive:true,force:true});
 for(const ext of ['js','wasm','wasm.map'])fs.rmSync(output+'/libpdg.'+ext,{force:true});process.exit(0); }
if(process.env.PDG_WASM_FAIL===mode)process.exit(7);
fs.mkdirSync(output,{recursive:true});
fs.writeFileSync(output+'/libpdg.js',mode+' JavaScript');
fs.writeFileSync(output+'/libpdg.wasm',mode==='test'?'embedded test fixtures':mode+' runtime only');
if(mode!=='release' && process.env.PDG_WASM_NO_MAP!==mode)fs.writeFileSync(output+'/libpdg.wasm.map','source map');
`, 0o755);
    const env = {...process.env, PATH:fixture+'/bin'+path.delimiter+process.env.PATH,
        EMSDK_PYTHON:fixture+'/bin/python3',
        PDG_WASM_TEST_LOG:fixture+'/test.log', PDG_WASM_BUILD_LOG:fixture+'/build.log', PDG_WASM_ARCH:'wasm32'};
    const version = fs.readFileSync(fixture+'/VERSION', 'utf8').trim();
    function release(directory, skip, extra = {}) {
        return run('bash', ['tools/release-emscripten.sh', '--tag', 'v'+version, '--output-dir', directory,
            ...(skip ? ['--skip-tests'] : [])], {env:{...env, ...extra}});
    }
    function checkPackages(directory) {
        for (const [prefix, mode] of [['pdg', 'release'], ['pdg-debug', 'debug']]) {
            const base = prefix+'-v'+version+'-emscripten-wasm32';
            const zip = path.join(fixture, directory, base+'.zip');
            assert(fs.existsSync(zip), 'both runtime ZIPs must exist');
            assert.strictEqual(fs.readFileSync(zip+'.sha256', 'utf8').split(/\s+/)[0],
                crypto.createHash('sha256').update(fs.readFileSync(zip)).digest('hex'));
            const extract = path.join(fixture, directory, 'extracted-'+mode);
            fs.mkdirSync(extract);
            pass(run('cmake', ['-E', 'tar', 'xf', zip], {cwd:extract}));
            const runtime = path.join(extract, base);
            assert.strictEqual(fs.readFileSync(runtime+'/libpdg.js', 'utf8'), mode+' JavaScript');
            assert.strictEqual(fs.readFileSync(runtime+'/libpdg.wasm', 'utf8'), mode+' runtime only');
            assert.strictEqual(fs.existsSync(runtime+'/libpdg.wasm.map'), mode==='debug');
            for (const file of ['LICENSE', 'README.md', 'VERSION', 'THIRD_PARTY_LICENSES/node.txt',
                'THIRD_PARTY_LICENSES/libtess2.txt']) assert(fs.existsSync(path.join(runtime, file)));
        }
    }
    pass(release('normal', false));
    checkPackages('normal');
    assert.match(fs.readFileSync(fixture+'/test.log', 'utf8'), /unit --web --no-build --automated\nui --web --no-build --automated\ndemo --web --no-build --automated\n/);
    fs.writeFileSync(fixture+'/build.log', '');
    fs.writeFileSync(fixture+'/test.log', '');
    pass(release('skipped', true));
    checkPackages('skipped');
    assert.strictEqual(fs.readFileSync(fixture+'/test.log', 'utf8'), '');
    assert.strictEqual(fs.readFileSync(fixture+'/build.log', 'utf8'),
        'release clean\nrelease build\ndebug clean\ndebug build\n');
    const missingMap = release('missing-map', true, {PDG_WASM_NO_MAP:'debug'});
    assert.notStrictEqual(missingMap.status, 0);
    assert.match(missingMap.stderr, /Expected Emscripten debug output was not produced/);
    assert(!fs.existsSync(fixture+'/missing-map'));
    assert.strictEqual(release('failed-build', true, {PDG_WASM_FAIL:'debug'}).status, 7);
    assert(!fs.existsSync(fixture+'/failed-build'));
    console.log('PASS: WASM optimization modes, dual runtime packages, checksums, test gating and failed-build rejection');
} finally { fs.rmSync(fixture, {recursive:true, force:true}); }
