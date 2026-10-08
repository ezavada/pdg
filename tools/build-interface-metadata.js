'use strict';

// Compile binding-owned declarations into a module usable by every JS backend.
// No engine objects are constructed or called during metadata generation.
const fs = require('fs');
const path = require('path');
const {enrich, alphabeticalOrder} = require('./api-contracts');
const source = require('./interface-metadata-source');
const root = path.resolve(__dirname, '..');
const outputPath = path.join(root, 'src/js/interface_metadata_data.js');

function validate(api, adapters) {
    if (api.metadata_version !== 1) throw Error('Unsupported interface metadata version');
    const policies = ['reference', 'copy', 'take_ownership', 'reference_internal'];
    function validateQualifiers(type, qualifiers, qualified) {
        if (!qualifiers) return;
        if (!/^object \w+$/.test(type || '') || typeof qualifiers.const !== 'boolean' ||
            !['reference','pointer','rvalue-reference'].includes(qualifiers.indirection) ||
            Object.keys(qualifiers).some(key => !['indirection','const'].includes(key)))
            throw Error('Invalid native qualifiers: '+qualified);
    }
    function entries(items, owner) {
        const names = new Set();
        for (const member of items) {
            const qualified = owner + '.' + member.name;
            if (!member.name || names.has(member.name)) throw Error('Duplicate metadata: ' + qualified);
            names.add(member.name);
            validateQualifiers(member.returns,member.native_return_qualifiers,qualified);
            const binding = member.native_binding;
            if (binding) {
                if (binding.adapter && adapters && !Object.prototype.hasOwnProperty.call(adapters, binding.adapter))
                    throw Error('Unknown native adapter: ' + binding.adapter);
                if (binding.type && !/^pdg::\w+$/.test(binding.type)) throw Error('Invalid native class: ' + qualified);
                if (binding.base && !/^pdg::\w+$/.test(binding.base)) throw Error('Invalid native base: ' + qualified);
                if (binding.ownership && !['owned', 'borrowed', 'retained', 'value'].includes(binding.ownership))
                    throw Error('Invalid native ownership: ' + qualified);
                if (binding.return_policy && !policies.includes(binding.return_policy))
                    throw Error('Invalid native return policy: ' + qualified);
            }
            if (member.type === 'class') entries(member.interface, qualified);
            if (member.type === 'function' || member.type === 'constructor') {
                if (!Array.isArray(member.params)) throw Error('Missing parameters: ' + qualified);
                const variants = Array.isArray(member.params[0]) ? member.params : [member.params];
                if (member.native_parameter_order) {
                    const order = member.native_parameter_order;
                    if (variants.length !== 1 || !Array.isArray(order) || order.length !== member.params.length ||
                        new Set(order).size !== order.length || order.some(name => !member.params.some(p => p.name === name)))
                        throw Error('Invalid native parameter order: '+qualified);
                }
                const validation = member.argument_validation;
                if (validation) {
                    if (variants.length !== 1 || validation.arity !== member.params.length ||
                        !Array.isArray(validation.parameters) || validation.parameters.length !== validation.arity ||
                        validation.parameters.some((rule, index) => rule.index !== index ||
                            rule.name !== member.params[index].name || member.params[index].optional ||
                            !/^number(?: (?:int|uint))?$/.test(member.params[index].type) || rule.type !== 'number' ||
                            (rule.integer !== undefined && rule.integer !== true) ||
                            (rule.conversion !== undefined && !['int32','uint32'].includes(rule.conversion)) ||
                            (rule.integer && (!Number.isSafeInteger(rule.min) || !Number.isSafeInteger(rule.max) || rule.min > rule.max)) ||
                            (!rule.integer && (rule.min !== undefined || rule.max !== undefined))))
                        throw Error('Invalid argument validation: ' + qualified);
                }
                for (const params of variants) {
                    const parameters = new Set();
                    for (const param of params) {
                        if (!param.name || !param.type || parameters.has(param.name))
                            throw Error('Invalid parameter: ' + qualified + '.' + param.name);
                        validateQualifiers(param.type,param.native_qualifiers,qualified+'.'+param.name);
                        parameters.add(param.name);
                    }
                }
                const overloads = member.native_binding && member.native_binding.overloads;
                if (overloads) {
                    if (overloads.length !== variants.length) throw Error('Native overload count: ' + qualified);
                    const bindings = new Set();
                    overloads.forEach((overload, index) => {
                        const parameters = variants[index].map(param => param.name);
                        const bindingName = '_' + member.name + parameters.map(name => name[0].toUpperCase() + name.slice(1)).join('');
                        if (JSON.stringify(overload.parameters) !== JSON.stringify(parameters) || overload.binding_name !== bindingName || bindings.has(bindingName))
                            throw Error('Native overload parameters: ' + qualified);
                        if (!overload.signature) throw Error('Missing native signature: ' + qualified);
                        if (overload.return_policy !== undefined && !policies.includes(overload.return_policy))
                            throw Error('Invalid return policy: ' + qualified);
                        bindings.add(bindingName);
                    });
                }
            }
        }
    }
    entries(api.interface, api.name);
    const classes = new Map(api.interface.filter(item => item.type === 'class').map(item => [item.name, item]));
    function inherit(klass, visiting = new Set()) {
        if (visiting.has(klass.name)) throw Error('Cyclic metadata inheritance: ' + klass.name);
        visiting = new Set(visiting).add(klass.name);
        const names = new Set(klass.interface.map(member => member.name));
        for (const baseName of klass.implements || []) {
            const base = classes.get(baseName);
            if (!base) throw Error('Unknown metadata base: ' + baseName);
            inherit(base, visiting);
            for (const member of base.interface) {
                if (member.type === 'constructor' || names.has(member.name)) continue;
                const inherited = JSON.parse(JSON.stringify(member));
                inherited.inherited_from = member.inherited_from || baseName;
                klass.interface.push(inherited);
                names.add(member.name);
            }
        }
    }
    for (const klass of classes.values()) inherit(klass);
    return api;
}

function buildApi() {
    const {api: declarations, adapters, contracts} = source.inventory();
    const api = enrich(validate(declarations, adapters), contracts);
    require("./animation-recorder").enrich(api);
    api.binding_adapters = adapters;
    for (const [id, adapter] of Object.entries(api.binding_adapters)) {
        if (!/^pdg::\w+$/.test(adapter.symbol)) throw Error('Invalid adapter symbol: ' + id);
        if (!adapter.header.startsWith('src/bindings/emscripten/')) throw Error('Invalid adapter header: ' + id);
        const header = fs.readFileSync(path.join(root, adapter.header), 'utf8');
        if (!header.includes(adapter.symbol.slice(5) + '(')) throw Error('Stale adapter: ' + id);
    }
    function checkAdapters(items) {
        for (const item of items) {
            const binding = item.native_binding;
            if (binding && binding.adapter && !api.binding_adapters[binding.adapter])
                throw Error('Unknown native adapter: ' + binding.adapter);
            if (item.interface) checkAdapters(item.interface);
        }
    }
    checkAdapters(api.interface);
    api.vers = fs.readFileSync(path.join(root, 'VERSION'), 'utf8').trim();
    return alphabeticalOrder(api);
}

function build() {
    const api = buildApi();
    // The native JS embedder requires ASCII source; escapes preserve any
    // Unicode documentation text in the resulting runtime strings.
    return '// Generated by tools/build-interface-metadata.js. Edit the binding/helper implementations.\n' +
        "'use strict';\nObject.assign(exports, " + JSON.stringify(alphabeticalOrder(api))
            .replace(/[\u0080-\uffff]/g, character => '\\u'+character.charCodeAt(0).toString(16).padStart(4, '0')) + ');\n';
}

if (require.main === module) {
    const output = build();
    if (process.argv.includes('--check')) {
        if (!fs.existsSync(outputPath) || fs.readFileSync(outputPath, 'utf8') !== output)
            throw Error('Interface metadata is stale; run tools/node tools/build-interface-metadata.js');
    } else if (!fs.existsSync(outputPath) || fs.readFileSync(outputPath, 'utf8') !== output) {
        fs.writeFileSync(outputPath, output);
    }
}
module.exports = {validate, build, buildApi};
