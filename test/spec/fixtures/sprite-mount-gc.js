// Subprocess fixture, exercised by test/unit node_runtime.
// Native V8 regression: wrappers, layer membership and mounts each own their
// references independently. This intentionally requires Node's GC controls.
const pdg = require('pdg');
const assert = require('assert');
require('v8').setFlagsFromString('--expose-gc');
const collect = require('vm').runInNewContext('gc');
async function collectWrappers() {
    for (let i = 0; i < 3; ++i) {
        await new Promise(resolve => setImmediate(resolve));
        collect();
    }
}
(async function() {
    let host = new pdg.Sprite();
    let child = new pdg.Sprite();
    child.setupPhysicsBody().setMode(pdg.physicsBody_Kinematic);
    const id = child.createPart('identity').getId();
    const mount = host.createPart('socket').attachSprite(child);
    let weak = new WeakRef(child);
    child = null;
    await collectWrappers();
    assert.strictEqual(weak.deref(), undefined, 'the mount retains the native child without pinning its wrapper');
    child = mount.getAttachedSprite();
    assert.strictEqual(child.getPart(id).getName(), 'identity');
    assert.strictEqual(child.physics.getMode(), pdg.physicsBody_Kinematic);
    mount.detachSprite();
    child.physics.setMode(pdg.physicsBody_Dynamic);
    assert.notStrictEqual(child.physics, pdg.PhysicsBody.NoPhysics, 'detaching preserves the script reference');
    const retained = child.createPart('retained');
    weak = new WeakRef(child);
    child = null;
    await collectWrappers();
    assert.strictEqual(weak.deref(), undefined);
    assert.strictEqual(retained.getSprite(), null, 'owner collection detaches retained Parts');
    host = null;
    await collectWrappers();
    assert.strictEqual(mount.getSprite(), null);
    const layer = pdg.createSpriteLayer();
    let member = layer.createSprite();
    member.createPart('layer retained');
    weak = new WeakRef(member);
    member = null;
    await collectWrappers();
    assert.strictEqual(weak.deref(), undefined, 'layer membership does not pin the wrapper');
    member = layer.getNthSprite(0);
    assert.strictEqual(member.findPart('layer retained').getName(), 'layer retained');
    pdg.cleanupLayer(layer);
    assert.notStrictEqual(member.findPart('layer retained'), null, 'script handle survives layer destruction');
    console.log('Sprite mount GC: passed');
    pdg.quit();
})().catch(error => { console.error(error.stack || error); process.exit(1); });

pdg.run();
