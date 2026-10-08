#!/usr/bin/env node
'use strict';

// Only the checked-in IDL supplies declaration contracts. Do not inspect runtime
// objects or repair incomplete signatures by looking at implementation code.
const fs = require('fs');
const path = require('path');
const crypto = require('crypto');
const root = path.resolve(__dirname, '../..');
const input = 'docs/javascript/pdg-js.json';
const compare = (a, b) => a < b ? -1 : a > b ? 1 : 0;

function generate(api) {
    const classes = new Map(api.interface.filter(x => x.type === 'class').map(x => [x.name, x]));
    const schemas = api.schemas || {};
    const invalidSchemas = new Map();
    const deferred = [];
    const nonConstructible = [];
    let emitted = 0;
    function gap(symbol, reason) { deferred.push({symbol, reason}); }
    function type(value, location) {
        const c = typeof value === 'string' ? {type: value} : value || {};
        if (c.variants && api.runtime_profile) {
            const variant = c.variants.find(v => v.runtimes.includes(api.runtime_profile.runtime));
            if (!variant) throw Error('No contract variant for runtime at ' + location);
            return type(variant, location);
        }
        let result;
        if (Object.hasOwn(c, 'literal')) result = JSON.stringify(c.literal);
        else if (c.builtin && ['object','unknown','Uint8Array','ArrayBuffer'].includes(c.builtin)) result = c.builtin;
        else if (c.items) result = '(' + type(c.items, location) + ')[]';
        else if (c.values) result = '{[key: string]: ' + type(c.values, location) + '}';
        else if (c.one_of) result = c.one_of.map(x => type(x, location)).join(' | ');
        else if (c.schema) {
            if (!schemas[c.schema]) throw Error('Unknown schema ' + c.schema);
            if (invalidSchemas.has(c.schema)) throw Error('Unresolved schema ' + c.schema);
            result = c.schema;
        } else {
            const t = c.type;
            if (t === 'this') result = 'this';
            else if (schemas[t]) result = type({schema:t}, location);
            else if (/^number(?:\s+\w+)?$/.test(t)) result = 'number';
            else if (/^string(?:\s+\w+)?$/.test(t)) result = 'string';
            else if (['boolean','void','undefined','null','never'].includes(t)) result = t;
            else if (t && t.endsWith('[]')) result = '(' + type(t.slice(0, -2), location) + ')[]';
            else if (t && t.startsWith('array ')) result = '(' + type(t.slice(6), location) + ')[]';
            else if (t && t.startsWith('object ') && classes.has(t.slice(7))) result = t.slice(7);
            else throw Error('Unresolved type ' + JSON.stringify(t) + ' at ' + location);
        }
        if (c.nullable) result += ' | null';
        return result;
    }
    function parameters(params, location) {
        if (!Array.isArray(params)) throw Error('Missing parameter signature at ' + location);
        return params.map((p, i) => {
            if (!/^[A-Za-z_$][\w$]*$/.test(p.name)) throw Error('Unresolved parameter name at ' + location);
            if (p.optional && params.slice(i + 1).some(q => !q.optional)) throw Error('Optional parameter before required parameter at ' + location);
            if (p.rest && (i !== params.length - 1 || p.optional)) throw Error('Invalid rest parameter at ' + location);
            return (p.rest ? '...' : '') + p.name + (p.optional ? '?' : '') + ': ' + type(p.contract || p, location + '.' + p.name);
        }).join(', ');
    }
    function comment(member, extra = []) {
        const lines = [member.brief || member.description, member.note, ...extra].filter(Boolean);
        if (member.returns_contract?.ownership) lines.push('Result ownership: ' + member.returns_contract.ownership + '.');
        if (member.lifetime) lines.push('Lifetime: ' + member.lifetime + '.');
        if (member.synchronous) lines.push('Invoked synchronously; promises are not accepted.');
        return lines.length ? '/**\n' + lines.join('\n').replace(/\*\//g, '* /').split('\n').map(x => ' * ' + x).join('\n') + '\n */\n' : '';
    }
    function member(m, owner, constructor = false) {
        const location = owner ? owner + '.' + m.name : m.name;
        const signatures = Array.isArray(m.params?.[0]) ? m.params : [m.params];
        const result = [];
        signatures.forEach((params, i) => {
            try {
                const byParameter = m.returns_contract?.by_parameter || {};
                const matched = params.map(p => byParameter[p.name]).filter(Boolean);
                if(matched.length>1) throw Error('Ambiguous overload return at ' + location);
                const ret = constructor ? owner : type(matched[0] || m.returns_contract || m.returns || 'void', location + ' return');
                let args = parameters(params, location);
                let generic = '';
                if (m.event_map) {
                    const map = m.event_map;
                    if (schemas[map.schema]?.kind !== 'event_map') throw Error('Invalid event map at ' + location);
                    if (!params.some(p => p.name === map.selector) || !params.some(p => p.name === map.callback)) throw Error('Invalid event selector at ' + location);
                    generic = map.fallback ? '<K extends number>' : '<K extends keyof ' + map.schema + '>';
                    const eventType = map.fallback ? 'K extends keyof ' + map.schema + ' ? ' + map.schema + '[K] : ' + type(map.fallback, location) : map.schema + '[K]';
                    args = params.map(p => p.name + (p.optional ? '?' : '') + ': ' +
                        (p.name === map.selector ? 'K' : p.name === map.callback ? '(event: ' + eventType + ') => ' + type(map.returns, location) : type(p.contract || p, location))).join(', ');
                }
                const name = constructor ? 'new' : (owner ? '' : 'function ') + m.name;
                result.push(comment(m, params.filter(p => p.default_value !== undefined).map(p => '@param ' + p.name + ' - Defaults to ' + p.default_value + '.')) + name + generic + '(' + args + '): ' + ret + ';');
                emitted++;
            } catch (e) { gap(location + (signatures.length > 1 ? '#' + (i + 1) : ''), e.message); }
        });
        return result.join('\n');
    }
    function property(m, owner) {
        try {
            const t = m.readonly && Object.hasOwn(m, 'value') ? JSON.stringify(m.value) : type(m.value_contract || m, (owner ? owner + '.' : '') + m.name);
            emitted++;
            return comment(m) + (owner ? (m.readonly ? 'readonly ' : '') : (m.readonly ? 'const ' : 'let ')) + m.name + ': ' + t + ';';
        } catch (e) { gap((owner ? owner + '.' : '') + m.name, e.message); return ''; }
    }
    // Never weaken a record by silently dropping an unresolved field. Propagate
    // incomplete records/callbacks to their consumers, including other schemas.
    let changed;
    do {
        changed = false;
        for (const [name, schema] of Object.entries(schemas)) {
            if (invalidSchemas.has(name)) continue;
            try {
                if (['callback','constructor'].includes(schema.kind)) {
                    parameters(schema.params, name);
                    type(schema.returns, name);
                } else {
                    if (schema.kind === 'alias') type(schema.value, name);
                    for (const base of schema.extends || []) type(base, name);
                    for (const method of Object.values(schema.methods || {})) { parameters(method.params, name); type(method.returns || 'void', name); }
                    for (const entry of Object.values(schema.entries || {})) type(entry, name);
                    for (const [key, field] of Object.entries(schema.fields || {})) type(field, name + '.' + key);
                }
            } catch (error) { invalidSchemas.set(name, error.message); changed = true; }
        }
    } while (changed);
    const declarations = [];
    for (const [name, schema] of Object.entries(schemas)) {
        if (invalidSchemas.has(name)) { gap(name, invalidSchemas.get(name)); continue; }
        if (['callback','constructor'].includes(schema.kind)) {
            try { declarations.push(comment(schema) + 'type ' + name + ' = ' + (schema.kind === 'constructor' ? 'new ' : '') + '(' + parameters(schema.params, name) + ') => ' + type(schema.returns, name) + ';'); }
            catch (e) { gap(name, e.message); }
        } else if (schema.kind === 'alias') {
            declarations.push(comment(schema) + 'type ' + name + ' = ' + type(schema.value, name) + ';');
        } else if (schema.kind === 'external') {
            if (!schema.module || !/^[A-Za-z_$][\w$]*$/.test(schema.export)) throw Error('Invalid external schema ' + name);
            declarations.push(comment(schema) + 'type ' + name + ' = import(' + JSON.stringify(schema.module) + ').' + schema.export + ';');
        } else {
            const fields = [];
            if (schema.identity) fields.push('readonly [recordIdentity]: ' + JSON.stringify(schema.identity) + ';');
            if (schema.additional_properties) fields.push('[key: string]: ' + type(schema.additional_properties, name) + ';');
            for (const [constant, entry] of Object.entries(schema.entries || {})) {
                const exported = api.interface.find(x => x.name === constant && x.readonly && typeof x.value === 'number');
                if (!exported) throw Error('Missing numeric event constant: ' + constant);
                fields.push('[' + constant + ']: ' + type(entry, name) + ';');
            }
            for (const [key, field] of Object.entries(schema.fields || {})) {
                try { fields.push(comment(field) + (field.readonly ? 'readonly ' : '') + key + (field.optional ? '?' : '') + ': ' + type(field, name + '.' + key) + ';'); }
                catch (e) { gap(name + '.' + key, e.message); }
            }
            for (const [key, method] of Object.entries(schema.methods || {})) {
                fields.push(member({...method, name: key, returns_contract: method.returns}, name));
            }
            declarations.push(comment(schema) + 'interface ' + name + ((schema.extends || []).length ? ' extends ' + schema.extends.map(base => type(base, name)).join(', ') : '') + ' {\n' + indent(fields.filter(Boolean).join('\n')) + '\n}');
        }
    }
    for (const m of api.interface) {
        if (m.type !== 'class') {
            const text = m.type === 'function' ? member(m) : property(m);
            if (text) declarations.push(text);
            continue;
        }
        // Flatten the IDL's inherited inventory: JavaScript supports mixins and
        // overrides which cannot be represented as multiple TS class bases.
        const fields = [], values = [];
        // A factory-only class still exports a runtime constructor object for
        // prototype access and instanceof; omit only its public new signature.
        values.push('readonly prototype: ' + m.name + ';');
        values.push('[Symbol.hasInstance](value: unknown): value is ' + m.name + ';');
        if (m.native) {
            const ancestors = new Set();
            function collect(klass) {
                if (ancestors.has(klass.name)) return;
                ancestors.add(klass.name);
                for (const base of klass.implements || []) {
                    if (!classes.has(base)) throw Error('Unknown base ' + base);
                    collect(classes.get(base));
                }
            }
            collect(m);
            fields.push('readonly [nativeIdentity]: {' + [...ancestors].sort(compare).map(name => JSON.stringify(name) + ': true').join('; ') + '};');
        }
        for (const item of m.interface) {
            const text = item.type === 'constructor' ? member(item, m.name, true)
                : item.type === 'function' ? member(item, m.name) : property(item, m.name);
            if (text) (item.static || item.type === 'constructor' ? values : fields).push(text);
        }
        if (!m.interface.some(x => x.type === 'constructor')) {
            if (['factory','singleton','borrowed','abstract'].includes(m.construction?.kind))
                nonConstructible.push({symbol:m.name, ...m.construction});
            else gap(m.name + '.constructor', 'No construction policy or constructor signature in IDL');
        }
        declarations.push(comment(m) + 'interface ' + m.name + ' {\n' + indent(fields.join('\n')) + '\n}');
        if (values.length) declarations.push('const ' + m.name + ': {\n' + indent(values.join('\n')) + '\n};');
    }
    if (!api.runtime_profile) gap('$profiles', 'IDL has no captured runtime profile. Generate IDL using the intended runtime before publishing a platform-specific declaration package.');
    if (!Object.values(schemas).some(schema => schema.kind === 'event_map')) gap('$events', 'IDL does not map event IDs to payload and callback signatures.');
    const typePackages = [...new Set(Object.values(schemas).map(s => s.types_package).filter(Boolean))].sort(compare);
    const text = typePackages.map(name => '/// <reference types=' + JSON.stringify(name) + ' />\n').join('') +
        '// Generated by tools/typescript/generate.js from ' + input + '. Do not edit.\n' +
        '// PDG ' + api.vers + '; inventory runtime: ' + (api.runtime_profile?.runtime || 'unspecified') + '. See coverage.json.\n' +
        'declare const nativeIdentity: unique symbol;\ndeclare const recordIdentity: unique symbol;\ndeclare namespace pdg {\n' + indent(declarations.join('\n\n')) + '\n}\nexport = pdg;\n';
    return {text, report: {version: api.vers, runtimeProfile:api.runtime_profile, typePackages, emittedSignaturesAndProperties: emitted, nonConstructible, deferred: deferred.sort((a,b) => compare(a.symbol,b.symbol) || compare(a.reason,b.reason))}};
}
function indent(text) { return text.split('\n').map(x => x ? '    ' + x : '').join('\n'); }
function run(check = false) {
    const source = fs.readFileSync(path.join(root, input));
    const {text, report} = generate(JSON.parse(source));
    report.input = input;
    report.sha256 = crypto.createHash('sha256').update(source).digest('hex');
    const files = {'types/index.d.ts':text, 'types/coverage.json':JSON.stringify(report, null, 2) + '\n'};
    for (const [file, content] of Object.entries(files)) {
        const target = path.join(root, file);
        if (check) { if (!fs.existsSync(target) || fs.readFileSync(target,'utf8') !== content) throw Error('Stale generated file: ' + file); }
        else { fs.mkdirSync(path.dirname(target),{recursive:true}); fs.writeFileSync(target,content); }
    }
    console.log((check ? 'Checked' : 'Generated') + ' TypeScript declarations: ' + report.emittedSignaturesAndProperties + ' signatures/properties; ' + report.deferred.length + ' deferred entries.');
}
module.exports = {generate, run};
if (require.main === module) run(process.argv.includes('--check'));
