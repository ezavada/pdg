#define SERIALIZABLE_METHODS(klass)  \
    METHODS_FROM(klass, ISerializable, \
  METHOD(klass, GetSerializedSize)  CR \
  METHOD(klass, Serialize)          CR \
  METHOD(klass, Deserialize)        CR \
  METHOD(klass, GetMyClassTag) \
    )

