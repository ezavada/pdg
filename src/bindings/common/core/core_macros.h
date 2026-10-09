#define EMITTER_METHODS(klass)  \
    METHODS_FROM(klass, EventEmitter, \
  METHOD(klass, AddHandler)     CR \
  METHOD(klass, RemoveHandler)  CR \
  METHOD(klass, Clear)          CR \
  METHOD(klass, BlockEvent)     CR \
  METHOD(klass, UnblockEvent) \
    )
