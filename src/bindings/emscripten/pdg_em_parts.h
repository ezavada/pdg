// Retained browser handles for factory-owned Parts and PhysicsBody objects.
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
inline std::shared_ptr<Sprite> browserNewSprite() { return browserRetain(new Sprite()); }
inline emscripten::val browserPartNames(const Sprite& owner) {
    auto result = emscripten::val::array();
    unsigned index = 0;
    for (const auto& name : owner.getPartNames()) result.set(index++, name);
    return result;
}
}

#define SpriteParts_Extra \
    .smart_ptr_constructor("SpriteHandle", &pdg::browserNewSprite) \
    .function("_createPart", emscripten::optional_override([](pdg::Sprite& s, const std::string& name) { return pdg::browserPartCall([&] { return pdg::browserRetain(s.createPart(name)); }); })) \
    .function("_transferPart", emscripten::optional_override([](pdg::Sprite& s, pdg::Part* part, bool descendants) { return pdg::browserPartCall([&] { return pdg::browserRetain(s.transferPart(part,descendants)); }); }),emscripten::allow_raw_pointers()) \
    .function("_getPart", emscripten::optional_override([](pdg::Sprite& s, uint32_t id) { return pdg::browserPartCall([&] { return pdg::browserRetain(s.getPart(id)); }); })) \
    .function("_findPart", emscripten::optional_override([](pdg::Sprite& s, const std::string& name) { return pdg::browserPartCall([&] { return pdg::browserRetain(s.findPart(name)); }); })) \
    .function("_getAttachmentPart", emscripten::optional_override([](pdg::Sprite& s) { return pdg::browserPartCall([&] { return pdg::browserRetain(s.getAttachmentPart()); }); })) \
    .function("_readCollider", emscripten::optional_override([](pdg::Sprite& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(&static_cast<pdg::Collider&>(p.collider)); }); })) \
    .function("_setupCollider", emscripten::optional_override([](pdg::Sprite& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(&p.setupCollider()); }); })) \
    .function("removeCollider", emscripten::optional_override([](pdg::Sprite& p) { return pdg::browserPartCall([&] { p.removeCollider(); }); })) \
    .function("_readPhysics", emscripten::optional_override([](pdg::Sprite& s) { return pdg::browserPartCall([&] { return pdg::browserRetain(&static_cast<pdg::PhysicsBody&>(s.physics)); }); })) \
    .function("_setupPhysicsBody", emscripten::optional_override([](pdg::Sprite& s, double mass, double inertia) { return pdg::browserPartCall([&] { return pdg::browserRetain(&s.setupPhysicsBody(mass,inertia)); }); })) \
    .function("removePhysicsBody", emscripten::optional_override([](pdg::Sprite& s) { return pdg::browserPartCall([&] { s.removePhysicsBody(); }); })) \
    .function("removePart", emscripten::optional_override([](pdg::Sprite& s, uint32_t id) { return pdg::browserPartCall([&] { return s.removePart(id); }); })) \
    .function("clearParts", emscripten::optional_override([](pdg::Sprite& s) { return pdg::browserPartCall([&] { s.clearParts(); }); })) \
    .function("getPartCount", emscripten::optional_override([](const pdg::Sprite& s) { return pdg::browserPartCall([&] { return s.getPartCount(); }); })) \
    .function("getPartNames", emscripten::optional_override([](const pdg::Sprite& s) { return pdg::browserPartCall([&] { return pdg::browserPartNames(s); }); })) \
    .function("getSerializedSize", emscripten::optional_override([](pdg::Sprite& s, pdg::Serializer& ser) { return pdg::browserPartCall([&] { return s.getSerializedSize(&ser); }); })) \
    .function("serialize", emscripten::optional_override([](pdg::Sprite& s, pdg::Serializer& ser) { return pdg::browserPartCall([&] { s.serialize(&ser); }); })) \
    .function("deserialize", emscripten::optional_override([](pdg::Sprite& s, pdg::Deserializer& des) { return pdg::browserPartCall([&] { s.deserialize(&des); }); })) \
    .function("_setupFrameCollider", emscripten::optional_override([](pdg::Sprite& p,int mode,int threshold) { return pdg::browserPartCall([&] { return pdg::browserRetain(&p.setupFrameCollider(mode,threshold)); }); })) \
    .function("_setupAnimationCollider", emscripten::optional_override([](pdg::Sprite& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(&p.setupAnimationCollider()); }); })) \
    .function("_setFrameCollisionMask", emscripten::optional_override([](pdg::Sprite& p,pdg::Image* image,pdg::Image* mask) { return pdg::browserPartCall([&] { p.setFrameCollisionMask(image,mask); }); }),emscripten::allow_raw_pointers())


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
    class_<Part, base<AnimatedBase>>("Part")
        .smart_ptr<std::shared_ptr<Part>>("PartHandle")
        .function("getId", &Part::getId)
        .function("getName", &Part::getName)
        .function("isAttached", &Part::isAttached)
        .function("getBoneId", &Part::getBoneId)
        .function("isBoundToBone", &Part::isBoundToBone)
        .function("getAnimationBindingName", &Part::getAnimationBindingName)
        .function("getAnimationSocketName", &Part::getAnimationSocketName)
        .function("hasContent", &Part::hasContent)
        .function("getAttachmentError", &Part::getAttachmentError)
        .function("hasIKTarget", &Part::hasIKTarget)
        .function("isIKTargetReached", &Part::isIKTargetReached)
        .function("getIKError", &Part::getIKError)
        .function("hasIKLimits", &Part::hasIKLimits)
        .function("getIKMinAngle", optional_override([](const Part& p) { return browserPartCall([&] { return p.getIKMinAngle(); }); }))
        .function("getIKMaxAngle", optional_override([](const Part& p) { return browserPartCall([&] { return p.getIKMaxAngle(); }); }))
        .function("isIKDriven", &Part::isIKDriven)
        .function("_setIKLimits", emscripten::optional_override([](Part& p,double lo,double hi) { pdg::browserPartCall([&] { p.setIKLimits(lo,hi); }); }))
        .function("_setIKConstraint", optional_override([](Part& p,PhysicsConstraint& c) { browserPartCall([&] { p.setIKLimits(c); }); }))
        .function("_clearIKLimits", emscripten::optional_override([](Part& p) { p.clearIKLimits(); }))
        .function("_setIKDriveTarget", emscripten::optional_override([](Part& p,std::shared_ptr<Part> middle,std::shared_ptr<Part> tip,const Point& target,double force,double torque,int space,int bend,double influence,double frequency,double damping) {
            pdg::browserPartCall([&] { p.setIKDriveTarget(middle.get(),tip.get(),target,force,torque,space,bend,influence,frequency,damping); }); }))
        .function("_clearIKTarget", emscripten::optional_override([](Part& p) { p.clearIKTarget(); }))
    .function("_getNativeIdentity", emscripten::optional_override([](const Part& p) { return pdg::browserPartCall([&] { return reinterpret_cast<uintptr_t>(&p); }); }))
    .function("_getSprite", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { return browserRetain(p.getSprite()); }); }))
    .function("_getAttachedSprite", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { return browserRetain(p.getAttachedSprite()); }); }))
    .function("_getParentPart", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { return browserRetain(p.getParentPart()); }); }))
    .function("_setParentPart", emscripten::optional_override([](Part& p, std::shared_ptr<Part> parent) { return pdg::browserPartCall([&] { p.setParentPart(parent.get()); }); }))
    .function("_bindToBone", emscripten::optional_override([](Part& p, uint32_t id) { return pdg::browserPartCall([&] { p.bindToBone(id); }); }))
    .function("_unbindFromBone", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { p.unbindFromBone(); }); }))
    .function("_bindToAnimationBinding", emscripten::optional_override([](Part& p, const std::string& name) { return pdg::browserPartCall([&] { p.bindToAnimationBinding(name); }); }))
    .function("_bindToAnimationSocket", emscripten::optional_override([](Part& p, const std::string& name) { return pdg::browserPartCall([&] { p.bindToAnimationSocket(name); }); }))
    .function("_setDrawing", emscripten::optional_override([](Part& p, const Drawing& drawing) { return pdg::browserPartCall([&] { p.setDrawing(drawing); }); }))
    .function("_setImage", emscripten::optional_override([](Part& p, const Image& image, const Rect& bounds) { return pdg::browserPartCall([&] { p.setImage(image,bounds); }); }))
    .function("_clearContent", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { p.clearContent(); }); }))
    .function("_getContentBounds", emscripten::optional_override([](const Part& p, int space) { return pdg::browserPartCall([&] { return p.getContentBounds(space); }); }))
    .function("_getTransform", emscripten::optional_override([](const Part& p, int space) { return pdg::browserPartCall([&] { return p.getTransform(space); }); }))
    .function("_detachSprite", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { p.detachSprite(); }); }))
    .function("_attachSprite", emscripten::optional_override([](Part& p, Sprite* child, int placement, std::shared_ptr<Part> mount) { return pdg::browserPartCall([&] { return browserRetain(p.attachSprite(child,placement,mount.get())); }); }), emscripten::allow_raw_pointers())
    .function("_solveIK", emscripten::optional_override([](Part& p, std::shared_ptr<Part> middle, std::shared_ptr<Part> tip, const Point& target, int space, int bend, double influence) { return pdg::browserPartCall([&] { return p.solveIK(middle.get(),tip.get(),target,space,bend,influence); }); }))
    .function("_setIKTarget", emscripten::optional_override([](Part& p, std::shared_ptr<Part> middle, std::shared_ptr<Part> tip, const Point& target, int space, int bend, double influence) { return pdg::browserPartCall([&] { p.setIKTarget(middle.get(),tip.get(),target,space,bend,influence); }); }))
    .function("_readCollider", emscripten::optional_override([](pdg::Part& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(&static_cast<pdg::Collider&>(p.collider)); }); }))
    .function("_setupCollider", emscripten::optional_override([](pdg::Part& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(&p.setupCollider()); }); }))
    .function("_setupFrameCollider", emscripten::optional_override([](Part& p,int mode,int threshold) { return browserPartCall([&] { return browserRetain(&p.setupFrameCollider(mode,threshold)); }); }))
    .function("_setupAnimationCollider", emscripten::optional_override([](Part& p,const std::string& name) { return browserPartCall([&] { return browserRetain(&p.setupAnimationCollider(name)); }); }))
    .function("removeCollider", emscripten::optional_override([](pdg::Part& p) { return pdg::browserPartCall([&] { p.removeCollider(); }); }))
    .function("_readPhysics", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { return browserRetain(&static_cast<PhysicsBody&>(p.physics)); }); }))
    .function("_setupPhysicsBody", emscripten::optional_override([](Part& p, double mass, double inertia) { return pdg::browserPartCall([&] { return browserRetain(&p.setupPhysicsBody(mass,inertia)); }); }))
    .function("removePhysicsBody", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { p.removePhysicsBody(); }); }))
        ;
    class_<Collider>("Collider")
        .smart_ptr<std::shared_ptr<Collider>>("ColliderHandle")
        .function("getFriction", &Collider::getFriction)
        .function("getRestitution", &Collider::getRestitution)
        .function("_setFriction", optional_override([](Collider& p,double value){return browserPartCall([&]{p.setFriction(value);});}))
        .function("_setRestitution", optional_override([](Collider& p,double value){return browserPartCall([&]{p.setRestitution(value);});}))
        .function("_useBodyMaterial", optional_override([](Collider& p){p.useBodyMaterial();}))
        .function("_getNativeIdentity", optional_override([](const Collider& p) { return reinterpret_cast<uintptr_t>(&p); }))
        .function("isPresent", &Collider::isPresent)
        .function("isAttached", &Collider::isAttached)
        .function("isEnabled", &Collider::isEnabled)
        .function("isSensor", &Collider::isSensor)
        .function("getId", optional_override([](const Collider& p) { return double(p.getId()); }))
        .function("getCategory", &Collider::getCategory)
        .function("getCollisionMask", &Collider::getCollisionMask)
        .function("getGroup", &Collider::getGroup)
        .function("getShapeCount", &Collider::getShapeCount)
        .function("getContactError", &Collider::getContactError)
        .function("getWantsContactEvents", &Collider::getWantsContactEvents)
        .function("_setEnabled", optional_override([](Collider& p, bool v) { return browserPartCall([&] { p.setEnabled(v); }); }))
        .function("_setSensor", optional_override([](Collider& p, bool v) { return browserPartCall([&] { p.setSensor(v); }); }))
        .function("_setWantsContactEvents", optional_override([](Collider& p, bool v) { return browserPartCall([&] { p.setWantsContactEvents(v); }); }))
        .function("_setCategory", optional_override([](Collider& p, uint32_t v) { return browserPartCall([&] { p.setCategory(v); }); }))
        .function("_setCollisionMask", optional_override([](Collider& p, uint32_t v) { return browserPartCall([&] { p.setCollisionMask(v); }); }))
        .function("_setGroup", optional_override([](Collider& p, uint32_t v) { return browserPartCall([&] { p.setGroup(v); }); }))
        .function("_getPhysicsBody", optional_override([](const Collider& p) { return browserRetain(&p.getPhysicsBody()); }))
        .function("_setCircle", optional_override([](Collider& p, double radius, const Point& center) { return browserPartCall([&] { p.setCircle(radius,center); }); }))
        .function("_addCircle", optional_override([](Collider& p, double radius, const Point& center) { return browserPartCall([&] { return p.addCircle(radius,center); }); }))
        .function("_setCapsule", optional_override([](Collider& p, const Point& start, const Point& end, double radius) { return browserPartCall([&] { p.setCapsule(start,end,radius); }); }))
        .function("_addCapsule", optional_override([](Collider& p, const Point& start, const Point& end, double radius) { return browserPartCall([&] { return p.addCapsule(start,end,radius); }); }))
        .function("_getCapsuleStart", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getCapsuleStart(id); }); }))
        .function("_getCapsuleEnd", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getCapsuleEnd(id); }); }))
        .function("_getCapsuleRadius", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getCapsuleRadius(id); }); }))
        .function("_setBox", optional_override([](Collider& p, const Rect& bounds) { return browserPartCall([&] { p.setBox(bounds); }); }))
        .function("_addBox", optional_override([](Collider& p, const Rect& bounds) { return browserPartCall([&] { return p.addBox(bounds); }); }))
        .function("_clearShapes", optional_override([](Collider& p) { return browserPartCall([&] { p.clearShapes(); }); }))
        .function("_removeShape", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.removeShape(id); }); }))
        .function("_getShapeId", optional_override([](Collider& p, uint32_t index) { return browserPartCall([&] { return p.getShapeId(index); }); }))
        .function("_getBounds", optional_override([](Collider& p) { return browserPartCall([&] { return p.getBounds(); }); }))
        .function("_contains", optional_override([](Collider& p, const Point& point) { return browserPartCall([&] { return p.contains(point); }); }))
        .function("_overlaps", optional_override([](Collider& p, std::shared_ptr<Collider> other) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a Collider"); return p.overlaps(*other); }); }))
        .function("_setPhysicsBody", optional_override([](Collider& p, std::shared_ptr<PhysicsBody> body) { return browserPartCall([&] { if(!body)throw std::invalid_argument("Expected a PhysicsBody"); p.setPhysicsBody(*body); }); }))
        .function("_useOwnerPhysics", optional_override([](Collider& p) { return browserPartCall([&] { p.useOwnerPhysics(); }); }))
        .function("_addPolygon", optional_override([](Collider& p, emscripten::val vertices) { return browserPartCall([&] { const unsigned count=vertices["length"].as<unsigned>(); if(count<3||count>4096)throw std::invalid_argument("Expected 3 to 4096 vertices");
            std::vector<Point> points;for(unsigned i=0;i<count;++i)points.push_back(vertices[i].as<Point>());return p.addPolygon(points); }); }))
        .function("_setPolygon", optional_override([](Collider& p, emscripten::val vertices) { return browserPartCall([&] { const unsigned count=vertices["length"].as<unsigned>(); if(count<3||count>4096)throw std::invalid_argument("Expected 3 to 4096 vertices");
            std::vector<Point> points;for(unsigned i=0;i<count;++i)points.push_back(vertices[i].as<Point>());p.setPolygon(points); }); }))
        .function("getGeometrySource", &Collider::getGeometrySource)
        .function("_isSourceShape", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.isSourceShape(id); }); }))
        .function("_getShapeName", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getShapeName(id); }); }))
        .function("_getShapeType", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getShapeType(id); }); }))
        .function("_getCircleRadius", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getCircleRadius(id); }); }))

        .function("_setContactHandler", optional_override([](Collider& p, emscripten::val callback) {
            return browserPartCall([&] {
                if(callback.isNull()) {p.setContactHandler({});return;}
                if(callback.typeOf().as<std::string>()!="function")throw std::invalid_argument("Expected a callback or null");
                p.setContactHandler([callback](const ColliderContact& c) {
                    auto event=emscripten::val::object();event.set("collider",browserRetain(c.collider));event.set("other",browserRetain(c.other));
                    event.set("shape",c.shape);event.set("otherShape",c.otherShape);event.set("phase",c.phase);
                    event.set("point",c.point);event.set("normal",c.normal);event.set("impulse",c.impulse);
                    event.set("penetration",c.penetration);event.set("sensor",c.sensor);callback(event);
                });
            });
        }))
        .function("_setCollisionFilter", optional_override([](Collider& p, emscripten::val callback) {
            return browserPartCall([&] {
                if(callback.isNull()) {p.setCollisionFilter({});return;}
                if(callback.typeOf().as<std::string>()!="function")throw std::invalid_argument("Expected a callback or null");
                p.setCollisionFilter([callback](const Collider& a,const Collider& b) {
                    auto result=callback(browserRetain(const_cast<Collider*>(&a)),browserRetain(const_cast<Collider*>(&b)));
                    if(result.typeOf().as<std::string>()!="boolean")throw std::invalid_argument("Collision filter must return a boolean");
                    return result.as<bool>();
                });
            });
        }))
        .function("_setImageMask", optional_override([](Collider& p, Image* image,const Rect& bounds,int threshold) { return browserPartCall([&] { if(!image)throw std::invalid_argument("Expected an Image");p.setImageMask(*image,bounds,threshold); }); }),allow_raw_pointers())
        .function("_addImageMask", optional_override([](Collider& p, Image* image,const Rect& bounds,int threshold) { return browserPartCall([&] { if(!image)throw std::invalid_argument("Expected an Image");return p.addImageMask(*image,bounds,threshold); }); }),allow_raw_pointers())

        ;
    class_<PhysicsConstraint>("PhysicsConstraint")
        .smart_ptr<std::shared_ptr<PhysicsConstraint>>("PhysicsConstraintHandle")
        .function("_getNativeIdentity", optional_override([](const PhysicsConstraint& p) { return reinterpret_cast<uintptr_t>(&p); }))
        .function("isActive", &PhysicsConstraint::isActive)
        .function("isBroken", &PhysicsConstraint::isBroken)
        .function("getType", &PhysicsConstraint::getType)
        .function("getMaxForce", &PhysicsConstraint::getMaxForce)
        .function("getBreakForce", &PhysicsConstraint::getBreakForce)
        .function("getCollideBodies", &PhysicsConstraint::getCollideBodies)
        .function("getImpulse", &PhysicsConstraint::getImpulse)
        .function("getForce", &PhysicsConstraint::getForce)
        .function("_getAnchorA", optional_override([](const PhysicsConstraint& p) { return browserPartCall([&] { return p.getAnchorA(); }); }))
        .function("_getAnchorB", optional_override([](const PhysicsConstraint& p) { return browserPartCall([&] { return p.getAnchorB(); }); }))
        .function("_setAnchorA", optional_override([](PhysicsConstraint& p, const Point& anchor) { return browserPartCall([&] { p.setAnchorA(anchor); }); }))
        .function("_setAnchorB", optional_override([](PhysicsConstraint& p, const Point& anchor) { return browserPartCall([&] { p.setAnchorB(anchor); }); }))
        .function("_setAnchors", optional_override([](PhysicsConstraint& p, const Point& a, const Point& b) { return browserPartCall([&] { p.setAnchors(a,b); }); }))
        .function("_getGrooveStart", optional_override([](const PhysicsConstraint& p) { return browserPartCall([&] { return p.getGrooveStart(); }); }))
        .function("_getGrooveEnd", optional_override([](const PhysicsConstraint& p) { return browserPartCall([&] { return p.getGrooveEnd(); }); }))
        .function("_setGroove", optional_override([](PhysicsConstraint& p, const Point& a, const Point& b) { return browserPartCall([&] { p.setGroove(a,b); }); }))
        .function("getMinAngle", optional_override([](const PhysicsConstraint& p) { return browserPartCall([&] { return p.getMinAngle(); }); }))
        .function("getMaxAngle", optional_override([](const PhysicsConstraint& p) { return browserPartCall([&] { return p.getMaxAngle(); }); }))
        .function("_setAngleLimits", optional_override([](PhysicsConstraint& p,double lo,double hi) { return browserPartCall([&] { p.setAngleLimits(lo,hi); }); }))
        .function("disconnect", &PhysicsConstraint::disconnect)
        .function("_setMaxForce", optional_override([](PhysicsConstraint& p, double v) { return browserPartCall([&] { p.setMaxForce(v); }); }))
        .function("_setBreakForce", optional_override([](PhysicsConstraint& p, double v) { return browserPartCall([&] { p.setBreakForce(v); }); }))
        .function("_setCollideBodies", optional_override([](PhysicsConstraint& p, bool v) { return browserPartCall([&] { p.setCollideBodies(v); }); }))
        .function("_getBodyA", optional_override([](const PhysicsConstraint& p) { return browserRetain(&p.getBodyA()); }))
        .function("_getBodyB", optional_override([](const PhysicsConstraint& p) { return browserRetain(&p.getBodyB()); }))
        ;
    class_<PhysicsBody>("PhysicsBody")
        .smart_ptr<std::shared_ptr<PhysicsBody>>("PhysicsBodyHandle")
    .function("_createPinJoint", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, const Point& a, const Point& b) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createPinJoint(*other,a,b)); }); }))
    .function("_createPivotJoint", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, const Point& a, const Point& b) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createPivotJoint(*other,a,b)); }); }))
    .function("_createSlideJoint", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, const Point& a, const Point& b, double min, double max) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createSlideJoint(*other,a,b,min,max)); }); }))
    .function("_createGrooveJoint", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, const Point& start, const Point& end, const Point& anchor) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createGrooveJoint(*other,start,end,anchor)); }); }))
    .function("_createSpring", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, const Point& a, const Point& b, double length, double k, double damping) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createSpring(*other,a,b,length,k,damping)); }); }))
    .function("_createRotarySpring", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, double angle, double k, double damping) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createRotarySpring(*other,angle,k,damping)); }); }))
    .function("_createRotaryLimit", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, double min, double max) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createRotaryLimit(*other,min,max)); }); }))
    .function("_createRatchet", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, double interval, double phase) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createRatchet(*other,interval,phase)); }); }))
    .function("_createGear", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, double ratio, double phase) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createGear(*other,ratio,phase)); }); }))
    .function("_createMotor", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other, double rate, double torque) { return browserPartCall([&] { if(!other)throw std::invalid_argument("Expected a PhysicsBody"); return browserRetain(&p.createMotor(*other,rate,torque)); }); }))
    .function("getConstraintCount", &PhysicsBody::getConstraintCount)
    .function("_getConstraint", optional_override([](PhysicsBody& p, uint32_t index) { return browserPartCall([&] { return browserRetain(&p.getConstraint(index)); }); }))
    .function("_disconnect", optional_override([](PhysicsBody& p, std::shared_ptr<PhysicsBody> other) { p.disconnect(other.get()); }))

        .function("isAttached", &PhysicsBody::isAttached)
        .function("isPresent", &PhysicsBody::isPresent)
        .function("getMode", &PhysicsBody::getMode)
        .function("getSolver", &PhysicsBody::getSolver)
        .function("getState", &PhysicsBody::getState)
        .function("getDriveState", &PhysicsBody::getDriveState)
        .function("isDriveEnabled", &PhysicsBody::isDriveEnabled)
    .function("_clearDrive", emscripten::optional_override([](PhysicsBody& p) { pdg::browserPartCall([&] { p.clearDrive(); }); }))
    .function("_setDriveTarget", emscripten::optional_override([](PhysicsBody& p, const Point& point, double angle, double force, double torque, double frequency, double damping, int direction) {
        return pdg::browserPartCall([&] { p.setDriveTarget(point,angle,force,torque,frequency,damping,direction); });
    }))
        .function("getMass", &PhysicsBody::getMass)
        .function("getMomentOfInertia", &PhysicsBody::getMomentOfInertia)
        .function("getSpeed", &PhysicsBody::getSpeed)
        .function("getMovementDirectionInRadians", &PhysicsBody::getMovementDirectionInRadians)
        .function("getBreakAngularSpeed", &PhysicsBody::getBreakAngularSpeed)
        .function("_getBreakAngularSpeedReference", optional_override([](PhysicsBody& p) { return browserRetain(p.getBreakAngularSpeedReference()); }))
        .function("_setBreakAngularSpeed", optional_override([](PhysicsBody& p, double speed, std::shared_ptr<PhysicsBody> reference) {
            browserPartCall([&] { p.setBreakAngularSpeed(speed, reference.get()); });
        }))
        .function("getAngularVelocity", &PhysicsBody::getAngularVelocity)
        .function("getAngularMomentum", &PhysicsBody::getAngularMomentum)
        .function("getLinearDamping", &PhysicsBody::getLinearDamping)
        .function("getAngularDamping", &PhysicsBody::getAngularDamping)
        .function("getFriction", &PhysicsBody::getFriction)
        .function("getRestitution", &PhysicsBody::getRestitution)
    .function("_getNativeIdentity", emscripten::optional_override([](const PhysicsBody& p) { return pdg::browserPartCall([&] { return reinterpret_cast<uintptr_t>(&p); }); }))
    .function("_getVelocity", emscripten::optional_override([](const PhysicsBody& p) { return pdg::browserPartCall([&] { return p.getVelocity(); }); }))
    .function("_setVelocity", emscripten::optional_override([](PhysicsBody& p, const Vector& v) { return pdg::browserPartCall([&] { p.setVelocity(v); }); }))
    .function("_setVelocityInRadians", emscripten::optional_override([](PhysicsBody& p, double speed, double dir) { return pdg::browserPartCall([&] { p.setVelocityInRadians(speed,dir); }); }))
    .function("_teleport", emscripten::optional_override([](PhysicsBody& p, const Point& pos, double angle) { return pdg::browserPartCall([&] { p.teleport(pos,angle); }); }))
    .function("_applyImpulse", emscripten::optional_override([](PhysicsBody& p, const Vector& v) { return pdg::browserPartCall([&] { p.applyImpulse(v); }); }))
    .function("_applyImpulseAt", emscripten::optional_override([](PhysicsBody& p, const Vector& v, const Point& at) { return pdg::browserPartCall([&] { p.applyImpulse(v,at); }); }))
    .function("_applyForce", emscripten::optional_override([](PhysicsBody& p, const Vector& v, double seconds, double delay) { return pdg::browserPartCall([&] { return p.applyForce(v,seconds,delay); }); }))
    .function("_applyForceAt", emscripten::optional_override([](PhysicsBody& p, const Vector& v, double seconds, double delay, const Point& at) { return pdg::browserPartCall([&] { return p.applyForce(v,at,seconds,delay); }); }))
    .function("_applyTorque", emscripten::optional_override([](PhysicsBody& p, double torque, double seconds, double delay) { return pdg::browserPartCall([&] { return p.applyTorque(torque,seconds,delay); }); }))
    .function("addContinuousForce", emscripten::optional_override([](PhysicsBody& p, const Vector& v) { return pdg::browserPartCall([&] { return p.addContinuousForce(v); }); }))
    .function("addContinuousTorque", emscripten::optional_override([](PhysicsBody& p, double torque) { return pdg::browserPartCall([&] { return p.addContinuousTorque(torque); }); }))
    .function("removeForce", emscripten::optional_override([](PhysicsBody& p, uint32_t id) { return pdg::browserPartCall([&] { return p.removeForce(id); }); }))
    .function("step", emscripten::optional_override([](PhysicsBody& p, double seconds) { return pdg::browserPartCall([&] { if (p.isAttached()) throw std::logic_error("Owned bodies advance with their Sprite or Part"); p.step(seconds); }); }))
    .function("_setMass", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setMass(value); }); }))
    .function("_setMomentOfInertia", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setMomentOfInertia(value); }); }))
    .function("_setSpeed", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setSpeed(value); }); }))
    .function("_setAngularVelocity", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setAngularVelocity(value); }); }))
    .function("_setLinearDamping", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setLinearDamping(value); }); }))
    .function("_setAngularDamping", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setAngularDamping(value); }); }))
    .function("_setFriction", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setFriction(value); }); }))
    .function("_setRestitution", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.setRestitution(value); }); }))
    .function("_applyAngularImpulse", emscripten::optional_override([](PhysicsBody& p, double value) { return pdg::browserPartCall([&] { p.applyAngularImpulse(value); }); }))
    .function("_setMode", emscripten::optional_override([](PhysicsBody& p, int value) { return pdg::browserPartCall([&] { p.setMode(value); }); }))
    .function("_stopMoving", emscripten::optional_override([](PhysicsBody& p) { return pdg::browserPartCall([&] { p.stopMoving(); }); }))
    .function("_stopSpinning", emscripten::optional_override([](PhysicsBody& p) { return pdg::browserPartCall([&] { p.stopSpinning(); }); }))
    .function("_stopAllForces", emscripten::optional_override([](PhysicsBody& p) { return pdg::browserPartCall([&] { p.stopAllForces(); }); }))
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
