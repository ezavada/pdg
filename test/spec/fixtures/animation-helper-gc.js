// Subprocess fixture, exercised by test/unit node_runtime.
const pdg = require('pdg');
const assert = require('assert');
require('v8').setFlagsFromString('--expose-gc');
const collect = require('vm').runInNewContext('gc');
async function collectWrappers() {
    for (let i = 0; i < 4; ++i) {
        await new Promise(resolve => setImmediate(resolve));
        collect();
    }
}
(async function() {
    const owner = new pdg.Animated();
    let calls = 0;
    let helper = new pdg.IAnimationHelper(function() { ++calls; return false; });
    const active = new WeakRef(helper);
    owner.addAnimationHelper(helper);
    helper = null;
    await collectWrappers();
    assert(active.deref(), 'active registration keeps the wrapper alive');
    owner.animate(.1);
    assert.strictEqual(calls, 1);
    await collectWrappers();
    assert.strictEqual(active.deref(), undefined, 'finished registration releases the wrapper');

    function makeCycle() {
        const item = new pdg.IAnimationHelper(function() { return item.keep; });
        item.keep = true;
        return item;
    }
    helper = makeCycle();
    const cycle = new WeakRef(helper);
    owner.addAnimationHelper(helper).removeAnimationHelper(helper);
    helper = null;
    await collectWrappers();
    assert.strictEqual(cycle.deref(), undefined, 'inactive callback/wrapper cycle is collectible');

    let sprite = new pdg.Sprite();
    helper = new pdg.IAnimationHelper(function() { return true; });
    const ownerGone = new WeakRef(sprite), helperGone = new WeakRef(helper);
    sprite.addAnimationHelper(helper);
    sprite = helper = null;
    await collectWrappers();
    assert.strictEqual(ownerGone.deref(), undefined, 'adding a helper does not pin its owner wrapper');
    assert.strictEqual(helperGone.deref(), undefined, 'owner destruction retires its helper');
    console.log('Animation helper GC: passed');
    pdg.quit();
})().catch(error => { console.error(error.stack || error); process.exit(1); });
pdg.run();
