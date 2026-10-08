// Shared retention helpers, structured values and component constants.
// Class registrations are generated in pdg.embind.
#ifndef PDG_EM_PARTS_H
#define PDG_EM_PARTS_H
#include "pdg/sys/part.h"
#include "pdg/sys/physicsbody.h"
#include <emscripten/bind.h>
#include <memory>
#include <stdexcept>

namespace emscripten { namespace internal {
// Part is factory-owned; its protected destructor must only run via release().
template<> inline void raw_destructor<pdg::Part>(pdg::Part* part) { part->release(); }
}}
namespace pdg {
template<class T> std::shared_ptr<T> browserRetain(T* value) {
    if (!value) return nullptr;
    value->addRef();
    return std::shared_ptr<T>(value, [](T* object) { object->release(); });
}
template<class Operation> auto browserPartCall(Operation operation) -> decltype(operation()) {
    try { return operation(); }
    catch (const std::exception& error) {
        emscripten::val::global("Error").new_(std::string(error.what())).throw_();
    }
}
template<class Owner> emscripten::val browserProcedural(Owner& owner,int operation,emscripten::val input) {
    return browserPartCall([&]{
        if(!emscripten::val::global("Array").call<bool>("isArray",input))throw std::invalid_argument("Expected procedural array");
        const auto n=input["length"].as<unsigned>();if(n>50000)throw std::invalid_argument("Procedural array too long");
        std::vector<double> values;for(unsigned i=0;i<n;++i){if(input[i].typeOf().as<std::string>()!="number")throw std::invalid_argument("Invalid procedural number");values.push_back(input[i].as<double>());}
        auto output=owner.proceduralControl(operation,values);auto result=emscripten::val::array();for(unsigned i=0;i<output.size();++i)result.set(i,output[i]);return result;
    });
}
// @pdg-adapter {"name":"Scene.createSpriteLayer","value":{"symbol":"pdg::browserSceneCreateSpriteLayer","header":"src/bindings/emscripten/pdg_em_parts.h"}}
inline SpriteLayer* browserSceneCreateSpriteLayer(Scene& scene) { return browserPartCall([&]{return scene.createSpriteLayer();}); }
// @pdg-adapter {"name":"Scene.startTimer","value":{"symbol":"pdg::browserSceneStartTimer","header":"src/bindings/emscripten/pdg_em_parts.h"}}
inline void browserSceneStartTimer(Scene& scene,long id,double delay,bool once) { browserPartCall([&]{scene.startTimer(id,delay,once);}); }
// @pdg-adapter {"name":"Scene.getTick","value":{"symbol":"pdg::browserSceneTick","header":"src/bindings/emscripten/pdg_em_parts.h"}}
inline double browserSceneTick(const Scene& scene) { return double(scene.getTick()); }
// @pdg-adapter {"name":"CollisionQueryBuffer.getCollider","value":{"symbol":"pdg::browserQueryCollider","header":"src/bindings/emscripten/pdg_em_parts.h"}}
inline std::shared_ptr<Collider> browserQueryCollider(CollisionQueryBuffer& buffer,uint32_t index) {
    return browserPartCall([&]{return browserRetain(buffer.getCollider(index));});
}
// @pdg-adapter {"name":"CollisionQueryBuffer.setPredicate","value":{"symbol":"pdg::browserQueryPredicate","header":"src/bindings/emscripten/pdg_em_parts.h"}}
inline void browserQueryPredicate(CollisionQueryBuffer& buffer,emscripten::val callback) {
    if(callback.isNull()) {buffer.setPredicate({});return;}
    buffer.setPredicate([callback](const Collider& collider) {
        auto value=callback(browserRetain(const_cast<Collider*>(&collider)));
        if(value.typeOf().as<std::string>()!="boolean")throw std::invalid_argument("Query predicate must return a boolean");
        return value.as<bool>();
    });
}
inline std::shared_ptr<Sprite> browserNewSprite() { return browserRetain(new Sprite()); }
inline emscripten::val browserPartNames(const Sprite& owner) {
    auto result = emscripten::val::array();
    unsigned index = 0;
    for (const auto& name : owner.getPartNames()) result.set(index++, name);
    return result;
}
}

EMSCRIPTEN_BINDINGS(pdg_parts) {
    using namespace emscripten;
    using namespace pdg;
    value_object<SpatialTransform>("_SpatialTransform")
        .field("a", &SpatialTransform::a).field("b", &SpatialTransform::b)
        .field("c", &SpatialTransform::c).field("d", &SpatialTransform::d)
        .field("tx", &SpatialTransform::tx).field("ty", &SpatialTransform::ty);
    value_object<PhysicsBodyState>("_PhysicsBodyState")
        .field("x", &PhysicsBodyState::x).field("y", &PhysicsBodyState::y)
        .field("rotation", &PhysicsBodyState::rotation)
        .field("velocityX", &PhysicsBodyState::velocityX).field("velocityY", &PhysicsBodyState::velocityY)
        .field("angularVelocity", &PhysicsBodyState::angularVelocity);
    value_object<PhysicsDriveState>("_PhysicsDriveState")
        .field("enabled", &PhysicsDriveState::enabled)
        .field("x", &PhysicsDriveState::x)
        .field("y", &PhysicsDriveState::y)
        .field("rotation", &PhysicsDriveState::rotation)
        .field("maxForce", &PhysicsDriveState::maxForce)
        .field("maxTorque", &PhysicsDriveState::maxTorque)
        .field("frequency", &PhysicsDriveState::frequency)
        .field("dampingRatio", &PhysicsDriveState::dampingRatio)
        .field("forceX", &PhysicsDriveState::forceX)
        .field("forceY", &PhysicsDriveState::forceY)
        .field("torque", &PhysicsDriveState::torque)
        .field("positionError", &PhysicsDriveState::positionError)
        .field("rotationError", &PhysicsDriveState::rotationError)
        ;

    constant("boneId_None", static_cast<uint32_t>(boneId_None));
    constant("partId_None", static_cast<uint32_t>(partId_None));
    constant("collisionShape_None", static_cast<uint32_t>(collisionShape_None));
    constant("collisionShape_Capsule", static_cast<uint32_t>(collisionShape_Capsule));
    constant("collisionShape_Circle", static_cast<uint32_t>(collisionShape_Circle));
    constant("collisionShape_Convex", static_cast<uint32_t>(collisionShape_Convex));
    constant("collision_Begin", static_cast<uint32_t>(collision_Begin));
    constant("collision_Stay", static_cast<uint32_t>(collision_Stay));
    constant("collision_End", static_cast<uint32_t>(collision_End));
    constant("constraint_Pin", static_cast<uint32_t>(constraint_Pin));
    constant("constraint_Slide", static_cast<uint32_t>(constraint_Slide));
    constant("constraint_Pivot", static_cast<uint32_t>(constraint_Pivot));
    constant("constraint_Groove", static_cast<uint32_t>(constraint_Groove));
    constant("constraint_Spring", static_cast<uint32_t>(constraint_Spring));
    constant("constraint_RotarySpring", static_cast<uint32_t>(constraint_RotarySpring));
    constant("constraint_RotaryLimit", static_cast<uint32_t>(constraint_RotaryLimit));
    constant("constraint_Ratchet", static_cast<uint32_t>(constraint_Ratchet));
    constant("constraint_Gear", static_cast<uint32_t>(constraint_Gear));
    constant("constraint_Motor", static_cast<uint32_t>(constraint_Motor));
    constant("action_AnimationPhysicsRecoveryComplete", static_cast<int>(Sprite::action_AnimationPhysicsRecoveryComplete));
#ifdef PDG_SPRITER_SUPPORT
    constant("animationPhysics_Kinematic", static_cast<int>(animationPhysics_Kinematic));
    constant("animationPhysics_Dynamic", static_cast<int>(animationPhysics_Dynamic));
    constant("animationPhysics_Driven", static_cast<int>(animationPhysics_Driven));
    constant("animationPhysics_Mixed", static_cast<int>(animationPhysics_Mixed));
#endif
    constant("action_BodyBreak", static_cast<int>(Sprite::action_BodyBreak));
    constant("physicsBreak_Force", static_cast<int>(physicsBreak_Force));
    constant("physicsBreak_AngularSpeed", static_cast<int>(physicsBreak_AngularSpeed));
    constant("physicsForce_None", static_cast<uint32_t>(physicsForce_None));
    constant("partSpace_Local", static_cast<uint32_t>(partSpace_Local));
    constant("partSpace_Sprite", static_cast<uint32_t>(partSpace_Sprite));
    constant("partSpace_World", static_cast<uint32_t>(partSpace_World));
    constant("partPlacement_Snap", static_cast<uint32_t>(partPlacement_Snap));
    constant("partPlacement_PreserveWorld", static_cast<uint32_t>(partPlacement_PreserveWorld));
    constant("physicsBody_None", static_cast<uint32_t>(physicsBody_None));
    constant("physicsBody_Dynamic", static_cast<uint32_t>(physicsBody_Dynamic));
    constant("physicsBody_Kinematic", static_cast<uint32_t>(physicsBody_Kinematic));
    constant("physicsBody_Static", static_cast<uint32_t>(physicsBody_Static));
    constant("physicsSolver_None", static_cast<uint32_t>(physicsSolver_None));
    constant("physicsSolver_Basic", static_cast<uint32_t>(physicsSolver_Basic));
    constant("physicsSolver_Chipmunk", static_cast<uint32_t>(physicsSolver_Chipmunk));
}
#endif
