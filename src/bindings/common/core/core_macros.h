#define EMITTER_METHODS(klass)  \
  METHOD(klass, AddHandler)     CR \
  METHOD(klass, RemoveHandler)  CR \
  METHOD(klass, Clear)          CR \
  METHOD(klass, BlockEvent)     CR \
  METHOD(klass, UnblockEvent)
