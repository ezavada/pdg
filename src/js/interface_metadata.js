'use strict';

// Structured introspection reads declarations and export descriptors, never
// constructors, instance methods, or accessors. Queries return independent data.
var own = Object.prototype.hasOwnProperty;
function clone(value) { return JSON.parse(JSON.stringify(value)); }

function install(exports, declarations, runtimeProfile) {
    function inventory() {
        var api = clone(declarations);
        if (runtimeProfile) api.runtime_profile = clone(runtimeProfile);
        api.interface = api.interface.filter(function(member) {
            return !member.internal && own.call(exports, member.name);
        });
        if (api.contract_coverage) {
            var applied = [], unavailable = api.contract_coverage.unavailable.slice();
            api.contract_coverage.applied.forEach(function(name) {
                (name.split('.')[0] === api.name || own.call(exports, name.split('.')[0]) ? applied : unavailable).push(name);
            });
            api.contract_coverage.applied = applied;
            api.contract_coverage.unavailable = unavailable;
        }
        api.interface.forEach(function(member) {
            if (member.interface) member.interface = member.interface.filter(function(item) { return !item.internal; });
            if (member.type === 'class' || member.type === 'function') return;
            var descriptor = Object.getOwnPropertyDescriptor(exports, member.name);
            // Constants can vary with the build. Accessors remain unevaluated.
            if (member.readonly && descriptor && own.call(descriptor, 'value') &&
                ['number', 'boolean', 'string'].indexOf(typeof descriptor.value) >= 0)
                member.value = descriptor.value;
            else delete member.value;
        });
        return api;
    }
/* @pdg-member
{
  "name": "pdg.getInterfaceMetadata",
  "type": "function",
  "brief": "return an independent structured interface description without invoking engine code",
  "returns": "object",
  "params": [
    {
      "name": "interfaceName",
      "type": "string",
      "optional": true,
      "default_value": "undefined"
    },
    {
      "name": "memberName",
      "type": "string",
      "optional": true,
      "default_value": "undefined"
    }
  ]
}
*/
    function getInterfaceMetadata(owner, member) {
        if (owner === undefined) {
            if (member !== undefined) throw TypeError('A member query requires an interface name');
            return inventory();
        }
        if (typeof owner !== 'string' || (member !== undefined && typeof member !== 'string'))
            throw TypeError('Interface and member names must be strings');
        var api = inventory();
        var item = owner === 'pdg' ? api : api.interface.filter(function(item) { return item.name === owner; })[0];
        if (!item) throw RangeError('Unknown interface: ' + owner);
        if (member !== undefined) {
            item = (item.interface || []).filter(function(item) { return item.name === member; })[0];
            if (!item) throw RangeError('Unknown interface member: ' + owner + '.' + member);
        }
        return item;
    }
/* @pdg-member
{
  "name": "pdg.describeInterface",
  "type": "function",
  "brief": "format a structured interface description as readable signatures",
  "returns": "string",
  "params": [
    {
      "name": "interfaceName",
      "type": "string",
      "optional": true,
      "default_value": "undefined"
    },
    {
      "name": "memberName",
      "type": "string",
      "optional": true,
      "default_value": "undefined"
    }
  ]
}
*/
    function describeInterface(owner, member) {
        function describe(item) {
            if (item.type === 'module' || item.type === 'class')
                return item.name + '\n' + item.interface.map(describe).join('\n');
            if (item.type !== 'function' && item.type !== 'constructor') return item.type + ' ' + item.name;
            var variants = Array.isArray(item.params[0]) ? item.params : [item.params];
            return variants.map(function(params) {
                return (item.returns || 'undefined') + ' ' + item.name + '(' + params.map(function(param) {
                    return param.type + ' ' + param.name +
                        (param.optional ? ' = ' + param.default_value : '');
                }).join(', ') + ')' + (item.brief ? ' - ' + item.brief : '');
            }).join('\n');
        }
        return describe(getInterfaceMetadata(owner, member));
    }
    exports.getInterfaceMetadata = getInterfaceMetadata;
    exports.describeInterface = describeInterface;
}

exports.install = install;

/* @pdg-schema
{
  "name": "InterfaceMetadata",
  "value": {
    "kind": "record",
    "fields": {
      "name": {
        "type": "string"
      },
      "type": {
        "type": "string"
      },
      "interface": {
        "items": {
          "schema": "InterfaceMetadata"
        },
        "optional": true
      },
      "params": {
        "one_of": [
          {
            "items": {
              "schema": "ParameterMetadata"
            }
          },
          {
            "items": {
              "items": {
                "schema": "ParameterMetadata"
              }
            }
          }
        ],
        "optional": true
      },
      "returns": {
        "type": "string",
        "optional": true
      },
      "brief": {
        "type": "string",
        "optional": true
      },
      "implements": {
        "items": {
          "type": "string"
        },
        "optional": true
      },
      "schemas": {
        "values": {
          "schema": "JSONValue"
        },
        "optional": true
      },
      "runtime_profile": {
        "schema": "RuntimeProfile",
        "optional": true
      }
    },
    "additional_properties": {
      "builtin": "unknown"
    },
    "description": "An independent metadata module, class or member record. Extension fields contain JSON metadata."
  }
}
*/

/* @pdg-schema
{
  "name": "ParameterMetadata",
  "value": {
    "kind": "record",
    "fields": {
      "name": {
        "type": "string"
      },
      "type": {
        "type": "string"
      },
      "optional": {
        "type": "boolean",
        "optional": true
      },
      "default_value": {
        "type": "string",
        "optional": true
      }
    },
    "additional_properties": {
      "builtin": "unknown"
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.getInterfaceMetadata",
  "value": {
    "returns": {
      "schema": "InterfaceMetadata",
      "ownership": "owned"
    }
  }
}
*/

/* @pdg-schema
{
  "name": "RuntimeProfile",
  "value": {
    "kind": "record",
    "fields": {
      "runtime": {
        "type": "string"
      },
      "capabilities": {
        "values": {
          "type": "boolean"
        }
      },
      "scope": {
        "type": "string"
      }
    }
  }
}
*/
