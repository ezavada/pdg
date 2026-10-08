'use strict';

// Read declarations from implementation files; never load or execute PDG.
const fs = require('fs');
const path = require('path');
const {spawnSync} = require('child_process');
const acorn = require('../deps/node/deps/acorn/acorn/dist/acorn');
const root = path.resolve(__dirname, '..');
function filesUnder(directory, extension) {
    return fs.readdirSync(directory, {withFileTypes: true}).sort((a,b) => a.name.localeCompare(b.name)).flatMap(entry => {
        const filename = path.join(directory, entry.name);
        return entry.isDirectory() ? filesUnder(filename, extension) : filename.endsWith(extension) ? [filename] : [];
    });
}
function sourceFiles() {
    return filesUnder(path.join(root, 'src/bindings/common'), '.cpp').concat(
        filesUnder(path.join(root, 'src/bindings/common'), '.h'),
        path.join(root, 'src/bindings/javascript/v8/pdg_js_classes.cpp'),
        path.join(root, 'src/bindings/javascript/pdg.js'),
        filesUnder(path.join(root, 'src/js'), '.js').filter(file => !file.includes('/mvc-app/') && !file.endsWith('/interface_metadata_data.js')),
        filesUnder(path.join(root, 'src/bindings/emscripten'), '.h'),
        filesUnder(path.join(root, 'src/bindings/emscripten'), '.cpp'));
}
function split(text, separator = ',') {
    const result = []; let start = 0, depth = 0, quote = null;
    for (let i = 0; i < text.length; ++i) {
        const c = text[i];
        if (quote) { if (c === '\\') ++i; else if (c === quote) quote = null; continue; }
        if (c === '"' || c === "'") quote = c;
        else if ('([{'.includes(c)) ++depth;
        else if (')]}'.includes(c)) --depth;
        else if (c === separator && !depth) { result.push(text.slice(start, i).trim()); start = i + 1; }
    }
    result.push(text.slice(start).trim());
    return result;
}
function cppString(text) {
    return (text.match(/"(?:\\.|[^"\\])*"/g) || []).map(value => JSON.parse(value)).join('');
}
function signature(brief, result, parameters) {
    const normalizeType = type => type.replace(/^\[(.*)\]$/, '$1').replace(/^CR /, '').trim();
    function qualifiedType(text) {
        const type = normalizeType(text);
        if (!/[&*]|\bconst\b/.test(type)) return {type};
        const match = /^(const\s+)?object\s+(const\s+)?(\w+)\s*(const\s*)?(&&|[&*])$/.exec(type);
        if (!match || [match[1],match[2],match[4]].filter(Boolean).length > 1)
            throw Error('Invalid native-qualified type: ' + type);
        return {type:'object '+match[3], native_qualifiers:{
            indirection:match[5] === '&&' ? 'rvalue-reference' : match[5] === '&' ? 'reference' : 'pointer',
            const:!!(match[1] || match[2] || match[4])
        }};
    }
    let args = parameters.trim().replace(/^\(/, '').replace(/\)$/, '');
    // Expand independent alternative groups, including alternatives that contain
    // several parameters. Split respects nested default-value expressions.
    function expand(text) {
        const open = text.indexOf('{');
        if (open < 0) return [text];
        let depth = 1, close = open + 1;
        for (; close < text.length && depth; ++close) {
            if (text[close] === '{') ++depth;
            else if (text[close] === '}') --depth;
        }
        if (depth) throw Error('Unclosed signature alternatives: ' + parameters);
        return split(text.slice(open + 1, close - 1), '|').flatMap(variant =>
            expand(text.slice(0, open) + variant + text.slice(close)));
    }
    const variants = expand(args);
    function parseParameters(args) {
        if (!args.trim()) return [];
        return split(args).map(arg => {
            const match = arg.match(/^(\[[^\]]+\]|\S+)\s+([\w]+)(?:\s*=\s*(.*))?$/);
            if (!match) throw Error('Invalid signature parameter: ' + arg + ' in ' + parameters);
            const param = {name: match[2], ...qualifiedType(match[1])};
            if (match[3] !== undefined) { param.optional = true; param.default_value = match[3].trim(); }
            return param;
        });
    }
    const descriptor = {brief, params: variants.map(parseParameters)};
    if (variants.length === 1) descriptor.params = descriptor.params[0];
    const resultType = qualifiedType(result);
    const returns = resultType.type;
    if (resultType.native_qualifiers) descriptor.native_return_qualifiers = resultType.native_qualifiers;
    if (returns !== 'undefined') descriptor.returns = returns.replace('object cpSpace','object CpSpace').replace('object cpConstraint','object CpConstraint').replace('object cpArbiter','object CpArbiter');
    return descriptor;
}
function extractNative(nativeFiles = sourceFiles().filter(file =>
    (file.endsWith('.cpp') || file.endsWith('_bindings.h')) && !file.includes('/emscripten/'))) {
    const candidates = process.env.PDG_METADATA_CPP ? [process.env.PDG_METADATA_CPP] : ['clang', 'gcc'];
    const compiler = candidates.find(candidate => spawnSync(candidate, ['--version'], {stdio: 'ignore'}).status === 0);
    if (!compiler) throw Error('A C++ preprocessor (clang/gcc or PDG_METADATA_CPP) is required for interface metadata');
    const source = nativeFiles.map(file => 'PDG_META_SOURCE(' + JSON.stringify(path.relative(root, file)) + ')\n#include ' + JSON.stringify(file)).join('\n');
    const processed = spawnSync(compiler, ['-E', '-P', '-x', 'c++', '-DPDG_BUILDING_INTERFACE_FILES', '-DPDG_USE_CHIPMUNK_PHYSICS', '-DPDG_SPRITER_SUPPORT',
        '-I'+path.join(root,'src/bindings/javascript/v8'), '-I'+path.join(root,'src/bindings/common'),
        '-include', path.join(root,'tools/interface-metadata-macros.h'), '-'], {input:source, encoding:'utf8', maxBuffer:32*1024*1024});
    if (processed.status !== 0) throw Error('Metadata preprocessing failed:\n' + processed.stderr);
    const methods = new Map(), bindings = new Map(), classes = new Map(), constants = new Map(), declarations = new Map(), ownership = new Map(), singletons = new Map();
    const declaredOrigins = new Map(), construction = new Map();
    let current, sourceFile, validationEnd = -1, bodyStart = -1;
    function finishBody(end) {
        if (bodyStart < 0 || !methods.has(current)) return;
        const record = methods.get(current);
        if (!record.params) return;
        const body = processed.stdout.slice(bodyStart,end).replace(/"(?:\\.|[^"\\])*"/g, '""');
        const easingNames = new Set([...body.matchAll(/(?:easingIdToFunc\s*\(\s*|gEasingFunctions\s*\[\s*)(\w+)/g)].map(match => match[1]));
        const variants = Array.isArray(record.params[0]) ? record.params : [record.params];
        for (const params of variants) for (const param of params)
            if (easingNames.has(param.name) && /^number(?: int| uint)?$/.test(param.type))
                param.contract = {schema:'EasingFunction'};
        // Preserve a direct call's reordered arguments without a per-method exception.
        // Only a bijection of declared names is safe to infer here.
        const directCalls = [...body.matchAll(/self->\w+\s*\(([^()]*)\)/g)];
        if (!Array.isArray(record.params[0]) && directCalls.length === 1) {
            const args = directCalls[0][1].split(',').map(s => s.trim());
            const names = record.params.map(p => p.name);
            if (args.length === names.length && new Set(args).size === names.length &&
                args.every(name => names.includes(name)) && args.some((name,i) => name !== names[i]))
                record.parameter_order = args;
        }
        // A single value argument forwarded into a native value-returning call.
        // Keep the actual local type (Rect public inputs may be RotatedRect).
        const calls = [...body.matchAll(/self->(\w+)\s*\(/g)];
        const call = /\b(\w+)\s+out\s*=\s*self->(\w+)\((\w+)\)\s*;/.exec(body);
        if (calls.length === 1 && call && record.params.length === 1 &&
            record.params[0].name === call[3] && record.returns === 'object '+call[1] &&
            /^[@\s]*\{\s*args\.GetReturnValue\(\)\.Set\(\s*v8_MakeJavascript\w+\(isolate,\s*out\)/.test(body.slice(call.index+call[0].length))) {
            const local = new RegExp('pdg::(\\w+)\\s+'+call[3]+'\\s*;').exec(body);
            if (local) record.value_call = {method:call[2], result:call[1], argument:local[1]};
        }
    }
    const groups = [];
    const markers = /PDG_META_(SOURCE|METHOD|FUNCTION|CONSTRUCTOR|SIGNATURE|BIND|CLASS|BASE|CONSTANT|DECLARE|OWNERSHIP|SINGLETON|CONSTRUCTION|GROUP_BEGIN|GROUP_END|MEMBER_DECL|ARG_COUNT|ARG_RULE|C_CALL|C_CASE|C_INDEX)\(((?:"(?:\\.|[^"\\])*"|[^)])*)\)/g;
    for (const match of processed.stdout.matchAll(markers)) {
        if (['SOURCE','METHOD','FUNCTION','CONSTRUCTOR'].includes(match[1])) {
            finishBody(match.index);
            bodyStart = match.index + match[0].length;
        }
        const args = split(match[2]).map(cppString);
        switch (match[1]) {
        case 'SOURCE': sourceFile = args[0]; current = null; break;
        case 'GROUP_BEGIN': groups.push({klass:args[0], base:args[1]}); break;
        case 'GROUP_END':
            if (!groups.pop()) throw Error('Unmatched method group in '+sourceFile);
            break;
        case 'MEMBER_DECL': {
            const group = [...groups].reverse().find(item => item.klass === args[0]);
            const method = args[0]+'.'+args[1];
            if (group) declaredOrigins.set(method, group.base);
            else declaredOrigins.delete(method);
            break;
        }
        case 'DECLARE': declarations.set(args[0], {kind:args[1], source:sourceFile}); break;
        case 'OWNERSHIP': ownership.set(args[0], args[1]); break;
        case 'SINGLETON': singletons.set(args[0], args[1]); break;
        case 'CONSTRUCTION': construction.set(args[0], {kind:args[1],factory:args[2]}); break;
        case 'CLASS': classes.set(args[1], {name:args[0], source:sourceFile}); break;
        case 'BASE': classes.get(args[0]).base = args[1]; break;
        case 'CONSTANT': constants.set(args[0], {name:args[0],type:args[1],readonly:true}); break;
        case 'BIND': {
            const group = [...groups].reverse().find(item => item.klass === args[0]);
            bindings.set(args[0]+'.'+args[1], {method:args[0]+'.'+args[2], source:sourceFile, origin:group && group.base});
            break;
        }
        case 'METHOD': current = args[0]+'.'+args[1]; methods.set(current,{source:sourceFile}); break;
        case 'FUNCTION': current = 'pdg.'+args[0]; methods.set(current,{source:sourceFile}); break;
        case 'CONSTRUCTOR': current = args[0]+'.constructor'; methods.set(current,{source:sourceFile}); break;
        case 'SIGNATURE':
            if (!current) throw Error('Signature without method in ' + sourceFile);
            Object.assign(methods.get(current), signature(args[0],args[1],args[2]));
            validationEnd = match.index + match[0].length; break;
        case 'C_CASE': methods.get(current).c_predicate = args[0]; break;
        case 'C_INDEX': {
            const record = methods.get(current);
            record.c_index = {parameter:args[0], count:args[1]};
            break;
        }
        case 'C_CALL': {
            const record = methods.get(current);
            const callArgs = split(args[1].slice(1,-1));
            if (callArgs.shift() !== 'self') throw Error('C-function receiver must be first: '+current);
            const dispatch = record.c_dispatch || (record.c_dispatch = {cases:[]});
            dispatch.cases.push({symbol:args[0], ...(record.c_predicate ? {predicate:record.c_predicate} : {}), arguments:callArgs});
            delete record.c_predicate;
            break;
        }
        case 'ARG_COUNT':
        case 'ARG_RULE': {
            const record = methods.get(current);
            if (!record || validationEnd < 0 || !/^[;@\s]*$/.test(processed.stdout.slice(validationEnd, match.index))) {
                validationEnd = -1; break;
            }
            validationEnd = match.index + match[0].length;
            const validation = record.validation || (record.validation = {parameters:[]});
            if (match[1] === 'ARG_COUNT') validation.arity = Number(args[0]);
            else validation.parameters.push({macro:args[0], index:Number(args[1])-1, name:args[2]});
            break;
        }
        }
    }
    finishBody(processed.stdout.length);
    if (groups.length) throw Error('Unclosed method group in '+sourceFile);
    // This macro currently lives outside the V8 macro header's include guard,
    // so subsequent includes redefine it. Read its registration sites directly.
    for (const file of nativeFiles) {
        for (const match of fs.readFileSync(file,'utf8').matchAll(/\bINIT_UINT_CONSTANT\("([^"]+)"\s*,/g))
            constants.set(match[1],{name:match[1],type:'number',readonly:true});
    }
    for (const record of methods.values()) {
        const v = record.validation, params = record.params;
        if (!v) continue;
        if (!params || !params.length || Array.isArray(params[0]) || v.arity !== params.length ||
            v.parameters.length !== params.length || params.some((param, index) =>
                param.optional || !/^number(?: (?:int|uint))?$/.test(param.type) ||
                v.parameters[index].index !== index || v.parameters[index].name !== param.name))
            delete record.validation;
        else {
            const ranges = {INT8_ARG:[-128,127], INT16_ARG:[-32768,32767],
                INT32_ARG_RANGE:[-2147483648,2147483647], UINT8_ARG:[0,255],
                UINT16_ARG:[0,65535], UINT24_ARG:[0,16777215], UINT32_ARG_RANGE:[0,4294967295]};
            v.parameters = v.parameters.map(({index,macro,name}) => ({index,name,type:'number',
                ...(ranges[macro] ? {integer:true,min:ranges[macro][0],max:ranges[macro][1]} : {}),
                ...(macro === 'UINT32_ARG' ? {conversion:'uint32'} : ['INT32_ARG','INT8_ARG','INT16_ARG'].includes(macro) ? {conversion:'int32'} : {})}));
        }
    }
    return {methods, bindings, classes, constants, declarations, ownership, singletons, declaredOrigins, construction};
}
function extractJavaScript(files = sourceFiles().filter(file => file.endsWith('.js'))) {
    const methods = new Map(), classes = new Map(), bases = new Map(), singletons = new Map();
    for (const file of files) {
        const source = fs.readFileSync(file, 'utf8');
        const tree = acorn.parse(source, {ecmaVersion:'latest', sourceType:'script'});
        const getterAliases = new Map();
        function walk(node, owner, method) {
            if (!node || typeof node !== 'object') return;
            if (node.type === 'VariableDeclarator' && node.id.type === 'Identifier' && node.init &&
                node.init.type === 'MemberExpression' && node.init.object.name === 'bindings')
                getterAliases.set(node.id.name, node.init.property.name);
            if (node.type === 'AssignmentExpression' && node.left.type === 'MemberExpression' &&
                node.left.object.name === 'bindings' && node.right.type === 'CallExpression' && !node.right.arguments.length) {
                const callee = node.right.callee;
                const getter = callee.type === 'Identifier' ? getterAliases.get(callee.name) :
                    callee.type === 'MemberExpression' && callee.object.name === 'bindings' ? callee.property.name : undefined;
                if (getter && getter.startsWith('get')) singletons.set(getter, node.left.property.name);
            }
            if (node.type === 'ClassDeclaration' || node.type === 'ClassExpression') {
                owner = node.id && node.id.name;
                if (owner) {
                    classes.set(owner,{source:path.relative(root,file),position:node.start});
                    if (node.superClass && node.superClass.type === 'Identifier') bases.set(owner,[node.superClass.name]);
                }
            }
            if (node.type === 'MethodDefinition' && owner) {
                method = owner+'.'+(node.kind === 'constructor' ? 'constructor' : node.key.name);
                methods.set(method,{source:path.relative(root,file),position:node.start});
            }
            if (node.type === 'AssignmentExpression' && node.left.type === 'MemberExpression' && node.left.property.name === 'superclass') {
                const klass = node.left.object.property && node.left.object.property.name;
                const expression = node.right;
                const values = expression.type === 'ArrayExpression' ? expression.elements :
                    expression.type === 'NewExpression' && expression.callee.name === 'Array' ? expression.arguments : [expression];
                if (klass && values.every(value => value.type === 'MemberExpression')) bases.set(klass,values.map(value => value.property.name));
            }
            for (const [key, value] of Object.entries(node)) {
                if (key === 'start' || key === 'end') continue;
                if (Array.isArray(value)) value.forEach(child => walk(child,owner,method));
                else if (value && typeof value === 'object') walk(value,owner,method);
            }
        }
        walk(tree);
    }
    return {methods, classes, bases, singletons};
}

function annotations(files = sourceFiles()) {
    const records = [];
    for (const file of files) {
        const source = fs.readFileSync(file,'utf8');
        const pattern = /^[ \t]*\/\/ @pdg-(class|member|contract|schema|adapter) (\{[^\r\n]*\})[ \t]*$|\/\* @pdg-(class|member|contract|schema|adapter)\s*([\s\S]*?)\*\//gm;
        for (const match of source.matchAll(pattern)) {
            records.push({kind:match[1] || match[3], data:JSON.parse(match[2] || match[4]), source:path.relative(root,file)});
        }
    }
    return records;
}
function readContracts(records = annotations()) {
    const result = {version:1,schemas:{},members:{}};
    for (const {kind,data} of records) {
        const target = kind === 'schema' ? result.schemas : kind === 'contract' ? result.members : null;
        if (!target) continue;
        if (target[data.name]) throw Error('Duplicate '+kind+' annotation: '+data.name);
        target[data.name] = data.value;
    }
    return result;
}

function inventory() {
    const native = extractNative(), js = extractJavaScript(), records = annotations();
    const classes = new Map(), byCpp = new Map(), explicitMethods = new Set(), methodOrigins = new Map();
    for (const cpp of native.classes.keys()) {
        if (!native.declarations.has(cpp)) throw Error('Missing native class declaration: '+cpp);
    }
    for (const cpp of native.declarations.keys()) {
        const registered = native.classes.get(cpp);
        if (!registered) throw Error('Missing native class export: '+cpp);
        const klass = {name:registered.name,type:'class',native:true,implements:[],native_binding:{type:'pdg::'+cpp},interface:[]};
        if (registered.base) klass.native_binding.base = 'pdg::'+registered.base;
        if (native.ownership.has(cpp)) klass.native_binding.ownership = native.ownership.get(cpp);
        if (native.singletons.has(cpp)) klass.singleton = native.singletons.get(cpp);
        if (native.construction.has(cpp)) klass.construction = native.construction.get(cpp);
        classes.set(klass.name,klass); byCpp.set(cpp,klass);
    }
    const classDeclarations = new Set();
    for (const {kind,data,source} of records) {
        if (kind !== 'class') continue;
        if (classDeclarations.has(data.name)) throw Error('Duplicate class annotation: '+data.name);
        classDeclarations.add(data.name);
        let klass = classes.get(data.name);
        if (!klass) {
            if (!js.classes.has(data.name) && !fs.readFileSync(path.join(root,source),'utf8').includes('function '+data.name+'('))
                throw Error('Stale JavaScript class declaration: '+data.name);
            klass = {name:data.name,type:'class',implements:[],interface:[]}; classes.set(data.name,klass);
        }
        if (data.native_binding) Object.assign(klass.native_binding || (klass.native_binding = {}),data.native_binding);
        for (const key of ['construction','mixins','availability']) if (data[key]) klass[key] = data[key];
    }
    for (const [name,klass] of classes) {
        const registration = [...native.classes].find(([,value]) => value.name === name);
        const bases = js.bases.get(name) || (registration && registration[1].base ? [byCpp.get(registration[1].base).name] : []);
        klass.implements = [...new Set([...bases, ...(klass.mixins || [])])];
        if (klass.native && !klass.native_binding.base && bases.length === 1) {
            const base = classes.get(bases[0]);
            if (base && base.native_binding) klass.native_binding.base = base.native_binding.type;
        }
    }
    // The shared wrapper also publishes facade singletons such as pdg.fs.
    // Resolve getter aliases statically through their native return signatures.
    for (const [getter, singleton] of js.singletons) {
        const binding = native.bindings.get('pdg.'+getter);
        const method = binding && native.methods.get(binding.method);
        const klass = method && classes.get((method.returns || '').replace(/^object /, ''));
        if (!klass) continue;
        if (klass.singleton && klass.singleton !== singleton) throw Error('Conflicting singleton export: '+klass.name);
        klass.singleton = singleton;
    }
    for (const klass of classes.values()) {
        if (klass.singleton) {
            klass.note = 'Primary access via singleton instance: pdg.'+klass.singleton;
            klass.construction = {kind:'singleton',access:'pdg.'+klass.singleton};
        }
    }
    const rootEntries = new Map([...native.constants].map(([name,value]) => [name,value]));
    for (const [qualified,binding] of native.bindings) {
        const [cpp,name] = qualified.split('.');
        if (name.startsWith('_')) continue;
        const record = native.methods.get(binding.method);
        if (!record || !record.params) {
            const owner = cpp === 'pdg' ? cpp : byCpp.get(cpp) && byCpp.get(cpp).name;
            if (records.some(item => item.kind === 'member' && item.data.name === owner+'.'+name && item.data.params)) continue;
            throw Error('Missing METHOD_SIGNATURE or inline declaration for '+qualified);
        }
        const member = {name,type:'function',native:true,brief:record.brief,params:record.params};
        if (record.returns) member.returns = record.returns;
        if (record.native_return_qualifiers) member.native_return_qualifiers = record.native_return_qualifiers;
        if (record.validation) member.argument_validation = record.validation;
        if (record.value_call) member.native_value_call = record.value_call;
        if (record.parameter_order) member.native_parameter_order = record.parameter_order;
        if (record.c_dispatch) {
            member.native_c_dispatch = {...record.c_dispatch, ...(record.c_index ? {index:record.c_index} : {})};
            if (record.returns && record.returns !== 'this' && record.c_dispatch.cases.some(c => c.predicate))
                member.returns_contract = {one_of:[{type:record.returns},{type:'undefined'}]};
        }
        if (cpp === 'pdg') rootEntries.set(name,member);
        else if (byCpp.has(cpp)) {
            const klass = byCpp.get(cpp);
            klass.interface.push(member);
            const origin = binding.origin || native.declaredOrigins.get(binding.method);
            if (binding.origin && native.declaredOrigins.has(binding.method) &&
                binding.origin !== native.declaredOrigins.get(binding.method))
                throw Error('Conflicting method group origins: '+qualified);
            if (origin) methodOrigins.set(klass.name+'.'+name, origin);
            const text = fs.readFileSync(path.join(root,record.source),'utf8');
            const implementation = binding.method.split('.')[1];
            if (new RegExp('(?:METHOD_IMPL|SCRIPT_METHOD_IMPL|STATIC_METHOD_IMPL)\\(\\s*'+cpp+'\\s*,\\s*'+implementation+'\\s*\\)').test(text))
                explicitMethods.add(klass.name+'.'+name);
        }
    }
    for (const [qualified,record] of js.methods) {
        const [owner,name] = qualified.split('.');
        if (!classes.has(owner) || !record.params || name === 'constructor' || name.startsWith('_')) continue;
        const member = {name,type:'function',brief:record.brief,params:record.params};
        if (record.returns) member.returns = record.returns;
        if (record.native_return_qualifiers) member.native_return_qualifiers = record.native_return_qualifiers;
        classes.get(owner).interface.push(member);
    }
    const declared = new Set();
    for (const {kind,data} of records) {
        if (kind !== 'member') continue;
        if (declared.has(data.name)) throw Error('Duplicate member annotation: '+data.name);
        declared.add(data.name);
        const [owner,name] = data.name.split('.');
        const descriptor = {...data,name};
        if (owner === 'pdg') {
            const existing = rootEntries.get(name);
            if (existing && existing.params && descriptor.params) throw Error('Duplicate signature declaration: '+data.name);
            rootEntries.set(name,{...existing,...descriptor});
        }
        else {
            const klass = classes.get(owner);
            if (!klass) throw Error('Unknown member owner: '+owner);
            const existing = klass.interface.find(item => item.name === name);
            if (existing) {
                // Signature-bearing annotations would create a second authority.
                if (data.params && existing.params) throw Error('Duplicate signature declaration: '+data.name);
                Object.assign(existing,descriptor);
            } else {
                if (!data.type) throw Error('Stale member annotation: '+data.name);
                if (data.type === 'function' && data.native) {
                    const cpp = [...byCpp].find(([,value]) => value === klass)[0];
                    if (!native.bindings.has(cpp+'.'+name)) throw Error('Stale native method annotation: '+data.name);
                }
                klass.interface.push(descriptor);
            }
        }
    }
    // Method groups identify API origins even when each derived wrapper has an
    // explicit implementation. A changed signature remains a local override;
    // composition through a group alone does not make a class inherit it.
    function derivesFrom(klass, base, visiting = new Set()) {
        if (klass === base) return true;
        if (visiting.has(klass.name)) throw Error('Cyclic metadata inheritance: '+klass.name);
        visiting = new Set(visiting).add(klass.name);
        return klass.implements.some(name => {
            const parent = classes.get(name);
            if (!parent) throw Error('Unknown metadata base: '+name);
            return derivesFrom(parent, base, visiting);
        });
    }
    for (const [qualified, cppOrigin] of methodOrigins) {
        const [owner, name] = qualified.split('.');
        const klass = classes.get(owner), base = byCpp.get(cppOrigin);
        if (!base) throw Error('Unknown method group origin: '+cppOrigin);
        if (klass === base || !derivesFrom(klass, base)) continue;
        const member = klass.interface.find(item => item.name === name);
        const inherited = base.interface.find(item => item.name === name);
        // A reusable group can also provide concrete-class helpers that the
        // base interface does not expose (e.g. getMyClassTag()).
        if (!inherited) continue;
        if (JSON.stringify([member.params,member.returns,member.argument_validation]) === JSON.stringify([inherited.params,inherited.returns,inherited.argument_validation]))
            member.inherited_from = inherited.inherited_from || base.name;
    }
    // Repeated native registration macros expose inherited methods too. Retain
    // one description on the base when the public signature is identical.
    function inheritedMember(klass, name) {
        const own = klass.interface.find(item => item.name === name && item.type !== 'constructor');
        if (own) return own;
        for (const baseName of klass.implements) {
            const member = inheritedMember(classes.get(baseName), name);
            if (member) return member;
        }
    }
    function removeInherited(klass,visiting = new Set()) {
        if (visiting.has(klass.name)) throw Error('Cyclic metadata inheritance: '+klass.name);
        visiting = new Set(visiting).add(klass.name);
        for (const baseName of klass.implements) {
            const base = classes.get(baseName);
            if (!base) throw Error('Unknown metadata base: '+baseName);
            removeInherited(base,visiting);
            klass.interface = klass.interface.filter(member => {
                const inherited = inheritedMember(base, member.name);
                return !inherited || explicitMethods.has(klass.name+'.'+member.name) || member.native_binding || member.type !== 'function' ||
                    JSON.stringify([member.params,member.returns,member.argument_validation]) !== JSON.stringify([inherited.params,inherited.returns,inherited.argument_validation]);
            });
        }
    }
    for (const klass of classes.values()) removeInherited(klass);
    for (const klass of classes.values()) {
        const constructors = klass.interface.filter(member => member.type === 'constructor');
        if (constructors.length && klass.construction && klass.construction.kind !== 'public')
            throw Error('Constructor conflicts with construction policy: ' + klass.name);
        if (constructors.length) klass.construction = {kind:'public'};
        if (klass.construction && !['public','factory','singleton','borrowed','abstract'].includes(klass.construction.kind))
            throw Error('Unknown construction policy: ' + klass.name);
    }
    const adapters = {};
    for (const {kind,data} of records) {
        if (kind !== 'adapter') continue;
        if (adapters[data.name]) throw Error('Duplicate adapter: '+data.name);
        adapters[data.name] = data.value;
    }
    return {api:{metadata_version:1,name:'pdg',type:'module',lang:'javascript',interface:[...rootEntries.values(),...classes.values()]},adapters,contracts:readContracts(records)};
}

module.exports = {sourceFiles, extractNative, extractJavaScript, signature, annotations, readContracts, inventory};
