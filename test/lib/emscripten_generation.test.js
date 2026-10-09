'use strict';
const assert = require('assert');
const fs = require('fs');
const path = require('path');
const vm = require('vm');
const {generate, fingerprint, renderBinding, wrapperSpec, outputs} = require('../../tools/emscripten/generate');
const {install, installReturns, installReceivers, installValidation, rememberAnimationOwner,
    canonicalRetained, objectForIdentity, forgetObject, installEvents} = require('../../src/bindings/emscripten/pdg_em_runtime');
const root = path.resolve(__dirname, '../..');
const copy = value => JSON.parse(JSON.stringify(value));

// Check the actual source-driven output, without loading any PDG runtime.
const generated = outputs();
for (const [name, content] of generated) assert.strictEqual(fs.readFileSync(path.join(root, name), 'utf8'), content, name);
assert.deepStrictEqual([...outputs()], [...generated], 'Generation is deterministic');
const report = JSON.parse(generated.get('src/bindings/emscripten/coverage.json'));
assert(report.members.some(entry => entry.name === 'MemBlock.getData' && entry.status === 'generated'));
assert(report.members.some(entry => entry.name === 'FileManager.findNext' && entry.status === 'adapter'));
assert(report.counts['manual-unverified'] > 0, 'Do not claim legacy coverage as verified');
// Reviews must enumerate the remaining work, without stale or duplicate entries.
for (const [filename, status] of [
    ['manual-bindings-review.json', 'manual-unverified'],
    ['adapter-bindings-review.json', 'adapter']
]) {
    const review = JSON.parse(fs.readFileSync(path.join(root, 'tools/emscripten', filename), 'utf8'));
    const names = review.groups.flatMap(group => {
        assert.strictEqual(group.count, group.members.length, group.id);
        assert(group.reason && group.next_step, group.id);
        return group.members.map(member => member.name);
    });
    assert.strictEqual(review.count, names.length, filename);
    assert.strictEqual(new Set(names).size, names.length, filename);
    assert.deepStrictEqual(names.sort(), report.members.filter(m => m.status === status).map(m => m.name).sort(), filename);
    if (review.inventory_sha256) assert.strictEqual(review.inventory_sha256,
        require('crypto').createHash('sha256').update(fs.readFileSync(path.join(root, review.inventory))).digest('hex'));
}
const customSource = fs.readFileSync(path.join(root, 'src/bindings/emscripten/pdg_em_custom.inc'), 'utf8');
assert(!/\b\w+_Extra\b/.test(customSource), 'Routine registrations must not hide behind Extra macros');
assert(!customSource.includes('@pdg-custom Font'), 'All Font registrations are metadata-owned');
assert(!customSource.includes('EmscriptenCheckedMethod'), 'Checked member registrations belong to metadata');
const production = generated.get('src/bindings/emscripten/pdg.embind');
// C-function dispatch is driven by extracted calls, not class/method lookup tables.
const cOwner={name:'Opaque',native_binding:{type:'pdg::Opaque',browser:{generate:true}}};
const cApi={name:'pdg',schemas:{},binding_adapters:{},interface:[]};
const cMember={name:'getPoint',type:'function',native:true,params:[{name:'i',type:'number int'}],
    returns:'object Point',native_c_dispatch:{index:{parameter:'i',count:'nativeCount'},
        cases:[{symbol:'nativePoint',arguments:['i']}]}};
assert(renderBinding(cOwner,cMember,cApi).includes('EmscriptenCDispatch<pdg::Point, &nativeCount, pdg::EmscriptenCCase<&nativePoint, nullptr>>'));
const cSet={name:'setAnchor',type:'function',native:true,params:[{name:'anchor',type:'object Offset'}],
    returns:'this',native_c_dispatch:{cases:[{symbol:'nativeSet',predicate:'nativeIsJoint',arguments:['cpv(anchor.x, anchor.y)']}]}};
assert(renderBinding(cOwner,cSet,cApi).includes('EmscriptenCDispatch<void, nullptr, pdg::EmscriptenCCase<&nativeSet, &nativeIsJoint>>'));
const badC=copy(cSet); badC.native_c_dispatch.cases[0].arguments=['anchor + 1'];
assert.throws(()=>renderBinding(cOwner,badC,cApi),/argument transformation/);
badC.native_c_dispatch.cases[0].arguments=[];
assert.throws(()=>renderBinding(cOwner,badC,cApi),/argument transformation/);
assert.notStrictEqual(fingerprint(cSet,cOwner,cApi),fingerprint(badC,cOwner,cApi));
const sequentialC=copy(cMember); sequentialC.native_c_dispatch.cases.push({symbol:'anotherCall',arguments:['i']});
assert.throws(()=>renderBinding(cOwner,sequentialC,cApi),/distinct predicates/);
const repeatedC=copy(cSet); repeatedC.native_c_dispatch.cases.push(copy(repeatedC.native_c_dispatch.cases[0]));
assert.throws(()=>renderBinding(cOwner,repeatedC,cApi),/distinct predicates/);
assert(production.includes('EmscriptenCCase<&cpDampedSpringGetStiffness, &cpConstraintIsDampedSpring>'));
assert(production.includes('EmscriptenCCase<&cpDampedRotarySpringGetStiffness, &cpConstraintIsDampedRotarySpring>'));
assert.strictEqual(report.members.filter(m=>/^Cp(?:Arbiter|Constraint|Space)\./.test(m.name)&&m.status==='generated').length,65);
// Check qualifiers with the host compiler too: both drift directions must fail.
const {spawnSync}=require('child_process');
const cxx=['clang++','g++'].find(command=>spawnSync(command,['--version']).status===0);
assert(cxx,'A C++ compiler is required for signature policy tests');
function compileSignature(result,argument,actualArgument = "Value const&") {
    const fixture=`#include "src/bindings/emscripten/pdg_em_signature.h"
struct Value {}; struct Owner { Value& get(${actualArgument}) const; };
constexpr auto checked=pdg::EmscriptenSignatureCheck<&Owner::get, ${result}, ${argument}>::pointer;`;
    return spawnSync(cxx,['-std=c++20','-fsyntax-only','-x','c++','-iquote',root,'-'],{input:fixture,encoding:'utf8'});
}
const goodSignature=compileSignature('Value&','Value const&');
assert.strictEqual(goodSignature.status,0,goodSignature.stderr);
assert.match(compileSignature('Value*','Value const&').stderr,/native return qualifiers disagree/);
assert.match(compileSignature('Value&','Value&').stderr,/native parameter qualifiers disagree/);
assert.strictEqual(compileSignature('Value&','Value&&','Value&&').status,0);
assert.match(compileSignature('Value&','Value&','Value&&').stderr,/native parameter qualifiers disagree/);
assert(production.includes('pdg::EmscriptenSignatureCheck<&pdg::Port::setFontForStyle, pdg::EmscriptenAnyNativeType, pdg::Font*, pdg::EmscriptenAnyNativeType>'));
assert(production.includes('EmscriptenSignatureCheck<&pdg::Camera::getEffects, pdg::Camera&>'));
assert(production.includes('pdg::PhysicsBody&, pdg::Point const&, pdg::Point const&'));
assert(!customSource.includes('browserRetain(&p.getBodyA())'));
const constOwner={name:'Handle',type:'class',native_binding:{type:'pdg::Handle',ownership:'retained',browser:{generate:true}}};
const constResult={name:'get',type:'function',native:true,params:[],returns:'object Handle',
    native_return_qualifiers:{indirection:'reference',const:true}};
assert.throws(()=>renderBinding(constOwner,constResult,{name:'pdg',interface:[constOwner]}),/Const retained result requires/);


// Constructor defaults use parsed literals, create fresh values and never eval source.
function DefaultPoint(x,y) { this.x=x;this.y=y; }
function DefaultOwner() {}
DefaultOwner.prototype._method=function(point) { return point; };
install({DefaultPoint,DefaultOwner},[{owner:'DefaultOwner',name:'method',schemas:{},constraints:{},calls:[
    {target:'_method',params:[{name:'point',type:'object DefaultPoint',optional:true,default_value:'DefaultPoint(0,0)'}]}
]}]);
const defaultInstance=new DefaultOwner(),firstDefault=defaultInstance.method();
assert(firstDefault instanceof DefaultPoint);
assert.notStrictEqual(defaultInstance.method(),firstDefault);
assert.deepStrictEqual([firstDefault.x,firstDefault.y],[0,0]);

// Retained construction and factory-owned handles share one class policy.
// An explicit custom implementation suppresses only that method's default.
const retainedClass = {name:'Retained',type:'class',native_binding:{type:'pdg::Retained',ownership:'retained',
    browser:{generate:true,constructors:[{types:[],public:true}]}},interface:[
    {name:'Retained',type:'constructor',native:true,params:[]},
    {name:'count',type:'function',native:true,params:[],returns:'number'},
    {name:'special',type:'function',native:true,params:[],returns:'number'}
]};
const retainedClassApi={name:'pdg',schemas:{},interface:[retainedClass]};
const specialMember=retainedClass.interface[2];
const retainedClassManual={sources:[],members:{'Retained.special':fingerprint(specialMember,retainedClass,retainedClassApi)}};
const retainedCustom='// @pdg-custom Retained\n.function("_special", &customSpecial)\n// @pdg-end-custom';
const retainedClassOutput=generate(retainedClassApi,retainedCustom,retainedClassManual);
assert(retainedClassOutput.cpp.includes('.smart_ptr_constructor("RetainedHandle", &pdg::EmscriptenRetainedConstructor<pdg::Retained>::create)'));
assert(retainedClassOutput.cpp.includes('&pdg::Retained::count'));
assert(!retainedClassOutput.cpp.includes('&pdg::Retained::special'));
assert.strictEqual(JSON.parse(retainedClassOutput.coverage).members.find(m=>m.name==='Retained.Retained').status,'generated');
specialMember.native_binding={browser:{generate:true}};
assert.throws(()=>generate(retainedClassApi,retainedCustom.replace('"_special"','"special"'),retainedClassManual),/Duplicate generated registration/);
delete specialMember.native_binding;
delete retainedClass.native_binding.browser.constructors;
retainedClass.interface.shift();
retainedClassManual.members['Retained.special']=fingerprint(specialMember,retainedClass,retainedClassApi);
assert(generate(retainedClassApi,retainedCustom,retainedClassManual).cpp.includes('.smart_ptr<std::shared_ptr<pdg::Retained>>("RetainedHandle")'));
const existingHandle=retainedCustom.replace('.function', '.smart_ptr_constructor("Existing", &customConstructor)\n.function');
assert(!generate(retainedClassApi,existingHandle,retainedClassManual).cpp.includes('.smart_ptr<std::shared_ptr<pdg::Retained>>'));
// Missing capability-guarded entries must not prevent other wrappers loading.
function GuardedClass() {}
const guardedSpec={owner:'GuardedClass',name:'optionalMethod',optional:true,
    calls:[{target:'_optionalMethod',params:[]}],schemas:{},constraints:{}};
install({GuardedClass},[guardedSpec]);
assert.strictEqual(GuardedClass.prototype.optionalMethod,undefined);
assert.throws(()=>install({GuardedClass},[{...guardedSpec,optional:false}]),/Missing generated binding/);
GuardedClass.prototype._optionalMethod=function() { return 7; };
install({GuardedClass},[guardedSpec]);
assert.strictEqual(new GuardedClass().optionalMethod(),7);
assert(production.includes('EmscriptenValueMethod<pdg::SpriteLayer, pdg::RotatedRect, pdg::RotatedRect>::select(&pdg::SpriteLayer::layerToPort)'));
assert(!customSource.includes('layerToPort'), 'Coordinate calls are derived from native value forwarding');
assert(report.eventHelpers > 40, 'Sprite and layer subscriptions are generated');
assert(!production.includes('::onCollideSprite'), 'Script subscriptions do not pretend to be C++ members');
assert(production.includes('.function("_getSound", &pdg::emscriptenResourceGetSound, emscripten::allow_raw_pointers())'));

const eventApi={name:'pdg',schemas:{},binding_adapters:{},interface:[
    {name:'Notifier',type:'class',native_binding:{type:'pdg::Notifier',browser:{generate:true,
        events:{selector:'watch',families:[{event:'eventType_Test',field:'kind',methods:{whenReady:7,whenDone:8}}]}}},
        interface:['watch','whenReady','whenDone'].map(name=>({name,type:'function',native:true,params:[],returns:'object IEventHandler'}))}
]};
const eventOutput=generate(eventApi,'',{members:{},sources:[]});
assert.strictEqual(JSON.parse(eventOutput.coverage).eventHelpers,3);
function Notifier() {this.handlers=[];}
Notifier.prototype.addHandler=function(handler,event) {this.handlers.push({handler,event});};
Notifier.prototype.removeHandler=function(handler) {this.handlers=this.handlers.filter(x=>x.handler!==handler);};
function EventHandler(callback) {this.handleEvent=callback;}
const eventModule={exports:{}};
vm.runInNewContext(eventOutput.wrappers,{exports:eventModule.exports,require(){return {installEvents};}});
eventModule.exports.installEvents({Notifier,IEventHandler:EventHandler,eventType_Test:12});
const notifier=new Notifier();let notified=0,receiver;
const subscription=notifier.whenReady(function(){++notified;receiver=this;return true;});
assert.strictEqual(notifier.handlers[0].event,12);
assert.strictEqual(subscription.handleEvent({kind:8}),false);assert.strictEqual(notified,0);
assert.strictEqual(subscription.handleEvent({kind:7}),true);assert.strictEqual(receiver,notifier);
subscription.cancel();subscription.cancel();assert.strictEqual(notifier.handlers.length,0);
const selectedSubscription=notifier.watch(8,()=>true);
assert.strictEqual(selectedSubscription.handleEvent({kind:7}),false);
assert.strictEqual(selectedSubscription.handleEvent({kind:8}),true);
assert.throws(()=>notifier.watch(99,()=>true),/Unknown event action/);
assert.throws(()=>notifier.watch(7.5,()=>true),/integer/);
assert.throws(()=>notifier.whenReady(null),/callback/);
eventApi.interface[0].native_binding.browser.events.extends='Notifier';
assert.throws(()=>generate(eventApi,'',{members:{},sources:[]}),/Cyclic browser event policy/);

// Type rules, not getter names or per-member opt-ins, derive value wrappers.
const valueApi = {name:'pdg',schemas:{},binding_adapters:{},interface:[
    {name:'Value',type:'class',interface:[],native_binding:{browser:{return_value:{arguments:['x','y']}}}},
    {name:'Reader',type:'class',native_binding:{type:'pdg::Reader',browser:{generate:true}},interface:[
        {name:'read',type:'function',native:true,params:[],returns:'object Value',native_binding:{browser:{generate:true}}},
        {name:'count',type:'function',native:true,params:[],returns:'number',native_binding:{browser:{generate:true}}}
    ]}
]};
const valueOutput = generate(valueApi, '', {version:1,members:{},sources:[]});
assert(valueOutput.cpp.includes('.function("_read", pdg::EmscriptenMethod<pdg::EmscriptenOwnMethod<pdg::Reader, &pdg::Reader::read>::pointer>::binding)'));
assert(valueOutput.cpp.includes('.function("count", pdg::EmscriptenMethod<pdg::EmscriptenOwnMethod<pdg::Reader, &pdg::Reader::count>::pointer>::binding)'));
assert.strictEqual(JSON.parse(valueOutput.coverage).returnWrappers, 1);
delete valueApi.interface[1].interface[0].native_binding;
assert.strictEqual(generate(valueApi, '', {members:{},sources:[]}).cpp, valueOutput.cpp,
    'Generated classes plus the return type derive the native name and wrapper without member annotations');
function Value(x,y) { this.x=x; this.y=y; }
Value.prototype.sum = function() { return this.x + this.y; };
function Reader() { this.raw={x:3,y:7}; this.calls=0; }
Reader.prototype._read = function() { ++this.calls; return this.raw; };
Reader.prototype.count = function() { return 2; };
const valuesModule = {exports:{}};
vm.runInNewContext(valueOutput.wrappers, {exports:valuesModule.exports,require() { return {installReturns}; }});
valuesModule.exports.installReturns({Reader,Value});
const reader = new Reader(), value = reader.read();
assert(value instanceof Value); assert.strictEqual(value.sum(),10); assert.strictEqual(reader.calls,1);
value.x=99; assert.strictEqual(reader.read().x,3, 'Returned values are independent snapshots');
reader.raw=null; assert.strictEqual(reader.read(),null, 'Nullable native results remain null');
assert.strictEqual(reader.count(),2);
valueApi.interface[0].native_binding.browser.return_value.arguments = ['invalid.path()'];
assert.throws(() => generate(valueApi, '', {members:{},sources:[]}), /Invalid browser return conversion/);

// The existing ownership contract drives both native retention and JS identity.
// Arbitrary type/method names ensure this is not a factory-name convention.
const retainedApi = {name:'pdg', schemas:{}, binding_adapters:{}, interface:[
    {name:'Token', type:'class', interface:[], native_binding:{type:'pdg::Token',ownership:'retained'}},
    {name:'Shelf', type:'class', native_binding:{type:'pdg::Shelf',browser:{generate:true,remember_receiver:true}},
        interface:[{name:'lookup',type:'function',native:true,params:[],returns:'object Token'},
            {name:'store',type:'function',native:true,params:[{name:'token',type:'object Token'}]}]}
]};
const retainedOutput = generate(retainedApi, '', {members:{},sources:[]});
assert(retainedOutput.cpp.includes('EmscriptenRetained<pdg::Token> : std::true_type'));
assert(retainedOutput.cpp.includes('EmscriptenMethod<pdg::EmscriptenOwnMethod<pdg::Shelf, &pdg::Shelf::lookup>::pointer>::binding'));
function Token(identity) { this.identity=identity; this.deleted=false; this.deletes=0; }
Token.prototype._getNativeIdentity = function() { return this.identity; };
Token.prototype.isDeleted = function() { return this.deleted; };
Token.prototype.delete = function() { this.deleted=true; ++this.deletes; };
function Shelf() { this.result=null; }
Shelf.prototype._getNativeIdentity = function() { return 42; };
Shelf.prototype._lookup = function() { return this.result; };
Shelf.prototype.store = function(token) { this.stored=token; };
const retainedBindings = {Token,Shelf}, retainedModule={exports:{}};
vm.runInNewContext(retainedOutput.wrappers,{exports:retainedModule.exports,require() { return {installReturns}; }});
retainedModule.exports.installReturns(retainedBindings);
const shelf=new Shelf(), originalToken=new Token(7);
shelf.result=originalToken;
assert.strictEqual(shelf.lookup(),originalToken);
assert.strictEqual(objectForIdentity(retainedBindings,42),shelf,'Receivers remain discoverable from native identities');
const duplicateToken=new Token(7); shelf.result=duplicateToken;
assert.strictEqual(shelf.lookup(),originalToken);
assert.strictEqual(duplicateToken.deletes,1,'A duplicate releases its extra reference exactly once');
assert.strictEqual(originalToken.deletes,0,'Canonicalization preserves the live handle');
assert.strictEqual(canonicalRetained(retainedBindings,originalToken),originalToken);
assert.strictEqual(originalToken.deletes,0,'An already canonical handle is not released');
originalToken.delete(); shelf.result=new Token(7);
assert.strictEqual(shelf.lookup(),shelf.result,'Explicitly deleted wrappers can be replaced');
shelf.result=null; assert.strictEqual(shelf.lookup(),null);
const independentBindings={};
assert.strictEqual(canonicalRetained(independentBindings,new Token(7)).deletes,0,'Registries are isolated per runtime');
forgetObject(retainedBindings,42); assert.strictEqual(objectForIdentity(retainedBindings,42),null);
shelf.store(originalToken); assert.strictEqual(objectForIdentity(retainedBindings,42),shelf,'Void calls also remember their receiver');

// Borrowed getters return native identities, so repeated owner lookups cannot
// delete the owning layer. Root factories register the original handle once.
const borrowedBindings={_make:()=>new Token(55)};
installReturns(borrowedBindings,[{root:true,name:'make',target:'_make',returnConversion:{identity:true}}]);
const borrowed=borrowedBindings.make();
function Borrower() {}
Borrower.prototype._owner=function(){return 55;};
borrowedBindings.Borrower=Borrower;
installReturns(borrowedBindings,[{owner:'Borrower',name:'owner',target:'_owner',returnConversion:{identity:true}}]);
assert.strictEqual(new Borrower().owner(),borrowed);
assert.strictEqual(new Borrower().owner(),borrowed);
assert.strictEqual(borrowed.deletes,0);
forgetObject(borrowedBindings,55);assert.strictEqual(new Borrower().owner(),null);
assert(production.includes('EmscriptenBorrowedIdentity<pdg::SpriteLayer>'));

// Receiver identity comes from the IDL and survives inheritance and a later
// argument adapter, even when the native method returns a different JS handle.
const fluentApi = {name:'pdg', schemas:{}, binding_adapters:{}, interface:[{
    name:'Fluent', type:'class', native_binding:{type:'pdg::Fluent', browser:{generate:true}},
    interface:[{name:'mutate',type:'function',native:true,params:[],returns:'this'}]
}]};
const fluentOutput = generate(fluentApi, '', {members:{},sources:[]});
assert(fluentOutput.cpp.includes('.function("_mutate", &pdg::EmscriptenReceiverMethod<pdg::EmscriptenOwnMethod<pdg::Fluent, &pdg::Fluent::mutate>::pointer, false>::call'));
function Fluent() { this.calls=0; }
Fluent.prototype._mutate = function() { ++this.calls; return {}; };
class FluentChild extends Fluent {}
const fluentModule = {exports:{}};
vm.runInNewContext(fluentOutput.wrappers, {exports:fluentModule.exports,
    require() { return {installReturns,install,installReceivers,installValidation}; }});
fluentModule.exports.installReturns({Fluent});
const fluent = new FluentChild();
assert.strictEqual(fluent.mutate(), fluent);
const earlyMutate = Fluent.prototype.mutate;
Fluent.prototype.mutate = function(fail) {
    if (fail) throw new RangeError('rejected');
    earlyMutate.call(this); // An existing argument adapter may discard the result.
};
fluentModule.exports.install({Fluent});
assert.strictEqual(fluent.mutate().mutate(), fluent);
assert.strictEqual(fluent.calls, 3, 'Each chain link calls native code once');
assert.throws(() => fluent.mutate(true), /rejected/);
assert.strictEqual(fluent.calls, 3, 'Exceptions do not report successful completion');
installReceivers({Fluent}, [{owner:'Fluent',name:'guardedOut',optional:true}]);
assert.throws(() => installReceivers({Fluent}, [{owner:'Fluent',name:'missing'}]), /Missing generated binding/);

// Installation phases compose policies on one generated function. Type-level
// borrowed views work for arbitrary classes, not a list of drawing methods.
const compositionApi={name:'pdg',schemas:{},binding_adapters:{},interface:[
    {name:'Style',type:'class',native_binding:{type:'pdg::Style',browser:{argument:{alternatives:[{type:'AnimatedStyle',borrow:'_style'}]}}},interface:[]},
    {name:'Canvas',type:'class',native_binding:{type:'pdg::Canvas',browser:{generate:true}},interface:[
        {name:'paint',type:'function',native:true,returns:'this',params:[{name:'value',type:'number'},{name:'style',type:'object Style'}],
            argument_validation:{arity:2,parameters:[{index:0,name:'value',type:'number',conversion:'uint32'}]}},
        {name:'style',type:'function',native:true,returns:'object Style',params:[{name:'style',type:'object Style'}]}
    ]}
]};
function Style() {}
function AnimatedStyle() {this.base=new Style();this.borrows=0;}
AnimatedStyle.prototype.isDeleted=function(){return !!this.deleted;};
AnimatedStyle.prototype._style=function(){++this.borrows;return this.base;};
function Canvas() {this.calls=[];}
Canvas.prototype._paint=function(value,style){this.calls.push([value,style]);return {};};
Canvas.prototype.style=function(style){return style;};
class ChildCanvas extends Canvas {}
const compositionBindings={Style,AnimatedStyle,Canvas};
const compositionOutput=generate(compositionApi,'',{members:{},sources:[]});
const compositionModule={exports:{}};
let importsAllowed=true;
vm.runInNewContext(compositionOutput.wrappers,{exports:compositionModule.exports,
    require(){assert(importsAllowed,'Generated calls must not reload modules after initialization');return require('../../src/bindings/emscripten/pdg_em_runtime');}});
importsAllowed=false;
compositionModule.exports.installReturns(compositionBindings);
assert.strictEqual(compositionModule.exports.adaptArgument(compositionBindings,'Style',new Style()) instanceof Style,true);
const paint=Canvas.prototype.paint;
compositionModule.exports.install(compositionBindings);
assert.strictEqual(Canvas.prototype.paint,paint,'Final receiver and validation policies must reuse the generated wrapper');
const canvas=new ChildCanvas(),style=new Style(),animatedStyle=new AnimatedStyle();
assert.strictEqual(canvas.paint(-1,style),canvas);
assert.strictEqual(canvas.calls[0][0],4294967295);
assert.strictEqual(canvas.calls[0][1],style,'Ordinary native arguments retain identity');
assert.strictEqual(canvas.paint(2,animatedStyle),canvas);
assert.strictEqual(canvas.calls[1][1],animatedStyle.base,'Borrow the adjusted native base without copying');
assert.strictEqual(animatedStyle.borrows,1,'Convert each argument once');
assert.strictEqual(canvas.style(animatedStyle),animatedStyle.base,'Nonfluent return values survive adaptation');
assert.throws(()=>canvas.paint(1,{}),/Style/);
assert.throws(()=>canvas.paint(1,null),/Style/);
assert.throws(()=>canvas.paint('1',style),TypeError);
assert.throws(()=>canvas.paint(1),/argument count mismatch/);
assert.throws(()=>canvas.paint(1,style,3),/argument count mismatch/);
animatedStyle.deleted=true;
assert.throws(()=>canvas.paint(1,animatedStyle),/deleted/);
assert.strictEqual(canvas.calls.length,2,'Rejected calls never reach native code');
compositionModule.exports.install(compositionBindings);
assert.strictEqual(Canvas.prototype.paint,paint,'Repeated finalization must not add wrapper layers');
assert.strictEqual(canvas.paint(3,style),canvas);
assert.strictEqual(canvas.calls.length,3);
// The hot path must not allocate an argument array for an unchanged native
// object; a borrowed view and numeric coercion share one copy when both change.
const originalSlice=Array.prototype.slice;
let argumentCopies=0;
Array.prototype.slice=function(){++argumentCopies;return originalSlice.apply(this,arguments);};
try { canvas.paint(4,style); } finally { Array.prototype.slice=originalSlice; }
assert.strictEqual(argumentCopies,0);
animatedStyle.deleted=false;
Array.prototype.slice=function(){++argumentCopies;return originalSlice.apply(this,arguments);};
try { canvas.paint(-1,animatedStyle); } finally { Array.prototype.slice=originalSlice; }
assert.strictEqual(argumentCopies,1);
assert.strictEqual(canvas.calls.at(-1)[0],4294967295);
assert.strictEqual(canvas.calls.at(-1)[1],animatedStyle.base);
argumentCopies=0;
let borrowedResult;
Array.prototype.slice=function(){++argumentCopies;return originalSlice.apply(this,arguments);};
try { borrowedResult=canvas.style(animatedStyle); } finally { Array.prototype.slice=originalSlice; }
assert.strictEqual(borrowedResult,animatedStyle.base);
assert.strictEqual(argumentCopies,0,'Generated fixed-arity calls forward borrowed views without an argument array');

// Validation wrappers enforce source-derived constraints without changing
// native argument conversion or losing receiver identity.
let validationCalls=0;
function Numeric() {}
Numeric.prototype.byte=function(value) { ++validationCalls; return this; };
Numeric.prototype.word=function(value) { ++validationCalls; return value; };
installValidation({Numeric}, [
    {owner:'Numeric',name:'byte',arity:1,parameters:[{index:0,name:'value',type:'number',integer:true,min:0,max:255}]},
    {owner:'Numeric',name:'word',arity:1,parameters:[{index:0,name:'value',type:'number',conversion:'uint32'}]}
]);
const numeric = new Numeric();
assert.strictEqual(numeric.byte(0).byte(255), numeric);
for (const value of [-1,256,1.5,NaN,Infinity,null,undefined,'1',true])
    assert.throws(() => numeric.byte(value), TypeError);
assert.throws(() => numeric.byte(), /argument count mismatch/);
assert.throws(() => numeric.byte(1,2), /argument count mismatch/);
assert.strictEqual(validationCalls,2, 'Invalid input must not reach native code');
for (const value of [NaN,Infinity,-Infinity]) assert.strictEqual(numeric.word(value),0);
assert(Object.is(numeric.word(-0),0), 'Integer conversion must canonicalize negative zero');
assert.throws(() => numeric.word(null),TypeError);

// No annotation is needed to name, forward or validate a numeric method.
const numericApi = {name:'pdg',schemas:{},binding_adapters:{},interface:[{
    name:'Numeric',type:'class',native_binding:{type:'pdg::Numeric',browser:{generate:true}},interface:[{
        name:'accept',type:'function',native:true,params:[{name:'value',type:'number int'}],
        argument_validation:{arity:1,parameters:[{index:0,name:'value',type:'number',conversion:'int32',integer:true,min:-128,max:127}]}
    }]
}]};
const numericOutput = generate(numericApi,'',{members:{},sources:[]});
assert(numericOutput.cpp.includes('.function("_accept", pdg::EmscriptenMethod<pdg::EmscriptenOwnMethod<pdg::Numeric, &pdg::Numeric::accept>::pointer>::binding)'));
Numeric.prototype._accept = function(value) { return value; };
const numericModule = {exports:{}};
vm.runInNewContext(numericOutput.wrappers, {exports:numericModule.exports,
    require() { return {installReturns,install,installReceivers,installValidation}; }});
numericModule.exports.installReturns({Numeric});
numericModule.exports.install({Numeric});
assert.strictEqual(numeric.accept(-1.5),-1);
assert.strictEqual(numeric.accept(4294967297),1);
assert.strictEqual(numeric.accept(Infinity),0);
assert.throws(() => numeric.accept(128),TypeError);
assert.throws(() => numeric.accept(null),TypeError);
// Validation participates in stale-mapping detection.
const numericOwner = numericApi.interface[0], numericMethod = numericOwner.interface[0];
const beforeValidation = fingerprint(numericMethod,numericOwner,numericApi);
numericMethod.argument_validation.parameters[0].max=126;
assert.notStrictEqual(fingerprint(numericMethod,numericOwner,numericApi),beforeValidation);

// Callback conversion follows the schema, independent of class/method names.
const callbackApi = {name:'pdg',schemas:{Predicate:{kind:'callback',synchronous:true,
    params:[],returns:{type:'boolean'},native_binding:{type:'pdg::AnimationEvaluator',browser:{argument:'animation-evaluator'}}}},
    binding_adapters:{},interface:[{name:'Observer',type:'class',native_binding:{type:'pdg::Observer',browser:{generate:true}},interface:[{
        name:'choose',type:'function',native:true,returns:'this',params:[{name:'predicate',type:'function',contract:{schema:'Predicate'}}]
    }]}]};
const callbackOutput = generate(callbackApi,'',{members:{},sources:[]});
function Observer(id) { this.id=id; }
Observer.prototype._animationIdentity=function(){return this.id;};
Observer.prototype._choose=function(callback){this.callback=callback;};
const callbackModule={exports:{}};
vm.runInNewContext(callbackOutput.wrappers,{exports:callbackModule.exports,
    require(){return {installReturns,install,installReceivers,installValidation};}});
callbackModule.exports.installReturns({Observer});callbackModule.exports.install({Observer});
const observer=new Observer(101), otherObserver=new Observer(102);rememberAnimationOwner(otherObserver);
let observedContext;
assert.strictEqual(observer.choose(context => {observedContext=context;return true;}),observer);
assert.strictEqual(observer.callback(102,.25).value,true);
assert.strictEqual(observedContext.target,otherObserver);
assert.strictEqual(observedContext.elapsedSeconds,.25);
assert.throws(()=>observer.choose(null),TypeError);
observer.choose(()=>{throw new Error('callback failed');});
assert.strictEqual(observer.callback(101,0).error,'callback failed');
assert(observer.callback(999,0).error.includes('no script wrapper'));

// Run the production seven type rules with the actual public JS constructors.
const coordinates = require('../../src/js/coordinates');
const {Color} = require('../../src/js/color');
function ValueDeserializer() {}
const rawValues = {
    color:{red:.2,green:.4,blue:.6,alpha:.8}, offset:{x:2,y:3}, point:{x:4,y:5}, vector:{x:6,y:7},
    rect:{left:1,top:2,right:5,bottom:9},
    rotr:{left:1,top:2,right:5,bottom:9,radians:.7,centerOffset:{x:3,y:4}},
    quad:{points:[{x:1,y:2},{x:3,y:4},{x:5,y:6},{x:7,y:8}]}
};
for (const [key,value] of Object.entries(rawValues)) ValueDeserializer.prototype['_deserialize_'+key] = () => value;
const productionValues = {exports:{}};
vm.runInNewContext(generated.get('src/bindings/emscripten/pdg_em_generated.js'), {
    exports:productionValues.exports, require() { return {installReturns(bindings,specs) { installReturns(bindings,specs.filter(spec=>!spec.root)); }}; }
});
productionValues.exports.installReturns({...coordinates,Color,Deserializer:ValueDeserializer});
const valueReader = new ValueDeserializer();
for (const [key,type] of Object.entries({color:Color,offset:coordinates.Offset,point:coordinates.Point,
    vector:coordinates.Vector,rect:coordinates.Rect,rotr:coordinates.RotatedRect,quad:coordinates.Quad}))
    assert(valueReader['deserialize_'+key]() instanceof type, key);
assert.strictEqual(valueReader.deserialize_color().alpha,.8);
assert.strictEqual(valueReader.deserialize_rotr().radians,.7);
assert.strictEqual(valueReader.deserialize_rotr().centerOffset.x,3);
const convertedQuad=valueReader.deserialize_quad();
assert(convertedQuad.points[0] instanceof coordinates.Point);
convertedQuad.points[0].x=100; assert.strictEqual(rawValues.quad.points[0].x,1);

const method = {name:'move', type:'function', native:true, params:[{name:'x', type:'number'}], returns:'this',
    native_binding:{signature:'pdg::Thing&(float)', return_policy:'reference', browser:{generate:true, wrapper:{}}}};
const owner = {name:'Thing', type:'class', native:true, native_binding:{type:'pdg::Thing',browser:{generate:true}}, interface:[method]};
const api = {name:'pdg', interface:[owner], schemas:{}, binding_adapters:{}};
const manual = {version:1, members:{}, sources:[], reason:'test'};
const template = '';
assert(generate(api, template, manual).cpp.includes('EmscriptenMethodPointer<pdg::Thing, pdg::Thing&(float)>'));
assert(generate(api, template, manual).cpp.includes('class_<pdg::Thing>("Thing")'));
const missingOwner = copy(api);
delete missingOwner.interface[0].native_binding.browser;
assert.throws(() => generate(missingOwner, '', manual), /Missing generated browser owner/);
const fragment = '// @pdg-custom Thing\nThing_Extra\n// @pdg-end-custom\n';
assert(generate(api, fragment, manual).cpp.includes('Thing_Extra'));
assert.throws(() => generate(api, fragment + fragment, manual), /Duplicate custom fragment/);
assert.throws(() => generate(api, '// @pdg-custom Absent\nExtra\n// @pdg-end-custom', manual), /Unknown custom fragment owner/);
assert.throws(() => generate(api, 'unscoped C++', manual), /Unscoped custom binding code/);
assert.throws(() => generate(api, template, {...manual, members:{'Thing.move':fingerprint(method)}}), /Remove migrated/);
const legacyApi = copy(api);
legacyApi.interface[0].interface[0].native_binding = {browser:{generate:false}};
const legacy = legacyApi.interface[0].interface[0];
assert.throws(() => generate(legacyApi, '', manual), /Unclassified native API/);
const reviewed = {...manual, members:{'Thing.move':fingerprint(legacy, legacyApi.interface[0], legacyApi)}};
assert(generate(legacyApi, '', reviewed).coverage.includes('manual-unverified'));
legacy.params[0].type = 'string';
assert.throws(() => generate(legacyApi, '', reviewed), /Manual API contract changed/);
assert.throws(() => generate(api, template, {...manual, members:{'Thing.gone':'old'}}), /Stale manual/);
const schemaApi = copy(legacyApi);
schemaApi.schemas.Options = {kind:'record', fields:{enabled:{type:'boolean'}}};
const schemaMethod = schemaApi.interface[0].interface[0];
schemaMethod.params = [{name:'options',type:'object',contract:{schema:'Options'}}];
const schemaManual = {...manual, members:{'Thing.move':fingerprint(schemaMethod, schemaApi.interface[0], schemaApi)}};
schemaApi.schemas.Options.fields.enabled.type = 'string';
assert.throws(() => generate(schemaApi, '', schemaManual), /Manual API contract changed/);

assert.throws(() => renderBinding(owner, {...method, native_binding:{adapter:'missing'}}, api), /Unknown adapter/);
assert.throws(() => renderBinding(owner, {...method, native_binding:{signature:'void()', return_policy:'guess'}}, api), /Unknown return policy/);
assert(renderBinding(owner, {...method, native_binding:{}}, api).includes('&pdg::Thing::move'), 'Unambiguous C++ member pointers need no exact signature');
// Exception translation is independent of overload, pointer and return policies.
const checkedMethod = copy(method);
checkedMethod.native_binding.browser.exceptions = 'javascript';
let checkedText = renderBinding(owner, checkedMethod, api);
assert(checkedText.includes('&pdg::EmscriptenReceiverMethod<pdg::EmscriptenOwnMethod<pdg::Thing, static_cast<pdg::EmscriptenMethodPointer<pdg::Thing, pdg::Thing&(float)>>(&pdg::Thing::move)>::pointer, true>::call'));
assert(checkedText.includes('return_value_policy::reference()'));
delete checkedMethod.native_binding.signature;
checkedMethod.native_binding.binding_name = '_move';
checkedMethod.native_binding.symbol = 'pdg::Thing::moveNative';
checkedMethod.native_binding.allow_raw_pointers = true;
checkedText = renderBinding(owner, checkedMethod, api);
assert(checkedText.includes('.function("_move", &pdg::EmscriptenReceiverMethod<pdg::EmscriptenOwnMethod<pdg::Thing, &pdg::Thing::moveNative>::pointer, true>::call, emscripten::allow_raw_pointers()'));
checkedMethod.native_binding.browser.registrations = [{name:'_moveOverload',signature:'pdg::Thing&(double)'}];
assert(renderBinding(owner, checkedMethod, api).includes('EmscriptenMethodPointer<pdg::Thing, pdg::Thing&(double)>'));
assert.throws(() => renderBinding(owner, {...checkedMethod,static:true}, api), /requires a native instance method/);
assert.throws(() => renderBinding(owner, {...checkedMethod,type:'constructor'}, api), /requires a native instance method/);
assert.throws(() => renderBinding(api, checkedMethod, api), /requires a native instance method/);
assert.throws(() => renderBinding(owner, {...checkedMethod,native_binding:{...checkedMethod.native_binding,adapter:'free'}},
    {...api,binding_adapters:{free:{symbol:'pdg::free'}}}), /requires a native instance method/);
checkedMethod.native_binding.browser.exceptions = 'ignore';
assert.throws(() => renderBinding(owner, checkedMethod, api), /Unknown browser exception policy/);

// Class defaults generate native methods directly from the public inventory.
const defaultApi = copy(api), defaultOwner = defaultApi.interface[0];
defaultOwner.native_binding.browser.defaults = {exceptions:'javascript'};
const defaultMethod = defaultOwner.interface[0];
defaultMethod.native_binding = {binding_name:'_move'};
let defaultText = generate(defaultApi, '', manual).cpp;
assert(defaultText.includes('.function("_move", &pdg::EmscriptenReceiverMethod<pdg::EmscriptenOwnMethod<pdg::Thing, &pdg::Thing::move>::pointer, true>::call, emscripten::return_value_policy::reference())'));
const unmapped = {name:'automatic',type:'function',native:true,params:[],returns:'this'};
defaultOwner.interface.push(unmapped);
assert(generate(defaultApi, '', manual).cpp.includes('.function("_automatic", &pdg::EmscriptenReceiverMethod<pdg::EmscriptenOwnMethod<pdg::Thing, &pdg::Thing::automatic>::pointer, true>::call, emscripten::return_value_policy::reference())'), 'No native_binding annotation is required');
const optedOutApi = copy(defaultApi), optedOutOwner = optedOutApi.interface[0];
optedOutOwner.native_binding.browser.defaults.generate = false;
const optedOutManual = {...manual, members:Object.fromEntries(optedOutOwner.interface.map(m =>
    ['Thing.' + m.name, fingerprint(m, optedOutOwner, optedOutApi)]))};
assert(!generate(optedOutApi, '', optedOutManual).cpp.includes('::automatic'), 'A class can explicitly opt out');
const valueObjectApi = copy(defaultApi), valueObjectOwner = valueObjectApi.interface[0];
valueObjectOwner.native_binding.browser.kind = 'value_object';
valueObjectOwner.native_binding.browser.fields = [];
const valueObjectManual = {...manual, members:Object.fromEntries(valueObjectOwner.interface.map(m =>
    ['Thing.' + m.name, fingerprint(m, valueObjectOwner, valueObjectApi)]))};
assert(!generate(valueObjectApi, '', valueObjectManual).cpp.includes('::automatic'), 'Value objects register fields, not methods');
unmapped.native_binding = {browser:{generate:false}};
const defaultManual = {...manual,members:{'Thing.automatic':fingerprint(unmapped,defaultOwner,defaultApi)}};
assert(!generate(defaultApi, '', defaultManual).cpp.includes('::automatic'), 'Explicit exclusions remain manual');
defaultOwner.interface.pop();
defaultOwner.interface.push({name:'jsHelper',type:'function',params:[],returns:'number'});
assert(!generate(defaultApi, '', manual).cpp.includes('::jsHelper'), 'JavaScript methods are not native calls');
defaultOwner.interface.pop();
for (const special of [{...unmapped,name:'create',static:true,native_binding:undefined},
    {...unmapped,name:'Thing',type:'constructor',native_binding:undefined}]) {
    defaultOwner.interface.push(special);
    const specialOutput = generate(defaultApi, '', {...manual,members:{['Thing.'+special.name]:fingerprint(special,defaultOwner,defaultApi)}});
    assert.strictEqual(JSON.parse(specialOutput.coverage).members.find(x=>x.name==='Thing.'+special.name).status,
        'manual-unverified', 'Static methods and constructors need explicit mappings');
    defaultOwner.interface.pop();
}
defaultMethod.native_binding.browser = {generate:false};
assert(!generate(defaultApi, '', {...manual,members:{'Thing.move':fingerprint(defaultMethod,defaultOwner,defaultApi)}}).cpp.includes('::move'));
defaultMethod.native_binding.browser = {exceptions:'native'};
assert(!renderBinding(defaultOwner, defaultMethod, defaultApi).includes('EmscriptenCheckedMethod'), 'Member policy overrides class policy');
defaultMethod.native_binding.return_policy = 'copy';
assert(renderBinding(defaultOwner, defaultMethod, defaultApi).includes('return_value_policy::copy()'), 'Explicit ownership overrides inferred receiver policy');
delete defaultMethod.native_binding.return_policy;
delete defaultMethod.native_binding.browser;
defaultMethod.returns = 'number'; delete defaultMethod.returns_contract;
defaultMethod.native_binding.signature = 'int() const';
defaultText = renderBinding(defaultOwner, defaultMethod, defaultApi);
assert(defaultText.includes('EmscriptenMethodPointer<pdg::Thing, int() const>'));
assert(!defaultText.includes('return_value_policy'), 'Value returns do not inherit receiver policy');
assert(!renderBinding(defaultOwner, {...defaultMethod,static:true}, defaultApi).includes('EmscriptenCheckedMethod'));
defaultMethod.native_binding = {symbol:'pdg::adapterFunction'};
assert(!renderBinding(defaultOwner, defaultMethod, defaultApi).includes('EmscriptenCheckedMethod'), 'Free helpers do not inherit native member exception policy');
defaultOwner.native_binding.browser.support_bindings = [{name:'_nativeHelper',symbol:'pdg::Thing::helper'}];
assert(generate(defaultApi, '', manual).cpp.includes('.function("_nativeHelper", pdg::EmscriptenMethod<pdg::EmscriptenOwnMethod<pdg::Thing, &pdg::Thing::helper>::pointer>::binding)'));
defaultOwner.native_binding.browser.defaults.exceptions = 'ignore';
assert.throws(() => generate(defaultApi, '', manual), /Unknown browser exception policy/);
const guardedMethod = copy(method);
guardedMethod.native_binding.browser.guard = ['PDG_SPRITER_SUPPORT', 'PDG_USE_CHIPMUNK_PHYSICS'];
const guardedText = renderBinding(owner, guardedMethod, api);
assert(guardedText.startsWith('#ifdef PDG_SPRITER_SUPPORT\n#ifdef PDG_USE_CHIPMUNK_PHYSICS\n'));
assert(guardedText.endsWith('\n#endif\n#endif'));
guardedMethod.native_binding.browser.guard = ['FEATURE', 'invalid expression'];
assert.throws(() => renderBinding(owner, guardedMethod, api), /Invalid build guard/);
// A shared adapter's identity is independent of the registration's ownership policy.
const policyApi = {...api, binding_adapters:{adapter:{symbol:'pdg::adapt',signature:'void(pdg::Thing&)'}}};
const policyBinding = renderBinding(owner, {...method, native_binding:{adapter:'adapter',allow_raw_pointers:true,return_policy:'reference'}}, policyApi);
assert(policyBinding.includes('&pdg::adapt'));
assert(policyBinding.includes('allow_raw_pointers()'));
assert(policyBinding.includes('return_value_policy::reference()'));
assert.throws(() => wrapperSpec(owner, {...method, params:[{name:'value', type:'object'}]}, api), /Unsupported wrapper type/);

// Scaffolding, native inheritance order, constants, constructors, and value
// objects all come from metadata; no template enumerates the public classes.
const structureApi = copy(api);
structureApi.interface.unshift({name:'Child',type:'class',native:true,interface:[],
    native_binding:{type:'pdg::Child',base:'pdg::Thing',browser:{generate:true,guard:'!PDG_NO_GUI',constructors:[{types:['int']}]}}});
structureApi.interface.push({name:'Value',type:'class',interface:[],native_binding:{browser:{
    generate:true,type:'pdg::Value',kind:'value_object',binding_name:'_Value',fields:['x','y']}}});
structureApi.interface.push({name:'aMode',type:'number',readonly:true,native_binding:{cast:'int',browser:{generate:true}}});
const structural = generate(structureApi, '', manual).cpp;
assert(structural.indexOf('class_<pdg::Thing>') < structural.indexOf('class_<pdg::Child,'));
assert(structural.includes('class_<pdg::Child, emscripten::base<pdg::Thing>>("Child")'));
assert(structural.includes('.constructor<int>()'));
assert(structural.includes('#ifndef PDG_NO_GUI'));
assert(structural.includes('constant("aMode", static_cast<int>(pdg::aMode))'));
assert(structural.includes('value_object<pdg::Value>("_Value")'));
assert(structural.includes('.field("x", &pdg::Value::x)'));
// Primitive construction is a value-type policy, shared by every consuming
// method. Matching an overload must not construct values or mutate input data.
{
const valueApi = copy(structureApi);
const valueType = valueApi.interface.find(c => c.name === 'Value');
valueType.interface = ['x','y'].map(name => ({name,type:'number'}));
valueType.native_binding.browser.construct_from = ['string','number'];
const valueMethod = {...method, params:[
    [{name:'target',type:'object Value',native_qualifiers:{indirection:'reference',const:true}}],
    [{name:'targetName',type:'string'}], [{name:'targetNumber',type:'number'}]]};
let constructions = 0, receivedValue;
class Value {
    constructor(value) { ++constructions; this.x=Number(value); this.y=this.x; }
}
class ValueConsumer { _move(value) { receivedValue=value; } }
// A constructor policy must not widen a method that declares only an object.
const objectOnly = wrapperSpec(owner,{...valueMethod,params:valueMethod.params[0]},valueApi);
class ObjectConsumer { _move(value) { receivedValue=value; } }
install({Thing:ObjectConsumer,Value},[objectOnly]);
assert.throws(() => new ObjectConsumer().move('7'),TypeError);
const valueSpec = wrapperSpec(owner,valueMethod,valueApi);
install({Thing:ValueConsumer,Value},[valueSpec]);
const valueConsumer = new ValueConsumer();
for (const input of ['7',9]) {
    const before = constructions;
    assert.strictEqual(valueConsumer.move(input),valueConsumer);
    assert(receivedValue instanceof Value);
    assert.strictEqual(receivedValue.x,Number(input));
    assert.strictEqual(constructions,before+1);
}
const structuralValue = {x:1,y:2}, instanceValue = new Value(3);
for (const input of [structuralValue,instanceValue]) {
    valueConsumer.move(input); assert.strictEqual(receivedValue,input);
}
for (const input of [null,undefined,true,{}, {x:'1',y:2}])
    assert.throws(() => valueConsumer.move(input),TypeError);
valueType.native_binding.browser.construct_from = ['object'];
assert.throws(() => wrapperSpec(owner,valueMethod,valueApi),/Invalid value constructor inputs/);
}
structureApi.interface.find(x => x.name === 'Thing').native_binding.browser.support_bindings = [{name:'_identity',symbol:'pdg::identity'}];
const supported = generate(structureApi, '', manual);
assert(supported.cpp.includes('.function("_identity", &pdg::identity)'));
assert.strictEqual(JSON.parse(supported.coverage).registrations.supportBindings, 1);
assert(!JSON.parse(supported.coverage).members.some(x => x.name === 'Thing._identity'), 'Backend helpers must not invent public API contracts');
structureApi.interface.find(x => x.name === 'Thing').native_binding.browser.support_bindings.push({name:'_move',symbol:'pdg::move'});
assert.throws(() => generate(structureApi, '', manual), /Duplicate generated registration/);
structureApi.interface.find(x => x.name === 'Thing').native_binding.browser.support_bindings.pop();
structureApi.interface.find(x => x.name === 'Thing').native_binding.base = 'pdg::Child';
assert.throws(() => generate(structureApi, '', manual), /Cyclic browser inheritance/);

// Execute the generated production wrappers against mock adapters. The same
// functions and specifications are embedded in the browser build.
let seen;
function MemBlock() {}
function Serializer() {}
Serializer.prototype._serialize_mem = function(value) { seen = value; };
Serializer.prototype._sizeof_mem = function(value) { seen = value; return value.byteLength; };
Serializer.prototype.serialize_color = function(value) { seen = value; };
Serializer.prototype.sizeof_color = function() { return 4; };
function Deserializer() {}
Deserializer.prototype.setDataPtr = function(value) { seen = value; };
function TileLayer() {}
TileLayer.prototype._loadMapData = function() { seen = Array.from(arguments); };
function ConfigManager() {}
for (const name of ['useConfig','getConfigString','getConfigLong','getConfigFloat','getConfigBool',
    'setConfigString','setConfigLong','setConfigFloat','setConfigBool']) {
    ConfigManager.prototype[name] = function() { seen = Array.from(arguments); return 'native-result'; };
}
const bindings = {MemBlock, Serializer, Deserializer, TileLayer, ConfigManager};
const moduleForTest = {exports:{}};
vm.runInNewContext(generated.get('src/bindings/emscripten/pdg_em_generated.js'), {
    exports:moduleForTest.exports, require(name) { assert.strictEqual(name, 'pdg_em_runtime'); return {install, installValidation(target, specs) {
        installValidation(target, specs.filter(spec => typeof target[spec.owner]?.prototype[spec.name] === 'function'));
    }, installReceivers(target, specs) {
        // This fixture implements byte adapters only; fluent behavior is tested separately.
        installReceivers(target, specs.filter(spec => typeof target[spec.owner]?.prototype[spec.name] === 'function'));
    }}; }
});
moduleForTest.exports.install(bindings);
const bytes = new Uint8Array([9, 3, 5, 7]).subarray(1, 3);
const serializer = new Serializer();
serializer.serialize_mem(bytes);
assert.strictEqual(seen, bytes, 'The wrapper must preserve the view, offset and ownership');
assert.strictEqual(serializer.sizeof_mem(bytes), 2);
const block = new MemBlock();
serializer.serialize_mem(block);
assert.strictEqual(seen, block);
assert.throws(() => serializer.serialize_mem('binary'), TypeError);
assert.throws(() => serializer.serialize_mem(null), TypeError);
assert.throws(() => serializer.serialize_mem(new Uint16Array(3)), TypeError);
assert.throws(() => serializer.serialize_mem(bytes, 1), TypeError);
new Deserializer().setDataPtr(bytes);
assert.strictEqual(seen, bytes);
const tiles = new TileLayer();
tiles.loadMapData(bytes);
assert.deepStrictEqual(seen, [bytes, 0, 0, 0, 0]);
tiles.loadMapData(bytes, 4, undefined, 2);
assert.deepStrictEqual(seen, [bytes, 4, 0, 2, 0]);
for (const value of [-1, 0.5, NaN, Infinity, 2147483648]) assert.throws(() => tiles.loadMapData(bytes, value), RangeError);
assert.throws(() => tiles.loadMapData(bytes, '4'), TypeError);
const config = new ConfigManager();
assert.strictEqual(config.getConfigString('key'), 'native-result');
assert.throws(() => config.setConfigString('key', null), TypeError);
assert.throws(() => config.setConfigBool('key', 'true'), TypeError);
config.setConfigBool('key', false);
assert.deepStrictEqual(seen, ['key', false]);

// Overloads, receiver identity, static calls, named defaults and optional class
// capabilities are generic machinery rather than per-method exceptions.
function Thing() {}
Thing.prototype._moveX = function(x) { seen = x; return {}; };
Thing.prototype._moveName = function(name) { seen = name; return {}; };
Thing.prototype._moveOptions = function(options) { seen = options; };
Thing._static = function(value) { return value; };
const calls = [{target:'_moveX',params:[{name:'x',type:'number'}]}, {target:'_moveName',params:[{name:'name',type:'string'}]}];
const spec = {owner:'Thing', name:'move', calls, schemas:{}, returnsThis:true, constraints:{}};
install({Thing}, [spec]);
const thing = new Thing();
assert.strictEqual(thing.move(3), thing);
assert.strictEqual(seen, 3);
assert.strictEqual(thing.move('home'), thing);
assert.strictEqual(seen, 'home');
assert.throws(() => thing.move(null), TypeError);
install({Thing}, [{...spec, calls:[calls[0], {...calls[0], target:'_moveName'}]}]);
assert.throws(() => thing.move(3), /ambiguous/);
install({Thing, defaultMode:7}, [{...spec, static:true, name:'mode', returnsThis:false,
    calls:[{target:'_static', params:[{name:'mode',type:'number',optional:true,default_value:'defaultMode'}]}]}]);
assert.strictEqual(Thing.mode(), 7);
install({}, [spec]); // A headless build may omit this class.
assert.throws(() => install({Thing}, [{...spec, calls:[{target:'missing',params:[]}]}]), /Missing generated binding/);

// Schema validation leaves the actual record and callback untouched. Adapters
// remain responsible for native field conversion and callback retention.
const schemas = {Base:{kind:'record',fields:{enabled:{type:'boolean'}}},
    Options:{kind:'record',extends:['Base'],fields:{done:{schema:'Callback'},data:{builtin:'Uint8Array',optional:true}}},
    Callback:{kind:'callback',params:[],returns:{type:'undefined'}}};
const structured = {...method, params:[{name:'options',type:'object',contract:{schema:'Options',nullable:true}}],
    native_binding:{...method.native_binding,binding_name:'_moveOptions'}};
const structuredSpec = wrapperSpec(owner, structured, {...api, schemas});
assert.deepStrictEqual(Object.keys(structuredSpec.schemas).sort(), ['Base','Callback','Options']);
install({Thing}, [structuredSpec]);
const options = {enabled:true,done() {},data:bytes};
assert.strictEqual(thing.move(options), thing);
assert.strictEqual(seen, options);
assert.throws(() => thing.move({done() {}}), TypeError);
assert.throws(() => thing.move({enabled:true,done:7}), TypeError);
assert.strictEqual(thing.move(null), thing);
console.log('Emscripten generation and wrapper tests passed.');
