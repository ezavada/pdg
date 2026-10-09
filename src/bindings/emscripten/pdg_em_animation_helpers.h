#ifndef PDG_EM_ANIMATION_HELPERS_H
#define PDG_EM_ANIMATION_HELPERS_H
#include <emscripten/bind.h>
#include "pdg/sys/ianimationhelper.h"
#include "pdg/sys/easing.h"
#include <array>
#include <map>
#include <memory>
#include <utility>

namespace pdg {
// AnimatedBase owns these bridges. IDs remain safe after automatic helper removal;
// the destructor also removes registry entries when an owner is destroyed.
class BrowserAnimationHelper;
inline std::map<uint32_t, BrowserAnimationHelper*> browserHelpers;
inline uint32_t nextBrowserHelper = 1;
class BrowserAnimationHelper final : public IAnimationHelper {
public:
    AnimatedBase* owner;
    const uint32_t id;
    emscripten::val callback;
    BrowserAnimationHelper(AnimatedBase& animated, emscripten::val function)
        : owner(&animated), id(nextBrowserHelper++), callback(function) {
        if (!id) throw std::overflow_error("Animation helper ID space exhausted");
        browserHelpers.emplace(id, this);
    }
    ~BrowserAnimationHelper() override { browserHelpers.erase(id); }
    bool animate(AnimatedBase*, double seconds) override {
        // The script adapter catches user exceptions before crossing Wasm.
        return callback(seconds).as<bool>();
    }
};
inline uint32_t browserAddHelper(AnimatedBase& owner, emscripten::val callback) {
    auto helper = std::make_unique<BrowserAnimationHelper>(owner, callback);
    owner.addAnimationHelper(helper.get());
    return helper.release()->id;
}
inline void browserRemoveHelper(AnimatedBase& owner, uint32_t id) {
    const auto found = browserHelpers.find(id);
    if (found != browserHelpers.end() && found->second->owner == &owner)
        owner.removeAnimationHelper(found->second);
}

inline std::vector<emscripten::val> browserEasings;
template<size_t I> float browserEasing(double t, float b, float c, double d) {
    return browserEasings[I](t,b,c,d).template as<float>();
}
template<size_t... I> constexpr std::array<EasingFunc, sizeof...(I)> browserEasingFunctions(std::index_sequence<I...>) {
    return {{&browserEasing<I>...}};
}
inline int browserRegisterEasing(emscripten::val callback) {
    static constexpr auto functions = browserEasingFunctions(std::make_index_sequence<MAX_CUSTOM_EASINGS>());
    for (size_t i = 0; i < browserEasings.size(); ++i)
        if (browserEasings[i].strictlyEquals(callback)) return easingFuncToId(functions[i]);
    if (browserEasings.size() == functions.size()) throw std::range_error("Custom easing registry is full");
    const auto function = functions[browserEasings.size()];
    const int id = easingFuncToId(function);
    if (id == 0) throw std::range_error("Custom easing registry is full");
    browserEasings.push_back(callback);
    return id;
}
}
EMSCRIPTEN_BINDINGS(pdg_browser_easing) {
    emscripten::function("_registerBrowserEasing", &pdg::browserRegisterEasing);
}
#endif
