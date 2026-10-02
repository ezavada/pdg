'use strict';
// Exercise cache upgrades/failures without building Node or changing the real cache.
const assert = require('assert');
const fs = require('fs');
const os = require('os');
const path = require('path');
const {spawnSync} = require('child_process');
const helper = path.resolve(__dirname, '../../tools/build-node.sh');
const root = fs.mkdtempSync(path.join(os.tmpdir(), 'pdg node build '));
const source = path.join(root, 'deps/node');
const output = path.join(root, 'out');
const release = path.join(output, 'Release');
const stamp = path.join(release, '.pdg-node-version.h');
const bin = path.join(root, 'bin');
const log = path.join(root, 'builds');
function version(minor, eol = '\n') {
    fs.writeFileSync(path.join(source, 'src/node_version.h'),
        ['#define NODE_MAJOR_VERSION 24', '#define NODE_MINOR_VERSION ' + minor,
            '#define NODE_PATCH_VERSION 0', ''].join(eol));
}
function run(extra = {}) {
    return spawnSync('bash', [helper, root, output, '/bin/bash', '2', '--without-node-snapshot'], {
        env:{...process.env, PATH:bin + path.delimiter + process.env.PATH,
            PDG_FAKE_NODE_RELEASE:release, PDG_FAKE_NODE_LOG:log, ...extra}, encoding:'utf8'});
}
function pass(result) { assert.strictEqual(result.status, 0, result.stdout + result.stderr); }
try {
    fs.mkdirSync(path.join(source, 'src'), {recursive:true});
    fs.mkdirSync(path.join(source, 'lib/internal/per_context'), {recursive:true});
    fs.mkdirSync(path.join(source, 'deps/example'), {recursive:true});
    fs.mkdirSync(path.join(release, 'obj.target'), {recursive:true});
    fs.mkdirSync(bin);
    fs.writeFileSync(path.join(source, 'configure'), 'test "$1" = --without-node-snapshot\n');
    const primordials = path.join(source, 'lib/internal/per_context/primordials.js');
    const dependency = path.join(source, 'deps/example/module.mjs');
    fs.writeFileSync(primordials, "'use strict';\r\nconst value = 1;\r\n");
    fs.writeFileSync(dependency, 'export default 1;\r\n');
    fs.writeFileSync(path.join(bin, 'make'), `#!/bin/bash
set -eu
echo build >> "$PDG_FAKE_NODE_LOG"
mkdir -p "$PDG_FAKE_NODE_RELEASE/obj.target"
printf archive > "$PDG_FAKE_NODE_RELEASE/obj.target/libnode.a"
printf archive > "$PDG_FAKE_NODE_RELEASE/obj.target/libnode_base.a"
version=$(awk '/^#define NODE_(MAJOR|MINOR|PATCH)_VERSION / {gsub(/\\r/, "", $3); v = v sep $3; sep = "."} END {print "v" v}' src/node_version.h)
if [ -n "\${PDG_FAKE_WRONG_VERSION:-}" ]; then version=v24.3.0; fi
printf '#!/bin/sh\\nif [ "x$1" = x--version ]; then echo %s; exit 0; fi\\nexit %s\\n' "$version" "\${PDG_FAKE_RUNTIME_STATUS:-0}" > "$PDG_FAKE_NODE_RELEASE/node"
chmod +x "$PDG_FAKE_NODE_RELEASE/node"
exit "\${PDG_FAKE_BUILD_STATUS:-0}"
`, {mode:0o755});

    version(20);
    const initial = run();
    pass(initial);
    assert.match(initial.stdout, /Normalizing Node\.js embedded JavaScript sources to LF/);
    assert(!fs.readFileSync(primordials, 'utf8').includes('\r'));
    assert(!fs.readFileSync(dependency, 'utf8').includes('\r'));
    assert(fs.existsSync(stamp));
    assert.strictEqual(fs.realpathSync(path.join(source, 'out')), fs.realpathSync(output));
    assert.match(run().stdout, /build is current: v24\.20\.0/);
    assert.strictEqual(fs.readFileSync(log, 'utf8'), 'build\n');
    const staleOutput = path.join(root, 'stale-out');
    fs.mkdirSync(staleOutput);
    fs.unlinkSync(path.join(source, 'out'));
    fs.symlinkSync(staleOutput, path.join(source, 'out'));
    assert.match(run().stdout, /build is current: v24\.20\.0/);
    assert.strictEqual(fs.realpathSync(path.join(source, 'out')), fs.realpathSync(output));
    version(21);
    pass(run());
    assert.strictEqual(fs.readFileSync(log, 'utf8'), 'build\nbuild\n');
    assert.match(fs.readFileSync(stamp, 'utf8'), /MINOR_VERSION 21/);
    version(21, '\r\n');
    pass(run());
    assert.match(run().stdout, /build is current: v24\.21\.0/);

    // --version alone must not certify a runtime that cannot initialize V8.
    fs.writeFileSync(path.join(release, 'node'),
        '#!/bin/sh\nif [ "x$1" = x--version ]; then echo v24.21.0; exit 0; fi\nexit 9\n',
        {mode:0o755});
    const repaired = run();
    pass(repaired);
    assert.match(repaired.stdout, /cannot initialize JavaScript; rebuilding from scratch/);
    assert.match(run().stdout, /build is current: v24\.21\.0/);

    // A missing library rebuilds even when version metadata and executable match.
    fs.rmSync(path.join(release, 'libnode.a'));
    pass(run());
    fs.rmSync(path.join(release, 'libnode_base.a'));
    pass(run());
    version(22);
    assert.strictEqual(run({PDG_FAKE_BUILD_STATUS:'7'}).status, 7);
    assert(!fs.existsSync(stamp));
    // An executable with the wrong version cannot certify a successful cache.
    const wrong = run({PDG_FAKE_WRONG_VERSION:'1'});
    assert.strictEqual(wrong.status, 1);
    assert.match(wrong.stderr, /does not match source version v24.22.0/);
    assert(!fs.existsSync(stamp));
    const broken = run({PDG_FAKE_RUNTIME_STATUS:'9'});
    assert.strictEqual(broken.status, 1);
    assert.match(broken.stderr, /cannot initialize a JavaScript environment/);
    assert(!fs.existsSync(stamp));
    pass(run());
    assert.match(run().stdout, /build is current: v24\.22\.0/);
    console.log('PASS: Node cache reuse, runtime validation, version upgrades, missing archives and failed rebuilds');
} finally { fs.rmSync(root, {recursive:true, force:true}); }
