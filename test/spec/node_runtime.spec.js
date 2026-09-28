// Exercise Node's embedded library registrations and event loop in both the
// native client and the headless plugin. Browser/iOS skip these Node-only checks.
if (typeof process !== 'undefined' && process.versions && process.versions.node) {
    describe('Node runtime integration', function() {
        var fs = require('node:fs');
        var path = require('node:path');
        var header = fs.readFileSync(path.resolve(__dirname, '../../deps/node/src/node_version.h'), 'utf8');
        var expectedVersion = ['MAJOR', 'MINOR', 'PATCH'].map(function(part) {
            return header.match(new RegExp('#define NODE_' + part + '_VERSION (\\d+)'))[1];
        }).join('.');
        var worker, server;

        afterEach(function(done) {
            if (server) {
                server.closeAllConnections();
                server.close();
                server = null;
            }
            if (worker) {
                var pending = worker;
                worker = null;
                pending.terminate().then(function() { done(); }, function(error) {
                    expect(error).toBeUndefined();
                    done();
                });
            } else done();
        });

        it('runs the Node version pinned by the source checkout', function() {
            expect(process.versions.node).toBe(expectedVersion);
        });

        it('shares PDG across nested imports, createRequire and the module cache', function() {
            var assert = require('node:assert');
            var localRequire = require('node:module').createRequire(__filename);
            var nested = require('./fixtures/test_require/required_file.js');
            expect(nested()).toBe(pdg);
            expect(localRequire('pdg')).toBe(pdg);
            expect(localRequire.cache[localRequire.resolve('pdg')].exports).toBe(pdg);
            expect(localRequire('node:path')).toBe(path);
            assert.throws(function() { localRequire('./fixtures/test_require/missing-file.js'); },
                function(error) { return error.code === 'MODULE_NOT_FOUND'; });
            if (localRequire.resolve('pdg') === 'pdg') {
                var outsideRequire = require('node:module').createRequire(
                    path.join(require('node:os').tmpdir(), 'pdg-require-check', 'main.js'));
                expect(outsideRequire('pdg')).toBe(pdg);
            }
        });

        it('collects animation helpers after completion, removal and owner destruction', function() {
            expect(require('../lib/runtime_subprocess')('animation-helper-gc.js'))
                .toContain('Animation helper GC: passed');
        });

        it('preserves native mounts and layer members while collecting their wrappers', function() {
            expect(require('../lib/runtime_subprocess')('sprite-mount-gc.js'))
                .toContain('Sprite mount GC: passed');
        });

        if (pdg.hasGraphics) it('bypasses frame pacing for Quick benchmarks on existing and new windows', function() {
            expect(require('../lib/runtime_subprocess')('quick_pacing.js'))
                .toContain('PASS: ordinary frame limit, Quick bypass, existing and new windows:');
        });

        it('loads entry scripts with CommonJS scope, globals and module identity', function() {
            expect(require('../lib/runtime_subprocess')('entry-module.js'))
                .toContain('PASS: CommonJS entry scope, identity, cache, arguments and async globals');
        });

        it('loads crypto, compression and VM builtins from the embedded libraries', function() {
            var crypto = require('node:crypto');
            var zlib = require('node:zlib');
            var vm = require('node:vm');
            expect(crypto.createHash('sha256').update('abc').digest('hex'))
                .toBe('ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad');
            expect(zlib.gunzipSync(zlib.gzipSync(Buffer.from('PDG runtime'))).toString()).toBe('PDG runtime');
            expect(vm.runInNewContext('value * 2', {value:21})).toBe(42);
        });

        it('initializes a worker isolate and delivers its result', function(done) {
            worker = new (require('node:worker_threads').Worker)(
                'require("node:worker_threads").parentPort.postMessage({' +
                'version:process.versions.node, bytes:require("node:crypto").randomBytes(8).length});', {eval:true});
            worker.once('error', function(error) { expect(error).toBeUndefined(); done(); });
            worker.once('message', function(message) {
                expect(message.version).toBe(expectedVersion);
                expect(message.bytes).toBe(8);
                done();
            });
        });

        it('completes a fetch request through the embedded event loop', function(done) {
            server = require('node:http').createServer(function(request, response) {
                response.setHeader('Content-Type', 'application/json');
                response.end(JSON.stringify({node:process.versions.node, path:request.url}));
            });
            server.once('error', function(error) { expect(error).toBeUndefined(); done(); });
            server.listen(0, '127.0.0.1', function() {
                fetch('http://127.0.0.1:' + server.address().port + '/runtime').then(function(response) {
                    expect(response.status).toBe(200);
                    return response.json();
                }).then(function(body) {
                    expect(body.node).toBe(expectedVersion);
                    expect(body.path).toBe('/runtime');
                    done();
                }, function(error) { expect(error).toBeUndefined(); done(); });
            });
        });
    });
}
