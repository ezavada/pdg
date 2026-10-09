'use strict';

// Metadata enrichment and rendering only. This module never calls API methods,
// constructors, or property getters to discover a contract.
const contracts = require('./interface-metadata-source').readContracts();
const clone = value => JSON.parse(JSON.stringify(value));

function validateSchemas(value, schemas) {
    if (!value || typeof value !== 'object') return;
    if (value.schema && !Object.prototype.hasOwnProperty.call(schemas, value.schema))
        throw Error('Unknown API schema: ' + value.schema);
    Object.values(value).forEach(child => validateSchemas(child, schemas));
}

function enrich(api, source = contracts) {
    validateSchemas(source, source.schemas);
    const schemaKinds = new Set(['record', 'context', 'callback', 'constructor', 'alias', 'external', 'event_map']);
    function validateBases(name, seen = new Set()) {
        if (seen.has(name)) throw Error('Cyclic API schema inheritance: ' + name);
        const schema = source.schemas[name];
        if (!schemaKinds.has(schema.kind)) throw Error('Unknown API schema kind: ' + name);
        for (const base of schema.extends || []) {
            if (base.startsWith('object ')) {
                if (!api.interface.some(item => item.type === 'class' && item.name === base.slice(7)))
                    throw Error('Unknown API class base: ' + base);
            } else {
                if (!source.schemas[base] || !['record','context'].includes(source.schemas[base].kind))
                    throw Error('Invalid API schema base: ' + base);
                validateBases(base, new Set(seen).add(name));
            }
        }
    }
    Object.keys(source.schemas).forEach(name => validateBases(name));
    api.contract_version = source.version;
    api.schemas = clone(source.schemas);
    api.contract_coverage = {scope: 'partial; signature schemas and explicitly annotated contracts are authoritative', applied: [], unavailable: []};
    const classes = new Map(api.interface.filter(item => item.type === 'class').map(item => [item.name, item]));
    // Named record/callback types in signatures refer to binding-owned schemas.
    // Preserve named object types in IDL; schemas add field/nullability contracts.
    const builtins = new Set(['Array', 'Buffer', 'Object', 'Uint8Array']);
    function resolveType(type, qualified) {
        const match = /^(object|function) (\w+)(\[\])?$/.exec(type || '');
        if (!match) return null;
        const [, category, name, array] = match;
        if (classes.has(name) || builtins.has(name)) {
            if (category !== 'object') throw Error('Class used as callback type: ' + qualified + ': ' + name);
            return null;
        }
        const schema = source.schemas[name];
        if (!schema) throw Error('Unknown signature type: ' + qualified + ': ' + name);
        if (category === 'function' ? !['callback','constructor'].includes(schema.kind) : !['record', 'context','alias','external'].includes(schema.kind))
            throw Error('Incompatible signature schema: ' + qualified + ': ' + name);
        return array ? {type:'array',items:{schema:name}} : {type:category, schema:name};
    }
    function resolveMembers(items, owner) {
        for (const member of items) {
            const qualified = owner + '.' + member.name;
            if (member.interface) resolveMembers(member.interface, member.name);
            if (!member.params) continue;
            let resolved = false;
            const variants = Array.isArray(member.params[0]) ? member.params : [member.params];
            for (const params of variants) for (const param of params) {
                const contract = resolveType(param.type, qualified + '.' + param.name);
                if (!contract) continue;
                if (param.contract && param.contract.schema && param.contract.schema !== contract.schema)
                    throw Error('Conflicting signature schema: ' + qualified + '.' + param.name);
                if (!param.type.startsWith('object ')) param.type = contract.type;
                param.contract = {...param.contract, ...contract};
                resolved = true;
            }
            const result = resolveType(member.returns, qualified + ' return');
            if (result) {
                if (member.returns_contract && member.returns_contract.schema && member.returns_contract.schema !== result.schema)
                    throw Error('Conflicting signature schema: ' + qualified + ' return');
                if (!member.returns.startsWith('object ')) member.returns = result.type;
                member.returns_contract = {...member.returns_contract, ...result};
                resolved = true;
            }
            if (resolved) api.contract_coverage.applied.push(qualified);
        }
    }
    resolveMembers(api.interface, api.name || 'pdg');
    for (const [qualified, rule] of Object.entries(source.members)) {
        const [owner, name] = qualified.split('.');
        const klass = owner === api.name ? api : classes.get(owner);
        if (!klass && rule.optional_class) {
            api.contract_coverage.unavailable.push(qualified);
            continue;
        }
        const member = klass && klass.interface.find(item => item.name === name);
        if (!member) throw Error('Stale API contract: ' + qualified);
        if (rule.returns) {
            if (member.returns_contract && member.returns_contract.schema &&
                ((rule.returns.schema && rule.returns.schema !== member.returns_contract.schema) ||
                 (rule.returns.type && rule.returns.type !== member.returns_contract.type)))
                throw Error('Conflicting signature schema: ' + qualified + ' return');
            member.returns_contract = {...member.returns_contract, ...clone(rule.returns)};
        }
        if (rule.property) member.value_contract = clone(rule.property);
        if (rule.legacy_type) member.type = rule.legacy_type;
        if (rule.params) {
            const variants = member.params.length && Array.isArray(member.params[0]) ? member.params : [member.params];
            for (const [parameter, contract] of Object.entries(rule.params)) {
                let found = false;
                for (const params of variants) {
                    const param = params.find(item => item.name === parameter);
                    if (param && (!contract.when_type || param.type === contract.when_type ||
                        (param.contract && param.contract.type === contract.when_type &&
                         param.type === 'object ' + param.contract.schema))) {
                        if (param.contract && param.contract.schema &&
                            ((contract.schema && contract.schema !== param.contract.schema) ||
                             (contract.type && contract.type !== param.contract.type)))
                            throw Error('Conflicting signature schema: ' + qualified + '.' + parameter);
                        param.contract = {...param.contract, ...clone(contract)};
                        found = true;
                    }
                }
                if (!found) throw Error('Stale API parameter contract: ' + qualified + '.' + parameter);
            }
        }
        if (!api.contract_coverage.applied.includes(qualified)) api.contract_coverage.applied.push(qualified);
    }
    // Enrich inherited copies using the same contract as their declaration.
    // Do not apply a base contract to a local override with a different signature.
    for (const klass of classes.values()) for (const member of klass.interface) {
        if (!member.inherited_from) continue;
        const base = classes.get(member.inherited_from)?.interface.find(item => item.name === member.name);
        if (!base) continue;
        for (const key of ['returns_contract','value_contract','event_map']) if (base[key]) member[key] = clone(base[key]);
        const variants = params => Array.isArray(params?.[0]) ? params : [params || []];
        const inherited = variants(base.params);
        variants(member.params).forEach((params,index) => params.forEach(param => {
            const original = inherited[index]?.find(p => p.name === param.name);
            if (original?.contract) param.contract = clone(original.contract);
        }));
    }
    // Receiver identity is explicit in the signature. Same-class results can
    // still be new objects and must never be inferred as chaining returns.
    for (const klass of classes.values()) {
        for (const member of klass.interface) {
            if (member.returns !== 'this') continue;
            if (member.returns_contract && member.returns_contract.type !== 'this')
                throw Error('Conflicting receiver return contract: '+klass.name+'.'+member.name);
            member.returns_contract = {type:'this'};
        }
    }
    return api;
}

// Canonical presentation order is independent of source or previous output order.
// Parameters, overloads, base lists, and other positional arrays retain their order.
function memberSection(member, ownerType) {
    if (member.type === 'class') return 4;
    if (member.type === 'constructor') return 2;
    if (member.type === 'function') return 3;
    if (member.value !== undefined || (member.readonly && (ownerType === 'module' || member.static))) return 0;
    return 1;
}
function alphabeticalOrder(value, field, ownerType) {
    const compare = (a, b) => {
        const left = a.toLowerCase(), right = b.toLowerCase();
        return left < right ? -1 : left > right ? 1 : a < b ? -1 : a > b ? 1 : 0;
    };
    if (Array.isArray(value)) {
        const items = value.map(item => alphabeticalOrder(item));
        if (field === 'interface') items.sort((a, b) =>
            memberSection(a, ownerType) - memberSection(b, ownerType) || compare(a.name, b.name));
        else if (field === 'applied' || field === 'unavailable') items.sort(compare);
        return items;
    }
    if (!value || typeof value !== 'object') return value;
    return Object.fromEntries(Object.keys(value).sort(compare)
        .map(key => [key, alphabeticalOrder(value[key], key, value.type || (key === 'interface' ? 'module' : undefined))]));
}

function inventoryModule(exports, name) {
    function entriesOf(object, ancestors = new Set()) {
        const seen = new Set(ancestors);
        seen.add(object);
        return Object.entries(Object.getOwnPropertyDescriptors(object))
            .filter(([key]) => !key.startsWith('_'))
            .sort(([a], [b]) => a.localeCompare(b))
            .map(([exportName, descriptor]) => {
                if (!('value' in descriptor))
                    return {name: exportName, type: 'accessor', signature_status: 'unresolved'};
                const value = descriptor.value;
                if (typeof value === 'function' && value.prototype) {
                    const base = Object.getPrototypeOf(value.prototype);
                    const baseConstructor = base && Object.getOwnPropertyDescriptor(base, 'constructor');
                    const members = [];
                    for (const [staticMember, target] of [[false, value.prototype], [true, value]]) {
                        for (const [memberName, member] of Object.entries(Object.getOwnPropertyDescriptors(target))) {
                            if (memberName.startsWith('_') || ['constructor', 'prototype', 'name', 'length', 'caller', 'arguments'].includes(memberName)) continue;
                            members.push({name: memberName, type: typeof member.value === 'function' ? 'function' :
                                ('get' in member || 'set' in member) ? 'accessor' : typeof member.value,
                                static: staticMember, signature_status: 'unresolved'});
                        }
                    }
                    return {name: exportName, type: 'class', constructor_name: value.name,
                        implements: base && base !== Object.prototype && baseConstructor && typeof baseConstructor.value === 'function' ? [baseConstructor.value.name] : [],
                        signature_status: 'unresolved', interface: members.sort((a, b) => a.name.localeCompare(b.name))};
                }
                if (value !== null && typeof value === 'object') {
                    return {name: exportName, type: 'object', ...(seen.has(value) ? {cyclic_reference: true} :
                        {interface: entriesOf(value, seen)})};
                }
                return {name: exportName, type: typeof value,
                    ...(['string', 'number', 'boolean'].includes(typeof value) || value === null ? {value} :
                        {signature_status: 'unresolved'})};
            });
    }
    const entries = entriesOf(exports);
    return {name, type: 'module', source: 'src/js/mvc-app/index.js', stability: 'Evolving',
        coverage: 'Exports and own prototype/static members only. Unresolved signatures and instance fields require explicit contracts.',
        interface: entries};
}

function typeText(contract) {
    let text = contract.items ? 'Array of ' + typeText(contract.items) :
        contract.values ? 'Dictionary of ' + typeText(contract.values) :
        contract.builtin ? '\\c ' + contract.builtin :
        contract.one_of ? contract.one_of.map(typeText).join(' or ') :
        contract.variants ? contract.variants.map(variant => variant.runtimes.join('/') + ': ' + typeText(variant)).join('; ') :
        contract.schema ? '\\ref pdg::' + contract.schema :
        Object.prototype.hasOwnProperty.call(contract, 'literal') ? '\\c ' + JSON.stringify(contract.literal) :
        contract.type === 'this' ? 'the receiver (preserving its concrete class) for call chaining' : '\\c ' + contract.type.replace(/^object /, '');
    if (contract.nullable) text += ' or \\c null';
    return text;
}

function memberDocumentation(member, schemas = contracts.schemas) {
    const lines = [];
    if (member.value_contract) lines.push('\\par JavaScript value', typeText(member.value_contract) + '.');
    const variants = member.params && member.params.length && Array.isArray(member.params[0]) ? member.params : [member.params || []];
    const seen = new Set();
    for (const params of variants) for (const param of params) {
        if (param.contract && !seen.has(param.name)) {
            seen.add(param.name);
            const details = [];
            if (!parameterDocumentationType(param, schemas)) details.push(typeText(param.contract) + '.');
            if (param.contract.condition) details.push(param.contract.condition);
            // Authored .dox files own the @param descriptions. Supplemental
            // notes must not create duplicate parameter sections when merged.
            if (details.length) lines.push('\\note Parameter \\c ' + param.name + ': ' + details.join(' '));
        }
    }
    return lines.length ? '/**\n' + lines.join('\n') + '\n*/\n' : '';
}

// Resolve built-in aliases for visible Doxygen signatures. Records and other
// structured contracts keep their existing signature and linked shape docs.
function builtinDocumentationType(contract, schemas, seen = new Set()) {
    if (!contract) return null;
    let result;
    if (contract.one_of) {
        const choices = contract.one_of.map(choice => builtinDocumentationType(choice, schemas, seen));
        if (choices.some(choice => choice === null)) return null;
        // Doxygen's C++ parser drops a literal | in pseudo-header return types.
        result = choices.join(' or ');
    } else if (contract.builtin) {
        result = contract.builtin;
    } else if (Object.prototype.hasOwnProperty.call(contract, 'literal')) {
        if (typeof contract.literal === 'string') return null;
        result = JSON.stringify(contract.literal);
    } else if (contract.schema) {
        if (seen.has(contract.schema)) return null;
        const schema = schemas[contract.schema];
        if (!schema || schema.kind !== 'alias') return null;
        result = builtinDocumentationType(schema.value, schemas, new Set(seen).add(contract.schema));
    } else {
        return null;
    }
    return result !== null && contract.nullable ? result + ' or null' : result;
}

// Preserve concrete record, external and union-alias names in object parameters.
// Names refer to the documentation-only types in the surrounding pdg namespace.
function parameterDocumentationType(param, schemas) {
    // A null default already communicates null acceptance in the displayed
    // signature. Keep the underlying contract nullable for TypeScript and prose.
    const contract = param.contract && param.optional &&
        (param.default_value === 'null' || param.default_value === null)
        ? {...param.contract, nullable: false} : param.contract;
    const builtin = builtinDocumentationType(contract, schemas);
    if (builtin) return builtin;
    if (contract && schemas[contract.schema] &&
        (param.type === 'object' || param.type === 'object ' + contract.schema)) {
        return contract.schema + (contract.nullable ? ' or null' : '');
    }
    return null;
}

// Keep return notes next to the generated declaration, without a Doxygen block.
function memberResultComment(member) {
    const contract = member.returns_contract;
    if (!contract) return '';
    if (contract.type === 'this') return ' // returns self for chaining';
    const alternatives = new Set();
    const seen = new Set();
    function collect(value) {
        if (value.nullable) alternatives.add('null');
        if (Object.prototype.hasOwnProperty.call(value, 'literal')) alternatives.add(JSON.stringify(value.literal));
        if (value.type === 'undefined' || value.type === 'null') alternatives.add(value.type);
        if (value.one_of) value.one_of.forEach(collect);
        const schema = contracts.schemas[value.schema];
        if (schema && schema.kind === 'alias' && !seen.has(value.schema)) {
            seen.add(value.schema);
            collect(schema.value);
        }
    }
    collect(contract);
    if (alternatives.size) return ' // can return ' + [...alternatives].join(' or ');
    if (contract.copy) return ' // returns a new copy';
    if (contract.items && member.returns === 'object ' + contract.items.schema + '[]') return '';
    if (builtinDocumentationType(contract, contracts.schemas)) return '';
    const visible = parameterDocumentationType({type:member.returns, contract}, contracts.schemas)
        || (member.returns || '').replace(/^object /, '');
    if (contract.schema === visible || (contract.type || '').replace(/^object /, '') === visible) return '';
    const result = typeText(contract).replace(/\\c /g, '').replace(/\\ref pdg::/g, '');
    return ' // returns ' + result;
}

function schemaDocumentation(schemas) {
    let out = '\n';
    for (const [name, schema] of Object.entries(schemas)) {
        const lines = ['\\brief ' + (schema.description || name),
            '\\note Documentation-only JavaScript shape, not a runtime constructor.'];
        if (['record', 'context', 'alias', 'event_map'].includes(schema.kind))
            lines.push('\\ingroup StructuredDataTypes');
        if (schema.lifetime) lines.push('Lifetime: ' + schema.lifetime + '.');
        if (schema.extends) lines.push('Extends: ' + schema.extends.map(base =>
            typeText(base.startsWith('object ') ? {type:base} : {schema:base})).join(', ') + '.');
        if (schema.kind === 'alias') lines.push('\\par Type', typeText(schema.value) + '.');
        if (schema.kind === 'external') lines.push('\\par External type', '\\c ' + schema.export + ' from \\c ' + schema.module + '.');
        if (schema.kind === 'event_map') {
            lines.push('\\par Event payloads', '| Event constant | Payload |', '| --- | --- |');
            for (const [event, payload] of Object.entries(schema.entries)) lines.push('| ' + event + ' | ' + typeText(payload) + ' |');
        }
        if (['callback','constructor'].includes(schema.kind)) {
            lines.push('\\par Call signature', '\\c ' + (schema.kind === 'constructor' ? 'new ' : '') + 'callback(' + schema.params.map(p => p.name).join(',') + ')',
                '\\par Result', typeText(schema.returns) + '.');
            if (schema.synchronous) lines.push('\\note Must return synchronously.');
            for (const param of schema.params) lines.push('Parameter ' + param.name + ': ' + typeText(param) + '.');
        }
        if (schema.methods) {
            lines.push('\\par Methods', '| Method | Result | Behavior |', '| --- | --- | --- |');
            for (const [method, info] of Object.entries(schema.methods)) {
                const params = info.params.map(p => p.name + (p.optional ? ' = ' + p.default_value : '')).join(', ');
                lines.push('| ' + method + '(' + params + ') | ' + typeText(info.returns) + ' | ' + (info.description || '') + ' |');
            }
        }
        if (schema.fields) {
            lines.push('\\htmlonly[block]', '<div class="shared-api-options">', '\\endhtmlonly',
                '\\par Fields', '| Field | Type | Required/default | Meaning |', '| --- | --- | --- | --- |');
            for (const [field, info] of Object.entries(schema.fields)) {
                const requirement = info.optional ? (info.default_value === undefined ? 'Optional' : info.default_value) : 'Required';
                lines.push('| ' + field + ' | ' + typeText(info) + ' | ' + requirement + ' | ' + (info.description || '') + ' |');
            }
            lines.push('\\htmlonly[block]', '</div>', '\\endhtmlonly');
        }
        out += '/**\n' + lines.join('\n') + '\n*/\nstruct ' + name + ' {\n';
        for (const [field, info] of Object.entries(schema.fields || {})) {
            out += '/** \\brief ' + (info.description || field) + '\nType: ' + typeText(info) + '.\n' +
                (info.optional ? 'Optional.' : 'Required.') +
                (info.default_value !== undefined ? ' Default: \\c ' + info.default_value + '.' : '') + '\n*/\n';
            const type = info.one_of || info.items || info.values ? 'object' : info.schema || (info.type || 'object').replace(/^object /, '').replace('number int', 'int');
            out += type + ' ' + field + ';\n';
        }
        out += '};\n';
    }
    return out;
}

function moduleDocumentation(module) {
    const lines = ['/**', '\\page javascript_mvc_inventory JavaScript MVC module inventory',
        'These exports belong to the separate MVC module, not to the pdg root object.',
        'See \\ref javascript_mvc_guide for imports, lifecycle, and a View example.',
        '\\note API stability: ' + module.stability + '. ' + module.coverage,
        '| Export | Kind | Base classes |', '| --- | --- | --- |'];
    const entries = [];
    function collect(items, prefix = '') {
        for (const entry of items) {
            const name = prefix + entry.name;
            entries.push({...entry, name});
            if (entry.type === 'object' && entry.interface) collect(entry.interface, name + '.');
        }
    }
    collect(module.interface);
    for (const entry of entries) lines.push('| ' + entry.name + ' | ' + entry.type + ' | ' + (entry.implements || []).join(', ') + ' |');
    for (const entry of entries.filter(e => e.type === 'class')) {
        lines.push('\\section mvc_export_' + entry.name.replace(/\./g, '_') + ' ' + entry.name,
            'Constructor signatures and instance properties are not inferred by constructing objects.');
        for (const member of entry.interface) lines.push('- ' + (member.static ? 'Static ' : '') + '\\c ' + member.name + ' (' + member.type + ').');
    }
    return lines.join('\n') + '\n*/\n';
}

module.exports = {memberSection, alphabeticalOrder, enrich, inventoryModule, memberDocumentation, memberResultComment, builtinDocumentationType, parameterDocumentationType, schemaDocumentation, moduleDocumentation};
