'use strict';
const assert = require('assert');
const fs = require('fs');
const vm = require('vm');
const os = require('os');
const path = require('path');
const extractor = require('../../tools/interface-metadata-source');
const {install} = require('../../src/js/interface_metadata');
const declarations = require('../../src/js/interface_metadata_data');
const {validate, build} = require('../../tools/build-interface-metadata');
const copy = value => JSON.parse(JSON.stringify(value));

// The same native calls produce direct, indexed and type-selected C mappings.
function cMethod(owner,name) { return declarations.interface.find(c=>c.name===owner).interface.find(m=>m.name===name); }
assert.deepStrictEqual(cMethod('CpArbiter','getDepth').native_c_dispatch,
    {cases:[{arguments:['i'],symbol:'cpArbiterGetDepth'}],index:{count:'cpArbiterGetCount',parameter:'i'}});
assert.deepStrictEqual(cMethod('CpConstraint','getSpringStiffness').native_c_dispatch.cases.map(c=>[c.symbol,c.predicate]),
    [['cpDampedSpringGetStiffness','cpConstraintIsDampedSpring'],['cpDampedRotarySpringGetStiffness','cpConstraintIsDampedRotarySpring']]);
assert.deepStrictEqual(cMethod('CpConstraint','getPinDist').returns_contract,
    {one_of:[{type:'number'},{type:'undefined'}]});
assert.deepStrictEqual(cMethod('CpConstraint','setPinDist').returns_contract,{type:'this'});
assert.strictEqual(cMethod('CpConstraint','getSprite').native_c_dispatch,undefined);
assert.strictEqual(cMethod('CpSpace','step').native_c_dispatch.cases[0].symbol,'cpSpaceStep');

// Named and collective recorder APIs derive from the native command inventory.
const recorderCommands = require('../../tools/animation-recorder').commands();
assert.deepStrictEqual(declarations.animation_commands, recorderCommands);
const animatedNames = new Set(declarations.interface.find(c=>c.name==='Animated').interface.map(m=>m.name));
for (const owner of ['AnimationScript','Troupe']) {
    const members = declarations.interface.find(c=>c.name===owner).interface;
    for (const command of recorderCommands) {
        if (animatedNames.has(command.name)) continue;
        const method = members.find(m=>m.name===command.name);
        assert(method, owner+'.'+command.name);
        assert.strictEqual(method.native, false);
        assert.deepStrictEqual(method.returns_contract, {type:'this'});
    }
}
require('child_process').execFileSync(process.execPath,
    [path.resolve(__dirname,'../../tools/animation-recorder.js'),'--check']);

// Native syntax is retained separately from the public script type.
const qualifiedSignature=extractor.signature('qualified','[object PhysicsBody&]',
    '([object PhysicsBody*] body = null, [object Point const&] anchor = Point(0,0), [const object Point&] other)');
assert.strictEqual(qualifiedSignature.returns,'object PhysicsBody');
assert.deepStrictEqual(qualifiedSignature.native_return_qualifiers,{indirection:'reference',const:false});
assert.deepStrictEqual(qualifiedSignature.params.map(p=>p.type),['object PhysicsBody','object Point','object Point']);
assert.deepStrictEqual(qualifiedSignature.params[0].native_qualifiers,{indirection:'pointer',const:false});
assert.deepStrictEqual(qualifiedSignature.params[1].native_qualifiers,{indirection:'reference',const:true});
assert.strictEqual(qualifiedSignature.params[1].default_value,'Point(0,0)');
assert.deepStrictEqual(qualifiedSignature.params[2].native_qualifiers,qualifiedSignature.params[1].native_qualifiers);
for(const type of ['object Point**','object const Point const&','object Point* const','object Point const'])
    assert.throws(()=>extractor.signature('', '['+type+']', '()'),/Invalid native-qualified type/);

assert.deepStrictEqual(extractor.signature('', 'undefined', '([object Spline&&] spline)').params[0].native_qualifiers,
    {indirection:'rvalue-reference',const:false});

// Independent alternatives form a Cartesian product, preserving native identity
// and defaults. An alternative may still expand to several arguments.
const colorAlternatives = extractor.signature('', '[this]',
    '({[object Color const&] start|string startName|number startRGBA}, {[object Color const&] end|string endName|number endRGBA}, number seconds = 1)');
assert.strictEqual(colorAlternatives.params.length,9);
assert.deepStrictEqual(colorAlternatives.params[0][0].native_qualifiers,{indirection:'reference',const:true});
assert.deepStrictEqual(colorAlternatives.params[5].map(p=>p.type),['string','number','number']);
assert(colorAlternatives.params.every(params=>params[2].default_value==='1'));
assert.strictEqual(extractor.signature('', 'undefined',
    '({[object Point] point|number x, number y}, {string name|number id})').params.length,4);
assert.throws(()=>extractor.signature('', 'undefined','({string name|number id)'),/Unclosed/);

// Audit representatives cover shared macros, overloads, factories and native moves.
assert.deepStrictEqual(cMethod('Port','setFontForStyle').native_parameter_order,['font','style']);
for (const [owner,name,param,kind,isConst] of [
    ['Sprite','serialize','serializer','pointer',false],
    ['Serializer','sizeof_point','val','reference',true],
    ['Part','solveIK','middle','pointer',false],
    ['Part','solveIK','target','reference',true],
    ['Drawing','addSpline','spline','rvalue-reference',false],
    ['Drawing','addPolygon','polygon','rvalue-reference',false],
    ['Port','setClipRect','inClipRect','reference',true]
]) {
    const member=cMethod(owner,name);
    assert.deepStrictEqual(member.params.find(p=>p.name===param).native_qualifiers,
        {indirection:kind,const:isConst},owner+'.'+name+'.'+param);
}
assert.deepStrictEqual(cMethod('Attributes','getLineColor').native_return_qualifiers,
    {indirection:'reference',const:true});
assert.strictEqual(cMethod('Spline','addPoint').params[0].native_qualifiers,undefined,'Spline takes Point by value');
assert.strictEqual(cMethod('MemBlock','getData').native_return_qualifiers,undefined,'Byte arrays are copied script values');
assert.strictEqual(cMethod('Polygon','intersection').native_return_qualifiers,undefined,'Native result is a Polygon value');

// Canonical ordering ignores source order, while positional arrays stay intact.
const {alphabeticalOrder} = require('../../tools/api-contracts');
const unordered = {name:'pdg', schemas:{Z:{fields:{z:{type:'number'},a:{type:'number'}}},A:{}}, interface:[
    {name:'beta', interface:[{name:'z'}, {name:'a', params:[{name:'y'}, {name:'x'}],
        native_binding:{overloads:[{parameters:['y','x']}, {parameters:['point']}]}}]},
    {name:'Alpha'}, {name:'alpha'}
]};
const ordered = alphabeticalOrder(unordered);
assert.deepStrictEqual(Object.keys(ordered), ['interface','name','schemas']);
assert.deepStrictEqual(ordered.interface.map(item => item.name), ['Alpha','alpha','beta']);
assert.deepStrictEqual(ordered.interface[2].interface.map(item => item.name), ['a','z']);
assert.deepStrictEqual(ordered.interface[2].interface[0].params.map(item => item.name), ['y','x']);
assert.deepStrictEqual(ordered.interface[2].interface[0].native_binding.overloads.map(item => item.parameters), [['y','x'],['point']]);
assert.deepStrictEqual(Object.keys(ordered.schemas), ['A','Z']);
assert.deepStrictEqual(Object.keys(ordered.schemas.Z.fields), ['a','z']);
assert.deepStrictEqual(alphabeticalOrder(ordered), ordered);
assert.strictEqual(unordered.interface[0].name, 'beta');

// A poisoned export surface proves introspection does not call any engine code.
const exportsForTest = {};
for (const entry of declarations.interface) {
    Object.defineProperty(exportsForTest, entry.name, {
        enumerable: true, configurable: true,
        get() { throw Error('Introspection invoked accessor: ' + entry.name); }
    });
}
// Installation adds these two exports, so leave them writable.
delete exportsForTest.getInterfaceMetadata;
delete exportsForTest.describeInterface;
install(exportsForTest, declarations);
const api = exportsForTest.getInterfaceMetadata();
assert.strictEqual(api.metadata_version, 1);
assert.strictEqual(api.interface.length, declarations.interface.length);
assert.strictEqual(api.interface.find(item => item.name === 'running').value, undefined);
const move = exportsForTest.getInterfaceMetadata('Polygon', 'moveTo');
assert.deepStrictEqual(move.params.map(params => params.map(param => param.name)), [['point'], ['x', 'y']]);
assert.strictEqual(move.native_binding.overloads[1].binding_name, '_moveToXY');
assert.strictEqual(move.returns, 'this'); // Native overloads inherit the receiver return policy.
move.params[0][0].name = 'changed';
assert.strictEqual(exportsForTest.getInterfaceMetadata('Polygon', 'moveTo').params[0][0].name, 'point');
assert(exportsForTest.describeInterface('Polygon', 'moveTo').includes('number x, number y'));
assert(exportsForTest.describeInterface('Polygon', 'moveTo').includes('object Point point'));
assert.strictEqual(exportsForTest.getInterfaceMetadata('Camera', 'moveTo').inherited_from, 'Animated');
assert.strictEqual(exportsForTest.getInterfaceMetadata('Rect', 'assign').returns_contract.type, 'this');
assert.strictEqual(exportsForTest.getInterfaceMetadata('Polygon', 'addPoint').returns, 'this');
assert.strictEqual(exportsForTest.getInterfaceMetadata('Rect', 'plus').returns, 'object Rect');
assert(!extractor.readContracts().members['Polygon.addPoint']);
assert.strictEqual(exportsForTest.getInterfaceMetadata('Rect', 'plus').returns_contract.ownership, 'owned');
assert.strictEqual(exportsForTest.getInterfaceMetadata('FileManager', 'findNext').native_binding.adapter, 'file.find-next');
for (const [name, singleton] of Object.entries({FileManager:'fs', LogManager:'lm', ConfigManager:'cfg',
    ResourceManager:'res', EventManager:'evt', TimerManager:'tm', GraphicsManager:'gfx', SoundManager:'snd'})) {
    const manager = exportsForTest.getInterfaceMetadata(name);
    assert.strictEqual(manager.singleton, singleton);
    assert.strictEqual(manager.note, 'Primary access via singleton instance: pdg.'+singleton);
}
for (const name of ['EventManager','TimerManager']) {
    const manager = exportsForTest.getInterfaceMetadata(name);
    assert.deepStrictEqual(manager.implements, ['EventEmitter']);
    assert.strictEqual(manager.native_binding.base, 'pdg::EventEmitter');
}
assert.throws(() => exportsForTest.getInterfaceMetadata('Missing'), RangeError);
assert.throws(() => exportsForTest.getInterfaceMetadata('Polygon', 'missing'), RangeError);
assert.throws(() => exportsForTest.getInterfaceMetadata(null), TypeError);

const headless = {Animated() { throw Error('Constructor called'); }};
install(headless, declarations);
assert(!headless.getInterfaceMetadata().interface.some(item => item.name === 'Camera'));
assert.throws(() => headless.getInterfaceMetadata('Camera'), RangeError);

const source = require('../../tools/interface-metadata-source').inventory().api;
assert.throws(() => validate(copy(source), {}), /Unknown native adapter:/);
const invalidPolicy = copy(source);
invalidPolicy.interface.find(item => item.name === 'Polygon').interface.find(item => item.name === 'moveTo')
    .native_binding.overloads[0].return_policy = 'guess';
assert.throws(() => validate(invalidPolicy), /Invalid return policy/);
assert.doesNotThrow(() => validate(copy(source)), 'Overloads may inherit their return policy');
const invalidQualifiers=copy(source);
invalidQualifiers.interface.find(c=>c.name==='Camera').interface.find(m=>m.name==='getEffects').native_return_qualifiers.indirection='owned';
assert.throws(()=>validate(invalidQualifiers),/Invalid native qualifiers/);

const polygon = source.interface.find(item => item.name === 'Polygon');
polygon.interface.find(item => item.name === 'moveTo').native_binding.overloads[0].parameters = ['wrong'];
assert.throws(() => validate(copy(source)), /Native overload parameters/);
const cyclic = {metadata_version: 1, name: 'pdg', interface: [
    {name: 'A', type: 'class', implements: ['B'], interface: []},
    {name: 'B', type: 'class', implements: ['A'], interface: []}
]};
assert.throws(() => validate(cyclic), /Cyclic/);
assert.strictEqual(fs.readFileSync('src/js/interface_metadata_data.js', 'utf8'), build());
const generator = fs.readFileSync('tools/make-idl.js', 'utf8');
assert(!generator.includes('inspect(pdg'));
assert(!generator.includes('_fakeCreate'));
assert(generator.includes('pdg.getInterfaceMetadata()'));
// Exercise the source-driven Embind renderer with structured data, including an
// overload and an adapter. No live PDG objects or native calls are available.
const fixture = {name: 'pdg', interface: [
    {name: 'Polygon', type: 'class', native: true, native_binding: {type: 'pdg::Polygon'},
        interface: [exportsForTest.getInterfaceMetadata('Polygon', 'moveTo')]},
    {name: 'FileManager', type: 'class', native: true, native_binding: {type: 'pdg::FileManager'},
        interface: [exportsForTest.getInterfaceMetadata('FileManager', 'findNext')]}
], binding_adapters: declarations.binding_adapters};
function generate(api, format = '--embind-format', options = []) {
    let output = '';
    vm.runInNewContext(generator, {
        require(name) {
            if (name === 'pdg') return {argv: ['pdg', 'make-idl.js', format, ...options], getInterfaceMetadata() { return copy(api); }};
            if (name === './api-contracts') return require('../../tools/api-contracts');
            throw Error('Unexpected generator dependency: ' + name);
        },
        process: {env: {}, stdout: {write(value) { output += value; }}, stderr: {write() {}}}
    });
    return output;
}
const shuffledOutput = JSON.parse(generate(unordered, '--json-format'));
assert.deepStrictEqual(shuffledOutput.interface.map(item => item.name), ['Alpha','alpha','beta']);
assert.deepStrictEqual(shuffledOutput.interface[2].interface.map(item => item.name), ['a','z']);
assert.deepStrictEqual(shuffledOutput.interface[2].interface[0].params.map(item => item.name), ['y','x']);
assert.deepStrictEqual(Object.keys(shuffledOutput.schemas.Z.fields), ['a','z']);
const mixedFixture = {name:'pdg', schemas:{}, interface:[
    {name:'Mixed', type:'class', native:true, implements:[], interface:[
        {name:'zConstant', type:'number', native:true, readonly:true, value:7},
        {name:'zProperty', type:'number', native:true},
        {name:'zMethod', type:'function', native:true, brief:'', params:[]},
        {name:'aMethod', type:'function', native:true, brief:'', params:[]},
        {name:'Mixed', type:'constructor', native:true, brief:'', params:[]}
    ]}
]};
for (const format of ['--doxygen-h-format','--js-format']) {
    const text = generate(mixedFixture, format);
    assert(text.indexOf('aMethod') < text.indexOf('zMethod'), 'Methods must be alphabetical: '+format);
    assert(text.indexOf('zConstant') < text.indexOf('zProperty') && text.indexOf('zProperty') < text.indexOf('aMethod'),
        'Constants and properties must precede methods: '+format);
}
const mixedOrder = JSON.parse(generate(mixedFixture, '--json-format')).interface[0].interface;
assert.deepStrictEqual(mixedOrder.map(item => item.name), ['zConstant','zProperty','Mixed','aMethod','zMethod']);
const namespaceFixture = {name:'pdg', type:'module', schemas:{}, interface:[
    mixedFixture.interface[0], {name:'aFunction', type:'function', params:[]},
    {name:'aProperty', type:'number'}, {name:'zConstant', type:'number', readonly:true, value:7}
]};
assert.deepStrictEqual(JSON.parse(generate(namespaceFixture, '--json-format')).interface.map(item => item.name),
    ['zConstant','aProperty','aFunction','Mixed']);
const {renderBinding} = require('../../tools/emscripten/generate');
fixture.interface.push(copy(declarations.interface.find(c => c.name === 'Point')));
const embind = fixture.interface.filter(c => ['Polygon','FileManager'].includes(c.name)).map(owner => renderBinding(owner, owner.interface[0], fixture)).join('\n');
assert.throws(() => generate(fixture), /Use node tools\/emscripten\/generate.js/);
assert(embind.includes('EmscriptenMethodPointer<pdg::Polygon, pdg::Polygon&(float, float)>'));
assert(embind.includes('"_moveToXY"'));
assert(embind.includes('return_value_policy::reference()'));
assert(embind.includes('select_overload<bool(pdg::FileManager&, emscripten::val)>(&pdg::emscriptenFileFindNext)'));
delete fixture.interface[0].interface[0].native_binding;
assert.throws(() => renderBinding(fixture.interface[0], fixture.interface[0].interface[0], fixture), /Missing native mapping: Polygon.moveTo/);
const inheritedFixture = {name:'pdg', schemas:{}, interface:[
    {name:'Derived', type:'class', implements:['Base'], interface:[
        {name:'inheritedMethod', type:'function', native:true, brief:'', params:[], returns:'this', returns_contract:{type:'this'}, inherited_from:'Base'},
        {name:'ownMethod', type:'function', native:true, brief:'', params:[]}
    ]}
]};
for (const format of ['--doxygen-h-format', '--js-format']) {
    const normal = generate(inheritedFixture, format);
    const comparison = generate(inheritedFixture, format, ['--include-inherited']);
    assert(normal.includes('ownMethod'));
    assert(!normal.includes('inheritedMethod'));
    assert(comparison.includes('ownMethod'));
    assert(comparison.includes('inheritedMethod'));
    if (format === '--doxygen-h-format') {
        assert(comparison.includes('Derived inheritedMethod ('));
        assert(!comparison.includes('returns self for chaining'));
    }
    if (format === '--js-format') assert(comparison.includes('return this;'));
}
assert(generate(inheritedFixture, '--json-format').includes('inheritedMethod'));
// TileLayer repeats native event wrappers but inherits their public API through
// SpriteLayer. Generic EventEmitter registrations must also follow that chain.
const tile = declarations.interface.find(item => item.name === 'TileLayer');
assert.strictEqual(tile.interface.find(item => item.name === 'onErasePort').inherited_from, 'SpriteLayer');
assert.strictEqual(tile.interface.find(item => item.name === 'addHandler').inherited_from, 'EventEmitter');
assert(!tile.interface.find(item => item.name === 'getTileSize').inherited_from);
assert(!declarations.interface.find(item => item.name === 'Camera').interface
    .find(item => item.name === 'animate').inherited_from, 'Keep explicit overrides outside inherited groups');
assert(!extractor.readContracts().members['TileLayer.onErasePort'], 'Inheritance comes from the base, not duplicate annotations');
const tileFixture = {name:'pdg', schemas:{}, interface:[tile]};
for (const format of ['--doxygen-h-format', '--js-format']) {
    const normal = generate(tileFixture, format);
    const comparison = generate(tileFixture, format, ['--include-inherited']);
    assert(normal.includes('getTileSize'));
    for (const member of tile.interface.filter(item => item.inherited_from && item.type === 'function')) {
        const declaration = new RegExp('\\b'+member.name+'\\s*(?:\\(|:)');
        assert(!declaration.test(normal), 'Inherited TileLayer method leaked: '+member.name);
        assert(declaration.test(comparison), 'Inherited TileLayer method missing: '+member.name);
    }
}
// Editing a binding signature changes extracted metadata immediately; no
// inventory file is involved. The JavaScript fixture's throwing body is parsed
// without being invoked.
const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'pdg-metadata-source-'));
try {
    const groupsCpp = path.join(temporary, 'groups.cpp');
    fs.writeFileSync(groupsCpp,
        '#define EXTRA_METHODS(klass) METHODS_FROM(klass, Base, HAS_METHOD(klass, "extra", Extra))\n'+
        '#define BASE_METHODS(klass) METHODS_FROM(klass, Base, HAS_METHOD(klass, "shared", Shared) EXTRA_METHODS(klass))\n'+
        'EXPORT_CLASS_SYMBOLS("Derived", Derived, , , BASE_METHODS(Derived) HAS_METHOD(Derived, "own", Own))\n');
    const grouped = extractor.extractNative([groupsCpp]);
    assert.strictEqual(grouped.bindings.get('Derived.shared').origin, 'Base');
    assert.strictEqual(grouped.bindings.get('Derived.extra').origin, 'Base');
    assert.strictEqual(grouped.bindings.get('Derived.own').origin, undefined);
    fs.writeFileSync(groupsCpp,
        '#define BASE_METHODS(klass) METHODS_FROM(klass, Base, METHOD(klass, Shared) PROPERTY(klass, Value))\n'+
        'BINDING_CLASS(Derived) BASE_METHODS(Derived) METHOD(Derived, Own)\n');
    const declaredGroups = extractor.extractNative([groupsCpp]);
    assert.strictEqual(declaredGroups.declaredOrigins.get('Derived.Shared'), 'Base');
    assert.strictEqual(declaredGroups.declaredOrigins.get('Derived.SetValue'), 'Base');
    assert.strictEqual(declaredGroups.declaredOrigins.get('Derived.Own'), undefined);
    const classesCpp = path.join(temporary,'classes.cpp');
    fs.writeFileSync(classesCpp,
        'BINDING_CLASS(NativeAlias)\nSINGLETON_CLASS(Single)\nWRAPPER_CLASS(Wrapped)\nFACADE_CLASS(Facade)\n'+
        'EXPORT_CLASS_SYMBOLS("PublicAlias", NativeAlias, , , )\n');
    const extractedClasses = extractor.extractNative([classesCpp]);
    assert.strictEqual(extractedClasses.classes.get('NativeAlias').name, 'PublicAlias');
    assert.deepStrictEqual([...extractedClasses.declarations].map(([name, value]) => [name, value.kind]),
        [['NativeAlias','binding'], ['Single','singleton'], ['Wrapped','wrapper'], ['Facade','facade']]);
    const ownershipCpp = path.join(temporary, 'ownership.cpp');
    fs.writeFileSync(ownershipCpp, 'SINGLETON_MANAGER_INITIALIZER_IMPL(Manager, "mgr")\n');
    assert.deepStrictEqual([...extractor.extractNative([ownershipCpp]).singletons], [['Manager','mgr']]);
    fs.writeFileSync(ownershipCpp,
        'WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(Custom, save(cppObj,obj); cppObj->addRef())\n'+
        'WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(Factory, "Owner.create", save(cppObj,obj); cppObj->addRef())\n'+
        'WRAPPER_INITIALIZER_IMPL_CUSTOM(Ordinary, save(cppObj,obj))\n');
    assert.deepStrictEqual([...extractor.extractNative([ownershipCpp]).ownership],
        [['Custom','retained'], ['Factory','retained']]);
    fs.writeFileSync(ownershipCpp, 'WRAPPER_INITIALIZER_IMPL_CUSTOM(Custom, save(cppObj,obj))\n');
    assert.strictEqual(extractor.extractNative([ownershipCpp]).ownership.size, 0);
    assert.deepStrictEqual(declarations.interface.filter(item => item.native_binding && item.native_binding.ownership === 'retained')
        .map(item => item.name).sort(),
        ['AnimationScript','Bone','Camera','Collider','CollisionQueryBuffer','Part','Particle','ParticleEmitter','PhysicsBody','PhysicsConstraint','Scene','Sprite','Troupe'].sort());
    const cpp = path.join(temporary,'fixture.cpp');
    const writeCpp = defaultValue => fs.writeFileSync(cpp,
        'EXPORT_CLASS_SYMBOLS("Fixture", Fixture, , , HAS_METHOD(Fixture, "moveTo", MoveTo))\n'+
        'METHOD_IMPL(Fixture, MoveTo)\nMETHOD_SIGNATURE("move", [object Fixture], 1, (number x = '+defaultValue+'))\n');
    writeCpp(12);
    assert.strictEqual(extractor.extractNative([cpp]).methods.get('Fixture.MoveTo').params[0].default_value,'12');
    writeCpp(23);
    assert.strictEqual(extractor.extractNative([cpp]).methods.get('Fixture.MoveTo').params[0].default_value,'23');
    fs.writeFileSync(cpp,
        'SERIALIZER_SIZE_OF_METHOD_IMPL(4)\n'+
        'SERIALIZER_SIZE_OF_METHOD_IMPL(rect)\n'+
        'CUSTOM_SERIALIZER_SIZE_OF_METHOD_IMPL(ref, size_t n = 0)\n');
    const serializerMethods = extractor.extractNative([cpp]).methods;
    for (const [name, type] of [['4','number int'], ['rect','object Rect'], ['ref','object']]) {
        const method = serializerMethods.get('Serializer.Sizeof_' + name);
        assert.deepStrictEqual(method.params, [{name:'val', type}]);
        assert.strictEqual(method.returns, 'number uint');
        assert(method.brief.includes('serialize'));
    }
    assert(!extractor.annotations().some(record => record.kind === 'member' && record.data.name.startsWith('Serializer.sizeof_') && record.data.params),
        'Serializer size signatures must still come from the native macros');
    fs.writeFileSync(cpp, `
METHOD_IMPL(Fixture, Byte)
METHOD_SIGNATURE("", undefined, 1, ([number uint] value));
REQUIRE_ARG_COUNT(1);
REQUIRE_UINT8_ARG(1, value);
self->write(value);
METHOD_IMPL(Fixture, SignedByte)
METHOD_SIGNATURE("", undefined, 1, ([number int] value));
REQUIRE_ARG_COUNT(1);
REQUIRE_INT8_ARG(1, value);
METHOD_IMPL(Fixture, Conditional)
METHOD_SIGNATURE("", undefined, 1, (number value));
REQUIRE_ARG_COUNT(1);
if (something) { REQUIRE_NUMBER_ARG(1, value); }
METHOD_IMPL(Fixture, Partial)
METHOD_SIGNATURE("", undefined, 2, (number x, number y));
REQUIRE_ARG_COUNT(2);
REQUIRE_NUMBER_ARG(1, x);
if (something) { REQUIRE_NUMBER_ARG(2, y); }
METHOD_IMPL(Fixture, Optional)
METHOD_SIGNATURE("", undefined, 1, (number value = 0));
REQUIRE_ARG_COUNT(1);
REQUIRE_NUMBER_ARG(1, value);
METHOD_IMPL(Fixture, Word)
METHOD_SIGNATURE("", undefined, 1, ([number uint] value));
REQUIRE_ARG_COUNT(1);
REQUIRE_UINT32_ARG(1, value);
METHOD_IMPL(Fixture, FormattedWord) CR
METHOD_SIGNATURE("", undefined, 1, ([number uint] value)); CR
REQUIRE_ARG_COUNT(1); CR
REQUIRE_UINT32_ARG(1, value);
`);
    const validated = extractor.extractNative([cpp]).methods;
    assert.deepStrictEqual(validated.get('Fixture.Byte').validation, {arity:1,parameters:[
        {index:0,name:'value',type:'number',integer:true,min:0,max:255}]});
    assert.deepStrictEqual(validated.get('Fixture.SignedByte').validation, {arity:1,parameters:[
        {index:0,name:'value',type:'number',integer:true,min:-128,max:127,conversion:'int32'}]});
    assert.deepStrictEqual(validated.get('Fixture.Word').validation, {arity:1,parameters:[
        {index:0,name:'value',type:'number',conversion:'uint32'}]});
    assert.deepStrictEqual(validated.get('Fixture.FormattedWord').validation,validated.get('Fixture.Word').validation);
    for (const name of ['Conditional','Partial','Optional'])
        assert.strictEqual(validated.get('Fixture.'+name).validation, undefined, name+' must not infer unconditional validation');
    fs.writeFileSync(cpp, `
METHOD_IMPL(Fixture, Ease)
METHOD_SIGNATURE("", [this], 2, (number amount, [number int] curve = linearTween));
self->customMethod(amount, easingIdToFunc(curve));
METHOD_IMPL(Fixture, TableEase)
METHOD_SIGNATURE("", [this], 1, ([number int] curve));
self->customMethod(gEasingFunctions[curve]);
METHOD_IMPL(Fixture, NotEase)
METHOD_SIGNATURE("", [this], 1, ([number int] curve));
const char* text = "easingIdToFunc(curve)";
`);
    const easingMethods = extractor.extractNative([cpp]).methods;
    assert.deepStrictEqual(easingMethods.get('Fixture.Ease').params[1].contract,{schema:'EasingFunction'});
    assert.deepStrictEqual(easingMethods.get('Fixture.TableEase').params[0].contract,{schema:'EasingFunction'});
    assert.strictEqual(easingMethods.get('Fixture.NotEase').params[0].contract,undefined);
    fs.writeFileSync(cpp, `
METHOD_IMPL(Fixture, Project)
METHOD_SIGNATURE("", [object RotatedRect], 1, ([object Rect] bounds));
pdg::RotatedRect bounds;
RotatedRect out = self->transformRegion(bounds);
{ args.GetReturnValue().Set(v8_MakeJavascriptRect(isolate, out)); }
METHOD_IMPL(Fixture, Adjust)
METHOD_SIGNATURE("", [object Point], 1, ([object Point] point));
pdg::Point point;
Point out = self->transformPoint(point);
out.x += 1;
{ args.GetReturnValue().Set(v8_MakeJavascriptPoint(isolate, out)); }
`);
    const valueMethods=extractor.extractNative([cpp]).methods;
    assert.deepStrictEqual(valueMethods.get('Fixture.Project').value_call,
        {method:'transformRegion',result:'RotatedRect',argument:'RotatedRect'});
    assert.strictEqual(valueMethods.get('Fixture.Adjust').value_call,undefined,
        'Do not discard postprocessing after a native call');
    const js = path.join(temporary,'fixture.js');
    fs.writeFileSync(js, 'var getter = bindings.getManager; bindings.mgr = getter(); bindings.other = bindings.getOther();');
    assert.deepStrictEqual([...extractor.extractJavaScript([js]).singletons], [['getManager','mgr'], ['getOther','other']]);
    fs.writeFileSync(js,
        '// @pdg-member {"name":"Fixture.moveTo","type":"function","brief":"move","returns":"object Fixture","params":[{"name":"x","type":"number","optional":true,"default_value":"34"}]}\n'+
        'class Fixture { moveTo(x) { throw Error("must not run"); } }');
    assert(extractor.extractJavaScript([js]).methods.has('Fixture.moveTo'));
    assert.strictEqual(extractor.annotations([js])[0].data.params[0].default_value, '34');
    for (const file of extractor.sourceFiles().filter(file => file.endsWith('.js')))
        assert(!fs.readFileSync(file, 'utf8').includes('methodSignature'), 'Legacy signature helper remains in ' + file);

} finally { fs.rmSync(temporary,{recursive:true,force:true}); }
assert(!fs.existsSync('src/bindings/api/interface-metadata.json'));
assert(!fs.existsSync('src/bindings/api/javascript-contracts.js'));
assert(!fs.existsSync('src/bindings/api/native-adapters.json'));
console.log('Structured interface metadata checks passed');

// Captured runtime profiles are data supplied by the loader, never guessed by
// the declaration generator or inferred by executing engine accessors.
const profiled = {};
install(profiled, declarations, {runtime:'test', capabilities:{graphics:false},scope:'fixture'});
const firstProfile = profiled.getInterfaceMetadata();
assert.strictEqual(firstProfile.runtime_profile.runtime,'test');
firstProfile.runtime_profile.capabilities.graphics = true;
assert.strictEqual(profiled.getInterfaceMetadata().runtime_profile.capabilities.graphics,false);
