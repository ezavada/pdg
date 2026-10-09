// Layer wrappers survive native scene/layer disposal. Reject subsequent method
// calls instead of dereferencing the invalidated native object.
#undef METHOD_IMPL
#ifdef _JSC_STR
#define METHOD_IMPL(klass, method) \
    SCRIPT_METHOD_IMPL(klass, method) CR \
    klass* self=static_cast<klass*>(JSObjectGetPrivate(thisObject)); CR \
    if(!self) { THROW_ERR("Layer is disposed"); RETURN_NULL; } CR
#else
#define METHOD_IMPL(klass, method) \
    SCRIPT_METHOD_IMPL(klass, method) CR \
    klass##Wrap* objWrapper=jswrap::ObjectWrap::Unwrap<klass##Wrap>(THIS); CR \
    klass* self=dynamic_cast<klass*>(objWrapper->getCppObject()); CR \
    if(!self) { THROW_ERR("Layer is disposed"); RETURN_NULL; } CR
#endif
