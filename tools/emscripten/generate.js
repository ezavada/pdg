#!/usr/bin/env node
'use strict';

// Compile source-owned metadata and explicit custom adapter fragments. Never load PDG.
const fs = require('fs');
const path = require('path');
const crypto = require('crypto');
const {buildApi} = require('../build-interface-metadata');
const root = path.resolve(__dirname, '../..');
const base = 'src/bindings/emscripten/';
const policies = new Set(['reference', 'copy', 'take_ownership', 'reference_internal']);
function hash(value) { return crypto.createHash('sha256').update(JSON.stringify(value)).digest('hex'); }
function generatesMember(owner, member) {
    if (member.inherited_from) return false;
    const explicit = member.native_binding?.browser?.generate;
    if (explicit !== undefined) return explicit;
    // The public inventory already identifies native methods. Per-member
    // metadata is needed only for exclusions or a non-default native mapping.
    const browser = owner.native_binding?.browser;
    return member.type === 'function' && !!member.native && !member.static &&
        !!browser?.generate && browser.kind !== 'value_object' &&
        (browser.defaults?.generate ?? true);
}
function validateExceptionPolicy(policy) {
    if (policy !== undefined && !['javascript', 'native'].includes(policy))
        throw Error('Unknown browser exception policy: ' + policy);
}
function returnConversion(member, api) {
    const type = member.returns_contract?.type || member.returns;
    const match = /^object (\w+)$/.exec(type || '');
    if (!match) return null;
    const owner = api.interface.find(item => item.type === 'class' && item.name === match[1]);
    if (owner?.native_binding?.ownership === 'retained') return {retained:true};
    if (owner?.native_binding?.browser?.pointer_policy === 'borrowed' && owner.native_binding.browser.remember_receiver)
        return {identity:true};
    const rule = owner?.native_binding?.browser?.return_value;
    if (!rule) return null;
    if (!Array.isArray(rule.arguments) || rule.arguments.some(field => typeof field !== 'string' || !/^(\$|[A-Za-z_]\w*)$/.test(field)))
        throw Error('Invalid browser return conversion: ' + owner.name);
    return {type:owner.name, arguments:rule.arguments};
}
function returnsReceiver(member) {
    return member.returns_contract?.type === 'this' || member.returns === 'this';
}
function borrowedType(type, api) {
    return api.interface.some(owner => 'object '+owner.name === type && owner.native_binding?.browser?.pointer_policy === 'borrowed');
}
function eventFamilies(owner, api, seen = new Set()) {
    if (seen.has(owner.name)) throw Error('Cyclic browser event policy: '+owner.name);
    seen.add(owner.name);
    const policy = owner.native_binding?.browser?.events;
    if (!policy) return [];
    const base = policy.extends && api.interface.find(item => item.name === policy.extends);
    if (policy.extends && !base) throw Error('Unknown browser event policy: '+policy.extends);
    const families = [...(base ? eventFamilies(base,api,seen) : []), ...(policy.families || [])];
    const names = new Set();
    for (const family of families) {
        if (!/^\w+$/.test(family.event) || !/^\w+$/.test(family.field) || !family.methods)
            throw Error('Invalid browser event family: '+owner.name);
        for (const [name, code] of Object.entries(family.methods)) {
            if (!/^\w+$/.test(name) || !Number.isInteger(code) || names.has(name)) throw Error('Invalid browser event helper: '+name);
            names.add(name);
        }
    }
    return families;
}
function eventSpec(owner, member, api) {
    const families = eventFamilies(owner,api);
    if (!families.length) return null;
    if (member.name === owner.native_binding.browser.events.selector)
        return {owner:owner.name,name:member.name,families};
    const family = families.find(f => Object.hasOwn(f.methods,member.name));
    return family ? {owner:owner.name,name:member.name,event:family.event,field:family.field,code:family.methods[member.name]} : null;
}
function bindingName(member, api) {
    return member.native_binding?.binding_name || (returnConversion(member, api) || returnsReceiver(member) || member.argument_validation ? '_' : '') + member.name;
}
function inventory(api) {
    const result = new Map();
    for (const owner of [api, ...api.interface.filter(item => item.type === 'class')]) {
        for (const member of owner.interface || []) {
            if ((!member.native && !generatesMember(owner, member)) || member.inherited_from || !['function','constructor'].includes(member.type)) continue;
            result.set(owner.name + '.' + member.name, {owner, member});
        }
    }
    return result;
}
function fingerprint(member, owner, api) {
    const schemas = {};
    function schema(name) {
        if (Object.hasOwn(schemas, name)) return;
        schemas[name] = api?.schemas?.[name] || null;
        visit(schemas[name]);
    }
    function visit(value) {
        if (!value || typeof value !== 'object') return;
        if (value.schema) schema(value.schema);
        if (value.extends) value.extends.forEach(schema);
        Object.values(value).forEach(visit);
    }
    visit(member.params);
    visit(member.returns_contract);
    return hash([member.type, member.static || false, member.params, member.returns,
        member.returns_contract, member.native_binding || null, owner?.implements || [],
        owner?.native_binding || null, schemas,
        api?.binding_adapters?.[member.native_binding?.adapter] || null,
        ...(member.argument_validation ? [member.argument_validation] : []),
        ...(member.native_value_call ? [member.native_value_call] : []),
        ...(member.native_parameter_order ? [member.native_parameter_order] : []),
        ...(member.native_c_dispatch ? [member.native_c_dispatch] : []),
        ...(member.native_return_qualifiers ? [member.native_return_qualifiers] : [])]);
}
function qualifiedNativeType(type, qualifiers, api) {
    if (!qualifiers) return 'pdg::EmscriptenAnyNativeType';
    if (!['reference','pointer','rvalue-reference'].includes(qualifiers.indirection) || typeof qualifiers.const !== 'boolean')
        throw Error('Invalid native qualifiers: '+JSON.stringify(qualifiers));
    const klass = api.interface.find(owner => owner.type === 'class' && type === 'object '+owner.name);
    const record = api.schemas?.[type.replace(/^object /,'')];
    const native = klass?.native_binding?.browser?.type || klass?.native_binding?.type || record?.native_binding?.type;
    if (!native) throw Error('Missing native type for qualified '+type);
    return native + (qualifiers.const ? ' const' : '') + ({reference:'&',pointer:'*','rvalue-reference':'&&'}[qualifiers.indirection]);
}
function renderBinding(owner, member, api, {support = false} = {}) {
    const binding = member.native_binding || (generatesMember(owner, member) ? {} : null);
    if (!binding) throw Error('Missing native mapping: ' + owner.name + '.' + member.name);
    const browser = binding.browser || {};
    const adapter = binding.adapter && api.binding_adapters[binding.adapter];
    if (binding.adapter && !adapter) throw Error('Unknown adapter: ' + binding.adapter);
    // Adapter identity/signature is shared; each registration owns its policies.
    const native = {...adapter, ...binding};
    const nativeType = owner === api ? api.name : owner.native_binding?.browser?.type || owner.native_binding?.type;
    if (member.native_return_qualifiers?.const) {
        const resultClass = api.interface.find(c => member.returns === 'object '+c.name);
        if (resultClass?.native_binding?.ownership === 'retained')
            throw Error('Const retained result requires an explicit exposure policy: '+owner.name+'.'+member.name);
    }
    const valueCall = !native.adapter && !native.symbol && !native.signature && member.native_value_call;
    const symbol = native.symbol || (nativeType + '::' + (valueCall?.method || member.name));
    if (!native.symbol && !nativeType) throw Error('Missing native owner type: ' + owner.name);
    const name = bindingName(member, api);
    if (member.native_c_dispatch && !native.adapter && !native.symbol) {
        const dispatch = member.native_c_dispatch;
        const resultType = member.returns || 'undefined';
        const cppResult = {undefined:'void',this:'void',number:'double','number int':'double','number uint':'double',boolean:'bool',
            'object Point':'pdg::Point','object Offset':'pdg::Offset','object Vector':'pdg::Vector'}[resultType];
        if (!cppResult || !dispatch.cases?.length || Array.isArray(member.params[0]))
            throw Error('Unsupported C-function contract: '+owner.name+'.'+member.name);
        if (dispatch.cases.length > 1 && (dispatch.cases.some(c => !c.predicate) ||
            new Set(dispatch.cases.map(c => c.predicate)).size !== dispatch.cases.length))
            throw Error('C-function alternatives require distinct predicates: '+owner.name+'.'+member.name);
        const symbol = value => {
            if (!/^[A-Za-z_]\w*(?:::\w+)*$/.test(value)) throw Error('Invalid C-function symbol: '+value);
            return '&'+value;
        };
        const cases = dispatch.cases.map(c => {
            if (c.arguments.length !== member.params.length || c.arguments.some(arg =>
                !/^\w+$/.test(arg) && !/^cpv\(\w+\.x,\s*\w+\.y\)$/.test(arg)))
                throw Error('Unsupported C-function argument transformation: '+owner.name+'.'+member.name);
            return 'pdg::EmscriptenCCase<'+symbol(c.symbol)+', '+(c.predicate ? symbol(c.predicate) : 'nullptr')+'>';
        });
        if (dispatch.index && (member.params.length !== 1 || member.params[0].name !== dispatch.index.parameter))
            throw Error('Unsupported C-function index contract: '+owner.name+'.'+member.name);
        const count = dispatch.index ? symbol(dispatch.index.count) : 'nullptr';
        return guarded(browser.guard,'    .function('+JSON.stringify(name)+', &pdg::EmscriptenCDispatch<'+
            [cppResult,count,...cases].join(', ')+'>::call)');
    }
    const kind = member.type === 'constructor' ? 'constructor' : member.static ? 'class_function' : 'function';
    const global = owner === api;
    const defaults = owner.native_binding?.browser?.defaults || {};
    validateExceptionPolicy(defaults.exceptions);
    validateExceptionPolicy(browser.exceptions);
    const nativeMethod = !global && kind === 'function' && !binding.adapter && symbol.startsWith(nativeType + '::');
    const exceptions = browser.exceptions ?? (nativeMethod && !support ? defaults.exceptions : undefined);
    if (exceptions === 'javascript' && !nativeMethod)
        throw Error('Browser exception policy requires a native instance method: ' + owner.name + '.' + member.name);
    const borrowedReturn = borrowedType(member.returns_contract?.type || member.returns,api);
    const nativePointer = member.native_return_qualifiers?.indirection === 'pointer' || member.params?.flat().some(p => p.native_qualifiers?.indirection === 'pointer');
    const borrowedArgument = (Array.isArray(member.params?.[0]) ? member.params.flat() : member.params || []).some(p => borrowedType(p.type,api));
    const returnPolicy = native.return_policy ?? (nativeMethod &&
        (returnsReceiver(member) || borrowedReturn) ? 'reference' : undefined);
    const emit = (bindingName, signature, policy, selectedParams) => {
        if (policy && !policies.has(policy)) throw Error('Unknown return policy: ' + policy);
        let pointer = signature ? 'emscripten::select_overload<' + signature + '>(&' + symbol + ')' : '&' + symbol;
        if (nativeMethod || exceptions === 'javascript') {
            // Embind's select_overload is not constexpr. A member-pointer cast
            // permits overload selection as a checked-method template argument.
            if (signature) pointer = 'static_cast<pdg::EmscriptenMethodPointer<' + nativeType + ', ' + signature + '>>(&' + symbol + ')';
            else if (valueCall) pointer = 'pdg::EmscriptenValueMethod<'+nativeType+', pdg::'+valueCall.result+', pdg::'+valueCall.argument+'>::select(&'+symbol+')';
            if (!browser.registrations && (member.native_return_qualifiers || member.params?.flat().some(p => p.native_qualifiers))) {
                let params = selectedParams || member.params;
                if (Array.isArray(params[0]) && signature) {
                    // A wrapper can accept scalar coordinates as well as a value
                    // object while forwarding only the value-object C++ overload.
                    const argumentsText = signature.slice(signature.indexOf('(')+1,signature.lastIndexOf(')'));
                    const arity = argumentsText.trim() ? argumentsText.split(',').length : 0;
                    const exact = params.filter(variant => variant.length === arity);
                    const matching = exact.length ? exact : params.filter(variant => variant.length >= arity && variant.slice(arity).every(p => p.optional));
                    if (matching.length === 1) params = matching[0].slice(0,arity);
                }
                if (Array.isArray(params[0])) params = valueAlternatives({...member, params}, api) || params;
                if (Array.isArray(params[0])) {
                    const longest = params.reduce((a,b) => a.length >= b.length ? a : b);
                    if (params.some(v => v.some((p,i) => p.type !== longest[i].type ||
                        JSON.stringify(p.native_qualifiers) !== JSON.stringify(longest[i].native_qualifiers))))
                        throw Error('Incompatible qualified overloads: '+owner.name+'.'+member.name);
                    params = longest;
                }
                if (member.native_parameter_order) params = member.native_parameter_order.map(name => params.find(p => p.name === name));
                const qualified = [qualifiedNativeType(member.returns, member.native_return_qualifiers, api),
                    ...params.map(p => qualifiedNativeType(valueCall ? "object "+valueCall.argument : p.type,p.native_qualifiers,api))];
                pointer = 'pdg::EmscriptenSignatureCheck<'+pointer+', '+qualified.join(', ')+'>::pointer';
            }
            pointer = 'pdg::EmscriptenOwnMethod<'+nativeType+', '+pointer+'>::pointer';
            pointer = returnsReceiver(member) ? '&pdg::EmscriptenReceiverMethod<'+pointer+', '+(exceptions === 'javascript')+'>::call' :
                exceptions === 'javascript' ? '&pdg::EmscriptenCheckedMethod<' + pointer + '>::call' :
                'pdg::EmscriptenMethod<' + pointer + '>::binding';
        }
        const args = (member.type === 'constructor' ? '' : JSON.stringify(bindingName) + ', ') + pointer;
        return (global ? 'emscripten::' : '    .') + kind + '(' + args +
            (native.allow_raw_pointers || nativePointer || borrowedReturn || borrowedArgument ? ', emscripten::allow_raw_pointers()' : '') +
            (policy ? ', emscripten::return_value_policy::' + policy + '()' : '') + ')' + (global ? ';' : '');
    };
    let result;
    if (browser.registrations) {
        result = browser.registrations.map(item => emit(item.name, item.signature, item.return_policy ?? returnPolicy)).join('\n');
    } else if (binding.overloads) {
        result = binding.overloads.map(overload => emit(overload.binding_name, overload.signature, overload.return_policy ?? returnPolicy, member.params.find(params => params.map(p => p.name).join() === overload.parameters.join()))).join('\n');
    } else {
        result = emit(name, native.signature, returnPolicy);
    }
    return guarded(browser.guard, result);
}
function argumentTypes(api) {
    return Object.fromEntries(api.interface.filter(c => c.type === 'class' && c.native_binding?.browser?.argument)
        .map(c => {
            const rule = c.native_binding.browser.argument;
            if (!Array.isArray(rule.alternatives) || rule.alternatives.some(a =>
                !/^[A-Za-z_]\w*$/.test(a.type) || !/^[A-Za-z_]\w*$/.test(a.borrow)))
                throw Error('Invalid browser argument conversion: ' + c.name);
            return [c.name, {type:c.name, alternatives:rule.alternatives}];
        }));
}
function argumentConversions(member, api) {
    const types = argumentTypes(api);
    const variants = Array.isArray(member.params?.[0]) ? member.params : [member.params || []];
    const conversions = variants.map(params => params.flatMap((param, index) => {
        const rule = types[param.type?.replace(/^object /, '')];
        return rule ? [{index, rule, ...(param.optional ? {optional:true} : {})}] : [];
    }));
    // Native val adapters can handle several public shapes without JS overload
    // dispatch, provided all variants agree on the converted argument slots.
    if (conversions.some(value => JSON.stringify(value) !== JSON.stringify(conversions[0])))
        throw Error('Argument conversion requires an overload-specific policy: ' + member.name);
    return conversions[0];
}
function fixedArity(member) {
    const variants = Array.isArray(member.params?.[0]) ? member.params : [member.params || []];
    return variants.every(params => params.length === variants[0].length) ? variants[0].length : undefined;
}
function renderReturnWrappers(specs) {
    const indent = text => text.replace(/^/gm, '  ');
    return '[\n' + specs.map(spec => {
        let text = JSON.stringify(spec, null, 2);
        if (!spec.argumentConversions?.length || spec.argumentArity === undefined) return indent(text);
        // Emit a direct call from argument positions, not a per-method template
        // table. Correct-arity calls need no argument array even for borrowed views.
        const args = Array.from({length:spec.argumentArity}, (_, index) => 'arg' + index);
        const lines = [
            'function(native, bindings, policy, runtime) {',
            '    return function(' + args.join(', ') + ') {',
            '        if (arguments.length !== ' + args.length + ' || policy.validation)',
            '            return runtime.invokeMethod(bindings, native, policy, this, arguments);'
        ];
        spec.argumentConversions.forEach((conversion, index) => {
            const arg = args[conversion.index];
            lines.push('        ' + (conversion.optional ? 'if ('+arg+' !== undefined) ' : '') +
                arg + ' = runtime.adaptArgument(bindings, ' + arg + ', policy.argumentConversions[' + index + '].rule);');
        });
        lines.push('        if (policy.rememberReceiver) runtime.rememberObject(bindings, this);',
            '        const result = native.call(this' + (args.length ? ', ' + args.join(', ') : '') + ');',
            '        return policy.returnsThis ? this : runtime.convertReturn(bindings, result, policy.returnConversion);',
            '    };', '}');
        return indent(text.slice(0,-2) + ',\n  "create": ' + lines.join('\n') + '\n}');
    }).join(',\n') + '\n]';
}
// Public primitive alternatives can share one native value-object parameter.
// The signature declares accepted inputs; the value type declares construction.
function valueAlternatives(member, api) {
    if (!Array.isArray(member.params?.[0])) return null;
    const variants = member.params;
    if (!variants.every(params => params.length === variants[0].length)) return null;
    let converted = false;
    const params = variants[0].map((param, index) => {
        const choices = variants.map(args => args[index]);
        if (choices.every(p => p.type === param.type &&
            JSON.stringify(p.native_qualifiers) === JSON.stringify(param.native_qualifiers))) return param;
        const candidates = choices.filter(p => p.native_qualifiers).filter(p => {
            const value = api.interface.find(c => p.type === 'object '+c.name && c.native_binding?.browser?.kind === 'value_object');
            const inputs = value?.native_binding.browser.construct_from;
            return inputs && choices.every(choice => choice.type === p.type || inputs.includes(choice.type));
        });
        if (!candidates.length || candidates.some(p => p.type !== candidates[0].type ||
            JSON.stringify(p.native_qualifiers) !== JSON.stringify(candidates[0].native_qualifiers))) return null;
        converted = true;
        return candidates[0];
    });
    return converted && params.every(Boolean) ? params : null;
}
function wrapperSpec(owner, member, api) {
    const native = member.native_binding || {};
    const browser = native.browser || {};
    const valueParams = valueAlternatives(member, api);
    const flatParams = member.params?.flat() || [];
    const convertedParams = !!valueParams || (!Array.isArray(member.params?.[0]) && member.params?.some(param =>
        api.schemas?.[param.contract?.schema]?.native_binding?.browser?.argument));
    // Keep argument/overload adapters when they reshape native values. Simple
    // scalar/callback signatures can derive defaults and conversion from IDL.
    const scalarArguments = member.params?.length && member.params.every(p =>
        /^(number(?: int| uint)?|boolean|string|function)$/.test(p.type));
    const defaults = owner.native_binding?.browser?.defaults?.arguments === 'idl' &&
        (member.params?.some(p => p.optional) || scalarArguments);
    const automatic = !native.adapter && !native.signature && !native.overloads && !browser.registrations && (convertedParams || defaults) &&
        flatParams.every(param => /^(number(?: int| uint)?|boolean|string|function)$/.test(param.type) ||
            api.interface.some(type => 'object '+type.name === param.type && (type.native_binding?.type || type.native_binding?.browser?.type)));
    if (!browser.wrapper && !automatic) return null;
    const variants = Array.isArray(member.params[0]) ? member.params : [member.params];
    const schemas = {};
    function collect(contract) {
        if (!contract || typeof contract !== 'object') throw Error('Missing wrapper type');
        if (Object.hasOwn(contract, 'literal')) return;
        if (contract.one_of) { contract.one_of.forEach(collect); return; }
        if (contract.items || contract.values) { collect(contract.items || contract.values); return; }
        if (contract.builtin) {
            if (!['Uint8Array', 'object'].includes(contract.builtin)) throw Error('Unsupported wrapper builtin: ' + contract.builtin);
            return;
        }
        if (contract.schema && !schemas[contract.schema]) {
            const schema = api.schemas[contract.schema];
            if (!schema) throw Error('Unknown wrapper schema: ' + contract.schema);
            schemas[contract.schema] = schema;
            if (schema.kind === 'alias') collect(schema.value);
            else if (['record', 'context'].includes(schema.kind)) {
                for (const base of schema.extends || []) collect({schema:base});
                Object.values(schema.fields || {}).forEach(collect);
            } else if (!['callback', 'constructor'].includes(schema.kind)) {
                throw Error('Unsupported wrapper schema kind: ' + schema.kind);
            }
        }
        if (contract.schema) return;
        // Embind value objects accept structural values as well as class instances.
        // Derive that shape from the same field metadata as their registration.
        const valueClass = api.interface.find(c => contract.type === 'object '+c.name &&
            c.native_binding?.browser?.kind === 'value_object');
        if (valueClass) {
            const fields = Object.fromEntries(valueClass.native_binding.browser.fields.map(name => {
                const field = valueClass.interface.find(f => f.name === name);
                if (!field || !/^(number|boolean|string)$/.test(field.type))
                    throw Error('Missing scalar value field contract: '+valueClass.name+'.'+name);
                return [name,{type:field.type}];
            }));
            const constructFrom = valueClass.native_binding.browser.construct_from;
            if (constructFrom && (!Array.isArray(constructFrom) ||
                constructFrom.some(type => !['string','number','boolean'].includes(type))))
                throw Error('Invalid value constructor inputs: '+valueClass.name);
            schemas['native-value:'+valueClass.name] = {kind:'record',fields};
        }
        if (!/^(number(?: (?:int|uint))?|string|boolean|function|undefined|null|object \w+)$/.test(contract.type || ''))
            throw Error('Unsupported wrapper type: ' + contract.type);
    }
    variants.forEach(params => params.forEach(param => collect(param.contract || param)));
    const calls = variants.map(params => {
        let target = bindingName(member, api);
        if (native.overloads) {
            const names = params.map(param => param.name);
            const overload = native.overloads.find(item => JSON.stringify(item.parameters) === JSON.stringify(names));
            if (!overload) throw Error('Unmapped wrapper overload: ' + owner.name + '.' + member.name);
            target = overload.binding_name;
        }
        return {target, params:params.map((param,index) => valueParams && param.type !== valueParams[index].type
            ? {...param,value_constructor:valueParams[index].type.replace(/^object /,'')} : param)};
    });
    return {owner: owner.name, name: member.name, static: !!member.static, calls, schemas,
        ...(browser.guard ? {optional:true} : {}),
        ...(owner === api ? {root:true} : {}),
        returnsThis: returnsReceiver(member),
        ...(owner.native_binding?.browser?.remember_receiver && !member.static ? {rememberReceiver:true} : {}),
        constraints: browser.wrapper?.constraints || {},
        ...(argumentConversions(member, api).length ? {argumentConversions:argumentConversions(member, api)} : {}),
        ...(returnConversion(member, api) ? {returnConversion:returnConversion(member, api)} : {})};
}
function guarded(guard, code) {
    if (!guard) return code;
    if (Array.isArray(guard)) return guard.reduceRight((body, condition) => guarded(condition, body), code);
    if (!/^!?[A-Z_][A-Z_0-9]*$/.test(guard)) throw Error('Invalid build guard: ' + guard);
    return '#' + (guard[0] === '!' ? 'ifndef ' + guard.slice(1) : 'ifdef ' + guard) + '\n' + code + '\n#endif';
}
function customFragments(source) {
    const result = new Map();
    const rest = source.replace(/^\/\/ @pdg-custom (\w+)\n([\s\S]*?)^\/\/ @pdg-end-custom[ \t]*$/gm, (_, name, text) => {
        if (result.has(name)) throw Error('Duplicate custom fragment: ' + name);
        result.set(name, text.trim());
        return '';
    }).replace(/^\/\/[^\n]*$/gm, '').trim();
    if (rest) throw Error('Unscoped custom binding code');
    return result;
}
function generate(api, custom, manual) {
    const members = inventory(api);
    const emitted = new Set(), wrappers = [], returnWrappers = [], receiverWrappers = [], validationWrappers = [], events = [], registrations = new Set();
    const fragments = customFragments(custom);
    // A custom registration is already an explicit implementation. Do not
    // require a second per-member generate:false annotation for it. Both public
    // names and the shared private _name convention identify that method.
    const customMethods = new Map([...fragments].map(([owner, code]) => [owner,
        new Set([...code.matchAll(/\.(?:class_)?function\s*\(\s*"(\w+)"/g)].map(match => match[1]))]));
    for (const [owner, names] of customMethods)
        for (const name of names) registrations.add(owner+'.'+name);
    function generates(owner, member) {
        if (member.native_binding?.browser?.generate !== undefined) return generatesMember(owner, member);
        const methods = customMethods.get(owner.name);
        if (methods?.has(member.name) || methods?.has('_'+member.name)) return false;
        return generatesMember(owner, member);
    }
    const classes = api.interface.filter(item => item.type === 'class' && item.native_binding?.browser?.generate);
    const knownClasses = new Set(classes.map(item => item.name));
    for (const name of fragments.keys()) if (name !== api.name && !knownClasses.has(name)) throw Error('Unknown custom fragment owner: ' + name);
    const stats = {classes:0, valueObjects:0, constants:0, functions:0, methods:0, constructors:0, supportBindings:0};
    const nativeTypes = new Map(classes.map(owner => [owner.native_binding.browser.type || owner.native_binding.type, owner]));
    const ordered = [], visited = new Set(), visiting = new Set();
    function visit(owner) {
        if (visited.has(owner.name)) return;
        if (visiting.has(owner.name)) throw Error('Cyclic browser inheritance: ' + owner.name);
        visiting.add(owner.name);
        const binding = owner.native_binding, browser = binding.browser;
        validateExceptionPolicy(browser.defaults?.exceptions);
        const base = Object.hasOwn(browser, 'base') ? browser.base : binding.base;
        if (base && nativeTypes.has(base)) visit(nativeTypes.get(base));
        visiting.delete(owner.name); visited.add(owner.name); ordered.push(owner);
    }
    classes.forEach(visit);
    function emit(owner, member) {
        const event = eventSpec(owner,member,api);
        if (event) {
            events.push(event);
            emitted.add(owner.name+'.'+member.name);
            return '';
        }
        const binding = member.native_binding || {};
        const names = binding.browser?.registrations ? binding.browser.registrations.map(x => x.name) :
            binding.overloads ? binding.overloads.map(x => x.binding_name) : [bindingName(member, api)];
        for (const name of names) {
            const qualified = owner.name + '.' + name;
            if (registrations.has(qualified)) throw Error('Duplicate generated registration: ' + qualified);
            registrations.add(qualified);
        }
        emitted.add(owner.name + '.' + member.name);
        const spec = wrapperSpec(owner, member, api);
        if (spec) wrappers.push(spec);
        const conversion = returnConversion(member, api);
        const argumentsPolicy = argumentConversions(member, api);
        const receiver = returnsReceiver(member);
        const rememberReceiver = !!owner.native_binding?.browser?.remember_receiver && !member.static;
        if (member.argument_validation) validationWrappers.push({owner:owner.name, name:member.name,
            static:!!member.static, optional:!!binding.browser?.guard, ...member.argument_validation});
        if (receiver) receiverWrappers.push({owner:owner.name, name:member.name, static:!!member.static,
            optional:!!binding.browser?.guard});
        // Multiple native entries still need their existing argument dispatcher.
        // The final receiver wrapper wraps that public dispatcher, not an overload.
        if (!spec && (conversion || argumentsPolicy.length || ((receiver || rememberReceiver || member.argument_validation) && names.length === 1))) {
            if (names.length !== 1) throw Error('Return conversion with multiple native entries requires an argument wrapper: ' + owner.name + '.' + member.name);
            returnWrappers.push({owner:owner.name, name:member.name, target:names[0], static:!!member.static,
                ...(owner === api ? {root:true} : {}),
                ...(rememberReceiver ? {rememberReceiver:true} : {}),
                ...(argumentsPolicy.length ? {argumentConversions:argumentsPolicy, argumentArity:fixedArity(member)} : {}),
                optional:!!binding.browser?.guard, ...(receiver ? {returnsThis:true} : {returnConversion:conversion})});
        }
        if (member.type === 'constructor') stats.constructors++;
        else if (owner === api) stats.functions += names.length;
        else stats.methods += names.length;
        return renderBinding(owner, member, api);
    }
    const retained = api.interface.filter(owner => owner.type === 'class' && owner.native_binding?.ownership === 'retained');
    const borrowedIdentities = api.interface.filter(owner => owner.type === 'class' &&
        owner.native_binding?.browser?.pointer_policy === 'borrowed' && owner.native_binding.browser.remember_receiver);
    const lines = ['// Generated by tools/emscripten/generate.js. Edit source-owned native_binding annotations and pdg_em_custom.inc.',
        '#include <emscripten/bind.h>', '',
        'namespace pdg {\n' + retained.map(owner => guarded(owner.native_binding.browser?.guard,
            'template<> struct EmscriptenRetained<' + (owner.native_binding.browser?.type || owner.native_binding.type) + '> : std::true_type {};')).join('\n') + '\n'+
            borrowedIdentities.map(owner => 'template<> struct EmscriptenBorrowedIdentity<'+(owner.native_binding.browser.type || owner.native_binding.type)+'> : std::true_type {};').join('\n')+'\n}',
        'EMSCRIPTEN_BINDINGS(pdg) {', 'using namespace pdg;\nusing namespace emscripten;'];
    for (const member of api.interface) {
        if (!member.native_binding?.browser?.generate || member.type === 'class') continue;
        if (member.type === 'function') lines.push(emit(api, member));
        else if (member.readonly) {
            const binding = member.native_binding;
            let value = binding.symbol || api.name + '::' + member.name;
            if (binding.cast) {
                if (!['int', 'unsigned', 'double'].includes(binding.cast)) throw Error('Invalid constant cast');
                value = 'static_cast<' + binding.cast + '>(' + value + ')';
            }
            lines.push(guarded(binding.browser.guard, 'emscripten::constant(' + JSON.stringify(member.name) + ', ' + value + ');'));
            stats.constants++;
        } else throw Error('Unsupported browser export: ' + member.name);
    }
    if (fragments.has(api.name)) lines.push(fragments.get(api.name));
    // Value objects must be available to class methods returning them.
    for (const owner of [...ordered.filter(x => x.native_binding.browser.kind === 'value_object'),
        ...ordered.filter(x => x.native_binding.browser.kind !== 'value_object')]) {
        const binding = owner.native_binding, browser = binding.browser;
        const nativeType = browser.type || binding.type;
        if (!nativeType) throw Error('Missing browser native type: ' + owner.name);
        if (browser.kind && !['class', 'value_object'].includes(browser.kind)) throw Error('Unsupported browser registration kind: ' + browser.kind);
        const valueObject = browser.kind === 'value_object';
        const base = Object.hasOwn(browser, 'base') ? browser.base : binding.base;
        const body = ['emscripten::' + (valueObject ? 'value_object' : 'class_') + '<' + nativeType +
            (!valueObject && base ? ', emscripten::base<' + base + '>' : '') + '>(' + JSON.stringify(browser.binding_name || owner.name) + ')'];
        if (valueObject) {
            for (const field of browser.fields || []) {
                if (!/^\w+$/.test(field)) throw Error('Invalid value-object field');
                body.push('    .field(' + JSON.stringify(field) + ', &' + nativeType + '::' + field + ')');
            }
            stats.valueObjects++;
        } else {
            const retained = binding.ownership === 'retained';
            const customHandle = /\.smart_ptr(?:_constructor)?\b/.test(fragments.get(owner.name) || '');
            if (retained && !customHandle && !(browser.constructors || []).length)
                body.push('    .smart_ptr<std::shared_ptr<' + nativeType + '>>(' + JSON.stringify(owner.name+'Handle') + ')');
            for (const constructor of browser.constructors || []) {
                if (constructor.types && retained) body.push('    .smart_ptr_constructor(' + JSON.stringify(owner.name+'Handle') +
                    ', &pdg::EmscriptenRetainedConstructor<' + [nativeType,...constructor.types].join(', ') + '>::create)');
                else if (constructor.types) body.push('    .constructor<' + constructor.types.join(', ') + '>()');
                else if (constructor.factory) body.push('    .constructor(&' + constructor.factory +
                    (constructor.allow_raw_pointers ? ', emscripten::allow_raw_pointers()' : '') + ')');
                else throw Error('Missing native constructor mapping: ' + owner.name);
                if (constructor.public) {
                    const name = owner.name+'.'+owner.name;
                    const member = members.get(name)?.member;
                    if (!member || member.type !== 'constructor' || !constructor.types ||
                        member.params.some(Array.isArray) || member.params.length !== constructor.types.length)
                        throw Error('Public constructor mapping does not match inventory: '+name);
                    emitted.add(name);
                }
                stats.constructors++;
            }
            for (const member of owner.interface) {
                if (member.inherited_from || !generates(owner, member)) continue;
                body.push(emit(owner, member));
            }
            // Backend helpers and compatibility exports are not new public IDL
            // methods. Reuse the same native renderer without inventing signatures.
            for (const support of browser.support_bindings || []) {
                if (!/^\w+$/.test(support.name)) throw Error('Invalid support binding name');
                const qualified = owner.name + '.' + support.name;
                if (registrations.has(qualified)) throw Error('Duplicate generated registration: ' + qualified);
                registrations.add(qualified);
                body.push(renderBinding(owner, {name:support.name, type:'function', static:!!support.static,
                    native_binding:{...support, browser:support.browser || {}}}, api, {support:true}));
                stats.supportBindings++;
            }
            stats.classes++;
        }
        if (fragments.has(owner.name)) body.push(fragments.get(owner.name));
        body.push('    ;');
        lines.push(guarded(browser.guard, body.join('\n')));
    }
    lines.push('}', '');
    const entries = [];
    for (const [name, {owner, member}] of members) {
        if (generates(owner, member) && !emitted.has(name)) throw Error('Missing generated browser owner: ' + name);
        const legacy = manual.members[name];
        if (emitted.has(name)) {
            if (legacy) throw Error('Remove migrated member from manual inventory: ' + name);
            entries.push({name, status:member.native_binding?.adapter ? 'adapter' : 'generated', wrapper:!!eventSpec(owner, member, api) || !!member.native_binding?.browser?.wrapper || !!returnConversion(member, api) || returnsReceiver(member) || member.argument_validation || (argumentConversions(member, api).length ? true : undefined)});
        } else {
            if (!legacy) throw Error('Unclassified native API: ' + name + '. Declare a mapping or review its manual implementation.');
            if (legacy !== fingerprint(member, owner, api)) throw Error('Manual API contract changed; review its browser implementation: ' + name);
            entries.push({name, status:'manual-unverified'});
        }
    }
    for (const name of Object.keys(manual.members)) if (!members.has(name)) throw Error('Stale manual inventory member: ' + name);
    for (const source of manual.sources) if (!fs.existsSync(path.join(root, source))) throw Error('Missing manual implementation: ' + source);
    entries.sort((a,b) => a.name.localeCompare(b.name, 'en'));
    const counts = {};
    for (const entry of entries) counts[entry.status] = (counts[entry.status] || 0) + 1;
    return {
        cpp:lines.join('\n\n').trimEnd() + '\n',
        wrappers:'// Generated by tools/emscripten/generate.js. Do not edit.\n\'use strict\';\nconst runtime = require(\'pdg_em_runtime\');\nconst argumentTypes = ' + JSON.stringify(argumentTypes(api), null, 2) + ';\nexports.adaptArgument = function(bindings, type, value) {\n    return runtime.adaptArgument(bindings, value, argumentTypes[type]);\n};\nexports.installEvents = function(bindings) {\n    runtime.installEvents(bindings, ' + JSON.stringify(events, null, 2) + ');\n};\nexports.installReturns = function(bindings) {\n    runtime.installReturns(bindings, ' + renderReturnWrappers(returnWrappers) + ');\n};\nexports.install = function(bindings) {\n    runtime.install(bindings, ' + JSON.stringify(wrappers, null, 2) + ');\n    runtime.installReceivers(bindings, ' + JSON.stringify(receiverWrappers, null, 2) + ');\n    runtime.installValidation(bindings, ' + JSON.stringify(validationWrappers, null, 2) + ');\n};\n',
        coverage:JSON.stringify({version:1, scope:'Own native methods and constructors; inherited methods use their base implementation. Counts are generation coverage, not runtime availability.',
            manualStatus:manual.reason, manualSources:manual.sources, counts, registrations:stats, eventHelpers:events.length, wrappers:wrappers.length, returnWrappers:returnWrappers.length, receiverWrappers:receiverWrappers.length, validationWrappers:validationWrappers.length, members:entries}, null, 2) + '\n'
    };
}
function outputs() {
    const api = buildApi();
    const result = generate(api, fs.readFileSync(path.join(root, base + 'pdg_em_custom.inc'), 'utf8'),
        JSON.parse(fs.readFileSync(path.join(root, base + 'manual-bindings.json'), 'utf8')));
    return new Map([[base + 'pdg.embind', result.cpp], [base + 'pdg_em_generated.js', result.wrappers],
        [base + 'coverage.json', result.coverage]]);
}
function main() {
    const check = process.argv.includes('--check');
    if (process.argv.slice(2).some(arg => arg !== '--check')) throw Error('Usage: node tools/emscripten/generate.js [--check]');
    // Validate all inputs before writing any generated output.
    for (const [name, content] of outputs()) {
        const filename = path.join(root, name);
        if (fs.existsSync(filename) && fs.readFileSync(filename, 'utf8') === content) continue;
        if (check) throw Error('Stale Emscripten output: ' + name + '; run node tools/emscripten/generate.js');
        fs.writeFileSync(filename, content);
    }
    console.log(check ? 'Emscripten generated bindings are current.' : 'Generated Emscripten bindings, wrappers and coverage.');
}
if (require.main === module) main();
module.exports = {inventory, fingerprint, renderBinding, wrapperSpec, generate, outputs, customFragments};
