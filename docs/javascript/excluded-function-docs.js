// -----------------------------------------------
// excluded-function-docs.js
//
// Documentation overrides for functions without METHOD_SIGNATURE metadata.
// Some accept null at runtime; others are JavaScript helpers whose methods
// must not be invoked merely to discover their parameters.
//
// Written by Ed Zavada, 2024
// Copyright (c) 2024, Dream Rock Studios, LLC
// -----------------------------------------------

module.exports = {
    "Serializer.serialize_obj": {
        "params": [{
            "name": "obj",
            "type": "object ISerializable"
        }],
        "brief": "Serializes an ISerializable object"
    },
    "Serializer.sizeof_obj": {
        "returns": "number uint",
        "params": [{
            "name": "obj",
            "type": "object ISerializable"
        }],
        "brief": "Calculates the serialized size of an ISerializable object"
    },
};

// Keep these declarations aligned with the helpers in bindings/javascript/pdg.js.
function parameter(name, type, defaultValue) {
    const result = {name, type};
    if (arguments.length === 3) {
        result.optional = true;
        result.default_value = defaultValue;
    }
    return result;
}
function method(name, returns, params, brief) {
    module.exports[name] = {returns, params, brief};
}
method('Image.Image', 'object Image', [
    [parameter('filename', 'string')],
    [parameter('port', 'object Port'), parameter('copyPixels', 'boolean', 'CopyPixels')]
], 'load an image file or create a snapshot or live image of an offscreen port');
method('AnimationSpringTarget.AnimationSpringTarget', 'object AnimationSpringTarget', [
    parameter('mass', 'number', '1'), parameter('stiffness', 'number', '100'),
    parameter('damping', 'number', '20')
], 'create a damped spring target');
method('AnimationSpringTarget.getState', 'object', [], 'copy spring position and velocity');
method('AnimationSpringTarget.setState', undefined, [parameter('state', 'object')], 'replace spring position and velocity');
method('AnimationSpringTarget.applyImpulse', undefined, [parameter('x', 'number'), parameter('y', 'number')], 'apply an impulse to the spring target');
method('AnimationSpringTarget.update', 'object', [parameter('targetX', 'number'), parameter('targetY', 'number'), parameter('deltaSeconds', 'number')], 'advance the spring toward a target');
method('AnimationContactTarget.AnimationContactTarget', 'object AnimationContactTarget', [], 'create an unlocked contact target');
method('AnimationContactTarget.getState', 'object', [], 'copy contact position and influence');
method('AnimationContactTarget.lockWorld', undefined, [parameter('x', 'number'), parameter('y', 'number')], 'lock a contact in world coordinates');
method('AnimationContactTarget.lockPlatform', undefined, [parameter('x', 'number'), parameter('y', 'number'), parameter('support', 'number'), parameter('frame', 'object')], 'lock a contact to a moving platform');
method('AnimationContactTarget.release', undefined, [parameter('fadeSeconds', 'number', '0')], 'release a contact with an optional fade');
method('AnimationContactTarget.update', 'object', [
    parameter('deltaSeconds', 'number'), parameter('contactActive', 'boolean'),
    parameter('withinReach', 'boolean'), parameter('support', 'number', '0'),
    parameter('frame', 'object', 'undefined'), parameter('releaseSeconds', 'number', '0')
], 'update a contact lock or fade its influence');
method('pdg.animationHasTag', 'boolean', [parameter('pose', 'object'), parameter('object', 'string'), parameter('tag', 'string')], 'test an authored tag in an owned pose snapshot');

method('Collider.setContactHandler', 'object Collider', [parameter('callback', 'function')], 'set a contact callback, or null to clear it');
method('Collider.setCollisionFilter', 'object Collider', [parameter('callback', 'function')], 'set a collision predicate, or null to clear it');
