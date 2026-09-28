void partTransfers() {
    using namespace pdg;
    for(bool chipmunk:{false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(chipmunk)continue;
#endif
#ifdef PDG_NO_GUI
        auto* layer=createSpriteLayer();auto* restored=createSpriteLayer();
#else
        auto* layer=createSpriteLayer(nullptr);auto* restored=createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(chipmunk);
        layer->setGravity(0);layer->setDamping(1);
#endif
        auto* from=layer->createSprite();auto* to=layer->createSprite();
        from->setLocation(pdg::Point(30,40));from->setRotation(.3);
        to->setLocation(pdg::Point(-10,20));to->setRotation(-.2);to->setScale(2);
        to->createPart("existing");to->createPart("spare");
        auto* parent=from->createPart("upper");auto* child=from->createPart("lower");
        auto* stay=from->createPart("stay");child->setParentPart(parent).setLocation(4,0);
        parent->setupPhysicsBody(3,5).setVelocity(2,1);child->setupPhysicsBody(2,3).setVelocity(2,1);stay->setupPhysicsBody();
        auto& shape=parent->setupCollider();shape.setCapsule(pdg::Point(-1,0),pdg::Point(1,0),.3);
        auto& internal=parent->physics.createPivotJoint(child->physics);internal.addRef();
        auto& boundary=stay->physics.createPivotJoint(parent->physics);boundary.addRef();
        const auto oldId=parent->getId(),childId=child->getId();auto* body=parent->physics.operator->();
        const auto world=parent->getTransform(partSpace_World),childWorld=child->getTransform(partSpace_World);
        parent->physics.setDriveTarget(pdg::Point(world.tx+2,world.ty),.3,50,20);
        expect(to->transferPart(parent)==parent,"transfer retains the public Part identity");
        expect(parent->getSprite()==to && child->getSprite()==to && !from->getPart(oldId) && !from->getPart(childId),"transfer moves the subtree and source lookup");
        expect(parent->getId()!=oldId && to->getPart(parent->getId())==parent,"destination allocates fresh per-owner IDs");
        expect(parent->physics.operator->()==body && parent->collider.operator->()==&shape,"body/collider handles survive transfer");
        expect(internal.isActive() && !boundary.isActive(),"internal joints survive and crossing joints detach");
        expect(parent->physics.isDriveEnabled(),"world-space manual drive follows the body");
        const auto placed=parent->getTransform(partSpace_World);near(placed.tx,world.tx,"world x survives rotated/scaled destination");near(placed.a,world.a,"world scale survives destination frame");
        near(child->getTransform(partSpace_World).ty,childWorld.ty,"child world placement survives");
        near(body->getVelocity().x,2,"velocity survives transfer");
        parent->physics.clearDrive();
        // A later source teardown must not disconnect the transferred objects.
        layer->removeSprite(from);
        expect(internal.isActive() && parent->physics.isAttached(),"source destruction leaves transferred physics alive");
        Serializer writer;layer->serialize(&writer);auto reader=snapshotReader(writer);restored->deserialize(reader.get());
        auto* copy=restored->getNthSprite(0);expect(copy->findPart("lower")->getParentPart()==copy->findPart("upper"),"transferred hierarchy snapshots under destination IDs");
        expect(copy->findPart("upper")->physics.getConstraintCount()==1,"transferred internal joint snapshots");
        internal.release();boundary.release();cleanupLayer(restored);cleanupLayer(layer);
    }
    Sprite source,destination;
    auto* root=source.createPart("root");auto* child=source.createPart("child");child->setParentPart(root).setLocation(3,4);root->setLocation(10,20);
    const auto childWorld=child->getTransform(partSpace_World);
    destination.createPart("root");bool rejected=false;
    try{destination.transferPart(root);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && root->getSprite()==&source && source.getPartCount()==2,"name conflict rejects without moving either Part");
    destination.clearParts();destination.transferPart(root,false);
    expect(child->getSprite()==&source && !child->getParentPart(),"single-Part transfer leaves children with the source");
    near(child->getTransform(partSpace_World).tx,childWorld.tx,"left-behind child keeps world placement");
    Sprite third;auto* singular=third.createPart("singular");third.setScale(0,1);rejected=false;
    try{third.transferPart(root);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && root->getSprite()==&destination && singular->isAttached(),"singular destination rejects atomically");
    auto* mid=source.createPart("mid");auto* tip=source.createPart("tip");mid->setParentPart(child).setLocation(2,0);tip->setParentPart(mid).setLocation(2,0);
    child->setIKTarget(mid,tip,pdg::Point(3,3));rejected=false;
    try{destination.transferPart(mid);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && mid->getSprite()==&source && child->hasIKTarget(),"active IK requires explicit controller handoff");
    child->clearIKTarget();destination.transferPart(mid);expect(tip->getSprite()==&destination,"transfer succeeds after IK release");
}

void rigPartTransfers() {
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    using namespace pdg;
    const auto path=(std::filesystem::path(__FILE__).parent_path().parent_path()/"data/spriter-regression/arm.scml").string();
    for(bool generated:{false,true})for(bool subtree:{false,true}) {
#ifdef PDG_NO_GUI
        auto* layer=createSpriteLayer();auto* restored=createSpriteLayer();
#else
        auto* layer=createSpriteLayer(nullptr);auto* restored=createSpriteLayer(nullptr);
#endif
        layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);
        auto* source=layer->createSpriteFromSpriterFile(path.c_str());auto* destination=layer->createSpriteFromSpriterFile(path.c_str());
        for(auto* s:{source,destination}){s->pauseAnimation();s->enableAnimationPose("reference");}
        AnimationPhysicsDefinition def;
        for(uint32_t i=0;i<3;++i){AnimationPhysicsBody b;b.bone=i;b.mass=10;b.length=i==0?10:i==1?5:2;b.offsetX=b.length/2;def.bodies.push_back(b);}
        for(uint32_t i=0;i<2;++i){AnimationPhysicsJoint j;j.parent=i;j.child=i+1;j.parentX=def.bodies[i].length/2;j.childX=-def.bodies[i+1].length/2;def.joints.push_back(j);}
        if(generated)source->setupPhysicsFromAnimationRig(30);else source->setupAnimationPhysics(def);
        def.bodies.resize(1);def.joints.clear();destination->setupAnimationPhysics(def);
        auto* forearm=source->findPart("forearm");auto* hand=source->findPart("hand");
        // A detached descendant still belongs to the source skeleton and must
        // transfer with it, keeping a subsequently authored internal joint/drive.
        if(subtree) {
            source->detachAnimationPhysicsPart(hand);
            forearm->physics.createPivotJoint(hand->physics);
            const auto state=hand->physics.getState();
            hand->physics.setDriveTarget(pdg::Point(state.x,state.y),state.rotation,20,10);
        }
        auto& elbow=forearm->physics.getConstraint(0);elbow.addRef();
        source->setAnimationPhysicsRoot("forearm");
        source->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
        auto* body=forearm->physics.operator->();auto* collider=forearm->collider.operator->();
        const auto frame=forearm->getTransform(partSpace_World);const double mass=forearm->physics.getMass()+(subtree?hand->physics.getMass():0);
        bool rejected=false;try{destination->transferPart(source->findPart("shoulder"));}catch(const std::exception&){rejected=true;}
        expect(rejected && source->getPartCount()==3,"whole rig/name-conflicting transfer leaves source intact");
        auto* empty=layer->createSprite();rejected=false;
        try{empty->transferPart(source->findPart("shoulder"));}catch(const std::logic_error&){rejected=true;}
        expect(rejected && empty->getPartCount()==0 && source->getPartCount()==3,"last skeletal body cannot leave an active rig");
        layer->removeSprite(empty);
        expect(destination->transferPart(forearm,subtree)==forearm,"mapped Part moves through general transfer API");
        expect(forearm->getBoneId()==boneId_None && forearm->physics.operator->()==body && forearm->collider.operator->()==collider,"mapped transfer releases binding and retains editable components");
        expect(forearm->physics.getMode()==physicsBody_Dynamic && !elbow.isActive(),"mapped transfer releases animation drive and disconnects boundary joint");
        expect(source->getAnimationPhysicsRoot()==0,"moving selected root chooses remaining skeletal root");
        expect(hand->getSprite()==(subtree?destination:source),"mapped subtree option follows bone descendants");
        if(subtree)expect(hand->physics.isDriveEnabled(),"detached mapped body's manual drive survives transfer");
        near(source->physics.getMass(),30-mass,"source total loses transferred masses without redistribution");
        near(forearm->getTransform(partSpace_World).tx,frame.tx,"mapped capsule frame is preserved");
        destination->attachAnimationPhysicsPart(forearm,destination->findPart("shoulder"));
        if(subtree)destination->attachAnimationPhysicsPart(hand,forearm);
        near(destination->physics.getMass(),10+mass,"explicit attachment adds transferred component masses");
        const auto joints=forearm->physics.getConstraintCount();
        expect(subtree?joints>0:joints==0,"transferred internal joints remain only for selected subtree");
        for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
            Serializer writer;writer.setResourceMode(mode);layer->serialize(&writer);auto reader=snapshotReader(writer);restored->deserialize(reader.get());
            auto* a=restored->getNthSprite(0);auto* b=restored->getNthSprite(1);
            expect(!a->findPart("forearm") && b->isAnimationPhysicsPartAttached(b->findPart("forearm")),"both rigs restore transferred ownership and membership");
            near(a->physics.getMass(),30-mass,"compacted source rig snapshots total");near(b->physics.getMass(),10+mass,"destination snapshots aggregate");
            expect(b->findPart("forearm")->physics.getConstraintCount()==joints,"transferred joint graph snapshots");
            SpriteManager::getSingletonInstance()->stepAnimationPhysics(5);restored->animateLayer(5);
        }
        source->disableAnimationPhysics(0);
        expect(forearm->physics.isAttached() && forearm->physics.getSolver()==physicsSolver_Chipmunk,"source rig teardown cannot destroy transferred bodies");
        destination->detachAnimationPhysicsPart(forearm);destination->disableAnimationPhysics(0);
        expect(forearm->physics.isAttached(),"transferred bodies are ordinary accessories during destination teardown");
        elbow.release();cleanupLayer(restored);cleanupLayer(layer);
    }
#endif
}
