// Body overspeed is a notification, independently of geometry or constraints.
void angularSpeedBreaks() {
    using namespace pdg;
    struct Handler : IEventHandler {
        std::vector<SpriteJointBreakInfo> events;
        std::function<void(const SpriteJointBreakInfo&)> callback;
        bool handleEvent(EventEmitter*, long type, void* data) throw() override {
            if (type!=eventType_SpriteBreak) return false;
            const auto info=*static_cast<SpriteJointBreakInfo*>(data);
            events.push_back(info);
            if(callback)callback(info);
            return false; // Unhandled body overspeed must not disconnect anything.
        }
    };
    {
        Sprite sprite;
        auto* part=sprite.createPart("detached-shaft");const auto id=part->getId();
        auto& body=part->setupPhysicsBody();body.addRef();
        int nativeCalls=0;
        Handler handler;handler.callback=[&](const SpriteJointBreakInfo&) { sprite.removePart(id); };
        sprite.addHandler(&handler,eventType_SpriteBreak);
        body.setBreakHandler([&](const PhysicsBodyBreakInfo& info) { ++nativeCalls;near(info.body->getAngularVelocity(),2,"source survives owner removal through native callback"); });
        body.setBreakAngularSpeed(1).setAngularVelocity(2);
        part->animate(.01);
        expect(handler.events.size()==1 && nativeCalls==1 && !body.isAttached(),"direct Part.animate allows its own removal");
        sprite.removeHandler(&handler,eventType_SpriteBreak);body.release();
    }
    for(bool native:{false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(native)continue;
#endif
        auto* manager=SpriteManager::getSingletonInstance();
        auto* layer=SpriteManager::createSpriteLayer();manager->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);layer->setGravity(0);layer->setDamping(1);
#endif
        bool removedLayer=false;
        auto tick=[&] {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(native)manager->stepAnimationPhysics(10);
#endif
            if(!removedLayer)layer->animateLayer(10);
        };
        auto* sprite=layer->createSprite();auto* part=sprite->createPart("shaft");
        auto& root=sprite->setupPhysicsBody();auto& shaft=part->setupPhysicsBody();
        auto& joint=root.createPivotJoint(shaft);
        Handler handler;sprite->addHandler(&handler,eventType_SpriteBreak);
        shaft.setBreakAngularSpeed(10).setAngularVelocity(10);tick();
        expect(handler.events.empty(),"threshold equality does not notify");
        shaft.setAngularVelocity(11);tick();
        expect(handler.events.size()==1,"Part overspeed reaches its Sprite with either solver");
        const auto first=handler.events.back();
        expect(first.body==&shaft && first.part==part && first.actingSprite==sprite && first.inLayer==layer,
               "body break identifies source body, Part, Sprite and Layer");
        expect(first.reason==physicsBreak_AngularSpeed && first.action==Sprite::action_BodyBreak && !first.joint,
               "body breaks do not fabricate a joint");
        near(first.angularSpeed,11,"reported speed is radians/second");near(first.breakAngularSpeed,10,"reported threshold");
        tick();shaft.setBreakAngularSpeed(10);tick();
        expect(handler.events.size()==1,"persistent overspeed and identical setter do not flood events");
        expect(joint.isActive(),"unhandled body notification preserves constraints");
        near(shaft.getAngularVelocity(),11,"threshold does not clamp speed");
        shaft.setAngularVelocity(-10);tick();shaft.setAngularVelocity(-12);tick();
        expect(handler.events.size()==2,"falling to the boundary rearms either spin direction");
        near(handler.events.back().angularSpeed,12,"counterclockwise speed magnitude");
        root.setBreakAngularSpeed(3).setAngularVelocity(4);tick();
        expect(handler.events.back().body==&root && !handler.events.back().part,"root-body events have no Part");
        root.setBreakAngularSpeed(0);
        shaft.setBreakAngularSpeed(5,&root);root.setAngularVelocity(20);shaft.setAngularVelocity(20);tick();
        const auto count=handler.events.size();
        shaft.setAngularVelocity(26);tick();
        expect(handler.events.size()==count+1 && handler.events.back().referenceBody==&root,"relative angular speed uses explicit housing");
        near(handler.events.back().angularSpeed,6,"co-rotating pieces compare relative velocity");
        // Both modes of scene resources preserve the threshold, reference and latch.
        for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
            Serializer writer;writer.setResourceMode(mode);
            const auto size=layer->getSerializedSize(&writer);layer->serialize(&writer);
            expect(size+3==writer.getDataSize(),"overspeed graph size matches tagged stream");
            auto* restored=SpriteManager::createSpriteLayer();manager->addLayer(restored);
            auto reader=snapshotReader(writer);restored->deserialize(reader.get());
            auto* copy=restored->getNthSprite(0);auto* copiedPart=copy->findPart("shaft");
            auto& copiedBody=static_cast<PhysicsBody&>(copiedPart->physics);
            expect(copiedBody.getBreakAngularSpeedReference()==copy->physics.operator->(),"snapshot rebinds reference identity");
            near(copiedBody.getBreakAngularSpeed(),5,"snapshot preserves limit");
            Handler copiedHandler;copy->addHandler(&copiedHandler,eventType_SpriteBreak);
            PhysicsBody::checkBreakAngularSpeeds({&copiedBody});
            expect(copiedHandler.events.empty(),"restored handled excursion does not repeat");
            copiedBody.setAngularVelocity(20);PhysicsBody::checkBreakAngularSpeeds({&copiedBody});
            copiedBody.setAngularVelocity(27);PhysicsBody::checkBreakAngularSpeeds({&copiedBody});
            expect(copiedHandler.events.size()==1,"restored threshold rearms and continues");
            copy->removeHandler(&copiedHandler,eventType_SpriteBreak);cleanupLayer(restored);
        }
        // Both endpoints require saved body state, even when only Parts are referenced.
        root.disconnect();shaft.setBreakAngularSpeed(0);root.setBreakAngularSpeed(5,&shaft);
        layer->setSerializationFlags(ser_InitialData|ser_Positions);
        bool omitted=false;try { Serializer writer;layer->getSerializedSize(&writer); } catch(const std::exception&) { omitted=true; }
        expect(omitted,"relative threshold source cannot be omitted from selected body fields");
        layer->setSerializationFlags(ser_Full);root.setBreakAngularSpeed(0);
        // References outside a standalone Sprite snapshot must be rejected.
        auto* external=layer->createSprite();auto& outside=external->setupPhysicsBody();
        shaft.setBreakAngularSpeed(5,&outside);
        bool rejected=false;try { Serializer writer;sprite->serialize(&writer); } catch(const std::exception&) { rejected=true; }
        expect(rejected,"external angular-speed references cannot silently disappear from snapshots");
        external->removePhysicsBody();
        expect(!shaft.getBreakAngularSpeedReference() && shaft.getBreakAngularSpeed()==0,"removing reference disables monitor");
        // A callback may remove its own Part/body; event source survives dispatch.
        shaft.setBreakAngularSpeed(1).setAngularVelocity(2);
        shaft.addRef();const auto partId=part->getId();
        handler.callback=[&](const SpriteJointBreakInfo& info) { if(info.body==&shaft)sprite->removePart(partId); };
        tick();expect(!shaft.isAttached(),"body notification safely removes its owning Part");shaft.release();
        handler.callback={};sprite->removeHandler(&handler,eventType_SpriteBreak);
        // A callback can destroy a later event's owner, or the whole current layer.
        auto* a=layer->createSprite();auto* b=layer->createSprite();
        a->setupPhysicsBody().setBreakAngularSpeed(1).setAngularVelocity(2);
        b->setupPhysicsBody().setBreakAngularSpeed(1).setAngularVelocity(2);
        Handler removing;a->addHandler(&removing,eventType_SpriteBreak);
        Serializer pendingSnapshot;
        removing.callback=[&](const SpriteJointBreakInfo&) {
            layer->serialize(&pendingSnapshot);
            layer->removeSprite(b);removedLayer=true;cleanupLayer(layer);
        };
        tick();expect(removing.events.size()==1,"break callback safely removes another owner and its layer");
        auto* restored=SpriteManager::createSpriteLayer();manager->addLayer(restored);
        auto reader=snapshotReader(pendingSnapshot);restored->deserialize(reader.get());
        auto* delivered=restored->getNthSprite(2);auto* pending=restored->getNthSprite(3);
        Handler resumed;delivered->addHandler(&resumed,eventType_SpriteBreak);pending->addHandler(&resumed,eventType_SpriteBreak);
        PhysicsBody::checkBreakAngularSpeeds({delivered->physics.operator->(),pending->physics.operator->()});
        expect(resumed.events.size()==1 && resumed.events[0].actingSprite==pending,
               "snapshot inside a break callback preserves other bodies' undelivered notifications");
        delivered->removeHandler(&resumed,eventType_SpriteBreak);pending->removeHandler(&resumed,eventType_SpriteBreak);
        cleanupLayer(restored);
    }
}
