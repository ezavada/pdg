#ifndef PDG_EM_C_DISPATCH_H
#define PDG_EM_C_DISPATCH_H

#include <chipmunk/chipmunk.h>
#include <string>
#include <tuple>
#include <type_traits>

namespace pdg {
// cpVect has several public meanings. Input uses the common x/y value shape;
// the declared IDL return type selects Point, Offset or Vector on output.
template<> struct EmscriptenArgument<cpVect> {
    using Wire = Offset;
    static constexpr bool converted = true;
    static cpVect from(const Wire& value) { return cpv(value.x, value.y); }
};
template<auto Function, auto Predicate = nullptr> struct EmscriptenCCase {
    static constexpr auto function = Function;
    template<class Owner> static bool accepts(Owner* owner) {
        if constexpr (Predicate == nullptr) return true;
        else return Predicate(owner);
    }
};
template<class Public, class Result> emscripten::val emscriptenCValue(Result value) {
    if constexpr (std::is_same_v<Result, cpVect>)
        return emscripten::val(Public(value.x, value.y));
    else return emscripten::val(static_cast<Public>(value));
}
template<class Public, auto Count, class Signature, class... Cases> struct EmscriptenCDispatchImpl;
template<class Public, auto Count, class Result, class Owner, class... Args, class... Cases>
struct EmscriptenCDispatchImpl<Public, Count, Result (*)(Owner*, Args...), Cases...> {
    static_assert((std::is_same_v<Result (*)(Owner*, Args...),
        std::remove_cv_t<decltype(Cases::function)>> && ...),
        "C-function alternatives must have the same signature");
    static emscripten::val call(Owner& owner, typename EmscriptenArgument<Args>::Wire... args) {
        if constexpr (Count != nullptr) {
            static_assert(sizeof...(Args) == 1, "Indexed C calls require one index");
            auto index = std::get<0>(std::tie(args...));
            if (index < 0 || index >= Count(&owner))
                emscripten::val::global("RangeError").new_(std::string("contact index out of range")).throw_();
        }
        auto result = emscripten::val::undefined();
        bool matched = false;
        ([&] {
            if (matched || !Cases::accepts(&owner)) return;
            matched = true;
            if constexpr (std::is_void_v<Result>)
                Cases::function(&owner, EmscriptenArgument<Args>::from(args)...);
            else result = emscriptenCValue<Public>(Cases::function(&owner, EmscriptenArgument<Args>::from(args)...));
        }(), ...);
        // Unsupported getters are optional; unsupported setters reject the call
        // before reaching Chipmunk's asserting joint-specific implementation.
        if (!matched && std::is_void_v<Result>)
            emscripten::val::global("TypeError").new_(std::string("method is not valid for this constraint type")).throw_();
        return result;
    }
};
template<class Public, auto Count, class First, class... Rest>
struct EmscriptenCDispatch : EmscriptenCDispatchImpl<Public, Count,
    std::remove_cv_t<decltype(First::function)>, First, Rest...> {};
}
#endif
