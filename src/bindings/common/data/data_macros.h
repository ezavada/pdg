#define SERIALIZABLE_METHODS(klass)  \
  METHOD(klass, GetSerializedSize)  CR \
  METHOD(klass, Serialize)          CR \
  METHOD(klass, Deserialize)        CR \
  METHOD(klass, GetMyClassTag)

