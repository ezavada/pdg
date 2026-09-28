// Browser/iOS have no child_process API. Use the current executable so native
// clients exercise their bootstrap and --node exercises the headless addon.
if (typeof process !== 'undefined' && process.versions && process.versions.node) {
    describe('Process lifetime', function() {
        var fs = require('node:fs');
        var path = require('node:path');
        var cp = require('node:child_process');
        var embedded = false;
        try { process._linkedBinding('pdg'); embedded = true; } catch (_) {}
        var pdgModule = embedded ? 'pdg' : require.resolve('pdg');
        var workDir;

        beforeEach(function() {
            workDir = fs.mkdtempSync(path.join(process.env.PDG_TEST_TEMP_DIR, 'process-lifetime-'));
        });

        afterEach(function() {
            if (workDir) fs.rmSync(workDir, {recursive:true, force:true});
            workDir = null;
        });

        function run(source, overrides) {
            var script = path.join(workDir, 'main.js');
            fs.writeFileSync(script, 'require(' + JSON.stringify(pdgModule) + ');\n' +
                'function mark(value) { console.log("PDG_LIFETIME:" + value); }\n' + source);
            var env = Object.assign({}, process.env);
            // A caller's lifetime settings must not change the contract tested.
            ['PDG_NO_AUTO_EXIT', 'PDG_AUTO_EXIT_TIMEOUT', 'PDG_ORIGINAL_ARGS', 'NODE_OPTIONS'].forEach(function(key) {
                delete env[key];
            });
            Object.assign(env, overrides);
            var result = cp.spawnSync(process.execPath, [script], {
                cwd:workDir, env:env, encoding:'utf8',
                timeout:5000, killSignal:'SIGKILL', maxBuffer:1024 * 1024,
                stdio:['ignore', 'pipe', 'pipe']
            });
            // A hang or crash fails the test without taking down Jasmine or
            // leaving a child running. Include native crash output on failure.
            if (result.error || result.signal || result.status !== 0) {
                throw new Error('Child failed: ' + (result.error || result.signal || result.status) +
                    '\nstdout:\n' + result.stdout + '\nstderr:\n' + result.stderr);
            }
            return result.stdout.split(/\r?\n/).filter(function(line) {
                return line.indexOf('PDG_LIFETIME:') === 0;
            }).map(function(line) { return line.slice('PDG_LIFETIME:'.length); });
        }

        it('exits successfully after synchronous work without process.exit()', function() {
            expect(run('var sum = 0; for (var i = 1; i <= 100; ++i) sum += i; mark(sum);'))
                .toEqual(['5050']);
        });

        var timerScript = 'mark("ready");\n' +
            'var ticks = 0;\n' +
            'var timer = setInterval(function() {\n' +
            '    mark("tick:" + (++ticks));\n' +
            '    if (ticks === 3) { clearInterval(timer); mark("cleared"); }\n' +
            '}, 100);\n';
        var completed = ['ready', 'tick:1', 'tick:2', 'tick:3', 'cleared'];

        it('keeps referenced timers alive and exits after the last timer is cleared', function() {
            expect(run(timerScript)).toEqual(completed);
        });

        it('preserves main-thread sentinel handles after a worker exits, then shuts down cleanly', function() {
            expect(run('var pdg = require(' + JSON.stringify(pdgModule) + ');\n' +
                'var worker = new (require("node:worker_threads").Worker)("", {eval:true});\n' +
                'worker.on("exit", function(code) {\n' +
                '    var sprite = new pdg.Sprite();\n' +
                '    mark("worker:" + code);\n' +
                '    mark(sprite.collider === pdg.Collider.NoCollider);\n' +
                '    mark(sprite.physics === pdg.PhysicsBody.NoPhysics);\n' +
                '});\n')).toEqual(['worker:0', 'true', 'true']);
        });

        // These switches belong to the embedded bootstrap, not the Node addon.
        // Opting out suppresses PDG's forced exit; it does not create a keepalive
        // handle. Node still exits naturally once the timer has been cleared.
        if (embedded) {
            it('honors the configured forced-exit timeout while work remains', function() {
                expect(run(timerScript, {PDG_AUTO_EXIT_TIMEOUT:'0'})).toEqual(['ready']);
            });

            it('lets the global opt-out override the forced-exit timeout', function() {
                expect(run('global._pdgNoAutoExit = true;\n' + timerScript,
                    {PDG_AUTO_EXIT_TIMEOUT:'0'})).toEqual(completed);
            });

            it('lets the environment opt-out override the forced-exit timeout', function() {
                expect(run(timerScript, {PDG_NO_AUTO_EXIT:'1', PDG_AUTO_EXIT_TIMEOUT:'0'}))
                    .toEqual(completed);
            });
        }
    });
}
