// Native C calls remain executable binding source while metadata extraction
// records their function, receiver and joint predicate without duplicating them.
#ifndef PDG_PHYSICS_IMPL_MACROS_H
#define PDG_PHYSICS_IMPL_MACROS_H
#ifndef PDG_NATIVE_C_CALL
#define PDG_NATIVE_C_CALL(function, ...) function(__VA_ARGS__)
#endif
#ifndef PDG_NATIVE_C_CASE
#define PDG_NATIVE_C_CASE(predicate) predicate(self)
#endif
#ifndef REQUIRE_C_INDEX_ARG
#define REQUIRE_C_INDEX_ARG(n, name, countFunction) \
    REQUIRE_INT32_ARG_RANGE(n, name); CR \
    if (name < 0 || name >= countFunction(self)) { CR \
        THROW_RANGE_ERR("contact index out of range"); CR \
        RETURN_UNDEFINED; CR \
    }
#endif
#endif
