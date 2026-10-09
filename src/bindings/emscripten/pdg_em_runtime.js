'use strict';

// All retained engine types share one identity policy. Duplicate Embind handles
// release only their own reference; live JavaScript receivers are reused.
const objectRegistries = new WeakMap();
function objectRegistry(bindings) {
    if (!objectRegistries.has(bindings)) objectRegistries.set(bindings, new Map());
    return objectRegistries.get(bindings);
}
function objectIdentity(value) {
    return value._getNativeIdentity ? value._getNativeIdentity() : value._animationIdentity();
}
function rememberObject(bindings, value) {
    if (value) objectRegistry(bindings).set(objectIdentity(value), new WeakRef(value));
    return value;
}
function objectForIdentity(bindings, identity) {
    const registry = objectRegistry(bindings), value = registry.get(identity)?.deref();
    if (!value || (value.isDeleted && value.isDeleted())) {
        registry.delete(identity);
        return null;
    }
    return value;
}
function canonicalRetained(bindings, value) {
    if (!value) return null;
    const existing = objectForIdentity(bindings, objectIdentity(value));
    if (existing) {
        if (existing !== value) value.delete();
        return existing;
    }
    return rememberObject(bindings, value);
}
exports.rememberObject = rememberObject;
exports.objectForIdentity = objectForIdentity;
exports.forgetObject = function(bindings, identity) { objectRegistry(bindings).delete(identity); };
exports.canonicalRetained = canonicalRetained;

exports.installEvents = function(bindings, specs) {
    for (const spec of specs) {
        const Type = bindings[spec.owner];
        if (!Type) continue;
        Type.prototype[spec.name] = function(code, callback) {
            if(spec.owner==='Sprite' && spec.name==='on' && typeof code==='string')
                return bindings.Animated.prototype.on.call(this,code,callback);
            let route = spec;
            if (spec.families) {
                if (!Number.isInteger(code)) throw new TypeError('Expected an event action integer');
                const family = spec.families.find(f => Object.values(f.methods).includes(code));
                if (!family) throw new RangeError('Unknown event action: '+code);
                route = {event:family.event,field:family.field,code};
            } else callback = code;
            if (typeof callback !== 'function') throw new TypeError(spec.name+' requires a callback');
            const emitter = this, eventType = bindings[route.event];
            if (typeof eventType !== 'number') throw new Error('Missing event constant: '+route.event);
            const handler = new bindings.IEventHandler(function(event) {
                if (event && event[route.field] !== undefined && event[route.field] !== route.code) return false;
                return callback.call(emitter,event);
            });
            emitter.addHandler(handler,eventType);
            handler.cancel = function() { emitter.removeHandler(handler,eventType); };
            return handler;
        };
    }
};

// Shared owner registry for evaluator contracts. Store weak references so a
// retained native graph does not keep its JavaScript playback targets alive.
const animationOwners = new Map();
function rememberAnimationOwner(owner) {
    animationOwners.set(owner._animationIdentity(), new WeakRef(owner));
    return owner;
}
function convertArgument(value, contract, schemas, owner, bindings, valueConstructor) {
    if (valueConstructor) return Reflect.construct(bindings[valueConstructor], [value]);
    const argument = schemas[contract?.schema]?.native_binding?.browser?.argument;
    if (!argument || argument === 'native') return value;
    if (argument !== 'animation-evaluator' && argument !== 'animation-event-handler') throw new Error('Unknown argument conversion: ' + argument);
    if (typeof value !== 'function') throw new TypeError('Animation evaluator must be a function');
    rememberAnimationOwner(owner);
    return function(identity, elapsedSeconds, type, scriptName, markName, iteration, reverse, operationName) {
        try {
            const target = animationOwners.get(identity)?.deref();
            if (!target) throw new Error('Animation evaluator target has no script wrapper');
            const context={target:target,elapsedSeconds:elapsedSeconds};
            if(argument==='animation-event-handler') Object.assign(context,{type,scriptName,markName,iteration,reverse,operationName});
            return {value:value(context)};
        } catch (error) { return {error:String(error && error.message || error)}; }
    };
}
exports.rememberAnimationOwner = rememberAnimationOwner;


// Shared implementation for IDL-generated browser wrappers. Native adapters own
// storage and callback lifetimes; validation never retains or copies byte views.
function convertReturn(bindings, value, rule) {
    if (!rule || value == null) return value;
    if (rule.retained) return canonicalRetained(bindings, value);
    if (rule.identity) {
        // Borrowed native getters return an identity, never a deletable alias.
        // Module factories supply the original handle and register it here.
        if (typeof value === 'number') return objectForIdentity(bindings,value);
        return objectForIdentity(bindings,objectIdentity(value)) || rememberObject(bindings,value);
    }
    var Type = bindings[rule.type];
    if (typeof Type !== 'function') throw new Error('Missing return constructor: ' + rule.type);
    return Reflect.construct(Type, rule.arguments.map(function(field) { return field === '$' ? value : value[field]; }));
}
// Argument base views are borrowed for this call, never copied or deleted here.
function adaptArgument(bindings, value, rule) {
    for (const alternative of rule.alternatives || []) {
        const Type = bindings[alternative.type];
        if (Type && value instanceof Type) {
            if (value.isDeleted && value.isDeleted()) throw new Error(alternative.type + ' has been deleted');
            return value[alternative.borrow]();
        }
    }
    const Type = bindings[rule.type];
    if (Type && value instanceof Type) return value;
    throw new TypeError('Expected ' + [rule.type, ...(rule.alternatives || []).map(a => a.type)].join(' or '));
}
exports.adaptArgument = adaptArgument;

// Early return conversion, final receiver identity and validation are separate
// installation phases, but share one function and one mutable policy. Unknown
// handwritten dispatchers remain opaque so their behavior is never bypassed.
const methodPolicies = new WeakMap();
function prepareArguments(bindings, supplied, policy) {
    let args = supplied;
    function replace(index, value) {
        if (Object.is(value, args[index])) return;
        if (args === supplied) args = Array.prototype.slice.call(supplied);
        args[index] = value;
    }
    const validation = policy.validation;
    if (validation) {
        if (supplied.length !== validation.arity)
            throw new Error('argument count mismatch: expected ' + validation.arity + ', but got ' + supplied.length + ' arguments.');
        for (const rule of validation.parameters) {
            let value = supplied[rule.index];
            if (typeof value !== rule.type)
                throw new TypeError('argument ' + (rule.index + 1) + ' must be a number (' + rule.name + ').');
            if (rule.conversion === 'uint32') value = value >>> 0;
            else if (rule.conversion === 'int32') value = value | 0;
            if (rule.integer && (!Number.isInteger(value) || value < rule.min || value > rule.max))
                throw new TypeError('argument ' + (rule.index + 1) + ' must be a number in range [' + rule.min + ', ' + rule.max + '] (' + rule.name + ').');
            replace(rule.index, value);
        }
    }
    if (policy.argumentConversions) for (const conversion of policy.argumentConversions) {
        const value = args[conversion.index];
        if (conversion.optional && value === undefined) continue;
        replace(conversion.index, adaptArgument(bindings, value, conversion.rule));
    }
    return args;
}
function invokeMethod(bindings, native, policy, receiver, supplied) {
    const args = policy.validation || policy.argumentConversions
        ? prepareArguments(bindings, supplied, policy) : supplied;
    if (policy.rememberReceiver) rememberObject(bindings, receiver);
    const result = native.apply(receiver, args);
    return policy.returnsThis ? receiver : convertReturn(bindings, result, policy.returnConversion);
}
const methodRuntime = {adaptArgument, convertReturn, rememberObject, invokeMethod};
// Install type conversions before handwritten adapters and mixins capture public
// methods. Later phases merge policy into the same function whenever possible.
function installReturns(bindings, specs) {
    specs.forEach(function(spec) {
        var Type = spec.root ? bindings : bindings[spec.owner];
        if (!Type) return;
        var prototype = spec.root || spec.static ? Type : Type.prototype;
        var native = prototype[spec.target];
        if (typeof native !== 'function') {
            if (spec.optional) return;
            throw new Error('Missing generated binding: ' + spec.owner + '.' + spec.target);
        }
        const existing = methodPolicies.get(native);
        if (existing && existing.bindings === bindings) {
            Object.assign(existing.policy, spec);
            prototype[spec.name] = native;
            return;
        }
        const policy = Object.assign({}, spec);
        const method = spec.create ? spec.create(native, bindings, policy, methodRuntime) : function() {
            const args = policy.validation || policy.argumentConversions
                ? prepareArguments(bindings, arguments, policy) : arguments;
            if (policy.rememberReceiver) rememberObject(bindings, this);
            const result = native.apply(this, args);
            return policy.returnsThis ? this : convertReturn(bindings, result, policy.returnConversion);
        };
        methodPolicies.set(method, {bindings, policy});
        prototype[spec.name] = method;
    });
}
// Argument adapters may replace the early public method. Finalize receiver
// identity on that dispatcher, or merge it into an existing generated wrapper.
function installReceivers(bindings, specs) {
    installReturns(bindings, specs.map(function(spec) {
        return Object.assign({}, spec, {target:spec.name, returnsThis:true});
    }));
}
function install(bindings, specs) {
    function defaultValue(param) {
        if (param.default_value === 'undefined') return undefined;
        try { return JSON.parse(param.default_value); }
        catch (_) {
            if (Object.prototype.hasOwnProperty.call(bindings, param.default_value)) return bindings[param.default_value];
            const call = /^(\w+)\((.*)\)$/.exec(param.default_value);
            if (call && param.type === 'object '+call[1] && typeof bindings[call[1]] === 'function')
                return Reflect.construct(bindings[call[1]], JSON.parse('['+call[2]+']'));
            throw new Error('Unknown generated default: ' + param.default_value);
        }
    }
    function accepts(value, type, schemas, seen) {
        if (type.nullable && value === null) return true;
        if (Object.prototype.hasOwnProperty.call(type, 'literal')) return value === type.literal;
        if (type.one_of) return type.one_of.some(function(choice) { return accepts(value, choice, schemas, seen); });
        if (type.builtin === 'Uint8Array') return value instanceof Uint8Array;
        if (type.builtin === 'object') return value !== null && typeof value === 'object';
        if (type.schema) {
            var schema = schemas[type.schema];
            if (!schema) throw new Error('Unknown generated schema: ' + type.schema);
            if (schema.kind === 'alias') return accepts(value, schema.value, schemas, seen);
            if (schema.kind === 'callback' || schema.kind === 'constructor') return typeof value === 'function';
            if (schema.kind !== 'record' && schema.kind !== 'context') throw new Error('Unsupported generated schema: ' + type.schema);
            if (value === null || typeof value !== 'object') return false;
            if (seen.some(function(entry) { return entry.value === value && entry.schema === type.schema; })) return false;
            var next = seen.concat([{value:value, schema:type.schema}]);
            return (schema.extends || []).every(function(base) {
                return accepts(value, {schema:base}, schemas, next);
            }) && Object.keys(schema.fields || {}).every(function(name) {
                var field = schema.fields[name];
                return (field.optional && value[name] === undefined) || accepts(value[name], field, schemas, next);
            });
        }
        if (type.items || type.values) {
            if (value === null || typeof value !== 'object' || (type.items && !Array.isArray(value))) return false;
            if (seen.some(function(entry) { return entry.value === value; })) return false;
            var nested = seen.concat([{value:value}]);
            return Object.keys(value).every(function(key) { return accepts(value[key], type.items || type.values, schemas, nested); });
        }
        var name = type.type || '';
        if (/^number(?: |$)/.test(name)) return typeof value === 'number';
        if (name === 'string' || name === 'boolean' || name === 'function' || name === 'undefined') return typeof value === name;
        if (name === 'null') return value === null;
        if (name.indexOf('object ') === 0) {
            const publicName=name.slice(7), shape='native-value:'+publicName;
            return (typeof bindings[publicName] === 'function' && value instanceof bindings[publicName]) ||
                (!!schemas[shape] && accepts(value,{schema:shape},schemas,seen));
        }
        throw new Error('Unsupported generated type: ' + name);
    }
    specs.forEach(function(spec) {
        var Type = spec.root ? bindings : bindings[spec.owner];
        if (!Type) return; // Capability guards omit the entire native class.
        var prototype = spec.root || spec.static ? Type : Type.prototype;
        if (spec.optional && spec.calls.every(function(call) { return typeof prototype[call.target] !== 'function'; })) return;
        var natives = spec.calls.map(function(call) {
            var method = prototype[call.target];
            if (typeof method !== 'function') throw new Error('Missing generated binding: ' + spec.owner + '.' + call.target);
            return method;
        });
        const policy = Object.assign({}, spec);
        const method = function() {
            var supplied = policy.validation || policy.argumentConversions
                ? prepareArguments(bindings, arguments, policy) : arguments;
            var matches = [];
            spec.calls.forEach(function(call, index) {
                if (supplied.length > call.params.length) return;
                var args = [];
                for (var i = 0; i < call.params.length; ++i) {
                    var param = call.params[i];
                    var value = supplied[i];
                    if (value === undefined && param.optional) value = defaultValue(param);
                    if (!(param.optional && (value === undefined || (value === null && param.default_value === 'null'))) &&
                        !accepts(value, param.contract || param, spec.schemas, [])) return;
                    args.push(value);
                }
                matches.push({index:index, args:args, params:call.params});
            });
            // Equivalent public variants may share a single val adapter (bytes
            // and MemBlock); overlapping distinct native overloads are an error.
            if (!matches.length) throw new TypeError(spec.owner + '.' + spec.name + ': arguments do not match a declared overload');
            if (matches.length > 1 && matches.some(function(match) { return spec.calls[match.index].target !== spec.calls[matches[0].index].target; }))
                throw new TypeError(spec.owner + '.' + spec.name + ': ambiguous overload');
            var selected = matches[0];
            selected.params.forEach(function(param, index) {
                var value = selected.args[index], rule = spec.constraints[param.name];
                var integer = /^number (?:int|uint)$/.test(param.type);
                if (integer && (!Number.isInteger(value) || value < (param.type === 'number uint' ? 0 : -2147483648) || value > (param.type === 'number uint' ? 4294967295 : 2147483647)))
                    throw new RangeError(spec.name + ': invalid integer ' + param.name);
                if (rule && ((rule.min !== undefined && value < rule.min) || (rule.max !== undefined && value > rule.max)))
                    throw new RangeError(spec.name + ': out of range ' + param.name);
            });
            var owner = this;
            if (policy.rememberReceiver) rememberObject(bindings, owner);
            var converted = selected.args.map(function(value, index) {
                const param = selected.params[index];
                return convertArgument(value, param.contract || param, spec.schemas, owner, bindings, param.value_constructor);
            });
            var result = natives[selected.index].apply(this, converted);
            return policy.returnsThis ? this : convertReturn(bindings, result, policy.returnConversion);
        };
        methodPolicies.set(method, {bindings, policy});
        prototype[spec.name] = method;
    });
}
exports.install = install;
exports.installReturns = installReturns;

exports.installReceivers = installReceivers;

// Merge source-derived validation with argument conversion and return handling.
exports.installValidation = function(bindings, specs) {
    installReturns(bindings, specs.map(spec => ({owner:spec.owner, name:spec.name, target:spec.name,
        root:spec.root, static:spec.static, optional:spec.optional, validation:spec})));
};
