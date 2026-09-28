void rigSnapshots() {
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    using namespace pdg;
    const auto path=(std::filesystem::path(__FILE__).parent_path().parent_path()/"data/spriter-regression/arm.scml").string();
    for(bool generated:{false,true})for(int mode:{serialization_Complete,serialization_ExternalReferences})for(bool tags:{false,true}) {
#ifdef PDG_NO_GUI
        auto* layer=createSpriteLayer();auto* copy=createSpriteLayer();
#else
        auto* layer=createSpriteLayer(nullptr);auto* copy=createSpriteLayer(nullptr);
#endif
        layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);
        auto* s=layer->createSpriteFromSpriterFile(path.c_str());s->pauseAnimation();s->enableAnimationPose("reference");
        if(generated)s->setupPhysicsFromAnimationRig(30);
        else {
            AnimationPhysicsDefinition def;
            for(uint32 i=0;i<3;++i){AnimationPhysicsBody b;b.bone=i;b.mass=10;b.length=i==0?10:i==1?5:2;b.offsetX=b.length/2;b.radius=.25;def.bodies.push_back(b);}
            for(uint32 i=0;i<2;++i){AnimationPhysicsJoint j;j.parent=i;j.child=i+1;j.parentX=def.bodies[i].length/2;j.childX=-def.bodies[i+1].length/2;def.joints.push_back(j);}
            s->setupAnimationPhysics(def);
        }
        auto* root=s->findPart("shoulder");auto* forearm=s->findPart("forearm");auto* hand=s->findPart("hand");
        const auto rigTorque=s->physics.addContinuousTorque(11);
        const auto rigForce=s->physics.applyForce(pdg::Vector(3,4),.3,.2);
        expect(rigTorque && rigForce,"assembly loads register on dynamic root");
        near(s->physics.getMass(),30,"both rig setup paths report assembly total");
        expect(root->collider.getShapeCount()==1 && root->physics.getConstraintCount()>0,"explicit and generated bodies expose shared geometry/joints");
        root->collider.setCapsule(pdg::Point(-3,0),pdg::Point(3,0),.75).setCategory(8).setCollisionMask(2);
        const auto oldRootMass=root->physics.getMass();root->physics.setMass(12);near(s->physics.getMass(),42-oldRootMass,"component edits update either rig total");
        s->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
        AnimationPhysicsDriveSettings settings;settings.maxForce=80;settings.maxTorque=90;settings.frequency=3;
        s->setAnimationPhysicsDriveSettings(settings,"forearm").setAnimationPhysicsMode(animationPhysics_Driven,"forearm",false,0);
        s->detachAnimationPhysicsPart(hand);
        auto state=hand->physics.getState();hand->physics.setVelocity(1,2).setAngularVelocity(.25);
        hand->physics.setDriveTarget(pdg::Point(state.x+2,state.y),state.rotation+.1,40,50);
        hand->physics.setBreakAngularSpeed(5,root->physics.operator->());
        auto* weight=s->createPart("weight");weight->setupPhysicsBody(10,3).teleport(pdg::Point(20,30),0);
        weight->setupCollider().setBox(pdg::Rect(-1,-1,1,1));s->attachAnimationPhysicsPart(weight,forearm);
        forearm->physics.createPivotJoint(weight->physics).setMaxForce(73);
        s->setFlipX(true);
        const auto mass=s->physics.getMass(),moment=root->physics.getMomentOfInertia();
        const auto assemblyInertia=s->physics.getMomentOfInertia();
        const auto joints=forearm->physics.getConstraintCount();
        auto* keep=copy->createSprite();Serializer writer;writer.setResourceMode(mode);writer.setSendTags(tags);
        const auto bytes=layer->getSerializedSize(&writer);layer->serialize(&writer);
        expect(writer.getDataSize()==bytes+(tags?3:0),"active rig snapshot sizing matches bytes");
        // Truncate a graph tail after the rig record: failed adoption must also
        // destroy its staged native bodies without changing the running scene.
        {const auto length=writer.getDataSize()-3;auto* data=std::malloc(length);std::memcpy(data,writer.getDataPtr(),length);Deserializer reader(data,length);
         bool rejected=false;try{copy->deserialize(&reader);}catch(const std::exception&){rejected=true;}
         expect(rejected && copy->getNthSprite(0)==keep,"malformed active rig restores atomically at layer boundary");}
        auto reader=snapshotReader(writer);copy->deserialize(reader.get());auto* c=copy->getNthSprite(0);
        expect(c->isAnimationPhysicsEnabled(),"active physical rig restored");
        expect(c->isFlippedX(),"live reflected frame survives snapshot");
        near(c->physics.getMomentOfInertia(),assemblyInertia,"assembly inertia reconstructed from saved pose");
        expect(c->physics.removeForce(rigTorque) && c->physics.removeForce(rigForce),"assembly force handles survive snapshot independently of root mode");
        near(c->physics.getMass(),mass,"edited membership total restored");
        near(c->findPart("shoulder")->physics.getMomentOfInertia(),moment,"edited body inertia restored");
        expect(c->getAnimationPhysicsMode()==animationPhysics_Mixed,"mixed control restored");
        expect(c->getAnimationPhysicsMode("shoulder")==animationPhysics_Kinematic && c->getAnimationPhysicsMode("forearm")==animationPhysics_Driven,"per-bone authority restored");
        near(c->getAnimationPhysicsDriveSettings("forearm")->maxTorque,90,"drive tuning restored");
        expect(!c->isAnimationPhysicsPartAttached(c->findPart("hand")) && c->isAnimationPhysicsPartAttached(c->findPart("weight")),"detached limb and attached accessory membership restored");
        auto& restoredHand=c->findPart("hand")->physics;
        near(restoredHand.getVelocity().x,1,"detached velocity retained");near(restoredHand.getAngularVelocity(),.25,"detached spin retained");
        expect(restoredHand.isDriveEnabled(),"manual detached drive restored");
        expect(restoredHand.getBreakAngularSpeedReference()==c->findPart("shoulder")->physics.operator->(),"overspeed reference resolves into restored graph");
        expect(c->findPart("forearm")->physics.getConstraintCount()==joints,"edited constraints restored without definition duplicates");
        near(c->findPart("shoulder")->collider.getCapsuleRadius(c->findPart("shoulder")->collider.getShapeId(0)),.75,"edited geometry survives setup metadata");
        expect(c->findPart("shoulder")->collider.getCategory()==8,"collider filter restored");
        const auto oldBone=c->getAnimationBoneTransform("hand",animationSpace_World);
        const auto originalHand=restoredHand.getState();
        restoredHand.teleport(pdg::Point(originalHand.x+.125,originalHand.y),originalHand.rotation);
        near(c->getAnimationBoneTransform("hand",animationSpace_World).x,oldBone.x+.125,"restored direct edits invalidate the published physical pose");
        const auto before=restoredHand.getState();SpriteManager::getSingletonInstance()->stepAnimationPhysics(5);copy->animateLayer(5);
        expect(restoredHand.getState().x!=before.x,"restored detached body continues solving");
        restoredHand.clearDrive();c->detachAnimationPhysicsPart(c->findPart("weight"));
        near(c->physics.getMass(),mass-10,"restored membership remains editable");
        c->disableAnimationPhysics(0);near(c->physics.getMass(),mass-10,"restored teardown preserves assembly total");
        cleanupLayer(copy);cleanupLayer(layer);
    }
    for(bool disabling:{false,true}) {
#ifdef PDG_NO_GUI
        auto* source=createSpriteLayer();auto* restored=createSpriteLayer();
#else
        auto* source=createSpriteLayer(nullptr);auto* restored=createSpriteLayer(nullptr);
#endif
        source->setUseChipmunkPhysics(true);source->setGravity(0);source->setDamping(1);
        auto* s=source->createSpriteFromSpriterFile(path.c_str());s->pauseAnimation();s->enableAnimationPose("reference");
        s->setAnimationPhysicsRoot("shoulder").setupPhysicsFromAnimationRig(30);
        for(const auto& name:s->getPartNames()) {
            auto& b=s->findPart(name)->physics;const auto pose=b.getState();
            b.teleport(pdg::Point(pose.x+1,pose.y+.5),pose.rotation);
        }
        if(disabling)s->disableAnimationPhysics(.5);else s->setAnimationPhysicsMode(animationPhysics_Kinematic,.5);
        auto* manager=SpriteManager::getSingletonInstance();
        for(int i=0;i<20;++i){manager->stepAnimationPhysics(5);source->animateLayer(5);}
        Serializer writer;source->serialize(&writer);auto reader=snapshotReader(writer);restored->deserialize(reader.get());
        cleanupLayer(source);auto* c=restored->getNthSprite(0);
        struct Completion : IEventHandler {
            int count=0;bool disabled=false;
            bool handleEvent(EventEmitter*,long,void* data) throw() override {
                auto* info=static_cast<SpriteAnimateInfo*>(data);
                if(info->action!=Sprite::action_AnimationPhysicsRecoveryComplete)return false;
                ++count;disabled=static_cast<SpriteAnimationPhysicsRecoveryInfo*>(data)->disabled;return true;
            }
        } completion;
        c->addHandler(&completion,eventType_SpriteAnimate);
        expect(c->getAnimationPhysicsMode()==animationPhysics_Driven,"mid-recovery keeps physical authority after restore");
        for(int i=0;i<65;++i){manager->stepAnimationPhysics(5);restored->animateLayer(5);}
        expect(completion.count==0,"restored recovery does not finish before its remaining duration");
        for(int i=0;i<80;++i){manager->stepAnimationPhysics(5);restored->animateLayer(5);}
        expect(completion.count==1 && completion.disabled==disabling,"restored recovery completes exactly once with original destination");
        expect(c->isAnimationPhysicsEnabled()!=disabling,"pending rig disable survives restore");
        if(!disabling)expect(c->getAnimationPhysicsMode()==animationPhysics_Kinematic,"restored recovery reaches Kinematic");
        near(c->physics.getMass(),30,"recovery/disable preserve restored total mass");
        c->removeHandler(&completion,eventType_SpriteAnimate);
        Serializer completed;c->serialize(&completed);Sprite standalone;auto completedReader=snapshotReader(completed);standalone.deserialize(completedReader.get());
        expect(standalone.isAnimationPhysicsEnabled()!=disabling,"standalone Sprite also restores rig state");
        if(!disabling){standalone.disableAnimationPhysics(0);near(standalone.physics.getMass(),30,"unlayered restored teardown preserves total");}
        cleanupLayer(restored);
    }
    {
#ifdef PDG_NO_GUI
        auto* source=createSpriteLayer();auto* copy=createSpriteLayer();
#else
        auto* source=createSpriteLayer(nullptr);auto* copy=createSpriteLayer(nullptr);
#endif
        source->setUseChipmunkPhysics(true);source->setGravity(0);source->setDamping(1);
        auto* s=source->createSpriteFromSpriterFile(path.c_str());s->pauseAnimation();s->enableAnimationPose("reference");
        AnimationPhysicsDefinition def;AnimationPhysicsBody b;b.bone=0;b.mass=2;b.mask=0;def.bodies.push_back(b);
        s->setupAnimationPhysics(def);s->findPart("shoulder")->physics.setMomentOfInertia(3);
        const auto id=s->physics.applyTorque(30,.05,.01);
        SpriteManager::getSingletonInstance()->stepAnimationPhysics(20);source->animateLayer(20);
        Serializer writer;source->serialize(&writer);auto reader=snapshotReader(writer);copy->deserialize(reader.get());
        auto* restored=copy->getNthSprite(0);
        for(int i=0;i<10;++i) {
            SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);source->animateLayer(10);copy->animateLayer(10);
            near(restored->findPart("shoulder")->physics.getAngularVelocity(),s->findPart("shoulder")->physics.getAngularVelocity(),"restored assembly load continues for exactly the saved remaining duration");
        }
        near(restored->findPart("shoulder")->physics.getAngularVelocity(),.5,"restored finite torque contributes no duplicate impulse");
        expect(!restored->physics.removeForce(id),"restored completed force handle expires");
        cleanupLayer(copy);cleanupLayer(source);
    }
#endif
}
