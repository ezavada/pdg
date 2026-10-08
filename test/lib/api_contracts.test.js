'use strict';
const assert = require('assert');
const fs = require('fs');
const path = require('path');
const {enrich, inventoryModule, memberDocumentation, memberResultComment, schemaDocumentation, moduleDocumentation} = require('../../tools/api-contracts');
const contracts = require('../../tools/interface-metadata-source').readContracts();
const fresh = () => JSON.parse(fs.readFileSync(path.resolve(__dirname, '../../docs/javascript/pdg-js.json'), 'utf8'));
const api = enrich(fresh());
const receiverFixture = enrich({interface:[{name:'Animated', type:'class', interface:[
    {name:'copy', type:'function', params:[], returns:'object Animated'},
    {name:'mutate', type:'function', params:[], returns:'this'}
]}]}, {version:1, schemas:{}, members:{}});
assert(!receiverFixture.interface[0].interface[0].returns_contract);
assert.deepStrictEqual(receiverFixture.interface[0].interface[1].returns_contract, {type:'this'});
const klass = name => api.interface.find(item => item.type === 'class' && item.name === name);
const member = (owner, name) => klass(owner).interface.find(item => item.name === name);
for (const name of ['raycast', 'sweepCircle', 'nearestPoint']) {
    const query = member('Scene', name);
    assert.strictEqual(query.returns, 'object CollisionQueryHit');
    const variants = Array.isArray(query.params[0]) ? query.params : [query.params];
    for (const params of variants) for (const param of params) {
        if (param.name === 'options') assert.strictEqual(param.type, 'object CollisionQueryOptions');
    }
}
assert(!klass('CollisionQueryBuffer'));
assert(!klass('Scene').interface.some(m => m.name.startsWith('_')));

// The committed output must also include enrichment: exercising enrich() alone
// would miss a disconnected make-idl integration.
const generated = fresh();
assert.strictEqual(generated.contract_version, contracts.version);
assert.strictEqual(generated.interface.find(c => c.name === 'Sprite').interface
    .find(m => m.name === 'findPart').returns_contract.nullable, true);
assert.strictEqual(generated.modules, undefined);
const mvc = JSON.parse(fs.readFileSync(path.resolve(__dirname, '../../docs/javascript/pdg-mvc-js.json'), 'utf8'));
assert.strictEqual(mvc.name, 'mvc-app');
const coreHeader = fs.readFileSync(path.resolve(__dirname, '../../docs/javascript/pdg-js.h'), 'utf8');
for (const signature of [
    'CollisionQueryHit nearestPoint (Point point, number maxDistance, CollisionQueryOptions options = undefined)',
    'CollisionQueryHit raycast (Point start, Point end, CollisionQueryOptions options = undefined)',
    'CollisionQueryHit sweepCircle (Point center, number radius, Vector delta, CollisionQueryOptions options = undefined)',
    'CollisionQueryHit[] raycast (Point start, Point end, uint maxHits, CollisionQueryOptions options = undefined)',
    'CollisionQueryHit[] sweepCircle (Point center, number radius, Vector delta, uint maxHits, CollisionQueryOptions options = undefined)',
    'CollisionQueryHit[] overlapPoint (Point point, CollisionQueryOptions options = undefined)'
]) assert(coreHeader.includes(signature), signature);
assert(!coreHeader.includes('CollisionQueryBuffer'));
for (const line of coreHeader.split('\n').filter(line => /^ +[^/].*\);/.test(line))) {
    assert(!/\bor\b/.test(line.split('//')[0]), 'Union prose in declaration: ' + line);
}
assert(coreHeader.includes('CollisionQueryHit nearestPoint (Point point, number maxDistance, CollisionQueryOptions options = undefined); // can return null'));
assert(!klass('MemBlock').interface.some(method => method.name === 'toUint8'));
assert(coreHeader.includes('Uint8Array getData ()'));
assert(coreHeader.includes('Uint8Array getBytes (uint start, uint len)'));
assert(coreHeader.includes('Uint8Array getResource (string resourceName, int maxSize = -1)'));
for (const signature of [
    'loadMapData (Uint8Array data,', 'loadMapData (MemBlock data,',
    'serialize_mem (Uint8Array mem)', 'sizeof_mem (Uint8Array mem)',
    'setDataPtr (Uint8Array data)', 'binaryDump (Uint8Array inData,'
]) assert(coreHeader.includes(signature), signature);
// Named object contracts must survive in the visible signature, not only in
// a prose note. Keep arbitrary reference tokens as plain object parameters.
for (const signature of [
    'animationHasTag (AnimationPose pose,',
    'createSerializableObject (SerializableImplementation obj,',
    'NetConnection (NetworkSocket socket)',
    'NetClient (NetClientOptions opt = null)',
    'send (NetworkData message)',
    'sendDgram (NetworkData message)',
    'broadcast (NetworkSendable message,',
    'findNext (FileFindData ioFindData)',
    'Point (XY xy)',
    'setState (AnimationSpringState state)',
    'serialize_ref (object obj)', 'sizeof_ref (object val)'
]) assert(coreHeader.includes(signature), signature);
const mvcHeader = fs.readFileSync(path.resolve(__dirname, '../../docs/javascript/pdg-mvc-js.h'), 'utf8');
assert(!coreHeader.includes('javascript_mvc_inventory'));
assert(mvcHeader.includes('javascript_mvc_inventory'));
assert(!klass('Drawing').interface.some(item => item.name === 'draw'));
for (const [owner, names] of Object.entries({
    Image: ['setTransparentColor','setOpacity','setEdgeClamping'],
    Port: ['clear','drawDrawing','resetClipRect'],
    Polygon: ['move','addPoint','scale'],
    Rect: ['assign','add','sub'], Quad: ['rotate'], NetConnection: ['send','sendDgram']
})) {
    names.forEach(name => assert.strictEqual(member(owner, name).returns_contract.type, 'this'));
}
['plus','minus','times','dividedby','intersection','unionWith'].forEach(name => {
    assert.strictEqual(member('Rect', name).returns_contract.type, 'object Rect');
    assert.strictEqual(member('Rect', name).returns_contract.ownership, 'owned');
});

const mvcViewModule = mvc.interface.find(item => item.name === 'View');
assert.strictEqual(mvcViewModule.type, 'object');
const mvcView = mvcViewModule.interface.find(item => item.name === 'View');
assert.deepStrictEqual(mvcView.implements, ['AnimatedAttributes']);
assert(mvcView.interface.some(item => item.name === 'getParentView'));

assert.strictEqual(member('Sprite', 'findPart').returns_contract.nullable, true);
assert.deepStrictEqual(member('ResourceManager', 'getResource').returns_contract.one_of,
    [{schema:'ByteArray'}, {type:'boolean', literal:false}]);
for (const [name, type] of [['getConfigString','string'], ['getConfigLong','number'],
    ['getConfigFloat','number'], ['getConfigBool','boolean']]) {
    assert.deepStrictEqual(member('ConfigManager', name).returns_contract.one_of,
        [{type}, {type:'undefined'}]);
}
assert.deepStrictEqual(member('NetClient', 'connection').value_contract.one_of,
    [{type:'object NetConnection'}, {type:'boolean', literal:false}]);
assert.strictEqual(member('NetClient', 'connection').type, 'object');
assert.strictEqual(member('AnimationSpringTarget', 'update').returns_contract.schema, 'AnimationSpringState');
assert.deepStrictEqual(Object.keys(api.schemas.AnimationSpringState.fields), ['x','y','velocityX','velocityY']);
assert.strictEqual(member('AnimationContactTarget', 'getState').returns_contract.schema, 'AnimationContactState');
assert.strictEqual(api.schemas.AnimationContactState.fields.locked.type, 'boolean');
for (const owner of ['Animated', 'Sprite', 'Part', 'Particle', 'AnimatedAttributes']) {
    assert.strictEqual(member(owner, 'moveTo').returns_contract.type, 'this', owner + ' must preserve its receiver');
}
assert(!member('Offset', 'plus').returns_contract, 'Do not label newly allocated geometry results as fluent receiver returns');

// Both native and JavaScript signatures use the same parser and schema resolver.
const metadataSource = require('../../tools/interface-metadata-source');
function schemaFixture(parameters, result = '[object Options]') {
    return {name:'pdg', interface:[
        {name:'Drawing', type:'class', interface:[]},
        {name:'Sprite', type:'class', interface:[{
            name:'draw', type:'function', ...metadataSource.signature('Attach artwork.', result, parameters)
        }]}
    ]};
}
const schemaContracts = {version:1, members:{}, schemas:{
    Options:{kind:'record', fields:{bone:{type:'string'}}},
    DrawCallback:{kind:'callback', params:[], returns:{type:'object Drawing', nullable:true}},
    OtherOptions:{kind:'record', fields:{}}
}};
const named = enrich(schemaFixture('({[object Drawing] drawing|[function DrawCallback] callback}, [object Options] options)'), schemaContracts);
const namedMethod = named.interface[1].interface[0];
assert.strictEqual(namedMethod.params[0][0].type, 'object Drawing');
assert(!namedMethod.params[0][0].contract);
assert.deepStrictEqual(namedMethod.params[1][0].contract, {type:'function', schema:'DrawCallback'});
for (const params of namedMethod.params) {
    assert.strictEqual(params[1].type, 'object Options');
    assert.deepStrictEqual(params[1].contract, {type:'object', schema:'Options'});
}
assert.strictEqual(namedMethod.returns, 'object Options');
assert.deepStrictEqual(namedMethod.returns_contract, {type:'object', schema:'Options'});
const namedConditional = enrich(schemaFixture('([object Options] options)'), {
    ...schemaContracts, members:{'Sprite.draw':{params:{options:{when_type:'object',schema:'Options',nullable:true}}}}
});
assert.strictEqual(namedConditional.interface[1].interface[0].params[0].type, 'object Options');
assert.strictEqual(namedConditional.interface[1].interface[0].params[0].contract.nullable, true);
assert(named.contract_coverage.applied.includes('Sprite.draw'));
assert.throws(() => enrich(schemaFixture('([object Missing] options)'), schemaContracts), /Unknown signature type/);
assert.throws(() => enrich(schemaFixture('([function Options] callback)'), schemaContracts), /Incompatible signature schema/);
assert.throws(() => enrich(schemaFixture('([object DrawCallback] options)'), schemaContracts), /Incompatible signature schema/);
assert.throws(() => enrich(schemaFixture('([function Drawing] callback)'), schemaContracts), /Class used as callback type/);
assert.throws(() => enrich(schemaFixture('([object Options] options)'), {
    ...schemaContracts, members:{'Sprite.draw':{params:{options:{schema:'OtherOptions'}}}}
}), /Conflicting signature schema/);
assert(!metadataSource.readContracts().members['Sprite.addAnimationDrawable']);
const remainingContracts = metadataSource.readContracts().members;
for (const name of ['Animated.when', 'Animated.until', 'AnimationContactTarget.lockPlatform', 'AnimationSpringTarget.setState'])
    assert(!remainingContracts[name], name + ' must use its signature schema');
for (const owner of ['Animated', 'Sprite', 'Part', 'Camera', 'AnimationScript', 'Particle', 'ParticleEmitter', 'AnimatedAttributes']) {
    for (const name of ['when', 'until'])
        assert.deepStrictEqual(member(owner, name).params[0].contract, {type:'function', schema:'AnimationEvaluator'});
}
assert.strictEqual(member('AnimationContactTarget', 'lockPlatform').params[3].contract.schema, 'AnimationTransform');
assert.strictEqual(member('AnimationSpringTarget', 'setState').params[0].contract.schema, 'AnimationSpringState');
const frameContract = member('AnimationContactTarget', 'update').params.find(p => p.name === 'frame').contract;
assert.strictEqual(frameContract.schema, 'AnimationTransform');
assert(frameContract.condition.includes('platform lock remains active'));
assert.strictEqual(member('AnimationContactTarget', 'update').returns_contract.ownership, 'owned');
for (const name of ['AnimationContactTarget.update','AnimationContactTarget.getState','AnimationSpringTarget.update','AnimationSpringTarget.getState'])
    assert(!remainingContracts[name].returns.schema);


const overloads = member('Sprite', 'addAnimationDrawable').params;
assert.strictEqual(overloads.length, 2);
for (const params of overloads) assert.strictEqual(params.find(p => p.name === 'options').contract.schema, 'AnimationDrawableOptions');
const callback = overloads.flat().find(p => p.name === 'callback');
assert.strictEqual(callback.contract.schema, 'AnimationDrawableCallback');
assert.strictEqual(api.schemas.AnimationDrawableCallback.synchronous, true);
assert.deepStrictEqual(api.schemas.AnimationDrawableCallback.returns, {type:'object Drawing', nullable:true});
assert.strictEqual(api.schemas.AnimationDrawableContext.lifetime, 'callback');
assert(!api.schemas.AnimationDrawableOptions.fields.bone.optional);
assert.strictEqual(api.schemas.AnimationDrawableOptions.fields.bounds.optional, true);

const missing = fresh();
missing.interface.find(c => c.name === 'Sprite').interface = klass('Sprite').interface.filter(m => m.name !== 'findPart');
assert.throws(() => enrich(missing), /Stale API contract: Sprite.findPart/);
const badParam = {version:1, schemas:contracts.schemas, members:{'Sprite.findPart':{params:{typo:{type:'string'}}}}};
assert.throws(() => enrich(fresh(), badParam), /Stale API parameter contract/);
assert.throws(() => enrich(fresh(), {version:1, schemas:{}, members:{'Sprite.findPart':{returns:{type:'object',schema:'Missing'}}}}), /Unknown API schema/);
const noNetwork = fresh();
noNetwork.interface = noNetwork.interface.filter(item => item.name !== 'NetClient');
assert(enrich(noNetwork).contract_coverage.unavailable.includes('NetClient.connection'));

let calls = 0;
class Base {}
class View extends Base {
    constructor() { super(); ++calls; throw Error('Do not construct controls'); }
    get controller() { ++calls; throw Error('Do not read getters'); }
    draw() { ++calls; throw Error('Do not call methods'); }
    static withPort() { ++calls; throw Error('Do not invoke factories'); }
}
const exportsFixture = {View, ViewAlias: View, nested: {View}, flags: {Top:8}, spacing:5};
exportsFixture.nested.circular = exportsFixture;
Object.defineProperty(exportsFixture, 'lazy', {get() { ++calls; throw Error('Do not read export getters'); }});
const inventory = inventoryModule(exportsFixture, 'mvc-app');
assert.strictEqual(calls, 0);
const view = inventory.interface.find(item => item.name === 'View');
assert.deepStrictEqual(view.implements, ['Base']);
assert.strictEqual(view.signature_status, 'unresolved');
assert(view.interface.some(m => m.name === 'controller' && m.type === 'accessor'));
assert(view.interface.some(m => m.name === 'withPort' && m.static));
assert(inventory.interface.some(item => item.name === 'ViewAlias'));
const nested = inventory.interface.find(item => item.name === 'nested');
assert.strictEqual(nested.interface.find(item => item.name === 'View').type, 'class');
assert.strictEqual(nested.interface.find(item => item.name === 'circular').cyclic_reference, true);
assert.strictEqual(inventory.interface.find(item => item.name === 'lazy').type, 'accessor');
assert.strictEqual(JSON.stringify(inventoryModule(exportsFixture, 'mvc-app')), JSON.stringify(inventory));
assert(!api.interface.some(item => item.name === 'View'), 'MVC must not be merged into pdg root exports');

assert.strictEqual(memberResultComment(member('Sprite', 'findPart')), ' // can return null');
assert.strictEqual(memberResultComment(member('Rect', 'add')), ' // returns self for chaining');
assert.strictEqual(memberResultComment(member('Rect', 'plus')), '');
assert(!coreHeader.includes('// returns new '));
assert.strictEqual(memberResultComment(member('Part', 'getTransform')), ' // returns a new copy');
assert(coreHeader.includes('AffineTransform getTransform (int space = partSpace_Local); // returns a new copy\n'));


assert(!memberDocumentation(member('Rect', 'add')).includes('JavaScript result'));
assert(memberDocumentation(member('NetClient', 'connection')).includes('\\c false'));
assert.strictEqual(memberDocumentation(generated.interface.find(m => m.name === 'createSerializableObject')), '');
assert.strictEqual(memberDocumentation(member('FileManager', 'findNext')), '');
assert(memberDocumentation(member('AnimationContactTarget', 'update')).includes(frameContract.condition));
assert(memberDocumentation(member('NetConnection', 'onMessage')).includes('\\ref pdg::NetMessageCallback'));
assert(!coreHeader.includes('\\par Type of '));
const rendered = schemaDocumentation(api.schemas);
assert(!rendered.includes('namespace contracts'));
assert(!coreHeader.includes('contracts::'));
for (const [name, schema] of Object.entries(api.schemas)) {
    const declaration = rendered.indexOf('\nstruct ' + name + ' {');
    assert(declaration >= 0, name);
    const comment = rendered.slice(rendered.lastIndexOf('/**', declaration), declaration);
    assert.strictEqual(comment.includes('\\ingroup StructuredDataTypes'),
        ['record', 'context', 'alias', 'event_map'].includes(schema.kind), name);
}
assert(rendered.includes('struct AnimationDrawableOptions'));
assert(rendered.includes('Must return synchronously'));
assert(rendered.includes('Documentation-only JavaScript shape'));
assert(moduleDocumentation(inventory).includes('mvc_export_View'));
assert(moduleDocumentation(inventory).includes('mvc_export_nested_View'));
console.log('PASS: precise API contracts, overloads, receiver returns, stale metadata rejection, and safe module inventory');

assert.throws(() => enrich({interface:[]}, {version:1,members:{},schemas:{
    A:{kind:'record',extends:['B']}, B:{kind:'record',extends:['A']}
}}), /Cyclic API schema inheritance/);
assert.throws(() => enrich({interface:[]}, {version:1,members:{},schemas:{
    A:{kind:'record',extends:['Absent']}
}}), /Invalid API schema base/);
const selective = enrich({name:'pdg',interface:[{name:'send',type:'function',params:[
    [{name:'message',type:'string'}],[{name:'message',type:'object'}]
]}]}, {version:1,schemas:{Message:{kind:'record',fields:{id:{type:'number'}}}},members:{
    'pdg.send':{params:{message:{when_type:'object',schema:'Message'}}}
}});
assert(!selective.interface[0].params[0][0].contract);
assert.equal(selective.interface[0].params[1][0].contract.schema,'Message');
