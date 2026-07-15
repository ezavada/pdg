#define HAS_EMITTER_METHODS(klass) \
    HAS_METHOD(klass, "addHandler", AddHandler)        \
    HAS_METHOD(klass, "removeHandler", RemoveHandler)  \
    HAS_METHOD(klass, "clear", Clear)                  \
    HAS_METHOD(klass, "blockEvent", BlockEvent)        \
    HAS_METHOD(klass, "unblockEvent", UnblockEvent)    \

#define EMITTER_BASE_CLASS_IMPL(klass) CR \
  METHOD_IMPL(klass, AddHandler) CR \
	METHOD_SIGNATURE("add a new handler for some event type, or for all events if no type specified. " CR \
	" \\param inHandler the object to handle events"  \
	" \\param inEventType the type of event to handle",  \
		undefined, 2, ([object IEventHandler] inHandler, [number int] inEventType = all_events)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler); CR \
	DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], IEventHandler); CR \
	OPTIONAL_INT32_ARG(2, inType, pdg::all_events); CR \
	self->addHandler(inHandler, inType); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, RemoveHandler) CR \
	METHOD_SIGNATURE("remove a handler for some event type, or for all events (see note) if no type specified. "  CR \
	"If the handler is listed multiple times it will only remove it once.\n"  CR \
	"NOTE: inType == all_events doesn't work quite like you might expect. If "  CR \
	"you have registered a handler for multiple events, but not with all_events, " CR \
	"doing removeHandler(handler, all_events) will do nothing. Basically, " CR \
	"all_events is a special event type that matches all event types when " CR \
 	"considering whether to invoke a handler or not.\n" CR \
	"It is safe to call remove handler from within an event handler's handleEvent() call." CR \
	" \\param inHandler the object to handle events"  \
	" \\param inEventType the type of event to stop handling (see note)",  \
	 	undefined, 2, ([object IEventHandler] inHandler, [number int] inEventType = all_events)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
	REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler); CR \
	OPTIONAL_INT32_ARG(2, inType, pdg::all_events); CR \
	self->removeHandler(inHandler, inType); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, Clear) CR \
	METHOD_SIGNATURE("remove all handlers", undefined, 0, ()); CR \
    REQUIRE_ARG_COUNT(0); CR \
	self->clear(); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, BlockEvent) CR \
	METHOD_SIGNATURE("temporarily ignore all events of a particular type. " CR \
	"Events that are blocked are NOT cached for later, they are just dropped." CR \
	" \\param inEventType the type of event to block",  \
		undefined, 1, ([number int] inEventType)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_INT32_ARG(1, inEventType); CR \
	self->blockEvent(inEventType); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, UnblockEvent) CR \
	METHOD_SIGNATURE("stop ignoring events of a particular type " CR \
	" \\param inEventType the type of event to unblock",  \
		undefined, 1, ([number int] inEventType)); CR \
    REQUIRE_ARG_COUNT(1); CR \
	REQUIRE_INT32_ARG(1, inEventType); CR \
	self->unblockEvent(inEventType); CR \
	NO_RETURN; CR \
	END

