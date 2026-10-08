#ifndef PDG_ANIMATION_OPERATION_H_INCLUDED
#define PDG_ANIMATION_OPERATION_H_INCLUDED

#include "pdg/sys/serializable.h"
#include <any>
#include <memory>
#include <functional>
#include <string>
#include <type_traits>
#include <vector>
#include <typeindex>

namespace pdg {
class AnimatedBase;
using AnimationArguments = std::vector<std::any>;
struct AnimationObjectArgument {
    std::weak_ptr<AnimatedBase*> lifetime;
    std::shared_ptr<RefCountedObj> retained;
    RefCountedObj* get() const;
};
AnimationObjectArgument captureAnimationObject(RefCountedObj*);
// Composite command values resolve borrowed object handles at playback time.
struct AnimationResolvedArgument {
    std::function<std::any()> resolve;
    mutable std::any value;
};
inline const std::any& resolveAnimationArgument(const std::any& argument) {
    if (const auto* captured = std::any_cast<AnimationResolvedArgument>(&argument)) {
        captured->value = captured->resolve();
        return captured->value;
    }
    return argument;
}
struct AnimationValueCodec {
    std::type_index type;
    std::string name;
    std::function<uint32(const std::any&, ISerializer*, bool)> write;
    std::function<std::any(IDeserializer*)> read;
};
void registerAnimationValueCodec(AnimationValueCodec);
uint32 serializeAnimationArgument(const std::any&, ISerializer*, bool writing);
std::any deserializeAnimationArgument(IDeserializer*);


// Values are captured when recording. Engine objects retain their shared identity.
template<class T> std::any captureAnimationArgument(const T& value) {
    using U=std::remove_cvref_t<T>;
    if constexpr (std::is_same_v<U,std::nullptr_t>) return std::any(AnimationObjectArgument{});
    else if constexpr (std::is_arithmetic_v<U> || std::is_enum_v<U>) return std::any(double(value));
    else if constexpr (std::is_convertible_v<U,const char*>) return std::any(std::string(value));
    else if constexpr (std::is_base_of_v<RefCountedObj,U>) {
        return std::any(captureAnimationObject(const_cast<U*>(&value)));
    } else if constexpr (std::is_pointer_v<U> && std::is_base_of_v<RefCountedObj,std::remove_pointer_t<U>>) {
        auto* object=const_cast<std::remove_const_t<std::remove_pointer_t<U>>*>(value);
        return std::any(captureAnimationObject(object));
    } else if constexpr (requires { value.share(); }) return std::any(value.share());
    else return std::any(value);
}

template<class... Args> AnimationArguments captureAnimationArguments(const Args&... args) {
    return {captureAnimationArgument(args)...};
}

template<class T> decltype(auto) animationArgument(const std::any& argument) {
    const auto& value = resolveAnimationArgument(argument);
    using U=std::remove_cvref_t<T>;
    if constexpr (std::is_arithmetic_v<U> || std::is_enum_v<U>) return static_cast<U>(std::any_cast<double>(value));
    else if constexpr (std::is_same_v<U,const char*> || std::is_same_v<U,char*>) return std::any_cast<const std::string&>(value).c_str();
    else if constexpr (std::is_base_of_v<RefCountedObj,U>) {
        auto* object=dynamic_cast<U*>(std::any_cast<const AnimationObjectArgument&>(value).get());
        if(!object) throw std::bad_any_cast();
        return static_cast<T>(*object);
    } else if constexpr (std::is_pointer_v<U> && std::is_base_of_v<RefCountedObj,std::remove_pointer_t<U>>) {
        const auto& reference=std::any_cast<const AnimationObjectArgument&>(value);
        auto* object=dynamic_cast<U>(reference.get());
        if(reference.get() && !object) throw std::bad_any_cast();
        return object;
    } else if constexpr (std::is_abstract_v<U>) return static_cast<T>(*std::any_cast<const std::shared_ptr<U>&>(value));
    else if constexpr (std::is_reference_v<T>) return std::any_cast<T>(const_cast<std::any&>(value));
    else return std::any_cast<U>(value);
}

// Shared semantic dispatch, independent of the class that recorded the operation.
void registerAnimationOperation(const std::string&,
    std::function<bool(AnimatedBase&,const AnimationArguments&)>,
    std::function<double(const AnimationArguments&)>);
bool applyAnimationOperation(AnimatedBase&, const std::string&, const AnimationArguments&);
double animationOperationDuration(const std::string&, const AnimationArguments&);
}
#endif
