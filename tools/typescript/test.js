#!/usr/bin/env node
'use strict';
const assert = require('assert/strict');
const fs = require('fs');
const path = require('path');
const os = require('os');
const {execFileSync} = require('child_process');
const {generate, run} = require('./generate');
const root = path.resolve(__dirname, '../..');
const tsc = require.resolve('typescript/bin/tsc');
function node(script, args = []) { execFileSync(process.execPath, [script, ...args], {cwd:root, stdio:'inherit'}); }
run(true);
node(path.join(__dirname,'build.js'));
const packageDir = path.join(root,'build/typescript/package');
assert(!fs.existsSync(path.join(packageDir,'IDL_GAPS.md')), 'Private IDL gaps must not be packaged');
assert.doesNotMatch(fs.readFileSync(path.join(packageDir,'README.md'),'utf8'), /IDL_GAPS|note-ai/);
node(tsc, ['-p','test/typescript']);

// Fail closed when a nested record cannot be described. A valid overload remains.
const sample = {vers:'test', schemas:{
    Bad:{kind:'record', fields:{payload:{type:'object'}}},
    Nested:{kind:'record', fields:{child:{schema:'Bad'}}},
    Callback:{kind:'callback', params:[{name:'value',schema:'Nested'}], returns:{type:'boolean'}}
}, interface:[{type:'function',name:'accept',params:[[{name:'value',type:'string'}],
    [{name:'value',contract:{schema:'Nested'}}]],returns:'boolean'}]};
const result = generate(sample);
assert.equal(result.text,generate(sample).text);
assert.match(result.text,/accept\(value: string\): boolean/);
assert.doesNotMatch(result.text,/interface Bad|interface Nested|type Callback|value: Nested/);
assert(result.report.deferred.some(x=>x.symbol==='accept#2'));
assert(result.report.deferred.some(x=>x.symbol==='Callback'));
const ts = require('typescript');
const declaration = ts.createSourceFile('index.d.ts', fs.readFileSync(path.join(root,'types/index.d.ts'),'utf8'), ts.ScriptTarget.Latest, true);
function rejectAny(node) { assert.notEqual(node.kind, ts.SyntaxKind.AnyKeyword); ts.forEachChild(node,rejectAny); }
rejectAny(declaration);

// Compile a consumer outside the repository so accidental source-tree imports
// and missing files in the actual distribution cannot be masked by the checkout.
const temporary = fs.mkdtempSync(path.join(os.tmpdir(),'pdg-typescript-'));
try {
    fs.cpSync(path.join(root,'build/typescript/package'),path.join(temporary,'pdg'),{recursive:true});
    fs.writeFileSync(path.join(temporary,'consumer.ts'), `
import type PDG = require('./pdg');
import {View} from './pdg/mvc-app/View';
import {Controller} from './pdg/mvc-app/Controller';
import {Subject, IObserver} from './pdg/mvc-app/Observer';
declare const controller: Controller;
declare const area: PDG.Rect;
class ScoreView extends View { score = 0; }
const view: ScoreView = new ScoreView(controller, area).moveTo(10,20,0.4);
new Subject().addObserver(new IObserver());
// @ts-expect-error preserve concrete subclasses in chains
const wrong: string = view.repeat(2);
`);
    node(tsc,['--strict','--noEmit','--skipLibCheck','false','--target','ES2022','--module','commonjs','--typeRoots',path.join(__dirname,'node_modules/@types'),path.join(temporary,'consumer.ts')]);
    const {Subject,IObserver} = require(path.join(temporary,'pdg/mvc-app/Observer'));
    let count=0;
    class Counter extends IObserver { notify(subject) { count++; subject.removeObserver(this); } }
    const subject = new Subject(); subject.addObserver(new Counter()); subject.notifyObservers(); subject.notifyObservers();
    assert.equal(count,1);
} finally { fs.rmSync(temporary,{recursive:true,force:true}); }
console.log('TypeScript checks passed: IDL omissions, strict contracts/examples, MVC compilation and isolated distribution consumer.');

// These vocabulary tests deliberately use invented names: no PDG-specific
// branches may be necessary to emit constructors, callbacks, records or events.
const vocabulary = {vers:'test',runtime_profile:{runtime:'test'},schemas:{
    BaseRecord:{kind:'record',fields:{id:{type:'number'}}},
    RecordCopy:{kind:'record',extends:['BaseRecord'],identity:'search',fields:{points:{items:{type:'string'}}}},
    Values:{kind:'alias',value:{values:{schema:'BaseRecord'}}},
    Factory:{kind:'constructor',params:[],returns:{schema:'RecordCopy'}},
    Payloads:{kind:'event_map',entries:{arrived:{schema:'BaseRecord'}}},
    PlatformBytes:{kind:'alias',value:{variants:[{runtimes:['test'],builtin:'Uint8Array'}]}}
},interface:[{name:'arrived',type:'number',readonly:true,value:1},
    {name:'Widget',type:'class',native:true,construction:{kind:'factory'},interface:[]},
    {name:'receive',type:'function',returns:'void',params:[{name:'code',type:'number'},{name:'handler',schema:'Factory'}],
        event_map:{schema:'Payloads',selector:'code',callback:'handler',returns:{type:'boolean'}}}]};
const generic = generate(vocabulary);
assert.equal(generic.report.deferred.length,0);
assert.match(generic.text,/interface RecordCopy extends BaseRecord/);
assert.match(generic.text,/type Factory = new \(\) => RecordCopy/);
assert.match(generic.text,/receive<K extends keyof Payloads>/);
assert.match(generic.text,/type PlatformBytes = Uint8Array/);
assert.deepEqual(generic.report.nonConstructible,[{symbol:'Widget',kind:'factory'}]);
