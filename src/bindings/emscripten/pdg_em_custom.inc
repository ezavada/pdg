// Custom adapters only. Routine registrations come from source metadata.

// @pdg-custom Serializer
.function("_syncSnapshotObjects", optional_override([](Serializer& self,val values,bool sizing) {
    std::vector<const ISerializable*> pointers;
    for(unsigned i=0;i<values["length"].as<unsigned>();++i) pointers.push_back(browserSnapshotPointer(values[i]));
    self.snapshotInstances(std::move(pointers),sizing);
}))
.function("_snapshotObjects", optional_override([](Serializer& self,bool sizing) {
    val result=val::array(); for(auto* object:self.snapshotInstances(sizing)) result.call<void>("push",browserSnapshotObject(object)); return result;
}))
.function("_measureObjectBody", emscripten::optional_override([](pdg::Serializer& self, emscripten::val measure) {
return self.measureObjectBody([&] { return measure().as<uint32>(); });
}))
// @pdg-end-custom

// @pdg-custom Animated
.function("getSerializedSize", emscripten::optional_override([](const pdg::AnimatedBase& owner,pdg::Serializer& serializer) { return pdg::browserPartCall([&] { return owner.getSerializedSize(&serializer); }); }))
.function("serialize", emscripten::optional_override([](const pdg::AnimatedBase& owner,pdg::Serializer& serializer) { pdg::browserPartCall([&] { owner.serialize(&serializer); }); }))
.function("deserialize", emscripten::optional_override([](pdg::AnimatedBase& owner,pdg::Deserializer& deserializer) { pdg::browserPartCall([&] { owner.deserialize(&deserializer); }); }))

// @pdg-end-custom

// @pdg-custom Sprite
#ifdef PDG_SPRITER_SUPPORT
.function("_procedural", &pdg::browserProcedural<pdg::Sprite>)
#endif
.smart_ptr_constructor("SpriteHandle", &pdg::browserNewSprite)
.function("_readCollider", emscripten::optional_override([](pdg::Sprite& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(&static_cast<pdg::Collider&>(p.collider)); }); }))
.function("_readPhysics", emscripten::optional_override([](pdg::Sprite& s) { return pdg::browserPartCall([&] { return pdg::browserRetain(&static_cast<pdg::PhysicsBody&>(s.physics)); }); }))
.function("getPartNames", emscripten::optional_override([](const pdg::Sprite& s) { return pdg::browserPartCall([&] { return pdg::browserPartNames(s); }); }))
.function("getSerializedSize", emscripten::optional_override([](pdg::Sprite& s, pdg::Serializer& ser) { return pdg::browserPartCall([&] { return s.getSerializedSize(&ser); }); }))
.function("serialize", emscripten::optional_override([](pdg::Sprite& s, pdg::Serializer& ser) { return pdg::browserPartCall([&] { s.serialize(&ser); }); }))
.function("deserialize", emscripten::optional_override([](pdg::Sprite& s, pdg::Deserializer& des) { return pdg::browserPartCall([&] { s.deserialize(&des); }); }))

.function("_getNativeIdentity", emscripten::optional_override([](const pdg::Sprite& sprite){return reinterpret_cast<uintptr_t>(&sprite);}))

#ifdef PDG_SPRITER_SUPPORT
.function("isSpriterSprite", &pdg::Sprite::isSpriterSprite)
#endif
#ifdef PDG_SPRITER_SUPPORT
.function("supportsAnimationPhysics", emscripten::optional_override([](const pdg::Sprite&){return pdg::Sprite::supportsAnimationPhysics();}))
#endif
#ifdef PDG_SPRITER_SUPPORT
.function("getAttachedSprite", emscripten::optional_override([](const pdg::Sprite& sprite, const std::string& name) { return pdg::browserRetain(pdg::emscriptenSpriteGetAttachedSprite(sprite,name)); }))
#endif
// @pdg-end-custom

// @pdg-custom SpriteLayer
.function("_getNativeIdentity", emscripten::optional_override([](const pdg::SpriteLayer& layer){return reinterpret_cast<uintptr_t>(&layer);}))

#ifdef PDG_SPRITER_SUPPORT
.function("_createSpriteFromSpriterFile", emscripten::optional_override([](pdg::SpriteLayer& layer, const std::string& path, const std::string& entity) { return pdg::browserRetain(pdg::emscriptenLayerCreateSpriteFromFile(layer,path,entity)); }))
#endif
#ifdef PDG_SPRITER_SUPPORT
.function("createSpriteFromSpriterEntity", emscripten::optional_override([](pdg::SpriteLayer& layer, const std::string& entity) { return pdg::browserRetain(pdg::emscriptenLayerCreateSpriteFromEntity(layer,entity)); }))
#endif
// @pdg-end-custom

// @pdg-custom Image
.class_function("_createImageFromOffscreenPort", &pdg::Image::createImageFromOffscreenPort, emscripten::allow_raw_pointers())
.function("getSerializedSize", emscripten::optional_override([](const pdg::Image& self, pdg::Serializer& writer) { return self.getSerializedSize(&writer); }))
.function("serialize", emscripten::optional_override([](const pdg::Image& self, pdg::Serializer& writer) { self.serialize(&writer); }))
.function("deserialize", emscripten::optional_override([](pdg::Image& self, pdg::Deserializer& reader) { self.deserialize(&reader); }))
.function("_getImageBounds", emscripten::select_overload<pdg::Rect()>(&pdg::Image::getImageBounds))
// @pdg-end-custom

// @pdg-custom AnimatedAttributes
.function("_attributes", &pdg::emscriptenAnimatedAttributesBase, emscripten::return_value_policy::reference())
// @pdg-end-custom

// @pdg-custom Port
// @pdg-end-custom

// @pdg-custom pdg
emscripten::function("_initialize", &pdg::emscriptenInit);
emscripten::function("_isQuitting", &pdg::emscriptenIsQuitting);
emscripten::function("_createSpriteLayerForPort", &pdg::emscriptenCreateSpriteLayerForPort, emscripten::allow_raw_pointers());
emscripten::function("cleanupSpriteLayer", &pdg::cleanupLayer, emscripten::allow_raw_pointers());
emscripten::function("_createTileLayerForPort", &pdg::emscriptenCreateTileLayerForPort, emscripten::allow_raw_pointers());
emscripten::function("_createSnapshotImage", &pdg::emscriptenCreateSnapshotImage, emscripten::allow_raw_pointers());
// @pdg-end-custom

// Specialized methods and lifecycle support for generated retained classes.

// @pdg-custom Camera
.function("_getNativeIdentity", optional_override([](const Camera& c) { return reinterpret_cast<uintptr_t>(&c); }))
.function("_addNativeEventBridge", optional_override([](Camera& c,long type,const val& emitter) { emscriptenEventEmitterAddBridge(c,type,emitter); }))
.function("getMyClassTag", &Camera::getMyClassTag)
.function("getSerializedSize", optional_override([](const Camera& c,Serializer& s) { return browserPartCall([&] { return c.getSerializedSize(&s); }); }))
.function("serialize", optional_override([](const Camera& c,Serializer& s) { browserPartCall([&] { c.serialize(&s); }); }))
.function("deserialize", optional_override([](Camera& c,Deserializer& s) { browserPartCall([&] { c.deserialize(&s); }); }))

.function("_matchCutTo",optional_override([](Camera& c,std::shared_ptr<Camera> destination,Sprite& source,Sprite& target,int mode,double approach,double settle,bool restore,int approachEasing,int settleEasing) {
            browserPartCall([&]{if(!destination)throw std::invalid_argument("Expected destination Camera");CameraMatchOptions options;
                options.matchSource=&source;options.matchTarget=&target;options.mode=static_cast<CameraMatchMode>(mode);options.approachSeconds=approach;options.settleSeconds=settle;
                options.settleReturnsCamera=restore;options.approachEasing=easingIdToFunc(approachEasing);options.settleEasing=easingIdToFunc(settleEasing);c.matchCutTo(*destination,options);});
        }))

.function("_matchFadeTo",optional_override([](Camera& c,std::shared_ptr<Camera> destination,Sprite& source,Sprite& target,int mode,double approach,double settle,bool restore,int approachEasing,int settleEasing,double fade,int fadeEasing) {
            browserPartCall([&]{if(!destination)throw std::invalid_argument("Expected destination Camera");CameraMatchOptions options;
                options.matchSource=&source;options.matchTarget=&target;options.mode=static_cast<CameraMatchMode>(mode);options.approachSeconds=approach;options.settleSeconds=settle;
                options.settleReturnsCamera=restore;options.approachEasing=easingIdToFunc(approachEasing);options.settleEasing=easingIdToFunc(settleEasing);options.fadeSeconds=fade;options.fadeEasing=easingIdToFunc(fadeEasing);c.matchFadeTo(*destination,options);});
        }))

.function("_cameraStopIt",optional_override([](Camera& c){browserPartCall([&]{c.stopIt();});}))
.function("_cameraRestartIt",optional_override([](Camera& c){browserPartCall([&]{c.restartIt();});}))
// @pdg-end-custom

// @pdg-custom Part
.function("_procedural", &pdg::browserProcedural<pdg::Part>)
.function("_setIKLimits", emscripten::optional_override([](Part& p,double lo,double hi) { pdg::browserPartCall([&] { p.setIKLimits(lo,hi); }); }))
.function("_setIKConstraint", optional_override([](Part& p,PhysicsConstraint& c) { browserPartCall([&] { p.setIKLimits(c); }); }))

.function("_getNativeIdentity", emscripten::optional_override([](const Part& p) { return pdg::browserPartCall([&] { return reinterpret_cast<uintptr_t>(&p); }); }))

.function("_getTransform", emscripten::optional_override([](const Part& p, int space) { return pdg::browserPartCall([&] { return p.getTransform(space); }); }))

.function("_solveIK", emscripten::optional_override([](Part& p, std::shared_ptr<Part> middle, std::shared_ptr<Part> tip, const Point& target, int space, int bend, double influence) { return pdg::browserPartCall([&] { return p.solveIK(middle.get(),tip.get(),target,space,bend,influence); }); }))

.function("_readCollider", emscripten::optional_override([](pdg::Part& p) { return pdg::browserPartCall([&] { return pdg::browserRetain(&static_cast<pdg::Collider&>(p.collider)); }); }))

.function("_readPhysics", emscripten::optional_override([](Part& p) { return pdg::browserPartCall([&] { return browserRetain(&static_cast<PhysicsBody&>(p.physics)); }); }))
// @pdg-end-custom

// @pdg-custom Collider
.function("_getNativeIdentity", optional_override([](const Collider& p) { return reinterpret_cast<uintptr_t>(&p); }))
.function("getId", optional_override([](const Collider& p) { return double(p.getId()); }))

.function("_addCircle", optional_override([](Collider& p, double radius, const Point& center) { return browserPartCall([&] { return p.addCircle(radius,center); }); }))
.function("_getCapsuleStart", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getCapsuleStart(id); }); }))
.function("_getCapsuleEnd", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getCapsuleEnd(id); }); }))
.function("_getCapsuleRadius", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.getCapsuleRadius(id); }); }))
.function("_removeShape", optional_override([](Collider& p, uint32_t id) { return browserPartCall([&] { return p.removeShape(id); }); }))
.function("_getShapeId", optional_override([](Collider& p, uint32_t index) { return browserPartCall([&] { return p.getShapeId(index); }); }))
.function("_addPolygon", optional_override([](Collider& p, emscripten::val vertices) { return browserPartCall([&] { const unsigned count=vertices["length"].as<unsigned>(); if(count<3||count>4096)throw std::invalid_argument("Expected 3 to 4096 vertices");
            std::vector<Point> points;for(unsigned i=0;i<count;++i)points.push_back(vertices[i].as<Point>());return p.addPolygon(points); }); }))
.function("_setPolygon", optional_override([](Collider& p, emscripten::val vertices) { return browserPartCall([&] { const unsigned count=vertices["length"].as<unsigned>(); if(count<3||count>4096)throw std::invalid_argument("Expected 3 to 4096 vertices");
            std::vector<Point> points;for(unsigned i=0;i<count;++i)points.push_back(vertices[i].as<Point>());p.setPolygon(points); }); }))
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
// @pdg-end-custom

// @pdg-custom PhysicsBody
.function("getState", &PhysicsBody::getState)
.function("getDriveState", &PhysicsBody::getDriveState)

.function("_getNativeIdentity", emscripten::optional_override([](const PhysicsBody& p) { return pdg::browserPartCall([&] { return reinterpret_cast<uintptr_t>(&p); }); }))
.function("_setVelocity", emscripten::optional_override([](PhysicsBody& p, const Vector& v) { return pdg::browserPartCall([&] { p.setVelocity(v); }); }))
.function("_applyImpulse", emscripten::optional_override([](PhysicsBody& p, const Vector& v) { return pdg::browserPartCall([&] { p.applyImpulse(v); }); }))
.function("_applyImpulseAt", emscripten::optional_override([](PhysicsBody& p, const Vector& v, const Point& at) { return pdg::browserPartCall([&] { p.applyImpulse(v,at); }); }))
.function("_applyForce", emscripten::optional_override([](PhysicsBody& p, const Vector& v, double seconds, double delay) { return pdg::browserPartCall([&] { return p.applyForce(v,seconds,delay); }); }))
.function("_applyForceAt", emscripten::optional_override([](PhysicsBody& p, const Vector& v, double seconds, double delay, const Point& at) { return pdg::browserPartCall([&] { return p.applyForce(v,at,seconds,delay); }); }))
.function("_applyTorque", emscripten::optional_override([](PhysicsBody& p, double torque, double seconds, double delay) { return pdg::browserPartCall([&] { return p.applyTorque(torque,seconds,delay); }); }))
.function("removeForce", emscripten::optional_override([](PhysicsBody& p, uint32_t id) { return pdg::browserPartCall([&] { return p.removeForce(id); }); }))
.function("step", emscripten::optional_override([](PhysicsBody& p, double seconds) { return pdg::browserPartCall([&] { if (p.isAttached()) throw std::logic_error("Owned bodies advance with their Sprite or Part"); p.step(seconds); }); }))

// @pdg-end-custom

// @pdg-custom PhysicsConstraint
.function("_getNativeIdentity", optional_override([](const PhysicsConstraint& p) { return reinterpret_cast<uintptr_t>(&p); }))

// @pdg-end-custom

// @pdg-custom Particle
.function("_getNativeIdentity", optional_override([](const Particle& p) { return reinterpret_cast<uintptr_t>(&p); }))
.function("_addNativeEventBridge", optional_override([](Particle& p,long type,const val& self) { emscriptenEventEmitterAddBridge(p,type,self); }))
.function("_readPhysics", optional_override([](Particle& p) { return browserPartCall([&] { return browserRetain(&static_cast<PhysicsBody&>(p.physics)); }); }))
.function("_readCollider", optional_override([](Particle& p) { return browserPartCall([&] { return browserRetain(&static_cast<Collider&>(p.collider)); }); }))
// @pdg-end-custom

// @pdg-custom ParticleEmitter
.function("_getNativeIdentity", optional_override([](const ParticleEmitter& p) { return reinterpret_cast<uintptr_t>(&p); }))

.function("_setParticleSpeed", optional_override([](ParticleEmitter& p,double lo,double hi) { browserPartCall([&] { p.setParticleSpeed(lo,hi); }); }))
.function("_emit", optional_override([](ParticleEmitter& p,uint32_t count) { return browserPartCall([&] { return p.emit(count); }); }))
// @pdg-end-custom

// @pdg-custom Deserializer
.function("_syncSnapshotObjects", optional_override([](Deserializer& self,val values) {
    std::vector<ISerializable*> pointers;
    for(unsigned i=0;i<values["length"].as<unsigned>();++i) pointers.push_back(browserSnapshotPointer(values[i]));
    self.snapshotInstances(std::move(pointers));
}))
.function("_snapshotObjects", optional_override([](Deserializer& self) {
    val result=val::array(); for(auto* object:self.snapshotInstances()) result.call<void>("push",browserSnapshotObject(object)); return result;
}))
// @pdg-end-custom

// @pdg-custom Scene
.function("_getNativeIdentity", optional_override([](const Scene& s) { return reinterpret_cast<uintptr_t>(&s); }))
.function("_addNativeEventBridge", optional_override([](Scene& s,long type,const val& emitter) { emscriptenEventEmitterAddBridge(s,type,emitter); }))
// @pdg-end-custom
