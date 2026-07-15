// -----------------------------------------------
// excluded-function-docs.js
//
// Documentation overrides for functions that are excluded from the standard
// METHOD_SIGNATURE system because they handle null parameters specially.
// These functions can't use the null-call documentation approach because
// null is a valid runtime parameter for them.
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
