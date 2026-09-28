void generatedRigDroppedAccessory(const std::string& path) {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);layer->enableCollisions();
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());
    sprite->pauseAnimation();sprite->enableAnimationPose("reference");sprite->setupPhysicsFromAnimationRig(34);
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
    auto* weight=sprite->createPart("dropped-weight");
    auto& body=weight->setupPhysicsBody(10,20);
    body.teleport(pdg::Point(0,0),0).setVelocity(0,500);
    weight->setupCollider().setBox(pdg::Rect(-2,-2,2,2)).setCategory(2).setCollisionMask(4).setRestitution(0);
    sprite->attachAnimationPhysicsPart(weight,sprite->findPart("hand"));
    sprite->detachAnimationPhysicsPart(weight);
    auto* floor=layer->createSprite();floor->setupPhysicsBody().setMode(physicsBody_Kinematic);
    floor->setupCollider().setBox(pdg::Rect(-100,50,100,60)).setCategory(4).setCollisionMask(2).setRestitution(0);
    // A late frame must still subdivide while only a detached accessory moves.
    auto* manager=SpriteManager::getSingletonInstance();
    manager->stepAnimationPhysics(200);
    expect(body.getState().y<51,"dropped accessory retains collision substeps after rig becomes Kinematic");
    expect(std::abs(body.getVelocity().y)<1,"inelastic accessory impact stops without a launch");
    layer->setGravity(1000);
    const double landedX=body.getState().x;
    for(int frame=0;frame<30;++frame) {
        const ms_delta durations[]={5,67,4,33,100};
        manager->stepAnimationPhysics(durations[frame%5]);
        const auto position=body.getState();
        expect(position.velocityY>-1,"varying frame times do not add rebound to a zero-elasticity contact");
        expect(position.y>47 && position.y<51 && std::abs(position.x-landedX)<1,
            "dropped weight settles at its contact surface without flying sideways");
    }
    cleanupLayer(layer);
}

void generatedRigMembership(const std::string& path) {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());
    sprite->pauseAnimation();sprite->enableAnimationPose("reference");sprite->setupPhysicsFromAnimationRig(34);
    auto* root=sprite->findPart("shoulder");auto* forearm=sprite->findPart("forearm");auto* hand=sprite->findPart("hand");
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
    auto* manager=SpriteManager::getSingletonInstance();manager->stepAnimationPhysics(10);layer->animateLayer(10);
    auto* weight=sprite->createPart("weight");auto& body=weight->setupPhysicsBody(10,20);
    const auto handState=hand->physics.getState();body.teleport(pdg::Point(handState.x,handState.y),handState.rotation);
    auto& grip=hand->physics.createPivotJoint(body);grip.addRef();
    sprite->attachAnimationPhysicsPart(weight,hand);sprite->attachAnimationPhysicsPart(weight,hand);
    near(sprite->physics.getMass(),44,"attached accessory counted once");
    expect(sprite->isAnimationPhysicsPartAttached(weight),"accessory membership query");
    const auto partState=forearm->physics.getState(),weightState=body.getState();
    const double inertia=forearm->physics.getMomentOfInertia();
    auto& elbow=root->physics.getConstraint(0);elbow.addRef();
    body.addRef();
    sprite->detachAnimationPhysicsPart(forearm);
    near(sprite->physics.getMass(),20,"detaching a limb removes descendants and registered equipment mass");
    expect(!elbow.isActive() && grip.isActive(),"detach disconnects boundary joints and retains internal grip");
    expect(forearm->physics.getConstraintCount()==1 && hand->physics.getConstraintCount()==2,"detached wrist stays connected");
    near(forearm->physics.getState().x,partState.x,"detach preserves body position");
    near(body.getState().x,weightState.x,"detach preserves accessory position");
    near(forearm->physics.getMomentOfInertia(),inertia,"detach preserves inertia");
    expect(forearm->physics.getMode()==physicsBody_Dynamic && hand->physics.getMode()==physicsBody_Dynamic,"detached bones released from animation");
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
    expect(hand->physics.getMode()==physicsBody_Dynamic,"whole-rig commands exclude detached limbs");
    sprite->physics.setMass(40);
    near(forearm->physics.getMass(),10,"remaining total edit does not redistribute detached mass");
    near(body.getMass(),10,"remaining total edit excludes detached equipment");
    bool rejected=false;try{sprite->setupPhysicsFromAnimationRig(50);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && sprite->physics.getMass()==40,"repeated setup rejects edited membership atomically");
    rejected=false;try{sprite->detachAnimationPhysicsPart(root);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && sprite->isAnimationPhysicsPartAttached(root),"cannot remove the last mapped member");
    forearm->physics.setDriveTarget(pdg::Point(partState.x,partState.y),partState.rotation,10,10);
    rejected=false;try{sprite->attachAnimationPhysicsPart(forearm);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && !sprite->isAnimationPhysicsPartAttached(forearm),"manual handoff requires explicit release");
    forearm->physics.clearDrive();sprite->attachAnimationPhysicsPart(forearm);
    sprite->attachAnimationPhysicsPart(hand);sprite->attachAnimationPhysicsPart(weight,hand);
    near(sprite->physics.getMass(),64,"reattachment restores existing masses without redistribution");
    expect(forearm->physics.getConstraintCount()==1,"membership registration does not invent a joint");
    root->physics.createPivotJoint(forearm->physics);
    sprite->detachAnimationPhysicsPart(root,false);
    expect(sprite->getAnimationPhysicsRoot()==1,"detaching root selects largest remaining skeleton branch");
    sprite->clearAnimationPhysicsRoot();expect(sprite->getAnimationPhysicsRoot()==1,"automatic root skips detached bones");
    const auto velocity=forearm->physics.getVelocity();sprite->physics.applyImpulse(Vector(10,0));
    near(forearm->physics.getVelocity().x,velocity.x+1,"whole-sprite impulse follows replacement root");
    sprite->attachAnimationPhysicsPart(root);
    rejected=false;try{sprite->detachAnimationPhysicsPart(root);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && sprite->physics.getMass()==64,"restored ancestor reclaims logical children without creating joints");
    sprite->detachAnimationPhysicsPart(root,false);
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.5);
    const auto weightId=weight->getId();
    rejected=false;try{sprite->removePart(weightId);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && sprite->findPart("weight")==weight && sprite->isAnimationPhysicsPartAttached(weight),"removal during recovery is rejected before changing Part ownership");
    sprite->setAnimationPhysicsMode(animationPhysics_Dynamic,0.0);
    sprite->removePart(weight->getId());near(sprite->physics.getMass(),14,"removing an accessory clears membership");
    expect(!grip.isActive() && !body.isAttached(),"removed accessory leaves retained handles safe");
    body.setMass(100);near(sprite->physics.getMass(),14,"retained removed body no longer changes total");
    auto* next=sprite->createPart("next");next->setupPhysicsBody(10,20);sprite->attachAnimationPhysicsPart(next,hand);
    sprite->disableAnimationPhysics(0);near(sprite->physics.getMass(),24,"disable carries participating mass");
    next->physics.setMass(12);near(sprite->physics.getMass(),24,"disable releases accessory membership");
    grip.release();elbow.release();body.release();cleanupLayer(layer);
}

void generatedPhysicalRig(const std::string& path) {
    generatedRigDroppedAccessory(path);
    generatedRigMembership(path);
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);layer->enableCollisions();
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());sprite->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"),"generated physical pose enables");
    sprite->setupPhysicsBody(4,8);
    auto& host=static_cast<PhysicsBody&>(sprite->physics);
    expect(sprite->getAnimationPhysicsRoot()==0,"automatic physical root uses largest tree");
    auto* conflict=sprite->createPart("forearm");
    bool rejected=false;try{sprite->setupPhysicsFromAnimationRig(34);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && sprite->getPartCount()==1 && !sprite->isAnimationPhysicsEnabled(),"generated setup conflict is atomic");
    sprite->removePart(conflict->getId());
    sprite->setupPhysicsFromAnimationRig(34);
    auto* shoulder=sprite->findPart("shoulder");auto* forearm=sprite->findPart("forearm");auto* hand=sprite->findPart("hand");
    expect(shoulder && forearm && hand,"generated rig creates all named segments");
    near(host.getMass(),34,"host reports sum of components through retained native reference");
    sprite->createPart("unrelated")->setupPhysicsBody(100,100);
    near(host.getMass(),34,"unrelated Part bodies are not assembly members");
    near(shoulder->physics.getMass(),20,"reference lengths distribute initial mass");
    near(forearm->physics.getMass(),10,"one child gives own joint to child joint");
    near(hand->physics.getMass(),4,"leaf uses authored reference image dimensions");
    expect(host.getMode()==physicsBody_Kinematic,"host is coordinating kinematic body");
    expect(shoulder->physics.getMode()==physicsBody_Dynamic,"generated rig starts dynamic");
    const auto shape=hand->collider.getShapeId(0);
    near(hand->collider.getCapsuleRadius(shape),.2,"generated capsule has public editable geometry");
    expect(forearm->physics.getConstraintCount()==2,"shared joints are discoverable from either endpoint");
    auto& joint=forearm->physics.getConstraint(0);joint.addRef();
    expect(joint.getType()==constraint_Pivot && std::isinf(joint.getMaxForce()),"default hinge is unconstrained in angle and unlimited in strength");
    auto& limb=static_cast<PhysicsBody&>(forearm->physics);limb.addRef();
    const auto initialInertia=limb.getMomentOfInertia();
    limb.setMass(15);near(limb.getMomentOfInertia(),initialInertia*1.5,"component mass scales inertia");
    near(host.getMass(),39,"component mass change adjusts total without redistributing");
    host.setMass(78);near(limb.getMass(),30,"host mass preserves tuned component proportions");
    near(limb.getMomentOfInertia(),initialInertia*3,"host mass scales component inertia");
    limb.setVelocity(3,4).setAngularVelocity(2);
    limb.setMomentOfInertia(7);
    hand->collider.setCapsule(pdg::Point(-2,0),pdg::Point(2,0),.3);
    const auto tunedShape=hand->collider.getShapeId(0);
    sprite->setupPhysicsFromAnimationRig(17);
    near(limb.getMass(),5,"repeat setup restores original length proportions");
    near(limb.getMomentOfInertia(),7.0/6,"repeat setup preserves tuned inertia to mass ratio");
    near(limb.getVelocity().x,3,"repeat setup preserves motion");
    expect(&forearm->physics.getConstraint(0)==&joint && forearm->physics==limb,"repeat setup preserves body and joint identity");
    expect(hand->collider.getShapeId(0)==tunedShape,"repeat setup preserves edited collider identity");
    host.applyImpulse(Vector(10,0));near(shoulder->physics.getVelocity().x,1,"whole sprite impulse targets selected root");
    sprite->setAnimationPhysicsRoot("forearm");
    const auto state=limb.getState();const auto moment=limb.getMomentOfInertia();
    host.applyImpulse(Vector(0,5),pdg::Point(state.x+2,state.y));
    near(limb.getAngularVelocity(),2+10/moment,"root routed world point retains its lever arm");
    expect(sprite->getAnimationPhysicsRoot()==1,"live root selection may target a non-top-level bone");
    sprite->clearAnimationPhysicsRoot();expect(sprite->getAnimationPhysicsRoot()==0,"clear root restores automatic selection");
    rejected=false;try{sprite->setupPhysicsBody(4,8);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && host.getMass()==17,"ambiguous single-body setup rejects while assembly is active");
    rejected=false;try{host.setMass(std::numeric_limits<double>::max());}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && host.getMass()==17 && limb.getMass()==5,"overflow validates all component inertia before any change");
    const auto rootBefore=shoulder->physics.getState();
    auto* manager=SpriteManager::getSingletonInstance();manager->stepAnimationPhysics(10);layer->animateLayer(10);
    const auto rootAfter=shoulder->physics.getState();
    expect(rootAfter.x!=rootBefore.x || rootAfter.y!=rootBefore.y,"generated bodies participate in the shared solver");
    const auto bone=sprite->getAnimationBoneTransform("shoulder",animationSpace_World);
    near(bone.x,rootAfter.x-5*std::cos(rootAfter.rotation),"solved body publishes into final animation pose");
    sprite->disableAnimationPhysics(0);
    near(host.getMass(),17,"disable carries current total into single-body physics");
    expect(!joint.isActive() && limb.getSolver()==physicsSolver_Basic,"retained joints disconnect and retained bodies detach safely");
    expect(forearm->physics==PhysicsBody::NoPhysics && hand->collider==Collider::NoCollider,"disable retains Parts but removes generated associations");
    limb.setMass(100);near(host.getMass(),17,"retained old component no longer contributes mass");
    joint.release();limb.release();
    sprite->seekAnimation("reference",0);
    sprite->setFlipX(true);
    sprite->setupPhysicsFromAnimationRig(34);
    const auto reflected=sprite->findPart("shoulder")->physics.getState();
    const auto reflectedBone=sprite->getAnimationBoneTransform("shoulder",animationSpace_World);
    near(reflectedBone.x,reflected.x-5*std::cos(reflected.rotation),"reflected setup preserves body-to-bone mapping");
    manager->stepAnimationPhysics(10);layer->animateLayer(10);
    expect(sprite->isAnimationPhysicsEnabled(),"reflected generated rig remains active through physics publication");
    sprite->disableAnimationPhysics(0);
    auto* small=layer->createSpriteFromSpriterFile((path.substr(0,path.find_last_of('/')+1)+"physics-generation.scml").c_str());
    expect(small->enableAnimationPose("reference"),"zero-length reference pose enables");
    small->setupPhysicsFromAnimationRig(2,1000);
    auto* root=small->findPart("root");
    auto* wall=layer->createSprite();wall->setLocation(3,0);wall->setupPhysicsBody().setMode(physicsBody_Static);
    wall->setupCollider().setCircle(1);
    int contacts=0;
    root->collider.setCollisionFilter([&](const Collider&,const Collider&){++contacts;return true;});
    small->physics.applyImpulse(Vector(10,0));
    for (int i=0;i<50;++i) { manager->stepAnimationPhysics(10);layer->animateLayer(10); }
    expect(contacts>0 && root->physics.getState().x<2,"generated shared capsule produces real solver contacts");
    small->disableAnimationPhysics(0);
    auto* guy=layer->createSpriteFromSpriterFile((path.substr(0,path.find_last_of('/')+1)+"../spriter-samples/greyguy/player.scml").c_str());
    expect(guy->enableAnimationPose("idle"),"Grey Guy reference pose enables for generation");
    guy->setupPhysicsFromAnimationRig(70,1000);
    size_t components=0;double mass=0;
    for (const auto& name:guy->getAnimationBoneNames()) if (auto* part=guy->findPart(name)) {
        if (part->physics!=PhysicsBody::NoPhysics) {
            ++components;mass+=part->physics.getMass();
            const auto frame=part->getTransform(partSpace_World);
            near(std::hypot(frame.a,frame.b),1,"generated Part frame uses rigid physical units");
            near(std::hypot(frame.c,frame.d),1,"nonuniform bone display scales do not deform physical capsules");
        }
    }
    expect(components>5,"real sample generates a multi-limb physical character");
    near(mass,70,"real sample component masses add to requested total");
    manager->stepAnimationPhysics(10);layer->animateLayer(10);
    expect(guy->isAnimationPhysicsEnabled(),"real sample generated rig survives animation and solver publication");
    auto* skipped=layer->createSpriteFromSpriterFile((path.substr(0,path.find_last_of('/')+1)+"physics-generation.scml").c_str());
    expect(skipped->enableAnimationPose("reference"),"skipped ancestor pose enables");
    skipped->setAnimationPhysicsRoot("helper");skipped->setupPhysicsFromAnimationRig(2,1000);
    skipped->setAnimationPhysicsMode(animationPhysics_Kinematic,"root",true,0);
    expect(skipped->getAnimationPhysicsMode("helper")==animationPhysics_Kinematic,"subtree traversal includes bodies below skipped ancestors");
    rejected=false;try{skipped->setAnimationPhysicsMode(animationPhysics_Dynamic,"root");}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected,"single skipped bone selection rejects rather than selecting all bodies");
    cleanupLayer(layer);
}
