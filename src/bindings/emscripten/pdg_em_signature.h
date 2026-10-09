#ifndef PDG_EM_SIGNATURE_H
#define PDG_EM_SIGNATURE_H
#include <tuple>
#include <type_traits>
#include <utility>

namespace pdg {
// Unqualified public types impose no native ABI assertion. Qualified types are
// checked exactly against the selected member pointer, including pointee const.
struct EmscriptenAnyNativeType {};
template<class Expected, class Actual>
inline constexpr bool emscriptenNativeTypeMatches =
    std::is_same_v<Expected, EmscriptenAnyNativeType> || std::is_same_v<Expected, Actual>;
template<class> struct EmscriptenNativeSignature;
template<class Owner, class Result, class... Args>
struct EmscriptenNativeSignature<Result (Owner::*)(Args...)> {
    using Return = Result;
    using Parameters = std::tuple<Args...>;
};
template<class Owner, class Result, class... Args>
struct EmscriptenNativeSignature<Result (Owner::*)(Args...) const>
    : EmscriptenNativeSignature<Result (Owner::*)(Args...)> {};
template<class Owner, class Result, class... Args>
struct EmscriptenNativeSignature<Result (Owner::*)(Args...) noexcept>
    : EmscriptenNativeSignature<Result (Owner::*)(Args...)> {};
template<class Owner, class Result, class... Args>
struct EmscriptenNativeSignature<Result (Owner::*)(Args...) const noexcept>
    : EmscriptenNativeSignature<Result (Owner::*)(Args...)> {};
template<auto Method, class Result, class... Args> struct EmscriptenSignatureCheck {
    using Native = EmscriptenNativeSignature<decltype(Method)>;
    static_assert(emscriptenNativeTypeMatches<Result, typename Native::Return>,
        "METHOD_SIGNATURE native return qualifiers disagree with C++");
    static_assert(sizeof...(Args) == std::tuple_size_v<typename Native::Parameters>,
        "METHOD_SIGNATURE native parameter count disagrees with C++");
    template<std::size_t... I> static constexpr bool argumentsMatch(std::index_sequence<I...>) {
        return (emscriptenNativeTypeMatches<Args, std::tuple_element_t<I, typename Native::Parameters>> && ...);
    }
    static_assert(argumentsMatch(std::index_sequence_for<Args...>{}),
        "METHOD_SIGNATURE native parameter qualifiers disagree with C++");
    static constexpr auto pointer = Method;
};
}
#endif
