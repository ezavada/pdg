// Mixed rigs must distinguish gameplay frame edits from solver publication.
void rigFrameMovement(const std::string& directory) {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);
    auto* manager=SpriteManager::getSingletonInstance();
    auto tick=[&](int count=1){for(int i=0;i<count;++i){manager->stepAnimationPhysics(5);layer->animateLayer(5);}};
    for(int policy:{animationRoot_Fixed,animationRoot_Follow}) {
        auto* sprite=layer->createSpriteFromSpriterFile((directory+"arm.scml").c_str());
        sprite->pauseAnimation();expect(sprite->enableAnimationPose("reference"),"frame fixture enables");
        sprite->setLocation(100,100);
        AnimationPhysicsDefinition def;def.rootMode=policy;
        for(unsigned i=0;i<3;++i) {
            AnimationPhysicsBody b;b.bone=i;b.length=i==0?10:i==1?5:2;b.offsetX=b.length/2;b.radius=.25;
            b.mode=i==0?animationBody_Kinematic:animationBody_Dynamic;def.bodies.push_back(b);
        }
        for(unsigned i=0;i<2;++i) {
            AnimationPhysicsJoint j;j.parent=i;j.child=i+1;j.parentX=def.bodies[i].length/2;j.childX=-def.bodies[i+1].length/2;
            def.joints.push_back(j);
        }
        sprite->setupAnimationPhysics(def);
        auto& root=static_cast<PhysicsBody&>(sprite->findPart("shoulder")->physics);
        auto& child=static_cast<PhysicsBody&>(sprite->findPart("forearm")->physics);
        auto* joint=&child.getConstraint(0);
        const auto before=child.getState();
        sprite->setLocation(130,150);
        sprite->getAnimationPose(); // This used to consume the pending move in Follow mode.
        near(child.getState().x,before.x,"moving frame does not teleport dynamic descendants");
        tick();
        near(root.getState().x,137,"queried root retains gameplay translation X");
        near(root.getState().y,153,"queried root retains gameplay translation Y");
        sprite->setRotation(3.14159265358979323846/2);
        sprite->getAnimationPose();tick();
        near(root.getState().x,127,"frame rotation carries offset root X");
        near(root.getState().y,157,"frame rotation carries offset root Y");
        near(root.getState().rotation,3.14159265358979323846/2,"frame rotation reaches physical root");
        sprite->moveBy(Offset(20,10),.2);tick(50);
        near(root.getState().x,147,"programmed frame movement reaches physical root X");
        near(root.getState().y,167,"programmed frame movement reaches physical root Y");
        expect(&child.getConstraint(0)==joint && joint->isActive(),"frame edits preserve joint identity");
        near(sprite->physics.getMass(),3,"frame edits preserve assembly mass");
        sprite->setAnimationPhysicsDriveSettings({100,100},"shoulder");
        sprite->setAnimationPhysicsMode(animationPhysics_Driven,"shoulder",false,0);
        sprite->setLocation(sprite->getLocation()+Offset(10,0));
        sprite->getAnimationPose();tick();
        const auto target=root.getDriveState().x;
        for(int n=0;n<20;++n){sprite->getAnimationPose();tick();near(root.getDriveState().x,target,"followed root does not feed back into driven target");}
        sprite->setAnimationPhysicsMode(animationPhysics_Dynamic);
        const auto frame=sprite->getLocation();
        for(const char* name:{"shoulder","forearm","hand"})sprite->findPart(name)->physics.setVelocity(10,0).setAngularVelocity(0);
        tick(20);
        if(policy==animationRoot_Fixed)near(sprite->getLocation().x,frame.x,"Fixed frame stays independent of free rig");
        else {
            const auto pose=sprite->getAnimationPose();
            const auto pivot=pose.getWorldTransform(0,{sprite->getLocation().x,sprite->getLocation().y,sprite->getRotation()});
            near(pivot.x,root.getState().x-5*std::cos(root.getState().rotation),"Follow queries retain solved bone position");
            expect(std::abs(sprite->getLocation().x-frame.x)>.01,"Follow frame moves with free root");
        }
        sprite->disableAnimationPhysics(0);layer->removeSprite(sprite);
    }
    cleanupLayer(layer);
}

void rigLoadsAndReflection(const std::string& directory) {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);
    auto* manager=SpriteManager::getSingletonInstance();
    auto tick=[&]{manager->stepAnimationPhysics(10);layer->animateLayer(10);};
    auto* sprite=layer->createSpriteFromSpriterFile((directory+"arm.scml").c_str());
    sprite->pauseAnimation();sprite->enableAnimationPose("reference");
    AnimationPhysicsDefinition def;
    for(unsigned i=0;i<3;++i){AnimationPhysicsBody b;b.bone=i;b.length=2;b.radius=.2;def.bodies.push_back(b);}
    sprite->setupAnimationPhysics(def);
    auto& root=static_cast<PhysicsBody&>(sprite->findPart("shoulder")->physics);
    auto& child=static_cast<PhysicsBody&>(sprite->findPart("forearm")->physics);
    auto& hand=static_cast<PhysicsBody&>(sprite->findPart("hand")->physics);
    root.setMass(2).setMomentOfInertia(3).teleport(pdg::Point(0,0),0).setVelocity(4,6).setAngularVelocity(2);
    child.setMass(3).setMomentOfInertia(5).teleport(pdg::Point(10,0),0).setVelocity(4,26).setAngularVelocity(2);
    hand.setMass(5).setMomentOfInertia(7).teleport(pdg::Point(0,10),0).setVelocity(-16,6).setAngularVelocity(2);
    near(sprite->physics.getMomentOfInertia(),475,"assembly inertia includes parallel-axis offsets");
    near(sprite->physics.getAngularMomentum(),950,"assembly momentum includes orbital and spin motion");
    for(auto* body:{&root,&child,&hand})body->setVelocity(0,0).setAngularVelocity(0);
    const auto force=sprite->physics.applyForce(Vector(4,0),.02,.01);
    const auto local=root.addContinuousTorque(3);
    expect(force && local,"assembly and component maintain independent force handles");
    tick();near(root.getVelocity().x,0,"delayed assembly force has not fired");
    tick();near(root.getVelocity().x,.02,"assembly force reaches only selected root");
    near(child.getVelocity().x,0,"root force is not distributed over members");
    tick();tick();near(root.getVelocity().x,.04,"assembly duration expires exactly once");
    expect(!sprite->physics.removeForce(force),"expired assembly handle is gone");
    expect(root.removeForce(local),"removing assembly loads leaves member IDs intact");
    const auto continuous=sprite->physics.addContinuousTorque(30);
    sprite->setAnimationPhysicsRoot("forearm");const auto before=child.getAngularVelocity();tick();
    near(child.getAngularVelocity(),before+.06,"continuous assembly torque follows root reassignment");
    expect(sprite->physics.removeForce(continuous),"original assembly handle cancels after root change");
    const auto spin=child.getAngularVelocity();tick();near(child.getAngularVelocity(),spin,"cancelled torque stays cancelled");
    sprite->setAnimationPhysicsRoot("shoulder");
    const auto dormant=sprite->physics.applyTorque(30,.015,.005);
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,"shoulder",false,0);
    expect(!sprite->physics.addContinuousTorque(1),"new load against Kinematic root returns no handle");
    tick();tick();tick();
    expect(!sprite->physics.removeForce(dormant),"finite assembly load ages during Kinematic control");
    sprite->setAnimationPhysicsMode(animationPhysics_Dynamic,"shoulder",false,0);
    root.setAngularVelocity(0);const auto offCenter=root.getState();
    sprite->physics.applyForce(Vector(0,4),pdg::Point(offCenter.x+2,offCenter.y),.01);
    tick();near(root.getAngularVelocity(),.08/3,"off-center assembly force captures selected-root lever arm");
    root.teleport(pdg::Point(0,0),.2).setVelocity(2,3).setAngularVelocity(4);
    child.teleport(pdg::Point(10,0),.4).setVelocity(5,6).setAngularVelocity(7);
    hand.teleport(pdg::Point(20,2),.6);
    auto& pivot=root.createPivotJoint(child,pdg::Point(1,2),pdg::Point(3,4));
    auto& limit=root.createRotaryLimit(child,-.3,.7);
    auto* collider=&sprite->findPart("forearm")->collider.setCircle(1,pdg::Point(2,3));
    const auto mass=sprite->physics.getMass(),inertia=sprite->physics.getMomentOfInertia();
    const auto old=child.getState();const auto bound=collider->getBounds();
    sprite->setFlipX(true);
    near(child.getState().x,-old.x,"live horizontal flip reflects physical positions");
    near(child.getState().velocityX,-old.velocityX,"live flip reflects velocity");
    near(child.getAngularVelocity(),-old.angularVelocity,"live flip reverses spin");
    near(pivot.getAnchorA().y,-2,"flip reflects edited pivot A");
    near(pivot.getAnchorB().y,-4,"flip reflects edited pivot B");
    near(limit.getMinAngle(),-.7,"flip swaps and negates minimum angle");
    near(limit.getMaxAngle(),.3,"flip swaps and negates maximum angle");
    near(collider->getBounds().left,-bound.right,"asymmetric collider reflects with artwork");
    near(sprite->physics.getMass(),mass,"reflection preserves assembly mass");
    near(sprite->physics.getMomentOfInertia(),inertia,"reflection preserves inertia");
    sprite->setFlipX(false);
    near(child.getState().rotation,old.rotation,"double flip restores unwrapped rotation");
    near(pivot.getAnchorA().y,2,"double flip restores joint anchors");
    near(collider->getBounds().left,bound.left,"double flip restores collider geometry");
    // Detached physical bones remain where the solver put them.
    sprite->detachAnimationPhysicsPart(sprite->findPart("hand"));const auto detached=hand.getState();
    sprite->setFlipY(true);
    near(hand.getState().x,detached.x,"flip excludes detached body X");
    near(hand.getState().y,detached.y,"flip excludes detached body Y");
    near(sprite->getAnimationBoneTransform("hand",animationSpace_World).y,detached.y,"detached bone query follows its unreflected body");
    sprite->setFlipY(false);
    auto* outside=layer->createSprite();auto& external=outside->setupPhysicsBody();
    auto& boundary=external.createMotor(root,0,20);
    bool rejected=false;try{sprite->setFlipX(true);}catch(const std::logic_error&){rejected=true;}
    expect(rejected && !sprite->isFlippedX(),"boundary angular joint rejects reflection atomically");
    near(child.getState().x,old.x,"rejected reflection leaves body state intact");
    boundary.disconnect();
    sprite->disableAnimationPhysics(0);layer->removeSprite(sprite);
    for(bool generated:{false,true})for(bool initialFlip:{false,true}) {
        auto* model=layer->createSpriteFromSpriterFile((directory+"arm.scml").c_str());
        model->pauseAnimation();model->enableAnimationPose("reference");
        model->setLocation(70,80);model->setRotation(.3);model->setFlipX(initialFlip);
        if(generated)model->setupPhysicsFromAnimationRig(10);else model->setupAnimationPhysics(def);
        model->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
        tick();
        const auto oldBone=model->getAnimationBoneTransform("forearm",animationSpace_World);
        const auto oldBody=model->findPart("forearm")->physics.getState();
        model->setFlipX(!initialFlip);tick();
        model->setFlipX(initialFlip);tick();
        near(model->getAnimationBoneTransform("forearm",animationSpace_World).x,oldBone.x,"Kinematic reflection roundtrip preserves posed bone X");
        near(model->findPart("forearm")->physics.getState().x,oldBody.x,"Kinematic reflection roundtrip preserves physical X");
        model->setAnimationPhysicsMode(animationPhysics_Dynamic);
        auto* limb=model->findPart("forearm");
        auto moved=limb->physics.getState();limb->physics.teleport(pdg::Point(moved.x+.01,moved.y),moved.rotation+.01);
        model->setAnimationPhysicsMode(animationPhysics_Kinematic,.1);
        tick();model->setFlipY(true);
        for(int n=0;n<300 && model->getAnimationPhysicsMode()!=animationPhysics_Kinematic;++n)tick();
        expect(model->getAnimationPhysicsMode()==animationPhysics_Kinematic,"recovery completes after live reflection");
        model->setFlipY(false);tick(); // Completed recovery may retain an inactive motor.
        model->disableAnimationPhysics(0);layer->removeSprite(model);
    }
    cleanupLayer(layer);
}
