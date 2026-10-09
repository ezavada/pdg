#include "pdg_script_macros.h"
// Expanded function names and predicates are emitted by the same expressions
// that execute in V8/JSC bindings; no browser-only per-method mapping is needed.
#define PDG_NATIVE_C_CALL(function, ...) PDG_META_C_CALL(PDG_SIGNATURE_STRING(function), PDG_SIGNATURE_STRING((__VA_ARGS__)))
#define PDG_NATIVE_C_CASE(predicate) PDG_META_C_CASE(PDG_SIGNATURE_STRING(predicate))
#define REQUIRE_C_INDEX_ARG(n, name, countFunction) REQUIRE_INT32_ARG_RANGE(n, name); PDG_META_C_INDEX(#name, PDG_SIGNATURE_STRING(countFunction))
#undef METHODS_FROM
#define METHODS_FROM(klass, base, ...) PDG_META_GROUP_BEGIN(#klass,#base) __VA_ARGS__ PDG_META_GROUP_END()
#undef METHOD
#define METHOD(klass, method) PDG_META_MEMBER_DECL(#klass,#method)
#undef METHOD_IMPL
#undef SCRIPT_METHOD_IMPL
#undef STATIC_METHOD_IMPL
#undef FUNCTION_IMPL
#undef CPP_MANAGED_CONSTRUCTOR_IMPL
#undef METHOD_SIGNATURE
#undef METHOD_SIGNATURE_NO_DOCS
#undef HAS_METHOD
#undef EXPORT_CLASS_SYMBOLS
#undef EXPORT_DERIVED_CLASS_SYMBOLS
#undef INIT_FUNCTION
#undef INIT_CONSTANT
#undef INIT_BOOL_CONSTANT
#undef BINDING_CLASS
#undef SINGLETON_CLASS
#undef WRAPPER_CLASS
#undef FACADE_CLASS
#undef WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM
#undef WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY
#undef SINGLETON_MANAGER_INITIALIZER_IMPL
#define SINGLETON_MANAGER_INITIALIZER_IMPL(klass, singletonName) PDG_META_SINGLETON(#klass,singletonName)
#define WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(klass, extraNewFromCpp) PDG_META_OWNERSHIP(#klass,"retained")
#define WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(klass, factoryFunction, extraNewFromCpp) PDG_META_OWNERSHIP(#klass,"retained") PDG_META_CONSTRUCTION(#klass,"factory",factoryFunction)
#undef WRAPPER_INITIALIZER_IMPL_FACTORY_ONLY
#define WRAPPER_INITIALIZER_IMPL_FACTORY_ONLY(klass, factoryFunction, extraNewFromCpp) PDG_META_CONSTRUCTION(#klass,"factory",factoryFunction)
#define BINDING_CLASS(klass) PDG_META_DECLARE(#klass,"binding")
#define SINGLETON_CLASS(klass) PDG_META_DECLARE(#klass,"singleton")
#define WRAPPER_CLASS(klass) PDG_META_DECLARE(#klass,"wrapper")
#define FACADE_CLASS(klass) PDG_META_DECLARE(#klass,"facade")
#define METHOD_IMPL(klass, method) PDG_META_METHOD(#klass, #method)
#define SCRIPT_METHOD_IMPL(klass, method) PDG_META_METHOD(#klass, #method)
#define STATIC_METHOD_IMPL(klass, method) PDG_META_METHOD(#klass, #method)
#define FUNCTION_IMPL(func) PDG_META_FUNCTION(#func)
#define CPP_MANAGED_CONSTRUCTOR_IMPL(klass) PDG_META_CONSTRUCTOR(#klass)
#define METHOD_SIGNATURE(brief, rettype, count, params) PDG_META_SIGNATURE(brief, PDG_SIGNATURE_STRING(rettype), PDG_SIGNATURE_STRING(params))
#define METHOD_SIGNATURE_NO_DOCS(rettype, count, params) PDG_META_SIGNATURE("", PDG_SIGNATURE_STRING(rettype), PDG_SIGNATURE_STRING(params))
#define HAS_METHOD(klass,name,method) PDG_META_BIND(#klass, name, #method)
#define EXPORT_CLASS_SYMBOLS(name, klass, consts, props, methods) PDG_META_CLASS(name,#klass) consts props methods
#define EXPORT_DERIVED_CLASS_SYMBOLS(name, klass, base, finalizer, consts, props, methods) PDG_META_CLASS(name,#klass) PDG_META_BASE(#klass,#base) consts props methods
#define INIT_FUNCTION(name,func) PDG_META_BIND("pdg",name,"" #func)
#define INIT_CONSTANT(name,value) PDG_META_CONSTANT(name,"number")
#define INIT_BOOL_CONSTANT(name,value) PDG_META_CONSTANT(name,"boolean")
#define INIT_UINT_CONSTANT(name,value) PDG_META_CONSTANT(name,"number")

// Preserve scalar validation declarations for source-owned metadata. Only an
// uninterrupted validation prefix is eligible; the extractor never promotes
// checks inside conditional branches to unconditional argument requirements.
#undef REQUIRE_ARG_COUNT
#define REQUIRE_ARG_COUNT(n) PDG_META_ARG_COUNT(#n)
#undef REQUIRE_NUMBER_ARG
#define REQUIRE_NUMBER_ARG(n, paramName) PDG_META_ARG_RULE("NUMBER_ARG", #n, #paramName)
#undef REQUIRE_INT32_ARG
#define REQUIRE_INT32_ARG(n, paramName) PDG_META_ARG_RULE("INT32_ARG", #n, #paramName)
#undef REQUIRE_UINT32_ARG
#define REQUIRE_UINT32_ARG(n, paramName) PDG_META_ARG_RULE("UINT32_ARG", #n, #paramName)
#undef REQUIRE_INT8_ARG
#define REQUIRE_INT8_ARG(n, paramName) PDG_META_ARG_RULE("INT8_ARG", #n, #paramName)
#undef REQUIRE_INT16_ARG
#define REQUIRE_INT16_ARG(n, paramName) PDG_META_ARG_RULE("INT16_ARG", #n, #paramName)
#undef REQUIRE_INT32_ARG_RANGE
#define REQUIRE_INT32_ARG_RANGE(n, paramName) PDG_META_ARG_RULE("INT32_ARG_RANGE", #n, #paramName)
#undef REQUIRE_UINT8_ARG
#define REQUIRE_UINT8_ARG(n, paramName) PDG_META_ARG_RULE("UINT8_ARG", #n, #paramName)
#undef REQUIRE_UINT16_ARG
#define REQUIRE_UINT16_ARG(n, paramName) PDG_META_ARG_RULE("UINT16_ARG", #n, #paramName)
#undef REQUIRE_UINT24_ARG
#define REQUIRE_UINT24_ARG(n, paramName) PDG_META_ARG_RULE("UINT24_ARG", #n, #paramName)
#undef REQUIRE_UINT32_ARG_RANGE
#define REQUIRE_UINT32_ARG_RANGE(n, paramName) PDG_META_ARG_RULE("UINT32_ARG_RANGE", #n, #paramName)
