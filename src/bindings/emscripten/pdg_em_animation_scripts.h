#ifndef PDG_EM_ANIMATION_SCRIPTS_H
#define PDG_EM_ANIMATION_SCRIPTS_H
#include <emscripten/bind.h>
#include "pdg/sys/animated.h"

#include "pdg/sys/animationrecorder.h"
namespace pdg {
inline void browserRecordCommand(AnimatedBase* target,int id,emscripten::val args) {
    if(!target || (!dynamic_cast<AnimationScript*>(target) && !dynamic_cast<Troupe*>(target))) throw std::invalid_argument("Expected animation recorder");
    auto number=[](emscripten::val value) { if(value.typeOf().as<std::string>()!="number") throw std::invalid_argument("Expected numeric animation argument"); double n=value.as<double>();if(!std::isfinite(n))throw std::invalid_argument("Expected finite animation argument");return n; };
    auto boolean=[](emscripten::val value) {if(value.typeOf().as<std::string>()!="boolean")throw std::invalid_argument("Expected boolean animation argument");return value.as<bool>();};
    auto easing=[&](emscripten::val value) {double n=number(value);if(n<0 || n>=NUM_EASING_FUNCTIONS || std::floor(n)!=n)throw std::invalid_argument("Invalid easing constant");return gEasingFunctions[int(n)];};
    auto read=[&](int index,const std::string& kind)->std::any {
        auto value=args[index];
        if(kind=="number")return number(value);
        if(kind=="boolean")return double(boolean(value));
        if(kind=="string") {if(value.typeOf().as<std::string>()!="string")throw std::invalid_argument("Expected string animation argument");return value.as<std::string>();}
        if(kind=="EasingFunc")return easing(value);
        if(kind=="Point")return value.as<Point>();
        if(kind=="Offset")return value.as<Offset>();
        if(kind=="Rect")return value.as<Rect>();
        if(kind=="Color")return value.as<Color>();
        if(kind=="Camera") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<Camera*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Camera");return captureAnimationArgument(*object);}
        if(kind=="Sprite") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<Sprite*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Sprite");return captureAnimationArgument(object);}
        if(kind=="Part") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<Part*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Part");return captureAnimationArgument(object);}
        if(kind=="Particle") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<Particle*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Particle");return captureAnimationArgument(*object);}
        if(kind=="PhysicsConstraint") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<PhysicsConstraint*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected PhysicsConstraint");return captureAnimationArgument(*object);}
        if(kind=="Animated") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<AnimatedBase*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Animated");return captureAnimationArgument(*object);}
#ifndef PDG_NO_GUI
        if(kind=="Font") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<Font*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Font");return captureAnimationArgument(object);}
#endif
#ifndef PDG_NO_GUI
        if(kind=="Image") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<Image*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Image");return captureAnimationArgument(object);}
#endif
#ifndef PDG_NO_GUI
        if(kind=="Drawing") {if(value.isNull()) return captureAnimationArgument(nullptr);auto* object=value.as<Drawing*>(emscripten::allow_raw_pointers());if(!object)throw std::invalid_argument("Expected Drawing");return captureAnimationArgument(*object);}
#endif
        if(kind=="AffineTransform") {glm::mat3 m(1.f);m[0][0]=number(value["a"]);m[0][1]=number(value["b"]);m[1][0]=number(value["c"]);m[1][1]=number(value["d"]);m[2][0]=number(value["tx"]);m[2][1]=number(value["ty"]);return m;}
        auto numericField=[&](const char* key,double fallback){auto v=value[key];return v.isUndefined()?fallback:number(v);};
        if(kind=="ParticleTrailOptions")return browserParticleTrailOptions(value);
        if(kind=="AnimationPhysicsDriveSettings") {AnimationPhysicsDriveSettings s;s.maxForce=numericField("maxForce",s.maxForce);s.maxTorque=numericField("maxTorque",s.maxTorque);s.frequency=numericField("frequency",s.frequency);s.dampingRatio=numericField("dampingRatio",s.dampingRatio);s.direction=int(numericField("direction",s.direction));return s;}
        if(kind=="CameraMatchOptions") {CameraMatchOptions s;s.matchSource=value["matchSource"].as<Sprite*>(emscripten::allow_raw_pointers());s.matchTarget=value["matchTarget"].as<Sprite*>(emscripten::allow_raw_pointers());if(!s.matchSource || !s.matchTarget)throw std::invalid_argument("Expected matching Sprites");s.mode=CameraMatchMode(int(numericField("mode",s.mode)));s.approachSeconds=numericField("approachSeconds",s.approachSeconds);s.settleSeconds=numericField("settleSeconds",s.settleSeconds);s.fadeSeconds=numericField("fadeSeconds",s.fadeSeconds);if(!value["settleReturnsCamera"].isUndefined())s.settleReturnsCamera=boolean(value["settleReturnsCamera"]);if(!value["approachEasing"].isUndefined())s.approachEasing=easing(value["approachEasing"]);if(!value["settleEasing"].isUndefined())s.settleEasing=easing(value["settleEasing"]);if(!value["fadeEasing"].isUndefined())s.fadeEasing=easing(value["fadeEasing"]);return captureRecorderMatchOptions(s);}
        throw std::invalid_argument("Unsupported animation argument type");
    };
    recordScriptCommand(*target,id,args["length"].as<int>(),read);
}

inline std::shared_ptr<AnimationScript> browserDefineScript(const std::string& name) {
    auto* builder=&AnimatedBase::defineScript(name);
    builder->addRef();
    return std::shared_ptr<AnimationScript>(builder,[](AnimationScript* value){value->release();});
}
inline uintptr_t browserAnimationIdentity(const AnimatedBase& owner) { return reinterpret_cast<uintptr_t>(&owner); }
inline AnimationEvaluator browserAnimationEvaluator(emscripten::val callback) {
    if (callback.typeOf().as<std::string>()!="function") throw std::invalid_argument("Animation evaluator must be a function");
    return [callback](const AnimationEvaluationContext& context) {
        auto response=callback(browserAnimationIdentity(context.target),context.elapsedSeconds);
        const auto error=response["error"];
        if (!error.isUndefined()) throw std::runtime_error(error.as<std::string>());
        const auto result=response["value"];
        if (result.typeOf().as<std::string>()!="boolean") throw std::runtime_error("Animation evaluator must return a boolean synchronously");
        return result.as<bool>();
    };
}
inline AnimationEventHandler browserAnimationEventHandler(emscripten::val callback) {
    if(callback.typeOf().as<std::string>()!="function") throw std::invalid_argument("Animation handler must be a function");
    return [callback](const AnimationEvent& event) {
        auto response=callback(browserAnimationIdentity(event.target),event.elapsedSeconds,event.type,event.scriptName,event.markName,event.iteration,event.reverse,event.operationName);
        const auto error=response["error"];
        if(!error.isUndefined()) throw std::runtime_error(error.as<std::string>());
    };
}
}
EMSCRIPTEN_BINDINGS(pdg_browser_animation_scripts) {
    emscripten::function("_recordAnimationCommand", emscripten::optional_override([](pdg::AnimatedBase* target,int id,emscripten::val args) {return pdg::browserPartCall([&] {pdg::browserRecordCommand(target,id,args);});}), emscripten::allow_raw_pointers());
    emscripten::function("_deleteAnimationScript", emscripten::optional_override([](const std::string& name) { return pdg::browserPartCall([&] { return pdg::AnimatedBase::deleteScript(name); }); }));

    emscripten::function("_defineAnimationScript", emscripten::optional_override([](const std::string& name) { return pdg::browserPartCall([&] { return pdg::browserDefineScript(name); }); }));
}
#endif
