// The same serializable type is registered in the server and browser runtimes.
class NetworkTestMessage extends pdg.ISerializable {
    constructor() {
        super(function() { return 3; },
            function(serializer) { serializer.serialize_1u(15); serializer.serialize_2u(99); },
            function(deserializer) { this.one=deserializer.deserialize_1u(); this.two=deserializer.deserialize_2u(); },
            function() { return 0x50444757; });
    }
}
pdg.registerSerializableClass(NetworkTestMessage);
exports.NetworkTestMessage = NetworkTestMessage;
